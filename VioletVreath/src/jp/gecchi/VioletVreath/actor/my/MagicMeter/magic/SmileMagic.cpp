#include "SmileMagic.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelTest.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

SmileMagic::SmileMagic(const char* prm_name, int* prm_pMP)
    : Magic(prm_name, prm_pMP,
            5,               //max_level
            500      , 1.0, 1.0,  //基本魔法コスト, ＋１レベル毎のコスト増加率  , 飛びレベル時のコスト削減率
            SEC_F(1) , 1.0, 0.9,  //基本詠唱時間  , ＋１レベル毎の詠唱時間増加率, 飛びレベル時の詠唱時間削減率
            SEC_F(1) , 1.0, 0.9,  //基本発動時間  , ＋１レベル毎の発動時間増加率, 飛びレベル時の発動時間削減率
            SEC_F(0) , 0.0,       //基本持続時間  , ＋１レベル毎の持続時間の乗率
            0        , 0.0        //基本維持コスト, ＋１レベル毎の維持コストの乗率
        ) {

    //数値の意味は VreathMagic.cpp のコメント参照
    lvinfo_[7].pno_ =  4;
    lvinfo_[6].pno_ = 12;
    lvinfo_[5].pno_ = 20;
    lvinfo_[4].pno_ = 28;
    lvinfo_[3].pno_ = 36;
    lvinfo_[2].pno_ = 44;
    lvinfo_[1].pno_ = 52;
    lvinfo_[0].pno_ = 60;

    pMoji_ = NEW SpriteLabelTest("(^_^)");
    pMoji_->inactivate();
    appendGroupChild(pMoji_);
}

void SmileMagic::onReset() {
    Magic::onReset();
    pMoji_->inactivate();
}

void SmileMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    _TRACE_("SmileMagic::processCastBegin(prm_now_level="<<prm_now_level<<",prm_new_level="<<prm_new_level<<")");
    if (prm_new_level > prm_now_level) {
        pMoji_->setPositionAt(pMYSHIP);
        pMoji_->setCullingDraw(false);
        //ニコニコビーム発射
        std::string s = "";
        for (int i = 0; i < prm_new_level; i++) {
            s += "(^_^)SMILE!\n";
        }
        pMoji_->update(s.c_str());
        pMoji_->setFaceAngZero();
        pMoji_->getLocoVehicle()->setRollPitchYawFaceAngVelo(0,0,0);
        pMoji_->activate();
    }
}
void SmileMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pMoji_->_x += 1000;
        pMoji_->_y += 1000;
        pMoji_->getLocoVehicle()->behave();
    }
}

void SmileMagic::processCastingCancel(int prm_now_level) {
    _TRACE_("SmileMagic::processCastFinish(prm_now_level="<<prm_now_level<<")");
    pMoji_->inactivate();
}

void SmileMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
    _TRACE_("SmileMagic::processCastFinish(prm_now_level="<<prm_now_level<<",prm_new_level="<<prm_new_level<<",r="<<prm_result_invoke<<")");
}

void SmileMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    _TRACE_("SmileMagic::processInvokeBegin(prm_now_level="<<prm_now_level<<",prm_new_level="<<prm_new_level<<")");
    if (prm_new_level > prm_now_level) {
        pMoji_->getLocoVehicle()->setFaceAngVelo(AXIS_Z, 5000);
    }
}

void SmileMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    if (prm_new_level > prm_now_level) {
        pMoji_->getLocoVehicle()->behave();
    }
}

void SmileMagic::processInvokingCancel(int prm_now_level) {
    _TRACE_("SmileMagic::processInvokingCancel(prm_now_level="<<prm_now_level<<")");
    pMoji_->inactivate();
}

void SmileMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    _TRACE_("SmileMagic::processInvokeFinish(prm_now_level="<<prm_now_level<<",prm_new_level="<<prm_new_level<<", r="<<prm_result_effect<<")");
}

void SmileMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    if (prm_now_level > 0) {
        _TRACE_("SmileMagic::processEffectBegin(prm_last_level="<<prm_last_level<<",prm_now_level="<<prm_now_level<<") (^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE(^_^)SMILE");
    }
    if (prm_now_level == 0) {
        _TRACE_("SmileMagic::processEffectBegin(prm_last_level="<<prm_last_level<<",prm_now_level="<<prm_now_level<<") 終了～");
        pMoji_->inactivate();
    }
}

void SmileMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
    if (prm_now_level > 0) {
        _TRACE_(FUNC_NAME<<" １回だけのはず");
    }
}

SmileMagic::~SmileMagic() {
}
