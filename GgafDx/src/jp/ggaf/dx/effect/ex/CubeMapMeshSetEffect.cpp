#include "jp/ggaf/dx/effect/ex/CubeMapMeshSetEffect.h"


using namespace GgafDx;

CubeMapMeshSetEffect::CubeMapMeshSetEffect(const char* prm_effect_name) : MeshSetEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDx_CubeMapMeshSetEffect;
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");
}

CubeMapMeshSetEffect::~CubeMapMeshSetEffect() {
}

