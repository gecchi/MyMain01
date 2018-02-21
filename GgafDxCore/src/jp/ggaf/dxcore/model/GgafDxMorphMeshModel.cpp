#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxConfig.h"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorphMeshModel::GgafDxMorphMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ") Begin");
    // 下位実装クラスが指定するモデル名は"M/4/xxxxx"という形式で、GgafDxModelManagerは
    // "M"からGgafDxMorphMeshModelと判断し、"M"を取り除いた"4/XXXX"をモデル名として扱う。
    // prm_model_name には "4/XXXX" が、渡ってくる。
    // プライマリのメッシュが1、モーフターゲットのメッシュが4つという意味
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そう
    // モデル名からフターゲット数を取得
    _TRACE_("GgafDxMorphMeshModel prm_model_name="<<prm_model_name);

    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() != 2) {
        throwGgafCriticalException("モデルIDにモーフターゲット数が指定されてません。prm_model_name="<<prm_model_name);
    } else {
        _morph_target_num = STOI(names[0]);
        _TRACE_("GgafDxMorphMeshModel モーフターゲット数は指定あり、_morph_target_num="<<_morph_target_num);
        if (_morph_target_num > 6) {
            _TRACE_(FUNC_NAME<<" モーフターゲット数が最大6個以上指定されてます。意図していますか？ _morph_target_num="<<_morph_target_num<<"/_model_name="<<_model_name);
        }
    }

    _papModel3D = nullptr;
    _papMeshesFront = nullptr;

    _pVertexDeclaration = nullptr;
    _pVertexBuffer_primary = nullptr;
    _paIDirect3DVertexBuffer9_morph = nullptr;
    _pIndexBuffer = nullptr;
    _paVtxBuffer_data_primary = nullptr;
    _papaVtxBuffer_data_morph = nullptr;
    _paIndexBuffer_data = nullptr;
    _paIndexParam = nullptr;
    _material_list_grp_num = 0;
    _size_vertices_primary = 0;
    _size_vertex_unit_primary = 0;
    _size_vertices_morph = 0;
    _size_vertex_unit_morph = 0;

    _obj_model |= Obj_GgafDxMorphMeshModel;
}

HRESULT GgafDxMorphMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    _TRACE4_("GgafDxMorphMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //対象アクター
    const GgafDxMorphMeshActor* const pTargetActor = (GgafDxMorphMeshActor*)prm_pActor_target;
    //対象アクターのエフェクトラッパ
    GgafDxMorphMeshEffect* const pMorphMeshEffect = (GgafDxMorphMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    //頂点バッファ設定
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //頂点フォーマット
        pDevice->SetStreamSource(0, _pVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        pDevice->SetIndices(_pIndexBuffer);

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
        if (GgafDxModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //マテリアル0番は、特別に規定のテクスチャを設定する仕様
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("GgafDxMorphMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
               _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "End() に失敗しました。");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
             }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name<<"("<<pMorphMeshEffect<<")");
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
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMorphMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMorphMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}

void GgafDxMorphMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    //【GgafDxMorphMeshModel再構築（＝初期化）処理概要】
    //基本的にはrestoreMeshModelの処理を一つ次元（配列）を増やしたようなもの
    //１）プライマリ＋モーフターゲットｘN の、頂点バッファ、頂点インデックスバッファ を作成
    //２）それぞれのXファイルから、独自に次の情報を読み込み、頂点バッファ、頂点インデックスバッファ に流し込む。
    //３）２）を行なう過程で、同時に GgafDxMeshModel に次のメンバを作成。
    //　　　　・プライマリメッシュ頂点バッファの写し
    //　　　　・モーフターゲットｘN の頂点バッファの写し
    //　　　　・頂点インデックスバッファの写し（プライマリメッシュのみ）
    //　　　　・マテリアル配列(要素数＝マテリアル数。プライマリメッシュのみ)
    //　　　　・テクスチャ配列(要素数＝マテリアル数。プライマリメッシュのみ)
    //　　　　・DrawIndexedPrimitive用引数配列(要素数＝マテリアルリストが変化した数。プライマリメッシュのみ)
    int morph_target_num = _morph_target_num;

    std::string* paXfileName = NEW std::string[morph_target_num+1];

    for (int i = 0; i < morph_target_num+1; i++) {
        char* xfilename_base = _model_name + 2; //２文字目以降  "2/ceres" → "ceres"
        paXfileName[i] = GgafDxModelManager::getMeshFileName(std::string(xfilename_base) + "_" + (char)('0'+i));
        if (paXfileName[i] == "") {
             throwGgafCriticalException("メッシュファイル(*.x)が見つかりません。model_name="<<(std::string(xfilename_base) + "_" + (char)('0'+i)));
        }
    }
    HRESULT hr;
    //流し込む頂点バッファデータ作成
    ToolBox::IO_Model_X* paIOX = nullptr;
    Frm::Model3D**                        papModel3D = nullptr;
    Frm::Mesh**                           papMeshesFront = nullptr;

    GgafDxMorphMeshModel::INDEXPARAM*     paIndexParam = nullptr;
    GgafDxMorphMeshModel::VERTEX_PRIMARY* paVtxBuffer_data_primary = nullptr;
    GgafDxMorphMeshModel::VERTEX_MORPH**  papaVtxBuffer_data_morph = nullptr;
    WORD*                                 paIdxBuffer_data = nullptr;
    D3DMATERIAL9*                         paMaterial = nullptr;

    GgafDxTextureConnection** model_papTextureConnection = nullptr;

    if (_papModel3D == nullptr) {
        paIOX = NEW ToolBox::IO_Model_X[morph_target_num+1];
        papModel3D = NEW Frm::Model3D*[morph_target_num+1];
        papMeshesFront = NEW Frm::Mesh*[morph_target_num+1];
        papaVtxBuffer_data_morph = NEW GgafDxMorphMeshModel::VERTEX_MORPH*[morph_target_num];
        int nVertices = 0;
        int nTextureCoords = 0;
        int nFaces = 0;
//        int nFaceNormals = 0;
        FLOAT model_bounding_sphere_radius;
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = paIOX[pattern].Load(paXfileName[pattern], papModel3D[pattern]);
            if (r == false) {
                throwGgafCriticalException("Xファイルの読込み失敗。2/ とか忘れてませんか？ 対象="<<paXfileName[pattern]);
            }
            //メッシュを結合する前に、情報を確保しておく
            int nMesh = (int)papModel3D[pattern]->_Meshes.size();
            uint16_t* paNumVertices = NEW uint16_t[nMesh];
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

            if (nVertices*(morph_target_num+1) > 65535) {
                throwGgafCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nVertices:"<<nVertices<<"  セット数:"<<(morph_target_num+1));
            }

            if (pattern == 0) {
                //プライマリメッシュ
                paVtxBuffer_data_primary = NEW GgafDxMorphMeshModel::VERTEX_PRIMARY[nVertices];
                _size_vertices_primary = sizeof(GgafDxMorphMeshModel::VERTEX_PRIMARY) * nVertices;
                _size_vertex_unit_primary = sizeof(GgafDxMorphMeshModel::VERTEX_PRIMARY);
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

                    //距離
                    model_bounding_sphere_radius = (FLOAT)(sqrt(paVtxBuffer_data_primary[i].x * paVtxBuffer_data_primary[i].x +
                                                                paVtxBuffer_data_primary[i].y * paVtxBuffer_data_primary[i].y +
                                                                paVtxBuffer_data_primary[i].z * paVtxBuffer_data_primary[i].z));
                    if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                        _bounding_sphere_radius = model_bounding_sphere_radius;
                    }
                }
            } else {
                //モーフターゲットメッシュ
                papaVtxBuffer_data_morph[pattern-1] = NEW GgafDxMorphMeshModel::VERTEX_MORPH[nVertices];
                _size_vertices_morph = sizeof(GgafDxMorphMeshModel::VERTEX_MORPH) * nVertices;
                _size_vertex_unit_morph = sizeof(GgafDxMorphMeshModel::VERTEX_MORPH);
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
                _TRACE_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<paXfileName[pattern]);
            }

            //法線設定とFrameTransformMatrix適用
            if (pattern == 0) { //プライマリメッシュ
                prepareVtx((void*)paVtxBuffer_data_primary, _size_vertex_unit_primary,
                           papModel3D[pattern], paNumVertices);
            } else {            //ターゲットメッシュ
                prepareVtx((void*)(papaVtxBuffer_data_morph[pattern-1]), _size_vertex_unit_morph,
                           papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);

        }

        //インデックスバッファ取得
        paIdxBuffer_data = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            paIdxBuffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
            paIdxBuffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
            paIdxBuffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
        }

        //描画時（DrawIndexedPrimitive）のパラメータリスト作成
        GgafDxMorphMeshModel::INDEXPARAM* paParam = NEW GgafDxMorphMeshModel::INDEXPARAM[nFaces];

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

            if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 0]) {
                max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 0];
            }
            if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 1]) {
                max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 1];
            }
            if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 2]) {
                max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 2];
            }
            if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 0]) {
                min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 0];
            }
            if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 1]) {
                min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 1];
            }
            if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 2]) {
                min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 2];
            }
            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        paIndexParam = NEW GgafDxMorphMeshModel::INDEXPARAM[paramno];
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
    }

    if (_pVertexDeclaration == nullptr) {

        int elemnum = (4+(2*morph_target_num))+1; //D3DVERTEXELEMENT9 構造体の配列要素数
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

        hr = GgafDxGod::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->CreateVertexDeclaration 失敗 model="<<(_model_name));
        //ストリーム数取得        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);

        GGAF_DELETEARR(paVtxelem);
    }

    //頂点バッファ作成
    if (_pVertexBuffer_primary == nullptr) {
        _paIDirect3DVertexBuffer9_morph = NEW LPDIRECT3DVERTEXBUFFER9[morph_target_num];
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {

            if (pattern == 0) {
                //プライマリ頂点バッファ
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_primary,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDxMorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(_pVertexBuffer_primary),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗（プライマリ） model="<<(_model_name));
                void *pVertexBuffer;
                hr = _pVertexBuffer_primary->Lock(0, _size_vertices_primary, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗（プライマリ） model="<<_model_name);
                memcpy(pVertexBuffer, paVtxBuffer_data_primary, _size_vertices_primary); //pVertexBuffer ← paVertex
                _pVertexBuffer_primary->Unlock();
            } else {
                //モーフターゲット頂点バッファ
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_morph,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDxMorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(_paIDirect3DVertexBuffer9_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗（モーフ:"<<pattern-1<<"） model="<<(_model_name));
                void *pVertexBuffer;
                hr = _paIDirect3DVertexBuffer9_morph[pattern-1]->Lock(0, _size_vertices_morph, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗（モーフ:"<<pattern-1<<"） model="<<_model_name);
                memcpy(pVertexBuffer, papaVtxBuffer_data_morph[pattern-1], _size_vertices_morph); //pVertexBuffer ← paVertex
                _paIDirect3DVertexBuffer9_morph[pattern-1]->Unlock();
            }
        }
    }


    //インデックスバッファデータ作成（プライマリ、モーフターゲット共に同じ）
    if (_pIndexBuffer == nullptr) {
        int nFaces = papMeshesFront[0]->_nFaces;

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));
        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , paIdxBuffer_data , sizeof(WORD) * nFaces * 3);
        _pIndexBuffer->Unlock();
    }



    //マテリアル設定
    //マテリアルはプライマリメッシュのマテリアル情報を、
    //プライマリ及び全モーフターゲットのマテリアルとする。
    //よってpapMeshesFront[0]だけ使う、残りは使わない。
    //TODO:将来的にはモーフターゲット別にマテリアル設定できれば表現が増す。いつかしようか、多分だいぶ先。
    setMaterial(papMeshesFront[0]);


    if (!_papTextureConnection) {
        _papTextureConnection = NEW GgafDxTextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    GGAF_DELETEARR(paIOX);
    GGAF_DELETEARR(paXfileName);

    //モデルに保持させる
    _papModel3D              = papModel3D;
    _papMeshesFront          = papMeshesFront;
    _paIndexBuffer_data         = paIdxBuffer_data;
    _paVtxBuffer_data_primary = paVtxBuffer_data_primary;
    _papaVtxBuffer_data_morph = papaVtxBuffer_data_morph;
    _paIndexParam            = paIndexParam;

    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMorphMeshModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMorphMeshModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");

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
            GGAF_RELEASE(_pVertexBuffer_primary);
            GGAF_DELETEARR(_paVtxBuffer_data_primary);
        } else {
            GGAF_RELEASE(_paIDirect3DVertexBuffer9_morph[pattern-1]);
            GGAF_DELETEARR(_papaVtxBuffer_data_morph[pattern-1]);
        }
        if (_papModel3D) {
            Frm::Model3D* p = _papModel3D[pattern];
            GGAF_DELETE(p);
        }
    }

    GGAF_DELETEARR(_paIDirect3DVertexBuffer9_morph);
    GGAF_DELETEARR(_papaVtxBuffer_data_morph);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);

    GGAF_DELETEARR(_papModel3D);
    //_papMeshesFront[0],_papMeshesFront[1] は _papModel3D をDELETEしているのでする必要は無い
    GGAF_DELETEARR(_papMeshesFront);
    _papMeshesFront = nullptr;
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paIndexParam);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");

}
GgafDxMorphMeshModel::~GgafDxMorphMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

