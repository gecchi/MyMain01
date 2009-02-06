#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShot001::MyShot001(const char* prm_name, const char* prm_model) : DefaultSpriteMyActor(prm_name, prm_model) {
    _class_name = "MyShot001";
}

void MyShot001::initialize() {
    setAnimationMethod(OSCILLATE_LOOP, 2);

    _pGeoMover->setMoveAngleRzVelocity(0);
    _pGeoMover->setAxisRotAngleVelocity(AXIS_Z, 2 * 1000);
    _pGeoMover->setMoveAngleRz(0);
    _pGeoMover->setAxisRotAngle(AXIS_Z, 0);
    _pGeoMover->setMoveVelocity(1000);

    _pChecker->useHitAreaBoxNum(7);
    _pChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000, true, true, true);
    _pChecker->setHitAreaBox(1, -10000, -140000, -10000, 10000, -120000, 10000, true, true, true);
    _pChecker->setHitAreaBox(2, -10000, 120000, -10000, 10000, 140000, 10000, true, true, true);
    _pChecker->setHitAreaBox(3, -140000, -10000, -10000, -120000, 10000, 10000, true, true, true);
    _pChecker->setHitAreaBox(4, 120000, -10000, -10000, 140000, 10000, 10000, true, true, true);
    _pChecker->setHitAreaBox(5, -10000, -10000, -140000, 10000, 10000, -120000, true, true, true);
    _pChecker->setHitAreaBox(6, -10000, -10000, 120000, 10000, 10000, 140000, true, true, true);

    //	_pChecker->_pHitAreaBoxs->setLine(0, -20000, 20000, 20000, 20000, true);
    //	_pChecker->_pHitAreaBoxs->setLine(1, 20000, 20000, 20000, -20000, true);
    //	_pChecker->_pHitAreaBoxs->setLine(2, 20000, -20000, -20000, -20000, true);
    //	_pChecker->_pHitAreaBoxs->setLine(3, -20000, -20000, -20000, 20000, true);
    //	_pChecker->_pHitAreaBoxs->setLine(4, 30000, 30000, -30000, -30000, true);
    //	_pChecker->_pHitAreaBoxs->setLine(5, -30000, 30000, 30000, -30000, true);
    //
    _SX = 10000;
    _SY = 10000;
    setAlpha(0.2);

    setBumpableAlone(true);
    refrain();

}

void MyShot001::processBehavior() {
    if (switchedToAct()) {
        //出現時共通処理
        setBumpableAlone(true);
        _X = GameGlobal::_pMyShip->_X;
        _Y = GameGlobal::_pMyShip->_Y;
        _Z = GameGlobal::_pMyShip->_Z;
    } else {
        //通常処理
        nextAnimationFrame();
        //座標に反映
        _pGeoMover->behave();
        _pChecker->behave();
    }
}

void MyShot001::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (isOffScreen()) {
        refrain();
    }

}

/*
 bool MyShot001::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
 //TRACE("MyShot001::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
 return false;
 }
 */

void MyShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("MyShot001::processOnHit ショットがヒットしました");
    //_TRACE_("MyShot001ヒットしました。("<<_X<<","<<_Y<<")");
    //farewell();
    refrain();
}

void MyShot001::onRefrain() {
    //消失時処理
    setBumpableAlone(false);
    moveFirst();
}

MyShot001::~MyShot001() {

}
