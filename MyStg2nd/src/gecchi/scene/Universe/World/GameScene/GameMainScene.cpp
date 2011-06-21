#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define ORDER_ID_STAGESCENE 11

//GameMainScene* GameMainScene::_pGameMainScene = NULL;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameMainScene";

    _pFont16_SCORE = NEW LabelGecchi16Font("SCORE");
    getLordActor()->addSubGroup(_pFont16_SCORE);
    _pFont16_RANK = NEW LabelGecchi16Font("RANK");
    getLordActor()->addSubGroup(_pFont16_RANK);
    _pFont16_STAMINA = NEW LabelGecchi16Font("STAMINA");
    getLordActor()->addSubGroup(_pFont16_STAMINA);
    _pFont1601 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pFont1601);
    _pFont1602 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pFont1602);
    _pFont8_JIKI_X = NEW LabelGecchi8Font("JIKI_X");
    getLordActor()->addSubGroup(_pFont8_JIKI_X);
    _pFont8_JIKI_Y = NEW LabelGecchi8Font("JIKI_Y");
    getLordActor()->addSubGroup(_pFont8_JIKI_Y);
    _pFont8_JIKI_Z = NEW LabelGecchi8Font("JIKI_Z");
    getLordActor()->addSubGroup(_pFont8_JIKI_Z);

    _pSceneMainCannnel = NULL;
    _had_ready_stage = false;
//    GameMainScene::_pGameMainScene = this;
    useProgress(10);
}

void GameMainScene::onReset() {
//    VB_UI->clear();
//    VB_PLAY->clear();
//    P_GOD->setVB(VB_PLAY); //保存のためプレイ用に変更

    _pFont1601->update("");
    _pFont1602->update("");
    if (_pSceneMainCannnel) {
        _pSceneMainCannnel->inactivate();
    }
    _pProg->set(GAMEMAINSCENE_PROG_INIT);
}
void GameMainScene::readyNextStage() {
    _stage++;
    readyStage(_stage);
}

void GameMainScene::readyStage(int prm_stage) {
    if (_had_ready_stage) {
        throwGgafCriticalException("GameMainScene::readyStage 既に準備済みのステージがあります。_stage="<<_stage<<" prm_stage="<<prm_stage);
    }

    _stage = prm_stage;
    _had_ready_stage = true;
//    _frame_ready_stage = 0;
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


//    GgafScene* pCommon = P_COMMON_SCENE->extract();
//    addSubLast(pCommon); // 共通シーンを配下に移動（一時停止をうまく制御させるため！）
    //initialize()時はinactive()であることに注意する事
}

void GameMainScene::processBehavior() {
    //SCORE表示
    sprintf(_buf, "SCORE %07u", _SCORE_);
    _pFont16_SCORE->update(550*1000, 1*1000, _buf);
    sprintf(_buf, "RANK %.7f", _RANK_);
    _pFont16_RANK->update(550*1000, 20*1000, _buf);
    sprintf(_buf, "STAMINA %7d", P_MYSHIP->_pStatus->get(STAT_Stamina));
    _pFont16_STAMINA->update(550*1000, 40*1000, _buf);

    sprintf(_buf, "X:%8d", P_MYSHIP->_X);
    _pFont8_JIKI_X->update(1*1000, (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*3-1)*1000, _buf);
    sprintf(_buf, "Y:%8d", P_MYSHIP->_Y);
    _pFont8_JIKI_Y->update(cnvCoordPix2App(1), cnvCoordPix2App(CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*2-1), _buf);
    sprintf(_buf, "Z:%8d", P_MYSHIP->_Z);
    _pFont8_JIKI_Z->update(1*1000, (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*1-1)*1000, _buf);


    switch (_pProg->get()) {
        case GAMEMAINSCENE_PROG_INIT: {
            _pProg->change(GAMEMAINSCENE_PROG_BEGIN);
            break;
        }

        case GAMEMAINSCENE_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                if (_pSceneMainCannnel && !_pSceneMainCannnel->wasDeclaredEnd()) {
                    //2面目以降はこのタイミングで前ステージをend
                    _TRACE_("_pSceneMainCannnel="<<_pSceneMainCannnel->getName()<<" end()");
                    _pSceneMainCannnel->end();
                }
            }
            if (_pProg->getFrameInProgress() == 120) { //deleteを考慮し２秒遊ぶ
                _pProg->change(GAMEMAINSCENE_PROG_PLAY);
            }
            break;
        }

        case GAMEMAINSCENE_PROG_PLAY: {
            if (_pProg->isJustChanged()) {
                if (_had_ready_stage) {
                    _had_ready_stage = false;
                    _pSceneMainCannnel = (StageScene*)obtainSceneFromFactory(ORDER_ID_STAGESCENE);
                    addSubLast(_pSceneMainCannnel); //ステージシーン追加
                } else {
                    throwGgafCriticalException("GameMainScene::processBehavior GAMEMAINSCENE_PROG_BEGIN 準備済みステージがありません。_stage="<<_stage);
                }
            }
            break;
        }

        case GAMEMAINSCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        default:
            break;
    }

}




void GameMainScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        //次のステージを工場に注文していいよというイベント
        _TRACE_("GameMainScene::onCatchEvent() EVENT_PREPARE_NEXT_STAGE 準備きた");
        if (_stage < 5) {
            readyNextStage();
        } else {
//            _TRACE_("最終面クリア");
//            _pProg->change(GAMEMAINSCENE_PROG_END);
            //TODO:エデニング？
        }
    }

}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}

