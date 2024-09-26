#include "Stage02.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi001.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBound002.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/Stage02PartController.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

Stage02::Stage02(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage02";

    pScene_StagePartCtrler_ = NEW Stage02PartController("Stage02PartController");
    pScene_StagePartCtrler_->inactivate();
    appendChild(pScene_StagePartCtrler_);
    Sleep(2);
    pWorldBound_  = NEW WorldBound002("BG_SPACE_TEST");
    getSceneChief()->appendChild(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    getSceneChief()->appendChild(pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("Stage02Msg");
    getSceneChief()->appendChild(pMessage_);
    pMessage_->inactivate();

    fadeoutSceneWithBgm(0); //最初は非表示
}

void Stage02::initialize() {
    Stage::initialize();
}

void Stage02::processBehavior() {
    Stage::processBehavior();
    ScenePhase* pPhase = getPhase();
    if (pPhase->getCurrent() == Stage::PHASE_INIT) {
       pPhase->change(Stage::PHASE_BEGIN);
    }

    if (pPhase->getCurrent() == Stage::PHASE_BEGIN) {
        if (pPhase->hasArrivedFrameAt(180)) { //ステージ2開始！
            pMessage_->activateImmed();
            pMessage_->update(300*1000, 300*1000, "SCENE 02 START!");
            pMessage_->inactivateDelay(240);
            pWorldBound_->activateTree();
            pScene_StagePartCtrler_->activate();
            fadeinScene(240);
            pPhase->change(Stage::PHASE_PLAYING);
        }
    }

    if (pPhase->getCurrent() == Stage::PHASE_END) {
        if (pPhase->hasJustChanged()) {
            _TRACE_(FUNC_NAME<<"  Stage::PHASE_ENDになりますた！");
            throwEventUpperTree(EVENT_PREPARE_TRANSIT_STAGE); //通過ステージ準備へ
        }

        if (pPhase->hasArrivedFrameAt(60)) {
            pMessage_->activateImmed();
            pMessage_->update(300*1000, 300*1000, "SCENE 02 CLEAR!!");
            pMessage_->inactivateDelay(120);
            fadeoutSceneWithBgm(300);
        }
        if (pPhase->hasArrivedFrameAt(300)) {
            throwEventUpperTree(EVENT_STAGE02_WAS_FINISHED);
        }
    }
}

void Stage02::processJudgement() {
}

void Stage02::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    ScenePhase* pPhase = getPhase();
    if (prm_event_val == EVENT_STAGE02_CTRLER_WAS_END ) {
        _TRACE_(FUNC_NAME<<" STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをStage::PHASE_ENDへ");
        pScene_StagePartCtrler_->sayonara(SEC_F(60));
        pPhase->change(Stage::PHASE_END);
    } else {

    }
}

Stage02::~Stage02() {

}
