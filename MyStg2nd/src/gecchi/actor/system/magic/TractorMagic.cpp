#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

TractorMagic::TractorMagic(const char* prm_name, AmountGraph* prm_pMP)
        : Magic(prm_name, prm_pMP,
                2,          //max_level
                100*4   , 0.9,   //基本魔法コスト , 飛びレベル時の rate
                1       , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
                1       , 0.9,   //基本発動時間   , 飛びレベル時の rate
                60*10   , 0.0,   //基本持続時間   , 各レベルの削減割合
                1.01    , 0.0    //基本維持コスト , 各レベル時の rate
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
    _lvinfo[1]._pno = 28;
    _lvinfo[2]._pno = 24;

    _is_tracting = false;
}

void TractorMagic::processCastBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastFinish(int prm_now_level, int prm_new_level) {
}


void TractorMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokeingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokeFinish(int prm_now_level, int prm_new_level) {
    P_MYSHIP->changeEffectTechniqueInterim("Flush", 6); //フラッシュ
}

int TractorMagic::effect(int prm_level) {
    _is_tracting = true;
	int r = Magic::effect(prm_level);
	return r;
}

void TractorMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
}
void TractorMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}
void TractorMagic::processEffectFinish(int prm_justbefore_level) {
    _is_tracting = false;
}

TractorMagic::~TractorMagic() {
}
