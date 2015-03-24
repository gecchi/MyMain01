#include "OptionMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectOptionMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

OptionMagic::OptionMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            9,                    //max_level
            10000   , 1.15, 0.95, //基本魔法コスト, ＋１レベル毎のコスト増加率  , 飛びレベル時のコスト削減率
            60*2    , 1.12, 0.95, //基本詠唱時間  , ＋１レベル毎の詠唱時間増加率, 飛びレベル時の詠唱時間削減率
            60*0.8  , 1.1 , 0.95, //基本発動時間  , ＋１レベル毎の発動時間増加率, 飛びレベル時の発動時間削減率
            60*60*3 , 0.9,        //基本持続時間  , ＋１レベル毎の持続時間の乗率
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

    papEffect_ = NEW EffectOptionMagic001*[max_level_];
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i] = NEW EffectOptionMagic001("EF");
        papEffect_[i]->inactivate();
        addSubGroup(papEffect_[i]);
    }
}

void OptionMagic::onReset() {
    Magic::onReset();
    turnoffOptionEffect();
    MyOptionController::setNumOption(0);
}

void OptionMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::processCastBegin("<<prm_now_level<<","<<prm_new_level<<")");
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
        EffectOptionMagic001* pEffect;
        for (int lv = prm_now_level+1, n = 0; lv <= prm_new_level; lv++, n++) {
            pEffect = papEffect_[lv-1];
            pEffect->positionAs(pCore);
            pEffect->pAxsMver_->resetMv();
            pEffect->pAxsMver_->setVxyzMvVelo(veloVxMv*0.8,
                                              veloVyMv + (ANG_SIN(paAng_way[n]) * PX_C(3)),
                                              veloVzMv + (ANG_COS(paAng_way[n]) * PX_C(3)) ); //放射状にエフェクト放出
            pEffect->pAxsMver_->execGravitationMvSequenceTwd(P_MYSHIP, 10000, 200, 2000);
            pEffect->setAlpha(0.9);
            pEffect->setScaleR(1.0f);
            _TRACE_(getBehaveingFrame()<<":OptionMagic::processCastBegin("<<prm_now_level<<","<<prm_new_level<<") papEffect_["<<(lv-1)<<"]->activate();");
            pEffect->activate();
        }
        pMyShip->pMyMagicEnergyCore_->execOptionMagic();
        GGAF_DELETEARR(paAng_way);
    } else if (prm_new_level < prm_now_level) {
        //レベルダウン
        turnoffOptionEffect();
    }
}

void OptionMagic::processCastingBehavior(int prm_now_level, int prm_new_level){
    if (prm_new_level > prm_now_level) {
        frame t = getProgress()->getFrame();
        float s = 10.0f * (1.0f * t / time_of_next_state_);
        if (s < 1.0f) {
            s = 1.0f;
        }
        for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
            papEffect_[lv-1]->setScaleR(s);
        }
    }
}

void OptionMagic::processCastingCancel(int prm_now_level) {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::processCastingCancel("<<prm_now_level<<")");
    turnoffOptionEffect();
}

void OptionMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::processCastFinish("<<prm_now_level<<","<<prm_new_level<<","<<prm_result_invoke<<")");
}

void OptionMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::processInvokeBegin("<<prm_now_level<<","<<prm_new_level<<")");
    if (prm_new_level > prm_now_level) {
        //レベルアップ時
        for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
            MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
            papEffect_[lv-1]->pAxsMver_->execGravitationMvSequenceTwd(
                                             p->_x + p->pOption_->x_org_,
                                             p->_y + p->pOption_->y_org_,
                                             p->_z + p->pOption_->z_org_,
                                             40000, 400, 200000
                                         );
        }
    }
}

void OptionMagic::processInvokingCancel(int prm_now_level) {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::processInvokingCancel("<<prm_now_level<<")");
    turnoffOptionEffect();
}

void OptionMagic::processInvokingBehavior(int prm_now_level, int prm_new_level)  {
    if (prm_new_level > prm_now_level) {
        //レベルアップ時
        for (int lv = prm_now_level+1; lv <= prm_new_level; lv++) {
            MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
            papEffect_[lv-1]->pAxsMver_->setGravitationTwd(p->_x + p->pOption_->x_org_,
                                                           p->_y + p->pOption_->y_org_,
                                                           p->_z + p->pOption_->z_org_ );
        }
    }
}

void OptionMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::processInvokeFinish("<<prm_now_level<<","<<prm_new_level<<","<<prm_result_effect<<")");
}

void OptionMagic::processEffectBegin(int prm_last_level, int prm_now_level)  {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::processEffectBegin("<<prm_last_level<<","<<prm_now_level<<")");

    MyOptionController::setNumOption(prm_now_level);

    if (prm_now_level > prm_last_level) {
        //レベルアップ時、エフェクトの処理
        for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
            MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
            //ダブルプッシュした時と同じ
            p->getKuroko()->turnRzRyMvAngTo(D0ANG, D0ANG,
                                            D_ANG(20), 0,
                                            TURN_CLOSE_TO,
                                            false );
            p->is_free_from_myship_mode_ = false;
            p->is_handle_move_mode_ = false;
            p->return_to_default_position_seq_ = true;
            p->pOption_->return_to_base_radiusPosition_seq_ = true;
            p->pOption_->return_to_base_angExpanse_seq_= true;

            papEffect_[lv-1]->inactivateDelay(120); //非活動の保険
            _TRACE_(getBehaveingFrame()<<":OptionMagic::processEffectBegin("<<prm_last_level<<","<<prm_now_level<<") papEffect_["<<(lv-1)<<"]->inactivateDelay(120);");
            papEffect_[lv-1]->pAxsMver_->stopGravitationMvSequence();
            papEffect_[lv-1]->positionAs(p->pOption_);

            MyOptionController::adjustDefaltAngPosition(180, prm_last_level, prm_now_level-1);
        }
    }
}

void OptionMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    //エフェクトの処理
    frame t = getProgress()->getFrame();
    if (prm_now_level > prm_last_level) {
        if (t < 180) {
            float a = t*(1.0/180);
            for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
                MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
                papEffect_[lv-1]->setAlpha(1.0f - a);
                papEffect_[lv-1]->positionAs(p->pOption_);
                p->pOption_->setAlpha(a);
            }
        }
        if (t == 180) {
            for (int lv = prm_last_level+1; lv <= prm_now_level; lv++) {
                MyOptionController* p = P_MYSHIP_SCENE->papOptionCtrler_[lv-1];
                papEffect_[lv-1]->inactivate();
                _TRACE_(getBehaveingFrame()<<":OptionMagic::processEffectingBehavior("<<prm_last_level<<","<<prm_now_level<<") papEffect_["<<(lv-1)<<"]->inactivate();");
                p->pOption_->setAlpha(1.0);
            }
        }
    } else if (prm_last_level > prm_now_level) { //レベルダウン

    }
}

void OptionMagic::turnoffOptionEffect() {
    _TRACE_(getBehaveingFrame()<<":OptionMagic::turnoffOptionEffect()");
    for (int i = 0; i < max_level_; i++) {
        papEffect_[i]->inactivate();
    }
}

OptionMagic::~OptionMagic() {
    GGAF_DELETEARR(papEffect_);
}
