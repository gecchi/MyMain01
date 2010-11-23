#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9PointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDx9PointSpriteModel::GgafDx9PointSpriteModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9PointSpriteModel::GgafDx9PointSpriteModel(" << _model_name << ")");
    _pIDirect3DVertexBuffer9 = NULL;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restorePointSpriteModel(GgafDx9PointSpriteModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDx9PointSpriteModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9PointSpriteModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //対象Actor
    static GgafDx9PointSpriteActor* pTargetActor;
    pTargetActor = (GgafDx9PointSpriteActor*)prm_pActor_Target;
    //対象PointSpriteActorのエフェクトラッパ
    static GgafDx9PointSpriteEffect* pPointSpriteEffect;
    pPointSpriteEffect = pTargetActor->_pPointSpriteEffect;
    //対象エフェクト
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //今回描画のUV
    static HRESULT hr;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PointSpriteModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->refer()->_pIDirect3DTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_power, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_threshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _fTexSize);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() SetInt(_hTextureSplitRowcol) に失敗しました。");
    }


    if (GgafDx9EffectManager::_pEffect_Active != pPointSpriteEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDx9EffectManager::_pEffect_Active != NULL) {
            TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() EndPass() に失敗しました。");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() End() に失敗しました。");

            ////
            if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDx9EffectManager::_pEffect_Active->_begin = false;
            }
            ////

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDx9PointSpriteActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::draw() BeginPass(0) に失敗しました。");

        ////
        if (pPointSpriteEffect->_begin == true) {
            throwGgafCriticalException("End していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
        ////

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDx9PointSpriteModel::draw() CommitChanges() に失敗しました。");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);

    //前回描画モデル保持
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pPointSpriteEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    //前回描画UV座標（へのポインタ）を保存
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9PointSpriteModel::restore() {
    TRACE3("GgafDx9PointSpriteModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restorePointSpriteModel(this);
    TRACE3("GgafDx9PointSpriteModel::restore() " << _model_name << " end");
}

void GgafDx9PointSpriteModel::onDeviceLost() {
    TRACE3("GgafDx9PointSpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9PointSpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9PointSpriteModel::release() {
    TRACE3("GgafDx9PointSpriteModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    TRACE3("GgafDx9PointSpriteModel::release() " << _model_name << " end");
}

GgafDx9PointSpriteModel::~GgafDx9PointSpriteModel() {
    //release();
    //はGgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) で呼び出される
}

