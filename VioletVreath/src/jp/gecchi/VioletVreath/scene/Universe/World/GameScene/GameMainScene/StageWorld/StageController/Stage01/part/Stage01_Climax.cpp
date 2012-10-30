#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_Climax::Stage01_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_Climax";
    orderActorToFactory(11111111, EnemyAstraea, "STG1BOSS");
    // gen01 end
    waiting_ = false;
}

void Stage01_Climax::initialize() {

}

void Stage01_Climax::processBehavior() {
    if (waiting_) {
        return;
    }

    if (getActivePartFrame() == 60) {
        pBoss_ = (EnemyAstraea*)obtainActorFromFactory(11111111);
        pBoss_->_Z = -1800000;
        pBoss_->_Y = -100000;
        getDirector()->addSubGroup(pBoss_);
    }

    if (getActivePartFrame() > 60) {
        if (pBoss_->isDisappear()) {
            //isDisappear()‚É‚È‚è‚Á•ú‚µ‚ð‚È‚ñ‚Æ‚©‚·‚é
            _TRACE_("Stage01_Climax::processBehavior() EVENT_STG01_CLIMAX_WAS_BROKEN!!!!");
            throwEventToUpperTree(EVENT_STG01_CLIMAX_WAS_BROKEN, this);
            waiting_ = true;
        }
    }


}

Stage01_Climax::~Stage01_Climax() {

}
