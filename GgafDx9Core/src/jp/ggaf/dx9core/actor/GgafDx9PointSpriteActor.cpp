#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9PointSpriteActor::GgafDx9PointSpriteActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique,
                                   GgafDx9Checker* prm_pChecker) :

                                       GgafDx9DrawableActor(prm_name,
                                                            prm_model_id,
                                                            "P",
                                                            prm_effect_id,
                                                            "P",
                                                            prm_technique,
                                                            prm_pChecker) {
    _obj_class |= Obj_GgafDx9PointSpriteActor;
    _class_name = "GgafDx9PointSpriteActor";
    _pPointSpriteModel = (GgafDx9PointSpriteModel*)_pGgafDx9Model;
    _pPointSpriteEffect = (GgafDx9PointSpriteEffect*)_pGgafDx9Effect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
//    _pUvFlipper->setTextureUvRotation(_pPointSpriteModel->_texture_split_rowcol,
//                                      1.0 / _pPointSpriteModel->_texture_split_rowcol,
//                                      1.0 / _pPointSpriteModel->_texture_split_rowcol );
    _pUvFlipper->forcePtnNoRange(0, _pPointSpriteModel->_texture_split_rowcol * _pPointSpriteModel->_texture_split_rowcol - 1);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
}


void GgafDx9PointSpriteActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDx9PointSpriteActorはメッシュαも設定（シェーダーで参照するため）
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

void GgafDx9PointSpriteActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDx9PointSpriteActorはメッシュαも設定（シェーダーで参照するため）
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

void GgafDx9PointSpriteActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_h_matView, &P_CAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_h_dist_VpFrontPlane, -_fDist_VpPlnFront);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(g_h_dist_VpFrontPlane) に失敗しました。");
    hr = pID3DXEffect->SetInt(_pPointSpriteEffect->_hUvFlipPtnNo, _pUvFlipper->_pattno_uvflip_now);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetInt(_hUvFlipPtnNo) に失敗しました。");
    // Zバッファを無効に
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Zバッファ書き込み不可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    //ポイントスプライトON
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    //ポイントスケールON
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
    _pPointSpriteModel->draw(this);
    //ポイントスプライトOFF
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
    //ポイントスケールOFF
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
    // Zバッファを有効に
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファ書き込み可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

GgafDx9PointSpriteActor::~GgafDx9PointSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
