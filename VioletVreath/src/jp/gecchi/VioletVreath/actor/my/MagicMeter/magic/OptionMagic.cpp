#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

OptionMagic::OptionMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            9,               //max_level
            10000   , 0.9,   //��{���@�R�X�g , ��у��x������ rate
            60*2    , 0.9,   //��{�r������   , ��у��x������ rate
            60*0.8  , 0.9,   //��{��������   , ��у��x������ rate
            60*60*3 , 1.0,   //��{��������   , �{�P���x�����̎������Ԃ̏旦
            0.0     , 0.0    //��{�ێ��R�X�g , �{�P���x�����̈ێ��R�X�g�̏旦
           ) {

    //���l�̈Ӗ��� VreathMagic.cpp �̃R�����g�Q��
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
    GgafDxDrawableActor* pEffect;
    for (int lv = prm_now_level+1, n = 0; lv <= prm_new_level; lv++, n++) {
        pEffect = papEffect_[lv-1];
        pEffect->locateWith(P_MYSHIP);
        pEffect->_pKurokoA->setRzRyMvAng(paAng_way[n], D90ANG);
        pEffect->_pKurokoA->setMvVelo(2000);
        pEffect->_pKurokoA->setMvAcce(-5);
        pEffect->setAlpha(0.9);
        pEffect->setScaleR(2.0f);
        pEffect->activate();
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
        //�r���������ǁAMP������Ȃ�����
        for (int i = 0; i < max_level_; i++) {
            papEffect_[i]->inactivateImmed();
        }
    }
}

void OptionMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    r_effect_ = 1;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
        papEffect_[lv-1]->_pKurokoA->setMvVelo(0);
        papEffect_[lv-1]->_pKurokoA->setMvAcce(0);
        papEffect_[lv-1]->_pKurokoB->execGravitationMvSequenceTwd(
                                         p->_X + p->pOption_->Xorg_,
                                         p->_Y + p->pOption_->Yorg_,
                                         p->_Z + p->pOption_->Zorg_,
                                         20000, 1000, 50000
                                     );
    }
}

void OptionMagic::processInvokingBehavior(int prm_now_level, int prm_new_level)  {
}

void OptionMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
}

int OptionMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //�I�v�V�����L���ɂ���B
    //(processEffectBegin ���A option �͈�x��behave()����č��W���v�Z���Ă����Ăق����j
    MyOptionController::setNumOption(prm_level);
    MyOptionController::adjustDefaltAngPosition(60);
    return r;
}

void OptionMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    //���x���A�b�v���A�G�t�F�N�g�̏���
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
        papEffect_[lv-1]->inactivateDelay(120); //�񊈓��̕ی�
        papEffect_[lv-1]->_pKurokoB->_gravitation_mv_seq_pActor_target = p->pOption_;
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    r_effect_ -= 0.01f;
    //���x���A�b�v���A�G�t�F�N�g�̏���
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
        papEffect_[lv-1]->setAlpha(r_effect_);
//        papEffect_[lv-1]->setScaleR(3.0f+(1.0f-r_effect_)*4.0);
        papEffect_[lv-1]->locateWith(p->pOption_);
        p->pOption_->setAlpha(1.0f-r_effect_);
    }
    if (r_effect_ < 0) {
        for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
            MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
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
