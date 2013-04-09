#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpeedMagic::SpeedMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,          //max_level
            1000      , 0.9,   //基本魔法コスト , 飛びレベル時の rate
            60*0.3    , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60*0.1    , 0.9,   //基本発動時間   , 飛びレベル時の rate
            60*60*2   , 0.9,   //基本持続時間   , ＋１レベル毎の持続時間の乗率
            0         , 0.0    //基本維持コスト , ＋１レベル毎の維持コストの乗率
           ) {

    //数値の意味は VreathMagic.cpp のコメント参照
    lvinfo_[7].pno_ =  70;
    lvinfo_[6].pno_ =  78;
    lvinfo_[5].pno_ =  86;
    lvinfo_[4].pno_ =  94;
    lvinfo_[3].pno_ = 102;
    lvinfo_[2].pno_ = 110;
    lvinfo_[1].pno_ = 118;
    lvinfo_[0].pno_ = 126;

    pEffect_ = NEW EffectSpeedMagic("EffectSpeedMagic");
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);
}
void SpeedMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    pEffect_->locateAs(P_MYSHIP);
    pEffect_->setAlpha(0.9);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    pEffect_->_pScaler->setScale(1000);
    pEffect_->activate();
}

void SpeedMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->locateAs(P_MYSHIP);
    pEffect_->_pScaler->addScale(10);
}

void SpeedMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void SpeedMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->setScale(1000);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}

void SpeedMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->addScale(100);
}

void SpeedMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

int SpeedMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //スピードを変更する。
    P_MYSHIP->setMoveSpeedLv((prm_level+1)*4);
    return r;
}

void SpeedMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
}

void SpeedMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

void SpeedMagic::processEffectFinish(int prm_justbefore_level) {
    P_MYSHIP->setMoveSpeedLv((0+1)*4);
}

SpeedMagic::~SpeedMagic() {
}
