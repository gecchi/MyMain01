#include "jp/ggaf/dx/effect/MassPointSpriteEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MassPointSpriteEffect::MassPointSpriteEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_MassPointSpriteEffect;
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_dist_CamZ_default", -(pCam->getZOrigin()));
    checkDxException(hr, D3D_OK, "SetFloat(g_dist_CamZ_default) �Ɏ��s���܂����B");

    //�V�F�[�_�[�n���h��
    _hTexSize = _pID3DXEffect->GetParameterByName( nullptr, "g_TexSize" );
    _hTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_TextureSplitRowcol" );
    _hInvTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_InvTextureSplitRowcol" );
}

MassPointSpriteEffect::~MassPointSpriteEffect() {
}

