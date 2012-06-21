#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

OptionMagic::OptionMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            9,               //max_level
            10000   , 0.9,   //Šî–{–‚–@ƒRƒXƒg , ”ò‚ÑƒŒƒxƒ‹‚Ì rate
            60*2    , 0.9,   //Šî–{‰r¥ŠÔ   , ”ò‚ÑƒŒƒxƒ‹‚Ì rate
            60*0.8  , 0.9,   //Šî–{”­“®ŠÔ   , ”ò‚ÑƒŒƒxƒ‹‚Ì rate
            60*60*3 , 1.0,   //Šî–{‘±ŠÔ   , {‚PƒŒƒxƒ‹–ˆ‚Ì‘±ŠÔ‚Ìæ—¦
            0.0     , 0.0    //Šî–{ˆÛƒRƒXƒg , {‚PƒŒƒxƒ‹–ˆ‚ÌˆÛƒRƒXƒg‚Ìæ—¦
           ) {
//    | 0          |  1         |  2 Lockon‡Z |  3 Lockon‡Z |  4 Vreath‡Z|  5 Vreath‡Z|  6 Tractor‡Z|  7 Tractor‡Z|
//    | 8          |  9         | 10 Lockon‡Y | 11 Lockon‡Y | 12 Vreath‡Y| 13 Vreath‡Y| 14 Tractor‡Y| 15 Tractor‡Y|
//    | 16         | 17         | 18 Lockon‡X | 19 Lockon‡X | 20 Vreath‡X| 21 Vreath‡X| 22 Tractor‡X| 23 Tractor‡X|
//    | 24         | 25         | 26 Lockon‡W | 27 Lockon‡W | 28 Vreath‡W| 29 Vreath‡W| 30 Tractor‡W| 31 Tractor‡W|
//    | 32         | 33         | 34 Lockon‡V | 35 Lockon‡V | 36 Vreath‡V| 37 Vreath‡V| 38 Tractor‡V| 39 Tractor‡V|
//    | 40 Option‡]| 41 Option‡]| 42 Lockon‡U | 43 Lockon‡U | 44 Vreath‡U| 45 Vreath‡U| 46 Tractor‡U| 47 Tractor‡U|
//    | 48 Option‡\| 49 Option‡\| 50 Lockon‡T | 51 Lockon‡T | 52 Vreath‡T| 53 Vreath‡T| 54 Tractor‡T| 55 Tractor‡T|
//    | 56 Option‡[| 57 Option‡[| 58 Empty    | 59 Empty    | 60 Empt  y | 61 Empty   | 62 Empty    | 63 Empty    |
//    | 64 Option‡Z| 65 Option‡Z| 66 Torpedo‡Z| 67 Torpedo‡Z| 68 Laser‡Z | 69 Laser‡Z | 70 Speed‡Z  | 71 Speed‡Z  |
//    | 72 Option‡Y| 73 Option‡Y| 74 Torpedo‡Y| 75 Torpedo‡Y| 76 Laser‡Y | 77 Laser‡Y | 78 Speed‡Y  | 79 Speed‡Y  |
//    | 80 Option‡X| 81 Option‡X| 82 Torpedo‡X| 83 Torpedo‡X| 84 Laser‡X | 85 Laser‡X | 86 Speed‡X  | 87 Speed‡X  |
//    | 88 Option‡W| 89 Option‡W| 90 Torpedo‡W| 91 Torpedo‡W| 92 Laser‡W | 93 Laser‡W | 94 Speed‡W  | 95 Speed‡W  |
//    | 96 Option‡V| 97 Option‡V| 98 Torpedo‡V| 99 Torpedo‡V|100 Laser‡V |101 Laser‡V |102 Speed‡V  |103 Speed‡V  |
//    |104 Option‡U|105 Option‡U|106 Torpedo‡U|107 Torpedo‡U|108 Laser‡U |109 Laser‡U |110 Speed‡U  |111 Speed‡U  |
//    |112 Option‡T|113 Option‡T|114 Torpedo‡T|115 Torpedo‡T|116 Laser‡T |117 Laser‡T |118 Speed‡T  |119 Speed‡T  |
//    |120 Empty   |121 Empty   |122 Empty    |123 Empty    |124 Empty   |125 Empty   |126 Empty    |127 Empty    |

    lvinfo_[9].pno_ =  48;
    lvinfo_[8].pno_ =  56;
    lvinfo_[7].pno_ =  64;
    lvinfo_[6].pno_ =  72;
    lvinfo_[5].pno_ =  80;
    lvinfo_[4].pno_ =  88;
    lvinfo_[3].pno_ =  96;
    lvinfo_[2].pno_ = 104;
    lvinfo_[1].pno_ = 112;
    lvinfo_[0].pno_ = 120;

    papEffect_ = NEW GgafDxDrawableActor*[max_level_];
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i] = NEW EffectMagic001("EF");
        papEffect_[i]->inactivateImmed();
        addSubGroup(papEffect_[i]);
    }
}
void OptionMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    angle* paAng_way = NEW angle[prm_new_level-prm_now_level];
    UTIL::getRadialAngle2D(0, prm_new_level-prm_now_level, paAng_way);
    int n = 0;
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i]->inactivateImmed();
    }
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        papEffect_[lv-1]->locateWith(P_MYSHIP);
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

void OptionMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
    if (prm_result_invoke == MAGIC_INVOKE_NG_MP_IS_SHORT) {
        //‰r¥‚µ‚½‚¯‚ÇAMP‚ª‘«‚è‚È‚©‚Á‚½
        for (int i = 0; i < max_level_; i++) {
            papEffect_[i]->inactivateImmed();
        }
    }
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

void OptionMagic::processInvokingBehavior(int prm_now_level, int prm_new_level)  {
}

void OptionMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
}
int OptionMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //ƒIƒvƒVƒ‡ƒ“—LŒø‚É‚·‚éB
    //(processEffectBegin A option ‚Íˆê“x‚Íbehave()‚³‚ê‚ÄÀ•W‚ğŒvZ‚µ‚Ä‚¨‚¢‚Ä‚Ù‚µ‚¢j
    MyOptionController::setNumOption(prm_level);
    MyOptionController::adjustDefaltAngPosition(60);
    return r;
}

void OptionMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    //ƒŒƒxƒ‹ƒAƒbƒvAƒGƒtƒFƒNƒg‚Ìˆ—
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrlr_[lv-1];
        papEffect_[lv-1]->inactivateDelay(120); //”ñŠˆ“®‚Ì•ÛŒ¯
        papEffect_[lv-1]->_pKurokoB->_gravitation_mv_seq_pActor_target = p->pOption_;
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    r_effect_ -= 0.01f;
    //ƒŒƒxƒ‹ƒAƒbƒvAƒGƒtƒFƒNƒg‚Ìˆ—
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrlr_[lv-1];
        papEffect_[lv-1]->setAlpha(r_effect_);
//        papEffect_[lv-1]->setScaleR(3.0f+(1.0f-r_effect_)*4.0);
        papEffect_[lv-1]->locateWith(p->pOption_);
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
