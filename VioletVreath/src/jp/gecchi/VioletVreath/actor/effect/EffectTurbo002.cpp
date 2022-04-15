#include "EffectTurbo002.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo002::EffectTurbo002(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo002") {
    _class_name = "EffectTurbo002";
    inactivate();
    effectBlendOne(); //���Z����
    setHitAble(false); //�����蔻�薳��
}

void EffectTurbo002::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
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
    getVecVehicle()->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectTurbo002::processBehavior() {
    addAlpha(-(1.0/60.0));
    getUvFlipper()->behave();
    getVecVehicle()->behave();
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
