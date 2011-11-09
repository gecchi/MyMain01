#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXAniMeshEffect::GgafDxD3DXAniMeshEffect(char* prm_effect_name) : GgafDxEffect(prm_effect_name) {

    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", &P_CAM->_matProj );
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshActor::GgafDxD3DXAniMeshEffect SetMatrix() �Ɏ��s���܂����B");
    //���C�g����
    hr = _pID3DXEffect->SetValue("g_vecLightDirection", &(GgafDxGod::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshEffect::GgafDxD3DXAniMeshEffect SetValue(g_vecLightDirection) �Ɏ��s���܂����B");
    //Diffuse����
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(GgafDxGod::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshEffect::GgafDxD3DXAniMeshEffect SetValue(g_colLightDiffuse) �Ɏ��s���܂����B");
    //Ambient����
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(GgafDxGod::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshEffect::GgafDxD3DXAniMeshEffect SetValue(g_colLightAmbient) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_zf", P_CAM->_zf);
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshEffect::GgafDxSpriteEffect SetFloat(g_zf) �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _h_matView = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
}

void GgafDxD3DXAniMeshEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &P_CAM->_matView );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) �Ɏ��s���܂����B");
}


GgafDxD3DXAniMeshEffect::~GgafDxD3DXAniMeshEffect() {
}
