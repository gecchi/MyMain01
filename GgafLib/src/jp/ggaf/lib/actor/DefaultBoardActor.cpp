#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

#include "jp/ggaf/lib/util/CollisionChecker2D_b.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model) :
                                        GgafDx::BoardActor(prm_name,
                                                           prm_model,
                                                           "DefaultBoardEffect",
                                                           "DefaultBoardTechnique",
                                                           NEW CollisionChecker2D_b(this) ) {

    _class_name = "DefaultBoardActor";
    _pColliChecker = (CollisionChecker2D_b*)_pChecker;
}

void DefaultBoardActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker2D_b::drawHitArea(_pColliChecker);
#endif
}

DefaultBoardActor::~DefaultBoardActor() {
    GGAF_DELETE(_pColliChecker);
}

