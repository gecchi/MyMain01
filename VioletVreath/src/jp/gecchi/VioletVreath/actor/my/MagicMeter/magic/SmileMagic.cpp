#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SmileMagic::SmileMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,          //max_level
            100       , 1.0,   //Šî–{–‚–@ƒRƒXƒg , ”ò‚ÑƒŒƒxƒ‹Žž‚Ì rate
            60*0.3    , 0.9,   //Šî–{‰r¥ŽžŠÔ   , ”ò‚ÑƒŒƒxƒ‹Žž‚Ì rate
            60*0.1    , 0.9,   //Šî–{”­“®ŽžŠÔ   , ”ò‚ÑƒŒƒxƒ‹Žž‚Ì rate
            0         , 0.0,   //Šî–{Ž‘±ŽžŠÔ   , {‚PƒŒƒxƒ‹–ˆ‚ÌŽ‘±ŽžŠÔ‚Ìæ—¦
            0         , 0.0    //Šî–{ˆÛŽƒRƒXƒg , {‚PƒŒƒxƒ‹–ˆ‚ÌˆÛŽƒRƒXƒg‚Ìæ—¦
        ) {
    //    | 0          |  1         |  2 Lockon‡Z |  3 Lockon‡Z |  4 Smile‡Z|  5 Smile‡Z|  6 Tractor‡Z|  7 Tractor‡Z|
    //    | 8          |  9         | 10 Lockon‡Y | 11 Lockon‡Y | 12 Smile‡Y| 13 Smile‡Y| 14 Tractor‡Y| 15 Tractor‡Y|
    //    | 16         | 17         | 18 Lockon‡X | 19 Lockon‡X | 20 Smile‡X| 21 Smile‡X| 22 Tractor‡X| 23 Tractor‡X|
    //    | 24         | 25         | 26 Lockon‡W | 27 Lockon‡W | 28 Smile‡W| 29 Smile‡W| 30 Tractor‡W| 31 Tractor‡W|
    //    | 32         | 33         | 34 Lockon‡V | 35 Lockon‡V | 36 Smile‡V| 37 Smile‡V| 38 Tractor‡V| 39 Tractor‡V|
    //    | 40 Option‡]| 41 Option‡]| 42 Lockon‡U | 43 Lockon‡U | 44 Smile‡U| 45 Smile‡U| 46 Tractor‡U| 47 Tractor‡U|
    //    | 48 Option‡\| 49 Option‡\| 50 Lockon‡T | 51 Lockon‡T | 52 Smile‡T| 53 Smile‡T| 54 Tractor‡T| 55 Tractor‡T|
    //    | 56 Option‡[| 57 Option‡[| 58 Empty    | 59 Empty    | 60 Empt  y | 61 Empty   | 62 Empty    | 63 Empty    |
    //    | 64 Option‡Z| 65 Option‡Z| 66 Torpedo‡Z| 67 Torpedo‡Z| 68 Laser‡Z | 69 Laser‡Z | 70 Speed‡Z  | 71 Speed‡Z  |
    //    | 72 Option‡Y| 73 Option‡Y| 74 Torpedo‡Y| 75 Torpedo‡Y| 76 Laser‡Y | 77 Laser‡Y | 78 Speed‡Y  | 79 Speed‡Y  |
    //    | 80 Option‡X| 81 Option‡X| 82 Torpedo‡X| 83 Torpedo‡X| 84 Laser‡X | 85 Laser‡X | 86 Speed‡X  | 87 Speed‡X  |
    //    | 88 Option‡W| 89 Option‡W| 90 Torpedo‡W| 91 Torpedo‡W| 92 Laser‡W | 93 Laser‡W | 94 Speed‡W  | 95 Speed‡W  |
    //    | 96 Option‡V| 97 Option‡V| 98 Torpedo‡V| 99 Torpedo‡V|100 Laser‡V |101 Laser‡V |102 Speed‡V  |103 Speed‡V  |
    //    |104 Option‡U|105 Option‡U|106 Torpedo‡U|107 Torpedo‡U|108 Laser‡U |109 Laser‡U |110 Speed‡U  |111 Speed‡U  |
    //    |112 Option‡T|113 Option‡T|114 Torpedo‡T|115 Torpedo‡T|116 Laser‡T |117 Laser‡T |118 Speed‡T  |119 Speed‡T  |
    //    |120 Empty   |121 Empty   |122 Empty    |123 Empty    |124 Empty   |125 Empty   |126 Empty    |127 Empty    |

    lvinfo_[7].pno_ =  4;
    lvinfo_[6].pno_ = 12;
    lvinfo_[5].pno_ = 20;
    lvinfo_[4].pno_ = 28;
    lvinfo_[3].pno_ = 36;
    lvinfo_[2].pno_ = 44;
    lvinfo_[1].pno_ = 52;
    lvinfo_[0].pno_ = 60;


    pEffect_ = NEW EffectSmileMagic001("EffectSmileMagic001");
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);

}
void SmileMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    pEffect_->locatedBy(P_MYSHIP);
    pEffect_->setAlpha(0.9);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    pEffect_->_pScaler->setScale(1000);
    pEffect_->activate();
}
void SmileMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->locatedBy(P_MYSHIP);
    pEffect_->_pScaler->addScale(10);
}
void SmileMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}


void SmileMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->setScale(1000);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}
void SmileMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->addScale(100);
}
void SmileMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

int SmileMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    return r;
}

void SmileMagic::processEffectBegin(int prm_last_level, int prm_now_level) {

}
void SmileMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
   
}

void SmileMagic::processEffectFinish(int prm_justbefore_level) {
//    P_MYSHIP->setMoveSpeedLv((0+1)*4);
}

SmileMagic::~SmileMagic() {
}
