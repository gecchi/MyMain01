#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafLib;

DefaultBoardActor::DefaultBoardActor(const char* prm_name, const char* prm_model) :
                                        GgafDx::BoardActor(prm_name,
                                                           prm_model,
                                                           "DefaultBoardEffect",
                                                           "DefaultBoardTechnique",
                                                           NEW ViewCollisionChecker(this) ) {

    _class_name = "DefaultBoardActor";
    _pColliCollisionChecker = (ViewCollisionChecker*)_pChecker;
}

void DefaultBoardActor::drawHitArea() {
#ifdef MY_DEBUG
    ViewCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultBoardActor::~DefaultBoardActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}

