#include "jp/ggaf/dx/effect/PointSpriteEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

PointSpriteEffect::PointSpriteEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_PointSpriteEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;

    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    hr = _pID3DXEffect->SetFloat("g_dist_CamZ_default", -(pCam->getZOrigin()));
    checkDxException(hr, D3D_OK, "SetFloat(g_dist_CamZ_default) に失敗しました。");

    //シェーダーハンドル
    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _hTexSize = _pID3DXEffect->GetParameterByName( nullptr, "g_TexSize" );
    _hTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_TextureSplitRowcol" );
    _hInvTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_InvTextureSplitRowcol" );
    _hUvFlipPtnNo = _pID3DXEffect->GetParameterByName( nullptr, "g_UvFlipPtnNo" );
}

PointSpriteEffect::~PointSpriteEffect() {
}

