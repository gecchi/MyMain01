#include "stdafx.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxPointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDxPointSpriteModel::GgafDxPointSpriteModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxPointSpriteModel::GgafDxPointSpriteModel(" << _model_name << ")");
    _pIDirect3DVertexBuffer9 = nullptr;
    _paVtxBuffer_org = nullptr;
    _vertices_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _fSquareSize = 0.0f;
    _fTexSize = 0.0f;
    _texture_split_rowcol = 1;
    _obj_model |= Obj_GgafDxPointSpriteModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restorePointSpriteModel(GgafDxPointSpriteModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxPointSpriteModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    TRACE4("GgafDxPointSpriteModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //対象Actor
    GgafDxPointSpriteActor* pTargetActor = (GgafDxPointSpriteActor*)prm_pActor_Target;
    //対象PointSpriteActorのエフェクトラッパ
    GgafDxPointSpriteEffect* pPointSpriteEffect = (GgafDxPointSpriteEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //今回描画のUV
    HRESULT hr;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxPointSpriteModel::FVF);
        pDevice->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _fTexSize);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetInt(_hTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetValue(pPointSpriteEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
    }
    if (GgafDxEffectManager::_pEffect_Active != pPointSpriteEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDxEffectManager::_pEffect_Active) {
            TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() EndPass() に失敗しました。");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() End() に失敗しました。");
#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_Active->_begin = false;
            }
#endif
        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxPointSpriteActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name<<"("<<pPointSpriteEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pPointSpriteEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteModel::draw() CommitChanges() に失敗しました。");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pPointSpriteEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxPointSpriteModel::restore() {
    TRACE3("GgafDxPointSpriteModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restorePointSpriteModel(this);
    TRACE3("GgafDxPointSpriteModel::restore() " << _model_name << " end");
}

void GgafDxPointSpriteModel::onDeviceLost() {
    TRACE3("GgafDxPointSpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxPointSpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxPointSpriteModel::release() {
    TRACE3("GgafDxPointSpriteModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pIDirect3DVertexBuffer9);
    GGAF_DELETEARR(_paVtxBuffer_org);
    if (_papTextureConnection) {
        if (_papTextureConnection[0]) {
            _papTextureConnection[0]->close();
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    TRACE3("GgafDxPointSpriteModel::release() " << _model_name << " end");
}

GgafDxPointSpriteModel::~GgafDxPointSpriteModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

