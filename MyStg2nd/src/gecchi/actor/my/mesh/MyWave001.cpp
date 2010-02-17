#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyWave001::MyWave001(const char* prm_name) : DefaultMeshActor(prm_name, "wave") {
    _class_name = "MyWave001";
}

void MyWave001::initialize() {
    //setFlipMethod(FLIP_OSCILLATE_LOOP, 2);

    _pMover->setRzMvAngVelo(0);
    //_pMover->setFaceAngVelo(AXIS_Z, 2*1000);
    //_pMover->setRzMvAng(0);
    //_pMover->setFaceAng(AXIS_Z, 0);
    _pMover->setMvVelo(20000);

    _pCollisionChecker->makeCollision(7);
    _pCollisionChecker->setColliBox(0, -10000, -10000, -10000, 10000, 10000, 10000, true, true, true);
    _pCollisionChecker->setColliBox(1, -10000, -140000, -10000, 10000, -120000, 10000, true, true, true);
    _pCollisionChecker->setColliBox(2, -10000, 120000, -10000, 10000, 140000, 10000, true, true, true);
    _pCollisionChecker->setColliBox(3, -140000, -10000, -10000, -120000, 10000, 10000, true, true, true);
    _pCollisionChecker->setColliBox(4, 120000, -10000, -10000, 140000, 10000, 10000, true, true, true);
    _pCollisionChecker->setColliBox(5, -10000, -10000, -140000, 10000, 10000, -120000, true, true, true);
    _pCollisionChecker->setColliBox(6, -10000, -10000, 120000, 10000, 10000, 140000, true, true, true);

    //	_pCollisionChecker->_pHitAreaBoxs->setLine(0, -20000, 20000, 20000, 20000, true);
    //	_pCollisionChecker->_pHitAreaBoxs->setLine(1, 20000, 20000, 20000, -20000, true);
    //	_pCollisionChecker->_pHitAreaBoxs->setLine(2, 20000, -20000, -20000, -20000, true);
    //	_pCollisionChecker->_pHitAreaBoxs->setLine(3, -20000, -20000, -20000, 20000, true);
    //	_pCollisionChecker->_pHitAreaBoxs->setLine(4, 30000, 30000, -30000, -30000, true);
    //	_pCollisionChecker->_pHitAreaBoxs->setLine(5, -30000, 30000, 30000, -30000, true);
    //
    _pScaler->forceScaleRange(1000,20000);
    //setAlpha(0.2);

    setHitAble(true);
    inactivateTree();

}

void MyWave001::processBehavior() {
    if (onChangeToActive()) {
        //出現時共通処理
        _pScaler->setScale(1000);
        _pScaler->intoTargetScaleLinerStep(100000,100);
        _pScaler->behave();
        setHitAble(true);
        setGeometry(GameGlobal::_pMyShip);
        _pMover->setFaceAng(AXIS_Z, GameGlobal::_pMyShip->_pMover->_angFace[AXIS_Z]);
        _pMover->setFaceAng(AXIS_Y, GameGlobal::_pMyShip->_pMover->_angFace[AXIS_Y]);
        _pMover->setRzRyMvAng(GameGlobal::_pMyShip->_pMover->_angFace[AXIS_Z],
                                     GameGlobal::_pMyShip->_pMover->_angFace[AXIS_Y]);
        //		_X = GameGlobal::_pMyShip->_X;
        //		_Y = GameGlobal::_pMyShip->_Y;
        //		_Z = GameGlobal::_pMyShip->_Z;
    } else {
        //通常処理
        //behaveUvFlip();
        //座標に反映
        _pScaler->behave();
        _pMover->behave();
    }
}

void MyWave001::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (isOutOfGameSpace()) {
        inactivateTree();
    }

}

/*
 bool MyWave001::processHitChkLogic(GgafDx9GeometricActor* prm_pOtherActor) {
 //TRACE("MyWave001::processHitChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pOtherActor->getPlatformScene()->getName()+"."+prm_pOtherActor->getName());
 return false;
 }
 */

void MyWave001::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("MyWave001::onHit ショットがヒットしました");
    //_TRACE_("MyWave001ヒットしました。("<<_X<<","<<_Y<<")");
    //sayonara();
    inactivateTree();
}

void MyWave001::onInactive() {
    //消失時処理
    setHitAble(false);
    moveFirst();
}

MyWave001::~MyWave001() {

}
