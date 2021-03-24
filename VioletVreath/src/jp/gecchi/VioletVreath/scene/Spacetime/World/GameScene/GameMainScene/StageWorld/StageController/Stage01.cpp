#include "Stage01.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/util/CmRandomNumberGenerator.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi001.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBound001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageController.h"
#include "Stage01/Stage01PartController.h"


#include "jp/ggaf/core/util/Util.h"



using namespace GgafLib;
using namespace VioletVreath;

Stage01::Stage01(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage01";

    pScene_StagePartCtrler_ = NEW Stage01PartController("Stage01PartController");
    pScene_StagePartCtrler_->inactivate();
    appendChild(pScene_StagePartCtrler_);
    Sleep(2);
    pWorldBound_  = NEW WorldBound001("BG_SPACE");
    bringSceneMediator()->appendGroupChild(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    bringSceneMediator()->appendGroupChild(pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("Stage01Msg");
    bringSceneMediator()->appendGroupChild(pMessage_);
    pMessage_->inactivate();


    pPlanet_ = NEW Planet001("Planet001");
    bringSceneMediator()->appendGroupChild(KIND_EFFECT, pPlanet_);
//    pHorizon_ = NEW Horizon001("Horizon001");
//    bringSceneMediator()->appendGroupChild(KIND_CHIKEI, pHorizon_);

    //debug ---->
//    EnemyHisbe* pTest = NEW EnemyHisbe("tst");
//    pTest->setPosition(PX_C(0),PX_C(0), PX_C(100));
//    pTest->setFaceAngTwd(PX_C(100), PX_C(100), PX_C(100));
//    pTest->callVecDriver()->behave();
//    bringSceneMediator()->appendGroupChild(pTest);
    //<-----debug

    fadeoutSceneWithBgm(0); //最初は非表示
}

void Stage01::initialize() {
    Stage::initialize();
}

void Stage01::processBehavior() {

//    if (getBehaveingFrame() == 9663) {
//        pGAME_SCENE->pauseGame();
//        _TRACE_("HOGEHOGE");
//    }
    Stage::processBehavior();
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case Stage::PROG_INIT: {
            pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (pProg->hasArrivedAt(180)) { //ステージ１開始！
                pMessage_->activateImmed();
                pWorldBound_->activateTree();    //背景ON
                pHoshiBoshi_->activateTree();    //背景ON
                pScene_StagePartCtrler_->activate();

                pPlanet_->activate();

                fadeinScene(360);
                pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (pProg->hasArrivedAt(60)) { //ステージ１開始！
                pMessage_->update(PX_C(300), PX_C(300), "SCENE DEBUG START!");
                pMessage_->inactivateDelay(240);
            }
            //EVENT_STAGE01_PART_CTRLER_WAS_ENDイベント待ち
            break;
        }
        case Stage::PROG_END: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<"  Stage::PROG_ENDになりますた！");
                throwEventUpperTree(EVENT_PREPARE_TRANSIT_STAGE); //通過ステージ準備へ
            }

            if (pProg->hasArrivedAt(60)) {
                pMessage_->activateImmed();
                pMessage_->update(PX_C(300), PX_C(300), "SCENE DEBUG CLEAR!!");
                pMessage_->inactivateDelay(120);
                fadeoutSceneWithBgm(300);
            }
            if (pProg->hasArrivedAt(300)) {
                throwEventUpperTree(EVENT_STAGE01_WAS_FINISHED);
            }
            break;
        }
        default: {
            break;
        }
    }

}

void Stage01::processJudgement() {
}

void Stage01::onCatchEvent(hashval prm_no, void* prm_pSource) {
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STAGE01_PART_CTRLER_WAS_END ) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_CTRLER_WAS_END をキャッチ。ステータスをStage::PROG_ENDへ");
        pScene_StagePartCtrler_->sayonara(60*60);
        pProg->change(Stage::PROG_END);
    } else {

    }
}


Stage01::~Stage01() {

}
