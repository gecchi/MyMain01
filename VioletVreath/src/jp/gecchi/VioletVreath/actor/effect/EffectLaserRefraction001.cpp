#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", nullptr) {
    _class_name = "EffectLaserRefraction001";
    effectBlendOne(); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void EffectLaserRefraction001::initialize() {
//    _pUvFlipper->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectLaserRefraction001::onActive() {
    //_pUvFlipper->setActivePtnToTop();
    //_pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //�p���p���A�j������
    setAlpha(0.5);
    _pScaler->setScale(R_SC(6));
    _pKurokoA->setFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
}

void EffectLaserRefraction001::processBehavior() {
    _pScaler->addScale(100);

    //_pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectLaserRefraction001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
}
