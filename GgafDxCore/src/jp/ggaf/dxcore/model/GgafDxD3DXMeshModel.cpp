#include "jp/ggaf/dxcore/model/GgafDxD3DXMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/actor/GgafDxD3DXMeshActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXMeshModel::GgafDxD3DXMeshModel(const char* prm_model_name, DWORD prm_dwOptions) : GgafDxModel(prm_model_name) {
    _pID3DXMesh = nullptr;
    _num_materials = 0L;
    _dwOptions = prm_dwOptions;
    _obj_model |= Obj_GgafDxD3DXMeshModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreD3DXMeshModel(GgafDxD3DXMeshModel*)
    //で行うようにした。要参照。
}

HRESULT GgafDxD3DXMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxD3DXMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    const GgafDxD3DXMeshActor* const pTargetActor = (GgafDxD3DXMeshActor*)prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    GgafDxMeshEffect* const pMeshEffect = (GgafDxMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMeshEffect->_pID3DXEffect;

    pDevice->SetFVF(GgafDxD3DXMeshActor::FVF);
    HRESULT hr;

    for (DWORD i = 0; i < _num_materials; i++) {
        if (GgafDxModelManager::_pModelLastDraw != this || _num_materials != 1) {
            if (_papTextureConnection[i]) {
                if (i == 0) {
                    //マテリアル0番は、特別に規定のテクスチャを設定する仕様
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[i]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("GgafDxD3DXMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
            //マテリアルのセット
            hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[i].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
        }

        //描画
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((pEffect_active != pMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() End() に失敗しました。");
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
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxD3DXMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() CommitChanges() に失敗しました。");
        }
        _TRACE4_("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        hr = _pID3DXMesh->DrawSubset(i);  //なんて便利なメソッド。
        GgafGod::_num_drawing++;
    }
    //前回描画モデル名反映
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}

//シェーダー実装前
//        if (pTargetActor->_sx == LEN_UNIT &&
//            pTargetActor->_sy == LEN_UNIT &&
//            pTargetActor->_sz == LEN_UNIT)
//        {
//            hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
//        } else {
//            //拡大縮小がなされているため、カメラ空間にトランスフォームされた後で頂点法線の正規化するように設定（負荷高）
//            pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
//            pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


void GgafDxD3DXMeshModel::restore() {
    _TRACE3_("GgafDxD3DXMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreD3DXMeshModel(this);
    _TRACE3_("GgafDxD3DXMeshModel::restore() " << _model_name << " end");
}

void GgafDxD3DXMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxD3DXMeshModel::onDeviceLost() " << _model_name << " start");
    //デバイスロスト時は解放します。
    release();
    _TRACE3_("GgafDxD3DXMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxD3DXMeshModel::release() {
    _TRACE3_("GgafDxD3DXMeshModel::release() " << _model_name << " start");
    if (_pID3DXMesh == nullptr) {
        _TRACE_("＜警告＞ [GgafDxD3DXMeshModel::release()]  "<<_model_name<<" の _pID3DXMeshが オブジェクトになっていないため release できません！");
    }
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
    GGAF_RELEASE(_pID3DXMesh);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);

    _TRACE3_("GgafDxD3DXMeshModel::release() " << _model_name << " end");
}

GgafDxD3DXMeshModel::~GgafDxD3DXMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}
