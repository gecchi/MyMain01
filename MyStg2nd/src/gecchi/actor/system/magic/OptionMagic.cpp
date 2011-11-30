#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

OptionMagic::OptionMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            8,          //max_level
            1000    , 0.9,   //��{���@�R�X�g , ��у��x������ rate
            60*2    , 0.9,   //��{�r������   , ��у��x������ rate
            60*0.2  , 0.9,   //��{��������   , ��у��x������ rate
            60*60*10, 0.0,   //��{��������   , �e���x���̍팸����
            0.0     , 0.0    //��{�ێ��R�X�g , �e���x������ rate
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
        _papEffect[i]->inactivateImmediately();
        addSubGroup(_papEffect[i]);
    }
}
void OptionMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    angle* paAngWay = NEW angle[prm_new_level-prm_now_level];
    GgafDxUtil::getRadialAngle2D(0, prm_new_level-prm_now_level, paAngWay);
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        _papEffect[lv-1]->locateAs(P_MYSHIP);
        _papEffect[lv-1]->_pKurokoA->setRzRyMvAng(paAngWay[lv-1], D90ANG);
        _papEffect[lv-1]->_pKurokoA->setMvVelo(2000);
        _papEffect[lv-1]->_pKurokoA->setMvAcce(-10);
        _papEffect[lv-1]->setAlpha(0.9);
        _papEffect[lv-1]->setScaleRate(2.0f);
        _papEffect[lv-1]->activate();
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
    _r_effect = 1;

}

void OptionMagic::processCastingBehavior(int prm_now_level, int prm_new_level){
    _r_effect += 0.02;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        _papEffect[lv-1]->setScaleRate(_r_effect);
    }
}

void OptionMagic::processCastFinish(int prm_now_level, int prm_new_level) {
    invoke(prm_new_level);
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
//
//        _papEffect[i]->_pKurokoA->setMvVelo(1000);
//        _papEffect[i]->_pKurokoA->setMvAcce(100);
//        _papEffect[i]->_pKurokoA->execTurnMvAngSequence(P_MYOPTIONCON->_X + P_MYOPTIONCON->_papMyOption[i]->_Xorg,
//                                                           P_MYOPTIONCON->_Y + P_MYOPTIONCON->_papMyOption[i]->_Yorg,
//                                                           P_MYOPTIONCON->_Z + P_MYOPTIONCON->_papMyOption[i]->_Zorg,
//                                                           3000,
//                                                           0,TURN_CLOSE_TO,true);
//
//
//
//        _papEffect[i]->_pKurokoA->forceMvVeloRange(P_MYOPTIONCON->_papMyOption[i]->_veloMv*5.0);
////                                SmoothMvVeloSequence2(2000, 0, _time_of_casting, true);
    }

}

void OptionMagic::processInvokeingBehavior(int prm_now_level, int prm_new_level)  {
//    if ((_time_of_invoking - _left_time_to_expire) < (D180ANG/3000)) {
//        return;
//    }
//    int targetX,targetY,targetZ;
//    int ok = 0;
//    for (int i = _old_level; i < _new_level; i++) {
//        targetX = P_MYOPTIONCON->_X + P_MYOPTIONCON->_papMyOption[i]->_Xorg;
//        targetY = P_MYOPTIONCON->_Y + P_MYOPTIONCON->_papMyOption[i]->_Yorg;
//        targetZ = P_MYOPTIONCON->_Z + P_MYOPTIONCON->_papMyOption[i]->_Zorg;
//        if (GgafUtil::abs(_papEffect[i]->_X - targetX) + GgafUtil::abs(_papEffect[i]->_Y - targetY) + GgafUtil::abs(_papEffect[i]->_Z - targetZ)/3  < GgafUtil::abs(P_MYOPTIONCON->_papMyOption[i]->_veloMv)*5) {
//            ok++;
//            _papEffect[i]->_pKurokoA->setMvVelo(500);
//        }
//        _papEffect[i]->_pKurokoA->execTurnMvAngSequence(targetX,
//                                                           targetY,
//                                                           targetZ,
//                                                           40000,
//                                                           0,TURN_CLOSE_TO,true);
//    }
//    if (ok == (_new_level - _old_level)) {
//        effect();
//    }
}

void OptionMagic::processInvokeFinish(int prm_now_level, int prm_new_level) {
    effect(prm_new_level);
}

void OptionMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    //�I�v�V�����L���ɂ���B
    //(processEffectBegin ���A option �͈�x��behave()����č��W���v�Z���Ă����Ăق����j
    P_MYOPTIONCON->setNumOption(prm_now_level);
    P_MYOPTIONCON->adjustDefaltAngPosition(60);
    //���x���A�b�v���A�G�t�F�N�g�̏���
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        _papEffect[lv-1]->inactivateDelay(120); //�񊈓��̕ی�
        _papEffect[lv-1]->_pKurokoB->_gravitation_mv_seq_pActor_target = P_MYOPTIONCON->_papMyOption[lv-1];
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    _r_effect -= 0.01f;
    //���x���A�b�v���A�G�t�F�N�g�̏���
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        _papEffect[lv-1]->setAlpha(_r_effect);
//        _papEffect[lv-1]->setScaleRate(3.0f+(1.0f-_r_effect)*4.0);
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
//void OptionMagic::processOnLevelDown(int prm_last_high_level, int prm_new_low_level) {
//    //���x���_�E�����A
//    P_MYOPTIONCON->setNumOption(prm_new_low_level);
//    P_MYOPTIONCON->adjustDefaltAngPosition(60);
//}

OptionMagic::~OptionMagic() {
    DELETEARR_IMPOSSIBLE_NULL(_papEffect);

}
