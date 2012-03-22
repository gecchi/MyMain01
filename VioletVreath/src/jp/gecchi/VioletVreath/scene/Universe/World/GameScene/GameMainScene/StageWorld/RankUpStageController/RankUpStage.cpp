#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

bool RankUpStage::pause_ = false;

RankUpStage::RankUpStage(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpStage";
    pWorldBoundSpace_  = NEW WorldBoundSpaceRankUp("BG_RankUp");
    pWorldBoundSpace_->inactivateImmed();
    getDirector()->addSubGroup(pWorldBoundSpace_);
    pHoshiBoshi_ = NEW HoshiBoshiRankUp("HoshiBoshiRankUp");
    getDirector()->addSubGroup( pHoshiBoshi_);
    pMessage_ = NEW LabelGecchi16Font("RankUpMsg");
    getDirector()->addSubGroup(pMessage_);
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
                pMessage_->update(PX2CO(500), PX2CO(200), "RANKUPSTAGE::PROG_BEGIN");
                _pBgmPerformer->play_fadein(0);
            }

            if (_pProg->getFrameInProgress() == 60) { //ステージ開始！
                _pProg->change(RankUpStage::PROG_PLAYING);
            }
            break;
        }
        case RankUpStage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                pMessage_->update("RANKUPSTAGE::PROG_PLAYING");
                pMessage_->_pFader->beat(120,30,30,30,-1);
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_BEGIN !");
            }
            //継承実装クラスのRankUpStage::PROG_RESULTへ進捗更新待ちイベント待ち
            break;
        }
        case RankUpStage::PROG_RESULT: {
            if (_pProg->isJustChanged()) {
                pMessage_->_pFader->reset();
                pMessage_->update("RANKUPSTAGE::PROG_RESULT");
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_RESULT !");
            }

            //結果表示？
            if (_pProg->getFrameInProgress() == 120) {
                pMessage_->update("KEKKA HAPYOU!!!");
                _pBgmPerformer->fadeout_stop(0);
            }

            if (_pProg->getFrameInProgress() == 120+300) {
                _pProg->change(RankUpStage::PROG_END);
            }
            break;
        }
        case RankUpStage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpStage::processBehavior() ["<<getName()<<"] RankUpStage::PROG_ENDになりますた！");
                pMessage_->update("RANKUPSTAGE::PROG_END");
                throwEventToUpperTree(EVENT_RANKUP_WAS_END, this);
            }

            if (_pProg->getFrameInProgress() == 180) {
                pMessage_->update("BYBY!");
            }

            break;
        }
        default:
            break;
    }
    pMessage_->_pFader->behave();

}

void RankUpStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

void RankUpStage::onEnded() {
    _TRACE_("RankUpStage::onEnded() ["<<getName()<<"] throwEventToUpperTree EVENT_RANKUP_ON_GARBAGED！");
    throwEventToUpperTree(EVENT_RANKUP_ON_GARBAGED, this);

}

RankUpStage::~RankUpStage() {
}
