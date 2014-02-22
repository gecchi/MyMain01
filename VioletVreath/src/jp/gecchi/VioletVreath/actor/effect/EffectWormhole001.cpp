#include "stdafx.h"
#include "EffectWormhole001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole001::EffectWormhole001(const char* prm_name) :
        EffectWormhole(prm_name, "8/EffectWormhole001") {
    _class_name = "EffectWormhole001";
    inactivate();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectWormhole001::initialize() {
}

void EffectWormhole001::onActive() {
    setAlpha(0.01);
    pScaler_->forceRange(30000, 1000); //�X�P�[�����O�E�͈�
    setScale(30000);
    pScaler_->transitionLinerUntil(1000, 30);//�X�P�[�����O�E60F��₵��1000�ɏk��
    _pKuroko->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectWormhole001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (pScaler_->_method[0] == NOSCALE) {
        //�k��������ABeat
        pScaler_->forceRange(1000, 2000);
        pScaler_->beat(30, 2, 0, 26, -1); //�������[�v
    }
    _pKuroko->behave();
    pScaler_->behave();
}

void EffectWormhole001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectWormhole001::onInactive() {
}

EffectWormhole001::~EffectWormhole001() {
}
