#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
//    //VIEW�ϊ��s��
//    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect SetMatrix(g_matView) �Ɏ��s���܂����B");
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", &pCAM->_vMatrixProj );
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect SetMatrix() �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _hMatView  = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hAlpha    = _pID3DXEffect->GetParameterByName( NULL, "g_hAlpha" );
    _hOffsetU  = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV  = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );
    _hPowerBlink = _pID3DXEffect->GetParameterByName( NULL, "g_PowerBlink" );
    _hBlinkThreshold = _pID3DXEffect->GetParameterByName( NULL, "g_BlinkThreshold" );
}

GgafDx9PointSpriteEffect::~GgafDx9PointSpriteEffect() {
}

