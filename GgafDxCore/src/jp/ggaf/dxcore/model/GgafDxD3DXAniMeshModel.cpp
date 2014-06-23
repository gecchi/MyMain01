#include "stdafx.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXAniMeshModel::GgafDxD3DXAniMeshModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
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

HRESULT GgafDxD3DXAniMeshModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxD3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    HRESULT hr;
    //対象アクター
    GgafDxD3DXAniMeshActor* pTargetActor = (GgafDxD3DXAniMeshActor*)prm_pActor_Target;
    //対象MeshActorのエフェクトラッパ
    GgafDxD3DXAniMeshEffect* pD3DXAniMeshEffect = (GgafDxD3DXAniMeshEffect*)(prm_pActor_Target->getEffect());
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

    int n = 0;
    //マテリアル・テクスチャの一発目をセット、
    LPDIRECT3DBASETEXTURE9 pTex = nullptr;
    LPDIRECT3DBASETEXTURE9 pLastTex = nullptr;
    if (_papTextureConnection[n]) {
        pLastTex = _papTextureConnection[n]->peek()->_pIDirect3DBaseTexture9;
        GgafDxGod::_pID3DDevice9->SetTexture(0, pLastTex);
    } else {
        //無ければテクスチャ無し
        GgafDxGod::_pID3DDevice9->SetTexture(0, nullptr);
    }
    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");

    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //描画
        if ((GgafDxEffectManager::_pEffect_Active != pD3DXAniMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDxEffectManager::_pEffect_Active) {
                TRACE4("["<<i<<"],EndPass: /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name);
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() EndPass() に失敗しました。");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->WorldTransMatrix));
        checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        if ((*it)->pMeshContainer == nullptr) {
            TRACE4("["<<i<<"]×SetMatrix FrameName="<<((*it)->Name)<<" 飛ばし！");
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
                if (n > 0) {
                    pTex = _papTextureConnection[n]->peek()->_pIDirect3DBaseTexture9;
                    if (pTex != pLastTex) {
                        //テクスチャが異なれば設定
                        GgafDxGod::_pID3DDevice9->SetTexture(0, pTex);
                        pLastTex = pTex;
                    }
                    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
                    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
                }
                TRACE4("["<<i<<"]["<<j<<"],SetMaterial");
                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() CommitChanges() に失敗しました。");
                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
                n++;
                GgafGod::_num_actor_drawing++;
            }
        }
    }
    //前回描画モデル名反映
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pD3DXAniMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxD3DXAniMeshModel::restore() {
    TRACE3("GgafDxD3DXAniMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreD3DXAniMeshModel(this);
    TRACE3("GgafDxD3DXAniMeshModel::restore() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::onDeviceLost() {
    TRACE3("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " start");
    //デバイスロスト時は解放します。
    release();
    TRACE3("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::release() {
    TRACE3("GgafDxD3DXAniMeshModel::release() " << _model_name << " start");
//    if (_pID3DXAniMesh == nullptr) {
//        throwGgafCriticalException("[GgafDxD3DXAniMeshModel::release] Error! _pID3DXAniMeshが オブジェクトになっていないため release できません！");
//    }
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                TRACE3("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列
//    GGAF_RELEASE(_pID3DXAniMesh);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_RELEASE(_pAcBase);
    GGAF_DELETE(_pAH);
    //TODO:いつ消すの？
    TRACE3("GgafDxD3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDxD3DXAniMeshModel::~GgafDxD3DXAniMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}
