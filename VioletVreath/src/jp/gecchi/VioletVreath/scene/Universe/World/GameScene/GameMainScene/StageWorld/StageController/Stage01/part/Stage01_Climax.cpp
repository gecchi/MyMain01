#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_Climax::Stage01_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_Climax";
    orderActorToFactory(11111111, EnemyAstraea, "STG1BOSS");
    // gen01 end
    _waiting = false;
}

void Stage01_Climax::initialize() {

}

void Stage01_Climax::processBehavior() {
    if (_waiting) {
        return;
    }

    if (getActivePartFrame() == 60) {
        _pBoss = (EnemyAstraea*)obtainActorFromFactory(11111111);
        _pBoss->_Z = -1800000;
        _pBoss->_Y = -100000;
        getDirector()->addSubGroup(_pBoss);
    }

    if (getActivePartFrame() > 60) {
        if (_pBoss->isDisappear()) {
            //isDisappear()‚É‚È‚è‚Á•ú‚µ‚ð‚È‚ñ‚Æ‚©‚·‚é
            _TRACE_("Stage01_Climax::processBehavior() EVENT_STG01_CLIMAX_WAS_BROKEN!!!!");
            throwEventToUpperTree(EVENT_STG01_CLIMAX_WAS_BROKEN,this);
            _waiting = true;
        }
    }


}

Stage01_Climax::~Stage01_Climax() {

}
