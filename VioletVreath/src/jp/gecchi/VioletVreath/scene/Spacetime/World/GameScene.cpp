#include "GameScene.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "PreDrawScene.h"
#include "GameScene/CommonScene.h"
#include "GameScene/GameBeginningScene.h"
#include "GameScene/GameDemoScene.h"
#include "GameScene/GameEndingScene.h"
#include "GameScene/GameMainScene.h"
#include "GameScene/GameMainScene/StageWorld.h"
#include "GameScene/GameOverScene.h"
#include "GameScene/GamePreTitleScene.h"
#include "GameScene/GameTitleScene.h"
#include "GameScene/MyShipScene.h"


using namespace GgafLib;
using namespace VioletVreath;

GameScene::GameScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) ,
pCommonScene_(nullptr),
pMyShipScene_(nullptr),
pStageWorld_(nullptr) {

    _class_name = "GameScene";
    pCommonScene_ = NEW CommonScene("Common");
    pCommonScene_->inactivate();
    appendChild(pCommonScene_);
    pMyShipScene_ = NEW MyShipScene("MyShipScene");
    pMyShipScene_->inactivate();
    appendChild(pMyShipScene_);
    pStageWorld_ = new StageWorld("StageWorld");
    pStageWorld_->inactivate();
    appendChild(pStageWorld_);

    pMenuBoardPause_ = NEW MenuBoardPause("MenuBoardPause");
    bringSceneMediator()->appendGroupChild(pMenuBoardPause_);

    appendChild(NEW GamePreTitleScene("PreGameTitle"));   //PHASE_PRE_TITLE
    appendChild(NEW GameTitleScene("GameTitle"));         //PHASE_TITLE
    appendChild(NEW GameDemoScene("GameDemo"));           //PHASE_DEMO
    appendChild(NEW GameBeginningScene("GameBeginning")); //PHASE_BEGINNING
    appendChild(NEW GameMainScene("GameMain"));           //PHASE_MAIN
    appendChild(NEW GameEndingScene("GameEnding"));       //PHASE_ENDING
    appendChild(NEW GameOverScene("GameOver"));           //PHASE_GAME_OVER
    getPhase()->relateChildScene(PHASE_PRE_TITLE, PHASE_GAME_OVER,  "PreGameTitle");
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    getBgmConductor()->ready(BGM_DEMO, "BGM_DEMO");
}

void GameScene::initialize() {
    _TRACE_(FUNC_NAME<<" �����܂���DemoScene����");
}

void GameScene::onReset() {
    VV_VB_UI->clear();
    pCARETAKER->setVB(VV_VB_UI);
    DefaultScene* pChildScene;
    ScenePhase* pPhase = getPhase();
    for (PhaseSceneMap::const_iterator it = pPhase->_mapPhase2Scene.begin(); it != pPhase->_mapPhase2Scene.end(); ++it) {
        pChildScene = it->second;
        if (pChildScene) {
            pChildScene->resetTree();
            pChildScene->fadeinScene(0);
            pChildScene->inactivate();
        }
    }
    pCARETAKER->getSpacetime()->getCameraWorkerChanger()->cleanCamWorker();
    G_RANK = 0.0;
    G_RANKUP_LEVEL = 0;
    G_SCORE = 0;
    pPhase->reset(PHASE_INIT);
}

void GameScene::onActive() {
}

void GameScene::processBehavior() {
    Spacetime* pSpacetime = pCARETAKER->getSpacetime();
#ifdef MY_DEBUG
    //���C���t���[���\���ؑ�
    if (VVB->isPushedDown(0, VV_VB_UI_DEBUG) || GgafDx::Input::isPushedDownKey(DIK_Q)) {
        if (pCARETAKER->_d3dfillmode == D3DFILL_SOLID && pCARETAKER->_draw_hit_area_kind == 0) {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
            pCARETAKER->_draw_hit_area_kind = 1;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME && pCARETAKER->_draw_hit_area_kind == 1) {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
            pCARETAKER->_draw_hit_area_kind = 2;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME && pCARETAKER->_draw_hit_area_kind == 2) {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
            pCARETAKER->_draw_hit_area_kind = 0;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME && pCARETAKER->_draw_hit_area_kind == 0) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
            pCARETAKER->_draw_hit_area_kind = 1;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_SOLID && pCARETAKER->_draw_hit_area_kind == 1) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
            pCARETAKER->_draw_hit_area_kind = 2;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_SOLID && pCARETAKER->_draw_hit_area_kind == 2) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
            pCARETAKER->_draw_hit_area_kind = 0;
        }
    }
#endif
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getPrevWhenChanged()) {
        case PHASE_MAIN: {
            _TRACE_(FUNC_NAME<<" Phase has Just Changed 'From' PHASE_MAIN");
            VV_VB_UI->clear();
            pCARETAKER->setVB(VV_VB_UI);  //���ɖ߂�
            break;
        }

        default: {
            break;
        }
    }


    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
//            _TRACE_(FUNC_NAME<<" Phase(=PHASE_INIT) has Just Changed");
            //pCARETAKER->syncTimeFrame(); //�`��𒆎~���āA�t���[���Ǝ��Ԃ̓������s��
            if ((pPhase->hasArrivedFrameAt(120))) {
                _TRACE_("pCARETAKER->_fps = "<<pCARETAKER->_fps);
                pPhase->changeWithSceneCrossfading(PHASE_PRE_TITLE);
                getBgmConductor()->stop();
            }
            break;
        }

        case PHASE_PRE_TITLE: {
            //##########  �^�C�g���O���o  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_PRE_TITLE)");
                getBgmConductor()->performFromTheBegining(BGM_DEMO);
            }
            //VV_VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VVB->isPushedDown(0, VV_VB_UI_EXECUTE)) { //skip
                pPhase->changeWithSceneFlipping(PHASE_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH �C�x���g��t
            break;
        }

        case PHASE_TITLE: {
            //##########  �^�C�g��  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_TITLE)");
            }
            //�C�x���g�҂� EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case PHASE_DEMO: {
            //##########  �f��  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_DEMO)");
            }
            //VV_VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VVB->isPushedDown(0, VV_VB_UI_EXECUTE)) {
                pPhase->changeWithSceneFlipping(PHASE_TITLE);
            }

            //������ EVENT_GAMEDEMOSCENE_FINISH �C�x���g��t
            break;
        }

        case PHASE_BEGINNING: {
            //##########  �Q�[���J�n�i���[�h�I�𓙁j  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_BEGINNING)");
                getBgmConductor()->fadeoutStopAll(120);
            }
            //�C�x���g�҂� EVENT_GAMEMODE_DECIDE
            break;
        }

        case PHASE_MAIN: {
            //##########  �Q�[�����C��  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_MAIN)");
                VV_VB_PLAY->clear();
                pCARETAKER->setVB(VV_VB_PLAY); //�v���C�p�ɕύX
            }

            //���|�[�Y�ł͂Ȃ���
            if (!pPhase->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_)  {
                    //���t���[���|�[�Y�ł͂Ȃ��A���O�t���[���|�[�Y�̏ꍇ�B
                    //�|�[�Y��������ŏ��̃t���[�������̓R�R��
                    pSpacetime->getCameraWorkerChanger()->undoCameraWork();
                }

                //�ʏ�i�s�������̓R�R
                //
#ifdef MY_DEBUG
                if (VVB->isPushedDown(0, VV_VB_PAUSE) || GgafDx::Input::isPushedDownKey(DIK_ESCAPE) || is_frame_advance_) {
                    //�|�[�Y�ł͂Ȃ��Ƃ��ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    pauseGame();
                }
#else
                if (VVB->isPushedDown(0, VV_VB_PAUSE) || is_frame_advance_) {
                    //�|�[�Y�ł͂Ȃ��Ƃ��ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    pauseGame();
                }
#endif
            }
            //���|�[�Y��
            if (pPhase->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_ == false) {
                    //���t���[���|�[�Y�ŁA�O�t���[���|�[�Y�ł͂Ȃ��ꍇ
                    //�|�[�Y������́A�ŏ��̃t���[�������̓R�R��
                    GgafDx::Input::updateMouseState();
                    GgafDx::Input::updateMouseState(); //�}�E�X���W�̑��΍��W��0�Ƀ��Z�b�g���邽��
                                                     //�A���Q��Ăяo��
                    pSpacetime->getCameraWorkerChanger()->changeCameraWork("PauseCamWorker");
                }

                //�|�[�Y�i�s�������̓R�R
                //

                if (pMenuBoardPause_->hasJustSunk() || is_frame_advance_) {
                    //�|�[�Y���ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    _TRACE_("UNPAUSE!");
                    pCARETAKER->setVB(VV_VB_PLAY);
                    pPhase->getGazedScene()->unpause();//�|�[�Y�����I�I
                }
            }
            //�C�x���g�҂� EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case PHASE_ENDING: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_ENDING)");
            }
            break;
        }

        case PHASE_GAME_OVER: {
            //##########  �Q�[���I�[�o�[  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_GAME_OVER)");
            }
            //�C�x���g�҂� EVENT_GAME_OVER_FINISH
            break;
        }

        case PHASE_FINISH: {
            //##########  �Q�[���V�[���I��  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_FINISH)");
                DefaultScene* pChildScene;
                for (PhaseSceneMap::const_iterator it = pPhase->_mapPhase2Scene.begin(); it != pPhase->_mapPhase2Scene.end(); ++it) {
                    pChildScene = it->second;
                    if (pChildScene) {
                        pChildScene->fadeoutSceneWithBgmTree(FADE_FRAMES);
                        pChildScene->inactivateDelay(FADE_FRAMES+10);
                    }
                }
            }
            if (pPhase->hasArrivedFrameAt(FADE_FRAMES+20)) {
                reset(); //���Z�b�g�i�ŏ��̃t�F�[�Y�ɖ߂�j
            }
            break;
        }

        default: {
            break;
        }
    }

    DefaultScene* pGazed = pPhase->getGazedScene();
    if (pGazed) {
        was_paused_flg_GameMainScene_prev_frame_ = pGazed->wasPaused();
    }

}

void GameScene::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
//    switch (prm_event_val) {
//        case EVENT_CARETAKER_WILL_DEMISE:
//
//            break;
//        default:
//            break;
//    }
    ScenePhase* pPhase = getPhase();
    if (prm_event_val == EVENT_CARETAKER_WILL_DEMISE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_CARETAKER_WILL_DEMISE) CommonScene���E���グ�Č�ɉ�������悤�ɂ��܂��B");
        //�Ǘ��҂�����ł��܂��O��
        //CommonScene���E���グ�A�����������ɂȂ�悤�ɑ��삷��B(���L�f�|�W�g���Ƃ����邵)
        appendChild(pMYSHIP_SCENE->extract());
        appendChild(pCOMMON_SCENE->extract());
        pMYSHIP_SCENE->moveFirst();
        pCOMMON_SCENE->moveFirst();
        //moveFirst()���闝�R�́A����͖����m�[�h����s���邽�߁B
        //���CommonScene���������Ȃ��悤�ɂ��邽�߁B
        //template<class T> GgafCore::Node<T>::~GgafCore::Node() �̃R�����g���Q��
    } else if (prm_event_val == EVENT_PREGAMETITLESCENE_FINISH) {
        //�v���^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        pPhase->changeWithSceneFlipping(PHASE_TITLE); //�^�C�g����

    } else if (prm_event_val == EVENT_GAMETITLESCENE_FINISH) {
        //�^�C�g���V�[�����{�[���ƌ��Ă��̂Ŏ��Ԑ؂�I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        pPhase->changeWithSceneCrossfading(PHASE_DEMO); //�f����

    } else if (prm_event_val == EVENT_GAMEDEMOSCENE_FINISH) {
        //�f���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        pPhase->changeWithSceneFadeoutFadein(PHASE_INIT,120,120); //�ŏ���
        getBgmConductor()->fadeoutStopAll(120);

    } else if (prm_event_val == EVENT_GAMESTART) {
        //�X�^�[�g
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        pPhase->changeWithSceneCrossfading(PHASE_BEGINNING); //�I�[�v�j���O�i�Q�[�����[�h�Z���N�g�j��

    } else if (prm_event_val == EVENT_GAMEMODE_DECIDE) {
        //�Q�[�����[�h�Z���N�g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        pPhase->changeWithSceneCrossfading(PHASE_MAIN,600);//���C����
    } else if (prm_event_val == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        if (pPhase->getCurrent() == PHASE_DEMO) {
            //����������A�f���V�[�����̑S�@���łȂ�΁A�f���V�[���I��
            pPhase->changeWithSceneFadeoutFadein(PHASE_INIT, 120, 120); //�ŏ���
            getBgmConductor()->fadeoutStopAll(120);
        } else {
            pPhase->changeWithSceneCrossfading(PHASE_GAME_OVER); //�Q�[���I�[�o�[��
        }
    } else if (prm_event_val == EVENT_GAMEOVERSCENE_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEOVERSCENE_FINISH)");
        pPhase->change(PHASE_FINISH);
    } else if (prm_event_val == EVENT_GO_TO_TITLE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GO_TO_TITLE)");
        _TRACE_("UNPAUSE!(because EVENT_GO_TO_TITLE)");
        pCARETAKER->setVB(VV_VB_PLAY);
        pPhase->getGazedScene()->unpause();//�|�[�Y�����I�I
        pPhase->change(PHASE_FINISH);
    }
}


void GameScene::processJudgement() {

}
void GameScene::pauseGame() {
    is_frame_advance_ = false;
    _TRACE_("PAUSE!");
    pCARETAKER->setVB(VV_VB_UI);  //���͂͂t�h�ɐ؂�ւ�
    getPhase()->getGazedScene()->pause(); //�|�[�Y�I�I
    pMenuBoardPause_->rise(PX_C(100), PX_C(20));
}

GameScene::~GameScene() {
}
