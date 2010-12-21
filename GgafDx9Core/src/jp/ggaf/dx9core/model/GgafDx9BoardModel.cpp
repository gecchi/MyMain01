#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9BoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

GgafDx9BoardModel::GgafDx9BoardModel(char* prm_model_name) :
    GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9BoardModel::GgafDx9BoardModel(" << _model_name << ")");
    _fSize_BoardModelWidthPx = 32.0f;
    _fSize_BoardModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_max = 1;
    _pIDirect3DVertexBuffer9 = NULL;
    _paRectUV = NULL;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreBoardModel(GgafDx9BoardModel*)
    //で行っている。
}

HRESULT GgafDx9BoardModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9BoardModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    //TODO クリアするかどうか
    //GgafDx9God::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0x000000, 1.0, 0);
    //↑TODO なぜここでクリアしようと考えが湧いたのかわからなくなった。

    //対象Actor
    GgafDx9BoardActor* pTargetActor = (GgafDx9BoardActor*)prm_pActor_Target;
    //対象BoardActorのエフェクトラッパ
    GgafDx9BoardEffect* pBoardEffect = (GgafDx9BoardEffect*)prm_pActor_Target->_pGgafDx9Effect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pBoardEffect->_pID3DXEffect;
    //今回描画のUV
    GgafDx9RectUV* pRectUV_Active = _paRectUV + (pTargetActor->_pUvFlipper->_pattno_uvflip_now);

    static HRESULT hr;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9BoardModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->refer()->_pIDirect3DBaseTexture9);
        //GgafDx9God::_pID3DDevice9->SetTexture(1, _papTextureCon[0]->refer()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_power, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_threshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hOffsetU, pRectUV_Active->_aUV[0].tu);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hOffsetV, pRectUV_Active->_aUV[0].tv);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) に失敗しました。");


    if (GgafDx9EffectManager::_pEffect_Active != pBoardEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) {
        if (GgafDx9EffectManager::_pEffect_Active != NULL) {
            TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() EndPass() に失敗しました。");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
            if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDx9EffectManager::_pEffect_Active->_begin = false;
            }
#endif

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDx9BoardModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pBoardEffect->_begin == true) {
            throwGgafCriticalException("End していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() CommitChanges() に失敗しました。");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name<<"("<<pBoardEffect<<")");
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    //前回描画モデル保持
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pBoardEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    //前回描画UV座標（へのポインタ）を保存
    GgafGod::_num_actor_drawing++;
    return D3D_OK;

}

void GgafDx9BoardModel::restore() {
    TRACE3("GgafDx9BoardModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreBoardModel(this);
    TRACE3("GgafDx9BoardModel::restore() " << _model_name << " end");
}

void GgafDx9BoardModel::release() {
    TRACE3("GgafDx9BoardModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    TRACE3("GgafDx9BoardModel::release() " << _model_name << " end");
}

void GgafDx9BoardModel::onDeviceLost() {
    TRACE3("GgafDx9BoardModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9BoardModel::onDeviceLost() " << _model_name << " end");
}

GgafDx9BoardModel::~GgafDx9BoardModel() {
    //release();
    //はGgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) で呼び出される
}
