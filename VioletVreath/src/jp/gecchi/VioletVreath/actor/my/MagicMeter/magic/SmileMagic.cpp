#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SmileMagic::SmileMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,                 //max_level
            100       , 1.0,   //基本魔法コスト , 飛びレベル時の rate
            12        , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60        , 0.9,   //基本発動時間   , 飛びレベル時の rate
            0         , 0.0,   //基本持続時間   , ＋１レベル毎の持続時間の乗率
            0         , 0.0    //基本維持コスト , ＋１レベル毎の維持コストの乗率
        ) {

    //数値の意味は VreathMagic.cpp のコメント参照
    lvinfo_[7].pno_ =  4;
    lvinfo_[6].pno_ = 12;
    lvinfo_[5].pno_ = 20;
    lvinfo_[4].pno_ = 28;
    lvinfo_[3].pno_ = 36;
    lvinfo_[2].pno_ = 44;
    lvinfo_[1].pno_ = 52;
    lvinfo_[0].pno_ = 60;

    pMoji_ = NEW SpriteLabelTest("(^_^)");
    pMoji_->update("SMILE(^_^)SMILE");
    pMoji_->inactivateImmed();
    addSubGroup(pMoji_);
}

void SmileMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    pMoji_->locateWith(P_MYSHIP);
    pMoji_->setAlpha(0.9);
    pMoji_->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    pMoji_->_pKurokoA->setFaceAngVelo(AXIS_X, 200);
    pMoji_->_pKurokoA->setFaceAngVelo(AXIS_Y, 300);
    pMoji_->activate();
}
void SmileMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    pMoji_->_X += 1000;
    pMoji_->_Y += 1000;
}
void SmileMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}


void SmileMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    pMoji_->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}

void SmileMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
}

void SmileMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
}


int SmileMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //ニコニコビーム発射
    std::string s = "";
    for (int i = 0; i < prm_level; i++) {
        s += "(^_^)SMILE!\n";
    }
    pMoji_->update(s.c_str());
    return r;
}

void SmileMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    _TRACE_("SmileMagic::processEffectBegin (^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE");
}

void SmileMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    //即効性魔法は processEffectingBehavior はコールされないはず
    throwGgafCriticalException("SmileMagic::processEffectingBehavior 即効性魔法は processEffectingBehavior はコールされないはず");
//    _TRACE_("SmileMagic::processEffectingBehavior (^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE");
}

void SmileMagic::processEffectFinish(int prm_justbefore_level) {
    pMoji_->inactivate();
    _TRACE_("SmileMagic::processEffectFinish (^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE");
}

SmileMagic::~SmileMagic() {
}
