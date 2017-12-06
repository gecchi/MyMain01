#include "GameScene.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearTreeRounder.hpp"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameBeginningScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameDemoScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameEndingScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameOverScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GamePreTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/PreDrawScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) ,
pCommonScene_(nullptr),
pMyShipScene_(nullptr),
pStageWorld_(nullptr) {

    _class_name = "GameScene";
    useProgress(PROG_BANPEI);
    pCommonScene_ = NEW CommonScene("Common");
    pCommonScene_->inactivate();
    addSubLast(pCommonScene_);
    pMyShipScene_ = NEW MyShipScene("MyShipScene");
    pMyShipScene_->inactivate();
    addSubLast(pMyShipScene_);
    pStageWorld_ = new StageWorld("StageWorld");
    pStageWorld_->inactivate();
    addSubLast(pStageWorld_);

    pMenuBoardPause_ = NEW MenuBoardPause("MenuBoardPause");
    bringSceneMediator()->addSubGroup(pMenuBoardPause_);

    addSubLast(NEW GamePreTitleScene("PreGameTitle"));
    addSubLast(NEW GameTitleScene("GameTitle"));
    addSubLast(NEW GameDemoScene("GameDemo"));
    addSubLast(NEW GameBeginningScene("GameBeginning"));
    addSubLast(NEW GameMainScene("GameMain"));
    addSubLast(NEW GameEndingScene("GameEnding"));
    addSubLast(NEW GameOverScene("GameOver"));
    getProgress()->relateSubScene(PROG_PRE_TITLE, PROG_GAME_OVER,  "PreGameTitle");
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    getConductor()->ready(BGM_DEMO, "OGG_BGM_DEMO");
}

void GameScene::initialize() {
    _TRACE_(FUNC_NAME<<" �����܂���DemoScene����");
}

void GameScene::onReset() {
    VB_UI->clear();
    pGOD->setVB(VB_UI);
    DefaultScene* pSubScene;
    SceneProgress* pProg = getProgress();
    for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); ++it) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->fadeinScene(0);
            pSubScene->inactivate();
        }
    }
    pGOD->getSpacetime()->resetCamWorker();
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
    if (VB->isPushedDown(VB_UI_DEBUG) || GgafDxInput::isPushedDownKey(DIK_Q)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
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
                World* pWorld = pSpacetime->getWorld();
                pWorld->pPreDrawScene_->inactivateTree();
                pWorld->pPreDrawScene_->pauseTree();
                getConductor()->stop();
            }
            break;
        }

        case PROG_PRE_TITLE: {
            //##########  �^�C�g���O���o  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_PRE_TITLE)");
                getConductor()->performFromTheBegining(BGM_DEMO);
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
                getConductor()->fadeoutStopAll(120);
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
                    pSpacetime->undoCameraWork();
                }

                //�ʏ�i�s�������̓R�R
                //
#ifdef MY_DEBUG
                if (VB->isPushedDown(VB_PAUSE) || GgafDxInput::isPushedDownKey(DIK_ESCAPE) || is_frame_advance_) {
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
                    GgafDxInput::updateMouseState();
                    GgafDxInput::updateMouseState(); //�}�E�X���W�̑��΍��W��0�Ƀ��Z�b�g���邽��
                                                     //�A���Q��Ăяo��
                    pSpacetime->changeCameraWork("PauseCamWorker");
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
                DefaultScene* pSubScene;
                for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); ++it) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneWithBgmTree(FADE_FRAMES);
                        pSubScene->inactivateDelay(FADE_FRAMES+10);
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
        addSubLast(pMYSHIP_SCENE->extract());
        addSubLast(pCOMMON_SCENE->extract());
        pMYSHIP_SCENE->moveFirst();
        pCOMMON_SCENE->moveFirst();
        //moveFirst()���闝�R�́A����͖����m�[�h����s���邽�߁B
        //���CommonScene���������Ȃ��悤�ɂ��邽�߁B
        //GgafCore::template<class T> GgafNode<T>::~GgafNode() �̃R�����g���Q��
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
        getConductor()->fadeoutStopAll(120);

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
            getConductor()->fadeoutStopAll(120);
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

        OctreeRounder* pHitCheckRounder = pGOD->getSpacetime()->getLinearOctreeHitCheckRounder();
#ifdef MY_DEBUG
        if (GgafDxInput::isPushedDownKey(DIK_I)) {
            pGOD->getSpacetime()->getLinearOctree()->putTree();
        }
#endif
        //�����؃A���S���Y���Ńq�b�g�`�F�b�N
        pHitCheckRounder->executeAll(
            KIND_CHIKEI,
            KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT
        );
        pHitCheckRounder->executeAll(
            KIND_ITEM,
            KIND_MY_BODY_CHIKEI_HIT
        );
        pHitCheckRounder->executeAll(
            KIND_MY,
            KIND_ENEMY_BODY
        );
        pHitCheckRounder->executeAll(
            KIND_ENEMY_SHOT,
            KIND_MY_BODY
        );


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
