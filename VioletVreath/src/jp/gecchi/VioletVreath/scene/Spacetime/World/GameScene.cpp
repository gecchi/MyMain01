#include "GameScene.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "PreDrawScene.h"
#include "GameScene/CommonScene.h"
#include "GameScene/GameBeginningScene.h"
#include "GameScene/GameDemoScene.h"
#include "GameScene/GameEndingScene.h"
#include "GameScene/GameMainScene.h"
#include "GameScene/GameMainScene/StageWorld.h"
#include "GameScene/GameOverScene.h"
#include "GameScene/GamePreTitleScene.h"
#include "GameScene/GameTitleScene.h"
#include "GameScene/MyShipScene.h"


using namespace GgafLib;
using namespace VioletVreath;

GameScene::GameScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) ,
pCommonScene_(nullptr),
pMyShipScene_(nullptr),
pStageWorld_(nullptr) {

    _class_name = "GameScene";
    pCommonScene_ = NEW CommonScene("Common");
    pCommonScene_->inactivate();
    appendChild(pCommonScene_);
    pMyShipScene_ = NEW MyShipScene("MyShipScene");
    pMyShipScene_->inactivate();
    appendChild(pMyShipScene_);
    pStageWorld_ = new StageWorld("StageWorld");
    pStageWorld_->inactivate();
    appendChild(pStageWorld_);

    pMenuBoardPause_ = NEW MenuBoardPause("MenuBoardPause");
    bringSceneMediator()->appendGroupChild(pMenuBoardPause_);

    appendChild(NEW GamePreTitleScene("PreGameTitle"));   //PHASE_PRE_TITLE
    appendChild(NEW GameTitleScene("GameTitle"));         //PHASE_TITLE
    appendChild(NEW GameDemoScene("GameDemo"));           //PHASE_DEMO
    appendChild(NEW GameBeginningScene("GameBeginning")); //PHASE_BEGINNING
    appendChild(NEW GameMainScene("GameMain"));           //PHASE_MAIN
    appendChild(NEW GameEndingScene("GameEnding"));       //PHASE_ENDING
    appendChild(NEW GameOverScene("GameOver"));           //PHASE_GAME_OVER
    getPhase()->relateChildScene(PHASE_PRE_TITLE, PHASE_GAME_OVER,  "PreGameTitle");
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    getBgmConductor()->ready(BGM_DEMO, "BGM_DEMO");
}

void GameScene::initialize() {
    _TRACE_(FUNC_NAME<<" いきますよDemoSceneさん");
}

void GameScene::onReset() {
    VV_VB_UI->clear();
    pCARETAKER->setVB(VV_VB_UI);
    DefaultScene* pChildScene;
    ScenePhase* pPhase = getPhase();
    for (PhaseSceneMap::const_iterator it = pPhase->_mapPhase2Scene.begin(); it != pPhase->_mapPhase2Scene.end(); ++it) {
        pChildScene = it->second;
        if (pChildScene) {
            pChildScene->resetTree();
            pChildScene->fadeinScene(0);
            pChildScene->inactivate();
        }
    }
    pCARETAKER->getSpacetime()->getCameraWorkerChanger()->cleanCamWorker();
    G_RANK = 0.0;
    G_RANKUP_LEVEL = 0;
    G_SCORE = 0;
    pPhase->reset(PHASE_INIT);
}

void GameScene::onActive() {
}

void GameScene::processBehavior() {
    Spacetime* pSpacetime = pCARETAKER->getSpacetime();
#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
    if (VVB->isPushedDown(0, VV_VB_UI_DEBUG) || GgafDx::Input::isPushedDownKey(DIK_Q)) {
        if (pCARETAKER->_d3dfillmode == D3DFILL_SOLID && pCARETAKER->_draw_hit_area_kind == 0) {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
            pCARETAKER->_draw_hit_area_kind = 1;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME && pCARETAKER->_draw_hit_area_kind == 1) {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
            pCARETAKER->_draw_hit_area_kind = 2;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME && pCARETAKER->_draw_hit_area_kind == 2) {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
            pCARETAKER->_draw_hit_area_kind = 0;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME && pCARETAKER->_draw_hit_area_kind == 0) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
            pCARETAKER->_draw_hit_area_kind = 1;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_SOLID && pCARETAKER->_draw_hit_area_kind == 1) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
            pCARETAKER->_draw_hit_area_kind = 2;
        } else if (pCARETAKER->_d3dfillmode == D3DFILL_SOLID && pCARETAKER->_draw_hit_area_kind == 2) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
            pCARETAKER->_draw_hit_area_kind = 0;
        }
    }
#endif
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getPrevWhenChanged()) {
        case PHASE_MAIN: {
            _TRACE_(FUNC_NAME<<" Phase has Just Changed 'From' PHASE_MAIN");
            VV_VB_UI->clear();
            pCARETAKER->setVB(VV_VB_UI);  //元に戻す
            break;
        }

        default: {
            break;
        }
    }


    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
//            _TRACE_(FUNC_NAME<<" Phase(=PHASE_INIT) has Just Changed");
            //pCARETAKER->syncTimeFrame(); //描画を中止して、フレームと時間の同期を行う
            if ((pPhase->hasArrivedFrameAt(120))) {
                _TRACE_("pCARETAKER->_fps = "<<pCARETAKER->_fps);
                pPhase->changeWithSceneCrossfading(PHASE_PRE_TITLE);
                getBgmConductor()->stop();
            }
            break;
        }

        case PHASE_PRE_TITLE: {
            //##########  タイトル前演出  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_PRE_TITLE)");
                getBgmConductor()->performFromTheBegining(BGM_DEMO);
            }
            //VV_VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VVB->isPushedDown(0, VV_VB_UI_EXECUTE)) { //skip
                pPhase->changeWithSceneFlipping(PHASE_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH イベント受付
            break;
        }

        case PHASE_TITLE: {
            //##########  タイトル  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_TITLE)");
            }
            //イベント待ち EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case PHASE_DEMO: {
            //##########  デモ  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_DEMO)");
            }
            //VV_VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VVB->isPushedDown(0, VV_VB_UI_EXECUTE)) {
                pPhase->changeWithSceneFlipping(PHASE_TITLE);
            }

            //或いは EVENT_GAMEDEMOSCENE_FINISH イベント受付
            break;
        }

        case PHASE_BEGINNING: {
            //##########  ゲーム開始（モード選択等）  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_BEGINNING)");
                getBgmConductor()->fadeoutStopAll(120);
            }
            //イベント待ち EVENT_GAMEMODE_DECIDE
            break;
        }

        case PHASE_MAIN: {
            //##########  ゲームメイン  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_MAIN)");
                VV_VB_PLAY->clear();
                pCARETAKER->setVB(VV_VB_PLAY); //プレイ用に変更
            }

            //今ポーズではない時
            if (!pPhase->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_)  {
                    //現フレームポーズではない、かつ前フレームポーズの場合。
                    //ポーズ解除から最初のフレーム処理はココへ
                    pSpacetime->getCameraWorkerChanger()->undoCameraWork();
                }

                //通常進行時処理はココ
                //
#ifdef MY_DEBUG
                if (VVB->isPushedDown(0, VV_VB_PAUSE) || GgafDx::Input::isPushedDownKey(DIK_ESCAPE) || is_frame_advance_) {
                    //ポーズではないときに、ポーズキーを押して離した場合の処理
                    //ポーズ発生時直後の初期処理はココへ
                    pauseGame();
                }
#else
                if (VVB->isPushedDown(0, VV_VB_PAUSE) || is_frame_advance_) {
                    //ポーズではないときに、ポーズキーを押して離した場合の処理
                    //ポーズ発生時直後の初期処理はココへ
                    pauseGame();
                }
#endif
            }
            //今ポーズ時
            if (pPhase->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_ == false) {
                    //現フレームポーズで、前フレームポーズではない場合
                    //ポーズ発生後の、最初のフレーム処理はココへ
                    GgafDx::Input::updateMouseState();
                    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にリセットするため
                                                     //連続２回呼び出す
                    pSpacetime->getCameraWorkerChanger()->changeCameraWork("PauseCamWorker");
                }

                //ポーズ進行時処理はココ
                //

                if (pMenuBoardPause_->hasJustSunk() || is_frame_advance_) {
                    //ポーズ時に、ポーズキーを押して離した場合の処理
                    //ポーズ解除時直後の初期処理はココへ
                    _TRACE_("UNPAUSE!");
                    pCARETAKER->setVB(VV_VB_PLAY);
                    pPhase->getGazedScene()->unpause();//ポーズ解除！！
                }
            }
            //イベント待ち EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case PHASE_ENDING: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_ENDING)");
            }
            break;
        }

        case PHASE_GAME_OVER: {
            //##########  ゲームオーバー  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_GAME_OVER)");
            }
            //イベント待ち EVENT_GAME_OVER_FINISH
            break;
        }

        case PHASE_FINISH: {
            //##########  ゲームシーン終了  ##########
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_FINISH)");
                DefaultScene* pChildScene;
                for (PhaseSceneMap::const_iterator it = pPhase->_mapPhase2Scene.begin(); it != pPhase->_mapPhase2Scene.end(); ++it) {
                    pChildScene = it->second;
                    if (pChildScene) {
                        pChildScene->fadeoutSceneWithBgmTree(FADE_FRAMES);
                        pChildScene->inactivateDelay(FADE_FRAMES+10);
                    }
                }
            }
            if (pPhase->hasArrivedFrameAt(FADE_FRAMES+20)) {
                reset(); //リセット（最初のフェーズに戻る）
            }
            break;
        }

        default: {
            break;
        }
    }

    DefaultScene* pGazed = pPhase->getGazedScene();
    if (pGazed) {
        was_paused_flg_GameMainScene_prev_frame_ = pGazed->wasPaused();
    }

}

void GameScene::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
//    switch (prm_event_val) {
//        case EVENT_CARETAKER_WILL_DEMISE:
//
//            break;
//        default:
//            break;
//    }
    ScenePhase* pPhase = getPhase();
    if (prm_event_val == EVENT_CARETAKER_WILL_DEMISE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_CARETAKER_WILL_DEMISE) CommonSceneを拾い上げて後に解放されるようにします。");
        //管理者が死んでしまう前に
        //CommonSceneを拾い上げ、解放順序が後になるように操作する。(共有デポジトリとかあるし)
        appendChild(pMYSHIP_SCENE->extract());
        appendChild(pCOMMON_SCENE->extract());
        pMYSHIP_SCENE->moveFirst();
        pCOMMON_SCENE->moveFirst();
        //moveFirst()する理由は、解放は末尾ノードから行われるため。
        //先にCommonSceneが解放されないようにするため。
        //template<class T> GgafCore::Node<T>::~GgafCore::Node() のコメントを参照
    } else if (prm_event_val == EVENT_PREGAMETITLESCENE_FINISH) {
        //プレタイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        pPhase->changeWithSceneFlipping(PHASE_TITLE); //タイトルへ

    } else if (prm_event_val == EVENT_GAMETITLESCENE_FINISH) {
        //タイトルシーンをボーっと見てたので時間切れ終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        pPhase->changeWithSceneCrossfading(PHASE_DEMO); //デモへ

    } else if (prm_event_val == EVENT_GAMEDEMOSCENE_FINISH) {
        //デモシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        pPhase->changeWithSceneFadeoutFadein(PHASE_INIT,120,120); //最初へ
        getBgmConductor()->fadeoutStopAll(120);

    } else if (prm_event_val == EVENT_GAMESTART) {
        //スタート
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        pPhase->changeWithSceneCrossfading(PHASE_BEGINNING); //オープニング（ゲームモードセレクト）へ

    } else if (prm_event_val == EVENT_GAMEMODE_DECIDE) {
        //ゲームモードセレクト完了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        pPhase->changeWithSceneCrossfading(PHASE_MAIN,600);//メインへ
    } else if (prm_event_val == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        if (pPhase->getCurrent() == PHASE_DEMO) {
            //もし万が一、デモシーン中の全機消滅ならば、デモシーン終了
            pPhase->changeWithSceneFadeoutFadein(PHASE_INIT, 120, 120); //最初へ
            getBgmConductor()->fadeoutStopAll(120);
        } else {
            pPhase->changeWithSceneCrossfading(PHASE_GAME_OVER); //ゲームオーバーへ
        }
    } else if (prm_event_val == EVENT_GAMEOVERSCENE_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEOVERSCENE_FINISH)");
        pPhase->change(PHASE_FINISH);
    } else if (prm_event_val == EVENT_GO_TO_TITLE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GO_TO_TITLE)");
        _TRACE_("UNPAUSE!(because EVENT_GO_TO_TITLE)");
        pCARETAKER->setVB(VV_VB_PLAY);
        pPhase->getGazedScene()->unpause();//ポーズ解除！！
        pPhase->change(PHASE_FINISH);
    }
}


void GameScene::processJudgement() {

}
void GameScene::pauseGame() {
    is_frame_advance_ = false;
    _TRACE_("PAUSE!");
    pCARETAKER->setVB(VV_VB_UI);  //入力はＵＩに切り替え
    getPhase()->getGazedScene()->pause(); //ポーズ！！
    pMenuBoardPause_->rise(PX_C(100), PX_C(20));
}

GameScene::~GameScene() {
}
