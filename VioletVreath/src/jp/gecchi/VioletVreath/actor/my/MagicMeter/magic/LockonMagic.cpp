#include "LockonMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectLockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LockonMagic::LockonMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            MyLockonController::max_lockon_num_,   //max_level
            1000*4  , 1.0, 0.9,  //��{���@�R�X�g, �{�P���x�����̃R�X�g������  , ��у��x�����̃R�X�g�팸��
            60      , 1.0, 0.9,  //��{�r������  , �{�P���x�����̉r�����ԑ�����, ��у��x�����̉r�����ԍ팸��
            30      , 1.0, 0.9,  //��{��������  , �{�P���x�����̔������ԑ�����, ��у��x�����̔������ԍ팸��
            60*60*60, 1.0,       //��{��������  , �{�P���x�����̎������Ԃ̏旦
            1.0     , 1.0        //��{�ێ��R�X�g, �{�P���x�����̈ێ��R�X�g�̏旦
           ) {

    //���l�̈Ӗ��� VreathMagic.cpp �̃R�����g�Q��
    lvinfo_[7].pno_ =  2;
    lvinfo_[6].pno_ = 10;
    lvinfo_[5].pno_ = 18;
    lvinfo_[4].pno_ = 26;
    lvinfo_[3].pno_ = 34;
    lvinfo_[2].pno_ = 42;
    lvinfo_[1].pno_ = 50;
    lvinfo_[0].pno_ = 58;

    pEffect_ = NEW EffectLockonMagic("EffectLockonMagic");
    pEffect_->inactivate();
    appendGroupChild(pEffect_);
}

void LockonMagic::onReset() {
    Magic::onReset();
    MyLockonController::lockon_num_ = 0;
}

void LockonMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP->pMyMagicEnergyCore_);
        pEffect_->setCullingDraw(false);
        pEffect_->getKuroko()->setFaceAngVelo(AXIS_Z, 100);
        pEffect_->setScale(1000);
        pEffect_->activate();
    }
}

void LockonMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP->pMyMagicEnergyCore_);
        pEffect_->addScale(10);
    }
}

void LockonMagic::processCastingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void LockonMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void LockonMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setScale(1000);
        pEffect_->getKuroko()->setFaceAngVelo(AXIS_Z, 3000);
    }
}

void LockonMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->addScale(100);
    }
}

void LockonMagic::processInvokingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void LockonMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

void LockonMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    //���q�������ˉ\����ύX�B
    MyLockonController::lockon_num_ = prm_now_level;
}

void LockonMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

LockonMagic::~LockonMagic() {
}
