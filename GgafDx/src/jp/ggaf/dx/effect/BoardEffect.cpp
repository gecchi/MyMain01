#include "jp/ggaf/dx/effect/BoardEffect.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"


using namespace GgafDx;

BoardEffect::BoardEffect(const char* prm_effect_name) : Fix2DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_BoardEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //ハンドル
    _h_offset_u = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v" );
    _h_transformed_x = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_x" );
    _h_transformed_y = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_y" );

    _h_local_left_top_x = _pID3DXEffect->GetParameterByName( nullptr, "g_local_left_top_x" );
    _h_local_left_top_y = _pID3DXEffect->GetParameterByName( nullptr, "g_local_left_top_y" );

    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_depth_z = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_z" );
    _h_sx = _pID3DXEffect->GetParameterByName( nullptr, "g_sx" );
    _h_sy = _pID3DXEffect->GetParameterByName( nullptr, "g_sy" );
    _h_rz = _pID3DXEffect->GetParameterByName( nullptr, "g_rz" );
}

BoardEffect::~BoardEffect() {
}

