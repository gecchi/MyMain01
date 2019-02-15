#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteMeshSetActor(prm_name,
                             prm_model,
                             UTIL::createChecker(this) ) {

    _class_name = "SpriteMeshSetActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void SpriteMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

SpriteMeshSetActor::~SpriteMeshSetActor() {
    GGAF_DELETE(_pColliChecker);
}

