#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(10);
    _pProgress->change(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

}
void GameDemoScene::reset() {
    _pProgress->change(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    unblindScene();
}
void GameDemoScene::onActive() {
}
void GameDemoScene::initialize() {
    reset();
}

void GameDemoScene::processBehavior() {

    switch (_pProgress->getChangedFrom()) {
        default:
            break;
    }

    switch (_pProgress->get()) {
        case GAMEDEMO_SCENE_PROG_INIT:
            _pProgress->change(GAMEDEMO_SCENE_PROG_DEMOPLAY);
            break;

        case GAMEDEMO_SCENE_PROG_DEMOPLAY:
            if (_pProgress->isJustChanged()) {
                _pStringBoard01->update(100, 100, "DEMOPLAY NOW");
                _pStringBoard02->update(100, 150, "GAME OVER");
            }
            if (_pProgress->getActivePartFrameInProgress() == 180) {
                _pProgress->change(GAMEDEMO_SCENE_PROG_RANKING);
            }

        case GAMEDEMO_SCENE_PROG_RANKING:
            if (_pProgress->isJustChanged()) {
                _pStringBoard01->update(100, 100, "RANKING NOW");
                _pStringBoard02->update(100, 150, "GAME OVER");
            }
            if (_pProgress->getActivePartFrameInProgress() == 180) {
                _pProgress->change(GAMEDEMO_SCENE_PROG_FINISH);
            }

        case GAMEDEMO_SCENE_PROG_FINISH:
            if (_pProgress->isJustChanged()) {
                fadeoutSceneTree(FADE_FRAME);
                inactivateDelay(FADE_FRAME);
                throwEventToUpperTree(EVENT_GAMEDEMO_SCENE_FINISH); //終わったイベント発動
            }

        default:
            break;
    }


//
//
//    //GAMEDEMO_SCENE_PROG_INIT 時の処理
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_INIT)) {
//    }
//    if (_pProgress->get() == GAMEDEMO_SCENE_PROG_INIT) {
//        _pProgress->change(GAMEDEMO_SCENE_PROG_DEMOPLAY);
//    }
//    if (_pProgress->wasChangedFrom(GAMEDEMO_SCENE_PROG_INIT)) {
//    }
//
//
//    //デモプレイ GAMEDEMO_SCENE_PROG_DEMOPLAY 時の処理
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
//        _TRACE_("GameDemoScene _pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_DEMOPLAY)");
//        _pStringBoard01->update(100, 100, "DEMOPLAY NOW");
//        _pStringBoard02->update(100, 150, "GAME OVER");
//    }
//    if (_pProgress->get() == GAMEDEMO_SCENE_PROG_DEMOPLAY) {
//        if (_pProgress->getActivePartFrameInProgress() == 180) {
//            _pProgress->change(GAMEDEMO_SCENE_PROG_RANKING);
//        }
//    }
//    if (_pProgress->wasChangedFrom(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
//        _TRACE_("GameDemoScene _pProgress->wasChangedFrom(GAMEDEMO_SCENE_PROG_DEMOPLAY)");
//    }
//
//    //ランキング GAMEDEMO_SCENE_PROG_RANKING 時の処理
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_RANKING)) {
//        _TRACE_("GameDemoScene _pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_RANKING)");
//        _pStringBoard01->update(100, 100, "RANKING NOW");
//        _pStringBoard02->update(100, 150, "GAME OVER");
//    }
//    if (_pProgress->get() == GAMEDEMO_SCENE_PROG_RANKING) {
//        if (_pProgress->getActivePartFrameInProgress() == 180) {
//            _pProgress->change(GAMEDEMO_SCENE_PROG_FINISH);
//        }
//    }
//    if (_pProgress->wasChangedFrom(GAMEDEMO_SCENE_PROG_RANKING)) {
//        _TRACE_("GameDemoScene _pProgress->wasChangedFrom(GAMEDEMO_SCENE_PROG_RANKING)");
//    }
//
//    //ランキング GAMEDEMO_SCENE_PROG_RANKING 時の処理
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_FINISH)) {
//        _TRACE_("GameDemoScene _pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_FINISH)");
//        fadeoutSceneTree(FADE_FRAME);
//        inactivateDelay(FADE_FRAME);
//        throwEventToUpperTree(EVENT_GAMEDEMO_SCENE_FINISH);
//    }
//    if (_pProgress->get() == GAMEDEMO_SCENE_PROG_FINISH) {
//    }
//    if (_pProgress->wasChangedFrom(GAMEDEMO_SCENE_PROG_FINISH)) {
//    }









//    if (_pProgress->get() == GAMEDEMO_SCENE_PROG_INIT) {
////        P_CAM->setDefaultPosition();
//
////        TamagoActor* pActor = (TamagoActor*)obtainActorFromFactory(111111);
////        getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
//
//        //自機表示
//        P_MYSHIP->activate(); //下位にオプション等があるし
//
//        //TODO:kesu
//        //テスト
////        TamagoActor* pActor = (TamagoActor*)obtainActorFromFactory(1111);
////        getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
//
//        _pProgress->change(GAMEDEMO_SCENE_PROG_BEGIN);
//    }
//
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_BEGIN)) {
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE BEGIN");
//        _pStringBoard02->update(100, 150, "HAJIMARI HAJIMARI!");
//        _frame_Begin = 0;
//    } else if (_pProgress->get() == GAMEDEMO_SCENE_PROG_BEGIN) {
//        //タイトル活動ループ
//        _frame_Begin++;
//
//        if (_frame_Begin == 120) {
//            _pProgress->change(GAMEDEMO_SCENE_PROG_TITLE); //タイトルへ
//        }
//    }
//
//
//    //ループ----->
//
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_TITLE)) {
//         //タイトル開始
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE TITLE");
//        _pStringBoard02->update(100, 150, "PUSH A UI_EXECUTE BUTTON");
//        _pBgmPerformer->stop(0);
//        _pBgmPerformer->play(0, true);
//
//        _frame_Title = 0;
//    }
//    if (_pProgress->get() == GAMEDEMO_SCENE_PROG_TITLE) {
//        //タイトル活動ループ
//        _frame_Title++;
//
//        //ここに処理
//        if (VB->isPushedDown(VB_UI_EXECUTE)) {
//            _pProgress->change(GAMEDEMO_SCENE_PROG_DECIDE);
//        }
//
//        if (_frame_Title == 600) {
//            _pProgress->change(GAMEDEMO_SCENE_PROG_DEMOPLAY); //デモへ
//        }
//    }
//
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
//        //デモプレイ開始
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DEMOPLAY");
//        _pStringBoard02->update(100, 150, "GAME OVER");
//       _pProgress->change(GAMEDEMO_SCENE_PROG_DEMOPLAY);
//        _frame_Demoplay = 0;
//
//        _pBgmPerformer->fadeout_stop(0, 180);//タイトルBGMが鳴っていれば消す
//
//    } else if (_pProgress->get() == GAMEDEMO_SCENE_PROG_DEMOPLAY) {
//        //デモプレイ活動ループ
//        _frame_Demoplay++;
//
//        //ここに処理
//        if (_frame_Demoplay == 300) {
//            _pProgress->change(GAMEDEMO_SCENE_PROG_RANKING); //ランキングへ
//        }
//    }
//
//
//
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_RANKING)) {
//        //ランキング表示
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE RANKING");
//        _pStringBoard02->update(100, 150, "WE ARE THE WORLD. DESTORY ALL THEM. POWER UP");
//        _frame_Ranking = 0;
//    }
//    if (_pProgress->get() == GAMEDEMO_SCENE_PROG_RANKING) {
//        //ランキング活動ループ
//        _frame_Ranking++;
//
//        //ここに処理
//
//
//        if (_frame_Ranking == 300) {
//            _pProgress->change(GAMEDEMO_SCENE_PROG_TITLE); //タイトルへ
//        }
//    }
//
//    //<-----ループ
//    //デモプレイかランキング時
//    if (GAMEDEMO_SCENE_PROG_DEMOPLAY <= _pProgress->get() && _pProgress->get() <= GAMEDEMO_SCENE_PROG_RANKING) {
//        if (VB->isPushedDown(VB_UI_EXECUTE)) { //VB_UI_EXECUTEでタイトルへ
//            _pProgress->change(GAMEDEMO_SCENE_PROG_TITLE);
//        }
//    }
//
//
//    //ゲームスタート
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_DECIDE)) {
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DECIDE");
//        _pStringBoard02->update(100, 150, "OK HJIMARIMASU!");
//        _frame_Decide = 0;
//    } else if (_pProgress->get() == GAMEDEMO_SCENE_PROG_DECIDE) {
//        //活動ループ
//        _frame_Decide++;
//
//        if (_frame_Decide == 120) {
//            _pBgmPerformer->fadeout_stop(0, 180);
//            _pProgress->change(GAMEDEMO_SCENE_PROG_END); //お終い
//        }
//    }
//
//    if (_pProgress->wasChangedTo(GAMEDEMO_SCENE_PROG_END)) {
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE END");
//        _pStringBoard02->update(100, 150, "SRABA");
//        inactivateDelay(200);
//    }



}

void GameDemoScene::processFinal() {

}

GameDemoScene::~GameDemoScene() {
}
