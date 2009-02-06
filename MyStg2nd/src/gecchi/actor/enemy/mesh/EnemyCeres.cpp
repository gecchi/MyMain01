#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCeres::EnemyCeres(const char* prm_name, const char* prm_model) : DefaultMeshEnemyActor(prm_name, prm_model) {
    _class_name = "EnemyCeres";

    _iMovePatternNo = 0;
    _pChecker->_iScorePoint = 100;
    //	_X = -100*1000;
    //	_Y = -100*1000;
    //	_Z = 0;

    _X = -356000; //äJénç¿ïW
    _Y = 0;
    _Z = -680000;
    _X_turn = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2 - 200000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _iBeginVelocity = 5000;

    //íeÉXÉgÉbÉNçÏê¨
    _pRotEnemyMeshShots001 = NEW RotationActor("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 16; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot", "M/myvic");
        pEnemyMeshShot->refrainImmediately(); //ç≈èâîÒï\é¶
            _pRotEnemyMeshShots001->addSubLast(pEnemyMeshShot);
        }
        //Ç´ÇØÇÒ	GgafFactory::_pGarbageBox->_pGarbageRootActor->addSubLast(_pRotEnemyMeshShots001); //âºèäëÆ
        addSubLast(_pRotEnemyMeshShots001); //âºèäëÆ

        _createRotationActor = true;
    }

EnemyCeres::EnemyCeres(const char* prm_name, const char* prm_model, RotationActor* prm_pRotEnemyMeshShots001) :
    DefaultMeshEnemyActor(prm_name, prm_model) {
    _class_name = "EnemyCeres";

    _iMovePatternNo = 0;
    _pChecker->_iScorePoint = 100;
    //	_X = -100*1000;
    //	_Y = -100*1000;
    //	_Z = 0;

    _X = -356000; //äJénç¿ïW
    _Y = 0;
    _Z = -680000;
    _X_turn = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2 - 200000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _iBeginVelocity = 5000;

    if (prm_pRotEnemyMeshShots001 == NULL) {
        _TRACE_("ÉçÅ[ÉeÅ[ÉVÉáÉì_pRotEnemyMeshShots001Ç™NULLÅBÇÊÇ¢ÇÃÇ≈Ç∑Ç©ÅH");
    }
    _pRotEnemyMeshShots001 = prm_pRotEnemyMeshShots001;
    _createRotationActor = false;
}

void EnemyCeres::initialize() {
    //ñ{óàÇÃèÍèäÇ÷
    getLordActor()->accept(KIND_ENEMY_SHOT_GU, (GgafMainActor*)_pRotEnemyMeshShots001->tear());

    setBumpableAlone(true);

    //	_pGeoMover->setMoveVelocity(1000);
    //	_pGeoMover->_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = true;
    //
    //	//_pGeoMover->setMoveAngleRzVelocityRenge(-2000, 2000);
    ////	//_pGeoMover->setMoveAngleRz(0,-100*1000,-100*1000);
    ////	_pGeoMover->setMoveAngle(100*1000,0,-100);


    //	_incZ =  (1.0*abs(_Z) / (GgafDx9Util::getDistance(_X, _Y, _X_turn, _Y_turn) / (_iBeginVelocity * sgn(_Z) * -1)) );//_incZÇ™Ç®Ç©ÇµÇ¢?

    _pGeoMover->setMoveAngle(_X_turn, _Y_turn, _Z_turn);
    _pGeoMover->setMoveVelocity(_iBeginVelocity);
    _pGeoMover->_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = true;
    _pGeoMover->_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = true;
    _pGeoMover->setAxisRotAngleVelocity(AXIS_X, 6000);

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pChecker->setStatus(100, 1, 1, 1);

}

void EnemyCeres::processBehavior() {
    //	if (_dwFrame > 5) {
    //		_TRACE_(_dwFrame << ":("<<_X<<","<<_Y<<","<<_Z<<")");
    //	}
    //
    //	if (_dwFrame == 100) {
    //		_pGeoMover->setMoveAngleRy(0);
    //	} else if (_dwFrame == 200) {
    //		_TRACE_("_dwFrame="<<_dwFrame);
    //		//_pGeoMover->setMoveAngleRy(ANGLE45);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE45);
    //	} else if (_dwFrame == 300) {
    ////		_pGeoMover->setMoveAngleRy(ANGLE90);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE90);
    //	} else if (_dwFrame == 400) {
    ////		_pGeoMover->setMoveAngleRy(ANGLE135);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE135);
    //	} else if (_dwFrame == 500) {
    ////		_pGeoMover->setMoveAngleRy(ANGLE180);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE180);
    //	} else if (_dwFrame == 600) {
    ////		_pGeoMover->setMoveAngleRy(ANGLE225);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE225);
    //	} else if (_dwFrame == 700) {
    ////		_pGeoMover->setMoveAngleRy(ANGLE270);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE270);
    //	} else if (_dwFrame == 800) {
    ////		_pGeoMover->setMoveAngleRy(ANGLE315);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE315);
    //	} else if (_dwFrame == 900) {
    ////		_pGeoMover->setMoveAngleRy(ANGLE360);
    //		_pGeoMover->setMoveAngleRyVelocity(2000);
    //		_pGeoMover->setTargetMoveAngleRy(ANGLE360);
    //	}


    //ï˚å¸ì]ä∑
    if (_iMovePatternNo == 0 && _X > _X_turn) {
        if (_pGeoMover->getDistanceFromMoveAngleRzTo(0, TURN_CLOSE_TO) > 0) {
            _pGeoMover->setMoveAngleRzVelocity(4000);
        } else {
            _pGeoMover->setMoveAngleRzVelocity(-4000);
        }
        if (_pGeoMover->getDistanceFromMoveAngleRyTo(ANGLE180, TURN_CLOSE_TO) > 0) {
            _pGeoMover->setMoveAngleRyVelocity(4000);
        } else {
            _pGeoMover->setMoveAngleRyVelocity(-4000);
        }
        _pGeoMover->setTargetMoveAngleRz(0);
        _pGeoMover->setTargetMoveAngleRy(ANGLE180);

        //íeÇåÇÇ¡ÇƒÇ›ÇÈ
        //		ÇTWAYíe
        //		angle way[5] ;
        //		GgafDx9Util::getWayAngle2D(180000, 5, 10000, way);
        //		EnemyShot001* pTama;
        //		RotationActor* pShots001 = GameGlobal::_pSceneCommon->_pEnemyShots001Rotation;
        //		for (int i = 0; i < 5; i++) {
        //			pTama = (EnemyShot001*)pShots001->obtain();
        //			if (pTama != NULL) {
        //				pTama->setGeometry (_X, _Y, 0);
        //				pTama->_pGeoMover->setMoveAngleRz(way[i]);
        //				pTama->act();
        //			}
        //		}


        angle way[16];
        //GgafDx9Util::getWayAngle2D(180000, 8, 10000, way);
        GgafDx9Util::getRadiationAngle2D(0, 16, way);
        EnemyMeshShot001* pTama;
        for (int i = 0; i < 8; i++) {
            pTama = (EnemyMeshShot001*)_pRotEnemyMeshShots001->obtain();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pGeoMover->setMoveAngleRzRy(-ANGLE90 + way[i], ANGLE90);
                pTama->act();
            }
        }
        for (int i = 8; i < 16; i++) {
            pTama = (EnemyMeshShot001*)_pRotEnemyMeshShots001->obtain();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pGeoMover->setMoveAngleRzRy(-ANGLE90 - way[i], -ANGLE90);
                pTama->act();
            }
        }

        _iMovePatternNo++;
    }

    //	if(0<_iMovePatternNo && _iMovePatternNo<20) {
    //		_iMovePatternNo++;
    //		_TRACE_(_iMovePatternNo<<"TURN ("<<_X<<","<<_Y<<","<<_Z<<") Å™("<<_pGeoMover->_vX<<","<<_pGeoMover->_vY<<","<<_pGeoMover->_vZ<<") Rz,Ry="<<_pGeoMover->_angRz_Move<<","<<_pGeoMover->_angRy_Move);
    //	}

    _pGeoMover->behave();
}

//void EnemyCeres::processBehavior() {
//
//	//ï˚å¸ì]ä∑
//	if (_iMovePatternNo == 0 && _X > _X_turn) {
//		_pGeoMover->setMoveAngleRz(sgn(_incZ)*-1*90000);
//		_pGeoMover->setMoveAngleRzVelocity(sgn(_incZ)*-1*3000);
//		_pGeoMover->setTargetMoveAngleRz(ANGLE180);
//		_pGeoMover->setMoveVelocity(1000);
//
//		_pGeoMover->setAxisRotAngleVelocity(AXIS_Y, sgn(_incZ)*-1*4000);
//		_pGeoMover->setTargetAxisRotAngle(AXIS_Y, ANGLE180);
//
//		//íeÇåÇÇ¡ÇƒÇ›ÇÈ
//
//		angle way[10] ;
//		GgafDx9Util::getWayAngle(180000, 10, 10000, way);
//		EnemyShot001* pTama;
//		RotationActor* pShots001 = GameGlobal::_pSceneCommon->_pEnemyShots001Rotation;
//		for (int i = 0; i < 10; i++) {
//			pTama = (EnemyShot001*)pShots001->obtain();
//			if (pTama) {
//				pTama->setGeometry (_X, _Y, 0);
//				pTama->_pGeoMover->setMoveAngleRz(way[i]);
//				pTama->act();
//			}
//		}
//
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 1 && _pGeoMover->_auto_move_angle_rz_target_Flg == false) {
//		_pGeoMover->setMoveVelocity(2000);
//		_pGeoMover->setMoveAcceleration(100);
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 2 && _X < -100000) {
//		//_TRACE_("Ceres:"<<getName()<<" (_X,_Y,_Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
//
//		_pGeoMover->setMoveVelocity(0);
//		_pGeoMover->setZMoveVelocity(0);
//		_pGeoMover->setMoveAcceleration(0);
//		_pGeoMover->setZMoveAcceleration(0);
//		_pGeoMover->setXYZMove(
//				5000,
//				GameGlobal::_pMyShip->_X,
//				GameGlobal::_pMyShip->_Y,
//				GameGlobal::_pMyShip->_Z
//				);
//		_iMovePatternNo++;
//	}
//	//_TRACE_("VX,VY="<<(_pGeoMover->_vX_Move)<<","<<(_pGeoMover->_vY_Move));
//
//	//ç¿ïWÇ…îΩâf
//	_pGeoMover->behave();
//	//_TRACE_("ab VX,VY="<<(_pGeoMover->_vX_Move)<<","<<(_pGeoMover->_vY_Move));
//	if (_incZ > 0) {
//		if (_Z > 0) {
//			_Z = 0;
//			_pGeoMover->setZMoveVelocity(0);
//		}
//	} else if (_incZ < 0) {
//		if (_Z < 0) {
//			_Z = 0;
//			_pGeoMover->setZMoveVelocity(0);
//		}
//	}
//
//	//_TRACE_("Ceres("<<_X<<","<<_Y<<","<<_Z<<")"<<_incZ <<"/"<<(_pGeoMover->_iVelocity_ZMove));
//}

void EnemyCeres::processJudgement() {
    if (isOffScreen()) {
        farewell();
        if (_createRotationActor) { //íeâï˙ó\ñÒ
            _pRotEnemyMeshShots001->farewell(60 * 5);
        }
    }
}

void EnemyCeres::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9UntransformedActor* pActor_Opponent = (GgafDx9UntransformedActor*)prm_pActor_Opponent;
    setBumpableAlone(false);

    if (pActor_Opponent->getHeadActor()->_kind & KIND_MY) {
        GameGlobal::_dwScore += _pChecker->_iScorePoint;
    }

    farewell();
    if (_createRotationActor) { //íeâï˙ó\ñÒ
        _pRotEnemyMeshShots001->farewell(60 * 5);
    }

    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->actAlone();
    }
}

bool EnemyCeres::isOffScreen() {
    if (_X < _X_OffScreenLeft - 800000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
}
