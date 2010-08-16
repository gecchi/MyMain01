#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    setProgress(GAMEDEMO_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "FrozenRay");
//    orderActorToFactory(111111, TamagoActor, "TAMAGO_X");
}
void GameDemoScene::reset() {
    _TRACE_("GameDemoScene::reset()");
    setProgress(GAMEDEMO_PROG_INIT);
}
void GameDemoScene::ready() {
    _TRACE_("GameDemoScene::ready()");
}

void GameDemoScene::initialize() {
    setProgress(GAMEDEMO_PROG_INIT);
    //TODO:kesu
    //テスト
    //orderActorToFactory(1111, TamagoActor, "TEST_TamagoActor");
}

void GameDemoScene::processBehavior() {
    if (getProgress() == GAMEDEMO_PROG_INIT) {
        pCAM->setDefaultPosition();

//        TamagoActor* pActor = (TamagoActor*)obtainActorFromFactory(111111);
//        getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);

        //自機表示
        GameGlobal::_pSceneCommon->_pMyShip->activate(); //下位にオプション等があるし

        //TODO:kesu
        //テスト
//        TamagoActor* pActor = (TamagoActor*)obtainActorFromFactory(1111);
//        getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);

        setProgress(GAMEDEMO_PROG_BEGIN);
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_BEGIN)) {
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE BEGIN");
        _pStringBoard02->update(100, 150, "HAJIMARI HAJIMARI!");
        _frame_Begin = 0;
    } else if (getProgress() == GAMEDEMO_PROG_BEGIN) {
        //タイトル活動ループ
        _frame_Begin++;

        if (_frame_Begin == 120) {
            setProgress(GAMEDEMO_PROG_TITLE); //タイトルへ
        }
    }


    //ループ----->

    if (onChangeProgressAt(GAMEDEMO_PROG_TITLE)) {
         //タイトル開始
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE TITLE");
        _pStringBoard02->update(100, 150, "PUSH A UI_EXECUTE BUTTON");
        _pBgmPerformer->stop(0);
        _pBgmPerformer->play(0, true);

        _frame_Title = 0;
    } else if (getProgress() == GAMEDEMO_PROG_TITLE) {
        //タイトル活動ループ
        _frame_Title++;

        //ここに処理
        if (VB->isPushedDown(VB_UI_EXECUTE)) {
            setProgress(GAMEDEMO_PROG_DECIDE);
        }

        if (_frame_Title == 600) {
            setProgress(GAMEDEMO_PROG_DEMOPLAY); //デモへ
        }
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_DEMOPLAY)) {
        //デモプレイ開始
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DEMOPLAY");
        _pStringBoard02->update(100, 150, "GAME OVER");
       setProgress(GAMEDEMO_PROG_DEMOPLAY);
        _frame_Demoplay = 0;

        _pBgmPerformer->fadeout_stop(0, 180);//タイトルBGMが鳴っていれば消す

    } else if (getProgress() == GAMEDEMO_PROG_DEMOPLAY) {
        //デモプレイ活動ループ
        _frame_Demoplay++;

        //ここに処理
        if (_frame_Demoplay == 300) {
            setProgress(GAMEDEMO_PROG_RANKING); //ランキングへ
        }
    }



    if (onChangeProgressAt(GAMEDEMO_PROG_RANKING)) {
        //ランキング表示
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE RANKING");
        _pStringBoard02->update(100, 150, "WE ARE THE WORLD. DESTORY ALL THEM. POWER UP");
        _frame_Ranking = 0;
    } else if (getProgress() == GAMEDEMO_PROG_RANKING) {
        //ランキング活動ループ
        _frame_Ranking++;

        //ここに処理


        if (_frame_Ranking == 300) {
            setProgress(GAMEDEMO_PROG_TITLE); //タイトルへ
        }
    }

    //<-----ループ
    //デモプレイかランキング時
    if (GAMEDEMO_PROG_DEMOPLAY <= getProgress() && getProgress() <= GAMEDEMO_PROG_RANKING) {
        if (VB->isPushedDown(VB_UI_EXECUTE)) { //VB_UI_EXECUTEでタイトルへ
            setProgress(GAMEDEMO_PROG_TITLE);
        }
    }


    //ゲームスタート
    if (onChangeProgressAt(GAMEDEMO_PROG_DECIDE)) {
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DECIDE");
        _pStringBoard02->update(100, 150, "OK HJIMARIMASU!");
        _frame_Decide = 0;
    } else if (getProgress() == GAMEDEMO_PROG_DECIDE) {
        //活動ループ
        _frame_Decide++;

        if (_frame_Decide == 120) {
            _pBgmPerformer->fadeout_stop(0, 180);
            setProgress(GAMEDEMO_PROG_END); //お終い
        }
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_END)) {
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE END");
        _pStringBoard02->update(100, 150, "SRABA");
        end(200);
    }



}

void GameDemoScene::processFinal() {

}

GameDemoScene::~GameDemoScene() {
}
