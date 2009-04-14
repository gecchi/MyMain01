#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionParent::MyOptionParent(const char* prm_name) :
  GgafDx9UntransformedActor(prm_name,
                            NEW GgafDx9GeometryMover(this),
                            NEW StgChecker(this) ) {
    _angVelocity_Turn = 5000;

    MyDummyOption* pMyDummyOption01 = NEW MyDummyOption("MY_OPTION01", 0, this);
    pMyDummyOption01->_radius = 150000;
    pMyDummyOption01->_angPosition = 0;
    addSubLast(pMyDummyOption01);

    MyDummyOption* pMyDummyOption02 = NEW MyDummyOption("MY_OPTION02", 1, this);
    pMyDummyOption02->_radius = 150000;
    pMyDummyOption02->_angPosition = ANGLE90;
    addSubLast(pMyDummyOption02);

    MyDummyOption* pMyDummyOption03 = NEW MyDummyOption("MY_OPTION03", 2, this);
    pMyDummyOption03->_radius = 150000;
    pMyDummyOption03->_angPosition = ANGLE180;
    addSubLast(pMyDummyOption03);

    MyDummyOption* pMyDummyOption04 = NEW MyDummyOption("MY_OPTION04", 4, this);
    pMyDummyOption04->_radius = 150000;
    pMyDummyOption04->_angPosition = ANGLE270;
    addSubLast(pMyDummyOption04);

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }
}

void MyOptionParent::initialize() {
    _pGeoMover->setMoveVelocity(0);
    _pGeoMover->setRyMoveAngleVelocityRenge(-1*_angVelocity_Turn, _angVelocity_Turn);
    _pGeoMover->setRzMoveAngleVelocityRenge(-1*_angVelocity_Turn, _angVelocity_Turn);

    _way_myship_prev = GameGlobal::_pMyShip->_way;
}

void MyOptionParent::processBehavior() {
//    _X = GameGlobal::_pMyShip->_X;
//    _Y = GameGlobal::_pMyShip->_Y;
//    _Z = GameGlobal::_pMyShip->_Z;

    if (_way_myship_prev != GameGlobal::_pMyShip->_way) {

        //方向が変わった
        _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;
        _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;
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
    //座標に反映
    if (GameGlobal::_pMyShip->_stc != 0) {
        //動かそうとしていた！
        _pGeoMover->behave();
    }
    _pRing_GeoHistory->next()->set(_X, _Y, _Z);
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

MyOptionParent::~MyOptionParent() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}
