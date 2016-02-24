#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"

#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"
#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXAniMeshModel::GgafDxD3DXAniMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _pAH = nullptr;
    _pFR = nullptr;
    _pAcBase = nullptr;
    _num_materials = 0L;
    _anim_ticks_per_second = 4800; //restoreD3DXAniMeshModel で上書きされる場合がある。

    _obj_model |= Obj_GgafDxD3DXAniMeshModel;


    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreD3DXAniMeshModel(GgafDxD3DXAniMeshModel*)
    //で行うようにした。要参照。
}

HRESULT GgafDxD3DXAniMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxD3DXAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    HRESULT hr;
    //対象アクター
    GgafDxD3DXAniMeshActor* pTargetActor = (GgafDxD3DXAniMeshActor*)prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    GgafDxD3DXAniMeshEffect* pD3DXAniMeshEffect = (GgafDxD3DXAniMeshEffect*)(prm_pActor_target->getEffect());
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxD3DXAniMeshActor::FVF);
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }
    pTargetActor->_pPuppeteer->work(); //アニメーション反映
    std::list< D3DXFRAME_WORLD* > *pDrawList = _stackWorldMat.GetDrawList(); // 描画リストを取得
    std::list<D3DXFRAME_WORLD*>::iterator it = pDrawList->begin();
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
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
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");

    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //描画(TODO:なんか無駄なループ）
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((pEffect_active != pD3DXAniMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("GgafDxD3DXAniMeshModel::draw() ["<<i<<"],EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() End() に失敗しました。");
                if (pEffect_active->_obj_effect & Obj_GgafDxMassMeshEffect) {
                    pDevice->SetStreamSourceFreq( 0, 1 );
                    pDevice->SetStreamSourceFreq( 1, 1 );
                }
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("GgafDxD3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("GgafDxD3DXAniMeshModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->WorldTransMatrix));
        checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
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
                    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
                }
                _TRACE4_("["<<i<<"]["<<j<<"],SetMaterial");
                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() CommitChanges() に失敗しました。");
                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
                n++;
                GgafGod::_num_drawing++;
            }
        }
    }
    //前回描画モデル名反映
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pD3DXAniMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxD3DXAniMeshModel::restore() {
    _TRACE3_("GgafDxD3DXAniMeshModel::restore() " << _model_name << " start");
    //TODO:作成中？！！！！！！！！

    //【restoreD3DXAniMeshModel再構築（＝初期化）処理概要】
    //1)D3DXLoadMeshFromXを使用してXファイルを読み込む
    //2)GgafDxD3DXAniMeshModelのメンバにセット
    //Xファイルのロードして必要な内容をGgafDxD3DXAniMeshModelメンバに設定しインスタンスとして完成させたい
//    LPD3DXMESH pID3DXAniMesh; //メッシュ(ID3DXAniMeshインターフェイスへのポインタ）
    D3DMATERIAL9* model_paMaterial = nullptr; //マテリアル(D3DXMATERIAL構造体の配列の先頭要素を指すポインタ）
    GgafDxTextureConnection** model_papTextureConnection = nullptr; //テクスチャ配列(IDirect3DTexture9インターフェイスへのポインタを保持するオブジェクト）
//    DWORD _num_materials;
    std::string xfile_name = GgafDxModelManager::getMeshFileName(_model_name);
    if (xfile_name == "") {
         throwGgafCriticalException("GgafDxModelManager::restoreD3DXAniMeshModel メッシュファイル(*.x)が見つかりません。model_name="<<(_model_name));
    }
    //AnimTicksPerSecondの値を独自に取り出す
    std::ifstream ifs(xfile_name.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException(" GgafDxModelManager::restoreD3DXAniMeshModel ["<<xfile_name<<"] が開けません");
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
    GgafDxAllocHierarchyWorldFrame* pAH = NEW GgafDxAllocHierarchyWorldFrame(); // CAllocHierarchyBaseの派生クラス
    D3DXFRAME_WORLD* pFR; // ワールド変換行列付きフレーム構造体
    ID3DXAnimationController* pAC; // アニメーションコントローラ
    hr = D3DXLoadMeshHierarchyFromX(
            xfile_name.c_str(),
            D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
            GgafDxGod::_pID3DDevice9,
            pAH,
            nullptr,
            (D3DXFRAME**)(&pFR),
            &pAC
         );
    _TRACE_("pAH="<<pAH<<" pFR="<<pFR<<" pAC="<<pAC<<" xfile_name.c_str()="<<xfile_name.c_str());
    checkDxException(hr, D3D_OK, "GgafDxModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" 読み込みに失敗しました。対象="<<xfile_name);
    if (pFR == nullptr) {
        throwGgafCriticalException("GgafDxModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" のフレーム情報が取得できません！");
    }
    //マテリアル配列を作成
    std::list<D3DXFRAME_WORLD*> listFrame;
    getDrawFrameList(&listFrame, pFR); //マテリアル総数を知りたいがため、フレームを廻り、リスト化
    std::list<D3DXFRAME_WORLD*>::iterator it = listFrame.begin();
    int model_nMaterials = 0;
    //フレームリストを廻って、マテリアル総数取得
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            model_nMaterials += (int)((*it)->pMeshContainer->NumMaterials);
        }
    }
    //配列数がやっと解ったので作成
    model_paMaterial = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureConnection  = NEW GgafDxTextureConnection*[model_nMaterials];
    //モデル保持用マテリアル、テクスチャ作成のため、もう一度回す
    it = listFrame.begin();
    int n = 0;
    char* texture_filename;
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
//                (*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse
                model_paMaterial[n] = (*it)->pMeshContainer->pMaterials[j].MatD3D; //マテリアル情報コピー

                texture_filename = (*it)->pMeshContainer->pMaterials[j].pTextureFilename;
                if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                    model_papTextureConnection[n] = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(texture_filename, this));
                } else {
                    //テクスチャ無し時は真っ白なテクスチャに置き換え
                    model_papTextureConnection[n] = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(PROPERTY::WHITE_TEXTURE.c_str(), this));
                }
                n ++;
            }
        }
    }
    //境界球
    D3DXVECTOR3 vecCenter;
    FLOAT model_bounding_sphere_radius;
    D3DXFrameCalculateBoundingSphere(pFR, &vecCenter, &model_bounding_sphere_radius);
    //メッシュ、マテリアル、テクスチャの参照、マテリアル数をモデルオブジェクトに保持させる

    _pAH = pAH;
    _pFR = pFR;
    _pAcBase = pAC;
    _bounding_sphere_radius = model_bounding_sphere_radius;
    _TRACE_("境界球半径="<<model_bounding_sphere_radius);
//    _advance_time_per_frame0 =  advanceTimePerFrame0; //トラック0番１ループの時間
//    _TRACE_("アニメーションセット0番_advance_time_per_frame");

//    _pID3DXAniMesh = pID3DXAniMesh;
    _paMaterial_default = model_paMaterial;
    _papTextureConnection = model_papTextureConnection;
    _num_materials = model_nMaterials;
    _anim_ticks_per_second = anim_ticks_per_second;
    _TRACE3_("GgafDxD3DXAniMeshModel::restore() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::getDrawFrameList(std::list<D3DXFRAME_WORLD*>* pList, D3DXFRAME_WORLD* pFrame) {
    if (pFrame->pMeshContainer) {
        //メッシュコンテナ有り
        pList->push_back(pFrame); //リストに追加
    }
    if (pFrame->pFrameFirstChild) {
        // 子フレーム有り
        getDrawFrameList(pList, (D3DXFRAME_WORLD*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //兄弟フレーム有り
        getDrawFrameList(pList, (D3DXFRAME_WORLD*)pFrame->pFrameSibling);
    }
}


void GgafDxD3DXAniMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " start");
    //デバイスロスト時は解放します。
    release();
    _TRACE3_("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::release() {
    _TRACE3_("GgafDxD3DXAniMeshModel::release() " << _model_name << " start");
//    if (_pID3DXAniMesh == nullptr) {
//        throwGgafCriticalException("[GgafDxD3DXAniMeshModel::release] Error! _pID3DXAniMeshが オブジェクトになっていないため release できません！");
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
    GGAF_DELETEARR(_pa_texture_filenames);
    GGAF_RELEASE(_pAcBase);
    GGAF_DELETE(_pAH);
    //TODO:いつ消すの？
    _TRACE3_("GgafDxD3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDxD3DXAniMeshModel::~GgafDxD3DXAniMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}
