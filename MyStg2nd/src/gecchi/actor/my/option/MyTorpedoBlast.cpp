#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MyTorpedoBlast::MyTorpedoBlast(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "MyTorpedoBlast",STATUS(MyTorpedoBlast)) {
    _class_name = "MyTorpedoBlast";
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setAlpha(0.2);
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void MyTorpedoBlast::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pKurokoA->setFaceAngVelo(AXIS_X, 27*1000);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 33*1000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 17*1000);
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    _pStatus->reset();
    _pCollisionChecker->setColliSphere(0, 1000);
    _pKurokoA->setMvVelo(0);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 400*1000);

}

void MyTorpedoBlast::onActive() {
    _pScaler->beat(120, 120/2, 0, 1); //1回膨らんでしぼむ
}

void MyTorpedoBlast::processBehavior() {
    if (_pScaler->_method[AXIS_X] == NOSCALE) {
        sayonara();//膨らんでしぼむが終了時
    } else {
        _pCollisionChecker->setColliSphere(0, _pScaler->_scale[AXIS_X]); //当たり判定も変化
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
    //ヒットしても消滅しません
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
}

MyTorpedoBlast::~MyTorpedoBlast() {
}
