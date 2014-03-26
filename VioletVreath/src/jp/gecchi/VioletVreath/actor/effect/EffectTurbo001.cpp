#include "stdafx.h"
#include "EffectTurbo001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo001::EffectTurbo001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo001", nullptr) {
    _class_name = "EffectTurbo001";
    pScaler_ = NEW GgafDxScaler(this);
    inactivate();
    effectBlendOne(); //â¡éZçáê¨
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ÉrÉãÉ{Å[ÉhRzâÒì]
    setHitAble(false); //ìñÇΩÇËîªíËñ≥Çµ
}

void EffectTurbo001::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 15);   //ÉAÉjÉÅîÕàÕÇÇOÅ`ÇPÇT
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1); //ÉAÉjÉÅèáèò
    setAlpha(0.99);
}

void EffectTurbo001::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 3000);        //âÒì]
}

void EffectTurbo001::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectTurbo001::processJudgement() {
    if (VB_PLAY->isBeingPressed(VB_TURBO)) { //É^Å[É{

    } else {
        inactivate();
    }
}

void EffectTurbo001::onInactive() {
}

EffectTurbo001::~EffectTurbo001() {
    GGAF_DELETE(pScaler_);
}
