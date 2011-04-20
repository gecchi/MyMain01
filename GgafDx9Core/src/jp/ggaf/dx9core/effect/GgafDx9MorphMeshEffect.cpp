#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &P_CAM->_matProj );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MorphMeshEffect SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_vecLightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect SetValue(g_vecLightDirection) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect SetValue(g_colLightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect SetValue(g_colLightAmbient) に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_zf", P_CAM->_zf);
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9SpriteEffect SetFloat(g_zf) に失敗しました。");


    //シェーダーハンドル
    _h_morph_target_num = _pID3DXEffect->GetParameterByName(NULL, "g_morph_target_num");
    _ah_weight[1] = _pID3DXEffect->GetParameterByName(NULL, "g_weight1");
    _ah_weight[2] = _pID3DXEffect->GetParameterByName(NULL, "g_weight2");
    _ah_weight[3] = _pID3DXEffect->GetParameterByName(NULL, "g_weight3");
    _ah_weight[4] = _pID3DXEffect->GetParameterByName(NULL, "g_weight4");
    _ah_weight[5] = _pID3DXEffect->GetParameterByName(NULL, "g_weight5");
    _ah_weight[6] = _pID3DXEffect->GetParameterByName(NULL, "g_weight6");

    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        hr = _pID3DXEffect->SetFloat(_ah_weight[i], 0.0f);
        checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect() SetFloat(_ah_weight["<<i<<"]) に失敗しました。");
    }
    _h_matView = _pID3DXEffect->GetParameterByName(NULL, "g_matView");
    _h_matWorld = _pID3DXEffect->GetParameterByName(NULL, "g_matWorld");
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName(NULL, "g_colMaterialDiffuse");
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
}

void GgafDx9MorphMeshEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &P_CAM->_matView );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

GgafDx9MorphMeshEffect::~GgafDx9MorphMeshEffect() {
}

