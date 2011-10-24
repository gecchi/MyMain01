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
    _pWorldBoundSpace->inactivateImmediately();
    getDirector()->addSubGroup(_pWorldBoundSpace);
    _pHoshiBoshi = NEW HoshiBoshiRankUp("HoshiBoshiRankUp");
    getDirector()->addSubGroup( _pHoshiBoshi);
    _pMessage = NEW LabelGecchi16Font("RankUpMsg");
    getDirector()->addSubGroup(_pMessage);
    useProgress(RANKUPSTAGE_PROG_END);
}

void RankUpStage::initialize() {
    _pProg->set(RANKUPSTAGE_PROG_INIT);
}
void RankUpStage::processBehavior() {

    switch (_pProg->get()) {
        case RANKUPSTAGE_PROG_INIT: {
            _pProg->change(RANKUPSTAGE_PROG_BEGIN);
            break;
        }
        case RANKUPSTAGE_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RANKUPSTAGE_PROG_BEGIN !");
                _pMessage->update(PX2CO(500), PX2CO(200), "RANKUPSTAGE_PROG_BEGIN");
            }

            if (_pProg->getFrameInProgress() == 60) { //ステージ開始！
                _pProg->change(RANKUPSTAGE_PROG_PLAYING);
            }
            break;
        }
        case RANKUPSTAGE_PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _pMessage->update("RANKUPSTAGE_PROG_PLAYING");
                _pMessage->_pFader->beat(120,30,30,30,-1);
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RANKUPSTAGE_PROG_BEGIN !");
            }
            //継承実装クラスのRANKUPSTAGE_PROG_RESULTへ進捗更新待ちイベント待ち
            _pMessage->_pFader->behave();
            break;
        }
        case RANKUPSTAGE_PROG_RESULT: {
            if (_pProg->isJustChanged()) {
                _pMessage->_pFader->reset();
                _pMessage->update("RANKUPSTAGE_PROG_RESULT");
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RANKUPSTAGE_PROG_RESULT !");
            }

            //結果表示？
            if (_pProg->getFrameInProgress() == 120) {
                _pMessage->update("KEKKA HAPYOU!!!");
            }

            if (_pProg->getFrameInProgress() == 200) {
                _pProg->change(RANKUPSTAGE_PROG_END);
            }
            break;
        }
        case RANKUPSTAGE_PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RANKUPSTAGE_PROG_ENDになりますた！");
                _pMessage->update("RANKUPSTAGE_PROG_END");
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

}
void RankUpStage::processFinal() {
}
void RankUpStage::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}

void RankUpStage::onGarbaged() {
    _TRACE_("RankUpStage::onGarbaged() ["<<getName()<<"] throwEventToUpperTree EVENT_RANKUP_ON_GARBAGED！");
    throwEventToUpperTree(EVENT_RANKUP_ON_GARBAGED, this);

}

RankUpStage::~RankUpStage() {
}
