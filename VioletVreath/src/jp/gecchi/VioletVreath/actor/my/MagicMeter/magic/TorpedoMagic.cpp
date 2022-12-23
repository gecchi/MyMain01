
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "TorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectTorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

TorpedoMagic::TorpedoMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            MyTorpedoController::max_torpedo_num_,   //max_level
            1000*4       , 1.0, 0.9, //基本魔法コスト, ＋１レベル毎のコスト増加率  , 飛びレベル時のコスト削減率
            SEC_F(1)     , 1.0, 0.9, //基本詠唱時間  , ＋１レベル毎の詠唱時間増加率, 飛びレベル時の詠唱時間削減率
            SEC_F(0.5)   , 1.0, 0.9, //基本発動時間  , ＋１レベル毎の発動時間増加率, 飛びレベル時の発動時間削減率
            SEC_F(60*10) , 1.0,      //基本持続時間  , ＋１レベル毎の持続時間の乗率
            1.0          , 1.0       //基本維持コスト, ＋１レベル毎の維持コストの乗率
           ) {

    //数値の意味は VreathMagic.cpp のコメント参照
    lvinfo_[7].pno_ =  66;
    lvinfo_[6].pno_ =  74;
    lvinfo_[5].pno_ =  82;
    lvinfo_[4].pno_ =  90;
    lvinfo_[3].pno_ =  98;
    lvinfo_[2].pno_ = 106;
    lvinfo_[1].pno_ = 114;
    lvinfo_[0].pno_ = 122;

    pEffect_ = NEW EffectTorpedoMagic("EffectTorpedoMagic");
    pEffect_->inactivate();
    appendGroupChild(pEffect_);
}

void TorpedoMagic::onReset() {
    Magic::onReset();
    pEffect_->inactivate();
    MyTorpedoController::torpedo_num_ = 0;
}

void TorpedoMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP);
        pEffect_->setCullingDraw(false);
        pEffect_->getVecVehicle()->setFaceAngVelo(AXIS_Z, 100);
        pEffect_->setScale(1000);
        pEffect_->activate();
    }
}

void TorpedoMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setPositionAt(pMYSHIP);
        pEffect_->addScale(10);
    }
}

void TorpedoMagic::processCastingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void TorpedoMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void TorpedoMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->setScale(1000);
        pEffect_->getVecVehicle()->setFaceAngVelo(AXIS_Z, 3000);
    }
}

void TorpedoMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->addScale(100);
    }
}

void TorpedoMagic::processInvokingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void TorpedoMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

void TorpedoMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    //光子魚雷発射可能数を変更。
    MyTorpedoController::torpedo_num_ = prm_now_level;
}

void TorpedoMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

TorpedoMagic::~TorpedoMagic() {
}
