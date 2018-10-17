#include "SpeedMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectSpeedMagic.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpeedMagic::SpeedMagic(const char* prm_name, int*prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,                     //max_level
            1000*2    , 1.0, 0.9,  //��{���@�R�X�g, �{�P���x�����̃R�X�g������  , ��у��x�����̃R�X�g�팸��
            60*0.3    , 1.0, 0.9,  //��{�r������  , �{�P���x�����̉r�����ԑ�����, ��у��x�����̉r�����ԍ팸��
            60*0.1    , 1.0, 0.9,  //��{��������  , �{�P���x�����̔������ԑ�����, ��у��x�����̔������ԍ팸��
            60*60*2   , 0.9,       //��{��������  , �{�P���x�����̎������Ԃ̏旦
            0         , 0.0        //��{�ێ��R�X�g, �{�P���x�����̈ێ��R�X�g�̏旦
           ) {

    //���l�̈Ӗ��� VreathMagic.cpp �̃R�����g�Q��
    lvinfo_[7].pno_ =  70;
    lvinfo_[6].pno_ =  78;
    lvinfo_[5].pno_ =  86;
    lvinfo_[4].pno_ =  94;
    lvinfo_[3].pno_ = 102;
    lvinfo_[2].pno_ = 110;
    lvinfo_[1].pno_ = 118;
    lvinfo_[0].pno_ = 126;

    pEffect_ = NEW EffectSpeedMagic("EffectSpeedMagic");
    pEffect_->inactivate();
    appendGroupChild(pEffect_);
}

void SpeedMagic::onReset() {
    Magic::onReset();
    pMYSHIP->setMoveSpeed(PX_C((0+1)*2));
}

void SpeedMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP->pMyMagicEnergyCore_);
        pEffect_->setAlpha(0.9);
        pEffect_->getKuroko()->setFaceAngVelo(AXIS_Z, 100);
        pEffect_->setScale(1000);
        pEffect_->activate();
    }
}

void SpeedMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP->pMyMagicEnergyCore_);
        pEffect_->addScale(10);
    }
}

void SpeedMagic::processCastingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void SpeedMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void SpeedMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setScale(1000);
        pEffect_->getKuroko()->setFaceAngVelo(AXIS_Z, 3000);
    }
}

void SpeedMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->addScale(100);
    }
}

void SpeedMagic::processInvokingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void SpeedMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

void SpeedMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    pMYSHIP->setMoveSpeed(PX_C((prm_now_level+1)*2));
}

void SpeedMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

SpeedMagic::~SpeedMagic() {
}
