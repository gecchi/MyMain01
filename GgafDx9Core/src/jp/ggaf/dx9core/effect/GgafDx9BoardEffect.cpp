#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardEffect::GgafDx9BoardEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //���ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matOrthoProj", &GgafDx9God::_vMatrixOrthoProj );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetMatrix(g_matOrthoProj) �Ɏ��s���܂����B");
���܂���������������������

    //���C�g����. �X�v���C�g�ɉA�e�͂���܂���
    //hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    //whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetValue(g_LightDirection) �Ɏ��s���܂����B");
    //Diffuse����. �X�v���C�g�ɉA�e�͂���܂���
    //hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    //whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshModel::GgafDx9BoardEffect SetValue(g_LightDiffuse) �Ɏ��s���܂����B");

//    //Ambient����
//    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
//    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetValue(g_LightAmbient) �Ɏ��s���܂����B");

//    //�e�N�X�`���̗񕪊���
//    hr = _pID3DXEffect->SetValue("g_RowTexSplit", &(_pBoardModel->_row_texture_split), sizeof(int));
//    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetValue(g_RowTexSplit) �Ɏ��s���܂����B");
//    //�e�N�X�`���̍s������
//    hr = _pID3DXEffect->SetValue("g_ColTexSplit", &(_pBoardModel->_col_texture_split), sizeof(int));
//    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetValue(g_ColTexSplit) �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hAlpha = _pID3DXEffect->GetParameterByName( NULL, "g_hAlpha" );
    _hOffsetU = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );
    //_hMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse" );

}


GgafDx9BoardEffect::~GgafDx9BoardEffect() {
    _TRACE_("GgafDx9BoardEffect::~GgafDx9BoardEffect() " << _effect_name << " start");
    _TRACE_("GgafDx9BoardEffect::~GgafDx9BoardEffect() " << _effect_name << " end");
}

