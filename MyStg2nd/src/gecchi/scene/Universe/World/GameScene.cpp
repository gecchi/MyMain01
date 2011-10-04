#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
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
_pMyShipScene(NULL),
_pStageController(NULL) {

    _class_name = "GameScene";
    useProgress(GAMESCENE_PROG_FINISH);
    _pCommonScene = NEW CommonScene("Common");
    _pCommonScene->inactivateImmediately();
    addSubLast(_pCommonScene);
    _pMyShipScene = NEW MyShipScene("MyShipScene");
    _pMyShipScene->inactivateImmediately();
    addSubLast(_pMyShipScene);
    _pStageController = new StageController("StageController");
    _pStageController->inactivateImmediately();
    addSubLast(_pStageController);
    _pGamePauseScene = new GamePauseScene("GamePauseScene");
    _pGamePauseScene->inactivateImmediately();
    addSubLast(_pGamePauseScene);

    addSubLast(NEW GamePreTitleScene("PreGameTitle"));
    addSubLast(NEW GameTitleScene("GameTitle"));
    addSubLast(NEW GameDemoScene("GameDemo"));
    addSubLast(NEW GameBeginningScene("GameBeginning"));
    addSubLast(NEW GameMainScene("GameMain"));
    addSubLast(NEW GameEndingScene("GameEnding"));
    addSubLast(NEW GameOverScene("GameOver"));

    _pProg->relatSubScene(GAMESCENE_PROG_PRE_TITLE, GAMESCENE_PROG_GAME_OVER,  "PreGameTitle");
    //たまご
    //addSubLast(NEW TamagoScene("TamagoScene"));
    _is_frame_advance = false;

    _was_paused_flg_GameMainScene_prev_frame = false;

}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
}

void GameScene::onReset() {

    VB_UI->clear();
    P_GOD->setVB(VB_UI);

    DefaultScene* pSubScene;
    for (map<progress, DefaultScene*>::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->fadeinSceneTree(0);
            pSubScene->inactivateImmediately();
        }
    }
    P_UNIVERSE->resetCameraWork();
    GameGlobal::init();
    _pProg->set(GAMESCENE_PROG_INIT);
}

void GameScene::onActive() {
}

void GameScene::processBehavior() {
#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
    if (VB->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif

    switch (_pProg->getPrev_WhenJustChanged()) {
        case GAMESCENE_PROG_MAIN: {
            VB_UI->clear();
            P_GOD->setVB(VB_UI);  //元に戻す
            break;
        }

        default:
            break;
    }


    switch (_pProg->get()) {
        case GAMESCENE_PROG_INIT: {
            if (_pProg->isJustChanged()) {
                //P_GOD->syncTimeFrame(); //描画を中止して、フレームと時間の同期を行う
            }
            if (_pProg->getFrameInProgress() >= 180 && P_GOD->_fps > CFG_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                _TRACE_("P_GOD->_fps = "<<P_GOD->_fps);
                _pProg->changeWithScene_Crossfading(GAMESCENE_PROG_PRE_TITLE);
            }
            break;
        }

        case GAMESCENE_PROG_PRE_TITLE: {
            //##########  タイトル前演出  ##########
            if (_pProg->isJustChanged()) {

            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                _pProg->changeWithScene_Flipping(GAMESCENE_PROG_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH イベント受付
            break;
        }

        case GAMESCENE_PROG_TITLE: {
            //##########  タイトル  ##########
            if (_pProg->isJustChanged()) {
            }
            //イベント待ち EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case GAMESCENE_PROG_DEMO: {
            //##########  デモ  ##########
            if (_pProg->isJustChanged()) {
            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _pProg->changeWithScene_Flipping(GAMESCENE_PROG_TITLE);
            }

            //或いは EVENT_GAMEDEMOSCENE_FINISH イベント受付
            break;
        }

        case GAMESCENE_PROG_BEGINNING: {
            //##########  ゲーム開始（モード選択等）  ##########
            if (_pProg->isJustChanged()) {
            }
            //イベント待ち EVENT_GAMEMODE_DECIDE
            break;
        }

        case GAMESCENE_PROG_MAIN: {
            //##########  ゲームメイン  ##########
            if (_pProg->isJustChanged()) {
                VB_PLAY->clear();
                P_GOD->setVB(VB_PLAY); //プレイ用に変更
            }

            //今ポーズではない時
            if (!_pProg->getGazeScene()->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == true)  {
                    //現フレームポーズではない、かつ前フレームポーズの場合。
                    //ポーズ解除から最初のフレーム処理はココへ
                    P_UNIVERSE->undoCameraWork();
                }

                //通常進行時処理はココ

                //

                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    //ポーズではないときに、ポーズキーを押して離した場合の処理
                    //ポーズ発生時直後の初期処理はココへ
                    _is_frame_advance = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //入力はＵＩに切り替え
                    _pProg->getGazeScene()->pause(); //ポーズ！！
                    _pGamePauseScene->reset();
                    _pGamePauseScene->activate();
                }
            }
            //今ポーズ時
            if (_pProg->getGazeScene()->_was_paused_flg) {
                if (_was_paused_flg_GameMainScene_prev_frame == false) {
                    //現フレームポーズで、前フレームポーズではない場合
                    //ポーズ発生後の、最初のフレーム処理はココへ
                    GgafDxInput::updateMouseState();
                    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にリセットするため
                                                     //連続２回呼び出す
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }

                //ポーズ進行時処理はココ

                //

                if (VB->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
                    //ポーズ時に、ポーズキーを押して離した場合の処理
                    //ポーズ解除時直後の初期処理はココへ
                    _TRACE_("UNPAUSE!");
                    P_GOD->setVB(VB_PLAY);
                    _pProg->getGazeScene()->unpause();//ポーズ解除！！
                    _pGamePauseScene->inactivate();
                }
            }
            _was_paused_flg_GameMainScene_prev_frame = _pProg->getGazeScene()->_was_paused_flg;
            //イベント待ち EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case GAMESCENE_PROG_ENDING: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        case GAMESCENE_PROG_GAME_OVER: {
            //##########  ゲームオーバー  ##########
            if (_pProg->isJustChanged()) {
            }
            //イベント待ち EVENT_GAME_OVER_FINISH
            break;
        }

        case GAMESCENE_PROG_FINISH: {
            //##########  ゲームシーン終了  ##########
            if (_pProg->isJustChanged()) {
                DefaultScene* pSubScene;
                for (map<progress, DefaultScene*>::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneTree(FADE_FRAMES);
                    }
                }
            }
            if (_pProg->getFrameInProgress() == FADE_FRAMES) {
                reset(); //リセット（最初の進捗状態に戻る）
            }
            break;
        }

        default:
            break;
    }
}

void GameScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {

//    switch (prm_no) {
//        case EVENT_GOD_WILL_DIE:
//
//            break;
//        default:
//            break;
//    }
    if (prm_no == EVENT_GOD_WILL_DIE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GOD_WILL_DIE) CommonSceneを拾い上げて後に解放されるようにします。");
        //神が死んでしまう前に
        //CommonSceneを拾い上げ、解放順序が後になるように操作する。
        addSubLast(P_MYSHIP_SCENE->extract());
        addSubLast(P_COMMON_SCENE->extract());
        P_MYSHIP_SCENE->moveFirstImmediately();
        P_COMMON_SCENE->moveFirstImmediately();
        //moveFirstImmediately()する理由は、解放は末尾ノードから行われるため。
        //先にCommonSceneが解放されないようにするため。
        //GgafCore::template<class T> GgafNode<T>::~GgafNode() のコメントを参照
    } else if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //プレタイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        _pProg->changeWithScene_Flipping(GAMESCENE_PROG_TITLE); //タイトルへ

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //タイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        //changeFlippingSubScene(GAMESCENE_PROG_DEMO);
        _pProg->changeWithScene_Crossfading(GAMESCENE_PROG_DEMO); //デモへ

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //デモシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        _pProg->changeWithScene_Crossfading(GAMESCENE_PROG_INIT); //最初へ

    } else if (prm_no == EVENT_GAMESTART) {
        //スタート
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        _pProg->changeWithScene_Crossfading(GAMESCENE_PROG_BEGINNING); //オープニング（ゲームモードセレクト）へ

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //ゲームモードセレクト完了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        _pProg->changeWithScene_Crossfading(GAMESCENE_PROG_MAIN,600);//メインへ
    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //とにかくタイトルへイベント発生
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        _pProg->changeWithScene_Flipping(GAMESCENE_PROG_TITLE); //タイトルへ
    }



    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        _pProg->changeWithScene_Crossfading(GAMESCENE_PROG_GAME_OVER); //ゲームオーバーへ
    } else if (prm_no == EVENT_GAME_OVER_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAME_OVER_FINISH)");
        _pProg->change(GAMESCENE_PROG_FINISH);
    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker::_num_check = 0;

//        if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//            CollisionChecker::_pLinearOctree->putTree();
//        }

        //本シーンの所属シーンの所属アクター全てについて当たり判定チェックを行う。
        //空間分割(八分木)アルゴリズムにより、チェック回数の最適化を行っています。
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
