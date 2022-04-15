#include "EffectWormhole001.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole001::EffectWormhole001(const char* prm_name) :
        EffectWormhole(prm_name, "EffectWormhole001_8") {
    _class_name = "EffectWormhole001";
    inactivate();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix_Billboard(); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectWormhole001::initialize() {
}

void EffectWormhole001::onActive() {
    setAlpha(0.01);
    getScaler()->setRange(30000, 1000); //�X�P�[�����O�E�͈�
    setScale(30000);
    getScaler()->transitionLinearUntil(1000, 30);//�X�P�[�����O�E60F��₵��1000�ɏk��
    getVecVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectWormhole001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }
    GgafDx::Scaler* pScaler = getScaler();
    if (!pScaler->isTransitioning()) {
        //�k��������ABeat
        pScaler->setRange(1000, 2000);
        pScaler->beat(30, 2, 0, 26, -1); //�������[�v
    }
    getVecVehicle()->behave();
    pScaler->behave();
}

void EffectWormhole001::processJudgement() {
}

void EffectWormhole001::onInactive() {
}

EffectWormhole001::~EffectWormhole001() {
}
