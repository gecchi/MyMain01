#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXAniMeshEffect::GgafDx9D3DXAniMeshEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", &pCAM->_vMatrixProj );
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::GgafDx9D3DXAniMeshEffect SetMatrix() �Ɏ��s���܂����B");
    //���C�g����
    hr = _pID3DXEffect->SetValue("g_vecLightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshEffect::GgafDx9D3DXAniMeshEffect SetValue(g_vecLightDirection) �Ɏ��s���܂����B");
    //Diffuse����
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshEffect::GgafDx9D3DXAniMeshEffect SetValue(g_colLightDiffuse) �Ɏ��s���܂����B");
    //Ambient����
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshEffect::GgafDx9D3DXAniMeshEffect SetValue(g_colLightAmbient) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_zf", pCAM->_zf );
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshEffect::GgafDx9SpriteEffect SetFloat(g_zf) �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _h_matView = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
}


GgafDx9D3DXAniMeshEffect::~GgafDx9D3DXAniMeshEffect() {
}

