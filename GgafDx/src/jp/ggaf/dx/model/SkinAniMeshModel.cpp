#include "jp/ggaf/dx/model/SkinAniMeshModel.h"

#include <algorithm>
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/SkinAniMeshActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/SkinAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/util/SkinAniMeshContainer.h"
#include "jp/ggaf/dx/util/SkinAniMeshFrame.h"

using namespace GgafDx;

SkinAniMeshModel::SkinAniMeshModel(const char* prm_model_name) : Model(prm_model_name) {
    _pAllocHierarchy = nullptr;
    _pFrameRoot = nullptr;
    _pAniControllerBase = nullptr;
    _num_materials = 0L;
//    _anim_ticks_per_second = 4800; //restoreSkinAniMeshModel で上書きされる場合がある。
    _paVtxBuffer_data = nullptr;
    _paIndexBuffer_data = nullptr;
    _pVertexDeclaration = nullptr;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _index_param_num = 0;
    _paIndexParam = nullptr;
    _paIndexBuffer_bone_combi_index = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = sizeof(SkinAniMeshModel::VERTEX);
    _nFaces = 0;
    _nVertices = 0;
    _tmp_frame_index = 0;
    _num_animation_set = 0;
    _papaBool_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _obj_model |= Obj_GgafDx_SkinAniMeshModel;
}

HRESULT SkinAniMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("SkinAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    HRESULT hr;
    //対象アクター
    SkinAniMeshActor* pTargetActor = (SkinAniMeshActor*)prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    SkinAniMeshEffect* pSkinAniMeshEffect = (SkinAniMeshEffect*)(prm_pActor_target->getEffect());
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pSkinAniMeshEffect->_pID3DXEffect;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //頂点バッファとインデックスバッファを設定
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //頂点フォーマット
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetIndices(_pIndexBuffer);
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
    }

    //マテリアル・テクスチャの一発目をセット、
    LPDIRECT3DBASETEXTURE9 pTex = _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9;
    hr = pDevice->SetTexture(0, pTex);
    checkDxException(hr, D3D_OK, "SetTexture に失敗しました。");
    hr = pID3DXEffect->SetValue(pSkinAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
    Puppeteer* pActorPuppeteer = pTargetActor->_pPuppeteer;
    pActorPuppeteer->updateAnimationTrack(); //アニメーション反映
    //モデルのワールド変換行列更新
    pTargetActor->_stackWorldMat.SetWorldMatrix(&(pTargetActor->_matWorld));
    ID3DXAnimationSet* pAs0 = pActorPuppeteer->_paAs[0];
    ID3DXAnimationSet* pAs1 = pActorPuppeteer->_paAs[1];
    int as0_index = (int)_mapAnimationSet_AniSetindex[pAs0];
    int as1_index = pAs1 ? _mapAnimationSet_AniSetindex[pAs1] : -1;
    pTargetActor->_stackWorldMat.UpdateFrame(_pFrameRoot, as0_index, as1_index, _papaBool_AnimationSetIndex_BoneFrameIndex_is_act);

    std::vector<SkinAniMeshFrame*>::iterator it_1 = _vecBoneIdFrame.begin();

/////////////////////////////////////////////
///




//    for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
//        DWORD bone_id = _vec_infl_bone_id_order[i];
//        hr = pID3DXEffect->SetMatrix(pSkinAniMeshEffect->_ah_matBone[i], &(_vecBoneIdFrame[bone_id]->_combined_matrix));
//    }


    for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
        hr = pID3DXEffect->SetMatrix(pSkinAniMeshEffect->_ah_matBone[i], _ap_draw_combined_matrix[i] );
    }

    for (int i = 0; i < _index_param_num; i++) {
        const INDEXPARAM& idxparam = _paIndexParam[i];
//        for (int j = 0; j < SkinAniMeshModel_MAX_BONE_WORLD_MATRIX; j++) {
//            if (it_1 != _vecBoneIdFrame.end()) {
//                hr = pID3DXEffect->SetMatrix(pSkinAniMeshEffect->_ah_matBone[j], &((*it_1)->_combined_matrix));
//                ++it_1;
//            } else {
//                break;
//            }
//        }

        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() End() に失敗しました。");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSkinAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSkinAniMeshEffect->_effect_name<<"("<<pSkinAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pSkinAniMeshEffect->_begin) {
                throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pSkinAniMeshEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() CommitChanges() に失敗しました。");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
    }

#ifdef MY_DEBUG
    GgafCore::God::_num_drawing++;
#endif
    //前回描画モデル名反映
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pSkinAniMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void SkinAniMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    if (_paVtxBuffer_data == nullptr) {
        HRESULT hr;
        std::string xfile_name = ModelManager::getMeshFileName(_model_name);
        TextureManager* pTextureManager = pGOD->_pModelManager->_pModelTextureManager;
        //AnimTicksPerSecondを独自に取り出す。デフォルトは4800
//        _anim_ticks_per_second = SkinAniMeshModel::getAnimTicksPerSecond(xfile_name);
//DEBUG
//_TRACE_("SkinAniMeshModel::restore() _anim_ticks_per_second="<<_anim_ticks_per_second);
//        if (_anim_ticks_per_second < 0) {
//            _anim_ticks_per_second = 4800;
//        }
        //Xファイルのファイルロード
        _pAllocHierarchy = NEW SkinAniMeshAllocHierarchy(); // CAllocHierarchyBaseの派生クラス
        hr = D3DXLoadMeshHierarchyFromX(
                xfile_name.c_str(),
                D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
                God::_pID3DDevice9,
                _pAllocHierarchy,
                nullptr,
                (D3DXFRAME**)(&_pFrameRoot),
                &_pAniControllerBase
             );
        _TRACE_("_pAllocHierarchy="<<_pAllocHierarchy<<" _pFrameRoot="<<_pFrameRoot<<" _pAniControllerBase="<<_pAniControllerBase<<" xfile_name.c_str()="<<xfile_name.c_str());
        checkDxException(hr, D3D_OK, xfile_name<<" 読み込みに失敗しました。対象="<<xfile_name);
        if (_pFrameRoot == nullptr) {
            throwCriticalException(xfile_name<<" のフレーム情報が取得できません！");
        }
        //デフォルトで設定されているトラックのアニメーションで姿勢を一回つくる（コピー用）
        //グローバル時間を0にする
        hr = _pAniControllerBase->ResetTime();
        checkDxException(hr, D3D_OK, "失敗しました。");
        //0秒進める（ことによって反映させる）。
        hr = _pAniControllerBase->AdvanceTime(0, nullptr);
        checkDxException(hr, D3D_OK, "失敗しました。");

        _vecDrawBoneFrame.clear();
        _vecAllBoneFrame.clear();
        _tmp_frame_index = 0;

        _TRACE_("setFrameInfo!!!!!!!!!!!!!!!!!1");
        setFrameInfo(_pFrameRoot); //フレームを廻り情報をメンバにセット
        //////
        _mapAnimationSet_AniSetindex.clear();
        _mapAnimationSetIndex_AnimationTargetBoneFrameNames.clear();
        _num_animation_set = _pAniControllerBase->GetMaxNumAnimationSets();
        for (UINT ani_set_index = 0; ani_set_index < _num_animation_set; ani_set_index++) {
            ID3DXAnimationSet* pAnimationSet = nullptr;
            hr = _pAniControllerBase->GetAnimationSet(ani_set_index, &(pAnimationSet)); //アニメーションセット保持
            checkDxException(hr, D3D_OK, "失敗しました");
            _mapAnimationSet_AniSetindex[pAnimationSet] = ani_set_index;
            int num_animation = pAnimationSet->GetNumAnimations();
            for (UINT ani_index = 0; ani_index < num_animation; ++ani_index) {
                LPCSTR target_bone_frame_name = nullptr;
                hr = pAnimationSet->GetAnimationNameByIndex(ani_index, &target_bone_frame_name);
                checkDxException(hr, D3D_OK, "失敗しました");
                _mapAnimationSetIndex_AnimationTargetBoneFrameNames[ani_set_index].push_back(target_bone_frame_name);

            }
        }

        _papaBool_AnimationSetIndex_BoneFrameIndex_is_act = NEW bool*[_num_animation_set];
        for (UINT ani_set_index = 0; ani_set_index < _num_animation_set; ani_set_index++) {
            _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index] = NEW bool[_tmp_frame_index+1];
            std::vector<LPCSTR>* pAnimationTargetBoneFrameNameList = &(_mapAnimationSetIndex_AnimationTargetBoneFrameNames[ani_set_index]);
            for (UINT frame_index = 0; frame_index < _vecAllBoneFrame.size(); frame_index++) {
                _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index][frame_index] = false;
                LPSTR frame_name = _vecAllBoneFrame[frame_index]->Name;
                if (frame_name) {
                    for (int n = 0; n < pAnimationTargetBoneFrameNameList->size(); n++) {
                        LPCSTR animation_target_bone_frame_name = (*pAnimationTargetBoneFrameNameList)[n];
                        if (strcmp(animation_target_bone_frame_name, frame_name) == 0) {
                            _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index][frame_index] = true;
                            break;
                        }
                    }
                }
            }
        }

        //境界球
        D3DXVECTOR3 vecCenter;
        FLOAT bounding_sphere_radius;
        D3DXFrameCalculateBoundingSphere((D3DXFRAME*)_pFrameRoot, &vecCenter, &bounding_sphere_radius);
        _bounding_sphere_radius = UTIL::getDistance(0.0f, 0.0f, 0.0f, vecCenter.x, vecCenter.y, vecCenter.z) + bounding_sphere_radius;

        _TRACE_("境界球半径="<<_bounding_sphere_radius);


        int draw_frame_num = _vecDrawBoneFrame.size();

        int materials_total_num = 0;
        int vertices_total_num = 0;
        int faces_total_num = 0;

        //フレームリストを廻って、マテリアル総数取得
        for (int i = 0; i < draw_frame_num; i++) {
            SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[i]->pMeshContainer);
            if (pMeshContainer == nullptr) {
                continue;
            }

            ID3DXMesh* pMesh = _vecDrawBoneFrame[i]->pMeshContainer->MeshData.pMesh;
            vertices_total_num += (int)(pMesh->GetNumVertices());  // 頂点数
            faces_total_num += (int)(pMesh->GetNumFaces());        // ポリゴン数
            materials_total_num += (int)(_vecDrawBoneFrame[i]->pMeshContainer->NumMaterials);
        }

        //配列数がやっと解ったので作成
        _num_materials = materials_total_num;
        _nVertices = vertices_total_num;
        _nFaces = faces_total_num;
        _paVtxBuffer_data =  NEW SkinAniMeshModel::VERTEX[_nVertices];
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        _paIndexBuffer_bone_combi_index = NEW int[_nFaces*3];
        if (!_paMaterial_default) {
            if (materials_total_num > 0) {
                _paMaterial_default = NEW D3DMATERIAL9[_num_materials];
                _pa_texture_filenames = NEW std::string[_num_materials];
                // 下で設定
            } else {
                //マテリアル定義が１つも無いので、描画のために無理やり１つマテリアルを作成。
                _num_materials = 1;
                _paMaterial_default  = NEW D3DMATERIAL9[1];
                _pa_texture_filenames = NEW std::string[1];
                setDefaultMaterial(&(_paMaterial_default[0]));
                _pa_texture_filenames[0] = CONFIG::WHITE_TEXTURE;
            }
        } //  if (!_paMaterial_default)


        //モデル保持用マテリアル、テクスチャ作成のため、もう一度回す
        int m_cnt = 0;   //マテリアルと押しカウンター
        int v_cnt = 0;   //頂点バッファ通しカウンター
        int i_cnt = 0;   //インデックスバッファ通しカウンター
        char* texture_filename;
        D3DVERTEXELEMENT9 e[MAX_FVF_DECL_SIZE];
        //フレームでループ！
        for (int i = 0; i < draw_frame_num; i++) {
            SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[i]->pMeshContainer);
            if (pMeshContainer == nullptr) {
                continue;
            }
            int nMaterials = (int)(pMeshContainer->NumMaterials);
            for (int j = 0; j < nMaterials; j++) {
                if (pMeshContainer->pMaterials) {
                    _paMaterial_default[m_cnt] = pMeshContainer->pMaterials[j].MatD3D; //マテリアル情報コピー
                    texture_filename = pMeshContainer->pMaterials[j].pTextureFilename;
                    if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                        _pa_texture_filenames[m_cnt] = std::string(texture_filename);
                    } else {
                        //テクスチャ無し時は真っ白なテクスチャに置き換え
                        _pa_texture_filenames[m_cnt] = CONFIG::WHITE_TEXTURE;
                    }
                } else {
                    setDefaultMaterial(&(_paMaterial_default[m_cnt]));
                    _pa_texture_filenames[m_cnt] = CONFIG::WHITE_TEXTURE;
                }
                m_cnt ++;
            }

            ID3DXMesh* pMesh = pMeshContainer->MeshData.pMesh;

            pMesh->GetDeclaration( e );
            int offset_position  = getOffsetFromElem( e, D3DDECLUSAGE_POSITION );
            int offset_normal  = getOffsetFromElem( e, D3DDECLUSAGE_NORMAL );
    //        int offset_color  = getOffsetFromElem( e, D3DDECLUSAGE_COLOR );
            int offset_texcoord  = getOffsetFromElem( e, D3DDECLUSAGE_TEXCOORD );

            IDirect3DVertexBuffer9* pVb;
            pMesh->GetVertexBuffer(&pVb);
            DWORD size_vertex_unit = pMesh->GetNumBytesPerVertex(); // 1つの頂点のサイズ
            void* pVertexBuffer;
            int nVertices = (int)(pMesh->GetNumVertices()); //メッシュコンテナの頂点数
            pVb->Lock(0, nVertices*size_vertex_unit, (void**)&pVertexBuffer, 0);
            for (int j = 0; j < nVertices; j++) {
                char* p = nullptr;
                SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[v_cnt]); //書き込む1頂点の開始アドレス
                char* pVertex_base = (char*)pVertexBuffer + (size_vertex_unit*j);  //読み込む1頂点の開始アドレス
                //    float x, y, z;    // 頂点座標
                p = pVertex_base + offset_position;
                memcpy(&(pVtx->x), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                memcpy(&(pVtx->y), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                memcpy(&(pVtx->z), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                //Normal  float nx, ny, nz; // 法線
                if (offset_normal > 0) {
                    p = pVertex_base + offset_normal;
                    memcpy(&(pVtx->nx), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx->ny), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx->nz), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                } else {
                    pVtx->nx = 0.0f;
                    pVtx->ny = 0.0f;
                    pVtx->nz = 0.0f;
                }
                // float bone_combi_index
                pVtx->bone_combi_index = -1; // 仮設定、下で再設定する

                //DWORD color ; //頂点カラー
                pVtx->color = D3DCOLOR_ARGB(255,255,255,255); //頂点カラー

                //float tu, tv;     // テクスチャ座標
                if (offset_texcoord > 0) {
                    p = pVertex_base + offset_texcoord;
                    memcpy(&(pVtx->tu), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx->tv), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                } else {
                    pVtx->tu = 0.0f;
                    pVtx->tv = 0.0f;
                }
//               _TRACE_("["<<i<<"]["<<j<<"]:pVtx->index="<<pVtx->index<<"  Vertex=("<<(pVtx->x)<<","<<(pVtx->y)<<","<<(pVtx->z)<<")  Normal=("<<(pVtx->nx)<<","<<(pVtx->ny)<<","<<(pVtx->nz)<<")  texcoordl=("<<(pVtx->tu)<<","<<(pVtx->tv)<<")");

                for (int k = 0; k < 4; k++) {  // 仮で初期値設定、下で再設定する
                    pVtx->infl_weight[k] = 0.0f;
                    pVtx->infl_bone_id[k] = 0xFF;
                    pVtx->infl_bone_id_order[k] = 0xFF;
                }
                v_cnt ++;
            }
            pVb->Unlock();
            pVb->Release();



            //skin情報のためにもっかいループ
            int vertx_through_count = 0;
            int bc_through_idx = 0;
            for (int i = 0; i < draw_frame_num; i++) {

                SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[i]->pMeshContainer);
                if (pMeshContainer == nullptr) {
                    continue;
                }
                /////////////
                _TRACE_("draw_frsme["<<i<<"]: idx="<<_vecDrawBoneFrame[i]->_frame_index<<", name="<<_vecDrawBoneFrame[i]->Name<<"");
                _TRACE_("pMeshContainer->_dwMaxInfleNum = "<<pMeshContainer->_dwMaxInfleNum);
                _TRACE_("pMeshContainer->_dwBoneCombNum = "<<pMeshContainer->_dwBoneCombNum);
                LPD3DXSKININFO pSkinInfo = pMeshContainer->pSkinInfo;
                D3DXBONECOMBINATION* paBoneCombination =
                        (D3DXBONECOMBINATION*)(pMeshContainer->_pBoneCombinationTable->GetBufferPointer());
                for (DWORD bc_idx = 0; bc_idx < pMeshContainer->_dwBoneCombNum; ++bc_idx, ++bc_through_idx) { //bc_idxはメッシュサブセットID
                    D3DXBONECOMBINATION* pBoneCombination = &(paBoneCombination[bc_idx]);
                    _TRACE_("paBoneCombination["<<bc_idx<<"] = "<<
                            " AttribId="<<pBoneCombination->AttribId<<
                            " FaceStart="<<pBoneCombination->FaceStart<<
                            " FaceCount="<<pBoneCombination->FaceCount<<
                            " VertexStart="<<pBoneCombination->VertexStart<<
                            " VertexCount="<<pBoneCombination->VertexCount<<
                            ""
                    );
                    //頂点情報にボーンコンビネーションインデックスを書き込み
                    for (DWORD v = 0; v < pBoneCombination->VertexCount; v++, vertx_through_count++) {
                        SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[vertx_through_count]);
                        pVtx->bone_combi_index = (float)bc_through_idx;
                    }
                    DWORD infl_id;
                    for ( infl_id = 0; infl_id < pMeshContainer->_dwMaxInfleNum; ++infl_id) { //
                        DWORD bone_id = pBoneCombination->BoneId[infl_id]; //bone_idはなんなのか？
                        DWORD bone_influ_vertices_num = pSkinInfo->GetNumBoneInfluences(bone_id);

                        _TRACE_("paBoneCombination["<<bc_idx<<"].BoneId["<<infl_id<<"]="<<bone_id<<" bone_influ_vertices_num="<<bone_influ_vertices_num);

                        if (bone_influ_vertices_num > 0) {
                            // Get the bone influcences
                            DWORD* vertices = new DWORD[bone_influ_vertices_num];
                            float* skin_weight  = new float[bone_influ_vertices_num];
                            pSkinInfo->GetBoneInfluence(bone_id, vertices, skin_weight);
                            for (DWORD v = 0; v < bone_influ_vertices_num; v++) {
                                if (skin_weight[v] > 0.0) {
                                    SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[vertices[v]]);
                                    bool is_exist = false;
                                    for (int k = 0; k < 4; k++) {
                                        if (pVtx->infl_bone_id[k] == (byte)bone_id) {
                                            is_exist = true;
                                            break;
                                        }
                                    }
                                    if (is_exist == false) {
                                        for (int k = 0; k < 4; k++) {
                                            if (pVtx->infl_weight[k] < skin_weight[v]) { //weight大きい順に
                                            //if (pVtx->infl_weight[k] == 0.0 || (pVtx->infl_weight[k] > 0.0 && pVtx->infl_weight[k] > skin_weight[v])) { //weight小さい順
                                                for (int j = 3; j > k; j--) {
                                                    //スライド
                                                    pVtx->infl_bone_id[j] = pVtx->infl_bone_id[j-1];
                                                    pVtx->infl_weight[j] = pVtx->infl_weight[j-1];
                                                }
                                                pVtx->infl_bone_id[k] = (byte)bone_id;
                                                pVtx->infl_weight[k] =  skin_weight[v];

                                                 std::vector<DWORD>::iterator p = std::find(_vec_infl_bone_id_order.begin(), _vec_infl_bone_id_order.end(), bone_id);
                                                 if (p == _vec_infl_bone_id_order.end()) {
                                                     //存在しない＝初めての bone_id
                                                     _vec_infl_bone_id_order.push_back(bone_id);
                                                 }
                                                 break;
                                            }
                                        }


//                                        for (int k = 0; k < 4; k++) {
//                                            if (pVtx->infl_bone_idx[k] == 0xFF) {
//                                                 pVtx->infl_bone_idx[k] = (byte)bone_id;
//                                                 pVtx->infl_weight[k] =  skin_weight[v];
//
//                                                 std::vector<DWORD>::iterator p = std::find(_vec_infl_bone_id_order.begin(), _vec_infl_bone_id_order.end(), bone_id);
//                                                 if (p == _vec_infl_bone_id_order.end()) {
//                                                     //存在しない＝初めての bone_id
//                                                     _vec_infl_bone_id_order.push_back(bone_id);
//                                                 }
//                                                 break;
//                                            }
//                                        }
                                    }
                                }
                            }

                            _TRACE_N_("Vertices=");
                            for (int v = 0; v < bone_influ_vertices_num; v++) {
                                _TRACE_N_("\t"<<vertices[v]<<"");
                            }
                            _TRACE_N_("\n");
                            _TRACE_N_("Weights=");
                            for (int v = 0; v < bone_influ_vertices_num; v++) {
                                _TRACE_N_("\t"<<skin_weight[v]<<"");
                            }
                            _TRACE_N_("\n");
                        }
                    }
                }

                //ボーンIDとFrameの紐付けと_bone_offset_matrixの保持
                DWORD dwNumBone = pSkinInfo->GetNumBones();  // ボーンの数を取得
                // ボーンの数だけ対応フレームを検索
                for (DWORD bone_id = 0; bone_id < dwNumBone; bone_id++) {
                    SkinAniMeshFrame* pFrame = nullptr;   // 一致したフレームポインタ
                   // ボーン名を取得
                   LPCSTR skin_bone_name = pSkinInfo->GetBoneName(bone_id);
                   if (skin_bone_name) {
                       // 名前検索
                       for (int fram_idx = 0; i < _vecAllBoneFrame.size(); fram_idx++) {
                           LPSTR frame_bone_name = _vecAllBoneFrame[fram_idx]->Name;
                           if (frame_bone_name) {
                               if (strcmp(skin_bone_name, frame_bone_name) == 0) { //SkinInfoボーン名がFrameと一致一致
                                   pFrame = _vecAllBoneFrame[fram_idx];
                                   break;
                               }
                           }
                       }
                       if (pFrame) {
                           _vecBoneIdFrame.push_back(pFrame);
                           pFrame->_bone_id = bone_id;
                           pFrame->_bone_offset_matrix = *(pSkinInfo->GetBoneOffsetMatrix(bone_id));
                       } else {
                           _vecBoneIdFrame.push_back(nullptr);
                       }
                   }
                }


                //DEBUG
                for (DWORD frame_idx = 0; frame_idx < _vecAllBoneFrame.size(); frame_idx++) {
                    _TRACE_("_vecAllBoneFrame["<<frame_idx<<"] Name=\""<<_vecAllBoneFrame[frame_idx]->Name<<"\" "<<
                                                              "_bone_id="<<_vecAllBoneFrame[frame_idx]->_bone_id<<" "<<
                                                              "pMeshContainer="<<_vecAllBoneFrame[frame_idx]->pMeshContainer);
                }
                _TRACE_("////////////////////////////////////");
                for (DWORD bone_id = 0; bone_id < _vecBoneIdFrame.size(); bone_id++) {
                    if (_vecBoneIdFrame[bone_id]) {
                        _TRACE_("_vecBoneIdFrame["<<bone_id<<"] = "<<_vecBoneIdFrame[bone_id]->Name<<" "<<
                                                                  "_frame_index="<<_vecBoneIdFrame[bone_id]->_frame_index<<" ");
                    } else {
                        _TRACE_("_vecBoneIdFrame["<<bone_id<<"] = nullptr"" "<<
                                "_frame_index="<<_vecBoneIdFrame[bone_id]->_frame_index<<" ");
                    }
                }

            } //for (int i = 0; i < draw_frame_num; i++) {


            //ボーンIDをオーダーに書き換える
            _map_infl_bone_id_to_order[0xFF] = 0xFF;
            for (DWORD i = 0; i < _vec_infl_bone_id_order.size(); i++) {
                _map_infl_bone_id_to_order[_vec_infl_bone_id_order[i]]=i;
            }

            for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
                _TRACE_("_vec_infl_bone_id_order["<<i<<"]="<<_vec_infl_bone_id_order[i]);
            }

            //    std::map<DWORD, byte> _map_infl_bone_id_to_order;
            for (std::map<DWORD, DWORD>::iterator p = _map_infl_bone_id_to_order.begin();
                    p != _map_infl_bone_id_to_order.end(); p++) {
                    // イテレータは pair<const string, int> 型なので、
                    _TRACE_("_map_infl_bone_id_to_order["<<p->first<<"]="<< p->second);
            }


            //頂点バッファのボーンIDをオーダーに書き換える
            for (int i = 0; i < _nVertices; i++) {
                SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[i]);
                pVtx->infl_bone_id_order[0] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[0]]);
                pVtx->infl_bone_id_order[1] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[1]]);
                pVtx->infl_bone_id_order[2] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[2]]);
                pVtx->infl_bone_id_order[3] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[3]]);
            }


            for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
                DWORD bone_id = _vec_infl_bone_id_order[i];
                _ap_draw_combined_matrix[i] = &(_vecBoneIdFrame[bone_id]->_combined_matrix);
            }

            ///

            /////////////////////////////////
            IDirect3DIndexBuffer9* pIb;
            pMesh->GetIndexBuffer(&pIb);
            DWORD nFace = pMesh->GetNumFaces();
            D3DINDEXBUFFER_DESC desc;
            pIb->GetDesc( &desc );
            if (desc.Format == D3DFMT_INDEX16) {
                void* pIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(WORD), (void**)&pIndexBuffer, 0);
                char* p = (char*)pIndexBuffer;
    //            _TRACE_("["<<i<<"]:IndexFmt=WORD");
                for (int f = 0; f < nFace; f++) {
                    WORD val1,val2,val3;
                    memcpy(&(val1), p, sizeof(WORD));  p += sizeof(WORD);
                    memcpy(&(val2), p, sizeof(WORD));  p += sizeof(WORD);
                    memcpy(&(val3), p, sizeof(WORD));  p += sizeof(WORD);
    //                _TRACE_("["<<i<<"]["<<f<<"]:Index=("<<val1<<","<<val2<<","<<val3<<")");
                    int offset = (v_cnt-nVertices); //頂点番号を通しにするための計算。
                                                    //v_cnt:通しカウンタ ＝ nVertices：初回はメッシュコンテナの頂点数 なので 0 となる。
                    _paIndexBuffer_data[i_cnt+0] = offset + val1;
                    _paIndexBuffer_data[i_cnt+1] = offset + val2;
                    _paIndexBuffer_data[i_cnt+2] = offset + val3;
                    _paIndexBuffer_bone_combi_index[i_cnt+0] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+0]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+1] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+1]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+2] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+2]].bone_combi_index);
                    i_cnt+=3;
                }
            } else {
                void* pIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(DWORD), (void**)&pIndexBuffer, 0);
                char* p = (char*)pIndexBuffer;
                for (int f = 0; f < nFace; f++) {
                    WORD val1,val2,val3;
                    memcpy(&(val1), p, sizeof(WORD));  p += sizeof(DWORD);
                    memcpy(&(val2), p, sizeof(WORD));  p += sizeof(DWORD);
                    memcpy(&(val3), p, sizeof(WORD));  p += sizeof(DWORD);
                    int offset = (v_cnt-nVertices); //頂点番号を通しにするための計算。
                                                    //v_cnt:通しカウンタ ＝ nVertices：初回はメッシュコンテナの頂点数 なので 0 となる。
                    _paIndexBuffer_data[i_cnt+0] = offset + val1;
                    _paIndexBuffer_data[i_cnt+1] = offset + val2;
                    _paIndexBuffer_data[i_cnt+2] = offset + val3;
                    _paIndexBuffer_bone_combi_index[i_cnt+0] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+0]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+1] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+1]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+2] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+2]].bone_combi_index);
                    i_cnt += 3;
                }
            }
            pIb->Unlock();
            pIb->Release();

            //情報は頂いたので Meshだけ解放！
            GGAF_RELEASE(pMeshContainer->MeshData.pMesh);
            pMeshContainer->MeshData.pMesh = nullptr;
        }


    ///////////////////////////////////////////////////

////////////////////////////////////////////////
        //描画時（DrawIndexedPrimitive）のパラメータリスト作成
        std::vector<SkinAniMeshModel::INDEXPARAM> param_tmp;

        int paramno = 0;

        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;

        int frame_no = 0;
        int prev_frame_no = -1;

        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;
        UINT vtx_idx1,vtx_idx2,vtx_idx3;
        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < _nFaces; faceNoCnt++) {
            frame_no = _paIndexBuffer_bone_combi_index[faceNoCnt*3 + 0]; //faceNoCnt(面番号)に対する頂点の属するフレームメッシュ通し番号
            if ((frame_no % SkinAniMeshModel_MAX_BONE_WORLD_MATRIX) == 0 && frame_no != prev_frame_no) {
//                _TRACE_("BREAK! frame_no="<<frame_no);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                param_tmp.push_back(SkinAniMeshModel::INDEXPARAM());
                param_tmp[paramno].MaterialNo = 0;
                param_tmp[paramno].BaseVertexIndex = 0;
                param_tmp[paramno].MinIndex = UINT_MAX; //次回ブレイク時に設定、必ずブレイクしたいため変な値にしとく
                param_tmp[paramno].NumVertices = UINT_MAX; //次回ブレイク時に設定
                param_tmp[paramno].StartIndex = faceNoCnt*3;
                param_tmp[paramno].PrimitiveCount = UINT_MAX; //次回ブレイク時に設定

                if (faceNoCnt > 0) {
                    param_tmp[paramno-1].MinIndex = min_num_vertices;
                    param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    param_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //リセット
                    max_num_vertices = 0;
                    min_num_vertices = UINT_MAX;
                }
                paramno++;
            }
            vtx_idx1 = _paIndexBuffer_data[faceNoCnt*3 + 0]; //faceNoCnt(面番号)に対する頂点番号
            vtx_idx2 = _paIndexBuffer_data[faceNoCnt*3 + 1];
            vtx_idx3 = _paIndexBuffer_data[faceNoCnt*3 + 2];

            if (max_num_vertices < vtx_idx1) {
                max_num_vertices = vtx_idx1;
            }
            if (max_num_vertices < vtx_idx2) {
                max_num_vertices = vtx_idx2;
            }
            if (max_num_vertices < vtx_idx3) {
                max_num_vertices = vtx_idx3;
            }

            if (min_num_vertices > vtx_idx1) {
                min_num_vertices = vtx_idx1;
            }
            if (min_num_vertices > vtx_idx2) {
                min_num_vertices = vtx_idx2;
            }
            if (min_num_vertices >  vtx_idx3) {
                min_num_vertices = vtx_idx3;
            }
            prev_frame_no = frame_no;
        }
        if (_nFaces > 0) {
            param_tmp[paramno-1].MinIndex = min_num_vertices;
            param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            param_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }
        _index_param_num = paramno;
        _paIndexParam = NEW SkinAniMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            _paIndexParam[i].MaterialNo      = param_tmp[i].MaterialNo;
            _paIndexParam[i].BaseVertexIndex = param_tmp[i].BaseVertexIndex;
            _paIndexParam[i].MinIndex        = param_tmp[i].MinIndex;
            _paIndexParam[i].NumVertices     = param_tmp[i].NumVertices;
            _paIndexParam[i].StartIndex      = param_tmp[i].StartIndex;
            _paIndexParam[i].PrimitiveCount  = param_tmp[i].PrimitiveCount;
        }
        _size_vertices = _size_vertex_unit * _nVertices;

        _TRACE_("まとめ！");
        for (int i = 0; i < _nVertices; i++) {
            SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[i]); //書き込む1頂点の開始アドレス
            _TRACE_("["<<i<<"]:"<<
                    " ["<<(pVtx->bone_combi_index)<<"] "<<
                    " Vertex=("<<(pVtx->x)<<","<<(pVtx->y)<<","<<(pVtx->z)<<")"<<
                    " infl_bone_id=("<<(int)(pVtx->infl_bone_id[0])<<","<<(int)(pVtx->infl_bone_id[1])<<","<<(int)(pVtx->infl_bone_id[2])<<","<<(int)(pVtx->infl_bone_id[3])<<")"<<
                    " infl_bone_id_order=("<<(int)(pVtx->infl_bone_id_order[0])<<","<<(int)(pVtx->infl_bone_id_order[1])<<","<<(int)(pVtx->infl_bone_id_order[2])<<","<<(int)(pVtx->infl_bone_id_order[3])<<")"<<
                    " infl_weight=("<<(pVtx->infl_weight[0])<<","<<(pVtx->infl_weight[1])<<","<<(pVtx->infl_weight[2])<<","<<(pVtx->infl_weight[3])<<")"<<
                    " Normal=("<<(pVtx->nx)<<","<<(pVtx->ny)<<","<<(pVtx->nz)<<")"

            );
        }
//        for (int i = 0; i < _nFaces; ++i) {
//            _TRACE_("["<<i<<"]:Index=("<<(_paIndexBuffer_data[i*3+0])<<","<<
//                    (_paIndexBuffer_data[i*3+1])<<","<<
//                    (_paIndexBuffer_data[i*3+2])<<")");
//        }

    } //if (_paVtxBuffer_data == nullptr)



    if (_pVertexDeclaration == nullptr) {
        HRESULT hr;
        //D3DVERTEXELEMENT9 構造体の配列要素数
        D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[9];
        WORD  st0_offset_next = 0;
        //プライマリ部頂点フォーマット
        //float x, y, z; // 頂点座標
        paVtxelem[0].Stream = 0;
        paVtxelem[0].Offset = st0_offset_next;
        paVtxelem[0].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[0].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[0].Usage = D3DDECLUSAGE_POSITION;
        paVtxelem[0].UsageIndex = 0;
        st0_offset_next += sizeof(float)*3;
        //float nx, ny, nz; // 法線
        paVtxelem[1].Stream = 0;
        paVtxelem[1].Offset = st0_offset_next;
        paVtxelem[1].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[1].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[1].Usage = D3DDECLUSAGE_NORMAL;
        paVtxelem[1].UsageIndex = 0;
        st0_offset_next += sizeof(float)*3;
        //float index;
        paVtxelem[2].Stream = 0;
        paVtxelem[2].Offset = st0_offset_next;
        paVtxelem[2].Type = D3DDECLTYPE_FLOAT1;
        paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[2].Usage = D3DDECLUSAGE_PSIZE;
        paVtxelem[2].UsageIndex = 0;
        st0_offset_next += sizeof(float)*1;
        //DWORD color; // 頂点カラー
        paVtxelem[3].Stream = 0;
        paVtxelem[3].Offset = st0_offset_next;
        paVtxelem[3].Type = D3DDECLTYPE_D3DCOLOR;
        paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[3].Usage = D3DDECLUSAGE_COLOR;
        paVtxelem[3].UsageIndex = 0;
        st0_offset_next += sizeof(DWORD);
        //float tu, tv; // テクスチャ座標
        paVtxelem[4].Stream = 0;
        paVtxelem[4].Offset = st0_offset_next;
        paVtxelem[4].Type = D3DDECLTYPE_FLOAT2;
        paVtxelem[4].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[4].Usage = D3DDECLUSAGE_TEXCOORD;
        paVtxelem[4].UsageIndex = 0;
        st0_offset_next += sizeof(float)*2;
        //float infl_weight[4];
        paVtxelem[5].Stream = 0;
        paVtxelem[5].Offset = st0_offset_next;
        paVtxelem[5].Type = D3DDECLTYPE_FLOAT4;
        paVtxelem[5].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[5].Usage = D3DDECLUSAGE_BLENDWEIGHT;
        paVtxelem[5].UsageIndex = 0;
        st0_offset_next += sizeof(float)*4;
        // byte  infl_bone_id[4];
        paVtxelem[6].Stream = 0;
        paVtxelem[6].Offset = st0_offset_next;
        paVtxelem[6].Type = D3DDECLTYPE_UBYTE4;
        paVtxelem[6].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[6].Usage = D3DDECLUSAGE_BLENDINDICES;
        paVtxelem[6].UsageIndex = 0;
        st0_offset_next += sizeof(byte)*4;
        // byte  infl_bone_id_order[4];
        paVtxelem[7].Stream = 0;
        paVtxelem[7].Offset = st0_offset_next;
        paVtxelem[7].Type = D3DDECLTYPE_UBYTE4;
        paVtxelem[7].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[7].Usage = D3DDECLUSAGE_BLENDINDICES;
        paVtxelem[7].UsageIndex = 1;
        st0_offset_next += sizeof(byte)*4;
        //D3DDECL_END()
        paVtxelem[8].Stream = 0xFF;
        paVtxelem[8].Offset = 0;
        paVtxelem[8].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[8].Method = 0;
        paVtxelem[8].Usage = 0;
        paVtxelem[8].UsageIndex = 0;

        hr = God::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "God::_pID3DDevice9->CreateVertexDeclaration 失敗 model="<<(_model_name));
        //ストリーム数取得        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);
        GGAF_DELETEARR(paVtxelem);
    }


    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        TextureManager* pTextureManager = pGOD->_pModelManager->_pModelTextureManager;
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    if (_pVertexBuffer == nullptr) {
        HRESULT hr;
        //頂点バッファ作成
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                0, //SkinAniMeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));

        //バッファへ作成済み頂点データを流し込む
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);
        memcpy(pVertexBuffer, _paVtxBuffer_data, _size_vertices); //pVertexBuffer ← paVertex
        _pVertexBuffer->Unlock();
    }

    //インデックスバッファデータ作成
    if (_pIndexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateIndexBuffer(
                                   sizeof(WORD) * _nFaces * 3,
                                   D3DUSAGE_WRITEONLY,
                                   D3DFMT_INDEX16,
                                   D3DPOOL_DEFAULT,
                                   &(_pIndexBuffer),
                                   nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));
        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , _paIndexBuffer_data , sizeof(WORD) * _nFaces * 3);
        _pIndexBuffer->Unlock();
    }
    _TRACE3_("_model_name=" << _model_name << " end");
}

ID3DXAnimationController* SkinAniMeshModel::getCloneAnimationController() {
    ID3DXAnimationController* _pAc = nullptr;
    HRESULT hr = _pAniControllerBase->CloneAnimationController(
                                _pAniControllerBase->GetMaxNumAnimationOutputs(),
                                _pAniControllerBase->GetMaxNumAnimationSets(),
                                _pAniControllerBase->GetMaxNumTracks(),
                                _pAniControllerBase->GetMaxNumEvents(),
                                        &_pAc);
    checkDxException(hr, D3D_OK, "アニメーションコントローラーのクローンに失敗しました。");
    return _pAc;
}
//int SkinAniMeshModel::getAnimTicksPerSecond(std::string& prm_xfile_name) {
//    if (prm_xfile_name == "") {
//         throwCriticalException("SkinAniMeshModel::getAnimTicksPerSecond() メッシュファイル("<<prm_xfile_name<<".x)が見つかりません。");
//    }
//    //XファイルからAnimTicksPerSecondの値を独自に取り出す
//    std::ifstream ifs(prm_xfile_name.c_str());
//    if (ifs.fail()) {
//        throwCriticalException("["<<prm_xfile_name<<"] が開けません");
//    }
//    std::string buf;
//    bool isdone = false;
//    int anim_ticks_per_second = -1;
//    std::string data;
//    while (isdone == false && !ifs.eof()) {
//        ifs >> data;
//        if (data == "AnimTicksPerSecond" || data == "AnimTicksPerSecond{") {
//            while (isdone == false) {
//                ifs >> data;
//                if (data == "{") {
//                    continue;
//                } else if (data == "}") {
//                    isdone = true;
//                    break;
//                } else {
//                    anim_ticks_per_second = atoi(data.c_str()); //"60;" → 60を得る
//                    if (anim_ticks_per_second == 0) {
//                        //数値に変換できない場合は無効
//                        anim_ticks_per_second = -1;
//                        isdone = false;
//                    } else {
//                        isdone = true;
//                    }
//                    break;
//                }
//            }
//        }
//    }
//    ifs.close();
//    return anim_ticks_per_second;
//}

void SkinAniMeshModel::setFrameInfo(SkinAniMeshFrame* prm_pFrame) {
    prm_pFrame->_frame_index = _tmp_frame_index; //フレームインデックスを保持
    _tmp_frame_index++;

    _vecAllBoneFrame.push_back(prm_pFrame);
    if (prm_pFrame->pMeshContainer) {
        //メッシュコンテナ有り
        _vecDrawBoneFrame.push_back(prm_pFrame);
    }
    if (prm_pFrame->pFrameFirstChild) {
        // 子フレーム有り
        setFrameInfo((SkinAniMeshFrame*)prm_pFrame->pFrameFirstChild);
    }
    if (prm_pFrame->pFrameSibling) {
        //兄弟フレーム有り
        setFrameInfo((SkinAniMeshFrame*)prm_pFrame->pFrameSibling);
    }
}
int SkinAniMeshModel::getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage ) {
    D3DVERTEXELEMENT9 *e = elems;
    while( e->Stream != 0xff ) {
        if ( e->Usage == usage )
            return (int)(e->Offset);
        e = e + 1;
    }
    return -1;
}

void SkinAniMeshModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    //デバイスロスト時は解放します。
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void SkinAniMeshModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);
    _TRACE3_("_model_name=" << _model_name << " end");
}

SkinAniMeshModel::~SkinAniMeshModel() {
    for (UINT ani_set_index = 0; ani_set_index < _num_animation_set; ani_set_index++) {
        bool* p = _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index];
        GGAF_DELETEARR(p);
    }
    GGAF_DELETEARR(_papaBool_AnimationSetIndex_BoneFrameIndex_is_act);

    GGAF_RELEASE(_pAniControllerBase);
    _pAllocHierarchy->DestroyFrame((D3DXFRAME*)_pFrameRoot);
    GGAF_DELETE(_pAllocHierarchy);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames); //Model::~Model() で実行されてるはず
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_bone_combi_index);
    GGAF_DELETEARR(_paIndexParam);
//    GGAF_DELETE(_pFrameRoot); //_pAllocHierarchyを消すと_pFrameRootは消さなくて良いと思う
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}
