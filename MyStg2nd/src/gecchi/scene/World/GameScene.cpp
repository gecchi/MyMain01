#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) {
    _pCommonScene = NEW CommonScene("Common");
    addSubLast(_pCommonScene);


    _pGameDemo = NEW GameDemoScene("GameDemo");
    addSubLast(_pGameDemo);

    _pGameBeginning = NEW GameBeginningScene("GameBeginning");
    addSubLast(_pGameBeginning);

    _pGameMain = NEW GameMainScene("GameMain");
    addSubLast(_pGameMain);

    _pGameEnding = NEW GameEndingScene("GameEnding");
    addSubLast(_pGameEnding);

    _pGameDemo->act();
    _pGameBeginning->inact();
    _pGameMain->inact();
    _pGameEnding->inact();

}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
    _pGameDemo->reset();
    _pSceneCannel = _pGameDemo;
}

void GameScene::processBehavior() {
    VB::update(); //入力情報更新
#ifdef OREDEBUG
    //ワイヤフレーム表示切替
    if (VB::isPushedDown(VB_UI_DEBUG)) {
        if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDx9God::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDx9God::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif

    if (_pSceneCannel == _pGameDemo) {
        if (_pGameDemo->getProgressOnChange() == GAMEDEMO_PROG_BEGIN) {
            _pGameBeginning->reset();
            _pGameBeginning->ready();
        }
        if (_pGameDemo->getProgressOnChange() == GAMEDEMO_PROG_DECIDE) {
            _pGameBeginning->act();
            _pSceneCannel = _pGameBeginning;
        }

    } else if (_pSceneCannel == _pGameBeginning) {
        if (_pGameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_BEGIN) {
            _pGameMain->reset();
        }

        if (_pGameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_DECIDE) {
            _stage = _pGameBeginning->_selected_stage;
            _pGameMain->ready(_stage);
        }

        if (_pGameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_END) {
            _pGameMain->act();
            _pSceneCannel = _pGameMain;
        }

    } else if (_pSceneCannel == _pGameMain) {
        if (_pGameMain->getProgressOnChange() == GAMEMAIN_PROG_BEGIN) {
            _pGameEnding->reset();
            _pGameEnding->ready();
        }
        if (_pGameMain->getProgressOnChange() == GAMEMAIN_PROG_END) {
            _pGameEnding->act();
            _pSceneCannel = _pGameEnding;
        }

    } else if (_pSceneCannel == _pGameEnding) {
        if (_pGameMain->getProgressOnChange() == GAMEENDING_PROG_BEGIN) {
            _pGameEnding->reset();
            _pGameEnding->ready();
        }
        if (_pGameMain->getProgressOnChange() == GAMEENDING_PROG_END) {
            _pGameEnding->act();
            _pSceneCannel = _pGameEnding;
        }

    }
}

void GameScene::processFinal() {
}

GameScene::~GameScene() {
}
