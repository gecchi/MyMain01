#include "jp/ggaf/lib/actor/SpriteMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

SpriteMeshActor::SpriteMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteMeshActor(prm_name,
                          prm_model,
                          UTIL::createChecker(this) ) {

    _class_name = "SpriteMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void SpriteMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

SpriteMeshActor::~SpriteMeshActor() {
    GGAF_DELETE(_pColliChecker);
}


