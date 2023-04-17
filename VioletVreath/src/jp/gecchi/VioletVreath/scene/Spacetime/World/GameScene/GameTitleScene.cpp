#include "GameTitleScene.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/manager/SeConnection.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiTitle.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundTitle.h"
#include "jp/gecchi/VioletVreath/actor/menu/title/MenuBoardTitle.h"
#include "jp/gecchi/VioletVreath/actor/title/TitleBoard.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameTitleScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

#define GAMETITLE_TIMEOUT (60*20)

enum {
    PHASE_INIT     ,
    PHASE_TITLE    ,
    PHASE_SELECT   ,
    PHASE_GAMESTART,
    PHASE_FINISH   ,
    PHASE_BANPEI,
};

GameTitleScene::GameTitleScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "GameTitleScene";
    getPhase()->reset(PHASE_INIT);

    pLabel01_ = NEW LabelGecchi16Font("STR01");
    bringSceneMediator()->appendGroupChild(pLabel01_);

    pLabel02_ = NEW LabelGecchi16Font("STR02");
    bringSceneMediator()->appendGroupChild(pLabel02_);

    pTitleBoard_ = NEW TitleBoard("TitleBoard");
    bringSceneMediator()->appendGroupChild(pTitleBoard_);

    pMenu_ = NEW MenuBoardTitle("MenuBoardTitle");
    bringSceneMediator()->appendGroupChild(pMenu_);

    pWorldBound_ = NEW WorldBoundTitle("TITLE_BG_WB");
    bringSceneMediator()->appendGroupChild(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshiTitle("TITLE_BG_HOSHI");
    bringSceneMediator()->appendGroupChild(pHoshiBoshi_);

    pSeConnection_exec_ = connectToSeManager("SE_EXECUTE");

   // getBgmConductor()->ready(0, "BGM_DEMO");
    frame_of_noinput_ = 0;
    active_item_ = 0;

}

void GameTitleScene::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    pLabel01_->update("");
    pLabel02_->update("");
    pTitleBoard_->setPosition(PX_C(100), PX_C(90));
    getPhase()->reset(PHASE_INIT);
}

void GameTitleScene::onActive() {
    pWorldBound_->activate();
    pHoshiBoshi_->activate();
    pWorldBound_->fadein();
    pHoshiBoshi_->fadein();
    getPhase()->reset(PHASE_INIT);
}

void GameTitleScene::initialize() {
    _TRACE_(FUNC_NAME<<"");
}

void GameTitleScene::processBehavior() {

    ScenePhase* pPhase = getPhase();
    switch (pPhase->getPrevWhenChanged()) {
        default: {
            break;
        }
    }
//    DECLARE_EVENT_VAL(STR02);
//    LabelGecchi16Font* pLabel02 = (LabelGecchi16Font*) bringSceneMediator()->bring(STR02);
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_TITLE);
            break;
        }

        case PHASE_TITLE: {
            if (pPhase->hasJustChanged()) {
                pLabel02_->update(PX_C(400), PX_C(400), "PUSH UI_EXECUTE TO BEGIN!");
            }
            if (VVB->isPushedDown(0, VVB_UI_EXECUTE) || GgafDx::Input::isPressedMouseButton(0)) {
                pSeConnection_exec_->peek()->play();
                pPhase->change(PHASE_SELECT);
            } else if (pPhase->hasArrivedFrameAt(GAMETITLE_TIMEOUT)) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                pPhase->change(PHASE_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case PHASE_SELECT: {
            if (pPhase->hasJustChanged()) {
                pMenu_->rise(PX_C(50), PX_C(250));
                frame_of_noinput_ = pPhase->getFrame();
            }

            if (pMenu_->canControll()) {
                if (pMenu_->getOnDecidedIndex() == MenuBoardTitle::ITEM_GAME_START) {
                    pMenu_->disableControll(); //入力受付終わり
                    pSeConnection_exec_->peek()->play();
                    pPhase->change(PHASE_GAMESTART);
                }
            }

            if (GgafDx::Input::getFirstPressedJoyRgbButton(P1_JOY_STICK) != -1) {
                frame_of_noinput_ = pPhase->getFrame();
            }
            if (GgafDx::Input::getFirstPushedDownKey() != -1) {
                frame_of_noinput_ = pPhase->getFrame();
            }
            if (pMenu_->getRisingSubMenu()) {
                //サブメニューを開いている場合は勝手にタイトルシーンを終了させない
                frame_of_noinput_ = pPhase->getFrame();
            }

            if (pPhase->getFrame() >= frame_of_noinput_ + GAMETITLE_TIMEOUT) {
                //ボーっと見てた場合
                _TRACE_("GameTitleScene throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH); //普通に終了イベント
                pPhase->change(PHASE_FINISH); //タイトルシーン終了へ
            }
            break;
        }

        case PHASE_GAMESTART: {
            if (pPhase->hasJustChanged()) {
            }
            if (pPhase->hasArrivedFrameAt(90)) {
                throwEventUpperTree(EVENT_GAMESTART);      //スタートでに終了イベント
                pPhase->change(PHASE_FINISH); //タイトルシーン終了へ
            }
            //点滅
            if (pPhase->getFrame() % 10U < 5 ) {
                pLabel02_->update(PX_C(700), PX_C(200), "READY GO!");
            } else {
                pLabel02_->update(PX_C(700), PX_C(200), "");
            }
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
                pMenu_->sinkMe();
//                fadeoutSceneWithBgmTree(FADE_FRAMES);
//                inactivateDelay(FADE_FRAMES);
            }
            //おしまい待ちぼうけループ
            break;
        }

        default: {
            break;
        }
    }
}

GameTitleScene::~GameTitleScene() {
//    GGAF_DELETEARR(papStringItem_);
    pSeConnection_exec_->close();
}
