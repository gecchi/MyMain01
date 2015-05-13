#include "EffectBunshinMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectBunshinMagic001::EffectBunshinMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectBunshinMagic001", nullptr) {
    _class_name = "EffectBunshinMagic001";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    effectBlendOne(); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void EffectBunshinMagic001::initialize() {
    setAlpha(0.9);
//    getUvFlipper()->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectBunshinMagic001::onActive() {
    getKuroko()->setRollPitchYawFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectBunshinMagic001::processBehavior() {
    getKuroko()->behave();
    pAxsMver_->behave();
}

void EffectBunshinMagic001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectBunshinMagic001::onInactive() {
}

EffectBunshinMagic001::~EffectBunshinMagic001() {
    GGAF_DELETE(pAxsMver_);
}
