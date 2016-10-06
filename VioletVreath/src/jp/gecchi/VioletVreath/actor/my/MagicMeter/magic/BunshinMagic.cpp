#include "BunshinMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectBunshinMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinBase.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

BunshinMagic::BunshinMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            9,                    //max_level
            10000   , 1.15, 0.95, //基本魔法コスト, ＋１レベル毎のコスト増加率  , 飛びレベル時のコスト削減率
            60      , 1.12, 0.95, //基本詠唱時間  , ＋１レベル毎の詠唱時間増加率, 飛びレベル時の詠唱時間削減率
            30      , 1.1 , 0.95, //基本発動時間  , ＋１レベル毎の発動時間増加率, 飛びレベル時の発動時間削減率
            60*60*9999 , 0.9,        //基本持続時間  , ＋１レベル毎の持続時間の乗率
            0.0     , 0.0         //基本維持コスト, ＋１レベル毎の維持コストの乗率
           ) {

    //数値の意味は VreathMagic.cpp のコメント参照
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
        addSubGroup(papEffect_[i]);
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
        //レベルアップ時
        //放射状にエフェクト放出
        MyShip* pMyShip = P_MYSHIP;
        MyMagicEnergyCore* pCore = pMyShip->pMyMagicEnergyCore_;
        angle* paAng_way = NEW angle[prm_new_level-prm_now_level];
        UTIL::getRadialAngle2D(0, prm_new_level-prm_now_level, paAng_way);
        velo veloVxMv = pCore->pAxsMver_->_velo_vx_mv;
        velo veloVyMv = pCore->pAxsMver_->_velo_vy_mv;
        velo veloVzMv = pCore->pAxsMver_->_velo_vz_mv;
        EffectBunshinMagic001* pEffect;
        for (int lv = prm_now_level+1, n = 0; lv <= prm_new_level; lv++, n++) {
            pEffect = papEffect_[lv-1];
            pEffect->locateAs(pCore);
            pEffect->pAxsMver_->resetMv();
            pEffect->pAxsMver_->setVxyzMvVelo(veloVxMv*0.8,
                                              veloVyMv + (ANG_SIN(paAng_way[n]) * PX_C(3)),
                                              veloVzMv + (ANG_COS(paAng_way[n]) * PX_C(3)) ); //放射状にエフェクト放出
            pEffect->pAxsMver_->execGravitationMvSequenceTwd(P_MYSHIP, 10000, 200, 2000);
            _TRACE_(getBehaveingFrame()<<":BunshinMagic::processCastBegin("<<prm_now_level<<","<<prm_new_level<<") papEffect_["<<(lv-1)<<"]->activate();");
            pEffect->activate();
            pEffect->blink(10, MAX_FRAME, 0, nullptr, false);
        }
//        pMyShip->pMyMagicEnergyCore_->execBunshinMagic();
        GGAF_DELETEARR(paAng_way);
    } else if (prm_new_level < prm_now_level) {
        //レベルダウン
        turnoffBunshinEffect();
    }
}

void BunshinMagic::processCastingBehavior(int prm_now_level, int prm_new_level){
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
    if (prm_new_level > prm_now_level) {
        //レベルアップ時
        for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
            MyBunshinBase* p = P_MYSHIP_SCENE->papBunshinBase_[lv-1];
            papEffect_[lv-1]->pAxsMver_->execGravitationMvSequenceTwd(
                                             P_MYSHIP,
                                             40000, 400, 200000
                                         );
        }
    }
}

void BunshinMagic::processInvokingCancel(int prm_now_level) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processInvokingCancel("<<prm_now_level<<")");
    turnoffBunshinEffect();
}

void BunshinMagic::processInvokingBehavior(int prm_now_level, int prm_new_level)  {
    if (prm_new_level > prm_now_level) {
        //レベルアップ時
        for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
            MyBunshinBase* p = P_MYSHIP_SCENE->papBunshinBase_[lv-1];
            papEffect_[lv-1]->pAxsMver_->setGravitationTwd(P_MYSHIP);
        }
    }
}

void BunshinMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processInvokeFinish("<<prm_now_level<<","<<prm_new_level<<","<<prm_result_effect<<")");
}

void BunshinMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    _TRACE_(getBehaveingFrame()<<":BunshinMagic::processEffectBegin("<<prm_last_level<<","<<prm_now_level<<")");
    MyBunshinBase::setBunshinNum(prm_now_level);
    if (prm_now_level > prm_last_level) {
        //レベルアップ時、エフェクトの処理
        for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
            MyBunshin* pBunshin = P_MYSHIP_SCENE->papBunshinBase_[lv-1]->pBunshin_;
            papEffect_[lv-1]->blink(0, 2, 120, pBunshin, false);
        }
    }
}

void BunshinMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    //エフェクトの処理
    if (prm_now_level > prm_last_level) {
    } else if (prm_last_level > prm_now_level) { //レベルダウン

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
