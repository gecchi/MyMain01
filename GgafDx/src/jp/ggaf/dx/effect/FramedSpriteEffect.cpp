#include "jp/ggaf/dx/effect/FramedSpriteEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

FramedSpriteEffect::FramedSpriteEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_FramedSpriteEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;

    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) に失敗しました。");

    //シェーダーハンドル
    _h_matWorldRotMv = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorldRotMv" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_alpha = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha" );

    _ah_offset_u[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u001" );
    _ah_offset_u[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u002" );
    _ah_offset_u[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u003" );
    _ah_offset_u[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u004" );
    _ah_offset_u[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u005" );
    _ah_offset_u[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u006" );
    _ah_offset_u[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u007" );
    _ah_offset_u[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u008" );
    _ah_offset_u[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u009" );

    _ah_offset_v[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v001" );
    _ah_offset_v[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v002" );
    _ah_offset_v[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v003" );
    _ah_offset_v[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v004" );
    _ah_offset_v[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v005" );
    _ah_offset_v[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v006" );
    _ah_offset_v[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v007" );
    _ah_offset_v[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v008" );
    _ah_offset_v[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v009" );

    _h_center_width = _pID3DXEffect->GetParameterByName( nullptr, "g_center_width" );
    _h_center_height = _pID3DXEffect->GetParameterByName( nullptr, "g_center_height" );

    _h_frame_width = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_width" );
    _h_frame_height = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_height" );

    _h_local_offset_x = _pID3DXEffect->GetParameterByName( nullptr, "g_local_offset_x" );
    _h_local_offset_y = _pID3DXEffect->GetParameterByName( nullptr, "g_local_offset_y" );

    _h_depth_z = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z" );

    _h_colMaterialDiffuse  = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );

    _h_frame_sx = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_sx" );
    _h_center_sx = _pID3DXEffect->GetParameterByName( nullptr, "g_center_sx" );

    _h_frame_sy = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_sy" );
    _h_center_sy = _pID3DXEffect->GetParameterByName( nullptr, "g_center_sy" );

}

FramedSpriteEffect::~FramedSpriteEffect() {
}

