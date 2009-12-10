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
    _ahAlpha[8] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha009" );
    _ahAlpha[9] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha010" );
    _ahAlpha[10] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha011" );
    _ahAlpha[11] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha012" );
    _ahAlpha[12] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha013" );
    _ahAlpha[13] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha014" );
    _ahAlpha[14] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha015" );
    _ahAlpha[15] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha016" );
    _ahAlpha[16] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha017" );
    _ahAlpha[17] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha018" );
    _ahAlpha[18] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha019" );
    _ahAlpha[19] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha020" );
    _ahAlpha[20] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha021" );
    _ahAlpha[21] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha022" );
    _ahAlpha[22] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha023" );
    _ahAlpha[23] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha024" );
    _ahAlpha[24] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha025" );
    _ahAlpha[25] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha026" );
    _ahAlpha[26] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha027" );
    _ahAlpha[27] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha028" );

    _ahOffsetU[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU001" );
    _ahOffsetU[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU002" );
    _ahOffsetU[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU003" );
    _ahOffsetU[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU004" );
    _ahOffsetU[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU005" );
    _ahOffsetU[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU006" );
    _ahOffsetU[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU007" );
    _ahOffsetU[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU008" );
    _ahOffsetU[8] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU009" );
    _ahOffsetU[9] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU010" );
    _ahOffsetU[10] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU011" );
    _ahOffsetU[11] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU012" );
    _ahOffsetU[12] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU013" );
    _ahOffsetU[13] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU014" );
    _ahOffsetU[14] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU015" );
    _ahOffsetU[15] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU016" );
    _ahOffsetU[16] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU017" );
    _ahOffsetU[17] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU018" );
    _ahOffsetU[18] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU019" );
    _ahOffsetU[19] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU020" );
    _ahOffsetU[20] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU021" );
    _ahOffsetU[21] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU022" );
    _ahOffsetU[22] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU023" );
    _ahOffsetU[23] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU024" );
    _ahOffsetU[24] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU025" );
    _ahOffsetU[25] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU026" );
    _ahOffsetU[26] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU027" );
    _ahOffsetU[27] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU028" );

    _ahOffsetV[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV001" );
    _ahOffsetV[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV002" );
    _ahOffsetV[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV003" );
    _ahOffsetV[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV004" );
    _ahOffsetV[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV005" );
    _ahOffsetV[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV006" );
    _ahOffsetV[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV007" );
    _ahOffsetV[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV008" );
    _ahOffsetV[8] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV009" );
    _ahOffsetV[9] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV010" );
    _ahOffsetV[10] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV011" );
    _ahOffsetV[11] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV012" );
    _ahOffsetV[12] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV013" );
    _ahOffsetV[13] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV014" );
    _ahOffsetV[14] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV015" );
    _ahOffsetV[15] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV016" );
    _ahOffsetV[16] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV017" );
    _ahOffsetV[17] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV018" );
    _ahOffsetV[18] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV019" );
    _ahOffsetV[19] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV020" );
    _ahOffsetV[20] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV021" );
    _ahOffsetV[21] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV022" );
    _ahOffsetV[22] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV023" );
    _ahOffsetV[23] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV024" );
    _ahOffsetV[24] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV025" );
    _ahOffsetV[25] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV026" );
    _ahOffsetV[26] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV027" );
    _ahOffsetV[27] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV028" );

    _ahTransformedX[0] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX001" );
    _ahTransformedX[1] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX002" );
    _ahTransformedX[2] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX003" );
    _ahTransformedX[3] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX004" );
    _ahTransformedX[4] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX005" );
    _ahTransformedX[5] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX006" );
    _ahTransformedX[6] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX007" );
    _ahTransformedX[7] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX008" );
    _ahTransformedX[8] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX009" );
    _ahTransformedX[9] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX010" );
    _ahTransformedX[10] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX011" );
    _ahTransformedX[11] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX012" );
    _ahTransformedX[12] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX013" );
    _ahTransformedX[13] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX014" );
    _ahTransformedX[14] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX015" );
    _ahTransformedX[15] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX016" );
    _ahTransformedX[16] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX017" );
    _ahTransformedX[17] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX018" );
    _ahTransformedX[18] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX019" );
    _ahTransformedX[19] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX020" );
    _ahTransformedX[20] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX021" );
    _ahTransformedX[21] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX022" );
    _ahTransformedX[22] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX023" );
    _ahTransformedX[23] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX024" );
    _ahTransformedX[24] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX025" );
    _ahTransformedX[25] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX026" );
    _ahTransformedX[26] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX027" );
    _ahTransformedX[27] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX028" );

    _ahTransformedY[0] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY001" );
    _ahTransformedY[1] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY002" );
    _ahTransformedY[2] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY003" );
    _ahTransformedY[3] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY004" );
    _ahTransformedY[4] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY005" );
    _ahTransformedY[5] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY006" );
    _ahTransformedY[6] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY007" );
    _ahTransformedY[7] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY008" );
    _ahTransformedY[8] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY009" );
    _ahTransformedY[9] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY010" );
    _ahTransformedY[10] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY011" );
    _ahTransformedY[11] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY012" );
    _ahTransformedY[12] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY013" );
    _ahTransformedY[13] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY014" );
    _ahTransformedY[14] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY015" );
    _ahTransformedY[15] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY016" );
    _ahTransformedY[16] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY017" );
    _ahTransformedY[17] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY018" );
    _ahTransformedY[18] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY019" );
    _ahTransformedY[19] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY020" );
    _ahTransformedY[20] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY021" );
    _ahTransformedY[21] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY022" );
    _ahTransformedY[22] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY023" );
    _ahTransformedY[23] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY024" );
    _ahTransformedY[24] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY025" );
    _ahTransformedY[25] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY026" );
    _ahTransformedY[26] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY027" );
    _ahTransformedY[27] = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY028" );

    _ahDepthZ[0] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ001" );
    _ahDepthZ[1] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ002" );
    _ahDepthZ[2] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ003" );
    _ahDepthZ[3] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ004" );
    _ahDepthZ[4] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ005" );
    _ahDepthZ[5] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ006" );
    _ahDepthZ[6] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ007" );
    _ahDepthZ[7] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ008" );
    _ahDepthZ[8] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ009" );
    _ahDepthZ[9] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ010" );
    _ahDepthZ[10] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ011" );
    _ahDepthZ[11] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ012" );
    _ahDepthZ[12] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ013" );
    _ahDepthZ[13] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ014" );
    _ahDepthZ[14] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ015" );
    _ahDepthZ[15] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ016" );
    _ahDepthZ[16] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ017" );
    _ahDepthZ[17] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ018" );
    _ahDepthZ[18] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ019" );
    _ahDepthZ[19] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ020" );
    _ahDepthZ[20] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ021" );
    _ahDepthZ[21] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ022" );
    _ahDepthZ[22] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ023" );
    _ahDepthZ[23] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ024" );
    _ahDepthZ[24] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ025" );
    _ahDepthZ[25] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ026" );
    _ahDepthZ[26] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ027" );
    _ahDepthZ[27] = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ028" );

}

GgafDx9BoardSetEffect::~GgafDx9BoardSetEffect() {
}

