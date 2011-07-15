#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

enum {
    GAMESCENE_PROG_INIT = 1 ,
    GAMESCENE_PROG_PRE_TITLE,
    GAMESCENE_PROG_TITLE    ,
    GAMESCENE_PROG_DEMO     ,
    GAMESCENE_PROG_BEGINNING,
    GAMESCENE_PROG_MAIN     ,
    GAMESCENE_PROG_ENDING   ,
    GAMESCENE_PROG_GAME_OVER,
    GAMESCENE_PROG_FINISH   ,
};
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

    addSubLast(NEW GamePreTitleScene("PreGameTitle"));
    addSubLast(NEW GameTitleScene("GameTitle"));
    addSubLast(NEW GameDemoScene("GameDemo"));
    addSubLast(NEW GameBeginningScene("GameBeginning"));
    addSubLast(NEW GameMainScene("GameMain"));
    addSubLast(NEW GameEndingScene("GameEnding"));
    addSubLast(NEW GameOverScene("GameOver"));


    useProgress(GAMESCENE_PROG_FINISH);
    _pProg->affectSubScene(GAMESCENE_PROG_PRE_TITLE, "PreGameTitle");
//    _pProg->getAffect(GAMESCENE_PROG_PRE_TITLE] = NEW GamePreTitleScene("PreGameTitle");
//    _pProg->getAffect(GAMESCENE_PROG_TITLE]     = NEW GameTitleScene("GameTitle");
//    _pProg->getAffect(GAMESCENE_PROG_DEMO]      = NEW GameDemoScene("GameDemo");
//    _pProg->getAffect(GAMESCENE_PROG_BEGINNING] = NEW GameBeginningScene("GameBeginning");
//    _pProg->getAffect(GAMESCENE_PROG_MAIN]      = NEW GameMainScene("GameMain");
//    _pProg->getAffect(GAMESCENE_PROG_ENDING]    = NEW GameEndingScene("GameEnding");
//    _pProg->getAffect(GAMESCENE_PROG_GAME_OVER] = NEW GameOverScene("GameOver");
//    map<progress, DefaultScene*>::const_iterator it = _mapSubScene.begin();
//    while(it != _mapSubScene.end()){

//
//    DefaultScene* pSubScene;
//    for (map<progress, DefaultScene*>::const_iterator it = _mapSubScene.begin(); it != _mapSubScene.end(); it++) {
//        pSubScene = it->second;
//        addSubLast(pSubScene);
//        pSubScene->inactivateImmediately();
//    }


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
    _pMyShipScene->fadeinSceneTree(0);
    _pCommonScene->fadeinSceneTree(0);
    _pMyShipScene->inactivate();

    DefaultScene* pSubScene;
    for (map<progress, DefaultScene*>::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->fadeinSceneTree(0);
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
//    _pScene_PreGameTitle->fadeinSceneTree(0);
//    _pScene_GameTitle->fadeinSceneTree(0);
//    _pScene_GameDemo->fadeinSceneTree(0);
//    _pScene_GameBeginning->fadeinSceneTree(0);
//    _pScene_GameMain->fadeinSceneTree(0);
//    _pScene_GameEnding->fadeinSceneTree(0);
//    _pScene_GameOver->fadeinSceneTree(0);
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

//void GameScene::changeFlippingSubScene(progress prm_progress) {
//    if (_pProg->getAffect(_pProg->get()]) {
//        _pProg->getAffect(_pProg->get()]->inactivate();
//    }
//    if (_pProg->getAffect(prm_progress]) {
//        _pProg->getAffect(prm_progress]->reset();
//        _pProg->getAffect(prm_progress]->activate();
//        _pProg->getAffect(prm_progress]->fadeinSceneTree(0);
//    }
//    _pProg->change(prm_progress);
//}
//
//void GameScene::changeFadeingSubScene(progress prm_progress, frame prm_fadeout_frames, frame prm_fadein_frames) {
//    if (_pProg->getAffect(_pProg->get()]) {
//        _pProg->getAffect(_pProg->get()]->fadeoutSceneTree(prm_fadeout_frames);
//        _pProg->getAffect(_pProg->get()]->inactivateDelay(prm_fadeout_frames);
//    }
//    if (_pProg->getAffect(prm_progress]) {
//        _pProg->getAffect(prm_progress]->reset();
//        _pProg->getAffect(prm_progress]->activate();
//        _pProg->getAffect(prm_progress]->fadeoutSceneTree(0);
//        _pProg->getAffect(prm_progress]->fadeinSceneTree(prm_fadein_frames);
//    }
//    _pProg->change(prm_progress);
//}

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
//            GameMainScene* pGameMainScene = (GameMainScene*)(_pProg->getAffect(GAMESCENE_PROG_MAIN]);
//            if (!pGameMainScene->_had_ready_stage) {
//                pGameMainScene->readyStage(_stage);
//            }
            _pProg->changeWithCrossfadingSubScene(GAMESCENE_PROG_PRE_TITLE);
            break;
        }

        case GAMESCENE_PROG_PRE_TITLE: {
            //##########  �^�C�g���O���o  ##########
            if (_pProg->isJustChanged()) {
                P_GOD->syncTimeFrame();
            }
            //VB_UI_EXECUTE �ŁA�X�L�b�v����TITLE��
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                _pProg->changeWithFlippingSubScene(GAMESCENE_PROG_TITLE);
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
                _pProg->changeWithFlippingSubScene(GAMESCENE_PROG_TITLE);
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

            if (!_pProg->getAffect(GAMESCENE_PROG_MAIN)->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == true)  {
                    P_UNIVERSE->undoCameraWork();
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    _is_frame_advance = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //���͂͂t�h�ɐ؂�ւ�
                    _pProg->getAffect(GAMESCENE_PROG_MAIN)->pause();
                    _pMyShipScene->pause();
                    _pCommonScene->pause();
                }
            }
            if (_pProg->getAffect(GAMESCENE_PROG_MAIN)->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == false) {
                    GgafDx9Input::updateMouseState();
                    GgafDx9Input::updateMouseState(); //�}�E�X���W�̑��΍��W��0�ɂ��邽�߂Q��Ăяo��
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    P_GOD->setVB(VB_PLAY);
                    _pProg->getAffect(GAMESCENE_PROG_MAIN)->unpause();
                    _pMyShipScene->unpause();
                    _pCommonScene->unpause();
                }
            }
            _was_paused_flg_GameMainScene_prev_frame = _pProg->getAffect(GAMESCENE_PROG_MAIN)->_was_paused_flg;
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
                _pMyShipScene->fadeoutSceneTree(FADE_FRAMES);
                _pCommonScene->fadeoutSceneTree(FADE_FRAMES);
                DefaultScene* pSubScene;
                for (map<progress, DefaultScene*>::const_iterator it = _mapSubScene.begin(); it != _mapSubScene.end(); it++) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneTree(FADE_FRAMES);
                    }
                }
//                _pScene_PreGameTitle->fadeoutSceneTree(FADE_FRAMES);
//                _pScene_GameTitle->fadeoutSceneTree(FADE_FRAMES);
//                _pScene_GameDemo->fadeoutSceneTree(FADE_FRAMES);
//                _pScene_GameBeginning->fadeoutSceneTree(FADE_FRAMES);
//                _pScene_GameMain->fadeoutSceneTree(FADE_FRAMES);
//                _pScene_GameEnding->fadeoutSceneTree(FADE_FRAMES);
//                _pScene_GameOver->fadeoutSceneTree(FADE_FRAMES);
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

void GameScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //�v���^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        _pProg->changeWithFlippingSubScene(GAMESCENE_PROG_TITLE); //�^�C�g����

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //�^�C�g���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        //changeFlippingSubScene(GAMESCENE_PROG_DEMO);
        _pProg->changeWithCrossfadingSubScene(GAMESCENE_PROG_DEMO); //�f����

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //�f���V�[���I��
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        _pProg->changeWithCrossfadingSubScene(GAMESCENE_PROG_INIT); //�ŏ���

    } else if (prm_no == EVENT_GAMESTART) {
        //�X�^�[�g
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        _pProg->changeWithCrossfadingSubScene(GAMESCENE_PROG_BEGINNING); //�I�[�v�j���O�i�Q�[�����[�h�Z���N�g�j��

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //�Q�[�����[�h�Z���N�g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        _stage = 1;
        _pProg->getAffect(GAMESCENE_PROG_MAIN)->reset();
        _pProg->getAffect(GAMESCENE_PROG_MAIN)->activate();
        _pMyShipScene->reset();
        _pMyShipScene->activate();
        _pProg->changeWithFlippingSubScene(GAMESCENE_PROG_MAIN);//���C����

    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //�Ƃɂ����^�C�g���փC�x���g����
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        _pProg->changeWithFlippingSubScene(GAMESCENE_PROG_TITLE); //�^�C�g����
    }



    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        _pProg->changeWithCrossfadingSubScene(GAMESCENE_PROG_GAME_OVER); //�Q�[���I�[�o�[��
    } else if (prm_no == EVENT_GAME_OVER_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAME_OVER_FINISH)");
        _pProg->changeWithFlippingSubScene(GAMESCENE_PROG_FINISH);
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
