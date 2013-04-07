#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02_Climax::Stage02_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02_Climax";
    orderActorToFactory(11111111, EnemyAstraea, "STG1BOSS");
    // gen01 end
    waiting_ = false;
}

void Stage02_Climax::initialize() {

}

void Stage02_Climax::processBehavior() {
    if (waiting_) {
        return;
    }

    if (getActiveFrame() == 60) {
        pBoss_ = (EnemyAstraea*)obtainActorFromFactory(11111111);
        pBoss_->_Z = -1800000;
        pBoss_->_Y = -100000;
        getSceneDirector()->addSubGroup(pBoss_);
    }

    if (getActiveFrame() > 60) {
        if (pBoss_->isDisappear()) {
            //isDisappear()になりっ放しをなんとかする
            _TRACE_("Stage02_Climax::processBehavior() EVENT_STG02_CLIMAX_WAS_BROKEN!!!!");
            throwEventUpperTree(EVENT_STG02_CLIMAX_WAS_BROKEN);
            waiting_ = true;
        }
    }


}

Stage02_Climax::~Stage02_Climax() {

}
