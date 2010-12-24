#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeMapMeshSetEffect::GgafDx9CubeMapMeshSetEffect(char* prm_effect_name) : GgafDx9MeshSetEffect(prm_effect_name) {
    _h_pos_camera = _pID3DXEffect->GetParameterByName( NULL, "pos_camera" );
}

void GgafDx9CubeMapMeshSetEffect::setParamPerFrame() {
    GgafDx9MeshSetEffect::setParamPerFrame();
    HRESULT hr = _pID3DXEffect->SetValue(_h_pos_camera, &P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_pos_camera) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
}

GgafDx9CubeMapMeshSetEffect::~GgafDx9CubeMapMeshSetEffect() {
}

