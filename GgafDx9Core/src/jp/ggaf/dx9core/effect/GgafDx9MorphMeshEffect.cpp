#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", &pCAM->_vMatrixProj );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MorphMeshEffect SetMatrix() �Ɏ��s���܂����B");
    //���C�g����
    hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect SetValue(g_LightDirection) �Ɏ��s���܂����B");
    //Diffuse����
    hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect SetValue(g_LightDiffuse) �Ɏ��s���܂����B");
    //Ambient����
    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect SetValue(g_LightAmbient) �Ɏ��s���܂����B");

    hr = _pID3DXEffect->SetFloat("g_zf", pCAM->_zf );
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9SpriteEffect SetFloat(g_zf) �Ɏ��s���܂����B");


    //�V�F�[�_�[�n���h��
    _hMorphTargetnum = _pID3DXEffect->GetParameterByName(NULL, "g_morph_target_num");
    _hWeight[1] = _pID3DXEffect->GetParameterByName(NULL, "g_weight1");
    _hWeight[2] = _pID3DXEffect->GetParameterByName(NULL, "g_weight2");
    _hWeight[3] = _pID3DXEffect->GetParameterByName(NULL, "g_weight3");
    _hWeight[4] = _pID3DXEffect->GetParameterByName(NULL, "g_weight4");
    _hWeight[5] = _pID3DXEffect->GetParameterByName(NULL, "g_weight5");
    _hWeight[6] = _pID3DXEffect->GetParameterByName(NULL, "g_weight6");

    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        hr = _pID3DXEffect->SetFloat(_hWeight[i], 0.0f);
        checkDxException(hr, D3D_OK, "GgafDx9MorphMeshEffect::GgafDx9MorphMeshEffect() SetFloat(_hWeight["<<i<<"]) �Ɏ��s���܂����B");
    }
    _hMatView = _pID3DXEffect->GetParameterByName(NULL, "g_matView");
    _hMatWorld = _pID3DXEffect->GetParameterByName(NULL, "g_matWorld");
    _hMaterialDiffuse = _pID3DXEffect->GetParameterByName(NULL, "g_MaterialDiffuse");
    _hPowerBlink = _pID3DXEffect->GetParameterByName( NULL, "g_PowerBlink" );
    _hBlinkThreshold = _pID3DXEffect->GetParameterByName( NULL, "g_BlinkThreshold" );
}


GgafDx9MorphMeshEffect::~GgafDx9MorphMeshEffect() {
}

