#include "stdafx.h"
#include "OptionMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectOptionMagic001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

OptionMagic::OptionMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            9,                    //max_level
            10000   , 1.15, 0.95, //��{���@�R�X�g, �{�P���x�����̃R�X�g������  , ��у��x�����̃R�X�g�팸��
            60*2    , 1.12, 0.95, //��{�r������  , �{�P���x�����̉r�����ԑ�����, ��у��x�����̉r�����ԍ팸��
            60*0.8  , 1.1 , 0.95, //��{��������  , �{�P���x�����̔������ԑ�����, ��у��x�����̔������ԍ팸��
            60*60*3 , 0.9,        //��{��������  , �{�P���x�����̎������Ԃ̏旦
            0.0     , 0.0         //��{�ێ��R�X�g, �{�P���x�����̈ێ��R�X�g�̏旦
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
        papEffect_[i] = NEW EffectOptionMagic001("EF");
        papEffect_[i]->inactivateImmed();
        addSubGroup(papEffect_[i]);
    }
}
void OptionMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    //���ˏ�ɃG�t�F�N�g���o
    MyShip* pMyShip = P_MYSHIP;
    angle* paAng_way = NEW angle[prm_new_level-prm_now_level];
    UTIL::getRadialAngle2D(0, prm_new_level-prm_now_level, paAng_way);
    for (int i = 0; i < max_level_; i++) {
        if (papEffect_[i]->isActive()) {
            if (i+1 > prm_new_level) {
                papEffect_[i]->inactivateImmed();
                papEffect_[i]->positionAs(pMyShip);
            }
        } else {
            papEffect_[i]->inactivateImmed();
            papEffect_[i]->positionAs(pMyShip);
        }
    }
    GgafDxDrawableActor* pEffect;
    velo rvelo = PX_C(3);
    for (int lv = prm_now_level+1, n = 0; lv <= prm_new_level; lv++, n++) {
        pEffect = papEffect_[lv-1];
        pEffect->_pKurokoB->resetMv();
        pEffect->_pKurokoB->setVxyzMvVelo(-rvelo,
                                          ANG_SIN(paAng_way[n]) * rvelo,
                                          ANG_COS(paAng_way[n]) * rvelo
                                         ); //���ˏ�ɃG�t�F�N�g���o
        pEffect->setAlpha(0.9);
        pEffect->setScaleR(1.0f);
        pEffect->activate();
    }

    GGAF_DELETEARR(paAng_way);
}

void OptionMagic::processCastingBehavior(int prm_now_level, int prm_new_level){

    frame t = _pProg->getFrameInProgress();
    float s = 10.0f * (1.0f * t / time_of_next_state_);
    if (s < 1.0f) {
        s = 1.0f;
    }
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        papEffect_[lv-1]->setScaleR(s);
    }

    if (t == 60) {
       for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
            papEffect_[lv-1]->_pKurokoB->execGravitationMvSequenceTwd(P_MYSHIP, 10000, 200, 2000);
        }
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
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
        p->pOption_->onReset(); //����������Ȃ��ƃI�v�V������(Xorg_,Yorg_,Zorg_)�����f����Ȃ�
        papEffect_[lv-1]->_pKurokoB->execGravitationMvSequenceTwd(
                                         p->_X + p->pOption_->Xorg_,
                                         p->_Y + p->pOption_->Yorg_,
                                         p->_Z + p->pOption_->Zorg_,
                                         40000, 200, 200000
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
        papEffect_[lv-1]->positionAs(p->pOption_);
        papEffect_[lv-1]->_pKurokoB->stopGravitationMvSequence();
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    //���x���A�b�v���A�G�t�F�N�g�̏���
    frame t = _pProg->getFrameInProgress();
    if (t < 120) {
        float a = t*(1.0/120);
        for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
            MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
            papEffect_[lv-1]->setAlpha(1.0f - a);
            papEffect_[lv-1]->positionAs(p->pOption_);
            p->pOption_->setAlpha(a);
        }
    }
    if (t == 120) {
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
    GGAF_DELETEARR(papEffect_);
}
