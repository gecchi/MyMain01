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
//    //VIEW変換行列
//    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDxGod::_matView );
//    checkDxException(hr, D3D_OK, "SetMatrix(g_matView) に失敗しました。");
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_dist_CamZ_default", -(pCam->getZOrigin()));
    checkDxException(hr, D3D_OK, "SetFloat(g_dist_CamZ_default) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_zn", pCam->getZNear());
    checkDxException(hr, D3D_OK, "SetFloat(g_zn) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "SetFloat(g_zf) に失敗しました。");

    //シェーダーハンドル
    _h_matView  = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
//    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
//    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
//    _h_alpha    = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
//    _h_dist_VpInfrontPlane = _pID3DXEffect->GetParameterByName( nullptr, "g_dist_VpInfrontPlane" );
    _hTexSize = _pID3DXEffect->GetParameterByName( nullptr, "g_TexSize" );
    _hTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_TextureSplitRowcol" );
    _hUvFlipPtnNo = _pID3DXEffect->GetParameterByName( nullptr, "g_UvFlipPtnNo" );
}

void GgafDxMassPointSpriteEffect::setParamPerFrame() {
    GgafDxCamera* const pCam = P_GOD->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

GgafDxMassPointSpriteEffect::~GgafDxMassPointSpriteEffect() {
}

