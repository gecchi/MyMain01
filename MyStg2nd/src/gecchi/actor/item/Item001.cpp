#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Item001::Item001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "Item001") {
    _class_name = "Item001";
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setAlpha(0.9);
}

void Item001::initialize() {
//    _pUvFlipper->forcePtnNoRange(0, 63);
    setHitAble(false);

}

void Item001::onActive() {
    _pMover->setFaceAngVelo(AXIS_X, 3*1000);
    _pMover->setFaceAngVelo(AXIS_Y, 5*1000);
    _pMover->setFaceAngVelo(AXIS_Z, 7*1000);
}

void Item001::processBehavior() {
    _pMover->behave();
}

void Item001::processJudgement() {
//    if (_fAlpha < 0) {
//        sayonara();
//    }
}

void Item001::onInactive() {
}

Item001::~Item001() {
}
