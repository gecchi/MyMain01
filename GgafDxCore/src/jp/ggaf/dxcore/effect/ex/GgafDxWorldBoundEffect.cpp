#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxWorldBoundEffect::GgafDxWorldBoundEffect(char* prm_effect_name) : GgafDxMorphMeshEffect(prm_effect_name) {
    //_h_pos_camera = _pID3DXEffect->GetParameterByName( NULL, "pos_camera" );
}

//void GgafDxWorldBoundEffect::setParamPerFrame() {
//    GgafDxMorphMeshEffect::setParamPerFrame();
//    HRESULT hr = _pID3DXEffect->SetValue(_h_pos_camera, P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
//    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_pos_camera) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
//}

GgafDxWorldBoundEffect::~GgafDxWorldBoundEffect() {
}

