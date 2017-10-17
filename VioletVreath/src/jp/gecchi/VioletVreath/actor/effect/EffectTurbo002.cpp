#include "EffectTurbo002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo002::EffectTurbo002(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo002", nullptr) {
    _class_name = "EffectTurbo002";
    inactivate();
    effectBlendOne(); //���Z����
    setHitAble(false); //�����蔻�薳��
}

void EffectTurbo002::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 0);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 2); //�A�j������
}

void EffectTurbo002::onActive() {
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.4);
    getScaler()->setRange(100000, 1000); //�X�P�[�����O�E�͈�
    setScale(1000);
    getScaler()->transitionLinearUntil(100000, 60);//�X�P�[�����O�E60F��₵��1000�ɏk��
    setRyFaceAng(D90ANG);
    getKuroko()->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectTurbo002::processBehavior() {
    addAlpha(-(1.0/60.0));
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectTurbo002::processJudgement() {
    if (!getScaler()->isTransitioning()) {
        inactivate();
    }
}

void EffectTurbo002::onInactive() {
}

EffectTurbo002::~EffectTurbo002() {
}
