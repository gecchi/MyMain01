#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

bool RankUpStage::_pause = false;

RankUpStage::RankUpStage(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpStage";
    _pWorldBoundSpace  = NEW WorldBoundSpaceRankUp("BG_RankUp");
    _pWorldBoundSpace->inactivateImmed();
    getDirector()->addSubGroup(_pWorldBoundSpace);
    _pHoshiBoshi = NEW HoshiBoshiRankUp("HoshiBoshiRankUp");
    getDirector()->addSubGroup( _pHoshiBoshi);
    _pMessage = NEW LabelGecchi16Font("RankUpMsg");
    getDirector()->addSubGroup(_pMessage);
    useProgress(RankUpStage::PROG_END);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "RANKUP_THEMA");
}

void RankUpStage::initialize() {
    _pProg->set(RankUpStage::PROG_INIT);
}
void RankUpStage::processBehavior() {

    switch (_pProg->get()) {
        case RankUpStage::PROG_INIT: {
            _pProg->change(RankUpStage::PROG_BEGIN);
            break;
        }
        case RankUpStage::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_BEGIN !");
                _pMessage->update(PX2CO(500), PX2CO(200), "RANKUPSTAGE::PROG_BEGIN");
                _pBgmPerformer->play(0, 0, true);
                _pBgmPerformer->fadein(0, 420);
            }

            if (_pProg->getFrameInProgress() == 60) { //ステージ開始！
                _pProg->change(RankUpStage::PROG_PLAYING);
            }
            break;
        }
        case RankUpStage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _pMessage->update("RANKUPSTAGE::PROG_PLAYING");
                _pMessage->_pFader->beat(120,30,30,30,-1);
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_BEGIN !");
            }
            //継承実装クラスのRankUpStage::PROG_RESULTへ進捗更新待ちイベント待ち
            break;
        }
        case RankUpStage::PROG_RESULT: {
            if (_pProg->isJustChanged()) {
                _pMessage->_pFader->reset();
                _pMessage->update("RANKUPSTAGE::PROG_RESULT");
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_RESULT !");
            }

            //結果表示？
            if (_pProg->getFrameInProgress() == 120) {
                _pMessage->update("KEKKA HAPYOU!!!");
                _pBgmPerformer->fadeout_stop(0, 300);
            }

            if (_pProg->getFrameInProgress() == 120+300) {
                _pProg->change(RankUpStage::PROG_END);
            }
            break;
        }
        case RankUpStage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_ENDになりますた！");
                _pMessage->update("RANKUPSTAGE::PROG_END");
                throwEventToUpperTree(EVENT_RANKUP_WAS_END, this);
            }

            if (_pProg->getFrameInProgress() == 180) {
                _pMessage->update("BYBY!");
            }

            break;
        }
        default:
            break;
    }
    _pMessage->_pFader->behave();

}

void RankUpStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

void RankUpStage::onEnded() {
    _TRACE_("RankUpStage::onEnded() ["<<getName()<<"] throwEventToUpperTree EVENT_RANKUP_ON_GARBAGED！");
    throwEventToUpperTree(EVENT_RANKUP_ON_GARBAGED, this);

}

RankUpStage::~RankUpStage() {
}
