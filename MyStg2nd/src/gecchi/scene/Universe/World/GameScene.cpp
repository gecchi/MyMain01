#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) ,
_pCommonScene(NULL),
_pMyShipScene(NULL),
_pScene_GameDemo(NULL),
_pScene_GameBeginning(NULL),
_pScene_GameMain(NULL),
_pScene_GameEnding(NULL),
_pScene_GameOver(NULL) {

    _class_name = "GameScene";

//    GameGlobal::_pSceneGame = this;

    _pCommonScene = NEW CommonScene("Common");
    addSubLast(_pCommonScene);

    _pMyShipScene = NEW MyShipScene("MyShipScene");
    addSubLast(_pMyShipScene);

    _pScene_GameDemo = NEW GameDemoScene("GameDemo");
    addSubLast(_pScene_GameDemo);

    _pScene_GameBeginning = NEW GameBeginningScene("GameBeginning");
    addSubLast(_pScene_GameBeginning);

    _pScene_GameMain = NEW GameMainScene("GameMain");
    addSubLast(_pScene_GameMain);

    _pScene_GameEnding = NEW GameEndingScene("GameEnding");
    addSubLast(_pScene_GameEnding);

    _pScene_GameOver = NEW GameOverScene("GameEnding");
    addSubLast(_pScene_GameOver);


    _pScene_GameDemo->inactivateImmediately();        //�ŏ��̃A�N�e�B�u�ȃT�u�V�[���̓f���V�[��
    _pScene_GameBeginning->inactivateImmediately();
    _pScene_GameMain->inactivateImmediately();
    _pScene_GameEnding->inactivateImmediately();
    _pScene_GameOver->inactivateImmediately();
    //���܂�
    //addSubLast(NEW TamagoScene("TamagoScene"));
    _is_frame_advance = false;
}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() �����܂���DemoScene����");
    _pScene_GameDemo->reset();
    _pSceneCannel = _pScene_GameDemo;
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
//    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
//        fadeinSceneTree(2*60);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//        fadeoutSceneTree(2*60);
//    }

    //�ꎞ��~����
    if (_pScene_GameMain->wasPause()) {
        if (VB_UI->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
            P_GOD->setVB(VB_PLAY);
            _pScene_GameMain->unpause();     //GameMainScene�ł̈ꎞ��~����
            P_UNIVERSE->popCameraWork();
//            P_ACTIVE_CAMWORKER->unpause();
            P_MYSHIP->unpause();
        }
    }

//     //���܂��@�\�B�ꎞ��~���Ă���΁A�J��������ł���B
//     if (_pScene_GameMain->canBehave() ) {
//         //�ꎞ��~���Ă��Ȃ���ԁB
//         //�X���[
//     } else {
//     }

    //�T�u�V�[���̐ؑւ��╽�s���s�̂��߂́A�������A���O�����A�t���O������
    if (_pSceneCannel == _pScene_GameDemo) {
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_BEGIN) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pScene_GameBeginning->reset();
            _pScene_GameBeginning->ready();
        }
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_DECIDE) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pScene_GameBeginning->activate();
            _pSceneCannel = _pScene_GameBeginning;
        }

    } else if (_pSceneCannel == _pScene_GameBeginning) {
        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_BEGIN) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pScene_GameMain->reset();
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_DECIDE) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _stage = _pScene_GameBeginning->_selected_stage;
            _pScene_GameMain->ready(_stage); //��s����
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_END) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pScene_GameMain->activate();
            _pSceneCannel = _pScene_GameMain;
        }

    } else if (_pSceneCannel == _pScene_GameMain) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_BEGIN) {
//            VB_UI->clear();
//            VB_PLAY->clear();
//            P_GOD->setVB(VB_PLAY); //�ۑ��̂��߃v���C�p�ɕύX

            //GameOver��GameEnding ��s����
            _pScene_GameOver->reset();
            _pScene_GameOver->ready();
            _pScene_GameEnding->reset();
            _pScene_GameEnding->ready();

        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_END) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);  //�߂�
//            _pScene_GameEnding->activate();
//            _pSceneCannel = _pScene_GameEnding;

            if (true) { //GameOver���ǂ�������
                _pSceneCannel = _pScene_GameOver;
            } else {
                _pSceneCannel = _pScene_GameEnding;
            }
        }

    } else if (_pSceneCannel == _pScene_GameEnding) {
        if (_pScene_GameEnding->getProgressOnChange() == GAMEENDING_PROG_BEGIN) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pScene_GameDemo->reset();
            _pScene_GameDemo->ready();

        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEENDING_PROG_END) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pSceneCannel = _pScene_GameDemo;
        }

    } else if (_pSceneCannel == _pScene_GameOver) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEOVER_PROG_BEGIN) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pScene_GameDemo->reset();
            _pScene_GameDemo->ready();
        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEOVER_PROG_END) {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);
            _pSceneCannel = _pScene_GameDemo;
        }

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

    if (getBehaveingFrame() == 120) {
        //�f���J�n
        _pScene_GameDemo->activate();
    }

}

GameScene::~GameScene() {
}
