#include "EffectExplosion004.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion004::EffectExplosion004(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion004", nullptr) {
    _class_name = "EffectExplosion004";
    //���Z����Technique�w��
    effectBlendOne();
    //���[���h�ϊ��s��̓r���{�[�h�w��
    defineRotMvWorldMatrix_Billboard();
}

void EffectExplosion004::initialize() {
    getScaler()->setRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion004::onActive() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    setScale(500);
    getScaler()->transitionLinearUntil(2000, 64);
    setAlpha(0.99);
}

void EffectExplosion004::processBehavior() {
    _alpha -= 0.01;
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectExplosion004::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

EffectExplosion004::~EffectExplosion004() {
}
