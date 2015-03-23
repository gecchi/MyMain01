#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshSetEffect.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMeshSetEffect::GgafDxCubeMapMeshSetEffect(const char* prm_effect_name) : GgafDxMeshSetEffect(prm_effect_name) {
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");
}

GgafDxCubeMapMeshSetEffect::~GgafDxCubeMapMeshSetEffect() {
}

