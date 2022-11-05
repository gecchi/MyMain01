#include "jp/ggaf/lib/actor/SpriteMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

SpriteMeshActor::SpriteMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteMeshActor(prm_name,
                          prm_model,
                          UTIL::createCollisionChecker(this) ) {

    _class_name = "SpriteMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void SpriteMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

SpriteMeshActor::~SpriteMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}


