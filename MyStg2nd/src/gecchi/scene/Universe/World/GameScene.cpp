#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) ,
_pCommonScene(NULL),
_pMyShipScene(NULL) {
//_pScene_GameTitle(NULL),
//_pScene_GameDemo(NULL),
//_pScene_GameBeginning(NULL),
//_pScene_GameMain(NULL),
//_pScene_GameEnding(NULL),
//_pScene_GameOver(NULL) {

    _class_name = "GameScene";

//    GameGlobal::_pSceneGame = this;

    _pCommonScene = NEW CommonScene("Common");
    addSubLast(_pCommonScene);
    _pMyShipScene = NEW MyShipScene("MyShipScene");
    addSubLast(_pMyShipScene);

    mapSubScene[GAMESCENE_PROG_PRE_TITLE] = NEW GamePreTitleScene("PreGameTitle");
    mapSubScene[GAMESCENE_PROG_TITLE]     = NEW GameTitleScene("GameTitle");
    mapSubScene[GAMESCENE_PROG_DEMO]      = NEW GameDemoScene("GameDemo");
    mapSubScene[GAMESCENE_PROG_BEGINNING] = NEW GameBeginningScene("GameBeginning");
    mapSubScene[GAMESCENE_PROG_MAIN]      = NEW GameMainScene("GameMain");
    mapSubScene[GAMESCENE_PROG_ENDING]    = NEW GameEndingScene("GameEnding");
    mapSubScene[GAMESCENE_PROG_GAME_OVER] = NEW GameOverScene("GameOver");
//    map<progress, DefaultScene*>::const_iterator it = mapSubScene.begin();
//    while(it != mapSubScene.end()){
    DefaultScene* pSubScene;
    for (map<progress, DefaultScene*>::const_iterator it = mapSubScene.begin(); it != mapSubScene.end(); it++) {
        pSubScene = it->second;
        addSubLast(pSubScene);
        pSubScene->inactivateImmediately();
    }


//    _pScene_PreGameTitle = NEW GamePreTitleScene("PreGameTitle");
//    addSubLast(_pScene_PreGameTitle);
//
//    _pScene_GameTitle = NEW GameTitleScene("GameTitle");
//    addSubLast(_pScene_GameTitle);
//
//    _pScene_GameDemo = NEW GameDemoScene("GameDemo");
//    addSubLast(_pScene_GameDemo);
//
//    _pScene_GameBeginning = NEW GameBeginningScene("GameBeginning");
//    addSubLast(_pScene_GameBeginning);
//
//    _pScene_GameMain = NEW GameMainScene("GameMain");
//    addSubLast(_pScene_GameMain);
//
//    _pScene_GameEnding = NEW GameEndingScene("GameEnding");
//    addSubLast(_pScene_GameEnding);
//
//    _pScene_GameOver = NEW GameOverScene("GameOver");
//    addSubLast(_pScene_GameOver);

//    _pMyShipScene->inactivateImmediately();
//    _pScene_GameTitle->inactivateImmediately();
//    _pScene_GameDemo->inactivateImmediately();        //�ŏ��̃A�N�e�B�u�ȃT�u�V�[���̓f���V�[��
//    _pScene_GameBeginning->inactivateImmediately();
//    _pScene_GameMain->inactivateImmediately();
//    _pScene_GameEnding->inactivateImmediately();
//    _pScene_GameOver->inactivateImmediately();
    //���܂�
    //addSubLast(NEW TamagoScene("TamagoScene"));
    _is_frame_advance = false;

    _stage = 1;
    _was_paused_flg_GameMainScene_prev_frame = false;
    useProgress(10);
}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() �����܂���DemoScene����");

//    _pScene_GameDemo->reset();
//    _pScene_GameDemo->ready();
//    _pSceneCannel = _pScene_GameDemo;
}

void GameScene::onReset() {
    VB_UI->clear();
    P_GOD->setVB(VB_UI);
    _pMyShipScene->resetTree();
    _pCommonScene->resetTree();
    _pMyShipScene->unblindSceneTree();
    _pCommonScene->unblindSceneTree();
    _pMyShipScene->inactivate();

    DefaultScene* pSubScene;
    for (map<progress, DefaultScene*>::const_iterator it = mapSubScene.begin(); it != mapSubScene.end(); it++) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->unblindSceneTree();
            pSubScene->inactivate();
        }
    }



//
//    _pScene_PreGameTitle->resetTree();
//    _pScene_GameTitle->resetTree();
//    _pScene_GameDemo->resetTree();
//    _pScene_GameBeginning->resetTree();
//    _pScene_GameMain->resetTree();
//    _pScene_GameEnding->resetTree();
//    _pScene_GameOver->resetTree();
//
//
//    _pScene_PreGameTitle->unblindSceneTree();
//    _pScene_GameTitle->unblindSceneTree();
//    _pScene_GameDemo->unblindSceneTree();
//    _pScene_GameBeginning->unblindSceneTree();
//    _pScene_GameMain->unblindSceneTree();
//    _pScene_GameEnding->unblindSceneTree();
//    _pScene_GameOver->unblindSceneTree();
//
//    _pMyShipScene->inactivate();
//    _pScene_PreGameTitle->inactivate();
//    _pScene_GameTitle->inactivate();
//    _pScene_GameDemo->inactivate();
//    _pScene_GameBeginning->inactivate();
//    _pScene_GameMain->inactivate();
//    _pScene_GameEnding->inactivate();
//    _pScene_GameOver->inactivate();

    _pProg->change(GAMESCENE_PROG_INIT);
}

void GameScene::onActive() {
}

void GameScene::changeFlippingSubScene(progress prm_progress) {
    if (mapSubScene[_pProg->get()]) {
        mapSubScene[_pProg->get()]->inactivate();
    }
    if (mapSubScene[prm_progress]) {
        mapSubScene[prm_progress]->reset();
        mapSubScene[prm_progress]->activate();
        mapSubScene[prm_progress]->unblindSceneTree();
    }
    _pProg->change(prm_progress);
}

void GameScene::changeFadeingSubScene(progress prm_progress, frame prm_fadeout_frames, frame prm_fadein_frames) {
    if (mapSubScene[_pProg->get()]) {
        mapSubScene[_pProg->get()]->fadeoutSceneTree(prm_fadeout_frames);
        mapSubScene[_pProg->get()]->inactivateDelay(prm_fadeout_frames);
    }
    if (mapSubScene[prm_progress]) {
        mapSubScene[prm_progress]->reset();
        mapSubScene[prm_progress]->activate();
        mapSubScene[prm_progress]->blindSceneTree();
        mapSubScene[prm_progress]->fadeinSceneTree(prm_fadein_frames);
    }
    _pProg->change(prm_progress);
}

void GameScene::processBehavior() {
#ifdef MY_DEBUG
    //���C���t���[���\���ؑ�
    if (VB->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDx9God::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDx9God::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif

    switch (_pProg->getPrev_WhenJustChanged()) {
        case GAMESCENE_PROG_MAIN: {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);  //���ɖ߂�
            break;
        }

        default:
            break;
    }


    switch (_pProg->get()) {
        case GAMESCENE_PROG_INIT: {
            //��s����
            GameMainScene* pGameMainScene = (GameMainScene*)(mapSubScene[GAMESCENE_PROG_MAIN]);
            if (!pGameMainScene->_had_ready_stage) {
                pGameMainScene->readyStage(_stage);
            }
            changeFadeingSubScene(GAMESCENE_PROG_PRE_TITLE, 0, FADE_FRAME);
            break;
        }

        case GAMESCENE_PROG_PRE_TITLE: {
            //##########  �^�C�g���O���o  ##########
            if (_pProg->isJustChanged()) {
                P_GOD->syncTimeFrame();
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                changeFlippingSubScene(GAMESCENE_PROG_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH �C�x���g��t
            break;
        }

        case GAMESCENE_PROG_TITLE: {
            //##########  �^�C�g��  ##########
            if (_pProg->isJustChanged()) {
            }
            //�C�x���g�҂� EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case GAMESCENE_PROG_DEMO: {
            //##########  �f��  ##########
            if (_pProg->isJustChanged()) {
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                changeFlippingSubScene(GAMESCENE_PROG_TITLE);
            }

            //������ EVENT_GAMEDEMOSCENE_FINISH �C�x���g��t
            break;
        }

        case GAMESCENE_PROG_BEGINNING: {
            //##########  �Q�[���J�n�i���[�h�I�𓙁j  ##########
            if (_pProg->isJustChanged()) {
            }
            //�C�x���g�҂� EVENT_GAMEMODE_DECIDE
            break;
        }

        case GAMESCENE_PROG_MAIN: {
            //##########  �Q�[�����C��  ##########
            if (_pProg->isJustChanged()) {
                VB_PLAY->clear();
                P_GOD->setVB(VB_PLAY); //�v���C�p�ɕύX
            }

            if (!mapSubScene[GAMESCENE_PROG_MAIN]->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == true)  {
                    P_UNIVERSE->undoCameraWork();
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    _is_frame_advance = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //���͂͂t�h�ɐ؂�ւ�
                    mapSubScene[GAMESCENE_PROG_MAIN]->pause();
                    _pMyShipScene->pause();
                    _pCommonScene->pause();
                }
            }
            if (mapSubScene[GAMESCENE_PROG_MAIN]->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == false) {
                    GgafDx9Input::updateMouseState();
                    GgafDx9Input::updateMouseState(); //�}�E�X���W�̑��΍��W��0�ɂ��邽�߂Q��Ăяo��
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    P_GOD->setVB(VB_PLAY);
                    mapSubScene[GAMESCENE_PROG_MAIN]->unpause();
                    _pMyShipScene->unpause();
                    _pCommonScene->unpause();
                }
            }
            _was_paused_flg_GameMainScene_prev_frame = mapSubScene[GAMESCENE_PROG_MAIN]->_was_paused_flg;
            //�C�x���g�҂� EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case GAMESCENE_PROG_ENDING: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        case GAMESCENE_PROG_GAME_OVER: {
            //##########  �Q�[���I�[�o�[  ##########
            if (_pProg->isJustChanged()) {
            }
            //�C�x���g�҂� EVENT_GAME_OVER_FINISH
            break;
        }

        case GAMESCENE_PROG_FINISH: {
            //##########  �Q�[���V�[���I��  ##########
            if (_pProg->isJustChanged()) {
                _pMyShipScene->fadeoutSceneTree(FADE_FRAME);
                _pCommonScene->fadeoutSceneTree(FADE_FRAME);
                DefaultScene* pSubScene;
                for (map<progress, DefaultScene*>::const_iterator it = mapSubScene.begin(); it != mapSubScene.end(); it++) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneTree(FADE_FRAME);
                    }
                }
//                _pScene_PreGameTitle->fadeoutSceneTree(FADE_FRAME);
//                _pScene_GameTitle->fadeoutSceneTree(FADE_FRAME);
//                _pScene_GameDemo->fadeoutSceneTree(FADE_FRAME);
//                _pScene_GameBeginning->fadeoutSceneTree(FADE_FRAME);
//                _pScene_GameMain->fadeoutSceneTree(FADE_FRAME);
//                _pScene_GameEnding->fadeoutSceneTree(FADE_FRAME);
//                _pScene_GameOver->fadeoutSceneTree(FADE_FRAME);
            }
            if (_pProg->getFrameInProgress() == FADE_FRAME) {
                reset(); //���Z�b�g�i�ŏ��̐i����Ԃɖ߂�j
            }
            break;
        }

        default:
            break;
    }
}

void GameScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //�v���^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        changeFlippingSubScene(GAMESCENE_PROG_TITLE); //�^�C�g����

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //�^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        //changeFlippingSubScene(GAMESCENE_PROG_DEMO);
        changeFadeingSubScene(GAMESCENE_PROG_DEMO, FADE_FRAME, FADE_FRAME); //�f����

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //�f���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        changeFadeingSubScene(GAMESCENE_PROG_INIT, FADE_FRAME, FADE_FRAME); //�ŏ���

    } else if (prm_no == EVENT_GAMESTART) {
        //�X�^�[�g
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        changeFadeingSubScene(GAMESCENE_PROG_BEGINNING, FADE_FRAME, FADE_FRAME); //�I�[�v�j���O�i�Q�[�����[�h�Z���N�g�j��

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //�Q�[�����[�h�Z���N�g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        _stage = 1;
        mapSubScene[GAMESCENE_PROG_MAIN]->reset();
        mapSubScene[GAMESCENE_PROG_MAIN]->activate();
        _pMyShipScene->reset();
        _pMyShipScene->activate();
        changeFadeingSubScene(GAMESCENE_PROG_MAIN, FADE_FRAME, FADE_FRAME);//���C����

    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //�Ƃɂ����^�C�g���փC�x���g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        changeFlippingSubScene(GAMESCENE_PROG_TITLE); //�^�C�g����
    }



    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        changeFadeingSubScene(GAMESCENE_PROG_GAME_OVER, FADE_FRAME, FADE_FRAME); //�Q�[���I�[�o�[��
    } else if (prm_no == EVENT_GAME_OVER_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAME_OVER_FINISH)");
        changeFlippingSubScene(GAMESCENE_PROG_FINISH);
    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker::_num_check = 0;

//        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//            CollisionChecker::_pLinearOctree->putTree();
//        }

        //�����؃A���S���Y���ŏ����V�[���̏����A�N�^�[�S�q�b�g�`�F�b�N
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





void GameScene::processFinal() {
}



GameScene::~GameScene() {
}
