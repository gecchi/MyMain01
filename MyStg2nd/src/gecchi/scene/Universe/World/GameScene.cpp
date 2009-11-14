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

    _pGameDemo = NEW GameDemoScene("GameDemo");
    addSubLast(_pGameDemo);

    _pGameBeginning = NEW GameBeginningScene("GameBeginning");
    addSubLast(_pGameBeginning);

    _pGameMain = NEW GameMainScene("GameMain");
    addSubLast(_pGameMain);

    _pGameEnding = NEW GameEndingScene("GameEnding");
    addSubLast(_pGameEnding);

    _pGameDemo->inactivate();        //最初のアクティブなサブシーンはデモシーン
    _pGameBeginning->inactivate();
    _pGameMain->inactivate();
    _pGameEnding->inactivate();

}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
    _pGameDemo->reset();
    _pSceneCannel = _pGameDemo;
}

void GameScene::processBehavior() {
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

    //サブシーンの切替えや平行実行のための、初期化、事前処理、フラグ処理等
    if (_pSceneCannel == _pGameDemo) {
        if (_pGameDemo->getProgressOnChange() == GAMEDEMO_PROG_BEGIN) {
            _pGameBeginning->reset();
            _pGameBeginning->ready();
        }
        if (_pGameDemo->getProgressOnChange() == GAMEDEMO_PROG_DECIDE) {
            _pGameBeginning->activate();
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
            _pGameMain->activate();
            _pSceneCannel = _pGameMain;
        }

    } else if (_pSceneCannel == _pGameMain) {
        if (_pGameMain->getProgressOnChange() == GAMEMAIN_PROG_BEGIN) {
            _pGameEnding->reset();
            _pGameEnding->ready();
        }
        if (_pGameMain->getProgressOnChange() == GAMEMAIN_PROG_END) {
            _pGameEnding->activate();
            _pSceneCannel = _pGameEnding;
        }

    } else if (_pSceneCannel == _pGameEnding) {
        if (_pGameMain->getProgressOnChange() == GAMEENDING_PROG_BEGIN) {
            _pGameEnding->reset();
            _pGameEnding->ready();
        }
        if (_pGameMain->getProgressOnChange() == GAMEENDING_PROG_END) {
            _pGameEnding->activate();
            _pSceneCannel = _pGameEnding;
        }

    }
}

void GameScene::processJudgement() {
    //配下のシーンに所属アクターの当たり判定処理実行
    //詳細は ACTOR.xls の hantei シート

    //TODO:ボトルネックもいいところ
    //なんとかしなければ
    if (_lifeframe >= 120) {
        StgChecker::_num_check = 0;

        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
            StgChecker::_pLinearOctree->putTree();
        }

//        StgChecker::_pLinearOctree->executeAllBumpChk(
//                 KIND_ENEMY_BODY ,
//                 KIND_MY_BODY
//               );



        StgChecker::_pLinearOctree->executeAllBumpChk(
                KIND_CHIKEI,
                KIND_MY_BODY | KIND_MY_SHOT_GU | KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_NOMAL | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER
              );

        StgChecker::_pLinearOctree->executeAllBumpChk(
                KIND_ENEMY_BODY | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_PA | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER,
                KIND_MY_BODY | KIND_MY_SHOT_GU | KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_PA
              );

        StgChecker::_pLinearOctree->executeAllBumpChk(
                KIND_ENEMY_BODY|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_OTHER,
                KIND_MY_SHOT_NOMAL
            );
        StgChecker::_pLinearOctree->executeAllBumpChk(
                KIND_OTHER,
                KIND_ENEMY_BODY | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_PA | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER
              );
        StgChecker::_pLinearOctree->executeAllBumpChk(
                KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_NOMAL,
                KIND_ENEMY_SHOT_GU
              );
        StgChecker::_pLinearOctree->executeAllBumpChk(
                KIND_MY_SHOT_CHOKI,
                KIND_MY_SHOT_GU
              );

//
//        executeBumpChkHeadActors(
//          KIND_CHIKEI,
//          KIND_MY_BODY | KIND_MY_SHOT_GU | KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_NOMAL | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER
//        );
//        executeBumpChkHeadActors(
//          KIND_ENEMY_BODY | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_PA | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER,
//          KIND_MY_BODY | KIND_MY_SHOT_GU | KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_PA
//        );
//
//        executeBumpChkHeadActors(
//            KIND_ENEMY_BODY|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_OTHER,
//            KIND_MY_SHOT_NOMAL
//        );
//        executeBumpChkHeadActors(
//          KIND_OTHER,
//          KIND_ENEMY_BODY | KIND_ENEMY_SHOT_GU | KIND_ENEMY_SHOT_CHOKI | KIND_ENEMY_SHOT_PA | KIND_ENEMY_SHOT_NOMAL | KIND_OTHER
//        );
//        executeBumpChkHeadActors(
//          KIND_MY_SHOT_CHOKI | KIND_MY_SHOT_NOMAL,
//          KIND_ENEMY_SHOT_GU
//        );
//        executeBumpChkHeadActors(
//          KIND_MY_SHOT_CHOKI,
//          KIND_MY_SHOT_GU
//        );
    }
}

void GameScene::processFinal() {

    if (_lifeframe == 120) {
        //デモ開始
        _pGameDemo->activate();
    }

}

GameScene::~GameScene() {
}
