#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMorphMeshEffect::GgafDxCubeMapMorphMeshEffect(char* prm_effect_name) : GgafDxMorphMeshEffect(prm_effect_name) {
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");

}

GgafDxCubeMapMorphMeshEffect::~GgafDxCubeMapMorphMeshEffect() {
}

