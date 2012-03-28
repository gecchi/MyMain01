#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectMagic001::EffectMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectMagic001", NULL) {
    _class_name = "EffectMagic001";
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setAlpha(0.9);
}

void EffectMagic001::initialize() {
//    _pUvFlipper->forcePtnRange(0, 63);
    setHitAble(false);

}

void EffectMagic001::onActive() {
    _pKurokoA->setFaceAngVelo(AXIS_X, P2C(3));
    _pKurokoA->setFaceAngVelo(AXIS_Y, P2C(5));
    _pKurokoA->setFaceAngVelo(AXIS_Z, P2C(7));
}

void EffectMagic001::processBehavior() {
    _pKurokoA->behave();
    _pKurokoB->behave();
}

void EffectMagic001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectMagic001::onInactive() {
}

EffectMagic001::~EffectMagic001() {
}
