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

    _class_name = "GameScene";
    useProgress(GAMESCENE_PROG_FINISH);

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

    _pProg->affectSubScene(GAMESCENE_PROG_PRE_TITLE, GAMESCENE_PROG_GAME_OVER,  "PreGameTitle");
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



    _pProg->change(GAMESCENE_PROG_INIT);
}

void GameScene::onActive() {
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

            if (!_pProg->getSubScene()->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == true)  {
                    P_UNIVERSE->undoCameraWork();
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    _is_frame_advance = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //���͂͂t�h�ɐ؂�ւ�
                    _pProg->getSubScene()->pause();
                    _pMyShipScene->pause();
                    _pCommonScene->pause();
                }
            }
            if (_pProg->getSubScene()->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == false) {
                    GgafDx9Input::updateMouseState();
                    GgafDx9Input::updateMouseState(); //�}�E�X���W�̑��΍��W��0�ɂ��邽�߂Q��Ăяo��
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    P_GOD->setVB(VB_PLAY);
                    _pProg->getSubScene()->unpause();
                    _pMyShipScene->unpause();
                    _pCommonScene->unpause();
                }
            }
            _was_paused_flg_GameMainScene_prev_frame = _pProg->getSubScene()->_was_paused_flg;
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
                for (map<progress, DefaultScene*>::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
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

        _pProg->changeWithFlippingSubScene(GAMESCENE_PROG_MAIN);//���C����
        _pProg->getSubScene()->reset();
        _pProg->getSubScene()->activate();
        _pMyShipScene->reset();
        _pMyShipScene->activate();

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
