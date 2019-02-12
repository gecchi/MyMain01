#include "jp/ggaf/dx/effect/ex/CubeMapMorphMeshEffect.h"


using namespace GgafDx;

CubeMapMorphMeshEffect::CubeMapMorphMeshEffect(const char* prm_effect_name) : MorphMeshEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDx_CubeMapMorphMeshEffect;
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");

}

CubeMapMorphMeshEffect::~CubeMapMorphMeshEffect() {
}

