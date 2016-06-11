#include "jp/ggaf/dxcore/effect/GgafDxMassPointSpriteEffect.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassPointSpriteEffect::GgafDxMassPointSpriteEffect(const char* prm_effect_name) : GgafDxMassEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDxMassPointSpriteEffect;
    GgafDxCamera* const pCam = P_GOD->getSpacetime()->getCamera();
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_dist_CamZ_default", -(pCam->getZOrigin()));
    checkDxException(hr, D3D_OK, "SetFloat(g_dist_CamZ_default) に失敗しました。");
//    hr = _pID3DXEffect->SetFloat("g_zn", pCam->getZNear());
//    checkDxException(hr, D3D_OK, "SetFloat(g_zn) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "SetFloat(g_zf) に失敗しました。");

    //シェーダーハンドル
    _h_matView  = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _hTexSize = _pID3DXEffect->GetParameterByName( nullptr, "g_TexSize" );
    _hTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_TextureSplitRowcol" );
}

void GgafDxMassPointSpriteEffect::setParamPerFrame() {
    GgafDxCamera* const pCam = P_GOD->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

GgafDxMassPointSpriteEffect::~GgafDxMassPointSpriteEffect() {
}

