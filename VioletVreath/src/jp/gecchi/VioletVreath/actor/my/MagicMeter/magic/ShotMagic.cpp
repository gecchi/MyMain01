#include "ShotMagic.h"

#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectShotMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"



using namespace GgafLib;
using namespace VioletVreath;

ShotMagic::ShotMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            3,                    //max_level
            1000*4       , 1.5, 0.9,   //��{���@�R�X�g, �{�P���x�����̃R�X�g������  , ��у��x�����̃R�X�g�팸��
            SEC_F(1)     , 1.5, 0.9,   //��{�r������  , �{�P���x�����̉r�����ԑ�����, ��у��x�����̉r�����ԍ팸��
            SEC_F(0.5)   , 1.5, 0.9,   //��{��������  , �{�P���x�����̔������ԑ�����, ��у��x�����̔������ԍ팸��
            SEC_F(60*10) , 0.8,        //��{��������  , �{�P���x�����̎������Ԃ̏旦
            0            , 1.0         //��{�ێ��R�X�g, �{�P���x�����̈ێ��R�X�g�̏旦
           ) {

    //���l�̈Ӗ��� VreathMagic.cpp �̃R�����g�Q��
    lvinfo_[3].pno_ = 100;
    lvinfo_[2].pno_ = 108;
    lvinfo_[1].pno_ = 116;
    lvinfo_[0].pno_ = 124;

    pEffect_ = NEW EffectShotMagic("EffectShotMagic");
    pEffect_->inactivate();
    appendChild(pEffect_);
}

void ShotMagic::onReset() {
    Magic::onReset();
    pEffect_->inactivate();
    pMYSHIP->can_shoot_laser_ = false;
}

void ShotMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP->pMyMagicEnergyCore_);
        pEffect_->setCullingDraw(false);
        pEffect_->getLocusVehicle()->setFaceAngVelo(AXIS_Z, 100);
        pEffect_->setScale(1000);
        pEffect_->activate();
    } else {

    }
}

void ShotMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP->pMyMagicEnergyCore_);
        pEffect_->addScale(10);
    }
}

void ShotMagic::processCastingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void ShotMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
    if (prm_new_level > prm_now_level) {

    }
}

void ShotMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setScale(1000);
        pEffect_->getLocusVehicle()->setFaceAngVelo(AXIS_Z, -3000);
    }
}

void ShotMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->addScale(100);
    }
}

void ShotMagic::processInvokingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void ShotMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

void ShotMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    if (prm_now_level > 0) {
        pMYSHIP->shot_level_ = prm_now_level;
    } else {
        //���x��0�փ��x���_�E����
        pMYSHIP->shot_level_ = 1;
    }
}

void ShotMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}


ShotMagic::~ShotMagic() {
}
