#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

CubeMapMeshSetActor::CubeMapMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::CubeMapMeshSetActor(prm_name,
                              prm_model,
                              "CubeMapMeshSetEffect",
                              "CubeMapMeshSetTechnique",
                              UTIL::createCollisionChecker(this) ) {
    _class_name = "CubeMapMeshSetActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void CubeMapMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

CubeMapMeshSetActor::~CubeMapMeshSetActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
