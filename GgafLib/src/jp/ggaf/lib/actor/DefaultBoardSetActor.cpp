#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"

#include "jp/ggaf/lib/util/ViewCollisionChecker.h"

using namespace GgafLib;

DefaultBoardSetActor::DefaultBoardSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::BoardSetActor(
            prm_name,
            prm_model,
            "DefaultBoardSetEffect",
            "DefaultBoardSetTechnique",
            NEW ViewCollisionChecker(this) ) {
    _class_name = "DefaultBoardSetActor";
    _pColliCollisionChecker = (ViewCollisionChecker*)_pChecker;
}

void DefaultBoardSetActor::drawHitArea() {
#ifdef MY_DEBUG
    ViewCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultBoardSetActor::~DefaultBoardSetActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}

