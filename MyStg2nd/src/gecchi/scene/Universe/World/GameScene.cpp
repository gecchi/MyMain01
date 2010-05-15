#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) {
    GameGlobal::_pSceneGame = this;

    _pCommonScene = NEW CommonScene("Common");
    addSubLast(_pCommonScene);

    _pScene_GameDemo = NEW GameDemoScene("GameDemo");
    addSubLast(_pScene_GameDemo);

    _pScene_GameBeginning = NEW GameBeginningScene("GameBeginning");
    addSubLast(_pScene_GameBeginning);

    _pScene_GameMain = NEW GameMainScene("GameMain");
    addSubLast(_pScene_GameMain);

    _pScene_GameEnding = NEW GameEndingScene("GameEnding");
    addSubLast(_pScene_GameEnding);

    _pScene_GameDemo->inactivate();        //�ŏ��̃A�N�e�B�u�ȃT�u�V�[���̓f���V�[��
    _pScene_GameBeginning->inactivate();
    _pScene_GameMain->inactivate();
    _pScene_GameEnding->inactivate();

    addSubLast(NEW TamagoScene("TamagoScene"));

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

    if (_pScene_GameMain->wasPause()) {
        if (VB->isPushedDown(VB_PAUSE)) {
            _TRACE_("UNPAUSE!");
            VB = VB_PLAY;
            _pScene_GameMain->unpause();     //�ꎞ��~
        }
    }


    //�T�u�V�[���̐ؑւ��╽�s���s�̂��߂́A�������A���O�����A�t���O������
    if (_pSceneCannel == _pScene_GameDemo) {
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_BEGIN) {
            _pScene_GameBeginning->reset();
            _pScene_GameBeginning->ready();
        }
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_DECIDE) {
            _pScene_GameBeginning->activate();
            _pSceneCannel = _pScene_GameBeginning;
        }

    } else if (_pSceneCannel == _pScene_GameBeginning) {
        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_BEGIN) {
            _pScene_GameMain->reset();
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_DECIDE) {
            _stage = _pScene_GameBeginning->_selected_stage;
            _pScene_GameMain->ready(_stage);
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_END) {
            _pScene_GameMain->activate();
            _pSceneCannel = _pScene_GameMain;
        }

    } else if (_pSceneCannel == _pScene_GameMain) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_BEGIN) {
            _pScene_GameEnding->reset();
            _pScene_GameEnding->ready();
        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_END) {
            _pScene_GameEnding->activate();
            _pSceneCannel = _pScene_GameEnding;
        }

    } else if (_pSceneCannel == _pScene_GameEnding) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEENDING_PROG_BEGIN) {
            _pScene_GameEnding->reset();
            _pScene_GameEnding->ready();
        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEENDING_PROG_END) {
            _pScene_GameEnding->activate();
            _pSceneCannel = _pScene_GameEnding;
        }

    }

}

void GameScene::processJudgement() {
    //�z���̃V�[���ɏ����A�N�^�[�̓����蔻�菈�����s
    //�ڍׂ� �V�[��Creater.xls �� ��ʑ��� �V�[�g
    if (getBehaveingFrame() >= 120) {
        CollisionChecker::_num_check = 0;

        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
            CollisionChecker::_pLinearOctree->putTree();
        }

        //�����؃A���S���Y���Ńq�b�g�`�F�b�N
        CollisionChecker::_pLinearOctree->executeAllHitChk(
                KIND_MY_SHOT|KIND_MY_BODY,
                KIND_ENEMY_BODY|KIND_OTHER|KIND_CHIKEI
              );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
                KIND_ENEMY_SHOT,
                KIND_MY_BODY|KIND_OTHER|KIND_CHIKEI
              );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
                KIND_ENEMY_BODY|KIND_OTHER,
                KIND_OTHER|KIND_CHIKEI
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
