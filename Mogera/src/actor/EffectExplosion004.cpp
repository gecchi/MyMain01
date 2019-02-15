#include "EffectExplosion004.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace Mogera;

EffectExplosion004::EffectExplosion004(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion004") {
    _class_name = "EffectExplosion004";
    //���Z����Technique�w��
//    effectBlendOne();
    //���[���h�ϊ��s��̓r���{�[�h�w��
    defineRotMvWorldMatrix_Billboard();
}

void EffectExplosion004::initialize() {
    getScaler()->setRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion004::onActive() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    setScale(500);
    getScaler()->transitionLinearUntil(2000, 64);
    setCullingDraw(false);
    setAlpha(1.0);
}

void EffectExplosion004::processBehavior() {
    _alpha -= 0.01;
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectExplosion004::processJudgement() {
    if (getActiveFrame() > 120) {
        sayonara();
    }
}

EffectExplosion004::~EffectExplosion004() {
}
