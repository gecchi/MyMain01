#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeMapMeshEffect::GgafDx9CubeMapMeshEffect(char* prm_effect_name) : GgafDx9MeshEffect(prm_effect_name) {
    _h_cameraPosW = _pID3DXEffect->GetParameterByName( NULL, "cameraPosW" );
}

void GgafDx9CubeMapMeshEffect::setParamPerFrame() {
    GgafDx9MeshEffect::setParamPerFrame();
    HRESULT hr = _pID3DXEffect->SetValue(_h_cameraPosW, &P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_cameraPosW) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
}

GgafDx9CubeMapMeshEffect::~GgafDx9CubeMapMeshEffect() {
}

