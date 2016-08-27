#include "EffectExplosion003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion003::EffectExplosion003(const char* prm_name) :
        DefaultPointSpriteSetActor(prm_name, "EffectExplosion003", nullptr) {
    _class_name = "EffectExplosion003";
    pScaler_ = NEW GgafDxScaler(this);
    setHitAble(false);
}

int EffectExplosion003::isOutOfView() {
    //‰æ–ÊŠO”»’è–³‚µ
    return 0;
}

void EffectExplosion003::initialize() {

}

void EffectExplosion003::onActive() {
    setScale(0);
    pScaler_->transitionAcceUntilVelo(R_SC(0.01) , R_SC(0.1), -R_SC(0.001));
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
    setRzRyFaceAng(getKuroko()->getRzMvAng(), getKuroko()->getRyMvAng());
}

void EffectExplosion003::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectExplosion003::processJudgement() {
    if (!pScaler_->isTransitioning()) {
        sayonara();
    }
}

EffectExplosion003::~EffectExplosion003() {
    GGAF_DELETE(pScaler_);
}
