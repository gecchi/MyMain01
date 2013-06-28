#include "stdafx.h"
#include "LockonMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectLockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LockonMagic::LockonMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            MyLockonController::max_lockon_num_,               //max_level
            1000*4  , 0.9,   //��{���@�R�X�g , ��у��x������ rate
            60*2    , 0.9,   //��{�r������   , ��у��x������ rate
            60*2    , 0.9,   //��{��������   , ��у��x������ rate
            60*60*60, 1.0,   //��{��������   , �{�P���x�����̎������Ԃ̏旦
            1.0     , 1.0    //��{�ێ��R�X�g , �{�P���x�����̈ێ��R�X�g�̏旦
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
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);

}

void LockonMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    pEffect_->positionAs(P_MYSHIP);
    pEffect_->setAlpha(0.9);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    pEffect_->_pScaler->setScale(1000);
    pEffect_->activate();
}

void LockonMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->positionAs(P_MYSHIP);
    pEffect_->_pScaler->addScale(10);
}

void LockonMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void LockonMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->setScale(1000);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}

void LockonMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->addScale(100);
}

void LockonMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

int LockonMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //���q�������ˉ\����ύX�B
    MyLockonController::lockon_num_ = prm_level;
    return r;
}

void LockonMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
}

void LockonMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

void LockonMagic::processEffectFinish(int prm_justbefore_level) {
    _TRACE_("���b�N�I���S���Ȃ����ŁI�I�I");
    MyLockonController::lockon_num_ = 0;
}

LockonMagic::~LockonMagic() {
}
