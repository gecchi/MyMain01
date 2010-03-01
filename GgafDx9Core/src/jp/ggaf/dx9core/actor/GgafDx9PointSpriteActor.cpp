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
