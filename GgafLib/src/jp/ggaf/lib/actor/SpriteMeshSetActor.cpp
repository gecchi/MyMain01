#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteMeshSetActor(prm_name,
                             prm_model,
                             UTIL::createCollisionChecker(this) ) {

    _class_name = "SpriteMeshSetActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void SpriteMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

SpriteMeshSetActor::~SpriteMeshSetActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}

