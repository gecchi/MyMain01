#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "M/tamago") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    //inactivateTree();
    setBumpable(true);
    //
//    _pGeoMover->setRzMoveAngle(ANGLE180);
//    _pGeoMover->setMoveVelocity(2000);
//    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;
//
    //	_pGeoMover->setRotAngle(AXIS_Z, ANGLE180*1000);
    //	_pGeoMover->setMoveVelocity(2000);
    //


    //	_pGeoMover->_topIncrementRotAngle[AXIS_Z] = 60 * 1000;
    //
    //	_pGeoMover->_synchronize_ZaxisRotAngle_to_RzMoveAngle_Flg = true;
    //	_pGeoMover->_iType_AutoXYMoveAngleTarget = TURN_COUNTERCLOCKWISE;

    //	_pChecker->useHitAreaBoxNum(1, 0);
    //	_pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);

    _pChecker->useHitAreaBoxNum(2);
    _pChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _pChecker->setHitAreaBox(1, 100000, 100000, 100000, 130000, 130000, 130000);
    _SX = _SY = _SZ = 10*1000;
    _frame_offset = 0;
    //_pGeoMover->_iIncrementRotAngle[AXIS_X] = -100*1000;

    //_rnd = (110 + (rand() % 90));
}

void TamagoActor::processBehavior() {

//    _frame_offset++;
//    if (_pGeoMover->_angRot[AXIS_Z] < ANGLE180) {
//        _pGeoMover->setRotAngle(AXIS_X, ANGLE360 - _pGeoMover->_angRot[AXIS_Z]);
//    } else {
//        _pGeoMover->setRotAngle(AXIS_X, _pGeoMover->_angRot[AXIS_Z]);
//    }
//    //_pGeoMover->setRotAngleVelocity(AXIS_X, 5*1000);//１フレーム0.5度
//
//    if (_frame_offset % _rnd == 0) {
//        _rnd = (110 + (rand() % 90));
//
//        _pGeoMover->setTargetRzMoveAngleV(GameGlobal::_pMyShip->_X, GameGlobal::_pMyShip->_Y);
//        if (_pGeoMover->getDifferenceFromRzMoveAngleTo(_pGeoMover->_angTargetRzMove, TURN_CLOSE_TO) > 0) {
//            _pGeoMover->setRzMoveAngleVelocity(2 * 1000);
//        } else {
//            _pGeoMover->setRzMoveAngleVelocity(-2 * 1000);
//        }
//
//        _pGeoMover->setMoveVelocityRenge(ANGLE360, 2 * 1000);
//        _pGeoMover->setMoveVelocity(10 * 1000); //初速10px
//        _pGeoMover->setMoveAcceleration(-80);
//        //		_pGeoMover->setTargetRzMoveAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//    }

    //	if (_frame_offset == 10) {
    //		//_pGeoMover->setTargetRzMoveAngle(c);
    //		_pGeoMover->setMoveVelocity(2000);
    //		_pGeoMover->setTargetRzMoveAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
    //	}
    //
    //	if (_frame_offset == 150) {
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(ANGLE360*1000);
    //		//_pGeoMover->setTargetRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
    //	}
    //
    //
    //	if (_frame_offset == 200) {
    //
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(ANGLE90*1000);
    //		//_pGeoMover->setTargetRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
    //	}
    //
    //	if (_frame_offset == 250) {
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(0);
    //	}
    //	if (_frame_offset == 300) {
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(2250*1000);
    //	}
    //	if (_frame_offset == 400) {
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(ANGLE90*1000);
    //	}
    //
    //	if (_frame_offset == 500) {
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(3150*1000);
    //	}
    //
    //	if (_frame_offset == 550) {
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(ANGLE90*1000);
    //	}
    //	if (_frame_offset == 570) {
    //		_pGeoMover->setMoveVelocity(6000);
    //		_pGeoMover->setTargetRzMoveAngle(2250*1000);
    //	}
    //
    //
    //	if (_frame_offset == 650) {
    //		_pGeoMover->setMoveVelocity(1000);
    //		_pGeoMover->_iIncrementXYMoveSpeed = 30;
    //		_pGeoMover->_move_angle_target_Flg = false;
    //		_pGeoMover->_rot_angle_targeting_flg = false;
    //		_pGeoMover->_rot_angle_Flg = true;
    //		_pGeoMover->_iIncrementXYMoveAngle =80*1000;
    //	}

    //座標に反映
    _pGeoMover->behave();
    _pChecker->behave();

}

void TamagoActor::processJudgement() {
}

void TamagoActor::processOnHit(GgafActor* prm_pActor_Opponent) {
    _TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
