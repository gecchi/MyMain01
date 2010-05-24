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

    _pScene_GameDemo->inactivate();        //最初のアクティブなサブシーンはデモシーン
    _pScene_GameBeginning->inactivate();
    _pScene_GameMain->inactivate();
    _pScene_GameEnding->inactivate();

    addSubLast(NEW TamagoScene("TamagoScene"));

}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
    _pScene_GameDemo->reset();
    _pSceneCannel = _pScene_GameDemo;
}

void GameScene::processBehavior() {
#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
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
            VB_PLAY->_pVBMap_Active->_state |= VB_PAUSE; //VB_PAUSE押している事にする
            pGOD->setVB(VB_PLAY);

            _pScene_GameMain->unpause();     //一時停止
        }
    }


    //サブシーンの切替えや平行実行のための、初期化、事前処理、フラグ処理等
    if (_pSceneCannel == _pScene_GameDemo) {
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_BEGIN) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameBeginning->reset();
            _pScene_GameBeginning->ready();
        }
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_DECIDE) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameBeginning->activate();
            _pSceneCannel = _pScene_GameBeginning;
        }

    } else if (_pSceneCannel == _pScene_GameBeginning) {
        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_BEGIN) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameMain->reset();
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_DECIDE) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _stage = _pScene_GameBeginning->_selected_stage;
            _pScene_GameMain->ready(_stage); //先行準備
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_END) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameMain->activate();
            _pSceneCannel = _pScene_GameMain;
        }

    } else if (_pSceneCannel == _pScene_GameMain) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_BEGIN) {
            VB_UI->clear();
            VB_PLAY->clear();
            pGOD->setVB(VB_PLAY); //保存のためプレイ用に変更
            _pScene_GameEnding->reset();
            _pScene_GameEnding->ready();
        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_END) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);  //戻す
            _pScene_GameEnding->activate();
            _pSceneCannel = _pScene_GameEnding;
        }

    } else if (_pSceneCannel == _pScene_GameEnding) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEENDING_PROG_BEGIN) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameEnding->reset();
            _pScene_GameEnding->ready();
        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEENDING_PROG_END) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameEnding->activate();
            _pSceneCannel = _pScene_GameEnding;
        }

    }

}

void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker::_num_check = 0;

        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
            CollisionChecker::_pLinearOctree->putTree();
        }

        //八分木アルゴリズムでヒットチェック
        //配下のシーンに所属アクターの当たり判定処理実行
        //詳細は 「シーンCreater.xls」 の 「種別相関」 シート参照
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
            KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA|KIND_CHIKEI|KIND_OTHER,
            KIND_OTHER
        );
    }
}

void GameScene::processFinal() {

    if (getBehaveingFrame() == 120) {
        //デモ開始
        _pScene_GameDemo->activate();
    }

}

GameScene::~GameScene() {
}
