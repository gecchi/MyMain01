#include "jp/ggaf/dx/effect/ex/CubeMapMeshEffect.h"


using namespace GgafDx;

CubeMapMeshEffect::CubeMapMeshEffect(const char* prm_effect_name) : MeshEffect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_CubeMapMeshEffect;
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");
}

CubeMapMeshEffect::~CubeMapMeshEffect() {
}

