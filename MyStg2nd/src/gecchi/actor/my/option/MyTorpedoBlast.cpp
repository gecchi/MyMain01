#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyTorpedoBlast::MyTorpedoBlast(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "donatu_0") {
    _class_name = "MyTorpedoBlast";
    MyStgUtil::resetMyTorpedoBlastStatus(_pStatus);
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setMaterialColor(1.0, 0.3, 0.3);
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(true);  //Z�o�b�t�@�͏������ݗL��
}

void MyTorpedoBlast::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 100);
}

void MyTorpedoBlast::onActive() {
    MyStgUtil::resetMyTorpedoBlastStatus(_pStatus);
    setAlpha(1.0);
    _pMover->setFaceAngVelo(AXIS_X, 1*1000);
    _pMover->setFaceAngVelo(AXIS_Y, 3*1000);
    _pMover->setFaceAngVelo(AXIS_Z, 2*1000);
    _pMover->setMvVelo(0);
    setHitAble(true);
    _pScaler->setScale(100);
    _pScaler->intoTargetScaleAcceStep(99, 30, -1); //�c���ł��ڂ�
}

void MyTorpedoBlast::processBehavior() {
    if (_pScaler->_method[AXIS_X] == NOSCALE) {
        sayonara();//�c���ł��ڂނ��I����
    } else {
        _pCollisionChecker->setColliSphere(0, _pScaler->_scale[AXIS_X]*1000); //�����蔻����ω�
        _pMover->behave();
        _pScaler->behave();
    }
}

void MyTorpedoBlast::processJudgement() {
}

void MyTorpedoBlast::onInactive() {
}


void MyTorpedoBlast::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�q�b�g���Ă����ł��܂���
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
}

MyTorpedoBlast::~MyTorpedoBlast() {
}
