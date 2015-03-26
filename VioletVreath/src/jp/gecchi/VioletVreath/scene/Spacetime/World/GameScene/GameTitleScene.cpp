#include "GameTitleScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiTitle.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundTitle.h"
#include "jp/gecchi/VioletVreath/actor/menu/title/MenuBoardTitle.h"
#include "jp/gecchi/VioletVreath/actor/title/TitleBoard.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameTitleScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define GAMETITLE_TIMEOUT (60*20)
GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(PROG_BANPEI);
    getProgress()->reset(GameTitleScene::PROG_INIT);

    pLabel01_ = NEW LabelGecchi16Font("STR01");
    bringDirector()->addSubGroup(pLabel01_);

    pLabel02_ = NEW LabelGecchi16Font("STR02");
    bringDirector()->addSubGroup(pLabel02_);

    pTitleBoard_ = NEW TitleBoard("TitleBoard");
    bringDirector()->addSubGroup(pTitleBoard_);

    pMenu_ = NEW MenuBoardTitle("pMenu_");
    bringDirector()->addSubGroup(pMenu_);

    pWorldBound_ = NEW WorldBoundTitle("TITLE_BG_WB");
    bringDirector()->addSubGroup(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshiTitle("TITLE_BG_HOSHI");
    bringDirector()->addSubGroup(pHoshiBoshi_);

    pSeConnection_exec_ = getConnection_SeManager("WAVE_EXECUTE");

   // getBGMer()->ready(0, "OGG_BGM_DEMO");
    frame_of_noinput_ = 0;
    active_item_ = 0;

}

void GameTitleScene::onReset() {
    _TRACE_("GameTitleScene::onReset() "<<NODE_INFO<<"");
    pLabel01_->update("");
    pLabel02_->update("");
    pTitleBoard_->position(PX_C(100), PX_C(90));
    getProgress()->reset(GameTitleScene::PROG_INIT);
}

void GameTitleScene::onActive() {
    pWorldBound_->inactivate();
    pHoshiBoshi_->inactivate();
    pWorldBound_->activate();
    pHoshiBoshi_->activate();
    pWorldBound_->fadein();
    pHoshiBoshi_->fadein();
    getProgress()->reset(GameTitleScene::PROG_INIT);
}

void GameTitleScene::initialize() {
    _TRACE_("GameTitleScene::initialize()");
}

void GameTitleScene::processBehavior() {

    SceneProgress* pProg = getProgress();
    switch (pProg->getFromProgOnChange()) {
        default: {
            break;
        }
    }

    switch (pProg->get()) {
        case GameTitleScene::PROG_INIT: {
            pProg->change(GameTitleScene::PROG_TITLE);
            break;
        }

        case GameTitleScene::PROG_TITLE: {
            if (pProg->isJustChanged()) {
                pLabel02_->update(PX_C(400), PX_C(400), "PUSH UI_EXECUTE TO BEGIN!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                pSeConnection_exec_->peek()->play();
                pProg->change(GameTitleScene::PROG_SELECT);
            } else if (pProg->hasArrivedAt(GAMETITLE_TIMEOUT)) {
                //�{�[���ƌ��Ă��ꍇ
                _TRACE_("GameTitleScene throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH); //���ʂɏI���C�x���g
                pProg->change(GameTitleScene::PROG_FINISH); //�^�C�g���V�[���I����
            }
            break;
        }

        case GameTitleScene::PROG_SELECT: {
            if (pProg->isJustChanged()) {
                pMenu_->rise(PX_C(50), PX_C(250));
                frame_of_noinput_ = pProg->getFrame();
            }

            if (pMenu_->canControll()) {
                if (pMenu_->getOnDecidedIndex() == MenuBoardTitle::ITEM_GAME_START) {
                    pMenu_->disableControll(); //���͎�t�I���
                    pSeConnection_exec_->peek()->play();
                    pProg->change(GameTitleScene::PROG_GAMESTART);
                }
            }

            if (GgafDxInput::getBeingPressedJoyRgbButton() != -1) { //
                frame_of_noinput_ = pProg->getFrame();
            }

            if (pProg->getFrame() >= frame_of_noinput_ + GAMETITLE_TIMEOUT) {
                //�{�[���ƌ��Ă��ꍇ
                _TRACE_("GameTitleScene throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMETITLESCENE_FINISH); //���ʂɏI���C�x���g
                pProg->change(GameTitleScene::PROG_FINISH); //�^�C�g���V�[���I����
            }
            break;
        }

        case GameTitleScene::PROG_GAMESTART: {
            if (pProg->isJustChanged()) {
            }
            if (pProg->hasArrivedAt(90)) {
                throwEventUpperTree(EVENT_GAMESTART);      //�X�^�[�g�łɏI���C�x���g
                pProg->change(GameTitleScene::PROG_FINISH); //�^�C�g���V�[���I����
            }
            //�_��
            if (pProg->getFrame() % 10U < 5 ) {
                pLabel02_->update(PX_C(700), PX_C(200), "READY GO!");
            } else {
                pLabel02_->update(PX_C(700), PX_C(200), "");
            }
            break;
        }

        case GameTitleScene::PROG_FINISH: {
            if (pProg->isJustChanged()) {
                pMenu_->sinkMe();
//                fadeoutSceneWithBgmTree(FADE_FRAMES);
//                inactivateDelay(FADE_FRAMES);
            }
            //�����܂��҂��ڂ������[�v
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