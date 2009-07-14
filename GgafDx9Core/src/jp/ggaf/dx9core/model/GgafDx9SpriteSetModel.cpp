#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9SpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDx9SpriteSetModel::GgafDx9SpriteSetModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9SpriteSetModel::GgafDx9SpriteSetModel(" << _model_name << ")");

    _fSize_SpriteSetModelWidthPx = 32.0f;
    _fSize_SpriteSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_ani_Max = 0;
    _pIDirect3DVertexBuffer9 = NULL;
    _paRectUV = NULL;
    _pRectUV_drawlast = NULL;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreSpriteSetModel(GgafDx9SpriteSetModel*)
    //で行っている。
}

//描画
HRESULT GgafDx9SpriteSetModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE4("GgafDx9SpriteSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    //対象Actor
    static GgafDx9SpriteSetActor* pTargetActor;
    pTargetActor = (GgafDx9SpriteSetActor*)prm_pActor_Target;
    //対象SpriteSetActorのエフェクトラッパ
    static GgafDx9SpriteSetEffect* pSpriteSetEffect;
    pSpriteSetEffect = pTargetActor->_pSpriteSetEffect;
    //対象エフェクト
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;

    //今回描画のUV
    static GgafDx9RectUV* pRectUV_Active;
    pRectUV_Active = _paRectUV + (pTargetActor->_pattno_ani_now);

    static HRESULT hr;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertec_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9SpriteSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->view());
    }
    hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_hOffsetU, pRectUV_Active->_aUV[0].tu);
    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetModel::draw() SetFloat(_hOffsetU) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_hOffsetV, pRectUV_Active->_aUV[0].tv);
    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetModel::draw() SetFloat(_hOffsetV) に失敗しました。");

    if (GgafDx9EffectManager::_pEffect_Active != pSpriteSetEffect)  {
        if (GgafDx9EffectManager::_pEffect_Active != NULL) {
            TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() EndPass() に失敗しました。");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
            mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() End() に失敗しました。");
        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        mightDx9Exception(hr, S_OK, "GgafDx9SpriteSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");
        TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::draw() BeginPass(0) に失敗しました。");
    } else {
        hr = pID3DXEffect->CommitChanges();
        mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetModel::draw() CommitChanges() に失敗しました。");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    //前回描画モデル保持
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pSpriteSetEffect;
    //前回描画UV座標（へのポインタ）を保存
    _pRectUV_drawlast = pRectUV_Active;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9SpriteSetModel::restore() {
    TRACE3("GgafDx9SpriteSetModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreSpriteSetModel(this);
    TRACE3("GgafDx9SpriteSetModel::restore() " << _model_name << " end");
}

void GgafDx9SpriteSetModel::onDeviceLost() {
    TRACE3("GgafDx9SpriteSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9SpriteSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9SpriteSetModel::release() {
    TRACE3("GgafDx9SpriteSetModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    _papTextureCon[0]->close();
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    TRACE3("GgafDx9SpriteSetModel::release() " << _model_name << " end");
}

GgafDx9SpriteSetModel::~GgafDx9SpriteSetModel() {
    TRACE3("GgafDx9SpriteSetModel::~GgafDx9SpriteSetModel() " << _model_name << " start");
    release();
}

