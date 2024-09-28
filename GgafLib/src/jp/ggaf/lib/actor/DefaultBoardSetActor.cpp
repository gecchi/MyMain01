#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"

using namespace GgafLib;

DefaultBoardSetActor::DefaultBoardSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::BoardSetActor(
            prm_name,
            prm_model,
            "DefaultBoardSetEffect",
            "DefaultBoardSetTechnique" ) {
    _class_name = "DefaultBoardSetActor";
    _pViewCollisionChecker = (ViewCollisionChecker*)getChecker();
}

void DefaultBoardSetActor::drawHitArea() {
#ifdef MY_DEBUG
    ViewCollisionChecker::drawHitArea(_pViewCollisionChecker);
#endif
}
GgafDx::CollisionChecker* DefaultBoardSetActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultBoardSetActor::~DefaultBoardSetActor() {
}

