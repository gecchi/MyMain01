#include "GameScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameBeginningScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameDemoScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameEndingScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameOverScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GamePreTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/PreDrawScene.h"
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
    useProgress(GameScene::PROG_BANPEI-1);
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
    getSceneDirector()->addSubGroup(pMenuBoardPause_);

    addSubLast(NEW GamePreTitleScene("PreGameTitle"));
    addSubLast(NEW GameTitleScene("GameTitle"));
    addSubLast(NEW GameDemoScene("GameDemo"));
    addSubLast(NEW GameBeginningScene("GameBeginning"));
    addSubLast(NEW GameMainScene("GameMain"));
    addSubLast(NEW GameEndingScene("GameEnding"));
    addSubLast(NEW GameOverScene("GameOver"));

    getProgress()->relateSubScene(GameScene::PROG_PRE_TITLE, GameScene::PROG_GAME_OVER,  "PreGameTitle");
    //���܂�
    //addSubLast(NEW TamagoScene("TamagoScene"));
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    getBGMer()->ready(0, "OGG_BGM_DEMO");
}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() �����܂���DemoScene����");
}

void GameScene::onReset() {
    VB_UI->clear();
    P_GOD->setVB(VB_UI);
    DefaultScene* pSubScene;
    SceneProgress* pProg = getProgress();
    for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); it++) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->fadeinSceneTree(0);
            pSubScene->inactivate();
        }
    }
    P_UNIVERSE->resetCamWorker();
    G_RANK = 0.0;
    G_RANKUP_LEVEL = 0;
    G_SCORE = 0;
    pProg->reset(GameScene::PROG_INIT);
}

void GameScene::onActive() {
}

void GameScene::processBehavior() {

#ifdef MY_DEBUG
    //���C���t���[���\���ؑ�
    if (VB->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif
    SceneProgress* pProg = getProgress();
    switch (pProg->getFromProgOnChange()) {
        case GameScene::PROG_MAIN: {
            _TRACE_("GameScene::processBehavior() Prog has Just Changed 'From' GameScene::PROG_MAIN");
            VB_UI->clear();
            P_GOD->setVB(VB_UI);  //���ɖ߂�
            break;
        }

        default: {
            break;
        }
    }


    switch (pProg->get()) {
        case GameScene::PROG_INIT: {
//            _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_INIT) has Just Changed");
            //P_GOD->syncTimeFrame(); //�`��𒆎~���āA�t���[���Ǝ��Ԃ̓������s��
            if ((pProg->getFrameInProgress() == 120)) {
                _TRACE_("P_GOD->_fps = "<<P_GOD->_fps);
                pProg->changeWithSceneCrossfading(GameScene::PROG_PRE_TITLE);
                P_WORLD->pPreDrawScene_->inactivateTreeImmed();
                P_WORLD->pPreDrawScene_->pauseTreeImmed();
                getBGMer()->stop();
            }
            break;
        }

        case GameScene::PROG_PRE_TITLE: {
            //##########  �^�C�g���O���o  ##########
            if (pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_PRE_TITLE)");
                getBGMer()->play_fadein(0);
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                pProg->changeWithSceneFlipping(GameScene::PROG_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH �C�x���g��t
            break;
        }

        case GameScene::PROG_TITLE: {
            //##########  �^�C�g��  ##########
            if (pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_TITLE)");
            }
            //�C�x���g�҂� EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case GameScene::PROG_DEMO: {
            //##########  �f��  ##########
            if (pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_DEMO)");
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                pProg->changeWithSceneFlipping(GameScene::PROG_TITLE);
            }

            //������ EVENT_GAMEDEMOSCENE_FINISH �C�x���g��t
            break;
        }

        case GameScene::PROG_BEGINNING: {
            //##########  �Q�[���J�n�i���[�h�I�𓙁j  ##########
            if (pProg->isJustChanged()) {
                getBGMer()->fadeout_stop();
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_BEGINNING)");
            }
            //�C�x���g�҂� EVENT_GAMEMODE_DECIDE
            break;
        }

        case GameScene::PROG_MAIN: {
            //##########  �Q�[�����C��  ##########
            if (pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_MAIN)");
                VB_PLAY->clear();
                P_GOD->setVB(VB_PLAY); //�v���C�p�ɕύX
            }

            //���|�[�Y�ł͂Ȃ���
            if (!pProg->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_)  {
                    //���t���[���|�[�Y�ł͂Ȃ��A���O�t���[���|�[�Y�̏ꍇ�B
                    //�|�[�Y��������ŏ��̃t���[�������̓R�R��
                    P_UNIVERSE->undoCameraWork();
                }

                //�ʏ�i�s�������̓R�R
                //

                if (VB->isPushedDown(VB_PAUSE) || is_frame_advance_) {
                    //�|�[�Y�ł͂Ȃ��Ƃ��ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    is_frame_advance_ = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //���͂͂t�h�ɐ؂�ւ�
                    pProg->getGazedScene()->pauseTree(); //�|�[�Y�I�I
                    pMenuBoardPause_->rise(PX_C(100), PX_C(20));
                }
            }
            //���|�[�Y��
            if (pProg->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_ == false) {
                    //���t���[���|�[�Y�ŁA�O�t���[���|�[�Y�ł͂Ȃ��ꍇ
                    //�|�[�Y������́A�ŏ��̃t���[�������̓R�R��
                    GgafDxInput::updateMouseState();
                    GgafDxInput::updateMouseState(); //�}�E�X���W�̑��΍��W��0�Ƀ��Z�b�g���邽��
                                                     //�A���Q��Ăяo��
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }

                //�|�[�Y�i�s�������̓R�R
                //

                if (pMenuBoardPause_->isJustSunk() || is_frame_advance_) {
                    //�|�[�Y���ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    _TRACE_("UNPAUSE!");
                    P_GOD->setVB(VB_PLAY);
                    pProg->getGazedScene()->unpauseTree();//�|�[�Y�����I�I
                }
            }
            //�C�x���g�҂� EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case GameScene::PROG_ENDING: {
            if (pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_ENDING)");
            }
            break;
        }

        case GameScene::PROG_GAME_OVER: {
            //##########  �Q�[���I�[�o�[  ##########
            if (pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_GAME_OVER)");
            }
            //�C�x���g�҂� EVENT_GAME_OVER_FINISH
            break;
        }

        case GameScene::PROG_FINISH: {
            //##########  �Q�[���V�[���I��  ##########
            if (pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_FINISH)");
                DefaultScene* pSubScene;
                for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); it++) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneWithBgmTree(FADE_FRAMES);
                        pSubScene->inactivateDelay(FADE_FRAMES);
                    }
                }
            }
            if (pProg->getFrameInProgress() == FADE_FRAMES+10) {
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
//        case EVENT_GOD_WILL_DIE:
//
//            break;
//        default:
//            break;
//    }
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_GOD_WILL_DIE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GOD_WILL_DIE) CommonScene���E���グ�Č�ɉ�������悤�ɂ��܂��B");
        //�_������ł��܂��O��
        //CommonScene���E���グ�A�����������ɂȂ�悤�ɑ��삷��B(���L�f�|�W�g���Ƃ����邵)
        addSubLast(P_MYSHIP_SCENE->extract());
        addSubLast(P_COMMON_SCENE->extract());
        P_MYSHIP_SCENE->moveFirstImmed();
        P_COMMON_SCENE->moveFirstImmed();
        //moveFirstImmed()���闝�R�́A����͖����m�[�h����s���邽�߁B
        //���CommonScene���������Ȃ��悤�ɂ��邽�߁B
        //GgafCore::template<class T> GgafNode<T>::~GgafNode() �̃R�����g���Q��
    } else if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //�v���^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        pProg->changeWithSceneFlipping(GameScene::PROG_TITLE); //�^�C�g����

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //�^�C�g���V�[�����{�[���ƌ��Ă��̂Ŏ��Ԑ؂�I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        pProg->changeWithSceneCrossfading(GameScene::PROG_DEMO); //�f����

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //�f���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        pProg->changeWithSceneFadeoutFadein(GameScene::PROG_INIT,120,120); //�ŏ���
        getBGMer()->fadeout_stop();

    } else if (prm_no == EVENT_GAMESTART) {
        //�X�^�[�g
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        pProg->changeWithSceneCrossfading(GameScene::PROG_BEGINNING); //�I�[�v�j���O�i�Q�[�����[�h�Z���N�g�j��

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //�Q�[�����[�h�Z���N�g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        pProg->changeWithSceneCrossfading(GameScene::PROG_MAIN,600);//���C����
    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //�Ƃɂ����^�C�g���փC�x���g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        pProg->changeWithSceneFlipping(GameScene::PROG_TITLE); //�^�C�g����
    }


    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        pProg->changeWithSceneCrossfading(GameScene::PROG_GAME_OVER); //�Q�[���I�[�o�[��
    } else if (prm_no == EVENT_GAMEOVERSCENE_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEOVERSCENE_FINISH)");
        pProg->change(GameScene::PROG_FINISH);
    } else if (prm_no == EVENT_GO_TO_TITLE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GO_TO_TITLE)");
        _TRACE_("UNPAUSE!(because EVENT_GO_TO_TITLE)");
        P_GOD->setVB(VB_PLAY);
        pProg->getGazedScene()->unpauseTree();//�|�[�Y�����I�I
        pProg->change(GameScene::PROG_FINISH);
    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker3D::_num_check = 0;

//        if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//            CollisionChecker3D::_pLinearOctree->putTree();
//        }

        //�{�V�[���̏����V�[���̏����A�N�^�[�S�Ăɂ��ē����蔻��`�F�b�N���s���B
        //��ԕ���(������)�A���S���Y���ɂ��A�`�F�b�N�񐔂̍œK�����s���Ă��܂��B
        //�ڍׂ� �u��ʑ��֒�`�R�s�y�c�[��.xls�v �� �u��ʑ��ցv �V�[�g�Q��

        LinearOctreeForActor* pLinearOctree = P_UNIVERSE->getLinearOctree();

        //�����؃A���S���Y���Ńq�b�g�`�F�b�N
        pLinearOctree->executeAllHitChk(
            KIND_CHIKEI,
            KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT
        );
        pLinearOctree->executeAllHitChk(
            KIND_ITEM,
            KIND_MY_BODY_CHIKEI_HIT
        );
        pLinearOctree->executeAllHitChk(
            KIND_MY,
            KIND_ENEMY_BODY
        );
        pLinearOctree->executeAllHitChk(
            KIND_ENEMY_SHOT,
            KIND_MY_BODY
        );


    }
}

GameScene::~GameScene() {
}
