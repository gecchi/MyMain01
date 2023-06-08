#include "jp/ggaf/dx/effect/PointSpriteSetEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

PointSpriteSetEffect::PointSpriteSetEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_PointSpriteSetEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;

    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    hr = _pID3DXEffect->SetFloat("g_dist_CamZ_default", -(pCam->getZOrigin()));
    checkDxException(hr, D3D_OK, "SetFloat(g_dist_CamZ_default) に失敗しました。");
    //シェーダーハンドル
    _ah_matWorld[0]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld001" );
    _ah_matWorld[1]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld002" );
    _ah_matWorld[2]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld003" );
    _ah_matWorld[3]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld004" );
    _ah_matWorld[4]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld005" );
    _ah_matWorld[5]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld006" );
    _ah_matWorld[6]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld007" );
    _ah_matWorld[7]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld008" );
    _ah_matWorld[8]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld009" );
    _ah_matWorld[9]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld010" );
    _ah_matWorld[10]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld011" );
    _ah_matWorld[11]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld012" );
    _ah_matWorld[12]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld013" );
    _ah_matWorld[13]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld014" );
    _ah_matWorld[14]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld015" );
    _ah_matWorld[15]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld016" );
    _ah_matWorld[16]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld017" );
    _ah_matWorld[17]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld018" );
    _ah_matWorld[18]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld019" );
    _ah_matWorld[19]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld020" );
    _ah_matWorld[20]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld021" );
    _ah_matWorld[21]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld022" );
    _ah_matWorld[22]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld023" );
    _ah_matWorld[23]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld024" );
    _ah_matWorld[24]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld025" );
    _ah_matWorld[25]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld026" );
    _ah_matWorld[26]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld027" );
    _ah_matWorld[27]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld028" );
    _ah_matWorld[28]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld029" );
    _ah_matWorld[29]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld030" );
    _ah_matWorld[30]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld031" );
    _ah_matWorld[31]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld032" );


    _ah_colMaterialDiffuse[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse001" );
    _ah_colMaterialDiffuse[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse002" );
    _ah_colMaterialDiffuse[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse003" );
    _ah_colMaterialDiffuse[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse004" );
    _ah_colMaterialDiffuse[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse005" );
    _ah_colMaterialDiffuse[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse006" );
    _ah_colMaterialDiffuse[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse007" );
    _ah_colMaterialDiffuse[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse008" );
    _ah_colMaterialDiffuse[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse009" );
    _ah_colMaterialDiffuse[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse010" );
    _ah_colMaterialDiffuse[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse011" );
    _ah_colMaterialDiffuse[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse012" );
    _ah_colMaterialDiffuse[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse013" );
    _ah_colMaterialDiffuse[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse014" );
    _ah_colMaterialDiffuse[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse015" );
    _ah_colMaterialDiffuse[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse016" );
    _ah_colMaterialDiffuse[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse017" );
    _ah_colMaterialDiffuse[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse018" );
    _ah_colMaterialDiffuse[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse019" );
    _ah_colMaterialDiffuse[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse020" );
    _ah_colMaterialDiffuse[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse021" );
    _ah_colMaterialDiffuse[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse022" );
    _ah_colMaterialDiffuse[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse023" );
    _ah_colMaterialDiffuse[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse024" );
    _ah_colMaterialDiffuse[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse025" );
    _ah_colMaterialDiffuse[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse026" );
    _ah_colMaterialDiffuse[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse027" );
    _ah_colMaterialDiffuse[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse028" );
    _ah_colMaterialDiffuse[28] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse029" );
    _ah_colMaterialDiffuse[29] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse030" );
    _ah_colMaterialDiffuse[30] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse031" );
    _ah_colMaterialDiffuse[31] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse032" );
    _hTexSize = _pID3DXEffect->GetParameterByName( nullptr, "g_TexSize" );
    _hTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_TextureSplitRowcol" );
    _hInvTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_InvTextureSplitRowcol" );
    _hUvFlipPtnNo = _pID3DXEffect->GetParameterByName( nullptr, "g_UvFlipPtnNo" );
}

PointSpriteSetEffect::~PointSpriteSetEffect() {
}

