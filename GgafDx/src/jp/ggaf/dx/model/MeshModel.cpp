#include "jp/ggaf/dx/model/MeshModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MeshActor.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

//DWORD MeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
DWORD MeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
                        D3DFVF_TEXCOORDSIZE2(0) | // real texture coord
                        D3DFVF_TEXCOORDSIZE3(1) | // tangent
                        D3DFVF_TEXCOORDSIZE3(2)   // binormal
                                    );
MeshModel::MeshModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_MeshModel;
    _paVertexBuffer = nullptr;
    _paIndexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _paIndex16Buffer_data = nullptr;
    _paIndex32Buffer_data = nullptr;
    _paIndexParam = nullptr;
    _material_list_grp_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _nVertices = 0;
    _nFaces = 0;
    _max_draw_set_num = 1;
    _is_65535 = false;
}

HRESULT MeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    //対象アクター
    //MeshActor* pTargetActor = (MeshActor*)prm_pActor_target;
    const FigureActor* const pTargetActor = prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    MeshEffect* const pMeshEffect = (MeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //頂点バッファとインデックスバッファを設定
        pDevice->SetStreamSource(0, _paVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(MeshModel::FVF);
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_fog_starts_far_rate, _fog_starts_far_rate);
        checkDxException(hr, D3D_OK, "SetFloat(_h_fog_starts_far_rate) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        const INDEXPARAM& idxparam = _paIndexParam[i];
        material_no = idxparam.MaterialNo;
        if (ModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //マテリアル0番は、特別に規定のテクスチャを設定する仕様
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("MeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            //本モデル描画初回
            if (pEffect_active) {
                _TRACE4_("前回 _pEffect_active != pMeshEffect ?? " <<pEffect_active<<"!="<<pMeshEffect<<"?? (" <<(pEffect_active->_effect_name)<<"!="<<(pMeshEffect->_effect_name)<<")");
                _TRACE4_("前回 ::_hash_technique_last_draw != prm_pActor_target->_hash_technique ?? " <<FigureActor::_hash_technique_last_draw<<"!="<<prm_pActor_target->_hash_technique<<"?? (prm_pActor_target=" <<prm_pActor_target<<" "<<(prm_pActor_target->getName())<<")");
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
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");
#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            //前回描画と同じモデル
            hr = pID3DXEffect->CommitChanges(); //マテリアルをコミットしなければいけない。
            checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
        if (_num_pass >= 2) { //２パス目以降が存在
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            for (UINT pass = 1; pass < _num_pass; pass++) {
                hr = pID3DXEffect->BeginPass(pass);
                checkDxException(hr, D3D_OK, pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
#ifdef MY_DEBUG
                GgafCore::Caretaker::_num_draw++;
#endif
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
        }
    }
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}
void MeshModel::dispFrame(Frm::Bone* pBone,int dep) {
    std::string indent = "";
    for (int i = 0; i < dep; i++) {
        indent += "    ";
    }
    _TRACE_("dispFrame():"<<indent<<"_MeshName("<<dep<<")="<<(pBone->_MeshName)<<"");
    _TRACE_("dispFrame():"<<indent<<"_Name("<<dep<<")="<<(pBone->_Name)<<"");
    for (std::list<Frm::Bone*>::iterator iteBone = pBone->_Bones.begin(); iteBone != pBone->_Bones.end(); iteBone++) {
        dispFrame((*iteBone),dep+1);
    }
}

void MeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");

    if (_paVtxBuffer_data == nullptr) {
        //【MeshModel再構築（＝初期化）処理概要】
        //１）頂点バッファ、頂点インデックスバッファ を new
        //２）Xファイルから、独自に次の情報を読み込み、頂点バッファ、頂点インデックスバッファ に流し込む。
        //３）２）を行なう過程で、同時に MeshModel に次のメンバを作成。
        //      ・頂点バッファの写し
        //      ・頂点インデックスバッファの写し
        //      ・マテリアル配列(要素数＝マテリアル数)
        //      ・テクスチャ配列(要素数＝マテリアル数)
        //      ・DrawIndexedPrimitive用引数配列(要素数＝マテリアルリストが変化した数)
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        loadMetaModelInfo(&xdata);
        if (_draw_set_num != 1) {
            _TRACE_("MeshModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 1 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
            _draw_set_num = 1;
        }
        std::string xfilepath = Model::getMeshXFilePath(xdata.XFileNames[0]);
        HRESULT hr;
        //流し込む頂点バッファデータ作成
        ToolBox::IO_Model_X iox;
        Frm::Model3D* pModel3D = NEW Frm::Model3D();
        bool r = iox.Load(xfilepath, pModel3D);
        if (r == false) {
            throwCriticalException("Xファイルの読込み失敗。対象="<<xfilepath);
        }
        //DEBUG
//        {
//            _TRACE_("-------------------------");
//            std::list<Frm::Bone*> lstBone = pModel3D->_toplevel_Skelettons;
//            for (std::list<Frm::Bone*>::iterator iteBone = lstBone.begin(); iteBone != lstBone.end(); iteBone++) {
//                bone((*iteBone));
//            }
//        }
        //メッシュを結合する前に、情報を確保しておく
        int nMesh = (int)pModel3D->_Meshes.size();
        uint32_t* paNumVertices = NEW uint32_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = pModel3D->_Meshes.begin();
                iteMeshes != pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        pModel3D->ConcatenateMeshes(); //メッシュを繋げる
        Frm::Mesh* pMeshesFront = pModel3D->_Meshes.front();
        _nVertices = pMeshesFront->_nVertices; //メッシュ連結後の総頂点数
        _nFaces = pMeshesFront->_nFaces;       //メッシュ連結後の総面数
//        nFaceNormals = pMeshesFront->_nFaceNormals; //メッシュ連結後の総法線数
        _paVtxBuffer_data = NEW MeshModel::VERTEX[_nVertices];
        _size_vertices = sizeof(MeshModel::VERTEX) * _nVertices;
        _size_vertex_unit = sizeof(MeshModel::VERTEX);
        UINT nTextureCoords = pMeshesFront->_nTextureCoords;
        if (_nVertices < nTextureCoords) {
            _TRACE3_("nTextureCoords="<<nTextureCoords<<"/_nVertices="<<_nVertices);
            _TRACE3_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<< xfilepath);
        }
        if (_nFaces * 3 > 65535) {
            _TRACE_("【警告】頂点インデックスが 65535 を超えたかもしれません。しらんけど。\n対象Model："<<getName()<<" インデックス:3*"<<_nFaces<<"(faces) _nVertices:"<<_nVertices);
            _is_65535 = true;
        }
        //頂点バッファ作成開始！
        //法線以外設定
        for (UINT i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data[i].x = pMeshesFront->_Vertices[i].data[0];
            _paVtxBuffer_data[i].y = pMeshesFront->_Vertices[i].data[1];
            _paVtxBuffer_data[i].z = pMeshesFront->_Vertices[i].data[2];
            _paVtxBuffer_data[i].nx = 0.0f;
            _paVtxBuffer_data[i].ny = 0.0f;
            _paVtxBuffer_data[i].nz = 0.0f;
            _paVtxBuffer_data[i].color = D3DCOLOR_ARGB(255,255,255,255); //頂点カラーは今の所使っていない
            if (i < nTextureCoords) {
                _paVtxBuffer_data[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //出来る限りUV座標設定
                _paVtxBuffer_data[i].tv = pMeshesFront->_TextureCoords[i].data[1];
            } else {
                _paVtxBuffer_data[i].tu = 0.0f;
                _paVtxBuffer_data[i].tv = 0.0f;
            }
            _paVtxBuffer_data[i].tan_x = 0.0f;
            _paVtxBuffer_data[i].tan_y = 0.0f;
            _paVtxBuffer_data[i].tan_z = 0.0f;
            _paVtxBuffer_data[i].bin_x = 0.0f;
            _paVtxBuffer_data[i].bin_y = 0.0f;
            _paVtxBuffer_data[i].bin_z = 0.0f;
        }

        //頂点バッファ作成
        prepareVtx3D((void*)_paVtxBuffer_data, _size_vertex_unit,
                    pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //距離
        FLOAT model_bounding_sphere_radius;
        for (UINT i = 0; i < _nVertices; i++) {
            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data[i].x * _paVtxBuffer_data[i].x +
                                                        _paVtxBuffer_data[i].y * _paVtxBuffer_data[i].y +
                                                        _paVtxBuffer_data[i].z * _paVtxBuffer_data[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        //インデックスバッファ登録
        if (_is_65535) {
            _paIndex32Buffer_data = NEW uint32_t[_nFaces*3];
            for (UINT i = 0; i < _nFaces; i++) {
                _paIndex32Buffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
                _paIndex32Buffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
                _paIndex32Buffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
            }

        } else {
            _paIndex16Buffer_data = NEW uint16_t[_nFaces*3];
            for (UINT i = 0; i < _nFaces; i++) {
                _paIndex16Buffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
                _paIndex16Buffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
                _paIndex16Buffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
            }
        }

        //描画時（DrawIndexedPrimitive）のパラメータリスト作成
        MeshModel::INDEXPARAM* paParam_tmp = NEW MeshModel::INDEXPARAM[_nFaces]; //最高にマテリアルがバラバラだった場合nFaces必要

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < _nFaces; faceNoCnt++) {
            materialno = pMeshesFront->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //_TRACE3_("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam_tmp[paramno].MaterialNo = materialno;
                paParam_tmp[paramno].BaseVertexIndex = 0;
                paParam_tmp[paramno].MinIndex = UINT_MAX; //次回ブレイク時に設定、必ずブレイクしたいため変な値にしとく
                paParam_tmp[paramno].NumVertices = UINT_MAX; //次回ブレイク時に設定
                paParam_tmp[paramno].StartIndex = faceNoCnt*3;
                paParam_tmp[paramno].PrimitiveCount = UINT_MAX; //次回ブレイク時に設定

                if (faceNoCnt > 0) {
                    paParam_tmp[paramno-1].MinIndex = min_num_vertices;
                    paParam_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //リセット
                    max_num_vertices = 0;
                    min_num_vertices = UINT_MAX;
                }
                paramno++;
            }
            if (_is_65535) {
                if (max_num_vertices <  _paIndex32Buffer_data[faceNoCnt*3 + 0]) {
                    max_num_vertices = _paIndex32Buffer_data[faceNoCnt*3 + 0];
                }
                if (max_num_vertices <  _paIndex32Buffer_data[faceNoCnt*3 + 1]) {
                    max_num_vertices = _paIndex32Buffer_data[faceNoCnt*3 + 1];
                }
                if (max_num_vertices <  _paIndex32Buffer_data[faceNoCnt*3 + 2]) {
                    max_num_vertices = _paIndex32Buffer_data[faceNoCnt*3 + 2];
                }
                if (min_num_vertices >  _paIndex32Buffer_data[faceNoCnt*3 + 0]) {
                    min_num_vertices = _paIndex32Buffer_data[faceNoCnt*3 + 0];
                }
                if (min_num_vertices >  _paIndex32Buffer_data[faceNoCnt*3 + 1]) {
                    min_num_vertices = _paIndex32Buffer_data[faceNoCnt*3 + 1];
                }
                if (min_num_vertices >  _paIndex32Buffer_data[faceNoCnt*3 + 2]) {
                    min_num_vertices = _paIndex32Buffer_data[faceNoCnt*3 + 2];
                }

            } else {
                if (max_num_vertices <  _paIndex16Buffer_data[faceNoCnt*3 + 0]) {
                    max_num_vertices = _paIndex16Buffer_data[faceNoCnt*3 + 0];
                }
                if (max_num_vertices <  _paIndex16Buffer_data[faceNoCnt*3 + 1]) {
                    max_num_vertices = _paIndex16Buffer_data[faceNoCnt*3 + 1];
                }
                if (max_num_vertices <  _paIndex16Buffer_data[faceNoCnt*3 + 2]) {
                    max_num_vertices = _paIndex16Buffer_data[faceNoCnt*3 + 2];
                }
                if (min_num_vertices >  _paIndex16Buffer_data[faceNoCnt*3 + 0]) {
                    min_num_vertices = _paIndex16Buffer_data[faceNoCnt*3 + 0];
                }
                if (min_num_vertices >  _paIndex16Buffer_data[faceNoCnt*3 + 1]) {
                    min_num_vertices = _paIndex16Buffer_data[faceNoCnt*3 + 1];
                }
                if (min_num_vertices >  _paIndex16Buffer_data[faceNoCnt*3 + 2]) {
                    min_num_vertices = _paIndex16Buffer_data[faceNoCnt*3 + 2];
                }
            }
            prev_materialno = materialno;
        }
        if (_nFaces > 0) {
            paParam_tmp[paramno-1].MinIndex = min_num_vertices;
            paParam_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        _paIndexParam = NEW MeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            _paIndexParam[i].MaterialNo      = paParam_tmp[i].MaterialNo;
            _paIndexParam[i].BaseVertexIndex = paParam_tmp[i].BaseVertexIndex;
            _paIndexParam[i].MinIndex        = paParam_tmp[i].MinIndex;
            _paIndexParam[i].NumVertices     = paParam_tmp[i].NumVertices;
            _paIndexParam[i].StartIndex      = paParam_tmp[i].StartIndex;
            _paIndexParam[i].PrimitiveCount  = paParam_tmp[i].PrimitiveCount;
        }
        _material_list_grp_num = paramno;

        delete[] paParam_tmp;

        //マテリアル設定
        if (_paMaterial_default == nullptr) {
            setMaterial(pMeshesFront);
        }


        GGAF_DELETE(pModel3D);
        //pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
        pMeshesFront = nullptr;
    }

    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //頂点バッファ作成
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                MeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));

        //バッファへ作成済み頂点データを流し込む
        void *paVertexBuffer;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&paVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
        memcpy(paVertexBuffer, _paVtxBuffer_data, _size_vertices); //paVertexBuffer ← paVertex
        _paVertexBuffer->Unlock();
    }

    //インデックスバッファデータ作成
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        if (_is_65535) {
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                        sizeof(uint32_t) * _nFaces * 3,
                                        D3DUSAGE_WRITEONLY,
                                        D3DFMT_INDEX32,
                                        D3DPOOL_DEFAULT,
                                        &(_paIndexBuffer),
                                        nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer , _paIndex32Buffer_data , sizeof(uint32_t) * _nFaces * 3);
            _paIndexBuffer->Unlock();
        } else {

            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                        sizeof(uint16_t) * _nFaces * 3,
                                        D3DUSAGE_WRITEONLY,
                                        D3DFMT_INDEX16,
                                        D3DPOOL_DEFAULT,
                                        &(_paIndexBuffer),
                                        nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer , _paIndex16Buffer_data , sizeof(uint16_t) * _nFaces * 3);
            _paIndexBuffer->Unlock();
        }
    }

    //テクスチャ作成
    if (!_papTextureConnection) {
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] = connectToTextureManager(_pa_texture_filenames[n].c_str());
        }
    }
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //テクスチャを解放
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列
    GGAF_RELEASE(_paVertexBuffer);
    GGAF_RELEASE(_paIndexBuffer);
    _TRACE3_("_model_id=" << _model_id << " end");
}

MeshModel::~MeshModel() {
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex16Buffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex32Buffer_data);
    GGAF_DELETEARR(_paIndexParam);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}





//        //デバッグ
//        _TRACE_("#頂点バッファ _nVertices="<<_nVertices);
//        float x,y,z,nx,ny,nz,tu,tv,tan_x,tan_y,tan_z,bin_x,bin_y,bin_z;
//        for (UINT i = 0; i < _nVertices; i++) {
//            x = _paVtxBuffer_data[i].x;
//            y = _paVtxBuffer_data[i].y;
//            z = _paVtxBuffer_data[i].z;
//            nx = _paVtxBuffer_data[i].nx;
//            ny = _paVtxBuffer_data[i].ny;
//            nz = _paVtxBuffer_data[i].nz;
//            tu = _paVtxBuffer_data[i].tu;
//            tv = _paVtxBuffer_data[i].tv;
//            tan_x = _paVtxBuffer_data[i].tan_x;
//            tan_y = _paVtxBuffer_data[i].tan_y;
//            tan_z = _paVtxBuffer_data[i].tan_z;
//            bin_x = _paVtxBuffer_data[i].bin_x;
//            bin_y = _paVtxBuffer_data[i].bin_y;
//            bin_z = _paVtxBuffer_data[i].bin_z;
//            //デバッグ
//            //_TRACE_("頂点["<<i<<"] pos("<<x<<","<<y<<","<<z<<")\tuv("<<tu<<","<<tv<<")\tn("<<nx<<","<<ny<<","<<nz<<")\tt("<<tan_x<<","<<tan_y<<","<<tan_z<<")\tb("<<bin_x<<","<<bin_y<<","<<bin_z<<")");
//        }


//    {
//        //デバッグ
//        _TRACE_("#頂点バッファ _nVertices="<<_nVertices);
//        float x,y,z,nx,ny,nz,tu,tv;
//        for (UINT i = 0; i < _nVertices; i++) {
//            x = _paVtxBuffer_data[i].x;
//            y = _paVtxBuffer_data[i].y;
//            z = _paVtxBuffer_data[i].z;
//            nx = _paVtxBuffer_data[i].nx;
//            ny = _paVtxBuffer_data[i].ny;
//            nz = _paVtxBuffer_data[i].nz;
//            tu = _paVtxBuffer_data[i].tu;
//            tv = _paVtxBuffer_data[i].tv;
//
//            _TRACE_("頂点["<<i<<"] "<<x<<";"<<y<<";"<<z<<";,\t"<<nx<<";"<<ny<<";"<<nz<<";,\t"<<tu<<";"<<tv<<";,");
//        }
//
//
//        _TRACE_("#インデックスバッファ _nFaces="<<_nFaces);
//        WORD vtx1,vtx2,vtx3;
//        for (int face = 0; face < _nFaces; face++) {
//            vtx1 = _paIndex16Buffer_data[face*3 + 0];
//            vtx2 = _paIndex16Buffer_data[face*3 + 1];
//            vtx3 = _paIndex16Buffer_data[face*3 + 2];
//            _TRACE_("面["<<face<<"] 3;"<<vtx1<<","<<vtx2<<","<<vtx3<<";,");
//        }
//
//        _TRACE_("マテリアル  num_materials="<<num_materials);
//        float a,r,g,b;
//        for (int i = 0; i < num_materials; i++) {
//            a = paMaterial[i].Diffuse.a;
//            r = paMaterial[i].Diffuse.r;
//            g = paMaterial[i].Diffuse.g;
//            b = paMaterial[i].Diffuse.b;
//            _TRACE_("nMaterial["<<i<<"] Diffuse(rgba)=("<<r<<","<<g<<","<<b<<","<<a<<")");
//            a = paMaterial[i].Ambient.a;
//            r = paMaterial[i].Ambient.r;
//            g = paMaterial[i].Ambient.g;
//            b = paMaterial[i].Ambient.b;
//            _TRACE_("nMaterial["<<i<<"] Ambient(rgba)=("<<r<<","<<g<<","<<b<<","<<a<<")");
//        }
//
//        _TRACE_("#マテリアルリスト _material_list_grp_num="<< _material_list_grp_num);
//        for (UINT i = 0; i < _material_list_grp_num; i++) {
//            int material_no = _paIndexParam[i].MaterialNo;
//            _TRACE_("MaterialGrp["<<i<<"] "<<material_no<<",");
//        }
//
//        _TRACE_("#IndexParam  _material_list_grp_num="<< _material_list_grp_num);
//        UINT MaterialNo;
//        INT BaseVertexIndex;
//        UINT MinIndex;
//        UINT NumVertices;
//        UINT StartIndex;
//        UINT PrimitiveCount;
//        for (UINT i = 0; i < _material_list_grp_num; i++) {
//            MaterialNo = _paIndexParam[i].MaterialNo;
//            BaseVertexIndex = _paIndexParam[i].BaseVertexIndex;
//            MinIndex = _paIndexParam[i].MinIndex;
//            NumVertices = _paIndexParam[i].NumVertices;
//            StartIndex = _paIndexParam[i].StartIndex;
//            PrimitiveCount = _paIndexParam[i].PrimitiveCount;
//            _TRACE_("MaterialGrp["<<i<<"] MaterialNo="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] BaseVertexIndex="<<BaseVertexIndex);
//            _TRACE_("MaterialGrp["<<i<<"] MinIndex="<<MinIndex);
//            _TRACE_("MaterialGrp["<<i<<"] NumVertices="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] StartIndex="<<StartIndex);
//            _TRACE_("MaterialGrp["<<i<<"] PrimitiveCount="<<PrimitiveCount);
//        }
//    }


