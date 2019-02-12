#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat) :
    GgafDx::SpriteMeshSetActor(prm_name,
                             prm_model,
                             prm_pStat,
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

