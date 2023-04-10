#include "jp/ggaf/dx/model/BoneAniMeshModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/BoneAniMeshActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/effect/BoneAniMeshEffect.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

//DefaultBoneAniMeshEffect.fx と 定数を一致させる事
#define BoneAniMeshModel_MAX_BONE_WORLD_MATRIX (4) //2以上でないとブレイクしないのでダメ

using namespace GgafDx;
DWORD BoneAniMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

BoneAniMeshModel::BoneAniMeshModel(const char* prm_model_id) : Model(prm_model_id) {
    _obj_class |= Obj_GgafDx_BoneAniMeshModel;
    _pAllocHierarchy = nullptr;
    _pFrameRoot = nullptr;
    _pAniControllerBase = nullptr;
    _num_materials = 0L;
    _anim_ticks_per_second = 4800; //restoreBoneAniMeshModel で上書きされる場合がある。
    _paVtxBuffer_data = nullptr;
    _paIndex16Buffer_data = nullptr;
    _paIndex32Buffer_data = nullptr;
    _paVertexBuffer = nullptr;
    _paIndexBuffer = nullptr;
    _index_param_num = 0;
    _paIndexParam = nullptr;
    _paIndexBuffer_frame_no = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = sizeof(BoneAniMeshModel::VERTEX);
    _nFaces = 0;
    _nVertices = 0;
    _tmp_frame_index = 0;
    _num_animation_set = 0;
    _max_draw_set_num = 1;
    _papaBool_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _indexBuffer_fmt = D3DFMT_UNKNOWN;
}

HRESULT BoneAniMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("BoneAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    HRESULT hr;
    //対象アクター
    BoneAniMeshActor* pTargetActor = (BoneAniMeshActor*)prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    BoneAniMeshEffect* pBoneAniMeshEffect = (BoneAniMeshEffect*)(prm_pActor_target->getEffect());
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pBoneAniMeshEffect->_pID3DXEffect;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //頂点バッファとインデックスバッファを設定
        pDevice->SetStreamSource(0, _paVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(BoneAniMeshModel::FVF);
        pDevice->SetIndices(_paIndexBuffer);
        hr = pID3DXEffect->SetFloat(pBoneAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoneAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoneAniMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoneAniMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
    }

    //マテリアル・テクスチャの一発目をセット、
    LPDIRECT3DBASETEXTURE9 pTex = _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9;
    hr = pDevice->SetTexture(0, pTex);
    checkDxException(hr, D3D_OK, "SetTexture に失敗しました。");
    hr = pID3DXEffect->SetValue(pBoneAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
    Puppeteer* pActorPuppeteer = pTargetActor->_pPuppeteer;
    pActorPuppeteer->updateAnimationTrack(); //アニメーション反映
    //モデルのワールド変換行列更新
    pTargetActor->_stackWorldMat.SetWorldMatrix(&(pTargetActor->_matWorld));
    ID3DXAnimationSet* pAs0 = pActorPuppeteer->_apAs[0]; //トラック0のアニメーションセット
    ID3DXAnimationSet* pAs1 = pActorPuppeteer->_apAs[1]; //トラック1のアニメーションセット
    int as0_index = pAs0 ? (int)_mapAnimationSet_AniSetindex[pAs0] : -1;
    int as1_index = pAs1 ? (int)_mapAnimationSet_AniSetindex[pAs1] : -1;
    pTargetActor->_stackWorldMat.UpdateFrame(&_matBaseTransformMatrix, _pFrameRoot, as0_index, as1_index, _papaBool_AnimationSetIndex_BoneFrameIndex_is_act);

    std::vector<BoneAniMeshFrame*>::iterator it_1 = _vecDrawBoneFrame.begin();

/////////////////////////////////////////////
    for (int i = 0; i < _index_param_num; i++) {
        const INDEXPARAM& idxparam = _paIndexParam[i];
        for (int j = 0; j < BoneAniMeshModel_MAX_BONE_WORLD_MATRIX; j++) {
            if (it_1 != _vecDrawBoneFrame.end()) {
                hr = pID3DXEffect->SetMatrix(pBoneAniMeshEffect->_ah_matWorld[j], &((*it_1)->_world_trans_matrix));
                ++it_1;
            } else {
                break;
            }
        }

        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "BoneAniMeshModel::draw() EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "BoneAniMeshModel::draw() End() に失敗しました。");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pBoneAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pBoneAniMeshEffect->_effect_name<<"("<<pBoneAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "BoneAniMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "BoneAniMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pBoneAniMeshEffect->_begin) {
                throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pBoneAniMeshEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "BoneAniMeshModel::draw() CommitChanges() に失敗しました。");
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
    }
    //前回描画モデル名反映
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pBoneAniMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void BoneAniMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data == nullptr) {
        HRESULT hr;
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        if (_draw_set_num != 1) {
            _TRACE_("BoneAniMeshModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は常に 1 です。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
            _draw_set_num = 1;
        }
        std::string xfilepath = Model::getMeshXFilePath(xdata.XFileNames[0]);
        //AnimTicksPerSecondを独自に取り出す。デフォルトは4800
        _anim_ticks_per_second = BoneAniMeshModel::getAnimTicksPerSecond(xfilepath);
        if (_anim_ticks_per_second < 0) {
            _anim_ticks_per_second = 4800;
        }
        //Xファイルのファイルロード
        _pAllocHierarchy = NEW BoneAniMeshAllocHierarchy(); // CAllocHierarchyBaseの派生クラス
        hr = D3DXLoadMeshHierarchyFromX(
                xfilepath.c_str(),
                D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
                pCARETAKER->_pID3DDevice9,
                _pAllocHierarchy,
                nullptr,
                (D3DXFRAME**)(&_pFrameRoot),
                &_pAniControllerBase
             );
        _TRACE_("_pAllocHierarchy="<<_pAllocHierarchy<<" _pFrameRoot="<<_pFrameRoot<<" _pAniControllerBase="<<_pAniControllerBase<<" xfile_name.c_str()="<<xfilepath.c_str());
        checkDxException(hr, D3D_OK, xfilepath<<" 読み込みに失敗しました。対象="<<xfilepath);
        if (_pFrameRoot == nullptr) {
            throwCriticalException(xfilepath<<" のフレーム情報が取得できません！");
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
            for (DWORD frame_index = 0; frame_index < _vecAllBoneFrame.size(); frame_index++) {
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
            if (_vecDrawBoneFrame[i]->pMeshContainer == nullptr) {
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
        _paVtxBuffer_data =  NEW BoneAniMeshModel::VERTEX[_nVertices];
        _indexBuffer_fmt = D3DFMT_UNKNOWN;
        _paIndexBuffer_frame_no = NEW int[_nFaces*3];
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
            D3DXMESHCONTAINER* pMeshContainer = _vecDrawBoneFrame[i]->pMeshContainer;
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
            void* paVertexBuffer;
            int nVertices = (int)(pMesh->GetNumVertices()); //メッシュコンテナの頂点数
            pVb->Lock(0, nVertices*size_vertex_unit, (void**)&paVertexBuffer, 0);
            for (int j = 0; j < nVertices; j++) {
                char* p = nullptr;
                BoneAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[v_cnt]); //書き込む1頂点の開始アドレス
                char* pVertex_base = (char*)paVertexBuffer + (size_vertex_unit*j);  //読み込む1頂点の開始アドレス
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
                // float index
                pVtx->index = i;

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
                v_cnt ++;
            }
            pVb->Unlock();
            pVb->Release();

            /////////////////////////////////
            IDirect3DIndexBuffer9* pIb;
            pMesh->GetIndexBuffer(&pIb);
            DWORD nFace = pMesh->GetNumFaces();
            D3DINDEXBUFFER_DESC desc;
            pIb->GetDesc( &desc );
            if (_indexBuffer_fmt == D3DFMT_UNKNOWN) {
                _indexBuffer_fmt = desc.Format;
                if (_indexBuffer_fmt == D3DFMT_INDEX16) {
                    _paIndex16Buffer_data = NEW uint16_t[_nFaces*3];
                } else {
                    _paIndex32Buffer_data = NEW uint32_t[_nFaces*3];
                }
            }


            if (_indexBuffer_fmt == D3DFMT_INDEX16) {
                void* paIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(uint16_t), (void**)&paIndexBuffer, 0);
                char* p = (char*)paIndexBuffer;
    //            _TRACE_("["<<i<<"]:IndexFmt=uint16_t");
                for (int f = 0; f < nFace; f++) {
                    uint16_t val1,val2,val3;
                    memcpy(&(val1), p, sizeof(uint16_t));  p += sizeof(uint16_t);
                    memcpy(&(val2), p, sizeof(uint16_t));  p += sizeof(uint16_t);
                    memcpy(&(val3), p, sizeof(uint16_t));  p += sizeof(uint16_t);
    //                _TRACE_("["<<i<<"]["<<f<<"]:Index=("<<val1<<","<<val2<<","<<val3<<")");
                    int offset = (v_cnt-nVertices); //頂点番号を通しにするための計算。
                                                    //v_cnt:通しカウンタ ＝ nVertices：初回はメッシュコンテナの頂点数 なので 0 となる。
                    _paIndex16Buffer_data[i_cnt+0] = offset + val1;
                    _paIndex16Buffer_data[i_cnt+1] = offset + val2;
                    _paIndex16Buffer_data[i_cnt+2] = offset + val3;
                    _paIndexBuffer_frame_no[i_cnt+0] = (int)(_paVtxBuffer_data[_paIndex16Buffer_data[i_cnt+0]].index);
                    _paIndexBuffer_frame_no[i_cnt+1] = (int)(_paVtxBuffer_data[_paIndex16Buffer_data[i_cnt+1]].index);
                    _paIndexBuffer_frame_no[i_cnt+2] = (int)(_paVtxBuffer_data[_paIndex16Buffer_data[i_cnt+2]].index);
                    i_cnt+=3;
                }
            } else {
                void* paIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(uint32_t), (void**)&paIndexBuffer, 0);
                char* p = (char*)paIndexBuffer;
                for (int f = 0; f < nFace; f++) {
                    uint32_t val1,val2,val3;
                    memcpy(&(val1), p, sizeof(uint32_t));  p += sizeof(uint32_t);
                    memcpy(&(val2), p, sizeof(uint32_t));  p += sizeof(uint32_t);
                    memcpy(&(val3), p, sizeof(uint32_t));  p += sizeof(uint32_t);
                    int offset = (v_cnt-nVertices); //頂点番号を通しにするための計算。
                                                    //v_cnt:通しカウンタ ＝ nVertices：初回はメッシュコンテナの頂点数 なので 0 となる。
                    _paIndex32Buffer_data[i_cnt+0] = offset + val1;
                    _paIndex32Buffer_data[i_cnt+1] = offset + val2;
                    _paIndex32Buffer_data[i_cnt+2] = offset + val3;
                    _paIndexBuffer_frame_no[i_cnt+0] = (int)(_paVtxBuffer_data[_paIndex32Buffer_data[i_cnt+0]].index);
                    _paIndexBuffer_frame_no[i_cnt+1] = (int)(_paVtxBuffer_data[_paIndex32Buffer_data[i_cnt+1]].index);
                    _paIndexBuffer_frame_no[i_cnt+2] = (int)(_paVtxBuffer_data[_paIndex32Buffer_data[i_cnt+2]].index);
                    i_cnt += 3;
                }
            }
            pIb->Unlock();
            pIb->Release();

            //情報は頂いたので Meshだけ解放！
            GGAF_RELEASE(pMeshContainer->MeshData.pMesh);
            pMeshContainer->MeshData.pMesh = nullptr;
        }

////////////////////////////////////////////////
        //描画時（DrawIndexedPrimitive）のパラメータリスト作成
        std::vector<BoneAniMeshModel::INDEXPARAM> param_tmp;

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
            frame_no = _paIndexBuffer_frame_no[faceNoCnt*3 + 0]; //faceNoCnt(面番号)に対する頂点の属するフレームメッシュ通し番号
//                _TRACE_("frame_no="<<frame_no<<" prev_frame_no="<<prev_frame_no);
            if ((frame_no % BoneAniMeshModel_MAX_BONE_WORLD_MATRIX) == 0 && frame_no != prev_frame_no) {
//                _TRACE_("BREAK!");
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                param_tmp.push_back(BoneAniMeshModel::INDEXPARAM());
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
            if (_indexBuffer_fmt == D3DFMT_INDEX16) {
                vtx_idx1 = _paIndex16Buffer_data[faceNoCnt*3 + 0]; //faceNoCnt(面番号)に対する頂点番号
                vtx_idx2 = _paIndex16Buffer_data[faceNoCnt*3 + 1];
                vtx_idx3 = _paIndex16Buffer_data[faceNoCnt*3 + 2];
            } else {
                vtx_idx1 = _paIndex32Buffer_data[faceNoCnt*3 + 0]; //faceNoCnt(面番号)に対する頂点番号
                vtx_idx2 = _paIndex32Buffer_data[faceNoCnt*3 + 1];
                vtx_idx3 = _paIndex32Buffer_data[faceNoCnt*3 + 2];
            }


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
        _paIndexParam = NEW BoneAniMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            _paIndexParam[i].MaterialNo      = param_tmp[i].MaterialNo;
            _paIndexParam[i].BaseVertexIndex = param_tmp[i].BaseVertexIndex;
            _paIndexParam[i].MinIndex        = param_tmp[i].MinIndex;
            _paIndexParam[i].NumVertices     = param_tmp[i].NumVertices;
            _paIndexParam[i].StartIndex      = param_tmp[i].StartIndex;
            _paIndexParam[i].PrimitiveCount  = param_tmp[i].PrimitiveCount;
        }
        _size_vertices = _size_vertex_unit * _nVertices;

//        _TRACE_("まとめ！");
//        for (int i = 0; i < _nVertices; i++) {
//            BoneAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[i]); //書き込む1頂点の開始アドレス
//            _TRACE_("["<<i<<"]:Vertex=("<<(pVtx->x)<<","<<(pVtx->y)<<","<<(pVtx->z)<<")  Normal=("<<(pVtx->nx)<<","<<(pVtx->ny)<<","<<(pVtx->nz)<<")");
//        }
//        for (int i = 0; i < _nFaces; ++i) {
//            _TRACE_("["<<i<<"]:Index=("<<(_paIndexBuffer_data[i*3+0])<<","<<
//                    (_paIndexBuffer_data[i*3+1])<<","<<
//                    (_paIndexBuffer_data[i*3+2])<<")");
//        }

    } //if (_paVtxBuffer_data == nullptr)


    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] = connectToTextureManager(_pa_texture_filenames[n].c_str());
        }
    }

    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //頂点バッファ作成
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                BoneAniMeshModel::FVF,
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
        if (_indexBuffer_fmt == D3DFMT_INDEX16) {
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
        } else {
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
        }

    }
    _TRACE3_("_model_id=" << _model_id << " end");
}

ID3DXAnimationController* BoneAniMeshModel::getCloneAnimationController() {
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
int BoneAniMeshModel::getAnimTicksPerSecond(std::string& prm_xfile_name) {
    if (prm_xfile_name == "") {
         throwCriticalException("BoneAniMeshModel::getAnimTicksPerSecond() メッシュファイル(*.x)が見つかりません。");
    }
    //XファイルからAnimTicksPerSecondの値を独自に取り出す
    std::ifstream ifs(prm_xfile_name.c_str());
    if (ifs.fail()) {
        throwCriticalException("["<<prm_xfile_name<<"] が開けません");
    }
    std::string buf;
    bool isdone = false;
    int anim_ticks_per_second = -1;
    std::string data;
    while (isdone == false && !ifs.eof()) {
        ifs >> data;
        if (data == "AnimTicksPerSecond" || data == "AnimTicksPerSecond{") {
            while (isdone == false) {
                ifs >> data;
                if (data == "{") {
                    continue;
                } else if (data == "}") {
                    isdone = true;
                    break;
                } else {
                    anim_ticks_per_second = atoi(data.c_str()); //"60;" → 60を得る
                    if (anim_ticks_per_second == 0) {
                        //数値に変換できない場合は無効
                        anim_ticks_per_second = -1;
                        isdone = false;
                    } else {
                        isdone = true;
                    }
                    break;
                }
            }
        }
    }
    ifs.close();
    return anim_ticks_per_second;
}

void BoneAniMeshModel::setFrameInfo(BoneAniMeshFrame* prm_pFrame) {
    prm_pFrame->_frame_index = _tmp_frame_index; //フレームインデックスを保持
    _tmp_frame_index++;

    _vecAllBoneFrame.push_back(prm_pFrame);
    if (prm_pFrame->pMeshContainer) {
        //メッシュコンテナ有り
        _vecDrawBoneFrame.push_back(prm_pFrame);
    }
    if (prm_pFrame->pFrameFirstChild) {
        // 子フレーム有り
        setFrameInfo((BoneAniMeshFrame*)prm_pFrame->pFrameFirstChild);
    }
    if (prm_pFrame->pFrameSibling) {
        //兄弟フレーム有り
        setFrameInfo((BoneAniMeshFrame*)prm_pFrame->pFrameSibling);
    }
}
int BoneAniMeshModel::getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage ) {
    D3DVERTEXELEMENT9 *e = elems;
    while( e->Stream != 0xff ) {
        if ( e->Usage == usage )
            return (int)(e->Offset);
        e = e + 1;
    }
    return -1;
}

void BoneAniMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //デバイスロスト時は解放します。
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void BoneAniMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
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

BoneAniMeshModel::~BoneAniMeshModel() {
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
    GGAF_DELETEARR_NULLABLE(_paIndex16Buffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex32Buffer_data);
    GGAF_DELETEARR(_paIndexBuffer_frame_no);
    GGAF_DELETEARR(_paIndexParam);
//    GGAF_DELETE(_pFrameRoot); //_pAllocHierarchyを消すと_pFrameRootは消さなくて良いと思う
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}
