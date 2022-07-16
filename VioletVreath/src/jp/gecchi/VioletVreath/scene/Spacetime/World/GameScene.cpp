#include "GameScene.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/core/util/LinearOctree.h"
#include "jp/ggaf/core/util/LinearTreeRounder.hpp"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/God.h"
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

    appendChild(NEW GamePreTitleScene("PreGameTitle"));
    appendChild(NEW GameTitleScene("GameTitle"));
    appendChild(NEW GameDemoScene("GameDemo"));
    appendChild(NEW GameBeginningScene("GameBeginning"));
    appendChild(NEW GameMainScene("GameMain"));
    appendChild(NEW GameEndingScene("GameEnding"));
    appendChild(NEW GameOverScene("GameOver"));
    getPhase()->relateChildScene(PHASE_PRE_TITLE, PHASE_GAME_OVER,  "PreGameTitle");
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    getBgmConductor()->ready(BGM_DEMO, "BGM_DEMO");
    pHitCheckRounder_ = nullptr;
}

void GameScene::initialize() {
    _TRACE_(FUNC_NAME<<" いきますよDemoSceneさん");
    pHitCheckRounder_ = pGOD->getSpacetime()->getLinearOctreeHitCheckRounder();
}

void GameScene::onReset() {
    VB_UI->clear();
    pGOD->setVB(VB_UI);
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
    pGOD->getSpacetime()->getCameraWorkerChanger()->cleanCamWorker();
    G_RANK = 0.0;
    G_RANKUP_LEVEL = 0;
    G_SCORE = 0;
    pPhase->reset(PHASE_INIT);
}

void GameScene::onActive() {
}

void GameScene::processBehavior() {
    Spacetime* pSpacetime = pGOD->getSpacetime();
#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
    if (VB->isPushedDown(VB_UI_DEBUG) || GgafDx::Input::isPushedDownKey(DIK_Q)) {
        if (pGOD->_d3dfillmode == D3DFILL_WIREFRAME) {
            pGOD->_d3dfillmode = D3DFILL_SOLID;
        } else {
            pGOD->_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getPrevWhenChanged()) {
        case PHASE_MAIN: {
            _TRACE_(FUNC_NAME<<" Phase has Just Changed 'From' PHASE_MAIN");
            VB_UI->clear();
            pGOD->setVB(VB_UI);  //元に戻す
            break;
        }

        default: {
            break;
        }
    }


    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
//            _TRACE_(FUNC_NAME<<" Phase(=PHASE_INIT) has Just Changed");
            //pGOD->syncTimeFrame(); //描画を中止して、フレームと時間の同期を行う
            if ((pPhase->hasArrivedFrameAt(120))) {
                _TRACE_("pGOD->_fps = "<<pGOD->_fps);
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
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
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
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
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
                VB_PLAY->clear();
                pGOD->setVB(VB_PLAY); //プレイ用に変更
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
                if (VB->isPushedDown(VB_PAUSE) || GgafDx::Input::isPushedDownKey(DIK_ESCAPE) || is_frame_advance_) {
                    //ポーズではないときに、ポーズキーを押して離した場合の処理
                    //ポーズ発生時直後の初期処理はココへ
                    pauseGame();
                }
#else
                if (VB->isPushedDown(VB_PAUSE) || is_frame_advance_) {
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
                    pGOD->setVB(VB_PLAY);
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

void GameScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
//    switch (prm_no) {
//        case EVENT_GOD_WILL_DEMISE:
//
//            break;
//        default:
//            break;
//    }
    ScenePhase* pPhase = getPhase();
    if (prm_no == EVENT_GOD_WILL_DEMISE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GOD_WILL_DEMISE) CommonSceneを拾い上げて後に解放されるようにします。");
        //神が死んでしまう前に
        //CommonSceneを拾い上げ、解放順序が後になるように操作する。(共有デポジトリとかあるし)
        appendChild(pMYSHIP_SCENE->extract());
        appendChild(pCOMMON_SCENE->extract());
        pMYSHIP_SCENE->moveFirst();
        pCOMMON_SCENE->moveFirst();
        //moveFirst()する理由は、解放は末尾ノードから行われるため。
        //先にCommonSceneが解放されないようにするため。
        //template<class T> GgafCore::Node<T>::~GgafCore::Node() のコメントを参照
    } else if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //プレタイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        pPhase->changeWithSceneFlipping(PHASE_TITLE); //タイトルへ

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //タイトルシーンをボーっと見てたので時間切れ終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        pPhase->changeWithSceneCrossfading(PHASE_DEMO); //デモへ

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //デモシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        pPhase->changeWithSceneFadeoutFadein(PHASE_INIT,120,120); //最初へ
        getBgmConductor()->fadeoutStopAll(120);

    } else if (prm_no == EVENT_GAMESTART) {
        //スタート
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        pPhase->changeWithSceneCrossfading(PHASE_BEGINNING); //オープニング（ゲームモードセレクト）へ

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //ゲームモードセレクト完了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        pPhase->changeWithSceneCrossfading(PHASE_MAIN,600);//メインへ
    } else if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        if (pPhase->getCurrent() == PHASE_DEMO) {
            //もし万が一、デモシーン中の全機消滅ならば、デモシーン終了
            pPhase->changeWithSceneFadeoutFadein(PHASE_INIT, 120, 120); //最初へ
            getBgmConductor()->fadeoutStopAll(120);
        } else {
            pPhase->changeWithSceneCrossfading(PHASE_GAME_OVER); //ゲームオーバーへ
        }
    } else if (prm_no == EVENT_GAMEOVERSCENE_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEOVERSCENE_FINISH)");
        pPhase->change(PHASE_FINISH);
    } else if (prm_no == EVENT_GO_TO_TITLE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GO_TO_TITLE)");
        _TRACE_("UNPAUSE!(because EVENT_GO_TO_TITLE)");
        pGOD->setVB(VB_PLAY);
        pPhase->getGazedScene()->unpause();//ポーズ解除！！
        pPhase->change(PHASE_FINISH);
    }
}


void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
#ifdef MY_DEBUG
        CollisionChecker::_num_check = 0;
#endif
        //本シーンの所属シーンの所属アクター全てについて当たり判定チェックを行う。
        //空間分割(八分木)アルゴリズムにより、チェック回数の最適化を行っています。
        //詳細は 「種別相関定義コピペツール.xls」 の 「種別相関」 シート参照

        OctreeRounder* pHitCheckRounder = pHitCheckRounder_;
#ifdef MY_DEBUG
        if (GgafDx::Input::isPushedDownKey(DIK_I)) {
            pGOD->getSpacetime()->getLinearOctree()->putTree();
        }
#endif
        //八分木アルゴリズムでヒットチェック
        static const kind_t group_A1 = KIND_CHIKEI;
        static const kind_t group_B1 = KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT;
        pHitCheckRounder->executeAll(group_A1, group_B1);

        static const kind_t group_A2 = KIND_ITEM;
        static const kind_t group_B2 = KIND_MY_BODY_CHIKEI_HIT;
        pHitCheckRounder->executeAll(group_A2, group_B2);

        static const kind_t group_A3 = KIND_MY;
        static const kind_t group_B3 = KIND_ENEMY_BODY;
        pHitCheckRounder->executeAll(group_A3, group_B3);

        static const kind_t group_A4 = KIND_ENEMY_SHOT;
        static const kind_t group_B4 = KIND_MY_BODY;
        pHitCheckRounder->executeAll(group_A4, group_B4);
    }
}
void GameScene::pauseGame() {
    is_frame_advance_ = false;
    _TRACE_("PAUSE!");
    pGOD->setVB(VB_UI);  //入力はＵＩに切り替え
    getPhase()->getGazedScene()->pause(); //ポーズ！！
    pMenuBoardPause_->rise(PX_C(100), PX_C(20));
}

GameScene::~GameScene() {
}
