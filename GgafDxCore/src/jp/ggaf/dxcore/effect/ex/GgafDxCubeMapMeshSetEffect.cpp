#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMeshSetEffect::GgafDxCubeMapMeshSetEffect(char* prm_effect_name) : GgafDxMeshSetEffect(prm_effect_name) {
//    _h_pos_camera = _pID3DXEffect->GetParameterByName( NULL, "pos_camera" );

    _h_reflectance = _pID3DXEffect->GetParameterByName(NULL, "g_reflectance");
}

//void GgafDxCubeMapMeshSetEffect::setParamPerFrame() {
//    GgafDxMeshSetEffect::setParamPerFrame();
////    HRESULT hr = _pID3DXEffect->SetValue(_h_pos_camera, P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
////    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_pos_camera) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
//}

GgafDxCubeMapMeshSetEffect::~GgafDxCubeMapMeshSetEffect() {
}

