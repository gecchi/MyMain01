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
    _was_paused_flg_GameMainScene_prev_frame = false;
    useProgress(10);
}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");

//    _pScene_GameDemo->reset();
//    _pScene_GameDemo->ready();
//    _pSceneCannel = _pScene_GameDemo;
}

void GameScene::onReset() {
    VB_UI->clear();
    P_GOD->setVB(VB_UI);
    _pMyShipScene->resetTree();
    _pCommonScene->resetTree();
    _pScene_PreGameTitle->resetTree();
    _pScene_GameTitle->resetTree();
    _pScene_GameDemo->resetTree();
    _pScene_GameBeginning->resetTree();
    _pScene_GameMain->resetTree();
    _pScene_GameEnding->resetTree();
    _pScene_GameOver->resetTree();

    _pMyShipScene->unblindSceneTree();
    _pCommonScene->unblindSceneTree();
    _pScene_PreGameTitle->unblindSceneTree();
    _pScene_GameTitle->unblindSceneTree();
    _pScene_GameDemo->unblindSceneTree();
    _pScene_GameBeginning->unblindSceneTree();
    _pScene_GameMain->unblindSceneTree();
    _pScene_GameEnding->unblindSceneTree();
    _pScene_GameOver->unblindSceneTree();

    _pMyShipScene->inactivate();
    _pScene_PreGameTitle->inactivate();
    _pScene_GameTitle->inactivate();
    _pScene_GameDemo->inactivate();
    _pScene_GameBeginning->inactivate();
    _pScene_GameMain->inactivate();
    _pScene_GameEnding->inactivate();
    _pScene_GameOver->inactivate();

    _pPrg->change(GAME_SCENE_PROG_INIT);
}

void GameScene::onActive() {
    reset();
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

    switch (_pPrg->getChangedFrom()) {
        case GAME_SCENE_PROG_MAIN:
            VB_UI->clear();
            P_GOD->setVB(VB_UI);  //元に戻す
            break;
        default:
            break;
    }


    switch (_pPrg->get()) {
        case GAME_SCENE_PROG_INIT:
            //先行準備
            if (!_pScene_GameMain->_had_ready_stage) {
                _pScene_GameMain->readyStage(_stage);
            }
            _pPrg->change(GAME_SCENE_PROG_PRE_TITLE);
            break;

        case GAME_SCENE_PROG_PRE_TITLE:
            //##########  タイトル前演出  ##########
            if (_pPrg->isJustChanged()) {
                P_GOD->syncTimeFrame();
                _pScene_PreGameTitle->reset();
                _pScene_PreGameTitle->activate();
            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _pScene_PreGameTitle->inactivate();
                _pPrg->change(GAME_SCENE_PROG_TITLE);
            }
            //或いは EVENT_PREGAMETITLE_SCENE_FINISH イベント受付
            break;

        case GAME_SCENE_PROG_TITLE:
            //##########  タイトル  ##########
            if (_pPrg->isJustChanged()) {
                _pScene_GameTitle->reset();
                _pScene_GameTitle->activate();
            }
            //イベント待ち EVENT_GAMETITLE_SCENE_FINISH or EVENT_GAMESTART
            break;

        case GAME_SCENE_PROG_DEMO:
            //##########  デモ  ##########
            if (_pPrg->isJustChanged()) {
                _pScene_GameDemo->reset();
                _pScene_GameDemo->activate();
            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _pPrg->change(GAME_SCENE_PROG_TITLE);
                _pScene_GameDemo->inactivate();
            }
            //或いは EVENT_GAMEDEMO_SCENE_FINISH イベント受付
            break;

        case GAME_SCENE_PROG_BEGINNING:
            //##########  ゲーム開始（モード選択等）  ##########
            if (_pPrg->isJustChanged()) {
                _pScene_GameBeginning->reset();
                _pScene_GameBeginning->activate();
            }
            //イベント待ち EVENT_GAMEMODE_DECIDE
            break;

        case GAME_SCENE_PROG_MAIN:
            //##########  ゲームメイン  ##########
            if (_pPrg->isJustChanged()) {
                VB_PLAY->clear();
                P_GOD->setVB(VB_PLAY); //プレイ用に変更
                _pScene_GameMain->reset();
                _pScene_GameMain->activate();
                _pMyShipScene->reset();
                _pMyShipScene->activate();
            }

            if (!_pScene_GameMain->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == true)  {
                    P_UNIVERSE->undoCameraWork();
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    _is_frame_advance = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //入力はＵＩに切り替え

                    _pScene_GameMain->pause();
                    _pMyShipScene->pause();
                    _pCommonScene->pause();
                }
            }
            if (_pScene_GameMain->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == false) {
                    GgafDx9Input::updateMouseState();
                    GgafDx9Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }
                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    P_GOD->setVB(VB_PLAY);
                    _pScene_GameMain->unpause();
                    _pMyShipScene->unpause();
                    _pCommonScene->unpause();
                }
            }
            _was_paused_flg_GameMainScene_prev_frame = _pScene_GameMain->_was_paused_flg;

            //イベント待ち EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;

        case GAME_SCENE_PROG_ENDING:
            if (_pPrg->isJustChanged()) {
            }
            break;

        case GAME_SCENE_PROG_GAME_OVER:
            //##########  ゲームオーバー  ##########
            if (_pPrg->isJustChanged()) {
                _pScene_GameOver->reset();
                _pScene_GameOver->activate();
            }
            //イベント待ち EVENT_GAME_OVER_FINISH
            break;

        case GAME_SCENE_PROG_FINISH:
            //##########  ゲームシーン終了  ##########
            if (_pPrg->isJustChanged()) {
                _pMyShipScene->fadeoutSceneTree(FADE_FRAME);
                _pCommonScene->fadeoutSceneTree(FADE_FRAME);
                _pScene_PreGameTitle->fadeoutSceneTree(FADE_FRAME);
                _pScene_GameTitle->fadeoutSceneTree(FADE_FRAME);
                _pScene_GameDemo->fadeoutSceneTree(FADE_FRAME);
                _pScene_GameBeginning->fadeoutSceneTree(FADE_FRAME);
                _pScene_GameMain->fadeoutSceneTree(FADE_FRAME);
                _pScene_GameEnding->fadeoutSceneTree(FADE_FRAME);
                _pScene_GameOver->fadeoutSceneTree(FADE_FRAME);
            }
            if (_pPrg->getActivePartFrameInProgress() == FADE_FRAME) {
                reset(); //リセット（最初の進捗状態に戻る）
            }
            break;

        default:
            break;
    }
}

void GameScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREGAMETITLE_SCENE_FINISH) {
        //プレタイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLE_SCENE_FINISH)");
        _pPrg->change(GAME_SCENE_PROG_TITLE); //タイトルへ

    } else if (prm_no == EVENT_GAMETITLE_SCENE_FINISH) {
        //タイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLE_SCENE_FINISH)");
        _pPrg->change(GAME_SCENE_PROG_DEMO); //デモへ

    } else if (prm_no == EVENT_GAMEDEMO_SCENE_FINISH) {
        //デモシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMO_SCENE_FINISH)");
        _pPrg->change(GAME_SCENE_PROG_INIT); //最初へ

    } else if (prm_no == EVENT_GAMESTART) {
        //スタート
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        _pPrg->change(GAME_SCENE_PROG_BEGINNING); //オープニング（ゲームモードセレクト）へ

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //ゲームモードセレクト完了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        _stage = 1;
        _pPrg->change(GAME_SCENE_PROG_MAIN); //メインへ

    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //とにかくタイトルへイベント発生
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        _pPrg->change(GAME_SCENE_PROG_TITLE); //タイトルへ
    }



    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        _pPrg->change(GAME_SCENE_PROG_GAME_OVER); //ゲームオーバーへ
    } else if (prm_no == EVENT_GAME_OVER_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAME_OVER_FINISH)");
        _pPrg->change(GAME_SCENE_PROG_FINISH);
    }
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
