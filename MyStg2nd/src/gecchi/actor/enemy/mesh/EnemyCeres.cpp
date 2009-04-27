#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCeres::EnemyCeres(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/Ceres") {
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
    _veloBegin = 5000;

    //íeÉXÉgÉbÉNçÏê¨
    _pRotEnemyMeshShots001 = NEW RotationActor("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 16; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //ç≈èâîÒï\é¶
            _pRotEnemyMeshShots001->addSubLast(pEnemyMeshShot);
        }
        //Ç´ÇØÇÒ	GgafFactory::_pGarbageBox->_pGarbageRootActor->addSubLast(_pRotEnemyMeshShots001); //âºèäëÆ
        addSubLast(_pRotEnemyMeshShots001); //âºèäëÆ

        _createRotationActor = true;
    }

EnemyCeres::EnemyCeres(const char* prm_name, RotationActor* prm_pRotEnemyMeshShots001) :
    DefaultMeshEnemyActor(prm_name, "X/Ceres") {
    _class_name = "EnemyCeres";

    _iMovePatternNo = 0;
    _pChecker->_iScorePoint = 100;
    //	_X = -100*1000;
    //	_Y = -100*1000;
    //	_Z = 0;

    _X = -356000; //äJénç¿ïW
    _Y = 0;
    _Z = -680000;
    _X_turn = _X_OffScreenRight - 30000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _veloBegin = 5000;

    if (prm_pRotEnemyMeshShots001 == NULL) {
        _TRACE_("ÉçÅ[ÉeÅ[ÉVÉáÉì_pRotEnemyMeshShots001Ç™NULLÅBÇÊÇ¢ÇÃÇ≈Ç∑Ç©ÅH");
    }
    _pRotEnemyMeshShots001 = prm_pRotEnemyMeshShots001;
    _createRotationActor = false;
}

void EnemyCeres::initialize() {
    //ñ{óàÇÃèÍèäÇ÷
    getLordActor()->accept(KIND_ENEMY_SHOT_GU, (GgafMainActor*)_pRotEnemyMeshShots001->breakAwayFromTree());

    setBumpable(true);

    //	_pGeoMover->setMoveVelocity(1000);
    //	_pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;
    //
    //	//_pGeoMover->setRzMoveAngleVelocityRenge(-2000, 2000);
    ////	//_pGeoMover->setRzMoveAngle(0,-100*1000,-100*1000);
    ////	_pGeoMover->setMoveAngle(100*1000,0,-100);


    //	_incZ =  (1.0*abs(_Z) / (GgafDx9Util::getDistance(_X, _Y, _X_turn, _Y_turn) / (_veloBegin * sgn(_Z) * -1)) );//_incZÇ™Ç®Ç©ÇµÇ¢?

    _pGeoMover->setMoveAngle(_X_turn, _Y_turn, _Z_turn);
    _pGeoMover->setMoveVelocity(_veloBegin);
    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;
    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;
    _pGeoMover->setRotAngleVelocity(AXIS_X, 6000);

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pChecker->setStatus(100, 1, 1, 1);

}

void EnemyCeres::processBehavior() {
    //	if (_lifeframe > 5) {
    //		_TRACE_(_lifeframe << ":("<<_X<<","<<_Y<<","<<_Z<<")");
    //	}
    //
    //	if (_lifeframe == 100) {
    //		_pGeoMover->setRyMoveAngle(0);
    //	} else if (_lifeframe == 200) {
    //		_TRACE_("_lifeframe="<<_lifeframe);
    //		//_pGeoMover->setRyMoveAngle(ANGLE45);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE45);
    //	} else if (_lifeframe == 300) {
    ////		_pGeoMover->setRyMoveAngle(ANGLE90);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE90);
    //	} else if (_lifeframe == 400) {
    ////		_pGeoMover->setRyMoveAngle(ANGLE135);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE135);
    //	} else if (_lifeframe == 500) {
    ////		_pGeoMover->setRyMoveAngle(ANGLE180);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE180);
    //	} else if (_lifeframe == 600) {
    ////		_pGeoMover->setRyMoveAngle(ANGLE225);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE225);
    //	} else if (_lifeframe == 700) {
    ////		_pGeoMover->setRyMoveAngle(ANGLE270);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE270);
    //	} else if (_lifeframe == 800) {
    ////		_pGeoMover->setRyMoveAngle(ANGLE315);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE315);
    //	} else if (_lifeframe == 900) {
    ////		_pGeoMover->setRyMoveAngle(ANGLE360);
    //		_pGeoMover->setRyMoveAngleVelocity(2000);
    //		_pGeoMover->setAutoTargetRyMoveAngle(ANGLE360);
    //	}


    //ï˚å¸ì]ä∑
    if (_iMovePatternNo == 0 && _X > _X_turn) {
        if (_pGeoMover->getDistanceFromRzMoveAngleTo(0, TURN_CLOSE_TO) > 0) {
            _pGeoMover->setRzMoveAngleVelocity(4000);
        } else {
            _pGeoMover->setRzMoveAngleVelocity(-4000);
        }
        if (_pGeoMover->getDistanceFromRyMoveAngleTo(ANGLE180, TURN_CLOSE_TO) > 0) {
            _pGeoMover->setRyMoveAngleVelocity(4000);
        } else {
            _pGeoMover->setRyMoveAngleVelocity(-4000);
        }
        _pGeoMover->setAutoTargetRzMoveAngle(0);
        _pGeoMover->setAutoTargetRyMoveAngle(ANGLE180);

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
        //				pTama->_pGeoMover->setRzMoveAngle(way[i]);
        //				pTama->activateTree();
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
                pTama->_pGeoMover->setRzRyMoveAngle(-ANGLE90 + way[i], ANGLE90);
                pTama->activate();
            }
        }
        for (int i = 8; i < 16; i++) {
            pTama = (EnemyMeshShot001*)_pRotEnemyMeshShots001->obtain();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pGeoMover->setRzRyMoveAngle(-ANGLE90 - way[i], -ANGLE90);
                pTama->activate();
            }
        }

        _iMovePatternNo++;
    }

    if ( _iMovePatternNo == 1) {
        if (_Z > _Z_turn) {
            _Z -= 1000;
        } else if (_Z < _Z_turn) {
            _Z += 1000;
        }
    }

    //	if(0<_iMovePatternNo && _iMovePatternNo<20) {
    //		_iMovePatternNo++;
    //		_TRACE_(_iMovePatternNo<<"TURN ("<<_X<<","<<_Y<<","<<_Z<<") Å™("<<_pGeoMover->_vX<<","<<_pGeoMover->_vY<<","<<_pGeoMover->_vZ<<") Rz,Ry="<<_pGeoMover->_angRzMove<<","<<_pGeoMover->_angRyMove);
    //	}

    _pGeoMover->behave();
}

//void EnemyCeres::processBehavior() {
//
//	//ï˚å¸ì]ä∑
//	if (_iMovePatternNo == 0 && _X > _X_turn) {
//		_pGeoMover->setRzMoveAngle(sgn(_incZ)*-1*90000);
//		_pGeoMover->setRzMoveAngleVelocity(sgn(_incZ)*-1*3000);
//		_pGeoMover->setAutoTargetRzMoveAngle(ANGLE180);
//		_pGeoMover->setMoveVelocity(1000);
//
//		_pGeoMover->setRotAngleVelocity(AXIS_Y, sgn(_incZ)*-1*4000);
//		_pGeoMover->setAutoTargetRotAngle(AXIS_Y, ANGLE180);
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
//				pTama->_pGeoMover->setRzMoveAngle(way[i]);
//				pTama->activateTree();
//			}
//		}
//
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 1 && _pGeoMover->_auto_move_angle_rz_target_flg == false) {
//		_pGeoMover->setMoveVelocity(2000);
//		_pGeoMover->setMoveAcceleration(100);
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 2 && _X < -100000) {
//		//_TRACE_("Ceres:"<<getName()<<" (_X,_Y,_Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
//
//		_pGeoMover->setMoveVelocity(0);
//		_pGeoMover->setVzMoveVelocity(0);
//		_pGeoMover->setMoveAcceleration(0);
//		_pGeoMover->setVzMoveAcceleration(0);
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
//			_pGeoMover->setVzMoveVelocity(0);
//		}
//	} else if (_incZ < 0) {
//		if (_Z < 0) {
//			_Z = 0;
//			_pGeoMover->setVzMoveVelocity(0);
//		}
//	}
//
//	//_TRACE_("Ceres("<<_X<<","<<_Y<<","<<_Z<<")"<<_incZ <<"/"<<(_pGeoMover->_veloVzMove));
//}

void EnemyCeres::processJudgement() {
    if (isOffScreen()) {
        arigatou_sayounara();
        if (_createRotationActor) { //íeâï˙ó\ñÒ
            _pRotEnemyMeshShots001->arigatou_sayounara(60 * 5);
        }
    }
}

void EnemyCeres::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9UntransformedActor* pActor_Opponent = (GgafDx9UntransformedActor*)prm_pActor_Opponent;
    setBumpable(false);

    if (pActor_Opponent->getHeadActor()->_kind & KIND_MY) {
        GameGlobal::_dwScore += _pChecker->_iScorePoint;
    }

    arigatou_sayounara();
    if (_createRotationActor) { //íeâï˙ó\ñÒ
        _pRotEnemyMeshShots001->arigatou_sayounara(60 * 5);
    }

    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
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
