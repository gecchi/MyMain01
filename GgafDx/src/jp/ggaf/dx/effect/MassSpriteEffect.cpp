#include "jp/ggaf/dx/effect/MassSpriteEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MassSpriteEffect::MassSpriteEffect(const char* prm_effect_name) : MassEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDx_MassSpriteEffect;
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "SetFloat(g_zf) �Ɏ��s���܂����B");

    //�V�F�[�_�[�n���h��
    _h_matView  = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
}

void MassSpriteEffect::setParamPerFrame() {
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix());
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) �Ɏ��s���܂����B");
}

MassSpriteEffect::~MassSpriteEffect() {
}

