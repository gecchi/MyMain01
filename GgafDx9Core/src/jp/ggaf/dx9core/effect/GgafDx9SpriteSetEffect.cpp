#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
//    //VIEW�ϊ��s��
//    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
//    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect SetMatrix(g_matView) �Ɏ��s���܂����B");
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9Universe::_pCamera->_vMatrixProj );
    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect SetMatrix() �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _hMatView  = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );

    _ahMatWorld[0]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld001" );
    _ahMatWorld[1]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld002" );
    _ahMatWorld[2]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld003" );
    _ahMatWorld[3]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld004" );
    _ahMatWorld[4]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld005" );
    _ahMatWorld[5]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld006" );
    _ahMatWorld[6]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld007" );
    _ahMatWorld[7]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld008" );

    _hOffsetU  = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV  = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );


    _hAlpha    = _pID3DXEffect->GetParameterByName( NULL, "g_hAlpha" );

}

GgafDx9SpriteSetEffect::~GgafDx9SpriteSetEffect() {
}

