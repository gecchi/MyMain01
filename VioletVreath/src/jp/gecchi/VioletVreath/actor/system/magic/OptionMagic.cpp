#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

OptionMagic::OptionMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            8,               //max_level
            1000    , 0.9,   //基本魔法コスト , 飛びレベル時の rate
            60*2    , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60*0.2  , 0.9,   //基本発動時間   , 飛びレベル時の rate
            60*60    , 0.0,  //基本持続時間   , 各レベルの削減割合
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
    _lvinfo[0]._pno = 3;
    _lvinfo[1]._pno = 61;
    _lvinfo[2]._pno = 57;
    _lvinfo[3]._pno = 53;
    _lvinfo[4]._pno = 49;
    _lvinfo[5]._pno = 45;
    _lvinfo[6]._pno = 49;
    _lvinfo[7]._pno = 45;
    _lvinfo[8]._pno = 41;

    _papEffect = NEW GgafDxDrawableActor*[8];
    for (int i = 0; i < 8; i++) {
        _papEffect[i] = NEW EffectMagic001("EF");
        _papEffect[i]->inactivateImmed();
        addSubGroup(_papEffect[i]);
    }
}
void OptionMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    angle* paAngWay = NEW angle[prm_new_level-prm_now_level];
    GgafDxUtil::getRadialAngle2D(0, prm_new_level-prm_now_level, paAngWay);
    int n = 0;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        _papEffect[lv-1]->locateAs(P_MYSHIP);
        _papEffect[lv-1]->_pKurokoA->setRzRyMvAng(paAngWay[n], D90ANG);
        _papEffect[lv-1]->_pKurokoA->setMvVelo(2000);
        _papEffect[lv-1]->_pKurokoA->setMvAcce(-5);
        _papEffect[lv-1]->setAlpha(0.9);
        _papEffect[lv-1]->setScaleR(2.0f);
        _papEffect[lv-1]->activate();
        n++;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
    _r_effect = 1;

}

void OptionMagic::processCastingBehavior(int prm_now_level, int prm_new_level){
    _r_effect += 0.02;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        _papEffect[lv-1]->setScaleR(_r_effect);
    }
}

void OptionMagic::processCastFinish(int prm_now_level, int prm_new_level) {

}

void OptionMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    _r_effect = 1;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        _papEffect[lv-1]->_pKurokoA->setMvVelo(0);
        _papEffect[lv-1]->_pKurokoA->setMvAcce(0);
        _papEffect[lv-1]->_pKurokoB->execGravitationVxyzMvSequence(
               P_MYOPTIONCON->_X + P_MYOPTIONCON->_papMyOption[lv-1]->_Xorg,
               P_MYOPTIONCON->_Y + P_MYOPTIONCON->_papMyOption[lv-1]->_Yorg,
               P_MYOPTIONCON->_Z + P_MYOPTIONCON->_papMyOption[lv-1]->_Zorg,
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
    P_MYOPTIONCON->setNumOption(prm_level);
    P_MYOPTIONCON->adjustDefaltAngPosition(60);
	return r;
}

void OptionMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    //レベルアップ時、エフェクトの処理
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        _papEffect[lv-1]->inactivateDelay(120); //非活動の保険
        _papEffect[lv-1]->_pKurokoB->_gravitation_mv_seq_pActor_target = P_MYOPTIONCON->_papMyOption[lv-1];
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    _r_effect -= 0.01f;
    //レベルアップ時、エフェクトの処理
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        _papEffect[lv-1]->setAlpha(_r_effect);
//        _papEffect[lv-1]->setScaleR(3.0f+(1.0f-_r_effect)*4.0);
        _papEffect[lv-1]->locateAs(P_MYOPTIONCON->_papMyOption[lv-1]);
        P_MYOPTIONCON->_papMyOption[lv-1]->setAlpha(1.0f-_r_effect);
    }
    if (_r_effect < 0) {
        for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
            _papEffect[lv-1]->inactivate();
            P_MYOPTIONCON->_papMyOption[lv-1]->setAlpha(1.0);
        }
    }
}

void OptionMagic::processEffectFinish(int prm_justbefore_level) {
    P_MYOPTIONCON->setNumOption(0);
}

OptionMagic::~OptionMagic() {
    DELETEARR_IMPOSSIBLE_NULL(_papEffect);
}
