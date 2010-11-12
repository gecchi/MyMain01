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
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setMaterialColor(1.0, 0.3, 0.3);
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
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
    _pScaler->intoTargetScaleAcceStep(99, 30, -1); //膨らんでしぼむ
}

void MyTorpedoBlast::processBehavior() {
    if (_pScaler->_method[AXIS_X] == NOSCALE) {
        sayonara();//膨らんでしぼむが終了時
    } else {
        _pCollisionChecker->setColliSphere(0, _pScaler->_scale[AXIS_X]*1000); //当たり判定も変化
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
    //ヒットしても消滅しません
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
}

MyTorpedoBlast::~MyTorpedoBlast() {
}
