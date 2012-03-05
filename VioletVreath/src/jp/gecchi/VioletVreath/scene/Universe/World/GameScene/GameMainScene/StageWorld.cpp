#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

StageWorld::StageWorld(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageWorld";

    can_rank_up_ = true;
    pStageController_ = NEW StageController("StageController");
    addSubLast(pStageController_);
    pRankUpStageController_ = NEW RankUpStageController("RankUpStageController");
    addSubLast(pRankUpStageController_);

}

void StageWorld::onReset() {
    P_MYSHIP_SCENE->resetTree();
    P_MYSHIP_SCENE->activateImmed();
    addSubLast(P_MYSHIP_SCENE->extract()); //�X���[�̉e����^���Ȃ����߂Ɉ��
}

void StageWorld::initialize() {
}

void StageWorld::processBehavior() {
    //�����N�A�b�v�V�[����������

    if (VB_PLAY->isPushedDown(VB_BUTTON7)) {
        _TRACE_("_RANK_UP_LEVEL_�H�H�H"<<_RANK_UP_LEVEL_);
        if (can_rank_up_) {
            _RANK_UP_LEVEL_ = _RANK_UP_LEVEL_ + 1;
            pRankUpStageController_->execute();
            _TRACE_("P_STAGE_CONTROLLER ���X���[");
            P_STAGE_CONTROLLER->addRunFrameOnce(1); //�X���[�J�n
        } else {
            //�X���[
        }
    } else {
        //can_rank_up_ = false;
    }
}
void StageWorld::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_RANKUP_WAS_END) {
        _TRACE_("StageWorld::onCatchEvent EVENT_RANKUP_WAS_END");
        //�X���[��
        _TRACE_("P_STAGE_CONTROLLER ���X���[��");
        P_STAGE_CONTROLLER->addRunFrameOnce(-1); //�X���[�J�n
    }
}

StageWorld::~StageWorld() {
    if (P_STAGE_CONTROLLER->pStageMainCannel_) {
        P_STAGE_CONTROLLER->pStageMainCannel_->end();
        P_STAGE_CONTROLLER->pStageMainCannel_ = NULL;
    }
}
