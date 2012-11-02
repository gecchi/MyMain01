#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VreathMagic::VreathMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,          //max_level
            100       , 1.0,   //äÓñ{ñÇñ@ÉRÉXÉg , îÚÇ—ÉåÉxÉãéûÇÃ rate
            60        , 0.9,   //äÓñ{ârè•éûä‘   , îÚÇ—ÉåÉxÉãéûÇÃ rate
            60        , 0.9,   //äÓñ{î≠ìÆéûä‘   , îÚÇ—ÉåÉxÉãéûÇÃ rate
            60*60*3   , 0.3,   //äÓñ{éùë±éûä‘   , Å{ÇPÉåÉxÉãñàÇÃéùë±éûä‘ÇÃèÊó¶
            4         , 2.0    //äÓñ{à€éùÉRÉXÉg , Å{ÇPÉåÉxÉãñàÇÃà€éùÉRÉXÉgÇÃèÊó¶
        ) {

    //ç∂óÒëIëâ¬î\èÛë‘ÅAâEóÒëIëïsâ¬èÛë‘
    //    | 0          |  1         |  2 LockonáZ |  3 LockonáZ |  4 VreatháZ|  5 VreatháZ|  6 TractoráZ|  7 TractoráZ|
    //    | 8          |  9         | 10 LockonáY | 11 LockonáY | 12 VreatháY| 13 VreatháY| 14 TractoráY| 15 TractoráY|
    //    | 16         | 17         | 18 LockonáX | 19 LockonáX | 20 VreatháX| 21 VreatháX| 22 TractoráX| 23 TractoráX|
    //    | 24         | 25         | 26 LockonáW | 27 LockonáW | 28 VreatháW| 29 VreatháW| 30 TractoráW| 31 TractoráW|
    //    | 32         | 33         | 34 LockonáV | 35 LockonáV | 36 VreatháV| 37 VreatháV| 38 TractoráV| 39 TractoráV|
    //    | 40 Optioná]| 41 Optioná]| 42 LockonáU | 43 LockonáU | 44 VreatháU| 45 VreatháU| 46 TractoráU| 47 TractoráU|
    //    | 48 Optioná\| 49 Optioná\| 50 LockonáT | 51 LockonáT | 52 VreatháT| 53 VreatháT| 54 TractoráT| 55 TractoráT|
    //    | 56 Optioná[| 57 Optioná[| 58 Empty    | 59 Empty    | 60 Empty   | 61 Empty   | 62 Empty    | 63 Empty    |
    //    | 64 OptionáZ| 65 OptionáZ| 66 TorpedoáZ| 67 TorpedoáZ| 68 LaseráZ | 69 LaseráZ | 70 SpeedáZ  | 71 SpeedáZ  |
    //    | 72 OptionáY| 73 OptionáY| 74 TorpedoáY| 75 TorpedoáY| 76 LaseráY | 77 LaseráY | 78 SpeedáY  | 79 SpeedáY  |
    //    | 80 OptionáX| 81 OptionáX| 82 TorpedoáX| 83 TorpedoáX| 84 LaseráX | 85 LaseráX | 86 SpeedáX  | 87 SpeedáX  |
    //    | 88 OptionáW| 89 OptionáW| 90 TorpedoáW| 91 TorpedoáW| 92 LaseráW | 93 LaseráW | 94 SpeedáW  | 95 SpeedáW  |
    //    | 96 OptionáV| 97 OptionáV| 98 TorpedoáV| 99 TorpedoáV|100 LaseráV |101 LaseráV |102 SpeedáV  |103 SpeedáV  |
    //    |104 OptionáU|105 OptionáU|106 TorpedoáU|107 TorpedoáU|108 LaseráU |109 LaseráU |110 SpeedáU  |111 SpeedáU  |
    //    |112 OptionáT|113 OptionáT|114 TorpedoáT|115 TorpedoáT|116 LaseráT |117 LaseráT |118 SpeedáT  |119 SpeedáT  |
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
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);

    for (int i = 0; i <= MMETER_MAX_LEVEL; i++) {
        beat_time_[i]               = 0;
        apaInt_vreath_per_frame_[i] = 0;
        aInt_total_vreath_[i]       = 0;
        r_add_vreath_[i]            = 0.0;
    }

    beat_time_[0] = 0.0;
    beat_time_[1] = 180;
    beat_time_[2] = beat_time_[1]/2;
    beat_time_[3] = beat_time_[2]/2;
    beat_time_[4] = beat_time_[3]/2;
    beat_time_[5] = beat_time_[4]/2;
//    beat_time_[6] = beat_time_[5]/2;
//    beat_time_[7] = beat_time_[6]/2;

    //ñàÉtÉåÅ[ÉÄâ¡éZÇ≥ÇÍÇÈVreathèÊó¶ÉeÅ[ÉuÉã
    for (int lv = 0; lv <= max_level_; lv++) {
        //r_add_vreath_ = - sqrt((max_lv-1)^2 - (lv-1)^2) + max_lv
        //max_level=7 ÇÃèÍçá
        //lv =7.0 Ç≈ ó¶ 7.0
        //lv =1.0 Ç≈ ó¶ 1.0
        //Ç∆Ç»ÇÈÇÊÇ§Ç»1/4â~
        r_add_vreath_[lv] =  -1.0*sqrt((double)(((max_level_-1)*(max_level_-1)) - ((lv-1)*(lv-1)))) + max_level_;
    }

    for (int lv = 0; lv <= max_level_; lv++) {
        if (beat_time_[lv] == 0) {
            apaInt_vreath_per_frame_[lv] = NEW int[1];
            apaInt_vreath_per_frame_[lv][0] = 0;
        } else {
            apaInt_vreath_per_frame_[lv] = NEW int[beat_time_[lv]];
            //ëOîº
            for (frame f = 0; f <= beat_time_[lv]/2; f++) {
                int t = f*3600.0/beat_time_[lv];
                apaInt_vreath_per_frame_[lv][f] = MY_SHIP_VREATH_COST*2.0*UTIL::SMOOTH_DV[t];
            }
            //å„îº
            for (frame f = beat_time_[lv]/2 + 1; f < beat_time_[lv]; f++) {
                apaInt_vreath_per_frame_[lv][f] = 0; //ãzÇÌÇ»Ç¢ÅÅvreathÇÕñàÉtÉåÅ[ÉÄMY_SHIP_VREATH_COSTçÌÇÁÇÍÇÈ
            }
        }
    }
    //äeÉåÉxÉãÇÃëçåƒãzó (aInt_total_vreath_[])ÇåvéZ
    for (int lv = 0; lv <= max_level_; lv++) {
        if (beat_time_[lv] == 0) {
            aInt_total_vreath_[lv] = 0;
        } else {
            int sum_v_onebeat = 0; //1åƒãzÇÃëßÇÃó 
            for (frame f = 0; f < beat_time_[lv]; f++) {
                sum_v_onebeat += apaInt_vreath_per_frame_[lv][f] * r_add_vreath_[lv];
            }
            for (frame f = 0; f < beat_time_[lv]; f++) {
                sum_v_onebeat -= MY_SHIP_VREATH_COST;
            }
            //åƒãzâÒêîÇèÊÇ∂Çƒëçåƒãzó ÇåvéZ
            aInt_total_vreath_[lv] = sum_v_onebeat * ((1.0 * lvinfo_[lv].time_of_effect_) / beat_time_[lv]);
        }
    }
}

void VreathMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    pEffect_->locateWith(P_MYSHIP);
    pEffect_->setAlpha(0.9);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    pEffect_->_pScaler->setScale(1000);
    pEffect_->activate();
}

void VreathMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->locateWith(P_MYSHIP);
    pEffect_->_pScaler->addScale(10);
}

void VreathMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void VreathMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->setScale(1000);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}

void VreathMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->addScale(100);
}

void VreathMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

int VreathMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //ÉåÉxÉãÇÃílÇ…âûÇ∂ÇƒÅAprocessEffectingBehavior()Ç…ÇƒåƒãzÇÇ®Ç±Ç»Ç§ÇÃÇ≈ÅAÇ±Ç±Ç≈ÇÃê›íËÇÕì¡Ç…ñ≥Ç¢ÅB
    return r;
}

void VreathMagic::processEffectBegin(int prm_last_level, int prm_now_level) {

}
void VreathMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    if (beat_time_[prm_now_level] > 0) {
        frame f = getActivePartFrame() % beat_time_[prm_now_level];
#ifdef MY_DEBUG
        if (f > beat_time_[prm_now_level]) {
            throwGgafCriticalException("VreathMagic::processEffectingBehavior îÕàÕäOÇ≈Ç∑ÅB f="<<f<<" beat_time_["<<prm_now_level<<"]");
        }
#endif
        int add_vreath = apaInt_vreath_per_frame_[prm_now_level][f] * r_add_vreath_[prm_now_level];
        P_MYSHIP->vreath_.inc(add_vreath);
    }
}

void VreathMagic::processEffectFinish(int prm_justbefore_level) {
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
        DELETEARR_IMPOSSIBLE_NULL(apaInt_vreath_per_frame_[lv]);
    }
}
