#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) ,
pCommonScene_(nullptr),
pMyShip_Scene(nullptr),
pStageWorld_(nullptr) {

    _class_name = "GameScene";
    useProgress(GameScene::PROG_FINISH);
    pCommonScene_ = NEW CommonScene("Common");
    pCommonScene_->inactivateImmed();
    addSubLast(pCommonScene_);
    pMyShip_Scene = NEW MyShipScene("MyShipScene");
    pMyShip_Scene->inactivateImmed();
    addSubLast(pMyShip_Scene);
    pStageWorld_ = new StageWorld("StageWorld");
    pStageWorld_->inactivateImmed();
    addSubLast(pStageWorld_);

    pMenuBoardPause_ = NEW MenuBoardPause("MenuBoardPause");
    getDirector()->addSubGroup(pMenuBoardPause_);

    addSubLast(NEW GamePreTitleScene("PreGameTitle"));
    addSubLast(NEW GameTitleScene("GameTitle"));
    addSubLast(NEW GameDemoScene("GameDemo"));
    addSubLast(NEW GameBeginningScene("GameBeginning"));
    addSubLast(NEW GameMainScene("GameMain"));
    addSubLast(NEW GameEndingScene("GameEnding"));
    addSubLast(NEW GameOverScene("GameOver"));

    _pProg->relatSubScene(GameScene::PROG_PRE_TITLE, GameScene::PROG_GAME_OVER,  "PreGameTitle");
    //たまご
    //addSubLast(NEW TamagoScene("TamagoScene"));
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "OGG_BGM_DEMO");

}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
}

void GameScene::onReset() {

    VB_UI->clear();
    P_GOD->setVB(VB_UI);

    DefaultScene* pSubScene;
    for (ProgSceneMap::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->fadeinSceneTree(0);
            pSubScene->inactivateImmed();
        }
    }
    P_UNIVERSE->resetCamWorker();
    GameGlobal::init();
    _pProg->set(GameScene::PROG_INIT);
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

    switch (_pProg->getFromProgOnChange()) {
        case GameScene::PROG_MAIN: {
            _TRACE_("GameScene::processBehavior() Prog has Just Changed 'From' GameScene::PROG_MAIN");
            VB_UI->clear();
            P_GOD->setVB(VB_UI);  //元に戻す
            break;
        }

        default:
            break;
    }


    switch (_pProg->get()) {
        case GameScene::PROG_INIT: {
//            _TRACE_("GameScene::processBehavior() Prog(=GameScene::PROG_INIT) has Just Changed");
            //P_GOD->syncTimeFrame(); //描画を中止して、フレームと時間の同期を行う
            if ((_pProg->getFrameInProgress() == 120)) {
                _TRACE_("P_GOD->_fps = "<<P_GOD->_fps);
                _pProg->changeWithSceneCrossfading(GameScene::PROG_PRE_TITLE);
                P_WORLD->pPreDrawScene_->inactivateTreeImmed();
                P_WORLD->pPreDrawScene_->pauseTreeImmed();

            }
            break;
        }

        case GameScene::PROG_PRE_TITLE: {
            //##########  タイトル前演出  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_PRE_TITLE)");
                _pBgmPerformer->play_fadein(0);
            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                _pProg->changeWithSceneFlipping(GameScene::PROG_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH イベント受付
            break;
        }

        case GameScene::PROG_TITLE: {
            //##########  タイトル  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_TITLE)");
            }
            //イベント待ち EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case GameScene::PROG_DEMO: {
            //##########  デモ  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_DEMO)");
            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _pProg->changeWithSceneFlipping(GameScene::PROG_TITLE);
            }

            //或いは EVENT_GAMEDEMOSCENE_FINISH イベント受付
            break;
        }

        case GameScene::PROG_BEGINNING: {
            //##########  ゲーム開始（モード選択等）  ##########
            if (_pProg->hasJustChanged()) {
                _pBgmPerformer->fadeout_stop();
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_BEGINNING)");
            }
            //イベント待ち EVENT_GAMEMODE_DECIDE
            break;
        }

        case GameScene::PROG_MAIN: {
            //##########  ゲームメイン  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_MAIN)");
                VB_PLAY->clear();
                P_GOD->setVB(VB_PLAY); //プレイ用に変更
            }

            //今ポーズではない時
            if (!_pProg->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_ == true)  {
                    //現フレームポーズではない、かつ前フレームポーズの場合。
                    //ポーズ解除から最初のフレーム処理はココへ
                    P_UNIVERSE->undoCameraWork();
                }

                //通常進行時処理はココ
                //

                if (VB->isPushedDown(VB_PAUSE) || is_frame_advance_) {
                    //ポーズではないときに、ポーズキーを押して離した場合の処理
                    //ポーズ発生時直後の初期処理はココへ
                    is_frame_advance_ = false;
                    _TRACE_("PAUSE!");
                    P_GOD->setVB(VB_UI);  //入力はＵＩに切り替え
                    _pProg->getGazedScene()->pauseTree(); //ポーズ！！
                    pMenuBoardPause_->rise(PX_C(100), PX_C(20));
                }
            }
            //今ポーズ時
            if (_pProg->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_ == false) {
                    //現フレームポーズで、前フレームポーズではない場合
                    //ポーズ発生後の、最初のフレーム処理はココへ
                    GgafDxInput::updateMouseState();
                    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にリセットするため
                                                     //連続２回呼び出す
                    P_UNIVERSE->switchCameraWork("PauseCamWorker");
                }

                //ポーズ進行時処理はココ
                //

                if (pMenuBoardPause_->isJustSink() || is_frame_advance_) {
                    //ポーズ時に、ポーズキーを押して離した場合の処理
                    //ポーズ解除時直後の初期処理はココへ
                    _TRACE_("UNPAUSE!");
                    P_GOD->setVB(VB_PLAY);
                    _pProg->getGazedScene()->unpauseTree();//ポーズ解除！！
                }
            }
            was_paused_flg_GameMainScene_prev_frame_ = _pProg->getGazedScene()->wasPaused();
            //イベント待ち EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case GameScene::PROG_ENDING: {
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_ENDING)");
            }
            break;
        }

        case GameScene::PROG_GAME_OVER: {
            //##########  ゲームオーバー  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_GAME_OVER)");
            }
            //イベント待ち EVENT_GAME_OVER_FINISH
            break;
        }

        case GameScene::PROG_FINISH: {
            //##########  ゲームシーン終了  ##########
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameScene::processBehavior() Prog has Just Changed (to GameScene::PROG_FINISH)");
                DefaultScene* pSubScene;
                for (ProgSceneMap::const_iterator it = _pProg->_mapProg2Scene.begin(); it != _pProg->_mapProg2Scene.end(); it++) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneWithBgmTree(FADE_FRAMES);
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

void GameScene::onCatchEvent(hashval prm_no, void* prm_pSource) {

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
        P_MYSHIP_SCENE->moveFirstImmed();
        P_COMMON_SCENE->moveFirstImmed();
        //moveFirstImmed()する理由は、解放は末尾ノードから行われるため。
        //先にCommonSceneが解放されないようにするため。
        //GgafCore::template<class T> GgafNode<T>::~GgafNode() のコメントを参照
    } else if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //プレタイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        _pProg->changeWithSceneFlipping(GameScene::PROG_TITLE); //タイトルへ

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //タイトルシーンをボーっと見てたので時間切れ終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        _pProg->changeWithSceneCrossfading(GameScene::PROG_DEMO); //デモへ

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //デモシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        _pProg->changeWithSceneCrossfading(GameScene::PROG_INIT); //最初へ

    } else if (prm_no == EVENT_GAMESTART) {
        //スタート
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        _pProg->changeWithSceneCrossfading(GameScene::PROG_BEGINNING); //オープニング（ゲームモードセレクト）へ

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //ゲームモードセレクト完了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        _pProg->changeWithSceneCrossfading(GameScene::PROG_MAIN,600);//メインへ
    } else if (prm_no == EVENT_GOTO_GAMETITLE) {
        //とにかくタイトルへイベント発生
        _TRACE_("GameScene::onCatchEvent(EVENT_GOTO_GAMETITLE)");
        _pProg->changeWithSceneFlipping(GameScene::PROG_TITLE); //タイトルへ
    }


    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        _pProg->changeWithSceneCrossfading(GameScene::PROG_GAME_OVER); //ゲームオーバーへ
    } else if (prm_no == EVENT_GAMEOVERSCENE_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEOVERSCENE_FINISH)");
        _pProg->change(GameScene::PROG_FINISH);
    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker3D::_num_check = 0;

//        if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//            CollisionChecker3D::_pLinearOctree->putTree();
//        }

        //本シーンの所属シーンの所属アクター全てについて当たり判定チェックを行う。
        //空間分割(八分木)アルゴリズムにより、チェック回数の最適化を行っています。
        //詳細は 「種別相関定義コピペツール.xls」 の 「種別相関」 シート参照

        //八分木アルゴリズムでヒットチェック
        CollisionChecker3D::_pLinearOctree->executeAllHitChk(
        KIND_CHIKEI,
        KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT
        );
        CollisionChecker3D::_pLinearOctree->executeAllHitChk(
        KIND_ITEM,
        KIND_MY_BODY_CHIKEI_HIT
        );
        CollisionChecker3D::_pLinearOctree->executeAllHitChk(
        KIND_MY,
        KIND_ENEMY_BODY
        );
        CollisionChecker3D::_pLinearOctree->executeAllHitChk(
        KIND_ENEMY_SHOT,
        KIND_MY_BODY
        );


    }
}

GameScene::~GameScene() {
}
