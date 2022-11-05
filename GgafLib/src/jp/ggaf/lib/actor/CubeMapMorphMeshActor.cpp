#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

CubeMapMorphMeshActor::CubeMapMorphMeshActor(const char* prm_name, const char* prm_model) :
        GgafDx::CubeMapMorphMeshActor(prm_name,
                                    prm_model,
                                    "CubeMapMorphMeshEffect",
                                    "CubeMapMorphMeshTechnique",
                                    UTIL::createCollisionChecker(this) ) {
    _class_name = "CubeMapMorphMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void CubeMapMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
    }


CubeMapMorphMeshActor::~CubeMapMorphMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
