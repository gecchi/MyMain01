#include "stdafx.h"
#include "EffectOptionMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectOptionMagic001::EffectOptionMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectOptionMagic001", nullptr) {
    _class_name = "EffectOptionMagic001";
    pAxMver_ = NEW GgafDxAxesMover(this);
    effectBlendOne(); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void EffectOptionMagic001::initialize() {
    setAlpha(0.9);
//    _pUvFlipper->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectOptionMagic001::onActive() {
    _pKuroko->setFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectOptionMagic001::processBehavior() {
    _pKuroko->behave();
    pAxMver_->behave();
}

void EffectOptionMagic001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectOptionMagic001::onInactive() {
}

EffectOptionMagic001::~EffectOptionMagic001() {
    GGAF_DELETE(pAxMver_);
}
