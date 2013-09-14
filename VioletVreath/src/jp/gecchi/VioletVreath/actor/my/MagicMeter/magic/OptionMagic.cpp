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
            9,               //max_level
            10000   , 0.9,   //基本魔法コスト , 飛びレベル時の rate
            60*2    , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60*0.8  , 0.9,   //基本発動時間   , 飛びレベル時の rate
            60*60*3 , 1.0,   //基本持続時間   , ＋１レベル毎の持続時間の乗率
            0.0     , 0.0    //基本維持コスト , ＋１レベル毎の維持コストの乗率
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

    papEffect_ = NEW GgafDxDrawableActor*[max_level_];
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i] = NEW EffectOptionMagic001("EF");
        papEffect_[i]->inactivateImmed();
        addSubGroup(papEffect_[i]);
    }
    r_effect_ = 1.0;
}
void OptionMagic::processCastBegin(int prm_now_level, int prm_new_level) {
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
    velo rvelo = PX_C(10);
    for (int lv = prm_now_level+1, n = 0; lv <= prm_new_level; lv++, n++) {
        pEffect = papEffect_[lv-1];
        pEffect->_pKurokoB->resetMv();
        pEffect->_pKurokoB->setVxyzMvVelo(-rvelo, ANG_SIN(paAng_way[n])*rvelo, ANG_COS(paAng_way[n])*rvelo);
        pEffect->_pKurokoB->execGravitationMvSequenceTwd(pMyShip,
                                                         rvelo, 200, 1);
        pEffect->setAlpha(0.9);
        pEffect->setScaleR(2.0f);
        pEffect->activate();
    }

    GGAF_DELETEARR(paAng_way);
    r_effect_ = 1.0;
}

void OptionMagic::processCastingBehavior(int prm_now_level, int prm_new_level){
    r_effect_ += 0.02;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        papEffect_[lv-1]->setScaleR(r_effect_);
    }
}

void OptionMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
    if (prm_result_invoke == MAGIC_INVOKE_NG_MP_IS_SHORT) {
        //詠唱したけど、MPが足りなかった
        for (int i = 0; i < max_level_; i++) {
            papEffect_[i]->inactivateImmed();
        }
    }
}

void OptionMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    r_effect_ = 1;
    for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
        papEffect_[lv-1]->_pKurokoB->execGravitationMvSequenceTwd(
                                         p->_X + p->pOption_->Xorg_,
                                         p->_Y + p->pOption_->Yorg_,
                                         p->_Z + p->pOption_->Zorg_,
                                         20000, 300, 50000
                                     );
    }
}

void OptionMagic::processInvokingBehavior(int prm_now_level, int prm_new_level)  {
}

void OptionMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
}

int OptionMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    //オプション有効にする。
    //(processEffectBegin 時、 option は一度はbehave()されて座標を計算しておいてほしい）
    MyOptionController::setNumOption(prm_level);
    MyOptionController::adjustDefaltAngPosition(60);
    return r;
}

void OptionMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    //レベルアップ時、エフェクトの処理
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
        papEffect_[lv-1]->inactivateDelay(120); //非活動の保険
        papEffect_[lv-1]->_pKurokoB->_gravitation_mv_seq_pActor_target = p->pOption_;
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    r_effect_ -= 0.01f;
    //レベルアップ時、エフェクトの処理
    for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
        MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
        papEffect_[lv-1]->setAlpha(r_effect_);
//        papEffect_[lv-1]->setScaleR(3.0f+(1.0f-r_effect_)*4.0);
        papEffect_[lv-1]->positionAs(p->pOption_);
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
    GGAF_DELETEARR(papEffect_);
}
