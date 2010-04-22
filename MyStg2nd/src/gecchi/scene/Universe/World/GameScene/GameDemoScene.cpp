#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    setProgress(GAMEDEMO_PROG_INIT);
    _pStringBoard01 = NEW GgafDx9StringBoardActor("STR01", "moji");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW GgafDx9StringBoardActor("STR02", "moji");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);

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
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEDEMO_PROG_BEGIN) {
        //タイトル活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
            setProgress(GAMEDEMO_PROG_TITLE); //タイトルへ
        }
    }


    //ループ----->

    if (onChangeProgressAt(GAMEDEMO_PROG_TITLE)) {
         //タイトル開始
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE TITLE");
        _pStringBoard02->update(100, 150, "PUSH A UI_EXECUTE BUTTON");
        _dwFrame_Title = 0;
    } else if (getProgress() == GAMEDEMO_PROG_TITLE) {
        //タイトル活動ループ
        _dwFrame_Title++;

        //ここに処理
        if (VB_PLAY->isPushedDown(VB_UI_EXECUTE)) {
            setProgress(GAMEDEMO_PROG_DECIDE);
        }

        if (_dwFrame_Title == 300) {
            setProgress(GAMEDEMO_PROG_DEMOPLAY); //デモへ
        }
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_DEMOPLAY)) {
        //デモプレイ開始
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DEMOPLAY");
        _pStringBoard02->update(100, 150, "GAME OVER");
       setProgress(GAMEDEMO_PROG_DEMOPLAY);
        _dwFrame_Demoplay = 0;
    } else if (getProgress() == GAMEDEMO_PROG_DEMOPLAY) {
        //デモプレイ活動ループ
        _dwFrame_Demoplay++;

        //ここに処理
        if (_dwFrame_Demoplay == 300) {
            setProgress(GAMEDEMO_PROG_RANKING); //ランキングへ
        }
    }



    if (onChangeProgressAt(GAMEDEMO_PROG_RANKING)) {
        //ランキング表示
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE RANKING");
        _pStringBoard02->update(100, 150, "1ST GECCHIRAQ ");
        _dwFrame_Ranking = 0;
    } else if (getProgress() == GAMEDEMO_PROG_RANKING) {
        //ランキング活動ループ
        _dwFrame_Ranking++;

        //ここに処理


        if (_dwFrame_Ranking == 300) {
            setProgress(GAMEDEMO_PROG_TITLE); //タイトルへ
        }
    }

    //<-----ループ
    //デモプレイかランキング時
    if (GAMEDEMO_PROG_DEMOPLAY <= getProgress() && getProgress() <= GAMEDEMO_PROG_RANKING) {
        if (VB_PLAY->isPushedDown(VB_UI_EXECUTE)) { //VB_UI_EXECUTEでタイトルへ
            setProgress(GAMEDEMO_PROG_TITLE);
        }
    }


    //ゲームスタート
    if (onChangeProgressAt(GAMEDEMO_PROG_DECIDE)) {
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DECIDE");
        _pStringBoard02->update(100, 150, "OK HJIMARIMASU!");
        _dwFrame_Decide = 0;
    } else if (getProgress() == GAMEDEMO_PROG_DECIDE) {
        //活動ループ
        _dwFrame_Decide++;

        if (_dwFrame_Decide == 120) {
            setProgress(GAMEDEMO_PROG_END); //お終い
        }
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_END)) {
        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE END");
        _pStringBoard02->update(100, 150, "SRABA");
        inactivateAfter(200);
    }



}

void GameDemoScene::processFinal() {

}

GameDemoScene::~GameDemoScene() {
}
