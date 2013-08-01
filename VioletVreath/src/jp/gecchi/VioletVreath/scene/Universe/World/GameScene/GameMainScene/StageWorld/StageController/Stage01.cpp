#include "stdafx.h"
#include "Stage01.h"

#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi001.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpace001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/Stage01PartController.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/util/CmRandomNumberGenerator.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Horizon/Horizon001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01::Stage01(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage01";

    pScene_StagePartCtrler_ = NEW Stage01PartController("Stage01PartController");
    pScene_StagePartCtrler_->inactivate();
    addSubLast(pScene_StagePartCtrler_);
    Sleep(2);
    pWorldBoundSpace_  = NEW WorldBoundSpace001("BG_SPACE");
    getSceneDirector()->addSubGroup(pWorldBoundSpace_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    getSceneDirector()->addSubGroup(pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("Stage01Msg");
    getSceneDirector()->addSubGroup(pMessage_);
    pMessage_->inactivate();


    pPlanet_ = NEW Planet001("Planet001");
    getSceneDirector()->addSubGroup(KIND_EFFECT, pPlanet_);
    pHorizon_ = NEW Horizon001("Horizon001");
    getSceneDirector()->addSubGroup(KIND_CHIKEI, pHorizon_);

    //debug ---->
//    EnemyHisbe* pTest = NEW EnemyHisbe("tst");
//    pTest->position(PX_C(0),PX_C(0), PX_C(100));
//    pTest->_pKurokoA->setFaceAngTwd(PX_C(100), PX_C(100), PX_C(100));
//    pTest->_pKurokoA->behave();
//    getSceneDirector()->addSubGroup(pTest);
    //<-----debug

    fadeoutSceneWithBgm(0); //最初は非表示
}

void Stage01::initialize() {
    Stage::initialize();
}

void Stage01::processBehavior() {
    Stage::processBehavior();

    switch (_pProg->get()) {
        case Stage::PROG_INIT: {
            _pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (_pProg->getFrameInProgress() == 180) { //ステージ１開始！
                pMessage_->activateImmed();
                pWorldBoundSpace_->activateTree();    //背景ON
                pHoshiBoshi_->activateTree();    //背景ON
                pScene_StagePartCtrler_->activate();

                pPlanet_->activate();

                fadeinSceneTree(360);
                _pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (_pProg->getFrameInProgress() == 60) { //ステージ１開始！
                pMessage_->update(PX_C(300), PX_C(300), "SCENE 01 START!");
                pMessage_->inactivateDelay(240);
            }
            //EVENT_STG01_CTRLER_WAS_ENDイベント待ち
            break;
        }
        case Stage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01::processBehavior()  Stage::PROG_ENDになりますた！");
                throwEventUpperTree(EVENT_PREPARE_TRANSIT_STAGE); //通過ステージ準備へ
            }

            if (_pProg->getFrameInProgress() == 60) {
                pMessage_->activateImmed();
                pMessage_->update(PX_C(300), PX_C(300), "SCENE 01 CLEAR!!");
                pMessage_->inactivateDelay(120);
                fadeoutSceneWithBgm(300);
            }
            if (_pProg->getFrameInProgress() == 300) {
                throwEventUpperTree(EVENT_STG01_WAS_END);
            }
            break;
        }
        default:
            break;

    }

}

void Stage01::processJudgement() {
}

void Stage01::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CTRLER_WAS_END ) {
        _TRACE_("Stage01::onCatchEvent() EVENT_STG01_CTRLER_WAS_END をキャッチ。ステータスをStage::PROG_ENDへ");
        pScene_StagePartCtrler_->sayonara(60*60);
        _pProg->change(Stage::PROG_END);
    } else {

    }
}


Stage01::~Stage01() {

}
