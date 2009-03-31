#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionParent::MyOptionParent(const char* prm_name) : DefaultMeshActor(prm_name, "X/ceres") {
    _angVelocity_Turn = 3000;

    MyOption* pMyOption01 = NEW MyOption("MY_OPTION01", 0, this);
    pMyOption01->_distR = 200000;
    pMyOption01->_angPosRotX = 0;
    addSubLast(pMyOption01);

//    MyOption* pMyOption02 = NEW MyOption("MY_OPTION02", 1, this);
//    pMyOption01->_distR = 200000;
//    pMyOption01->_angPosRotX = ANGLE90;
//    addSubLast(pMyOption02);
//
//    MyOption* pMyOption03 = NEW MyOption("MY_OPTION03", 2, this);
//    pMyOption01->_distR = 200000;
//    pMyOption01->_angPosRotX = ANGLE180;
//    addSubLast(pMyOption03);

//    MyOption* pMyOption04 = NEW MyOptionParent("MY_OPTION04");
//    pMyOption01->_distR = 100000;
//    pMyOption01->_angPosRotX = 0;
//    addSubLast(pMyOption04);


}

void MyOptionParent::initialize() {
    _pGeoMover->setMoveVelocity(0);
    _pGeoMover->setRyMoveAngleVelocityRenge(-1*_angVelocity_Turn, _angVelocity_Turn);
    _pGeoMover->setRzMoveAngleVelocityRenge(-1*_angVelocity_Turn, _angVelocity_Turn);

    _way_myship_prev = GameGlobal::_pMyShip->_way;
}

void MyOptionParent::processBehavior() {
    _X = GameGlobal::_pMyShip->_X + 150000;
    _Y = GameGlobal::_pMyShip->_Y;
    _Z = GameGlobal::_pMyShip->_Z;

    if (_way_myship_prev != GameGlobal::_pMyShip->_way) {

        //•ûŒü‚ª•Ï‚í‚Á‚½
        _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_Flg = true;
        _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_Flg = true;
        switch(GameGlobal::_pMyShip->_way) {
            case WAY_UP:
                setTerget(ANGLE90, 0);
                break;
            case WAY_UP_FRONT:
                setTerget(ANGLE45, 0);
                break;
            case WAY_UP_BEHIND:
                setTerget(ANGLE135, 0);
                break;
            case WAY_DOWN:
                setTerget(ANGLE270, 0);
                break;
            case WAY_DOWN_FRONT:
                setTerget(ANGLE315, 0);
                break;
            case WAY_DOWN_BEHIND:
                setTerget(ANGLE225, 0);
                break;
            case WAY_FRONT:
                setTerget(0, 0);
                break;
            case WAY_BEHIND:
                setTerget(0, ANGLE180);
                //            _pGeoMover->setAutoTargetRzMoveAngle(0);
                //            _pGeoMover->setAutoTargetRyMoveAngle(ANGLE180);

                break;
            case WAY_ZLEFT:
                setTerget(0, ANGLE270);
                break;
            case WAY_ZLEFT_FRONT:
                setTerget(0, ANGLE315);
                break;
            case WAY_ZLEFT_BEHIND:
                setTerget(0, ANGLE225);
                break;
            case WAY_ZRIGHT:
                setTerget(0, ANGLE90);
                break;
            case WAY_ZRIGHT_FRONT:
                setTerget(0, ANGLE45);
                break;
            case WAY_ZRIGHT_BEHIND:
                setTerget(0, ANGLE135);
                break;
            default:
                break;
        }
        _way_myship_prev = GameGlobal::_pMyShip->_way;
    }
    //À•W‚É”½‰f
    if (GameGlobal::_pMyShip->_stc != 0) {
        //“®‚©‚»‚¤‚Æ‚µ‚Ä‚¢‚½I
        _pGeoMover->behave();
    }
}


void MyOptionParent::setTerget(angle prm_angRz_Target, angle prm_angRy_Target) {
    if (_pGeoMover->getDistanceFromRzMoveAngleTo(prm_angRz_Target, TURN_CLOSE_TO) > 0) {
        _pGeoMover->setRzMoveAngleVelocity(_angVelocity_Turn);
    } else {
        _pGeoMover->setRzMoveAngleVelocity(-1 * _angVelocity_Turn);
    }
    if (_pGeoMover->getDistanceFromRyMoveAngleTo(prm_angRy_Target, TURN_CLOSE_TO) > 0) {
        _pGeoMover->setRyMoveAngleVelocity(_angVelocity_Turn);
    } else {
        _pGeoMover->setRyMoveAngleVelocity(-1 * _angVelocity_Turn);
    }
    _pGeoMover->setAutoTargetRzMoveAngle(prm_angRz_Target);
    _pGeoMover->setAutoTargetRyMoveAngle(prm_angRy_Target);
}

void MyOptionParent::processJudgement() {
}

void MyOptionParent::processOnHit(GgafActor* prm_pActor_Opponent) {
}

MyOptionParent::~MyOptionParent() {
}
