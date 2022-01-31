#include "jp/ggaf/dx/effect/FramedSpriteEffect.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

FramedSpriteEffect::FramedSpriteEffect(const char* prm_effect_name) : Effect(prm_effect_name) {
    _obj_effect |= Obj_GgafDx_FramedSpriteEffect;
    Camera* const pCam = pGOD->getSpacetime()->getCamera();
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "SetFloat(g_zf) に失敗しました。");

    //シェーダーハンドル
    _h_matView  = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
    _h_far_rate = _pID3DXEffect->GetParameterByName( nullptr, "g_far_rate" );

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

    _ah_offset_x[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x001" );
    _ah_offset_x[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x002" );
    _ah_offset_x[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x003" );
    _ah_offset_x[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x004" );
    _ah_offset_x[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x005" );
    _ah_offset_x[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x006" );
    _ah_offset_x[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x007" );
    _ah_offset_x[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x008" );
    _ah_offset_x[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_x009" );

    _ah_offset_y[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y001" );
    _ah_offset_y[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y002" );
    _ah_offset_y[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y003" );
    _ah_offset_y[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y004" );
    _ah_offset_y[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y005" );
    _ah_offset_y[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y006" );
    _ah_offset_y[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y007" );
    _ah_offset_y[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y008" );
    _ah_offset_y[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_y009" );


    _h_center_width = _pID3DXEffect->GetParameterByName( nullptr, "g_center_width" );
    _h_center_height = _pID3DXEffect->GetParameterByName( nullptr, "g_center_height" );

    _h_frame_width = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_width" );
    _h_frame_height = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_height" );

    _h_local_offset_x = _pID3DXEffect->GetParameterByName( nullptr, "g_local_offset_x" );
    _h_local_offset_y = _pID3DXEffect->GetParameterByName( nullptr, "g_local_offset_y" );

    _h_x = _pID3DXEffect->GetParameterByName( nullptr, "g_x" );
    _h_y = _pID3DXEffect->GetParameterByName( nullptr, "g_y" );
    _h_z = _pID3DXEffect->GetParameterByName( nullptr, "g_z" );
    _h_rz = _pID3DXEffect->GetParameterByName( nullptr, "g_rz" );
    _h_depth_z = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z" );

    _h_tex_blink_power     = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
    _h_colMaterialDiffuse  = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );

    _h_frame_width_rate = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_width_rate" );
    _h_center_width_rate = _pID3DXEffect->GetParameterByName( nullptr, "g_center_width_rate" );

    _h_frame_height_rate = _pID3DXEffect->GetParameterByName( nullptr, "g_frame_height_rate" );
    _h_center_height_rate = _pID3DXEffect->GetParameterByName( nullptr, "g_center_height_rate" );
}

void FramedSpriteEffect::setParamPerFrame() {
    Camera* const pCam = pGOD->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

FramedSpriteEffect::~FramedSpriteEffect() {
}

