#include "jp/ggaf/dx/model/MorphMeshModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MorphMeshActor.h"
#include "jp/ggaf/dx/effect/MorphMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

MorphMeshModel::MorphMeshModel(const char* prm_model_id) : Model(prm_model_id) {
    _obj_class |= Obj_GgafDx_MorphMeshModel;
    _TRACE3_("_model_id="<<_model_id);
    _morph_target_num = 0;

    _papModel3D = nullptr;
    _papMeshesFront = nullptr;

    _pVertexDeclaration = nullptr;
    _paVertexBuffer_primary = nullptr;
    _paIDirect3DVertexBuffer9_morph = nullptr;
    _paIndexBuffer = nullptr;
    _paVtxBuffer_data_primary = nullptr;
    _papaVtxBuffer_data_morph = nullptr;
    _paIndex16Buffer_data = nullptr;
    _paIndex32Buffer_data = nullptr;
    _paIndexParam = nullptr;
    _material_list_grp_num = 0;
    _size_vertices_primary = 0;
    _size_vertex_unit_primary = 0;
    _size_vertices_morph = 0;
    _size_vertex_unit_morph = 0;
    _max_draw_set_num = 1;
    _is_65535 = true;
}

HRESULT MorphMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* pDevice = pCARETAKER->_pID3DDevice9;
    _TRACE4_("MorphMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //対象アクター
    const MorphMeshActor* const pTargetActor = (MorphMeshActor*)prm_pActor_target;
    //対象アクターのエフェクトラッパ
    MorphMeshEffect* const pMorphMeshEffect = (MorphMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    //頂点バッファ設定
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //頂点フォーマット
        pDevice->SetStreamSource(0, _paVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        const UINT material_no = _paIndexParam[i].MaterialNo;
        if (ModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //マテリアル0番は、特別に規定のテクスチャを設定する仕様
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("MorphMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
               _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "End() に失敗しました。");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
             }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMorphMeshEffect->_effect_name<<"("<<pMorphMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
            //モーフターゲットの数により pass を切り替えている
            //プリマリメッシュのみ                             = pass0
            //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
            //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
            //以下最大９まで
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "BeginPass("<<_morph_target_num<<") に失敗しました。");

#ifdef MY_DEBUG
            if (pMorphMeshEffect->_begin) {
                throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMorphMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMorphMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
    }
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMorphMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}

void MorphMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //【MorphMeshModel再構築（＝初期化）処理概要】
    //基本的にはrestoreMeshModelの処理を一つ次元（配列）を増やしたようなもの
    //１）プライマリ＋モーフターゲットｘN の、頂点バッファ、頂点インデックスバッファ を作成
    //２）それぞれのXファイルから、独自に次の情報を読み込み、頂点バッファ、頂点インデックスバッファ に流し込む。
    //３）２）を行なう過程で、同時に MeshModel に次のメンバを作成。
    //　　　　・プライマリメッシュ頂点バッファの写し
    //　　　　・モーフターゲットｘN の頂点バッファの写し
    //　　　　・頂点インデックスバッファの写し（プライマリメッシュのみ）
    //　　　　・マテリアル配列(要素数＝マテリアル数。プライマリメッシュのみ)
    //　　　　・テクスチャ配列(要素数＝マテリアル数。プライマリメッシュのみ)
    //　　　　・DrawIndexedPrimitive用引数配列(要素数＝マテリアルリストが変化した数。プライマリメッシュのみ)
    if (_paVtxBuffer_data_primary == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::MeshXFileFmt xdata;

        std::string model_def_file = std::string(_model_id) + ".meshx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
        pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
        _matBaseTransformMatrix = xdata.BaseTransformMatrix;
        _draw_set_num = xdata.DrawSetNum;
        if (_draw_set_num != 1) {
            _TRACE_("MorphMeshModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 1 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
            _draw_set_num = 1;
        }
        _morph_target_num = xdata.XFileNum - 1;
        int morph_target_num = _morph_target_num;
        std::string* paXfilepath = NEW std::string[morph_target_num+1];
        for (int i = 0; i < morph_target_num+1; i++) {
            paXfilepath[i] = Model::getXFilePath(xdata.XFileNames[i]);
        }

        HRESULT hr;
        //流し込む頂点バッファデータ作成
        ToolBox::IO_Model_X* paIOX = nullptr;
        Frm::Model3D**                  papModel3D = nullptr;
        Frm::Mesh**                     papMeshesFront = nullptr;

        MorphMeshModel::INDEXPARAM*     paIndexParam = nullptr;
        MorphMeshModel::VERTEX_PRIMARY* paVtxBuffer_data_primary = nullptr;
        MorphMeshModel::VERTEX_MORPH**  papaVtxBuffer_data_morph = nullptr;
        uint16_t* paIdx16Buffer_data = nullptr;
        uint32_t* paIdx32Buffer_data = nullptr;

        paIOX = NEW ToolBox::IO_Model_X[morph_target_num+1];
        papModel3D = NEW Frm::Model3D*[morph_target_num+1];
        papMeshesFront = NEW Frm::Mesh*[morph_target_num+1];
        papaVtxBuffer_data_morph = NEW MorphMeshModel::VERTEX_MORPH*[morph_target_num];
        int nVertices = 0;
        int nTextureCoords = 0;
        int nFaces = 0;
//        int nFaceNormals = 0;
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = paIOX[pattern].Load(paXfilepath[pattern], papModel3D[pattern]);
            if (r == false) {
                throwCriticalException("Xファイルの読込み失敗。2/ とか忘れてませんか？ 対象="<<paXfilepath[pattern]);
            }
            //メッシュを結合する前に、情報を確保しておく
            int nMesh = (int)papModel3D[pattern]->_Meshes.size();
            uint32_t* paNumVertices = NEW uint32_t[nMesh];
            int index_Mesh = 0;
            for (std::list<Frm::Mesh*>::iterator iteMeshes = papModel3D[pattern]->_Meshes.begin();
                    iteMeshes != papModel3D[pattern]->_Meshes.end(); iteMeshes++) {
                paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
                index_Mesh++;
            }
            papModel3D[pattern]->ConcatenateMeshes(); //メッシュを繋げる
            papMeshesFront[pattern] = papModel3D[pattern]->_Meshes.front();
            nVertices = papMeshesFront[pattern]->_nVertices;
            nTextureCoords = papMeshesFront[pattern]->_nTextureCoords;
            nFaces = papMeshesFront[pattern]->_nFaces;
//            nFaceNormals = papMeshesFront[pattern]->_nFaceNormals;

            if (nFaces * 3 > 65535) {
                _is_65535 = true;
                _TRACE_("【警告】頂点インデックスが 65535 を超えたかもしれません。しらんけど。\n対象Model："<<getName()<<"  インデックス:3*"<<nFaces<<"(faces) nVertices:"<<nVertices);
            }

            if (pattern == 0) {
                //プライマリメッシュ
                paVtxBuffer_data_primary = NEW MorphMeshModel::VERTEX_PRIMARY[nVertices];
                _size_vertices_primary = sizeof(MorphMeshModel::VERTEX_PRIMARY) * nVertices;
                _size_vertex_unit_primary = sizeof(MorphMeshModel::VERTEX_PRIMARY);
                //法線以外設定
                for (int i = 0; i < nVertices; i++) {
                    paVtxBuffer_data_primary[i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    paVtxBuffer_data_primary[i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    paVtxBuffer_data_primary[i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    paVtxBuffer_data_primary[i].nx = 0.0f;
                    paVtxBuffer_data_primary[i].ny = 0.0f;
                    paVtxBuffer_data_primary[i].nz = 0.0f;
                    paVtxBuffer_data_primary[i].color = D3DCOLOR_ARGB(255,255,255,255);
                    if (i < nTextureCoords) {
                        paVtxBuffer_data_primary[i].tu = papMeshesFront[pattern]->_TextureCoords[i].data[0];  //出来る限りUV座標設定
                        paVtxBuffer_data_primary[i].tv = papMeshesFront[pattern]->_TextureCoords[i].data[1];
                    } else {
                        paVtxBuffer_data_primary[i].tu = 0.0f;
                        paVtxBuffer_data_primary[i].tv = 0.0f;
                    }
                }
            } else {
                //モーフターゲットメッシュ
                papaVtxBuffer_data_morph[pattern-1] = NEW MorphMeshModel::VERTEX_MORPH[nVertices];
                _size_vertices_morph = sizeof(MorphMeshModel::VERTEX_MORPH) * nVertices;
                _size_vertex_unit_morph = sizeof(MorphMeshModel::VERTEX_MORPH);
                //法線以外設定
                for (int i = 0; i < nVertices; i++) {
                    papaVtxBuffer_data_morph[pattern-1][i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    papaVtxBuffer_data_morph[pattern-1][i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    papaVtxBuffer_data_morph[pattern-1][i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    papaVtxBuffer_data_morph[pattern-1][i].nx = 0.0f;
                    papaVtxBuffer_data_morph[pattern-1][i].ny = 0.0f;
                    papaVtxBuffer_data_morph[pattern-1][i].nz = 0.0f;
                }
            }

            if (nVertices < nTextureCoords) {
                _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
                _TRACE_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<paXfilepath[pattern]);
            }

            //法線設定とFrameTransformMatrix適用
            if (pattern == 0) { //プライマリメッシュ
                prepareVtx((void*)paVtxBuffer_data_primary, _size_vertex_unit_primary,
                           papModel3D[pattern], paNumVertices);
                //距離
                FLOAT model_bounding_sphere_radius;
                for (int i = 0; i < nVertices; i++) {
                    model_bounding_sphere_radius = (FLOAT)(sqrt(paVtxBuffer_data_primary[i].x * paVtxBuffer_data_primary[i].x +
                                                                paVtxBuffer_data_primary[i].y * paVtxBuffer_data_primary[i].y +
                                                                paVtxBuffer_data_primary[i].z * paVtxBuffer_data_primary[i].z));
                    if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                        _bounding_sphere_radius = model_bounding_sphere_radius;
                    }
                }
            } else {            //ターゲットメッシュ
                prepareVtx((void*)(papaVtxBuffer_data_morph[pattern-1]), _size_vertex_unit_morph,
                           papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);
        }

        //インデックスバッファ取得
        if (_is_65535) {
            paIdx32Buffer_data = NEW uint32_t[nFaces*3];
            for (int i = 0; i < nFaces; i++) {
                paIdx32Buffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
                paIdx32Buffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
                paIdx32Buffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
            }
        } else {
            paIdx16Buffer_data = NEW uint16_t[nFaces*3];
            for (int i = 0; i < nFaces; i++) {
                paIdx16Buffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
                paIdx16Buffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
                paIdx16Buffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
            }
        }

        //描画時（DrawIndexedPrimitive）のパラメータリスト作成
        MorphMeshModel::INDEXPARAM* paParam = NEW MorphMeshModel::INDEXPARAM[nFaces];

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            materialno = papMeshesFront[0]->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //_TRACE3_("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = UINT_MAX; //次回ブレイク時に設定、変な値にしとく
                paParam[paramno].NumVertices = UINT_MAX; //次回ブレイク時に設定
                paParam[paramno].StartIndex = faceNoCnt*3;
                paParam[paramno].PrimitiveCount = UINT_MAX; //次回ブレイク時に設定

                if (faceNoCnt > 0) {
                    paParam[paramno-1].MinIndex = min_num_vertices;
                    paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //リセット
                    max_num_vertices = 0;
                    min_num_vertices = UINT_MAX;
                }
                paramno++;
            }
            if (_is_65535) {
                if (max_num_vertices <  paIdx32Buffer_data[faceNoCnt*3 + 0]) {
                    max_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 0];
                }
                if (max_num_vertices <  paIdx32Buffer_data[faceNoCnt*3 + 1]) {
                    max_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 1];
                }
                if (max_num_vertices <  paIdx32Buffer_data[faceNoCnt*3 + 2]) {
                    max_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 2];
                }
                if (min_num_vertices >  paIdx32Buffer_data[faceNoCnt*3 + 0]) {
                    min_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 0];
                }
                if (min_num_vertices >  paIdx32Buffer_data[faceNoCnt*3 + 1]) {
                    min_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 1];
                }
                if (min_num_vertices >  paIdx32Buffer_data[faceNoCnt*3 + 2]) {
                    min_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 2];
                }
            } else {
                if (max_num_vertices <  paIdx16Buffer_data[faceNoCnt*3 + 0]) {
                     max_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 0];
                 }
                 if (max_num_vertices <  paIdx16Buffer_data[faceNoCnt*3 + 1]) {
                     max_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 1];
                 }
                 if (max_num_vertices <  paIdx16Buffer_data[faceNoCnt*3 + 2]) {
                     max_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 2];
                 }
                 if (min_num_vertices >  paIdx16Buffer_data[faceNoCnt*3 + 0]) {
                     min_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 0];
                 }
                 if (min_num_vertices >  paIdx16Buffer_data[faceNoCnt*3 + 1]) {
                     min_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 1];
                 }
                 if (min_num_vertices >  paIdx16Buffer_data[faceNoCnt*3 + 2]) {
                     min_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 2];
                 }
            }
            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        paIndexParam = NEW MorphMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            paIndexParam[i].MinIndex = paParam[i].MinIndex;
            paIndexParam[i].NumVertices = paParam[i].NumVertices;
            paIndexParam[i].StartIndex = paParam[i].StartIndex;
            paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
        }
        _material_list_grp_num = paramno;
        delete[] paParam;


        GGAF_DELETEARR(paIOX);
        GGAF_DELETEARR(paXfilepath);

        //モデルに保持させる
        _papModel3D               = papModel3D;
        _papMeshesFront           = papMeshesFront;
        if (_is_65535) {
            _paIndex32Buffer_data = paIdx32Buffer_data;
        } else {
            _paIndex16Buffer_data = paIdx16Buffer_data;
        }
        _paVtxBuffer_data_primary = paVtxBuffer_data_primary;
        _papaVtxBuffer_data_morph = papaVtxBuffer_data_morph;
        _paIndexParam             = paIndexParam;
        //マテリアル設定
        //マテリアルはプライマリメッシュのマテリアル情報を、
        //プライマリ及び全モーフターゲットのマテリアルとする。
        //よってpapMeshesFront[0]だけ使う、残りは使わない。
        //TODO:将来的にはモーフターゲット別にマテリアル設定できれば表現が増す。いつかしようか、多分だいぶ先。
        setMaterial(papMeshesFront[0]);
    }

    if (_pVertexDeclaration == nullptr) {
        HRESULT hr;
        int elemnum = (4+(2*_morph_target_num))+1; //D3DVERTEXELEMENT9 構造体の配列要素数
        D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[elemnum];
                                                         // 4 = プライマリメッシュ
                                                         // (2*morph_target_num) = モーフターゲットメッシュ
                                                         // 1 = D3DDECL_END()
        //プライマリメッシュ部頂点フォーマット
        //FVFは使えないので、CreateVertexDeclarationで
        //TODO:頂点フォーマットを毎回構築ではなくて、モデル側に保時させたい。
        //プライマリ部頂点フォーマット
        //float x, y, z; // 頂点座標
        paVtxelem[0].Stream = 0;
        paVtxelem[0].Offset = 0;
        paVtxelem[0].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[0].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[0].Usage = D3DDECLUSAGE_POSITION;
        paVtxelem[0].UsageIndex = 0;
        //float nx, ny, nz; // 法線
        paVtxelem[1].Stream = 0;
        paVtxelem[1].Offset = sizeof(float)*3;
        paVtxelem[1].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[1].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[1].Usage = D3DDECLUSAGE_NORMAL;
        paVtxelem[1].UsageIndex = 0;
        //DWORD color; // 頂点カラー
        paVtxelem[2].Stream = 0;
        paVtxelem[2].Offset = sizeof(float)*6;
        paVtxelem[2].Type = D3DDECLTYPE_D3DCOLOR;
        paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[2].Usage = D3DDECLUSAGE_COLOR;
        paVtxelem[2].UsageIndex = 0;
        //float tu, tv; // テクスチャ座標
        paVtxelem[3].Stream = 0;
        paVtxelem[3].Offset = sizeof(float)*6+sizeof(DWORD);
        paVtxelem[3].Type = D3DDECLTYPE_FLOAT2;
        paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[3].Usage = D3DDECLUSAGE_TEXCOORD;
        paVtxelem[3].UsageIndex = 0;
        //モーフターゲットメッシュ部頂点フォーマット
        for (int i = 4, s = 1; i < elemnum-1; i+=2, s++) {
            //float x, y, z; // 頂点座標
            paVtxelem[i].Stream = s;
            paVtxelem[i].Offset = 0;
            paVtxelem[i].Type = D3DDECLTYPE_FLOAT3;
            paVtxelem[i].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[i].Usage = D3DDECLUSAGE_POSITION;
            paVtxelem[i].UsageIndex = s;
            //float nx, ny, nz; // 法線
            paVtxelem[i+1].Stream = s;
            paVtxelem[i+1].Offset = sizeof(float)*3;
            paVtxelem[i+1].Type = D3DDECLTYPE_FLOAT3;
            paVtxelem[i+1].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[i+1].Usage = D3DDECLUSAGE_NORMAL;
            paVtxelem[i+1].UsageIndex = s;
        }
        //D3DDECL_END()
        paVtxelem[elemnum-1].Stream = 0xFF;
        paVtxelem[elemnum-1].Offset = 0;
        paVtxelem[elemnum-1].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[elemnum-1].Method = 0;
        paVtxelem[elemnum-1].Usage = 0;
        paVtxelem[elemnum-1].UsageIndex = 0;

        hr = pCARETAKER->_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "pCARETAKER->_pID3DDevice9->CreateVertexDeclaration 失敗 model="<<(_model_id));
        //ストリーム数取得        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);

        GGAF_DELETEARR(paVtxelem);
    }
    //頂点バッファ作成
    if (_paVertexBuffer_primary == nullptr) {
        HRESULT hr;
        _paIDirect3DVertexBuffer9_morph = NEW LPDIRECT3DVERTEXBUFFER9[_morph_target_num];
        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {

            if (pattern == 0) {
                //プライマリ頂点バッファ
                hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_primary,
                        D3DUSAGE_WRITEONLY,
                        0, //MorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(_paVertexBuffer_primary),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗（プライマリ） model="<<(_model_id));
                void *paVertexBuffer;
                hr = _paVertexBuffer_primary->Lock(0, _size_vertices_primary, (void**)&paVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗（プライマリ） model="<<_model_id);
                memcpy(paVertexBuffer, _paVtxBuffer_data_primary, _size_vertices_primary); //paVertexBuffer ← paVertex
                _paVertexBuffer_primary->Unlock();
            } else {
                //モーフターゲット頂点バッファ
                hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_morph,
                        D3DUSAGE_WRITEONLY,
                        0, //MorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(_paIDirect3DVertexBuffer9_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗（モーフ:"<<pattern-1<<"） model="<<(_model_id));
                void *paVertexBuffer;
                hr = _paIDirect3DVertexBuffer9_morph[pattern-1]->Lock(0, _size_vertices_morph, (void**)&paVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗（モーフ:"<<pattern-1<<"） model="<<_model_id);
                memcpy(paVertexBuffer, _papaVtxBuffer_data_morph[pattern-1], _size_vertices_morph); //paVertexBuffer ← paVertex
                _paIDirect3DVertexBuffer9_morph[pattern-1]->Unlock();
            }
        }
    }


    //インデックスバッファデータ作成（プライマリ、モーフターゲット共に同じ）
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        if (_is_65535) {
            int nFaces = _papMeshesFront[0]->_nFaces;
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                        sizeof(uint32_t) * nFaces * 3,
                                        D3DUSAGE_WRITEONLY,
                                        D3DFMT_INDEX32,
                                        D3DPOOL_DEFAULT,
                                        &(_paIndexBuffer),
                                        nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer, _paIndex32Buffer_data , sizeof(uint32_t) * nFaces * 3);
            _paIndexBuffer->Unlock();
        } else {
            int nFaces = _papMeshesFront[0]->_nFaces;
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                        sizeof(uint16_t) * nFaces * 3,
                                        D3DUSAGE_WRITEONLY,
                                        D3DFMT_INDEX16,
                                        D3DPOOL_DEFAULT,
                                        &(_paIndexBuffer),
                                        nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer, _paIndex16Buffer_data , sizeof(uint16_t) * nFaces * 3);
            _paIndexBuffer->Unlock();
        }
    }

    if (!_papTextureConnection) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    _TRACE3_("_model_id=" << _model_id << " end");
}

void MorphMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MorphMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");

    //テクスチャを解放
    if (_papTextureConnection) {
        for (DWORD i = 0; i < _num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列

    for (int pattern = 0; pattern <= _morph_target_num; pattern++) {
        if (pattern == 0) {
            GGAF_RELEASE(_paVertexBuffer_primary);
        } else {
            GGAF_RELEASE(_paIDirect3DVertexBuffer9_morph[pattern-1]);
        }
    }
    GGAF_DELETEARR(_paIDirect3DVertexBuffer9_morph);
    GGAF_RELEASE(_paIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);
    _TRACE3_("_model_id=" << _model_id << " end");

}
MorphMeshModel::~MorphMeshModel() {

    for (int pattern = 0; pattern <= _morph_target_num; pattern++) {
        if (pattern == 0) {
            GGAF_DELETEARR(_paVtxBuffer_data_primary);
        } else {
            GGAF_DELETEARR(_papaVtxBuffer_data_morph[pattern-1]);
        }
        if (_papModel3D) {
            Frm::Model3D* p = _papModel3D[pattern];
            GGAF_DELETE(p);
        }
    }
    GGAF_DELETEARR(_papaVtxBuffer_data_morph);
    GGAF_DELETEARR(_papModel3D);
    //_papMeshesFront[0],_papMeshesFront[1] は _papModel3D をDELETEしているのでする必要は無い
    GGAF_DELETEARR(_papMeshesFront);
    _papMeshesFront = nullptr;
    GGAF_DELETEARR_NULLABLE(_paIndex16Buffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex32Buffer_data);
    GGAF_DELETEARR(_paIndexParam);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}

