#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyShot001::MyShot001(const char* prm_name) :
        SingleLaser(prm_name, "MyShot001", STATUS(MyShot001)) { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "MyShot001";
}

void MyShot001::initialize() {
    setHitAble(false);
    _SX = R2SC(45);
    _SY = _SZ = R2SC(35);
    setBoundingSphereRadiusRate(45.0f);
    setAlpha(0.99); //�������ɂ��邱�Ƃŗ��ʃ����_�����O
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -PXCO(50), -PXCO(50), -PXCO(50),
                                    PXCO(50),  PXCO(50),  PXCO(50));
    _pKurokoA->setFaceAngVelo(AXIS_X, DANG(12));
}

void MyShot001::onActive() {
    setHitAble(true);
    _pKurokoA->setMvVelo(PXCO(70));             //�ړ����x
    _pKurokoA->setMvAcce(100);
}

void MyShot001::processBehavior() {
    //���Z�����N�|�C���g������
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //�e�Ȃ̂ŕs�v

    //���W�ɔ��f
    //if (onChangeToActive()) {

    //} else {
        _pKurokoA->behave();
    //}
}

void MyShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void MyShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locatedBy(this);
        }
        sayonara();
    //}
}


void MyShot001::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}
MyShot001::~MyShot001() {
}
