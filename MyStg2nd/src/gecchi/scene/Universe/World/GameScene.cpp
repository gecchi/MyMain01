#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) ,
_pCommonScene(NULL),
_pMyShipScene(NULL),
_pScene_GameTitle(NULL),
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

    _pScene_GameTitle = NEW GameTitleScene("GameDemo");
    addSubLast(_pScene_GameTitle);

    _pScene_GameDemo = NEW GameDemoScene("GameDemo");
    addSubLast(_pScene_GameDemo);

    _pScene_GameBeginning = NEW GameBeginningScene("GameBeginning");
    addSubLast(_pScene_GameBeginning);

    _pScene_GameMain = NEW GameMainScene("GameMain");
    addSubLast(_pScene_GameMain);

    _pScene_GameEnding = NEW GameEndingScene("GameEnding");
    addSubLast(_pScene_GameEnding);

    _pScene_GameOver = NEW GameOverScene("GameOver");
    addSubLast(_pScene_GameOver);

    _pMyShipScene->inactivateImmediately();
    _pScene_GameTitle->inactivateImmediately();
    _pScene_GameDemo->inactivateImmediately();        //最初のアクティブなサブシーンはデモシーン
    _pScene_GameBeginning->inactivateImmediately();
    _pScene_GameMain->inactivateImmediately();
    _pScene_GameEnding->inactivateImmediately();
    _pScene_GameOver->inactivateImmediately();
    //たまご
    //addSubLast(NEW TamagoScene("TamagoScene"));
    _is_frame_advance = false;
}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
    _pScene_GameDemo->reset();
//    _pScene_GameDemo->ready();
//    _pSceneCannel = _pScene_GameDemo;
}

void GameScene::reset() {

}

void GameScene::onActive() {
   changeProgress(GAME_SCENE_PROG_INIT);

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

    //GAME_SCENE_PROG_INIT 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_INIT)) {
        _pMyShipScene->reset();
        _pMyShipScene->inactivate();
        _pScene_GameTitle->reset();
        _pScene_GameTitle->inactivate();
        _pScene_GameDemo->reset();
        _pScene_GameDemo->inactivate();
        _pScene_GameBeginning->reset();
        _pScene_GameBeginning->inactivate();
        _pScene_GameMain->reset();
        _pScene_GameMain->inactivate();
        _pScene_GameEnding->reset();
        _pScene_GameEnding->inactivate();
        _pScene_GameOver->reset();
        _pScene_GameOver->inactivate();
    }
    if (getProgress() == GAME_SCENE_PROG_INIT) {
        changeProgress(GAME_SCENE_PROG_TITLE); //デモへ
    }
    if (onInactiveProgress(GAME_SCENE_PROG_INIT)) {
    }

    //GAME_SCENE_PROG_TITLE 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_TITLE)) {
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_TITLE)");
        VB_UI->clear();
        P_GOD->setVB(VB_UI);
        _pScene_GameTitle->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_TITLE) {
        //イベント待ち
        //EVENT_GAMETITLE_SCENE_FINISH or
        //EVENT_GAMETITLE_SCENE_GAMESTART
    }
    if (onInactiveProgress(GAME_SCENE_PROG_TITLE)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_TITLE)");
    }

    //GAME_SCENE_PROG_DEMO 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_DEMO)) {
        VB_UI->clear();
        P_GOD->setVB(VB_UI);
//        _pScene_GameBeginning->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_DEMO) {
    }
    if (onInactiveProgress(GAME_SCENE_PROG_DEMO)) {
//        _pScene_GameTitle->fadeoutSceneTree(120);
//        _pScene_GameTitle->inactivateDelay(120);
    }


    //GAME_SCENE_PROG_BEGINNING 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_BEGINNING)) {
    }
    if (getProgress() == GAME_SCENE_PROG_BEGINNING) {
    }
    if (onInactiveProgress(GAME_SCENE_PROG_BEGINNING)) {
    }


    //GAME_SCENE_PROG_MAIN 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_MAIN)) {
    }
    if (getProgress() == GAME_SCENE_PROG_MAIN) {
    }
    if (onInactiveProgress(GAME_SCENE_PROG_MAIN)) {
    }


    //GAME_SCENE_PROG_ENDING 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_ENDING)) {
    }
    if (getProgress() == GAME_SCENE_PROG_ENDING) {
    }
    if (onInactiveProgress(GAME_SCENE_PROG_ENDING)) {
    }


    //GAME_SCENE_PROG_GAME_OVER 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_GAME_OVER)) {
    }
    if (getProgress() == GAME_SCENE_PROG_GAME_OVER) {
    }
    if (onInactiveProgress(GAME_SCENE_PROG_GAME_OVER)) {
    }



//#ifdef MY_DEBUG
//    //ワイヤフレーム表示切替
//    if (VB->isPushedDown(VB_UI_DEBUG)) {
//        if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
//            GgafDx9God::_d3dfillmode = D3DFILL_SOLID;
//        } else {
//            GgafDx9God::_d3dfillmode = D3DFILL_WIREFRAME;
//        }
//    }
//#endif
////    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
////        fadeinSceneTree(2*60);
////    }
////    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
////        fadeoutSceneTree(2*60);
////    }
//
//    //一時停止解除
//    if (_pScene_GameMain->wasPause()) {
//        if (VB_UI->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
//            P_GOD->setVB(VB_PLAY);
//            _pScene_GameMain->unpause();     //GameMainSceneでの一時停止解除
//            P_UNIVERSE->popCameraWork();
////            P_ACTIVE_CAMWORKER->unpause();
//            P_MYSHIP->unpause();
//        }
//    }
//
////     //おまけ機能。一時停止していれば、カメラ操作できる。
////     if (_pScene_GameMain->canBehave() ) {
////         //一時停止していない状態。
////         //スルー
////     } else {
////     }
//
//    //サブシーンの切替えや平行実行のための、初期化、事前処理、フラグ処理等
//    if (_pSceneCannel == _pScene_GameDemo) {
//        if (_pScene_GameDemo->getProgressOnActive() == GAMEDEMO_SCENE_PROG_BEGIN) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _pScene_GameBeginning->reset();
//            _pScene_GameBeginning->ready();
//        }
//        if (_pScene_GameDemo->getProgressOnActive() == GAMEDEMO_SCENE_PROG_DECIDE) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _pScene_GameBeginning->activate();
//            _pSceneCannel = _pScene_GameBeginning;
//        }
//
//    } else if (_pSceneCannel == _pScene_GameBeginning) {
//        if (_pScene_GameBeginning->getProgressOnActive() == GAMEBEGINNING_SCENE_PROG_BEGIN) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//
//        }
//
//        if (_pScene_GameBeginning->getProgressOnActive() == GAMEBEGINNING_SCENE_PROG_DECIDE) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _stage = _pScene_GameBeginning->_selected_stage;
//            _pScene_GameMain->ready(_stage); //先行準備
//
//        }
//
//        if (_pScene_GameBeginning->getProgressOnActive() == GAMEBEGINNING_SCENE_PROG_END) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _pScene_GameMain->reset();
//            _pScene_GameMain->activate();
//            _pSceneCannel = _pScene_GameMain;
//        }
//
//    } else if (_pSceneCannel == _pScene_GameMain) {
//        if (_pScene_GameMain->getProgressOnActive() == GAMEMAIN_SCENE_PROG_BEGIN) {
//            _pMyShipScene->reset();
//            _pMyShipScene->activate();
//            _TRACE_("_pMyShipScene activateしました！");
////            VB_UI->clear();
////            VB_PLAY->clear();
////            P_GOD->setVB(VB_PLAY); //保存のためプレイ用に変更
//
//            //GameOverかGameEnding 先行準備
//            _pScene_GameOver->reset();
//            _pScene_GameOver->ready();
//            _pScene_GameEnding->reset();
//            _pScene_GameEnding->ready();
//
//        }
//
//    } else if (_pSceneCannel == _pScene_GameEnding) {
//        if (_pScene_GameEnding->getProgressOnActive() == GAMEENDING_SCENE_PROG_BEGIN) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _pScene_GameDemo->reset();
//            _pScene_GameDemo->ready();
//
//        }
//        if (_pScene_GameEnding->getProgressOnActive() == GAMEENDING_SCENE_PROG_END) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _pSceneCannel = _pScene_GameDemo;
//        }
//
//    } else if (_pSceneCannel == _pScene_GameOver) { //余地のないGAME_OVER
//        if (_pScene_GameOver->getProgressOnActive() == GAMEOVER_SCENE_PROG_BEGIN) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _pScene_GameDemo->reset();
//            _pScene_GameDemo->ready();
//        }
//        if (_pScene_GameOver->getProgressOnActive() == GAMEOVER_SCENE_PROG_END) {
//            VB_UI->clear();
//            P_GOD->setVB(VB_UI);
//            _pSceneCannel = _pScene_GameDemo;
//        }
//
//    }

}

void GameScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_GAMETITLE_SCENE_FINISH) {
        //タイトル、ぼーっと終了時
        changeProgress(GAME_SCENE_PROG_DEMO); //デモへ
    } else if  (prm_no == EVENT_GAMETITLE_SCENE_GAMESTART) {
        //タイトルでゲームスタートしました！
        changeProgress(GAME_SCENE_PROG_BEGINNING); //ゲームオープニングへ
    }



//    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
//        _TRACE_("GameScene EVENT_ALL_MY_SHIP_WAS_DESTROYED was Catch!!");
//        if (true) { //GameOverかどうか分岐
//            _pMyShipScene->fadeoutScene(180);
//            _pMyShipScene->inactivateDelay(180);
//            _pScene_GameMain->changeProgress(GAMEMAIN_SCENE_PROG_END);
//            _pScene_GameMain->_pSceneMainCannnel->fadeoutSceneTree(180);
//            _TRACE_(_pScene_GameMain->_pSceneMainCannnel->getName()<<" をfadeoutSceneします");
//            _pSceneCannel = _pScene_GameOver;
//            _pSceneCannel->activate();
//            _pSceneCannel->changeProgress(GAMEOVER_SCENE_PROG_BEGIN);
//        } else {
//            _pSceneCannel = _pScene_GameEnding;
//        }
//
//
//    } else if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
//        _TRACE_("GameScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");
//    } else if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_FINISH) {
//        _TRACE_("GameScene EVENT_MY_SHIP_WAS_DESTROYED_FINISH was Catch!!");
//    } else if (prm_no == EVENT_GAME_OVER_FINISH) {
//        _TRACE_("GameScene EVENT_GAME_OVER_FINISH was Catch!!");
//        _pSceneCannel = _pScene_GameDemo;
//        _pScene_GameDemo->reset();
//        _pScene_GameDemo->ready();
//        _pScene_GameDemo->activate();
//        _pScene_GameDemo->changeProgress(GAMEDEMO_SCENE_PROG_BEGIN);
//    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker::_num_check = 0;

//        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//            CollisionChecker::_pLinearOctree->putTree();
//        }

        //八分木アルゴリズムで所属シーンの所属アクター全ヒットチェック
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
        KIND_ENEMY_BODY_CHIKEI_NOMAL|KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA|KIND_CHIKEI|KIND_OTHER,
        KIND_OTHER
        );
    }
}





void GameScene::processFinal() {

//    if (getBehaveingFrame() == 120) {
//        //デモ開始
//        _pScene_GameDemo->activate();
//    }

}



GameScene::~GameScene() {
}
