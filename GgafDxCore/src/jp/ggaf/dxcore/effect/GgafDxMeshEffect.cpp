#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMeshEffect::GgafDxMeshEffect(const char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    GgafDxCamera* const pCam = P_GOD->getSpacetime()->getCamera();
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::GgafDxMeshEffect SetMatrix() �Ɏ��s���܂����B");
    //���C�g����
    hr = _pID3DXEffect->SetValue("g_vecLightFrom_World", &(GgafDxGod::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxMeshEffect SetValue(g_vecLightFrom_World) �Ɏ��s���܂����B");
    //Diffuse����
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(GgafDxGod::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxMeshEffect SetValue(g_colLightDiffuse) �Ɏ��s���܂����B");
    //Ambient����
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(GgafDxGod::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxMeshEffect SetValue(g_colLightAmbient) �Ɏ��s���܂����B");

    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxSpriteEffect SetFloat(g_zf) �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _h_matView = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
    _h_matInvWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matInvWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
    _h_offset_u = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v" );
    _h_specular = _pID3DXEffect->GetParameterByName( nullptr, "g_specular" );
    _h_specular_power = _pID3DXEffect->GetParameterByName( nullptr, "g_specular_power" );
    _h_posCam = _pID3DXEffect->GetParameterByName( nullptr, "g_posCam_World" );
    _h_far_rate = _pID3DXEffect->GetParameterByName( nullptr, "g_far_rate" );
//    _h_colFog = _pID3DXEffect->GetParameterByName( nullptr, "g_colFog" );
}

void GgafDxMeshEffect::setParamPerFrame() {
    GgafDxCamera* const pCam = P_GOD->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::setParamPerFrame SetMatrix(_h_matView) �Ɏ��s���܂����B_effect_name="<<_effect_name);
    hr = _pID3DXEffect->SetValue(_h_posCam, pCam->getVecCamFromPoint(), sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::setParamPerFrame SetValue(_h_posCam) �Ɏ��s���܂����B_effect_name="<<_effect_name);
}

GgafDxMeshEffect::~GgafDxMeshEffect() {
}

