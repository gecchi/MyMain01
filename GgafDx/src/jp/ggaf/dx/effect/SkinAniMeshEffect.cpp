#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

SkinAniMeshEffect::SkinAniMeshEffect(const char* prm_effect_name) : Effect(prm_effect_name) {
    _obj_effect |= Obj_GgafDx_SkinAniMeshEffect;
    Camera* pCam = pGOD->getSpacetime()->getCamera();
    D3DLIGHT9* pLight = &(pGOD->_d3dlight9_default);
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matProj) �Ɏ��s���܂����B");
    //���C�g����
    hr = _pID3DXEffect->SetValue("g_vecLightFrom_World", &(pLight->Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "SetValue(g_vecLightFrom_World) �Ɏ��s���܂����B");
    //Diffuse����
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(pLight->Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "SetValue(g_colLightDiffuse) �Ɏ��s���܂����B");
    //Ambient����
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(pLight->Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "SetValue(g_colLightAmbient) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "SetFloat(g_zf) �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _h_matView = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
//    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
    _h_specular = _pID3DXEffect->GetParameterByName( nullptr, "g_specular" );
    _h_specular_power = _pID3DXEffect->GetParameterByName( nullptr, "g_specular_power" );
    _h_posCam = _pID3DXEffect->GetParameterByName( nullptr, "g_posCam_World" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );

    //�V�F�[�_�[�n���h��
    _h_matView = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _ah_matWorld[0]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld001" );
    _ah_matWorld[1]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld002" );
    _ah_matWorld[2]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld003" );
    _ah_matWorld[3]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld004" );
    _ah_matWorld[4]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld005" );
    _ah_matWorld[5]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld006" );
    _ah_matWorld[6]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld007" );
    _ah_matWorld[7]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld008" );
    _ah_matWorld[8]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld009" );
    _ah_matWorld[9]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld010" );
    _ah_matWorld[10]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld011" );
    _ah_matWorld[11]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld012" );
    _ah_matWorld[12]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld013" );
    _ah_matWorld[13]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld014" );
    _ah_matWorld[14]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld015" );
    _ah_matWorld[15]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld016" );
    _ah_matWorld[16]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld017" );
    _ah_matWorld[17]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld018" );
    _ah_matWorld[18]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld019" );
    _ah_matWorld[19]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld020" );
    _ah_matWorld[20]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld021" );
    _ah_matWorld[21]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld022" );
    _ah_matWorld[22]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld023" );
    _ah_matWorld[23]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld024" );
    _ah_matWorld[24]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld025" );
    _ah_matWorld[25]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld026" );
    _ah_matWorld[26]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld027" );
    _ah_matWorld[27]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld028" );
    _ah_matWorld[28]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld029" );
    _ah_matWorld[29]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld030" );
}

void SkinAniMeshEffect::setParamPerFrame() {
    Camera* pCam = pGOD->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix() );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetValue(_h_posCam, pCam->getVecCamFromPoint(), sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "SetValue(_h_posCam) �Ɏ��s���܂����B_effect_name="<<_effect_name);
}


SkinAniMeshEffect::~SkinAniMeshEffect() {
}

