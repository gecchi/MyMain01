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
    //setAnimationMethod(OSCILLATE_LOOP, 2);

    _pMover->setRzMoveAngleVelocity(0);
    //_pMover->setRotAngleVelocity(AXIS_Z, 2*1000);
    //_pMover->setRzMoveAngle(0);
    //_pMover->setRotAngle(AXIS_Z, 0);
    _pMover->setMoveVelocity(20000);

    _pStgChecker->useHitAreaBoxNum(7);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000, true, true, true);
    _pStgChecker->setHitAreaBox(1, -10000, -140000, -10000, 10000, -120000, 10000, true, true, true);
    _pStgChecker->setHitAreaBox(2, -10000, 120000, -10000, 10000, 140000, 10000, true, true, true);
    _pStgChecker->setHitAreaBox(3, -140000, -10000, -10000, -120000, 10000, 10000, true, true, true);
    _pStgChecker->setHitAreaBox(4, 120000, -10000, -10000, 140000, 10000, 10000, true, true, true);
    _pStgChecker->setHitAreaBox(5, -10000, -10000, -140000, 10000, 10000, -120000, true, true, true);
    _pStgChecker->setHitAreaBox(6, -10000, -10000, 120000, 10000, 10000, 140000, true, true, true);

    //	_pStgChecker->_pHitAreaBoxs->setLine(0, -20000, 20000, 20000, 20000, true);
    //	_pStgChecker->_pHitAreaBoxs->setLine(1, 20000, 20000, 20000, -20000, true);
    //	_pStgChecker->_pHitAreaBoxs->setLine(2, 20000, -20000, -20000, -20000, true);
    //	_pStgChecker->_pHitAreaBoxs->setLine(3, -20000, -20000, -20000, 20000, true);
    //	_pStgChecker->_pHitAreaBoxs->setLine(4, 30000, 30000, -30000, -30000, true);
    //	_pStgChecker->_pHitAreaBoxs->setLine(5, -30000, 30000, 30000, -30000, true);
    //
    _pScaler->setScaleRange(1000,20000);
    //setAlpha(0.2);

    setBumpable(true);
    inactivateTree();

}

void MyWave001::processBehavior() {
    if (onChangeToActive()) {
        //出現時共通処理
        _pScaler->setScale(1000);
        _pScaler->intoTargetScaleLinerStep(100000,100);
		_pScaler->behave();
        setBumpable(true);
        setGeometry(GameGlobal::_pMyShip);
        _pMover->setRotAngle(AXIS_Z, GameGlobal::_pMyShip->_pMover->_angRot[AXIS_Z]);
        _pMover->setRotAngle(AXIS_Y, GameGlobal::_pMyShip->_pMover->_angRot[AXIS_Y]);
        _pMover->setRzRyMoveAngle(GameGlobal::_pMyShip->_pMover->_angRot[AXIS_Z],
                                     GameGlobal::_pMyShip->_pMover->_angRot[AXIS_Y]);
        //		_X = GameGlobal::_pMyShip->_X;
        //		_Y = GameGlobal::_pMyShip->_Y;
        //		_Z = GameGlobal::_pMyShip->_Z;
    } else {
        //通常処理
        //addNextAnimationFrame();
        //座標に反映
        _pScaler->behave();
        _pMover->behave();
        _pStgChecker->behave();
    }
}

void MyWave001::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (wasGone()) {
        inactivateTree();
    }

}

/*
 bool MyWave001::processBumpChkLogic(GgafDx9GeometricActor* prm_pActor_Opponent) {
 //TRACE("MyWave001::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
 return false;
 }
 */

void MyWave001::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("MyWave001::processOnHit ショットがヒットしました");
    //_TRACE_("MyWave001ヒットしました。("<<_X<<","<<_Y<<")");
    //adios();
    inactivateTree();
}

void MyWave001::onInactive() {
    //消失時処理
    setBumpable(false);
    moveFirst();
}

MyWave001::~MyWave001() {

}
