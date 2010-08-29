#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define ORDER_ID_STAGESCENE 11

GameMainScene* GameMainScene::_pGameMainScene = NULL;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _pFont16_SCORE = NEW LabelGecchi16Font("SCORE");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont16_SCORE);
    _pFont16_RANK = NEW LabelGecchi16Font("RANK");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont16_RANK);
    _pFont16_STAMINA = NEW LabelGecchi16Font("STAMINA");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont16_STAMINA);
    _pFont1601 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont1601);
    _pFont1602 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont1602);
    _pFont8_JIKI_X = NEW LabelGecchi8Font("JIKI_X");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont8_JIKI_X);
    _pFont8_JIKI_Y = NEW LabelGecchi8Font("JIKI_Y");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont8_JIKI_Y);
    _pFont8_JIKI_Z = NEW LabelGecchi8Font("JIKI_Z");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont8_JIKI_Z);
    _pScene_Stage01 = NULL;
    _pScene_Stage02 = NULL;
    _pScene_Stage03 = NULL;
    _pScene_Stage04 = NULL;
    _pScene_Stage05 = NULL;

    _pSceneMainCannnel = NULL;

    GameMainScene::_pGameMainScene = this;
}

void GameMainScene::reset() {
}

void GameMainScene::ready(int prm_stage) {
    _stage = prm_stage;
    _had_ready_stage = true;
    _frame_ready_stage = 0;
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage01Scene, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage02Scene, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage03Scene, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage04Scene, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage05Scene, "Stage05");
            break;
        default:
            break;
    }
}

void GameMainScene::initialize() {

    setProgress(GAMEMAIN_PROG_INIT);
    //initialize()時はinactive()であることに注意する事
}

void GameMainScene::processBehavior() {
    if (getProgress() == GAMEMAIN_PROG_INIT) {
        VB_UI->clear();
        VB_PLAY->clear();
        pGOD->setVB(VB_PLAY); //保存のためプレイ用に変更
        GgafScene* pCommon = pCOMMONSCENE->extract();
        addSubLast(pCommon); // 共通シーンを配下に移動（一時停止をうまく制御させるため！）
        setProgress(GAMEMAIN_PROG_BEGIN);
    }

    if (onChangeProgressAt(GAMEMAIN_PROG_BEGIN)) {
        _pFont1601->update(300, 300, "GAME_MAIN_SCENE BEGIN");
        _pFont1602->update(300, 350, "DESTOROY ALL THEM!!");

        if (_pSceneMainCannnel) {
            //2面目以降はこのタイミングで前ステージをend
            _TRACE_("_pSceneMainCannnel="<<_pSceneMainCannnel->getName()<<" end()");
            _pSceneMainCannnel->end(30*60);
        }

        _pSceneMainCannnel = (StageScene*)obtainSceneFromFactory(ORDER_ID_STAGESCENE);
        addSubLast(_pSceneMainCannnel); //ステージシーン追加

        _had_ready_stage = false;
        _frame_Begin = 0;


    } else if (getProgress() == GAMEMAIN_PROG_BEGIN) {
        //活動ループ
        _frame_Begin++;

        if (_frame_Begin == 180) {
            setProgress(GAMEMAIN_PROG_PLAY); //
        }
    }

    if (onChangeProgressAt(GAMEMAIN_PROG_PLAY)) {
        _pFont1601->update(300, 300, "");
        _pFont1602->update(300, 350, "");

    } else if (getProgress() == GAMEMAIN_PROG_PLAY) {
        //活動ループ
        if (_had_ready_stage) {
            _frame_ready_stage++;
            if (_frame_ready_stage == 5*60) {
                _TRACE_("新ステージCOMEING!!");
                setProgress(GAMEMAIN_PROG_BEGIN);
            }
        }
    }

    if (onChangeProgressAt(GAMEMAIN_PROG_END)) {
         VB_UI->clear();
         pGOD->setVB(VB_UI);  //戻す
        _TRACE_("オワタ");
    } else if (getProgress() == GAMEMAIN_PROG_END) {
    }


    //SCORE表示
    sprintf(_buf, "SCORE %07u", _SCORE_);
    _pFont16_SCORE->update(550, 1, _buf);
    sprintf(_buf, "RANK %.7f", _RANK_);
    _pFont16_RANK->update(550, 20, _buf);
    sprintf(_buf, "STAMINA %7d", pMYSHIP->_pStatus->get(STAT_Stamina));
    _pFont16_STAMINA->update(550, 40, _buf);

    sprintf(_buf, "X:%8d", pMYSHIP->_X);
    _pFont8_JIKI_X->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*3-1, _buf);
    sprintf(_buf, "Y:%8d", pMYSHIP->_Y);
    _pFont8_JIKI_Y->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*2-1, _buf);
    sprintf(_buf, "Z:%8d", pMYSHIP->_Z);
    _pFont8_JIKI_Z->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*1-1, _buf);
    //カメラワーク関連

    if (getProgress() == GAMEMAIN_PROG_PLAY || getProgress() == GAMEMAIN_PROG_BEGIN) {

        //一時停止
        if (VB_PLAY->isReleasedUp(VB_PAUSE)) {
            _TRACE_("PAUSE!");
            pGOD->setVB(VB_UI);  //入力はＵＩに切り替え
            pause();     //自身配下を一時停止する。一時停止解除はGameSceneで行われる
        }
    }
}

void GameMainScene::catchEvent(UINT32 prm_no, void* prm_pSource) {

    if (prm_no == PREPARE_NEXT_STAGE) {
        //次のステージを工場に注文していいよというイベント
        _TRACE_("GameMainScene::catchEvent() PREPARE_NEXT_STAGE準備きた");
        if (_stage < 5) {
            _stage++;
            ready(_stage);

        } else {
            _TRACE_("最終面クリア");
            setProgress(GAMEMAIN_PROG_END);
            //TODO:エデニング？
        }
    }
}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}

