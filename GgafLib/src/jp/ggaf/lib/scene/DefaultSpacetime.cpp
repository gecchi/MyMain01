#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "jp/ggaf/lib/actor/DefaultSceneChief.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"

using namespace GgafLib;


DefaultSpacetime::DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera) :
        GgafDx::Spacetime(prm_name, prm_pCamera) {
    _class_name = "DefaultSpacetime";
}


void DefaultSpacetime::processSettlementBehavior() {
    GgafDx::Spacetime::processSettlementBehavior();
#ifdef MY_DEBUG
    ViewCollisionChecker::_num_check_actors = 0;
    WorldCollisionChecker::_num_otoku_check = 0;
    WorldCollisionChecker::_num_zannen_check = 0;
    WorldCollisionChecker::_num_check_actors = 0;
    WorldCollisionChecker::_num_check = 0;
    ViewCollisionChecker::_num_check = 0;
#endif
}

void DefaultSpacetime::processFinal() {
     GgafDx::Spacetime::processFinal();
}

DefaultSpacetime::~DefaultSpacetime() {
#ifdef MY_DEBUG
    WorldCollisionChecker::releaseHitArea();
    ViewCollisionChecker::releaseHitArea();
#endif
}
