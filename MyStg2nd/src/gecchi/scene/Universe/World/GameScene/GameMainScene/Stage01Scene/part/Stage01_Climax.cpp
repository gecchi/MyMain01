#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_Climax::Stage01_Climax(const char* prm_name) : DefaultScene(prm_name) {

    orderActorToFactory(11111111, FormationPallas001a, "STG1BOSS");
    // gen01 end
}

void Stage01_Climax::initialize() {

}

void Stage01_Climax::processBehavior() {
    if (getActivePartFrame() == 60) {
        _pBoss = (EnemyAstraea*)obtainActorFromFactory(11111111);
        getLordActor()->addSubGroup(_pBoss);
    }

    if (getActivePartFrame() > 60) {
        if (_pBoss->isDisappear()) {
            _TRACE_("Stage01_Climax::processBehavior() STG01_BOSS_WAS_BROKEN!!!!");
            throwUpEvent(STG01_BOSS_WAS_BROKEN);
        }
    }


}

void Stage01_Climax::processFinal() {
}

Stage01_Climax::~Stage01_Climax() {

}
