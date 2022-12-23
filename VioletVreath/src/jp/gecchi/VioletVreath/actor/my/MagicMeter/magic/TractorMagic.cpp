#include "TractorMagic.h"

#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

TractorMagic::TractorMagic(const char* prm_name, int* prm_pMP)
        : Magic(prm_name, prm_pMP,
                2,                    //max_level
                1000*4    , 1.0, 0.9,   //基本魔法コスト, ＋１レベル毎のコスト増加率  , 飛びレベル時のコスト削減率
                1         , 1.0, 0.9,   //基本詠唱時間  , ＋１レベル毎の詠唱時間増加率, 飛びレベル時の詠唱時間削減率
                1         , 1.0, 0.9,   //基本発動時間  , ＋１レベル毎の発動時間増加率, 飛びレベル時の発動時間削減率
                SEC_F(20) , 1.5,        //基本持続時間  , ＋１レベル毎の持続時間の乗率
                1         , 1.1         //基本維持コスト, ＋１レベル毎の維持コストの乗率
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

void TractorMagic::onReset() {
    Magic::onReset();
    is_tracting_ = false;
}

void TractorMagic::processCastBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastingCancel(int prm_now_level) {
}
void TractorMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void TractorMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokingCancel(int prm_now_level) {

}
void TractorMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pMYSHIP->effectFlush(30); //フラッシュ
}

void TractorMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    if ( prm_now_level == 0) {
        is_tracting_ = false;
    } else {
        is_tracting_ = true;
    }
}
void TractorMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

TractorMagic::~TractorMagic() {
}
