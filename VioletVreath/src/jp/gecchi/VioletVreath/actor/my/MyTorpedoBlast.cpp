#include "stdafx.h"
#include "MyTorpedoBlast.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyTorpedoBlast::MyTorpedoBlast(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "MyTorpedoBlast",STATUS(MyTorpedoBlast)) {
    _class_name = "MyTorpedoBlast";
    effectBlendOne(); //���Z��������Technique�w��
    setAlpha(0.3);
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void MyTorpedoBlast::initialize() {
    _pColliChecker->makeCollision(1);
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(6), D_ANG(0));
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    _pStatus->reset();
    _pColliChecker->setColliSphere(0, PX_C(10));
    _pKurokoA->setMvVelo(0);
    _pScaler->setScale(R_SC(1));
    _pScaler->forceRange(R_SC(1), R_SC(400));
}

void MyTorpedoBlast::onActive() {
    _pScaler->beat(120, 120/2, 0, 1); //1��c���ł��ڂ�
}

void MyTorpedoBlast::processBehavior() {
    if (_pScaler->_method[AXIS_X] == NOSCALE) {
        sayonara();//�c���ł��ڂނ��I����
    } else {
        _pColliChecker->setColliSphere(0, _pScaler->_scale[AXIS_X]); //�����蔻����ω�
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
    int sta = UTIL::calcMyStamina(this, pOther);
}

MyTorpedoBlast::~MyTorpedoBlast() {
}
