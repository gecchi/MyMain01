#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) ,
_pCommonScene(NULL),
_pMyShipScene(NULL),
_pStageWorld(NULL) {

    _class_name = "GameScene";
    useProgress(GameScene::PROG_FINISH);
    _pCommonScene = NEW CommonScene("Common");
    _pCommonScene->inactivateImmed();
    addSubLast(_pCommonScene);
    _pMyShipScene = NEW MyShipScene("MyShipScene");
    _pMyShipScene->inactivateImmed();
    addSubLast(_pMyShipScene);
    _pStageWorld = new StageWorld("StageWorld");
    _pStageWorld->inactivateImmed();
    addSubLast(_pStageWorld);

//    _pGamePauseScene = new GamePauseScene("GamePauseScene");
//    _pGamePauseScene->inactivateImmed();
//    addSubLast(_pGamePauseScene);
    _pMenuBoardPause = NEW MenuBoardPause("MenuBoardPause");
    getDirector()->addSubGroup(_pMenuBoardPause);

    addSubLast(NEW GamePreTitleScene("PreGameTitle"));
    addSubLast(NEW GameTitleScene("GameTitle"));
    addSubLast(NEW GameDemoScene("GameDemo"));
    addSubLast(NEW GameBeginningScene("GameBeginning"));
    addSubLast(NEW GameMainScene("GameMain"));
    addSubLast(NEW GameEndingScene("GameEnding"));
    addSubLast(NEW GameOverScene("GameOver"));

    _pProg->relatSubScene(GameScene::PROG_PRE_TITLE, GameScene::PROG_GAME_OVER,  "PreGameTitle");
    //���܂�
    //addSubLast(NEW TamagoScene("TamagoScene"));
    _is_frame_advance = false;

    _was_paused_flg_GameMainScene_prev_frame = false;

}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() �����܂���DemoScene����");
}

void GameScene::onReset() {

    VB_UI->clear();
    P_GOD->setVB(VB_UI);

    DefaultScene* pSubScene;
    for (map<progress, DefaultScene*>::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->fadeinSceneTree(0);
            pSubScene->inactivateImmed();
        }
    }
    P_UNIVERSE->resetCameraWork();
    GameGlobal::init();
    _pProg->set(GameScene::PROG_INIT);
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

    switch (_pProg->getPrev_WhenJustChanged()) {
        case GameScene::PROG_MAIN: {
            _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_MAIN) has just been Changed ");
            VB_UI->clear();
            P_GOD->setVB(VB_UI);  //���ɖ߂�
            break;
        }

        default:
            break;
    }


    switch (_pProg->get()) {
        case GameScene::PROG_INIT: {
//            _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_INIT) is Just Changed");
            //P_GOD->syncTimeFrame(); //�`��𒆎~���āA�t���[���Ǝ��Ԃ̓������s��
            if ((_pProg->getFrameInProgress() >= 180 && P_GOD->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) || GgafDxInput::isPushedDownKey(DIK_P)) {
                _TRACE_("P_GOD->_fps = "<<P_GOD->_fps);
                _pProg->changeWithScene_Crossfading(GameScene::PROG_PRE_TITLE);
            }
            break;
        }

        case GameScene::PROG_PRE_TITLE: {
            //##########  �^�C�g���O���o  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_PRE_TITLE) is Just Changed");
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                _pProg->changeWithScene_Flipping(GameScene::PROG_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH �C�x���g��t
            break;
        }

        case GameScene::PROG_TITLE: {
            //##########  �^�C�g��  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_TITLE) is Just Changed");
            }
            //�C�x���g�҂� EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case GameScene::PROG_DEMO: {
            //##########  �f��  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_DEMO) is Just Changed");
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _pProg->changeWithScene_Flipping(GameScene::PROG_TITLE);
            }

            //������ EVENT_GAMEDEMOSCENE_FINISH �C�x���g��t
            break;
        }

        case GameScene::PROG_BEGINNING: {
            //##########  �Q�[���J�n�i���[�h�I�𓙁j  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_BEGINNING) is Just Changed");
            }
            //�C�x���g�҂� EVENT_GAMEMODE_DECIDE
            break;
        }

        case GameScene::PROG_MAIN: {
            //##########  �Q�[�����C��  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_MAIN) is Just Changed");
                VB_PLAY->clear();
                P_GOD->setVB(VB_PLAY); //�v���C�p�ɕύX
            }

            //���|�[�Y�ł͂Ȃ���
            if (!_pProg->getGazeScene()->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == true)  {
                    //���t���[���|�[�Y�ł͂Ȃ��A���O�t���[���|�[�Y�̏ꍇ�B
                    //�|�[�Y��������ŏ��̃t���[�������̓R�R��
                    P_UNIVERSE->undoCameraWork();
                }

                //�ʏ�i�s�������̓R�R
                //

                if (VB->isPushedDown(VB_PAUSE) || _is_frame_advance) {
                    //�|�[�Y�ł͂Ȃ��Ƃ��ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    _is_frame_advance = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //���͂͂t�h�ɐ؂�ւ�
                    _pProg->getGazeScene()->pauseTree(); //�|�[�Y�I�I
                    _pMenuBoardPause->rise(PX2CO(100), PX2CO(20));
                }
            }
            //���|�[�Y��
            if (_pProg->getGazeScene()->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == false) {
                    //���t���[���|�[�Y�ŁA�O�t���[���|�[�Y�ł͂Ȃ��ꍇ
                    //�|�[�Y������́A�ŏ��̃t���[�������̓R�R��
                    GgafDxInput::updateMouseState();
                    GgafDxInput::updateMouseState(); //�}�E�X���W�̑��΍��W��0�Ƀ��Z�b�g���邽��
                                                     //�A���Q��Ăяo��
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }

                //�|�[�Y�i�s�������̓R�R
                //

                if (_pMenuBoardPause->isJustSink() || _is_frame_advance) {
                    //�|�[�Y���ɁA�|�[�Y�L�[�������ė������ꍇ�̏���
                    //�|�[�Y����������̏��������̓R�R��
                    _TRACE_("UNPAUSE!");
                    P_GOD->setVB(VB_PLAY);
                    _pProg->getGazeScene()->unpauseTree();//�|�[�Y�����I�I
                }
            }
            _was_paused_flg_GameMainScene_prev_frame = _pProg->getGazeScene()->_was_paused_flg;
            //�C�x���g�҂� EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case GameScene::PROG_ENDING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog(=GameScene::PROG_ENDING) is Just Changed");
            }
            break;
        }

        case GameScene::PROG_GAME_OVER: {
            //##########  �Q�[���I�[�o�[  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog(=GameScene::PROG_GAME_OVER) is Just Changed");
            }
            //�C�x���g�҂� EVENT_GAME_OVER_FINISH
            break;
        }

        case GameScene::PROG_FINISH: {
            //##########  �Q�[���V�[���I��  ##########
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog(=GameScene::PROG_FINISH) is Just Changed");
                DefaultScene* pSubScene;
                for (map<progress, DefaultScene*>::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneTree(FADE_FRAMES);
                    }
                }
            }
            if (_pProg->getFrameInProgress() == FADE_FRAMES) {
                reset(); //���Z�b�g�i�ŏ��̐i����Ԃɖ߂�j
            }
            break;
        }

        default:
            break;
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
    if (prm_no == EVENT_GOD_WILL_DIE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GOD_WILL_DIE) CommonScene���E���グ�Č�ɉ�������悤�ɂ��܂��B");
        //�_������ł��܂��O��
        //CommonScene���E���グ�A�����������ɂȂ�悤�ɑ��삷��B
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
        _pProg->changeWithScene_Flipping(GameScene::PROG_TITLE); //�^�C�g����

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //�^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        //changeFlippingSubScene(GameScene::PROG_DEMO);
        _pProg->changeWithScene_Crossfading(GameScene::PROG_DEMO); //�f����

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //�f���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        _pProg->changeWithScene_Crossfading(GameScene::PROG_INIT); //�ŏ���

    } else if (prm_no == EVENT_GAMESTART) {
        //�X�^�[�g
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        _pProg->changeWithScene_Crossfading(GameScene::PROG_BEGINNING); //�I�[�v�j���O�i�Q�[�����[�h�Z���N�g�j��

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //�Q�[�����[�h�Z���N�g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        _pProg->changeWithScene_Crossfading(GameScene::PROG_MAIN,600);//���C����
    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //�Ƃɂ����^�C�g���փC�x���g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        _pProg->changeWithScene_Flipping(GameScene::PROG_TITLE); //�^�C�g����
    }


    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        _pProg->changeWithScene_Crossfading(GameScene::PROG_GAME_OVER); //�Q�[���I�[�o�[��
    } else if (prm_no == EVENT_GAME_OVER_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAME_OVER_FINISH)");
        _pProg->change(GameScene::PROG_FINISH);
    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker::_num_check = 0;

//        if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//            CollisionChecker::_pLinearOctree->putTree();
//        }

        //�{�V�[���̏����V�[���̏����A�N�^�[�S�Ăɂ��ē����蔻��`�F�b�N���s���B
        //��ԕ���(������)�A���S���Y���ɂ��A�`�F�b�N�񐔂̍œK�����s���Ă��܂��B
        //�ڍׂ� �u�V�[��Creater.xls�v �� �u��ʑ��ցv �V�[�g�Q��
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_MY_BODY_NOMAL,
        KIND_ITEM
        );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_MY_SHOT|KIND_MY_BODY,
        KIND_ENEMY_BODY|KIND_OTHER|KIND_CHIKEI
        );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_ENEMY_SHOT,
        KIND_MY_BODY|KIND_OTHER|KIND_CHIKEI
        );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA,
        KIND_CHIKEI|KIND_OTHER
        );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_ENEMY_BODY_CHIKEI_NOMAL|KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA|KIND_CHIKEI|KIND_OTHER,
        KIND_OTHER
        );
    }
}

GameScene::~GameScene() {
}
