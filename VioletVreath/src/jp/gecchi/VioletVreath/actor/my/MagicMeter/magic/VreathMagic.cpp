#include "stdafx.h"
#include "VreathMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectVreathMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VreathMagic::VreathMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,                       //max_level
            1000      , 1.0, 0.9,    //基本魔法コスト, ＋１レベル毎のコスト増加率  , 飛びレベル時のコスト削減率
            60        , 1.0, 0.9,    //基本詠唱時間  , ＋１レベル毎の詠唱時間増加率, 飛びレベル時の詠唱時間削減率
            60        , 1.0, 0.9,    //基本発動時間  , ＋１レベル毎の発動時間増加率, 飛びレベル時の発動時間削減率
            60*60*3   , 0.3,         //基本持続時間  , ＋１レベル毎の持続時間の乗率
            0         , 0.0          //基本維持コスト, ＋１レベル毎の維持コストの乗率
        ) {

    //左列選択可能状態、右列選択不可状態
    //    | 0          |  1         |  2 Lockon�Z |  3 Lockon�Z |  4 Vreath�Z|  5 Vreath�Z|  6 Tractor�Z|  7 Tractor�Z|
    //    | 8          |  9         | 10 Lockon�Y | 11 Lockon�Y | 12 Vreath�Y| 13 Vreath�Y| 14 Tractor�Y| 15 Tractor�Y|
    //    | 16         | 17         | 18 Lockon�X | 19 Lockon�X | 20 Vreath�X| 21 Vreath�X| 22 Tractor�X| 23 Tractor�X|
    //    | 24         | 25         | 26 Lockon�W | 27 Lockon�W | 28 Vreath�W| 29 Vreath�W| 30 Tractor�W| 31 Tractor�W|
    //    | 32         | 33         | 34 Lockon�V | 35 Lockon�V | 36 Vreath�V| 37 Vreath�V| 38 Tractor�V| 39 Tractor�V|
    //    | 40 Option�]| 41 Option�]| 42 Lockon�U | 43 Lockon�U | 44 Vreath�U| 45 Vreath�U| 46 Tractor�U| 47 Tractor�U|
    //    | 48 Option�\| 49 Option�\| 50 Lockon�T | 51 Lockon�T | 52 Vreath�T| 53 Vreath�T| 54 Tractor�T| 55 Tractor�T|
    //    | 56 Option�[| 57 Option�[| 58 Empty    | 59 Empty    | 60 Empty   | 61 Empty   | 62 Empty    | 63 Empty    |
    //    | 64 Option�Z| 65 Option�Z| 66 Torpedo�Z| 67 Torpedo�Z| 68 Laser�Z | 69 Laser�Z | 70 Speed�Z  | 71 Speed�Z  |
    //    | 72 Option�Y| 73 Option�Y| 74 Torpedo�Y| 75 Torpedo�Y| 76 Laser�Y | 77 Laser�Y | 78 Speed�Y  | 79 Speed�Y  |
    //    | 80 Option�X| 81 Option�X| 82 Torpedo�X| 83 Torpedo�X| 84 Laser�X | 85 Laser�X | 86 Speed�X  | 87 Speed�X  |
    //    | 88 Option�W| 89 Option�W| 90 Torpedo�W| 91 Torpedo�W| 92 Laser�W | 93 Laser�W | 94 Speed�W  | 95 Speed�W  |
    //    | 96 Option�V| 97 Option�V| 98 Torpedo�V| 99 Torpedo�V|100 Laser�V |101 Laser�V |102 Speed�V  |103 Speed�V  |
    //    |104 Option�U|105 Option�U|106 Torpedo�U|107 Torpedo�U|108 Laser�U |109 Laser�U |110 Speed�U  |111 Speed�U  |
    //    |112 Option�T|113 Option�T|114 Torpedo�T|115 Torpedo�T|116 Laser�T |117 Laser�T |118 Speed�T  |119 Speed�T  |
    //    |120 Empty   |121 Empty   |122 Empty    |123 Empty    |124 Empty   |125 Empty   |126 Empty    |127 Empty    |

//    lvinfo_[7].pno_ =  4;
//    lvinfo_[6].pno_ = 12;
    lvinfo_[5].pno_ = 20;
    lvinfo_[4].pno_ = 28;
    lvinfo_[3].pno_ = 36;
    lvinfo_[2].pno_ = 44;
    lvinfo_[1].pno_ = 52;
    lvinfo_[0].pno_ = 60;

    pEffect_ = NEW EffectVreathMagic001("EffectVreathMagic001");
    pEffect_->inactivate();
    addSubGroup(pEffect_);

    for (int i = 0; i <= MMETER_MAX_LEVEL; i++) {
        beat_time_[i]               = 0;
        apaInt_vreath_per_frame_[i] = 0;
        aInt_total_vreath_[i]       = 0;
        r_add_vreath_[i]            = 0.0;
    }
    //１回の呼吸時間テーブル
    beat_time_[0] = 0.0;
    beat_time_[1] = 180;
    beat_time_[2] = beat_time_[1]/2; //だんだん
    beat_time_[3] = beat_time_[2]/2; //呼吸が
    beat_time_[4] = beat_time_[3]/2; //早く
    beat_time_[5] = beat_time_[4]/2; //なる！
//    beat_time_[6] = beat_time_[5]/2;
//    beat_time_[7] = beat_time_[6]/2;

    //毎フレーム加算されるVreath乗率テーブル
    for (int lv = 0; lv <= max_level_; lv++) {
        //r_add_vreath_ = - sqrt((max_lv-1)^2 - (lv-1)^2) + max_lv
        //max_level=7 の場合
        //lv =7.0 で 率 7.0
        //lv =1.0 で 率 1.0
        //となるような1/4円
        r_add_vreath_[lv] =  -1.0*sqrt((double)(((max_level_-1)*(max_level_-1)) - ((lv-1)*(lv-1)))) + max_level_;
    }

    for (int lv = 0; lv <= max_level_; lv++) {
        if (beat_time_[lv] == 0) {
            apaInt_vreath_per_frame_[lv] = NEW int[1];
            apaInt_vreath_per_frame_[lv][0] = 0;
        } else {
            apaInt_vreath_per_frame_[lv] = NEW int[beat_time_[lv]];
            //前半
            for (frame f = 0; f <= beat_time_[lv]/2; f++) {
                int t = f*3600.0/beat_time_[lv];
                apaInt_vreath_per_frame_[lv][f] = MY_SHIP_VREATH_COST*2.0*UTIL::SMOOTH_DV[t];
            }
            //後半
            for (frame f = beat_time_[lv]/2 + 1; f < beat_time_[lv]; f++) {
                apaInt_vreath_per_frame_[lv][f] = 0; //吸わない＝vreathは毎フレームMY_SHIP_VREATH_COST削られる
            }
        }
    }
    //各レベルの総呼吸量(aInt_total_vreath_[])を計算
    for (int lv = 0; lv <= max_level_; lv++) {
        if (beat_time_[lv] == 0) {
            aInt_total_vreath_[lv] = 0;
        } else {
            int sum_v_onebeat = 0; //1呼吸の息の量
            for (frame f = 0; f < beat_time_[lv]; f++) {
                sum_v_onebeat += apaInt_vreath_per_frame_[lv][f] * r_add_vreath_[lv];
            }
            for (frame f = 0; f < beat_time_[lv]; f++) {
                sum_v_onebeat -= MY_SHIP_VREATH_COST;
            }
            //呼吸回数を乗じて総呼吸量を計算
            aInt_total_vreath_[lv] = sum_v_onebeat * ((1.0 * lvinfo_[lv].time_of_effect_) / beat_time_[lv]);
        }
    }
}

void VreathMagic::onReset() {
    Magic::onReset();
    pEffect_->inactivate();
}

void VreathMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->positionAs(P_MYSHIP);
        pEffect_->setAlpha(0.9);
        pEffect_->_pKuroko->setFaceAngVelo(AXIS_Z, 100);
        pEffect_->_pScaler->setScale(1000);
        pEffect_->activate();
    }
}

void VreathMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->positionAs(P_MYSHIP);
        pEffect_->_pScaler->addScale(10);
    }
}

void VreathMagic::processCastingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void VreathMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void VreathMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->_pScaler->setScale(1000);
        pEffect_->_pKuroko->setFaceAngVelo(AXIS_Z, 3000);
    }
}

void VreathMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pEffect_->_pScaler->addScale(100);
    }
}

void VreathMagic::processInvokingCancel(int prm_now_level) {
    pEffect_->inactivate();
}

void VreathMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

void VreathMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    if ( prm_now_level > 0) {
    } else {
        //レベル0へレベルダウン時
        pEffect_->inactivate();
    }
}
void VreathMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    if (beat_time_[prm_now_level] > 0) {
        frame f = getActiveFrame() % beat_time_[prm_now_level];
#ifdef MY_DEBUG
        if (f > beat_time_[prm_now_level]) {
            throwGgafCriticalException("VreathMagic::processEffectingBehavior 範囲外です。 f="<<f<<" beat_time_["<<prm_now_level<<"]");
        }
#endif
        int add_vreath = apaInt_vreath_per_frame_[prm_now_level][f] * r_add_vreath_[prm_now_level];
        P_MYSHIP->_pStatus->plus(STAT_Stamina, add_vreath);
    } else {

    }
}

int VreathMagic::calcTotalVreath(int prm_now_level, int prm_target_up_level) {
    int sum_vreath = 0;
    for (int lv = prm_now_level+1; lv <= prm_target_up_level; lv++) {
        sum_vreath += aInt_total_vreath_[lv];
    }
    return sum_vreath;
}

VreathMagic::~VreathMagic() {
    for (int lv = 0; lv <= max_level_; lv++) {
        GGAF_DELETEARR(apaInt_vreath_per_frame_[lv]);
    }
}
