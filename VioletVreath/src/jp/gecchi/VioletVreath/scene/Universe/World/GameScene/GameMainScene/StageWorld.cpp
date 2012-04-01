#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

StageWorld::StageWorld(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageWorld";

    can_rank_up_ = true;
    pStageCtrlr_ = NEW StageController("StageController");
    addSubLast(pStageCtrlr_);
    pRankUpStageCtrlr_ = NEW RankUpStageController("RankUpStageController");
    addSubLast(pRankUpStageCtrlr_);

}

void StageWorld::onReset() {
    P_MYSHIP_SCENE->resetTree();
    P_MYSHIP_SCENE->activateImmed();
    addSubLast(P_MYSHIP_SCENE->extract()); //スローの影響を与えないために一つ上
}

void StageWorld::initialize() {
}

void StageWorld::processBehavior() {
    //ランクアップシーン差し込み

    if (VB_PLAY->isPushedDown(VB_BUTTON7)) {
        _TRACE_("_RANK_UP_LEVEL_？？？"<<_RANK_UP_LEVEL_);
        if (can_rank_up_) {
            _RANK_UP_LEVEL_ = _RANK_UP_LEVEL_ + 1;
            pRankUpStageCtrlr_->execute();
            _TRACE_("P_STAGE_CTRLER をスロー");
            P_STAGE_CTRLER->addRunFrameOnce(1); //スロー開始
        } else {
            //スルー
        }
    } else {
        //can_rank_up_ = false;
    }
}
void StageWorld::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_RANKUP_WAS_END) {
        _TRACE_("StageWorld::onCatchEvent EVENT_RANKUP_WAS_END");
        //スロー回復
        _TRACE_("P_STAGE_CTRLER をスロー回復");
        P_STAGE_CTRLER->addRunFrameOnce(-1); //スロー開始
    }
}

StageWorld::~StageWorld() {
    if (P_STAGE_CTRLER->pStageMainCannel_) {
        P_STAGE_CTRLER->pStageMainCannel_->end();
        P_STAGE_CTRLER->pStageMainCannel_ = NULL;
    }
}
