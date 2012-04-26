#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

OptionMagic::OptionMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            9,               //max_level
            1000    , 0.9,   //基本魔法コスト , 飛びレベル時の rate
            60*2    , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60*0.8  , 0.9,   //基本発動時間   , 飛びレベル時の rate
            60*60 *60   , 0.0,  //基本持続時間   , 各レベルの削減割合
            0.0     , 0.0    //基本維持コスト , 各レベル時の rate
        ) {
//    |  0,   1,   2,   3 |
//    |  4,   5,   6,   7 |
//    |  8,   9,  10,  11 |
//    | 12,  13,  14,  15 |
//    | 16,  17,  18,  19 |
//    | 20,  21,  22,  23 |
//    | 24,  25,  26,  27 |
//    | 28,  29,  30,  31 |
//    | 32,  33,  34,  35 |
//    | 36,  37,  38,  39 |
//    | 40,  41,  42,  43 |
//    | 44,  45,  46,  47 |
//    | 48,  49,  50,  51 |
//    | 52,  53,  54,  55 |
//    | 56,  57,  58,  59 |
//    | 60,  61,  62,  63 |
    lvinfo_[0].pno_ = 3;
    lvinfo_[1].pno_ = 61;
    lvinfo_[2].pno_ = 57;
    lvinfo_[3].pno_ = 53;
    lvinfo_[4].pno_ = 49;
    lvinfo_[5].pno_ = 45;
    lvinfo_[6].pno_ = 41;
    lvinfo_[7].pno_ = 37;
    lvinfo_[8].pno_ = 33;
    lvinfo_[9].pno_ = 29;

    papEffect_ = NEW GgafDxDrawableActor*[max_level_];
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i] = NEW EffectMagic001("EF");
        papEffect_[i]->inactivateImmed();
        addSubGroup(papEffect_[i]);
    }
}
void OptionMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    angle* paAng_way = NEW angle[prm_new_level-prm_now_level];
    GgafDxUtil::getRadialAngle2D(0, prm_new_level-prm_now_level, paAng_way);
    int n = 0;
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i]->inactivateImmed();
    }
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        papEffect_[lv-1]->locatedBy(P_MYSHIP);
        papEffect_[lv-1]->_pKurokoA->setRzRyMvAng(paAng_way[n], D90ANG);
        papEffect_[lv-1]->_pKurokoA->setMvVelo(2000);
        papEffect_[lv-1]->_pKurokoA->setMvAcce(-5);
        papEffect_[lv-1]->setAlpha(0.9);
        papEffect_[lv-1]->setScaleR(2.0f);
        papEffect_[lv-1]->activate();
        n++;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAng_way);
    r_effect_ = 1;

}

void OptionMagic::processCastingBehavior(int prm_now_level, int prm_new_level){
    r_effect_ += 0.02;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        papEffect_[lv-1]->setScaleR(r_effect_);
    }
}

void OptionMagic::processCastFinish(int prm_now_level, int prm_new_level) {

}

void OptionMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    r_effect_ = 1;


    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrlr_[lv-1];
        papEffect_[lv-1]->_pKurokoA->setMvVelo(0);
        papEffect_[lv-1]->_pKurokoA->setMvAcce(0);
        papEffect_[lv-1]->_pKurokoB->execGravitationMvSequence(
               p->_X + p->pOption_->Xorg_,
               p->_Y + p->pOption_->Yorg_,
               p->_Z + p->pOption_->Zorg_,
               20000, 1000, 50000);
    }

}

void OptionMagic::processInvokeingBehavior(int prm_now_level, int prm_new_level)  {
}

void OptionMagic::processInvokeFinish(int prm_now_level, int prm_new_level) {
}
int OptionMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //オプション有効にする。
    //(processEffectBegin 時、 option は一度はbehave()されて座標を計算しておいてほしい）
    MyOptionController::setNumOption(prm_level);
    MyOptionController::adjustDefaltAngPosition(60);
    return r;
}

void OptionMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    //レベルアップ時、エフェクトの処理
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrlr_[lv-1];
        papEffect_[lv-1]->inactivateDelay(120); //非活動の保険
        papEffect_[lv-1]->_pKurokoB->_gravitation_mv_seq_pActor_target = p->pOption_;
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    r_effect_ -= 0.01f;
    //レベルアップ時、エフェクトの処理
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrlr_[lv-1];
        papEffect_[lv-1]->setAlpha(r_effect_);
//        papEffect_[lv-1]->setScaleR(3.0f+(1.0f-r_effect_)*4.0);
        papEffect_[lv-1]->locatedBy(p->pOption_);
        p->pOption_->setAlpha(1.0f-r_effect_);
    }
    if (r_effect_ < 0) {
        for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
            MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrlr_[lv-1];
            papEffect_[lv-1]->inactivate();
            p->pOption_->setAlpha(1.0);
        }
    }
}

void OptionMagic::processEffectFinish(int prm_justbefore_level) {
    MyOptionController::setNumOption(0);
}

OptionMagic::~OptionMagic() {
    DELETEARR_IMPOSSIBLE_NULL(papEffect_);
}
