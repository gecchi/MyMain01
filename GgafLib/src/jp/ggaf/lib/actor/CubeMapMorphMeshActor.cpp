#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

CubeMapMorphMeshActor::CubeMapMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafCore::Status* prm_pStat) :
        GgafDx::CubeMapMorphMeshActor(prm_name,
                                    prm_model_id,
                                    "CubeMapMorphMeshEffect",
                                    "CubeMapMorphMeshTechnique",
                                    prm_pStat,
                                    UTIL::createChecker(this) ) {
    _class_name = "CubeMapMorphMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void CubeMapMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
    }


CubeMapMorphMeshActor::~CubeMapMorphMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
