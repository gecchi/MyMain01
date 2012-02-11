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
    setAlpha(0.3);
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void MyTorpedoBlast::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pKurokoA->setFaceAngVelo(AXIS_X, DEG2ANG(0));
    _pKurokoA->setFaceAngVelo(AXIS_Y, DEG2ANG(6));
    _pKurokoA->setFaceAngVelo(AXIS_Z, DEG2ANG(0));
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    _pStatus->reset();
    _pCollisionChecker->setColliSphere(0, PX2CO(10));
    _pKurokoA->setMvVelo(0);
    _pScaler->setScale(R2SC(1));
    _pScaler->forceScaleRange(R2SC(1), R2SC(400));

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
