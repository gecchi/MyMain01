#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardSetEffect::GgafDx9BoardSetEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    static float view_width = (float)(GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH));
    static float view_height = (float)(GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT));

    hr = _pID3DXEffect->SetFloat("g_view_width", view_width);
    mightDx9Exception(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetFloat(g_view_width) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_view_height", view_height);
    mightDx9Exception(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetFloat(g_view_height) に失敗しました。");

    //ハンドル
    _ahAlpha[0] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha001" );
    _ahAlpha[1] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha002" );
    _ahAlpha[2] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha003" );
    _ahAlpha[3] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha004" );
    _ahAlpha[4] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha005" );
    _ahAlpha[5] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha006" );
    _ahAlpha[6] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha007" );
    _ahAlpha[7] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha008" );

    _ahOffsetU[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU001" );
    _ahOffsetU[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU002" );
    _ahOffsetU[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU003" );
    _ahOffsetU[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU004" );
    _ahOffsetU[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU005" );
    _ahOffsetU[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU006" );
    _ahOffsetU[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU007" );
    _ahOffsetU[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU008" );

    _ahOffsetV[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV001" );
    _ahOffsetV[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV002" );
    _ahOffsetV[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV003" );
    _ahOffsetV[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV004" );
    _ahOffsetV[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV005" );
    _ahOffsetV[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV006" );
    _ahOffsetV[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV007" );
    _ahOffsetV[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV008" );

    _ahTransformedX[0] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX001" );
    _ahTransformedX[1] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX002" );
    _ahTransformedX[2] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX003" );
    _ahTransformedX[3] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX004" );
    _ahTransformedX[4] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX005" );
    _ahTransformedX[5] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX006" );
    _ahTransformedX[6] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX007" );
    _ahTransformedX[7] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX008" );

    _ahTransformedY[0] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY001" );
    _ahTransformedY[1] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY002" );
    _ahTransformedY[2] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY003" );
    _ahTransformedY[3] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY004" );
    _ahTransformedY[4] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY005" );
    _ahTransformedY[5] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY006" );
    _ahTransformedY[6] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY007" );
    _ahTransformedY[7] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY008" );

    _ahDepthZ[0] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ001" );
    _ahDepthZ[1] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ002" );
    _ahDepthZ[2] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ003" );
    _ahDepthZ[3] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ004" );
    _ahDepthZ[4] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ005" );
    _ahDepthZ[5] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ006" );
    _ahDepthZ[6] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ007" );
    _ahDepthZ[7] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ008" );

}

GgafDx9BoardSetEffect::~GgafDx9BoardSetEffect() {
}

