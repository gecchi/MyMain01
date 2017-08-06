#include "EffectWormhole.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole::EffectWormhole(const char* prm_name, const char* prm_model_id) :
        DefaultMorphMeshActor(prm_name, prm_model_id, nullptr) {
    _class_name = "EffectWormhole";
    pScaler_ = NEW GgafDxScaler(this);
    inactivate();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectWormhole::initialize() {
}

void EffectWormhole::onActive() {
    setAlpha(0.01);
    pScaler_->setRange(30000, 1000); //�X�P�[�����O�E�͈�
    setScale(30000);
    pScaler_->transitionLinearUntil(1000, 30);//�X�P�[�����O�E60F��₵��1000�ɏk��
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectWormhole::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (!pScaler_->isTransitioning()) {
        //�k��������ABeat
        pScaler_->setRange(1000, 2000);
        pScaler_->beat(30, 2, 0, 26, -1); //�������[�v
    }
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectWormhole::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectWormhole::onInactive() {
}

EffectWormhole::~EffectWormhole() {
    GGAF_DELETE(pScaler_);
}
