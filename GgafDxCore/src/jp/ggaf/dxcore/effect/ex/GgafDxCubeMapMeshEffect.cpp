#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMeshEffect::GgafDxCubeMapMeshEffect(char* prm_effect_name) : GgafDxMeshEffect(prm_effect_name) {
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");
}

GgafDxCubeMapMeshEffect::~GgafDxCubeMapMeshEffect() {
}

