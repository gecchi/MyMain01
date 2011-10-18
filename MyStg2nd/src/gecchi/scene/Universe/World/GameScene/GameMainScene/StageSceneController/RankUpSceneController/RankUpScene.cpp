#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

bool RankUpScene::_pause = false;

RankUpScene::RankUpScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpScene";
    useProgress(RANKUPSCENE_PROG_END);
}

void RankUpScene::initialize() {
    _pProg->set(RANKUPSCENE_PROG_INIT);
}
void RankUpScene::processBehavior() {

    switch (_pProg->get()) {
        case RANKUPSCENE_PROG_INIT: {
            _pProg->change(RANKUPSCENE_PROG_BEGIN);
            break;
        }
        case RANKUPSCENE_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpScene::processBehavior() ["<<getName()<<"] RANKUPSCENE_PROG_BEGIN !");
                _pMessage->update(Px2Co(500), Px2Co(500), "RANKUPSCENE_PROG_BEGIN");
            }

            if (_pProg->getFrameInProgress() == 180) { //ステージ開始！
                _pProg->change(RANKUPSCENE_PROG_PLAYING);
            }
            break;
        }
        case RANKUPSCENE_PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                P_RANK_UP_CONTROLLER->slowdown(this); //スローダウン
                _pMessage->update("RANKUPSCENE_PROG_PLAYING");
                _TRACE_("RankUpScene::processBehavior() ["<<getName()<<"] RANKUPSCENE_PROG_BEGIN !");
            }
            //継承実装クラスのRANKUPSCENE_PROG_RESULTへ進捗更新待ちイベント待ち
            break;
        }
        case RANKUPSCENE_PROG_RESULT: {
            if (_pProg->isJustChanged()) {
                _pMessage->update("RANKUPSCENE_PROG_RESULT");
                _TRACE_("RankUpScene::processBehavior() ["<<getName()<<"] RANKUPSCENE_PROG_RESULT !");
            }

            //結果表示？
            if (_pProg->getFrameInProgress() == 180) {
                _pMessage->update("KEKKA HAPYOU!!!");
            }
            break;
        }
        case RANKUPSCENE_PROG_END: {
            if (_pProg->isJustChanged()) {
                P_RANK_UP_CONTROLLER->slowRelease(this); //スロー回復
                _TRACE_("RankUp001::processBehavior()  RANKUPSCENE_PROG_ENDになりますた！");
                _pMessage->update("RANKUPSCENE_PROG_END");
            }

            if (_pProg->getFrameInProgress() == 180) {
                _pMessage->update("BYBY!");
            }

            break;
        }
        default:
            break;

    }

}

void RankUpScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}
void RankUpScene::processFinal() {
}

//
//void RankUpScene::initialize() {
//}
//
//
//void RankUpScene::processJudgement() {
//}
//
//void RankUpScene::processFinal() {
//    //一時停止
//    if (VB->isPushedDown(VB_UI_CANCEL)) {
//        if (_pause) {
//            pauseTree();
//        } else {
//            unpauseTree();
//        }
//    }
//}

RankUpScene::~RankUpScene() {
}
