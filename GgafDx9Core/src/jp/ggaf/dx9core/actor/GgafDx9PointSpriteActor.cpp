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
    _class_name = "GgafDx9PointSpriteActor";
    _pPointSpriteModel = (GgafDx9PointSpriteModel*)_pGgafDx9Model;
    _pPointSpriteEffect = (GgafDx9PointSpriteEffect*)_pGgafDx9Effect;
    _pFunc_calcWorldMatrix = GgafDx9Util::setWorldMatrix_ScRxRzRyMv;
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _TRACE_("_pPointSpriteModel->_texture_split_rowcol ="<<_pPointSpriteModel->_texture_split_rowcol);
    _TRACE_("_pPointSpriteModel->_fTexSize = "<<_pPointSpriteModel->_fTexSize);
    _TRACE_("_pPointSpriteModel->_fTexSize / _pPointSpriteModel->_texture_split_rowcol = "<<(_pPointSpriteModel->_fTexSize / _pPointSpriteModel->_texture_split_rowcol));
    _pUvFlipper->setTextureUvRotation(_pPointSpriteModel->_texture_split_rowcol,
                                      1.0 / _pPointSpriteModel->_texture_split_rowcol,
                                      1.0 / _pPointSpriteModel->_texture_split_rowcol );
    _pUvFlipper->forcePtnNoRange(0, _pPointSpriteModel->_texture_split_rowcol * _pPointSpriteModel->_texture_split_rowcol - 1);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    _pFunc_calcWorldMatrix = GgafDx9Util::setWorldMatrix_ScRxRzRyMv;

}


void GgafDx9PointSpriteActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9PointSpriteActorはメッシュαも設定（シェーダーで参照するため）
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}


void GgafDx9PointSpriteActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    (*_pFunc_calcWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_hMatWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_hDist_VpPlnFront, -_fDist_VpPlnFront);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(g_hDist_VpPlnFront) に失敗しました。");
//_TRACE_(getName() << "_fDist_VpPlnFront = "<<(-(pCAM->_fDist_VpPlnFront)));
    float u = 0;
    float v = 0;
    _pUvFlipper->getUV(u, v);
    _TRACE_("U="<<u<<" V="<<v);
    hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_hOffsetU, u);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_hOffsetV, v);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetMatrix(_h_offset_v) に失敗しました。");
    //ポイントスプライトON
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    //ポイントスケールON
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
    _pPointSpriteModel->draw(this);
    //ポイントスプライトOFF
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
    //ポイントスケールOFF
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
}

GgafDx9PointSpriteActor::~GgafDx9PointSpriteActor() {
}
