#include "GameScene.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/core/util/LinearOctree.h"
#include "jp/ggaf/core/util/LinearTreeRounder.hpp"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/God.h"
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

    appendChild(NEW GamePreTitleScene("PreGameTitle"));
    appendChild(NEW GameTitleScene("GameTitle"));
    appendChild(NEW GameDemoScene("GameDemo"));
    appendChild(NEW GameBeginningScene("GameBeginning"));
    appendChild(NEW GameMainScene("GameMain"));
    appendChild(NEW GameEndingScene("GameEnding"));
    appendChild(NEW GameOverScene("GameOver"));
    getProgress()->relateChildScene(PROG_PRE_TITLE, PROG_GAME_OVER,  "PreGameTitle");
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    getBgmConductor()->ready(BGM_DEMO, "BGM_DEMO");
    pHitCheckRounder_ = nullptr;
}

void GameScene::initialize() {
    _TRACE_(FUNC_NAME<<" �����܂���DemoScene����");
    pHitCheckRounder_ = pGOD->getSpacetime()->getLinearOctreeHitCheckRounder();
}

void GameScene::onReset() {
    VB_UI->clear();
    pGOD->setVB(VB_UI);
    DefaultScene* pChildScene;
    SceneProgress* pProg = getProgress();
    for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); ++it) {
        pChildScene = it->second;
        if (pChildScene) {
            pChildScene->resetTree();
            pChildScene->fadeinScene(0);
            pChildScene->inactivate();
        }
    }
    pGOD->getSpacetime()->getCameraWorkerChanger()->cleanCamWorker();
    G_RANK = 0.0;
    G_RANKUP_LEVEL = 0;
    G_SCORE = 0;
    pProg->reset(PROG_INIT);
}

void GameScene::onActive() {
}

void GameScene::processBehavior() {
    Spacetime* pSpacetime = pGOD->getSpacetime();
#ifdef MY_DEBUG
    //���C���t���[���\���ؑ�
    if (VB->isPushedDown(VB_UI_DEBUG) || GgafDx::Input::isPushedDownKey(DIK_Q)) {
        if (GgafDx::God::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDx::God::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDx::God::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif
    SceneProgress* pProg = getProgress();
    switch (pProg->getFromProgOnChange()) {
        case PROG_MAIN: {
            _TRACE_(FUNC_NAME<<" Prog has Just Changed 'From' PROG_MAIN");
            VB_UI->clear();
            pGOD->setVB(VB_UI);  //���ɖ߂�
            break;
        }

        default: {
            break;
        }
    }


    switch (pProg->get()) {
        case PROG_INIT: {
//            _TRACE_(FUNC_NAME<<" Prog(=PROG_INIT) has Just Changed");
            //pGOD->syncTimeFrame(); //�`��𒆎~���āA�t���[���Ǝ��Ԃ̓������s��
            if ((pProg->hasArrivedAt(120))) {
                _TRACE_("pGOD->_fps = "<<pGOD->_fps);
                pProg->changeWithSceneCrossfading(PROG_PRE_TITLE);
                getBgmConductor()->stop();
            }
            break;
        }

        case PROG_PRE_TITLE: {
            //##########  �^�C�g���O���o  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_PRE_TITLE)");
                getBgmConductor()->performFromTheBegining(BGM_DEMO);
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                pProg->changeWithSceneFlipping(PROG_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH �C�x���g��t
            break;
        }

        case PROG_TITLE: {
            //##########  �^�C�g��  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_TITLE)");
            }
            //�C�x���g�҂� EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case PROG_DEMO: {
            //##########  �f��  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_DEMO)");
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                pProg->changeWithSceneFlipping(PROG_TITLE);
            }

            //������ EVENT_GAMEDEMOSCENE_FINISH �C�x���g��t
            break;
        }

        case PROG_BEGINNING: {
            //##########  �Q�[���J�n�i���[�h�I�𓙁j  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_BEGINNING)");
                getBgmConductor()->fadeoutStopAll(120);
            }
            //�C�x���g�҂� EVENT_GAMEMODE_DECIDE
            break;
        }

        case PROG_MAIN: {
            //##########  �Q�[�����C��  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_MAIN)");
                VB_PLAY->clear();
                pGOD->setVB(VB_PLAY); //�v���C�p�ɕύX
            }

            //���|�[�Y�ł͂Ȃ���
            if (!pProg->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_)  {
                    //���t���[���|�[�Y�ł͂Ȃ��A���O�t���[���|�[�Y�̏ꍇ�B
                    //�|�[�Y��������ŏ��̃t���[�������̓R�R��
                    pSpacetime->getCameraWorkerChanger()->undoCameraWork();
                }

                //�ʏ�i�s�������̓R�R
                //
#ifdef MY_DEBUG
                if (VB->isPushedDown(VB_PAUSE) || GgafDx::Input::isPushedDownKey(DIK_ESCAPE) || is_frame_advance_) {
                    //�|�[�Y�ł͂Ȃ��Ƃ��ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    pauseGame();
                }
#else
                if (VB->isPushedDown(VB_PAUSE) || is_frame_advance_) {
                    //�|�[�Y�ł͂Ȃ��Ƃ��ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    pauseGame();
                }
#endif
            }
            //���|�[�Y��
            if (pProg->getGazedScene()->wasPaused()) {
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
                    pGOD->setVB(VB_PLAY);
                    pProg->getGazedScene()->unpauseTree();//�|�[�Y�����I�I
                }
            }
            //�C�x���g�҂� EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case PROG_ENDING: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_ENDING)");
            }
            break;
        }

        case PROG_GAME_OVER: {
            //##########  �Q�[���I�[�o�[  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_GAME_OVER)");
            }
            //�C�x���g�҂� EVENT_GAME_OVER_FINISH
            break;
        }

        case PROG_FINISH: {
            //##########  �Q�[���V�[���I��  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_FINISH)");
                DefaultScene* pChildScene;
                for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); ++it) {
                    pChildScene = it->second;
                    if (pChildScene) {
                        pChildScene->fadeoutSceneWithBgmTree(FADE_FRAMES);
                        pChildScene->inactivateDelay(FADE_FRAMES+10);
                    }
                }
            }
            if (pProg->hasArrivedAt(FADE_FRAMES+20)) {
                reset(); //���Z�b�g�i�ŏ��̐i����Ԃɖ߂�j
            }
            break;
        }

        default: {
            break;
        }
    }

    DefaultScene* pGazed = pProg->getGazedScene();
    if (pGazed) {
        was_paused_flg_GameMainScene_prev_frame_ = pGazed->wasPaused();
    }

}

void GameScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
//    switch (prm_no) {
//        case EVENT_GOD_WILL_DEMISE:
//
//            break;
//        default:
//            break;
//    }
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_GOD_WILL_DEMISE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GOD_WILL_DEMISE) CommonScene���E���グ�Č�ɉ�������悤�ɂ��܂��B");
        //�_������ł��܂��O��
        //CommonScene���E���グ�A�����������ɂȂ�悤�ɑ��삷��B(���L�f�|�W�g���Ƃ����邵)
        appendChild(pMYSHIP_SCENE->extract());
        appendChild(pCOMMON_SCENE->extract());
        pMYSHIP_SCENE->moveFirst();
        pCOMMON_SCENE->moveFirst();
        //moveFirst()���闝�R�́A����͖����m�[�h����s���邽�߁B
        //���CommonScene���������Ȃ��悤�ɂ��邽�߁B
        //template<class T> GgafCore::Node<T>::~GgafCore::Node() �̃R�����g���Q��
    } else if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //�v���^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        pProg->changeWithSceneFlipping(PROG_TITLE); //�^�C�g����

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //�^�C�g���V�[�����{�[���ƌ��Ă��̂Ŏ��Ԑ؂�I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        pProg->changeWithSceneCrossfading(PROG_DEMO); //�f����

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //�f���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        pProg->changeWithSceneFadeoutFadein(PROG_INIT,120,120); //�ŏ���
        getBgmConductor()->fadeoutStopAll(120);

    } else if (prm_no == EVENT_GAMESTART) {
        //�X�^�[�g
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        pProg->changeWithSceneCrossfading(PROG_BEGINNING); //�I�[�v�j���O�i�Q�[�����[�h�Z���N�g�j��

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //�Q�[�����[�h�Z���N�g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        pProg->changeWithSceneCrossfading(PROG_MAIN,600);//���C����
    } else if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        if (pProg->get() == PROG_DEMO) {
            //����������A�f���V�[�����̑S�@���łȂ�΁A�f���V�[���I��
            pProg->changeWithSceneFadeoutFadein(PROG_INIT, 120, 120); //�ŏ���
            getBgmConductor()->fadeoutStopAll(120);
        } else {
            pProg->changeWithSceneCrossfading(PROG_GAME_OVER); //�Q�[���I�[�o�[��
        }
    } else if (prm_no == EVENT_GAMEOVERSCENE_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEOVERSCENE_FINISH)");
        pProg->change(PROG_FINISH);
    } else if (prm_no == EVENT_GO_TO_TITLE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GO_TO_TITLE)");
        _TRACE_("UNPAUSE!(because EVENT_GO_TO_TITLE)");
        pGOD->setVB(VB_PLAY);
        pProg->getGazedScene()->unpauseTree();//�|�[�Y�����I�I
        pProg->change(PROG_FINISH);
    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
#ifdef MY_DEBUG
        CollisionChecker::_num_check = 0;
#endif
        //�{�V�[���̏����V�[���̏����A�N�^�[�S�Ăɂ��ē����蔻��`�F�b�N���s���B
        //��ԕ���(������)�A���S���Y���ɂ��A�`�F�b�N�񐔂̍œK�����s���Ă��܂��B
        //�ڍׂ� �u��ʑ��֒�`�R�s�y�c�[��.xls�v �� �u��ʑ��ցv �V�[�g�Q��

        OctreeRounder* pHitCheckRounder = pHitCheckRounder_;
#ifdef MY_DEBUG
        if (GgafDx::Input::isPushedDownKey(DIK_I)) {
            pGOD->getSpacetime()->getLinearOctree()->putTree();
        }
#endif
        //�����؃A���S���Y���Ńq�b�g�`�F�b�N
        static const kind_t group_A1 = KIND_CHIKEI;
        static const kind_t group_B1 = KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT;
        pHitCheckRounder->executeAll(group_A1, group_B1);

        static const kind_t group_A2 = KIND_ITEM;
        static const kind_t group_B2 = KIND_MY_BODY_CHIKEI_HIT;
        pHitCheckRounder->executeAll(group_A2, group_B2);

        static const kind_t group_A3 = KIND_MY;
        static const kind_t group_B3 = KIND_ENEMY_BODY;
        pHitCheckRounder->executeAll(group_A3, group_B3);

        static const kind_t group_A4 = KIND_ENEMY_SHOT;
        static const kind_t group_B4 = KIND_MY_BODY;
        pHitCheckRounder->executeAll(group_A4, group_B4);
    }
}
void GameScene::pauseGame() {
    is_frame_advance_ = false;
    _TRACE_("PAUSE!");
    pGOD->setVB(VB_UI);  //���͂͂t�h�ɐ؂�ւ�
    getProgress()->getGazedScene()->pauseTree(); //�|�[�Y�I�I
    pMenuBoardPause_->rise(PX_C(100), PX_C(20));
}

GameScene::~GameScene() {
}
