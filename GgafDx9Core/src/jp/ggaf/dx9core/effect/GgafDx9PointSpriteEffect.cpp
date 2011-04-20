#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //�V�F�[�_�[���ʂ̃O���[�o���ϐ��ݒ�
    HRESULT hr;
//    //VIEW�ϊ��s��
//    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_matView );
//    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect SetMatrix(g_matView) �Ɏ��s���܂����B");
    //�ˉe�ϊ��s��
    hr = _pID3DXEffect->SetMatrix("g_matProj", &P_CAM->_matProj );
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect SetMatrix(g_matProj) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_dist_CamZ_default", -(P_CAM->_cameraZ_org));
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect SetFloat(g_dist_CamZ_default) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_zn", P_CAM->_zn);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect SetFloat(g_zn) �Ɏ��s���܂����B");
    hr = _pID3DXEffect->SetFloat("g_zf", P_CAM->_zf);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9SpriteEffect SetFloat(g_zf) �Ɏ��s���܂����B");

    //_TRACE_("GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect g_dist_CamZ_default="<<P_CAM->_zn<<" g_dist_CamZ_default="<<( -(P_CAM->_cameraZ_org))<<"");
    //checkDxException(hr, D3D_OK, "GgafDx9PointSpriteEffect::GgafDx9PointSpriteEffect SetFloat(g_zn) �Ɏ��s���܂����B");
    //�V�F�[�_�[�n���h��
    _h_matView  = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hAlpha    = _pID3DXEffect->GetParameterByName( NULL, "g_hAlpha" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
    _h_dist_VpFrontPlane = _pID3DXEffect->GetParameterByName( NULL, "g_dist_VpFrontPlane" );
    _hTexSize = _pID3DXEffect->GetParameterByName( NULL, "g_TexSize" );
    _hTextureSplitRowcol = _pID3DXEffect->GetParameterByName( NULL, "g_TextureSplitRowcol" );
    _hUvFlipPtnNo = _pID3DXEffect->GetParameterByName( NULL, "g_UvFlipPtnNo" );
}

void GgafDx9PointSpriteEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &P_CAM->_matView );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) �Ɏ��s���܂����B");
}

GgafDx9PointSpriteEffect::~GgafDx9PointSpriteEffect() {
}

