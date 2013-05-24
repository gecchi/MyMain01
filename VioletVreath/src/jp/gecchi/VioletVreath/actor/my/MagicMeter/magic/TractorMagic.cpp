#include "stdafx.h"
#include "TractorMagic.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TractorMagic::TractorMagic(const char* prm_name, AmountGraph* prm_pMP)
        : Magic(prm_name, prm_pMP,
                2,          //max_level
                100*4   , 0.9,   //基本魔法コスト , 飛びレベル時の rate
                1       , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
                1       , 0.9,   //基本発動時間   , 飛びレベル時の rate
                120*10  , 1.0,   //基本持続時間   , ＋１レベル毎の持続時間の乗率
                1.01    , 1.2    //基本維持コスト , ＋１レベル毎の維持コストの乗率
            ) {

    //数値の意味は VreathMagic.cpp のコメント参照
    lvinfo_[7].pno_ =  6;
    lvinfo_[6].pno_ = 14;
    lvinfo_[5].pno_ = 22;
    lvinfo_[4].pno_ = 30;
    lvinfo_[3].pno_ = 38;
    lvinfo_[2].pno_ = 46;
    lvinfo_[1].pno_ = 54;
    lvinfo_[0].pno_ = 62;

    is_tracting_ = false;
}

void TractorMagic::processCastBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}


void TractorMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    P_MYSHIP->effectFlush(6); //フラッシュ
}

int TractorMagic::effect(int prm_level) {
    _TRACE_("TractorMagic::effect 前 is_tracting_="<<is_tracting_<<" level_="<<level_<<" prm_level="<<prm_level);
    int r = Magic::effect(prm_level);
    if ( prm_level == 0) {
        is_tracting_ = false;
    } else {
        is_tracting_ = true;
    }
    _TRACE_("TractorMagic::effect 後 is_tracting_="<<is_tracting_<<" level_="<<level_<<" prm_level="<<prm_level);
    return r;
}

void TractorMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
}
void TractorMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}
void TractorMagic::processEffectFinish(int prm_justbefore_level) {
    _TRACE_("TractorMagic::effect 前 is_tracting_="<<is_tracting_<<" level_="<<level_<<" prm_justbefore_level="<<prm_justbefore_level);
    is_tracting_ = false;
    _TRACE_("TractorMagic::effect 後 is_tracting_="<<is_tracting_<<" level_="<<level_<<" prm_justbefore_level="<<prm_justbefore_level);
}

TractorMagic::~TractorMagic() {
}
