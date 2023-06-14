#include "jp/ggaf/dx/model/D3DXAniMeshModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/D3DXAniMeshActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/effect/D3DXAniMeshEffect.h"
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

using namespace GgafDx;

D3DXAniMeshModel::D3DXAniMeshModel(const char* prm_model_id) : Model(prm_model_id) {
    _obj_class |= Obj_GgafDx_D3DXAniMeshModel;
    _pAllocHierarchy = nullptr;
    _pFrameRoot = nullptr;
    _pAniControllerBase = nullptr;
    _num_materials = 0L;
    _anim_ticks_per_second = 4800; //restoreD3DXAniMeshModel で上書きされる場合がある。
    _max_draw_set_num = 1;
}

HRESULT D3DXAniMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("D3DXAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    HRESULT hr;
    //対象アクター
    D3DXAniMeshActor* pTargetActor = (D3DXAniMeshActor*)prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    D3DXAniMeshEffect* pD3DXAniMeshEffect = (D3DXAniMeshEffect*)(prm_pActor_target->getEffect());
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pCARETAKER->_pID3DDevice9->SetFVF(D3DXAniMeshActor::FVF);
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_fog_starts_far_rate, _fog_starts_far_rate);
        checkDxException(hr, D3D_OK, "SetFloat(_h_fog_starts_far_rate) に失敗しました。");
    }

    pTargetActor->_pPuppeteer->updateAnimationTrack(); //アニメーション反映
    //モデルのワールド変換行列更新
    pTargetActor->_stackWorldMat.SetWorldMatrix(&(pTargetActor->_matWorld));
    pTargetActor->_stackWorldMat.UpdateFrame(&_matBaseTransformMatrix, _pFrameRoot);
    std::list< BoneAniMeshFrame* > *pDrawList = pTargetActor->_stackWorldMat.GetDrawList(); // 描画リストを取得
    std::list<BoneAniMeshFrame*>::iterator it = pDrawList->begin();

    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    int n = 0;
    //マテリアル・テクスチャの一発目をセット、
    LPDIRECT3DBASETEXTURE9 pTex = nullptr;
    LPDIRECT3DBASETEXTURE9 pLastTex = nullptr;
    if (_papTextureConnection[n]) {
        pLastTex = _papTextureConnection[n]->peek()->_pIDirect3DBaseTexture9;
        pDevice->SetTexture(0, pLastTex);
    } else {
        //無ければテクスチャ無し
        pDevice->SetTexture(0, nullptr);
    }
    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");

    for (int i = 0; it != pDrawList->end(); i++, ++it) {
        //描画(TODO:なんか無駄なループ）
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("["<<i<<"],EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() End() に失敗しました。");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin) {
                throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->_world_trans_matrix));
        checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        if ((*it)->pMeshContainer == nullptr) {
            _TRACE4_("["<<i<<"]×SetMatrix FrameName="<<((*it)->Name)<<" 飛ばし！");
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
                if (n > 0) {
                    pTex = _papTextureConnection[n]->peek()->_pIDirect3DBaseTexture9;
                    if (pTex != pLastTex) {
                        //テクスチャが異なれば設定
                        pDevice->SetTexture(0, pTex);
                        pLastTex = pTex;
                    }
                    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
                    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
                }
                _TRACE4_("["<<i<<"]["<<j<<"],SetMaterial");
                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() CommitChanges() に失敗しました。");
                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
#ifdef MY_DEBUG
                GgafCore::Caretaker::_num_draw++;
#endif
                n++;
            }
        }
    }
    //前回描画モデル名反映
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pD3DXAniMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

ID3DXAnimationController* D3DXAniMeshModel::getCloneAnimationController() {
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


void D3DXAniMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //TODO:作成中？！！！！！！！！
    ModelManager* pModelManager = pCARETAKER->_pModelManager;
    //【restoreD3DXAniMeshModel再構築（＝初期化）処理概要】
    //1)D3DXLoadMeshFromXを使用してXファイルを読み込む
    //2)D3DXAniMeshModelのメンバにセット
    //Xファイルのロードして必要な内容をD3DXAniMeshModelメンバに設定しインスタンスとして完成させたい
//    LPD3DXMESH pID3DXAniMesh; //メッシュ(ID3DXAniMeshインターフェイスへのポインタ）
    D3DMATERIAL9* model_paMaterial = nullptr; //マテリアル(D3DXMATERIAL構造体の配列の先頭要素を指すポインタ）
    TextureConnection** model_papTextureConnection = nullptr; //テクスチャ配列(IDirect3DTexture9インターフェイスへのポインタを保持するオブジェクト）
//    DWORD _num_materials;
    ModelManager::ModelXFileFmt xdata;
    obtainMetaModelInfo(&xdata);
    if (_draw_set_num != 1) {
        _TRACE_("D3DXAniMeshModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 1 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
        _draw_set_num = 1;
    }
    std::string xfilepath = Model::getMeshXFilePath(xdata.XFileNames[0]);
    //AnimTicksPerSecondの値を独自に取り出す
    std::ifstream ifs(xfilepath.c_str());
    if (ifs.fail()) {
        throwCriticalException("["<<xfilepath<<"] が開けません");
    }
    std::string buf;
    bool isdone = false;
    int anim_ticks_per_second = 4800;
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
                    isdone = true;
                    break;
                }
            }
        }
    }
    ifs.close();

//    LPD3DXBUFFER pID3DXBuffer; //受け取り用バッファ（マテリアル用）
    HRESULT hr;
    //Xファイルのファイルロード
    BoneAniMeshAllocHierarchy* pAllocHierarchy = NEW BoneAniMeshAllocHierarchy(); // CAllocHierarchyBaseの派生クラス
    BoneAniMeshFrame* pFrameRoot; // ワールド変換行列付きフレーム構造体
    ID3DXAnimationController* pAC; // アニメーションコントローラ
    hr = D3DXLoadMeshHierarchyFromX(
            xfilepath.c_str(),
            D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
            pCARETAKER->_pID3DDevice9,
            pAllocHierarchy,
            nullptr,
            (D3DXFRAME**)(&pFrameRoot),
            &pAC
         );
    _TRACE_("pAllocHierarchy="<<pAllocHierarchy<<" pFrameRoot="<<pFrameRoot<<" pAC="<<pAC<<" xfile_name.c_str()="<<xfilepath.c_str());
    checkDxException(hr, D3D_OK, xfilepath<<" 読み込みに失敗しました。対象="<<xfilepath);
    if (pFrameRoot == nullptr) {
        throwCriticalException(xfilepath<<" のフレーム情報が取得できません！");
    }
    //マテリアル配列を作成
    std::list<BoneAniMeshFrame*> listFrame;
    getDrawFrameList(&listFrame, pFrameRoot); //マテリアル総数を知りたいがため、フレームを廻り、リスト化
    std::list<BoneAniMeshFrame*>::iterator it = listFrame.begin();
    int model_nMaterials = 0;
    //フレームリストを廻って、マテリアル総数取得
    for (int i = 0; it != listFrame.end(); i++, ++it) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            model_nMaterials += (int)((*it)->pMeshContainer->NumMaterials);
        }
    }
    //配列数がやっと解ったので作成
    model_paMaterial = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureConnection  = NEW TextureConnection*[model_nMaterials];
    //モデル保持用マテリアル、テクスチャ作成のため、もう一度回す
    it = listFrame.begin();
    int n = 0;
    char* texture_filename;
    for (int i = 0; it != listFrame.end(); i++, ++it) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
//                (*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse
                model_paMaterial[n] = (*it)->pMeshContainer->pMaterials[j].MatD3D; //マテリアル情報コピー

                texture_filename = (*it)->pMeshContainer->pMaterials[j].pTextureFilename;
                if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                    model_papTextureConnection[n] = connectToTextureManager(texture_filename);
                } else {
                    //テクスチャ無し時は真っ白なテクスチャに置き換え
                    model_papTextureConnection[n] = connectToTextureManager(CONFIG::WHITE_TEXTURE.c_str());
                }
                n ++;
            }
        }
    }
    //境界球
    D3DXVECTOR3 vecCenter;
    FLOAT model_bounding_sphere_radius;
    D3DXFrameCalculateBoundingSphere(pFrameRoot, &vecCenter, &model_bounding_sphere_radius);
    //メッシュ、マテリアル、テクスチャの参照、マテリアル数をモデルオブジェクトに保持させる

    _pAllocHierarchy = pAllocHierarchy;
    _pFrameRoot = pFrameRoot;
    _pAniControllerBase = pAC;
    _bounding_sphere_radius = model_bounding_sphere_radius;
    _TRACE_("境界球半径="<<model_bounding_sphere_radius);
//    _advance_time_per_frame0 =  advanceTimePerFrame0; //トラック0番１ループの時間
//    _TRACE_("アニメーションセット0番_advance_time_per_frame");

//    _pID3DXAniMesh = pID3DXAniMesh;
    _paMaterial_default = model_paMaterial;
    _papTextureConnection = model_papTextureConnection;
    _num_materials = model_nMaterials;
    _anim_ticks_per_second = anim_ticks_per_second;
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXAniMeshModel::getDrawFrameList(std::list<BoneAniMeshFrame*>* pList, BoneAniMeshFrame* pFrame) {
    if (pFrame->pMeshContainer) {
        //メッシュコンテナ有り
        pList->push_back(pFrame); //リストに追加
    }
    if (pFrame->pFrameFirstChild) {
        // 子フレーム有り
        getDrawFrameList(pList, (BoneAniMeshFrame*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //兄弟フレーム有り
        getDrawFrameList(pList, (BoneAniMeshFrame*)pFrame->pFrameSibling);
    }
}


void D3DXAniMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //デバイスロスト時は解放します。
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXAniMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
//    if (_pID3DXAniMesh == nullptr) {
//        throwCriticalException("Error! _pID3DXAniMeshが オブジェクトになっていないため release できません！");
//    }
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列
//    GGAF_RELEASE(_pID3DXAniMesh);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_RELEASE(_pAniControllerBase);
    _pAllocHierarchy->DestroyFrame((D3DXFRAME*)_pFrameRoot);
    GGAF_DELETE(_pAllocHierarchy);
    //TODO:いつ消すの？
    _TRACE3_("_model_id=" << _model_id << " end");
}

D3DXAniMeshModel::~D3DXAniMeshModel() {
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}
