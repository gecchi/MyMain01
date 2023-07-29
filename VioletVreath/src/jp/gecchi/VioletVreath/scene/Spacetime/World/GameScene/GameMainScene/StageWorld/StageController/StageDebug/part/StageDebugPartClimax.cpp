#include "StageDebugPartClimax.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/scene/RotateFormationScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

StageDebugPartClimax::StageDebugPartClimax(const char* prm_name) :
        StageDebugPart<GgafLib::DefaultScene>(prm_name, EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED) {
    _class_name = "StageDebugPartClimax";
    requestActor(11111110, EnemyStraea, "STG1BOSS");
    requestActor(11111111, EnemyEmus, "111");
    requestActor(11111112, EnemyEmus, "222");
    // gen01 end
    waiting_ = false;
    pBoss_ = nullptr;
    getBgmConductor()->ready(0, "BGM_01_CLIMAX");
}

void StageDebugPartClimax::initialize() {
}

void StageDebugPartClimax::processBehavior() {
    if (waiting_) {
        //StageDebugPartController ‚ª EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED ‚ðE‚Á‚Ä‚­‚ê‚Ä‚¢‚éB
        //‚³‚æ‚È‚ç‚ð‘Ò‚Â
        return;
    }
    if (getBehaveingFrame() == 60) {
        //ƒ{ƒX“oêI
        pBoss_ = (EnemyStraea*)receiveActor(11111110);
        EnemyEmus* p1 = (EnemyEmus*)receiveActor(11111111);
        EnemyEmus* p2 = (EnemyEmus*)receiveActor(11111112);

        pBoss_->appendGroupChildAsFk(p1,
                PX_C(100),PX_C(100),PX_C(100),    0,0,0);
        pBoss_->appendGroupChildAsFk(p2,
                PX_C(-100),PX_C(-100),PX_C(-100), 0,0,0);
        pBoss_->_z = -1800000;
        pBoss_->_y = -100000;
        getSceneChief()->appendGroupChild(pBoss_);
    }

    if (getBehaveingFrame() > 60) {
        if (pBoss_->hasJustChangedToInactive()) {
            getBgmConductor()->fadeoutStop(0, 120);
            _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED!!!!");
            throwEventUpperTree(EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED);
            waiting_ = true;
        }
    }
}

StageDebugPartClimax::~StageDebugPartClimax() {

}
