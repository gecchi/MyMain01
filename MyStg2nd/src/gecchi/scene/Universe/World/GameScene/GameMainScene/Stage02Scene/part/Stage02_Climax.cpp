#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage02_Climax::Stage02_Climax(const char* prm_name) : DefaultScene(prm_name) {

    orderActorToFactory(11111111, EnemyAstraea, "STG1BOSS");
    // gen01 end
    _waiting = false;
}

void Stage02_Climax::initialize() {

}

void Stage02_Climax::processBehavior() {
    if (_waiting) {
        return;
    }

    if (getActivePartFrame() == 60) {
        _pBoss = (EnemyAstraea*)obtainActorFromFactory(11111111);
        _pBoss->_Z = -1800000;
        _pBoss->_Y = -100000;
        getLordActor()->addSubGroup(_pBoss);
    }

    if (getActivePartFrame() > 60) {
        if (_pBoss->isDisappear()) {
            //isDisappear()‚É‚È‚è‚Á•ú‚µ‚ð‚È‚ñ‚Æ‚©‚·‚é
            _TRACE_("Stage02_Climax::processBehavior() STG02_CLIMAX_WAS_BROKEN!!!!");
            throwUpEvent(STG02_CLIMAX_WAS_BROKEN,this);
            _waiting = true;
        }
    }


}

void Stage02_Climax::processFinal() {
}

Stage02_Climax::~Stage02_Climax() {

}
