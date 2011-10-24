#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

StageWorld::StageWorld(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageWorld";

    _can_rank_up = true;
    _pStageController = NEW StageController("StageController");
    addSubLast(_pStageController);
    _pRankUpStageController = NEW RankUpStageController("RankUpStageController");
    addSubLast(_pRankUpStageController);

}

void StageWorld::onReset() {
    P_MYSHIP_SCENE->resetTree();
    P_MYSHIP_SCENE->activateImmediately();
    addSubLast(P_MYSHIP_SCENE->extract()); //�X���[�̉e����^���Ȃ����߂Ɉ��
}

void StageWorld::initialize() {
}

void StageWorld::processBehavior() {
    //�����N�A�b�v�V�[����������

    if (GgafDxInput::isPushedDownKey(DIK_U)) {
        _TRACE_("_RANK_UP_LEVEL_�H�H�H"<<_RANK_UP_LEVEL_);
        if (_can_rank_up) {
            _RANK_UP_LEVEL_ = _RANK_UP_LEVEL_ + 1;
            _pRankUpStageController->execute();
            _TRACE_("P_STAGE_CONTROLLER ���X���[");
            P_STAGE_CONTROLLER->addRunFrameOnce(1); //�X���[�J�n
        } else {
            //�X���[
        }
    } else {
        //_can_rank_up = false;
    }
}
void StageWorld::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_RANKUP_WAS_END) {
        _TRACE_("StageWorld::onCatchEvent EVENT_RANKUP_WAS_END");
        //�X���[��
        _TRACE_("P_STAGE_CONTROLLER ���X���[��");
        P_STAGE_CONTROLLER->addRunFrameOnce(-1); //�X���[�J�n
    }
}
void StageWorld::processFinal() {



}

StageWorld::~StageWorld() {
    if (P_STAGE_CONTROLLER->_pStageMainCannel) {
        P_STAGE_CONTROLLER->_pStageMainCannel->end();
        P_STAGE_CONTROLLER->_pStageMainCannel = NULL;
    }
}
