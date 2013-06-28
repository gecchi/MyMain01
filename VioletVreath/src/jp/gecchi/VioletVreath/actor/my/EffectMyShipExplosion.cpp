#include "stdafx.h"
#include "EffectMyShipExplosion.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectMyShipExplosion::EffectMyShipExplosion(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion001", nullptr) {
    _class_name = "EffectMyShipExplosion";
    effectBlendOne(); //‰ÁŽZ‡¬
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv);
}

void EffectMyShipExplosion::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 15);
    setHitAble(false);
}

void EffectMyShipExplosion::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pUvFlipper->exec(FLIP_ORDER_NOLOOP, 20);
    positionAs(P_MYSHIP);
    _alpha = 0.99;
    _pScaler->setScale(8000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectMyShipExplosion::processBehavior() {
    _alpha -= 0.01;
    positionAs(P_MYSHIP);
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectMyShipExplosion::processJudgement() {
    if (_pUvFlipper->_uvflip_method == NOT_ANIMATED) {
        inactivate();
    }
}

EffectMyShipExplosion::~EffectMyShipExplosion() {
}
