#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model) :
                                        GgafDx::BoardActor(prm_name,
                                                           prm_model,
                                                           "DefaultBoardEffect",
                                                           "DefaultBoardTechnique") {

    _class_name = "DefaultBoardActor";
    _pViewCollisionChecker = (ViewCollisionChecker*)getChecker();
}

void DefaultBoardActor::drawHitArea() {
#ifdef MY_DEBUG
    ViewCollisionChecker::drawHitArea(_pViewCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultBoardActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultBoardActor::~DefaultBoardActor() {
}

