#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MyTorpedoBlast::MyTorpedoBlast(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "MyTorpedoBlast",STATUS(MyTorpedoBlast)) {
    _class_name = "MyTorpedoBlast";
    changeEffectTechnique("DestBlendOne"); //���Z��������Technique�w��
    setAlpha(0.2);
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void MyTorpedoBlast::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pKurokoA->setFaceAngVelo(AXIS_X, Deg2Ang(27));
    _pKurokoA->setFaceAngVelo(AXIS_Y, Deg2Ang(33));
    _pKurokoA->setFaceAngVelo(AXIS_Z, Deg2Ang(17));
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    _pStatus->reset();
    _pCollisionChecker->setColliSphere(0, Px2Co(10));
    _pKurokoA->setMvVelo(0);
    _pScaler->setScale(R2Sc(1));
    _pScaler->forceScaleRange(R2Sc(1), R2Sc(400));

}

void MyTorpedoBlast::onActive() {
    _pScaler->beat(120, 120/2, 0, 1); //1��c���ł��ڂ�
}

void MyTorpedoBlast::processBehavior() {
    if (_pScaler->_method[AXIS_X] == NOSCALE) {
        sayonara();//�c���ł��ڂނ��I����
    } else {
        _pCollisionChecker->setColliSphere(0, _pScaler->_scale[AXIS_X]); //�����蔻����ω�
        _pKurokoA->behave();
        _pScaler->behave();
    }
}

void MyTorpedoBlast::processJudgement() {
}

void MyTorpedoBlast::onInactive() {
}


void MyTorpedoBlast::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�q�b�g���Ă����ł��܂���
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
}

MyTorpedoBlast::~MyTorpedoBlast() {
}
