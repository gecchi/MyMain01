#include "StageWorld.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

StageWorld::StageWorld(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageWorld";
    can_rank_up_ = true;
    pStageCtrler_ = NEW StageController("StageController");
    addSubLast(pStageCtrler_);
    pRankUpStageCtrler_ = NEW RankUpStageController("RankUpStageController");
    addSubLast(pRankUpStageCtrler_);
}

void StageWorld::onReset() {
    _TRACE_("StageWorld::onReset() "<<NODE_INFO<<" GOD="<<P_GOD->_frame_of_God);
    _TRACE_("MyShipScene ���A�X���[�̉e����^���Ȃ����߂Ɉ��Ɉ����グ�܂� addSubLast(P_MYSHIP_SCENE->extract()); ");
    P_MYSHIP_SCENE->resetTree();
    P_MYSHIP_SCENE->activateImmed();
    addSubLast(P_MYSHIP_SCENE->extract()); //�X���[�̉e����^���Ȃ����߂Ɉ��
    pStageCtrler_->setRunFrameOnce(1); //�X���[�Ȃ���
}

void StageWorld::initialize() {
}

void StageWorld::processBehavior() {

    //debug ---->
//#ifdef MY_DEBUG
    if (GgafDxCore::GgafDxInput::isPushedDownKey(DIK_P)) {
        G_RANK += (1.0/G_RANK_R);
        _TRACE_("StageWorld::processBehavior() G_RANK="<<G_RANK<<"/G_RANK_DISP="<<G_RANK_DISP<<"");
    }
//#endif
    //<---- debug
    //�����N�A�b�v�V�[����������
    if (GameGlobal::updateRankUpLebel()) {
        _TRACE_("G_RANKUP_LEVEL �A�b�v���܂����I�I��"<<G_RANKUP_LEVEL<<" (G_RANK="<<G_RANK<<"/G_RANK_DISP="<<G_RANK_DISP<<")");
        if (can_rank_up_) {
            _TRACE_("�����N�A�b�v�V�[���������݂��܂��I");
            pRankUpStageCtrler_->startRunkUpStage(G_RANKUP_LEVEL);
            _TRACE_("P_STAGE_CTRLER ���X���[");
            pStageCtrler_->addRunFrameOnce(SLOW_FRAME_RANKUP); //�X���[�J�n
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
        _TRACE_("P_STAGE_CTRLER ���X���[��");
        pStageCtrler_->addRunFrameOnce(-SLOW_FRAME_RANKUP); //�X���[�J�n
    }
}

StageWorld::~StageWorld() {
    _TRACE_("StageWorld::~StageWorld() ");
}