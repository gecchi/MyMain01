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
    _pUvFliper->setUvFlipMethod(FLIP_OSCILLATE_LOOP, 2);

    _pMover->setRzMvAngVelo(0);
    //_pMover->setFaceAngVelo(AXIS_Z, 2 * 1000);
    _pMover->setFaceAngVelo(AXIS_X, 10000);
    //_pMover->setFaceAngVelo(AXIS_Y, 2 * 1800);

    _pMover->setRzMvAng(0);
    _pMover->setFaceAng(AXIS_Z, 0);
    _pMover->setMvVelo(40000);

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
    _SX = 50000;
    _SY = 50000;
    setAlpha(0.5);

    setHitAble(true);
    inactivateTree();

}

void MyShot001::processBehavior() {
    if (onChangeToActive()) {
        //èoåªéûã§í èàóù
        setHitAble(true);
        _X = GameGlobal::_pMyShip->_X;
        _Y = GameGlobal::_pMyShip->_Y;
        _Z = GameGlobal::_pMyShip->_Z;
    } else {
        //í èÌèàóù
        _pUvFliper->behave();
        //ç¿ïWÇ…îΩâf
        _pMover->behave();
    }
}

void MyShot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivateTree();
    }

}


void MyShot001::onHit(GgafActor* prm_pOtherActor) {
    inactivateTree();
}

void MyShot001::onInactive() {
    //è¡é∏éûèàóù
    setHitAble(false);
    moveFirst();
}

MyShot001::~MyShot001() {

}
