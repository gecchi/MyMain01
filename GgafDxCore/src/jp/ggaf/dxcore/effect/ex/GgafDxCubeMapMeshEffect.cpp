#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMeshEffect::GgafDxCubeMapMeshEffect(char* prm_effect_name) : GgafDxMeshEffect(prm_effect_name) {
//    _h_pos_camera = _pID3DXEffect->GetParameterByName( nullptr, "pos_camera" );
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");
}

//void GgafDxCubeMapMeshEffect::setParamPerFrame() {
//    GgafDxMeshEffect::setParamPerFrame();
//    HRESULT hr = _pID3DXEffect->SetValue(_h_pos_camera, P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
//    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_pos_camera) �Ɏ��s���܂����B");
//}

GgafDxCubeMapMeshEffect::~GgafDxCubeMapMeshEffect() {
}

