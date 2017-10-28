#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxPointSpriteEffect::GgafDxPointSpriteEffect(const char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDxPointSpriteEffect;
    GgafDxCamera* const pCam = pGOD->getSpacetime()->getCamera();
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_dist_CamZ_default", -(pCam->getZOrigin()));
    checkDxException(hr, D3D_OK, "SetFloat(g_dist_CamZ_default) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "SetFloat(g_zf) �Ɏ��s���܂����B");

    //�V�F�[�_�[�n���h��
    _h_matView  = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
//    _h_alpha    = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha" );
//    _h_dist_VpInfrontPlane = _pID3DXEffect->GetParameterByName( nullptr, "g_dist_VpInfrontPlane" );
    _hTexSize = _pID3DXEffect->GetParameterByName( nullptr, "g_TexSize" );
    _hTextureSplitRowcol = _pID3DXEffect->GetParameterByName( nullptr, "g_TextureSplitRowcol" );
    _hUvFlipPtnNo = _pID3DXEffect->GetParameterByName( nullptr, "g_UvFlipPtnNo" );
}

void GgafDxPointSpriteEffect::setParamPerFrame() {
    GgafDxCamera* const pCam = pGOD->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) �Ɏ��s���܂����B");
}

GgafDxPointSpriteEffect::~GgafDxPointSpriteEffect() {
}

