#include "LockonMagic.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectLockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"

using namespace GgafLib;
using namespace VioletVreath;

LockonMagic::LockonMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            MAX_LOCKON_NUM,   //max_level
            1000*4       , 1.0, 0.9,  //基本魔法コスト, ＋１レベル毎のコスト増加率  , 飛びレベル時のコスト削減率
            SEC_F(1)     , 1.0, 0.9,  //基本詠唱時間  , ＋１レベル毎の詠唱時間増加率, 飛びレベル時の詠唱時間削減率
            SEC_F(0.5)   , 1.0, 0.9,  //基本発動時間  , ＋１レベル毎の発動時間増加率, 飛びレベル時の発動時間削減率
            SEC_F(60*60) , 1.0,       //基本持続時間  , ＋１レベル毎の持続時間の乗率
            1.0          , 1.0        //基本維持コスト, ＋１レベル毎の維持コストの乗率
           ) {

    //数値の意味は VreathMagic.cpp のコメント参照
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
    pEffect_->inactivate();
    MyLockonController::lockon_num_ = 0;
}

void LockonMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP->pMyMagicEnergyCore_);
        pEffect_->setCullingDraw(false);
        pEffect_->getLocusVehicle()->setFaceAngVelo(AXIS_Z, 100);
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
        pEffect_->getLocusVehicle()->setFaceAngVelo(AXIS_Z, 3000);
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
    //光子魚雷発射可能数を変更。
    MyLockonController::lockon_num_ = prm_now_level;
}

void LockonMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

LockonMagic::~LockonMagic() {
}
