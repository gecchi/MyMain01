#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

#include "jp/ggaf/lib/util/CollisionChecker2D_b.h"

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

DefaultBoardActor::~DefaultBoardActor() {
    GGAF_DELETE(_pColliChecker);
}

