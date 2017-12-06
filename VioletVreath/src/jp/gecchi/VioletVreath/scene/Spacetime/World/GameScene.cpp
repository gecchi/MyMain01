#include "GameScene.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"
#include "jp/ggaf/core/util/GgafLinearTreeRounder.hpp"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameBeginningScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameDemoScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameEndingScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameOverScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GamePreTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/PreDrawScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) ,
pCommonScene_(nullptr),
pMyShipScene_(nullptr),
pStageWorld_(nullptr) {

    _class_name = "GameScene";
    useProgress(PROG_BANPEI);
    pCommonScene_ = NEW CommonScene("Common");
    pCommonScene_->inactivate();
    addSubLast(pCommonScene_);
    pMyShipScene_ = NEW MyShipScene("MyShipScene");
    pMyShipScene_->inactivate();
    addSubLast(pMyShipScene_);
    pStageWorld_ = new StageWorld("StageWorld");
    pStageWorld_->inactivate();
    addSubLast(pStageWorld_);

    pMenuBoardPause_ = NEW MenuBoardPause("MenuBoardPause");
    bringSceneMediator()->addSubGroup(pMenuBoardPause_);

    addSubLast(NEW GamePreTitleScene("PreGameTitle"));
    addSubLast(NEW GameTitleScene("GameTitle"));
    addSubLast(NEW GameDemoScene("GameDemo"));
    addSubLast(NEW GameBeginningScene("GameBeginning"));
    addSubLast(NEW GameMainScene("GameMain"));
    addSubLast(NEW GameEndingScene("GameEnding"));
    addSubLast(NEW GameOverScene("GameOver"));
    getProgress()->relateSubScene(PROG_PRE_TITLE, PROG_GAME_OVER,  "PreGameTitle");
    is_frame_advance_ = false;

    was_paused_flg_GameMainScene_prev_frame_ = false;

    getConductor()->ready(BGM_DEMO, "OGG_BGM_DEMO");
}

void GameScene::initialize() {
    _TRACE_(FUNC_NAME<<" いきますよDemoSceneさん");
}

void GameScene::onReset() {
    VB_UI->clear();
    pGOD->setVB(VB_UI);
    DefaultScene* pSubScene;
    SceneProgress* pProg = getProgress();
    for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); ++it) {
        pSubScene = it->second;
        if (pSubScene) {
            pSubScene->resetTree();
            pSubScene->fadeinScene(0);
            pSubScene->inactivate();
        }
    }
    pGOD->getSpacetime()->resetCamWorker();
    G_RANK = 0.0;
    G_RANKUP_LEVEL = 0;
    G_SCORE = 0;
    pProg->reset(PROG_INIT);
}

void GameScene::onActive() {
}

void GameScene::processBehavior() {
    Spacetime* pSpacetime = pGOD->getSpacetime();
#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
    if (VB->isPushedDown(VB_UI_DEBUG) || GgafDxInput::isPushedDownKey(DIK_Q)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif
    SceneProgress* pProg = getProgress();
    switch (pProg->getFromProgOnChange()) {
        case PROG_MAIN: {
            _TRACE_(FUNC_NAME<<" Prog has Just Changed 'From' PROG_MAIN");
            VB_UI->clear();
            pGOD->setVB(VB_UI);  //元に戻す
            break;
        }

        default: {
            break;
        }
    }


    switch (pProg->get()) {
        case PROG_INIT: {
//            _TRACE_(FUNC_NAME<<" Prog(=PROG_INIT) has Just Changed");
            //pGOD->syncTimeFrame(); //描画を中止して、フレームと時間の同期を行う
            if ((pProg->hasArrivedAt(120))) {
                _TRACE_("pGOD->_fps = "<<pGOD->_fps);
                pProg->changeWithSceneCrossfading(PROG_PRE_TITLE);
                World* pWorld = pSpacetime->getWorld();
                pWorld->pPreDrawScene_->inactivateTree();
                pWorld->pPreDrawScene_->pauseTree();
                getConductor()->stop();
            }
            break;
        }

        case PROG_PRE_TITLE: {
            //##########  タイトル前演出  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_PRE_TITLE)");
                getConductor()->performFromTheBegining(BGM_DEMO);
            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) { //skip
                pProg->changeWithSceneFlipping(PROG_TITLE);
            }
            //EVENT_PREGAMETITLESCENE_FINISH イベント受付
            break;
        }

        case PROG_TITLE: {
            //##########  タイトル  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_TITLE)");
            }
            //イベント待ち EVENT_GAMETITLESCENE_FINISH or EVENT_GAMESTART
            break;
        }

        case PROG_DEMO: {
            //##########  デモ  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_DEMO)");
            }
            //VB_UI_EXECUTE で、スキップしてTITLEへ
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                pProg->changeWithSceneFlipping(PROG_TITLE);
            }

            //或いは EVENT_GAMEDEMOSCENE_FINISH イベント受付
            break;
        }

        case PROG_BEGINNING: {
            //##########  ゲーム開始（モード選択等）  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_BEGINNING)");
                getConductor()->fadeoutStopAll(120);
            }
            //イベント待ち EVENT_GAMEMODE_DECIDE
            break;
        }

        case PROG_MAIN: {
            //##########  ゲームメイン  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_MAIN)");
                VB_PLAY->clear();
                pGOD->setVB(VB_PLAY); //プレイ用に変更
            }

            //今ポーズではない時
            if (!pProg->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_)  {
                    //現フレームポーズではない、かつ前フレームポーズの場合。
                    //ポーズ解除から最初のフレーム処理はココへ
                    pSpacetime->undoCameraWork();
                }

                //通常進行時処理はココ
                //
#ifdef MY_DEBUG
                if (VB->isPushedDown(VB_PAUSE) || GgafDxInput::isPushedDownKey(DIK_ESCAPE) || is_frame_advance_) {
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
            if (pProg->getGazedScene()->wasPaused()) {
                if (was_paused_flg_GameMainScene_prev_frame_ == false) {
                    //現フレームポーズで、前フレームポーズではない場合
                    //ポーズ発生後の、最初のフレーム処理はココへ
                    GgafDxInput::updateMouseState();
                    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にリセットするため
                                                     //連続２回呼び出す
                    pSpacetime->changeCameraWork("PauseCamWorker");
                }

                //ポーズ進行時処理はココ
                //

                if (pMenuBoardPause_->hasJustSunk() || is_frame_advance_) {
                    //ポーズ時に、ポーズキーを押して離した場合の処理
                    //ポーズ解除時直後の初期処理はココへ
                    _TRACE_("UNPAUSE!");
                    pGOD->setVB(VB_PLAY);
                    pProg->getGazedScene()->unpauseTree();//ポーズ解除！！
                }
            }
            //イベント待ち EVENT_ALL_MY_SHIP_WAS_DESTROYED
            break;
        }

        case PROG_ENDING: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_ENDING)");
            }
            break;
        }

        case PROG_GAME_OVER: {
            //##########  ゲームオーバー  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_GAME_OVER)");
            }
            //イベント待ち EVENT_GAME_OVER_FINISH
            break;
        }

        case PROG_FINISH: {
            //##########  ゲームシーン終了  ##########
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_FINISH)");
                DefaultScene* pSubScene;
                for (ProgSceneMap::const_iterator it = pProg->_mapProg2Scene.begin(); it != pProg->_mapProg2Scene.end(); ++it) {
                    pSubScene = it->second;
                    if (pSubScene) {
                        pSubScene->fadeoutSceneWithBgmTree(FADE_FRAMES);
                        pSubScene->inactivateDelay(FADE_FRAMES+10);
                    }
                }
            }
            if (pProg->hasArrivedAt(FADE_FRAMES+20)) {
                reset(); //リセット（最初の進捗状態に戻る）
            }
            break;
        }

        default: {
            break;
        }
    }

    DefaultScene* pGazed = pProg->getGazedScene();
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
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_GOD_WILL_DEMISE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GOD_WILL_DEMISE) CommonSceneを拾い上げて後に解放されるようにします。");
        //神が死んでしまう前に
        //CommonSceneを拾い上げ、解放順序が後になるように操作する。(共有デポジトリとかあるし)
        addSubLast(pMYSHIP_SCENE->extract());
        addSubLast(pCOMMON_SCENE->extract());
        pMYSHIP_SCENE->moveFirst();
        pCOMMON_SCENE->moveFirst();
        //moveFirst()する理由は、解放は末尾ノードから行われるため。
        //先にCommonSceneが解放されないようにするため。
        //GgafCore::template<class T> GgafNode<T>::~GgafNode() のコメントを参照
    } else if (prm_no == EVENT_PREGAMETITLESCENE_FINISH) {
        //プレタイトルシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_PREGAMETITLESCENE_FINISH)");
        pProg->changeWithSceneFlipping(PROG_TITLE); //タイトルへ

    } else if (prm_no == EVENT_GAMETITLESCENE_FINISH) {
        //タイトルシーンをボーっと見てたので時間切れ終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMETITLESCENE_FINISH)");
        pProg->changeWithSceneCrossfading(PROG_DEMO); //デモへ

    } else if (prm_no == EVENT_GAMEDEMOSCENE_FINISH) {
        //デモシーン終了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEDEMOSCENE_FINISH)");
        pProg->changeWithSceneFadeoutFadein(PROG_INIT,120,120); //最初へ
        getConductor()->fadeoutStopAll(120);

    } else if (prm_no == EVENT_GAMESTART) {
        //スタート
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMESTART)");
        pProg->changeWithSceneCrossfading(PROG_BEGINNING); //オープニング（ゲームモードセレクト）へ

    } else if (prm_no == EVENT_GAMEMODE_DECIDE) {
        //ゲームモードセレクト完了
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEMODE_DECIDE)");
        pProg->changeWithSceneCrossfading(PROG_MAIN,600);//メインへ
    } else if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
        _TRACE_("GameScene::onCatchEvent(EVENT_ALL_MY_SHIP_WAS_DESTROYED)");
        if (pProg->get() == PROG_DEMO) {
            //もし万が一、デモシーン中の全機消滅ならば、デモシーン終了
            pProg->changeWithSceneFadeoutFadein(PROG_INIT, 120, 120); //最初へ
            getConductor()->fadeoutStopAll(120);
        } else {
            pProg->changeWithSceneCrossfading(PROG_GAME_OVER); //ゲームオーバーへ
        }
    } else if (prm_no == EVENT_GAMEOVERSCENE_FINISH) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GAMEOVERSCENE_FINISH)");
        pProg->change(PROG_FINISH);
    } else if (prm_no == EVENT_GO_TO_TITLE) {
        _TRACE_("GameScene::onCatchEvent(EVENT_GO_TO_TITLE)");
        _TRACE_("UNPAUSE!(because EVENT_GO_TO_TITLE)");
        pGOD->setVB(VB_PLAY);
        pProg->getGazedScene()->unpauseTree();//ポーズ解除！！
        pProg->change(PROG_FINISH);
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

        OctreeRounder* pHitCheckRounder = pGOD->getSpacetime()->getLinearOctreeHitCheckRounder();
#ifdef MY_DEBUG
        if (GgafDxInput::isPushedDownKey(DIK_I)) {
            pGOD->getSpacetime()->getLinearOctree()->putTree();
        }
#endif
        //八分木アルゴリズムでヒットチェック
        pHitCheckRounder->executeAll(
            KIND_CHIKEI,
            KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT
        );
        pHitCheckRounder->executeAll(
            KIND_ITEM,
            KIND_MY_BODY_CHIKEI_HIT
        );
        pHitCheckRounder->executeAll(
            KIND_MY,
            KIND_ENEMY_BODY
        );
        pHitCheckRounder->executeAll(
            KIND_ENEMY_SHOT,
            KIND_MY_BODY
        );


    }
}
void GameScene::pauseGame() {
    is_frame_advance_ = false;
    _TRACE_("PAUSE!");
    pGOD->setVB(VB_UI);  //入力はＵＩに切り替え
    getProgress()->getGazedScene()->pauseTree(); //ポーズ！！
    pMenuBoardPause_->rise(PX_C(100), PX_C(20));
}

GameScene::~GameScene() {
}
