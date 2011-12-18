#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

SpeedMagic::SpeedMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,          //max_level
            100       , 0.9,   //基本魔法コスト , 飛びレベル時の rate
            60*0.3    , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60*0.1    , 0.9,   //基本発動時間   , 飛びレベル時の rate
            60*60*10  , 0.0,   //基本持続時間, 各レベルの削減割合
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
    _lvinfo[1]._pno = 60;
    _lvinfo[2]._pno = 56;
    _lvinfo[3]._pno = 52;
    _lvinfo[4]._pno = 48;
    _lvinfo[5]._pno = 44;

    _pEffect = NEW EffectSpeedMagic("EffectSpeedMagic");
    _pEffect->inactivateImmediately();
    addSubGroup(_pEffect);
}
void SpeedMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    _pEffect->locateAs(P_MYSHIP);
    _pEffect->setAlpha(0.9);
    _pEffect->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    _pEffect->_pScaler->setScale(1000);
    _pEffect->activate();
}
void SpeedMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    _pEffect->locateAs(P_MYSHIP);
    _pEffect->_pScaler->addScale(10);
}
void SpeedMagic::processCastFinish(int prm_now_level, int prm_new_level) {
}


void SpeedMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    _pEffect->_pScaler->setScale(1000);
    _pEffect->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}
void SpeedMagic::processInvokeingBehavior(int prm_now_level, int prm_new_level) {
    _pEffect->_pScaler->addScale(100);
}
void SpeedMagic::processInvokeFinish(int prm_now_level, int prm_new_level) {
    _pEffect->inactivate();
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
    P_MYSHIP->setMoveSpeedLv((0+1)*5);
}

SpeedMagic::~SpeedMagic() {
}
