#include "stdafx.h"
#include "MyTorpedoBlast.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //���Z��������Technique�w��
    setAlpha(0.3);
    setZEnable(true);        //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
}

void MyTorpedoBlast::initialize() {
    _pColliChecker->makeCollision(1);
    getKuroko()->setFaceAngVelo(D_ANG(0), D_ANG(6), D_ANG(0));
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    //MyTorpedo��reset()�����s�����B
    //MyTorpedoBlast�́AdispatchForce�����̂ŁA
    //onInactive() onActive()�ł̎����������
    _pStatus->reset();
    _pColliChecker->setColliSphere(0, PX_C(10));
    getKuroko()->setMvVelo(0);
    setScale(R_SC(1));
    pScaler_->forceRange(R_SC(1), R_SC(400));
    pScaler_->beat(120, 120/2, 0, 120/2, 1); //1��c���ł��ڂ�
}

void MyTorpedoBlast::processBehavior() {
    if (!pScaler_->isTransitioning()) {
        sayonara();//�c���ł��ڂނ��I����
    } else {
        _pColliChecker->setColliSphere(0, _sx); //�����蔻����ω�
        getKuroko()->behave();
        pScaler_->behave();
    }
}

void MyTorpedoBlast::processJudgement() {
}

void MyTorpedoBlast::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�q�b�g���Ă����ł��܂���
    int sta = UTIL::calcMyStamina(this, pOther);
}

MyTorpedoBlast::~MyTorpedoBlast() {
    GGAF_DELETE(pScaler_);
}
