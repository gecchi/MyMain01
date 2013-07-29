#include "stdafx.h"
#include "LaserMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectLaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionWateringLaserChip001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LaserMagic::LaserMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            3,          //max_level
            1000*4  , 0.9,   //基本魔法コスト , 飛びレベル時の rate
            60*3    , 0.9,   //基本詠唱時間   , 飛びレベル時の rate
            60*2    , 0.9,   //基本発動時間   , 飛びレベル時の rate
            60*60*10, 1.0,   //基本持続時間   , ＋１レベル毎の持続時間の乗率
            0       , 1.0    //基本維持コスト , ＋１レベル毎の維持コストの乗率
           ) {

    //数値の意味は VreathMagic.cpp のコメント参照
    lvinfo_[3].pno_ = 100;
    lvinfo_[2].pno_ = 108;
    lvinfo_[1].pno_ = 116;
    lvinfo_[0].pno_ = 124;

    pEffect_ = NEW EffectLaserMagic("EffectLaserMagic");
    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);
}

void LaserMagic::processCastBegin(int prm_now_level, int prm_new_level) {
    pEffect_->positionAs(P_MYSHIP);
    pEffect_->setAlpha(0.9);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    pEffect_->_pScaler->setScale(1000);
    pEffect_->activate();
}

void LaserMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->positionAs(P_MYSHIP);
    pEffect_->_pScaler->addScale(10);
}

void LaserMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void LaserMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->setScale(1000);
    pEffect_->_pKurokoA->setFaceAngVelo(AXIS_Z, 3000);
}

void LaserMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
    pEffect_->_pScaler->addScale(100);
}

void LaserMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    pEffect_->inactivate();
}

int LaserMagic::effect(int prm_level) {
    int r = Magic::effect(prm_level);
    if (prm_level > 0) {
        P_MYSHIP->can_shoot_laser_ = true;
        MyStraightLaserChip001::chengeTex(prm_level-1);
        MyOptionWateringLaserChip001::chengeTex(prm_level-1);
    } else {
        P_MYSHIP->can_shoot_laser_ = false;
    }

    return r;
}

void LaserMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
}

void LaserMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

void LaserMagic::processEffectFinish(int prm_justbefore_level) {

}


LaserMagic::~LaserMagic() {
}
