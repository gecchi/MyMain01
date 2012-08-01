#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TorpedoMagic::TorpedoMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            8,               //max_level
            1000*4  , 0.9,   //基本魔法コスト , 飛びレベル時の rate
            60*3    , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60*2    , 0.9,   //基本発動時間   , 飛びレベル時の rate
            60*60*10, 1.0,   //基本持続時間   , ＋１レベル毎の持続時間の乗率
            1.0     , 1.0    //基本維持コスト , ＋１レベル毎の維持コストの乗率
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
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);

}

void TorpedoMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    pEffect_->locateWith(P_MYSHIP);
    pEffect_->setAlpha(0.9);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    pEffect_->_pScaler->setScale(1000);
    pEffect_->activate();
}

void TorpedoMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->locateWith(P_MYSHIP);
    pEffect_->_pScaler->addScale(10);
}

void TorpedoMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void TorpedoMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->setScale(1000);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}

void TorpedoMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->addScale(100);
}

void TorpedoMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

int TorpedoMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //光子魚雷発射可能数を変更。
    MyTorpedoController::torpedo_num_ = prm_level;
    return r;
}

void TorpedoMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
}

void TorpedoMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

void TorpedoMagic::processEffectFinish(int prm_justbefore_level) {
    MyTorpedoController::torpedo_num_ = 0;
}

TorpedoMagic::~TorpedoMagic() {
}
