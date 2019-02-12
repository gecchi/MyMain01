#include "EffectWormhole.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole::EffectWormhole(const char* prm_name, const char* prm_model_id) :
        DefaultMorphMeshActor(prm_name, prm_model_id, nullptr) {
    _class_name = "EffectWormhole";
    inactivate();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix_Billboard(); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectWormhole::initialize() {
}

void EffectWormhole::onActive() {
    setAlpha(0.01);
    getScaler()->setRange(30000, 1000); //�X�P�[�����O�E�͈�
    setScale(30000);
    getScaler()->transitionLinearUntil(1000, 30);//�X�P�[�����O�E60F��₵��1000�ɏk��
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectWormhole::processBehavior() {
    GgafDx::Scaler* const pScaler = getScaler();

    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (!pScaler->isTransitioning()) {
        //�k��������ABeat
        pScaler->setRange(1000, 2000);
        pScaler->beat(30, 2, 0, 26, -1); //�������[�v
    }
    getKuroko()->behave();
    pScaler->behave();
}

void EffectWormhole::processJudgement() {
}

void EffectWormhole::onInactive() {
}

EffectWormhole::~EffectWormhole() {
}
