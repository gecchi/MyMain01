#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeMapMeshEffect::GgafDx9CubeMapMeshEffect(char* prm_effect_name) : GgafDx9MeshEffect(prm_effect_name) {
}

void GgafDx9CubeMapMeshEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &P_CAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
}

GgafDx9CubeMapMeshEffect::~GgafDx9CubeMapMeshEffect() {
}

