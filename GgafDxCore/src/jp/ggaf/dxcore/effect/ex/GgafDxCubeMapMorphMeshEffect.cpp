#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMorphMeshEffect::GgafDxCubeMapMorphMeshEffect(char* prm_effect_name) : GgafDxMorphMeshEffect(prm_effect_name) {
    //_h_pos_camera = _pID3DXEffect->GetParameterByName( NULL, "pos_camera" );
    _h_reflectance = _pID3DXEffect->GetParameterByName(NULL, "g_reflectance");

}

//void GgafDxCubeMapMorphMeshEffect::setParamPerFrame() {
//    GgafDxMorphMeshEffect::setParamPerFrame();
//    HRESULT hr = _pID3DXEffect->SetValue(_h_pos_camera, P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
//    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_pos_camera) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
//}

GgafDxCubeMapMorphMeshEffect::~GgafDxCubeMapMorphMeshEffect() {
}

