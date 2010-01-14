#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShot001::MyShot001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "moji2") {
//MyShot001::MyShot001(const char* prm_name) : DefaultSpriteMyActor(prm_name, "moji2") {
    _class_name = "MyShot001";
}

void MyShot001::initialize() {
    setAnimationMethod(OSCILLATE_LOOP, 2);

    _pMover->setRzMoveAngleVelocity(0);
    //_pMover->setFaceAngleVelocity(AXIS_Z, 2 * 1000);
    _pMover->setFaceAngleVelocity(AXIS_X, 10000);
    //_pMover->setFaceAngleVelocity(AXIS_Y, 2 * 1800);

    _pMover->setRzMoveAngle(0);
    _pMover->setFaceAngle(AXIS_Z, 0);
    _pMover->setMoveVelocity(40000);

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
    _SX = 50000;
    _SY = 50000;
    setAlpha(0.5);

    setBumpable(true);
    inactivateTree();

}

void MyShot001::processBehavior() {
    if (onChangeToActive()) {
        //èoåªéûã§í èàóù
        setBumpable(true);
        _X = GameGlobal::_pMyShip->_X;
        _Y = GameGlobal::_pMyShip->_Y;
        _Z = GameGlobal::_pMyShip->_Z;
    } else {
        //í èÌèàóù
        addNextAnimationFrame();
        //ç¿ïWÇ…îΩâf
        _pMover->behave();
    }
}

void MyShot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivateTree();
    }

}


void MyShot001::processOnHit(GgafActor* prm_pOtherActor) {
    inactivateTree();
}

void MyShot001::onInactive() {
    //è¡é∏éûèàóù
    setBumpable(false);
    moveFirst();
}

MyShot001::~MyShot001() {

}
