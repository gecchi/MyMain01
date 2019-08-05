#include "BunshinMagic.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/Kago.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectBunshinMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinBase.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

BunshinMagic::BunshinMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            10,                   //max_level
            10000   , 1.15, 0.95, //��{���@�R�X�g, �{�P���x�����̃R�X�g������  , ��у��x�����̃R�X�g�팸��
            60      , 1.12, 0.95, //��{�r������  , �{�P���x�����̉r�����ԑ�����, ��у��x�����̉r�����ԍ팸��
            30      , 1.1 , 0.95, //��{��������  , �{�P���x�����̔������ԑ�����, ��у��x�����̔������ԍ팸��
            60*60*9999 , 0.9,        //��{��������  , �{�P���x�����̎������Ԃ̏旦
            0.0     , 0.0         //��{�ێ��R�X�g, �{�P���x�����̈ێ��R�X�g�̏旦
           ) {

    //���l�̈Ӗ��� VreathMagic.cpp �̃R�����g�Q��
    lvinfo_[10].pno_ =  40;
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

    papEffect_ = NEW EffectBunshinMagic001*[max_level_];
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i] = NEW EffectBunshinMagic001("EF");
        papEffect_[i]->inactivate();
        appendGroupChild(papEffect_[i]);
    }
}

void BunshinMagic::onReset() {
    Magic::onReset();
    turnoffBunshinEffect();
    MyBunshinBase::setBunshinNum(0);
}

void BunshinMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processCastBegin("<<prm_now_level<<","<<prm_new_level<<")");
    if (prm_new_level > prm_now_level) {
        //���x���A�b�v��
        //���ˏ�ɃG�t�F�N�g���o
        MyShip* pMyShip = pMYSHIP;
        MyMagicEnergyCore* pCore = pMyShip->pMyMagicEnergyCore_;
        angle* paAng_way = NEW angle[prm_new_level-prm_now_level];
        UTIL::getRadialAngle2D(0, prm_new_level-prm_now_level, paAng_way);
        GgafDx::Kago* const pCoreKago = pCore->callKago();
        velo veloVxMv = pCoreKago->_velo_vx_mv;
        velo veloVyMv = pCoreKago->_velo_vy_mv;
        velo veloVzMv = pCoreKago->_velo_vz_mv;
        EffectBunshinMagic001* pEffect;
        for (int lv = prm_now_level+1, n = 0; lv <= prm_new_level; lv++, n++) {
            pEffect = papEffect_[lv-1];
            pEffect->setPositionAt(pCore);
            GgafDx::Kago* const pEffectKago = pEffect->callKago();
            pEffectKago->resetMv();
            pEffectKago->setVxyzMvVelo(veloVxMv*0.8,
                                          veloVyMv + (ANG_SIN(paAng_way[n]) * PX_C(3)),
                                          veloVzMv + (ANG_COS(paAng_way[n]) * PX_C(3)) ); //���ˏ�ɃG�t�F�N�g���o
            pEffectKago->execGravitationMvSequenceTwd(pMYSHIP, PX_C(10), PX_C(0.2), PX_C(2));
            _TRACE_(getBehaveingFrame()<<":BunshinMagic::processCastBegin("<<prm_now_level<<","<<prm_new_level<<") papEffect_["<<(lv-1)<<"]->activate();");
            pEffect->activate();
            pEffect->blink(10, MAX_FRAME, 0, nullptr, false);
        }
//        pMyShip->pMyMagicEnergyCore_->execBunshinMagic();
        GGAF_DELETEARR(paAng_way);
    } else if (prm_new_level < prm_now_level) {
        //���x���_�E��
        turnoffBunshinEffect();
    }
}

void BunshinMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
    }
}

void BunshinMagic::processCastingCancel(int prm_now_level) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processCastingCancel("<<prm_now_level<<")");
    turnoffBunshinEffect();
}

void BunshinMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processCastFinish("<<prm_now_level<<","<<prm_new_level<<","<<prm_result_invoke<<")");
}

void BunshinMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processInvokeBegin("<<prm_now_level<<","<<prm_new_level<<")");
    MyBunshinBase::setBunshinNum(prm_new_level); //���g�ݒ�
    if (prm_new_level > prm_now_level) {
        //���x���A�b�v���̓G�t�F�N�g�����g�ֈړ�
        MyBunshinBase** papBunshinBase = pMYSHIP_SCENE->papBunshinBase_;
        for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
            MyBunshin* pMyBunshin = papBunshinBase[lv-1]->pBunshin_;
            pMyBunshin->setAlpha(0); //����s�ɐݒ�
            pMyBunshin->getAlphaFader()->stop();
            papEffect_[lv-1]->callKago()->execGravitationMvSequenceTwd(
                                             pMyBunshin,
                                             PX_C(10)+pMYSHIP->mv_speed_, PX_C(1), PX_C(20)
                                         );
        }
    }
}

void BunshinMagic::processInvokingCancel(int prm_now_level) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processInvokingCancel("<<prm_now_level<<")");
    MyBunshinBase::setBunshinNum(prm_now_level);
    turnoffBunshinEffect();
}

void BunshinMagic::processInvokingBehavior(int prm_now_level, int prm_new_level)  {
    if (prm_new_level > prm_now_level) {
    }
}

void BunshinMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processInvokeFinish("<<prm_now_level<<","<<prm_new_level<<","<<prm_result_effect<<")");
}

void BunshinMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processEffectBegin("<<prm_last_level<<","<<prm_now_level<<")");
    if (prm_now_level > prm_last_level) {
        //���x���A�b�v���A�G�t�F�N�g�̏���
        MyBunshinBase** papBunshinBase = pMYSHIP_SCENE->papBunshinBase_;
        for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
            MyBunshin* pMyBunshin = papBunshinBase[lv-1]->pBunshin_;
            pMyBunshin->getAlphaFader()->transitionLinearUntil(1.0, 120);
            //�����
            papEffect_[lv-1]->callKago()->stopGravitationMvSequence();
            papEffect_[lv-1]->callKago()->resetMv();
            papEffect_[lv-1]->blink2(6, 30, 120, pMyBunshin, false);
        }
    }
}

void BunshinMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    //�G�t�F�N�g�̏���
    if (prm_now_level > prm_last_level) {
    } else if (prm_last_level > prm_now_level) { //���x���_�E��

    }
}

void BunshinMagic::turnoffBunshinEffect() {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::turnoffBunshinEffect()");
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i]->inactivate();
    }
}

BunshinMagic::~BunshinMagic() {
    GGAF_DELETEARR(papEffect_);
}
