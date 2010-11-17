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

    _pScene_PreGameTitle = NEW GamePreTitleScene("PreGameTitle");
    addSubLast(_pScene_PreGameTitle);

    _pScene_GameTitle = NEW GameTitleScene("GameTitle");
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

    _stage = 1;
}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
    reset();
//    _pScene_GameDemo->reset();
//    _pScene_GameDemo->ready();
//    _pSceneCannel = _pScene_GameDemo;
}

void GameScene::reset() {
    VB_UI->clear();
    P_GOD->setVB(VB_UI);
    _pMyShipScene->unblindSceneTree();
    _pScene_PreGameTitle->unblindSceneTree();
    _pScene_GameTitle->unblindSceneTree();
    _pScene_GameDemo->unblindSceneTree();
    _pScene_GameBeginning->unblindSceneTree();
    _pScene_GameMain->unblindSceneTree();
    _pScene_GameEnding->unblindSceneTree();
    _pScene_GameOver->unblindSceneTree();

    _pMyShipScene->inactivateImmediately();
    _pScene_PreGameTitle->inactivateImmediately();
    _pScene_GameTitle->inactivateImmediately();
    _pScene_GameDemo->inactivateImmediately();
    _pScene_GameBeginning->inactivateImmediately();
    _pScene_GameMain->inactivateImmediately();
    _pScene_GameEnding->inactivateImmediately();
    _pScene_GameOver->inactivateImmediately();
    changeProgress(GAME_SCENE_PROG_INIT);
}

void GameScene::onActive() {
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

    //########## GAME_SCENE_PROG_INIT ##########
    if (getProgress() == GAME_SCENE_PROG_INIT) {
        //先行準備
        if (!_pScene_GameMain->_had_ready_stage) {
            _pScene_GameMain->readyStage(_stage);
        }
        changeProgress(GAME_SCENE_PROG_PRE_TITLE); //デモへ
    }

    //##########  タイトル前演出(GAME_SCENE_PROG_PRE_TITLE)  ##########
    if (onActiveProgress(GAME_SCENE_PROG_PRE_TITLE)) {
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_PRE_TITLE)");
        _pScene_PreGameTitle->reset();
        _pScene_PreGameTitle->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_PRE_TITLE) {
        // EVENT_PREGAMETITLE_SCENE_FINISH イベント受付
        if (VB->isPushedDown(VB_UI_EXECUTE)) { //スキップしてTITLEへ
            changeProgress(GAME_SCENE_PROG_TITLE);
            _pScene_PreGameTitle->inactivate();
        }
    }
    if (onInactiveProgress(GAME_SCENE_PROG_PRE_TITLE)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_PRE_TITLE)");
    }


    //##########  タイトル(GAME_SCENE_PROG_TITLE)  ##########
    if (onActiveProgress(GAME_SCENE_PROG_TITLE)) {
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_TITLE)");
        _pScene_GameTitle->reset();
        _pScene_GameTitle->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_TITLE) {
        //イベント待ち EVENT_GAMETITLE_SCENE_FINISH or EVENT_GAMESTART
    }
    if (onInactiveProgress(GAME_SCENE_PROG_TITLE)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_TITLE)");
    }


    //##########  デモ(GAME_SCENE_PROG_DEMO)  ##########
    if (onActiveProgress(GAME_SCENE_PROG_DEMO)) {
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_DEMO)");
        _pScene_GameDemo->reset();
        _pScene_GameDemo->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_DEMO) {
        //イベント待ち EVENT_GAMEDEMO_SCENE_FINISH

        if (VB->isPushedDown(VB_UI_EXECUTE)) { //スキップしてTITLEへ
            changeProgress(GAME_SCENE_PROG_TITLE);
            _pScene_GameDemo->inactivate();
        }
    }
    if (onInactiveProgress(GAME_SCENE_PROG_DEMO)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_DEMO)");
    }

    //##########  GAME_SCENE_PROG_BEGINNING(ゲーム開始)  ##########
    if (onActiveProgress(GAME_SCENE_PROG_BEGINNING)) {
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_BEGINNING)");
        _pScene_GameBeginning->reset();
        _pScene_GameBeginning->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_BEGINNING) {
        //イベント待ち EVENT_GAMEMODE_DECIDE
    }
    if (onInactiveProgress(GAME_SCENE_PROG_BEGINNING)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_BEGINNING)");
    }

    //##########  GAME_SCENE_PROG_MAIN(メイン)  ##########
    if (onActiveProgress(GAME_SCENE_PROG_MAIN)) {
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_MAIN)");
        VB_PLAY->clear();
        P_GOD->setVB(VB_PLAY); //プレイ用に変更
        _pScene_GameMain->reset();
        _pScene_GameMain->activate();

        _pMyShipScene->reset();
        _pMyShipScene->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_MAIN) {
        //イベント待ち EVENT_ALL_MY_SHIP_WAS_DESTROYED
    }
    if (onInactiveProgress(GAME_SCENE_PROG_MAIN)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_MAIN)");
        VB_UI->clear();
        P_GOD->setVB(VB_UI);  //元に戻す
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
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_GAME_OVER)");
        _pScene_GameOver->reset();
        _pScene_GameOver->activate();
    }
    if (getProgress() == GAME_SCENE_PROG_GAME_OVER) {
        //イベント待ち EVENT_GAME_OVER_FINISH
    }
    if (onInactiveProgress(GAME_SCENE_PROG_GAME_OVER)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_GAME_OVER)");
    }

    //GAME_SCENE_PROG_GAME_OVER 時の処理
    if (onActiveProgress(GAME_SCENE_PROG_FINISH)) {
        _TRACE_("GameScene onActiveProgress(GAME_SCENE_PROG_FINISH)");
        _pMyShipScene->fadeoutSceneTree(FADE_FRAME);
        _pScene_PreGameTitle->fadeoutSceneTree(FADE_FRAME);
        _pScene_GameTitle->fadeoutSceneTree(FADE_FRAME);
        _pScene_GameDemo->fadeoutSceneTree(FADE_FRAME);
        _pScene_GameBeginning->fadeoutSceneTree(FADE_FRAME);
        _pScene_GameMain->fadeoutSceneTree(FADE_FRAME);
        _pScene_GameEnding->fadeoutSceneTree(FADE_FRAME);
        _pScene_GameOver->fadeoutSceneTree(FADE_FRAME);
    }
    if (getProgress() == GAME_SCENE_PROG_FINISH) {
        if (getActivePartFrameInProgress() == FADE_FRAME) {
            reset();
        }
    }
    if (onInactiveProgress(GAME_SCENE_PROG_FINISH)) {
        _TRACE_("GameScene onInactiveProgress(GAME_SCENE_PROG_FINISH)");
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

void GameScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREGAMETITLE_SCENE_FINISH) {
        //プレタイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLE_SCENE_FINISH)");
        changeProgress(GAME_SCENE_PROG_TITLE); //タイトルへ
    } else if (prm_no == EVENT_GAMETITLE_SCENE_FINISH) {
        //タイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLE_SCENE_FINISH)");
        changeProgress(GAME_SCENE_PROG_DEMO); //デモへ
    } else if (prm_no == EVENT_GAMEDEMO_SCENE_FINISH) {
        //デモシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMO_SCENE_FINISH)");
        changeProgress(GAME_SCENE_PROG_INIT); //最初へ
    } else if (prm_no == EVENT_GAMESTART) {
        //スタート
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        changeProgress(GAME_SCENE_PROG_BEGINNING); //オープニング（ゲームモードセレクト）へ
    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //ゲームモードセレクト完了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        _stage = 1;
        changeProgress(GAME_SCENE_PROG_MAIN); //メインへ
    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //とにかくタイトルへイベント発生
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        changeProgress(GAME_SCENE_PROG_TITLE); //タイトルへ
    }



    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        changeProgress(GAME_SCENE_PROG_GAME_OVER); //ゲームオーバーへ
    } else if (prm_no == EVENT_GAME_OVER_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAME_OVER_FINISH)");
        changeProgress(GAME_SCENE_PROG_FINISH);
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
