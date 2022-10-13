#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"

#include "jp/ggaf/lib/util/CollisionChecker2D_b.h"

using namespace GgafLib;

DefaultBoardSetActor::DefaultBoardSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::BoardSetActor(
            prm_name,
            prm_model,
            "DefaultBoardSetEffect",
            "DefaultBoardSetTechnique",
            NEW CollisionChecker2D_b(this) ) {
    _class_name = "DefaultBoardSetActor";
    _pColliChecker = (CollisionChecker2D_b*)_pChecker;
}

void DefaultBoardSetActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker2D_b::drawHitArea(_pColliChecker);
#endif
}

DefaultBoardSetActor::~DefaultBoardSetActor() {
    GGAF_DELETE(_pColliChecker);
}

