#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyWave001::MyWave001(const char* prm_name) :
        DefaultMeshActor(prm_name, "wave", NULL) {
    _class_name = "MyWave001";
}

void MyWave001::initialize() {
    //setFlipMethod(FLIP_OSCILLATE_LOOP, 2);

    _pKurokoA->setRzMvAngVelo(0);
    //_pKurokoA->setFaceAngVelo(AXIS_Z, 2*1000);
    //_pKurokoA->setRzMvAng(0);
    //_pKurokoA->setFaceAng(AXIS_Z, 0);
    _pKurokoA->setMvVelo(20000);

    _pColliChecker->makeCollision(7);
    _pColliChecker->setColliAAB(0,  -10000,  -10000,  -10000,   10000,   10000,   10000, true, true, true);
    _pColliChecker->setColliAAB(1,  -10000, -140000,  -10000,   10000, -120000,   10000, true, true, true);
    _pColliChecker->setColliAAB(2,  -10000,  120000,  -10000,   10000,  140000,   10000, true, true, true);
    _pColliChecker->setColliAAB(3, -140000,  -10000,  -10000, -120000,   10000,   10000, true, true, true);
    _pColliChecker->setColliAAB(4,  120000,  -10000,  -10000,  140000,   10000,   10000, true, true, true);
    _pColliChecker->setColliAAB(5,  -10000,  -10000, -140000,   10000,   10000, -120000, true, true, true);
    _pColliChecker->setColliAAB(6,  -10000,  -10000,  120000,   10000,   10000,  140000, true, true, true);


    //	_pColliChecker->pHitAreaBoxs_->setLine(0, -20000, 20000, 20000, 20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(1, 20000, 20000, 20000, -20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(2, 20000, -20000, -20000, -20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(3, -20000, -20000, -20000, 20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(4, 30000, 30000, -30000, -30000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(5, -30000, 30000, 30000, -30000, true);
    //
    _pScaler->forceScaleRange(1000,20000);
    //setAlpha(0.2);

    setHitAble(true);

}

void MyWave001::processBehavior() {
    if (onChangeToActive()) {
        //出現時共通処理
        _pScaler->setScale(1000);
        _pScaler->intoTargetScaleLinerStep(100000,100);
        _pScaler->behave();
        setHitAble(true);
        locatedBy(P_MYSHIP);
        _pKurokoA->setFaceAng(AXIS_Z, P_MYSHIP->_pKurokoA->_angFace[AXIS_Z]);
        _pKurokoA->setFaceAng(AXIS_Y, P_MYSHIP->_pKurokoA->_angFace[AXIS_Y]);
        _pKurokoA->setRzRyMvAng(P_MYSHIP->_pKurokoA->_angFace[AXIS_Z],
                                     P_MYSHIP->_pKurokoA->_angFace[AXIS_Y]);
        //		_X = P_MYSHIP->_X;
        //		_Y = P_MYSHIP->_Y;
        //		_Z = P_MYSHIP->_Z;
    } else {
        //通常処理
        //behaveUvFlip();
        //座標に反映
        _pScaler->behave();
        _pKurokoA->behave();
    }
}

void MyWave001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }

}

/*
 bool MyWave001::processHitChkLogic(GgafDxGeometricActor* prm_pOtherActor) {
 //TRACE("MyWave001::processHitChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pOtherActor->getPlatformScene()->getName()+"."+prm_pOtherActor->getName());
 return false;
 }
 */

void MyWave001::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("MyWave001::onHit ショットがヒットしました");
    //_TRACE_("MyWave001ヒットしました。("<<_X<<","<<_Y<<")");
    //end();
    sayonara();
}

void MyWave001::onInactive() {
}

MyWave001::~MyWave001() {

}
