#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCeres::EnemyCeres(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "Ceres") {
    _class_name = "EnemyCeres";
    _programSP = NULL;

    _iMovePatternNo = 0;
    _pStgChecker->_iScorePoint = 100;
    //	_X = -100*1000;
    //	_Y = -100*1000;
    //	_Z = 0;

    _X = -356000; //開始座標
    _Y = 0;
    _Z = -680000;
    _X_turn = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2 - 200000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _veloBegin = 5000;


    //弾ストック作成
    _pDispatcher_EnemyMeshShots001 = NEW ActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 32; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EnemyMeshShots001->addSubLast(pEnemyMeshShot);
    }
    //きけん	GgafFactory::_pGarbageBox->_pGarbageRootActor->addSubLast(_pDispatcher_EnemyMeshShots001); //仮所属
    addSubLast(_pDispatcher_EnemyMeshShots001); //仮所属

    _createActorDispatcher = true;

    double p[][3] = {
                       { -1024000 ,  -300000 ,  680000 },
                       {  -800000 ,   300000 ,  480000 },
                       {  -200000 ,  -300000 ,  200000 },
                       {   200000 ,   300000 ,  100000 },
                       {   400000 ,        0 ,       0 },
                       {   300000 ,        0 ,       0 },
                       {   200000 ,   200000 ,       0 },
                       {   100000 ,        0 ,  200000 },
                       {        0 ,  -200000 ,       0 },
                       {  -100000 ,        0 , -200000 },
                       {   300000 ,        0 ,       0 },
                       {        0 ,   300000 ,       0 },
                       {        0 ,        0 ,  300000 },
                       {   -300000 ,        0 ,       0 },
                       {        0 ,   -300000 ,       0 },
                       {        0 ,        0 ,  -300000 },
                       {  -800000 ,        0 ,       0 }
                    };
    _programSP = NEW GgafDx9FixedVelocitySplineProgram(p, 17, 0.2, 5000);
}

EnemyCeres::EnemyCeres(const char* prm_name, ActorDispatcher* prm_pDispatcher_EnemyMeshShots001) :
    DefaultMeshEnemyActor(prm_name, "Ceres") {
    _class_name = "EnemyCeres";

    _iMovePatternNo = 0;
    _pStgChecker->_iScorePoint = 100;
    //	_X = -100*1000;
    //	_Y = -100*1000;
    //	_Z = 0;

    _X = -356000; //開始座標
    _Y = 0;
    _Z = -680000;
    _X_turn = GgafDx9Camera::_X_ScreenRight - 30000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _veloBegin = 5000;

    if (prm_pDispatcher_EnemyMeshShots001 == NULL) {
        _TRACE_("アクター発送者_pDispatcher_EnemyMeshShots001がNULL。よいのですか？");
    }
    _pDispatcher_EnemyMeshShots001 = prm_pDispatcher_EnemyMeshShots001;
    _createActorDispatcher = false;

    double p[][3] = {
                       { -1024000 ,  -300000 ,  680000 },
                       {  -800000 ,   300000 ,  480000 },
                       {  -200000 ,  -300000 ,  200000 },
                       {   200000 ,   300000 ,  100000 },
                       {   400000 ,        0 ,       0 },
                       {   300000 ,        0 ,       0 },
                       {   200000 ,   200000 ,       0 },
                       {   100000 ,        0 ,  200000 },
                       {        0 ,  -200000 ,       0 },
                       {  -100000 ,        0 , -200000 },
                       {   300000 ,        0 ,       0 },
                       {        0 ,   300000 ,       0 },
                       {        0 ,        0 ,  300000 },
                       {   -300000 ,        0 ,       0 },
                       {        0 ,   -300000 ,       0 },
                       {        0 ,        0 ,  -300000 },
                       {  -800000 ,        0 ,       0 }
                    };
    _programSP = NEW GgafDx9FixedVelocitySplineProgram(p, 17, 0.2, 5000);


}

void EnemyCeres::initialize() {
    //本来の場所へ
    getLordActor()->accept(KIND_ENEMY_SHOT_GU, (GgafMainActor*)_pDispatcher_EnemyMeshShots001->extract());

    setBumpable(true);

    //	_pMover->setMoveVelocity(1000);
    //	_pMover->_synchronize_RyFaceAngle_to_RyMoveAngle_flg = true;
    //
    //	//_pMover->setRzMoveAngleVeloRenge(-2000, 2000);
    ////	//_pMover->setRzMoveAngle(0,-100*1000,-100*1000);
    ////	_pMover->setMoveAngle(100*1000,0,-100);


    //	_incZ =  (1.0f*abs(_Z) / (GgafDx9Util::getDistance(_X, _Y, _X_turn, _Y_turn) / (_veloBegin * sgn(_Z) * -1)) );//_incZがおかしい?

//    _pMover->setMoveAngle(_X_turn, _Y_turn, _Z_turn);
//    _pMover->setMoveVelocity(_veloBegin);
    _pMover->_synchronize_RzFaceAngle_to_RzMoveAngle_flg = true;
    _pMover->_synchronize_RyFaceAngle_to_RyMoveAngle_flg = true;
    _pMover->setFaceAngleVelocity(AXIS_X, 6000);
    _pMover->setMoveVelocity(8000);




    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pStgChecker->setStatus(100, 1, 1, 1);



    _pMover->executeSplineMoveProgram(_programSP, 0);
}

void EnemyCeres::processBehavior() {

    if (VB::isBeingPressed(VB_UP)) {
        _pMover->addMoveVelocity(100);
    } else if (VB::isBeingPressed(VB_DOWN)) {
        _pMover->addMoveVelocity(-100);
    }




    //	if (_lifeframe > 5) {
    //		_TRACE_(_lifeframe << ":("<<_X<<","<<_Y<<","<<_Z<<")");
    //	}
    //
    //	if (_lifeframe == 100) {
    //		_pMover->setRyMoveAngle(0);
    //	} else if (_lifeframe == 200) {
    //		_TRACE_("_lifeframe="<<_lifeframe);
    //		//_pMover->setRyMoveAngle(ANGLE45);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE45);
    //	} else if (_lifeframe == 300) {
    ////		_pMover->setRyMoveAngle(ANGLE90);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE90);
    //	} else if (_lifeframe == 400) {
    ////		_pMover->setRyMoveAngle(ANGLE135);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE135);
    //	} else if (_lifeframe == 500) {
    ////		_pMover->setRyMoveAngle(ANGLE180);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE180);
    //	} else if (_lifeframe == 600) {
    ////		_pMover->setRyMoveAngle(ANGLE225);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE225);
    //	} else if (_lifeframe == 700) {
    ////		_pMover->setRyMoveAngle(ANGLE270);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE270);
    //	} else if (_lifeframe == 800) {
    ////		_pMover->setRyMoveAngle(ANGLE315);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE315);
    //	} else if (_lifeframe == 900) {
    ////		_pMover->setRyMoveAngle(ANGLE360);
    //		_pMover->setRyMoveAngleVelocity(2000);
    //		_pMover->setStopTarget_RyMoveAngle(ANGLE360);
    //	}


    //方向転換
    if (_iMovePatternNo == 0 && _X > _X_turn) {
//        if (_pMover->getRzMoveAngleDistance(0, TURN_CLOSE_TO) > 0) {
//            _pMover->setRzMoveAngleVelocity(4000);
//        } else {
//            _pMover->setRzMoveAngleVelocity(-4000);
//        }
//        if (_pMover->getRyMoveAngleDistance(ANGLE180, TURN_CLOSE_TO) > 0) {
//            _pMover->setRyMoveAngleVelocity(4000);
//        } else {
//            _pMover->setRyMoveAngleVelocity(-4000);
//        }
//        _pMover->setStopTarget_RzMoveAngle(0);
//        _pMover->setStopTarget_RyMoveAngle(ANGLE180);

        //弾を撃ってみる
        //		５WAY弾
        //		angle way[5] ;
        //		GgafDx9Util::getWayAngle2D(180000, 5, 10000, way);
        //		EnemyShot001* pTama;
        //		ActorDispatcher* pShots001 = GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001;
        //		for (int i = 0; i < 5; i++) {
        //			pTama = (EnemyShot001*)pShots001->employ();
        //			if (pTama != NULL) {
        //				pTama->setGeometry (_X, _Y, 0);
        //				pTama->_pMover->setRzMoveAngle(way[i]);
        //				pTama->activateTree();
        //			}
        //		}


        angle way[32];
        //GgafDx9Util::getWayAngle2D(180000, 8, 10000, way);
        GgafDx9Util::getRadiationAngle2D(0, 32, way);
        EnemyMeshShot001* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (EnemyMeshShot001*)_pDispatcher_EnemyMeshShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMoveAngle(-ANGLE90 + way[i], ANGLE90);
                pTama->activate();
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (EnemyMeshShot001*)_pDispatcher_EnemyMeshShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMoveAngle(-ANGLE90 - way[i], -ANGLE90);
                pTama->activate();
            }
        }

        _iMovePatternNo++;
    }

//    if ( _iMovePatternNo == 1) {
//        if (_Z > _Z_turn) {
//            _Z -= 1000;
//        } else if (_Z < _Z_turn) {
//            _Z += 1000;
//        }
//    }

    //	if(0<_iMovePatternNo && _iMovePatternNo<20) {
    //		_iMovePatternNo++;
    //		_TRACE_(_iMovePatternNo<<"TURN ("<<_X<<","<<_Y<<","<<_Z<<") ↑("<<_pMover->_vX<<","<<_pMover->_vY<<","<<_pMover->_vZ<<") Rz,Ry="<<_pMover->_angRzMove<<","<<_pMover->_angRyMove);
    //	}

    _pMover->behave();
}

//void EnemyCeres::processBehavior() {
//
//	//方向転換
//	if (_iMovePatternNo == 0 && _X > _X_turn) {
//		_pMover->setRzMoveAngle(sgn(_incZ)*-1*90000);
//		_pMover->setRzMoveAngleVelocity(sgn(_incZ)*-1*3000);
//		_pMover->setStopTarget_RzMoveAngle(ANGLE180);
//		_pMover->setMoveVelocity(1000);
//
//		_pMover->setFaceAngleVelocity(AXIS_Y, sgn(_incZ)*-1*4000);
//		_pMover->setStopTarget_FaceAngle(AXIS_Y, ANGLE180);
//
//		//弾を撃ってみる
//
//		angle way[10] ;
//		GgafDx9Util::getWayAngle(180000, 10, 10000, way);
//		EnemyShot001* pTama;
//		ActorDispatcher* pShots001 = GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001;
//		for (int i = 0; i < 10; i++) {
//			pTama = (EnemyShot001*)pShots001->employ();
//			if (pTama) {
//				pTama->setGeometry (_X, _Y, 0);
//				pTama->_pMover->setRzMoveAngle(way[i]);
//				pTama->activateTree();
//			}
//		}
//
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 1 && _pMover->_move_angle_rz_target_flg == false) {
//		_pMover->setMoveVelocity(2000);
//		_pMover->setMoveVeloAcceleration(100);
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 2 && _X < -100000) {
//		//_TRACE_("Ceres:"<<getName()<<" (_X,_Y,_Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
//
//		_pMover->setMoveVelocity(0);
//		_pMover->setVzMoveVelocity(0);
//		_pMover->setMoveVeloAcceleration(0);
//		_pMover->setVzMoveVeloAcceleration(0);
//		_pMover->setXYZMove(
//				5000,
//				GameGlobal::_pMyShip->_X,
//				GameGlobal::_pMyShip->_Y,
//				GameGlobal::_pMyShip->_Z
//				);
//		_iMovePatternNo++;
//	}
//	//_TRACE_("VX,VY="<<(_pMover->_vX_Move)<<","<<(_pMover->_vY_Move));
//
//	//座標に反映
//	_pMover->behave();
//	//_TRACE_("ab VX,VY="<<(_pMover->_vX_Move)<<","<<(_pMover->_vY_Move));
//	if (_incZ > 0) {
//		if (_Z > 0) {
//			_Z = 0;
//			_pMover->setVzMoveVelocity(0);
//		}
//	} else if (_incZ < 0) {
//		if (_Z < 0) {
//			_Z = 0;
//			_pMover->setVzMoveVelocity(0);
//		}
//	}
//
//	//_TRACE_("Ceres("<<_X<<","<<_Y<<","<<_Z<<")"<<_incZ <<"/"<<(_pMover->_veloVzMove));
//}

void EnemyCeres::processJudgement() {
    if (wasGone()) {
        adios();
        if (_createActorDispatcher) { //弾解放予約
            _pDispatcher_EnemyMeshShots001->adios(60 * 5);
        }
    }
}

void EnemyCeres::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9GeometricActor* pActor_Opponent = (GgafDx9GeometricActor*)prm_pActor_Opponent;
    setBumpable(false);

    if (pActor_Opponent->getHeadActor()->_kind & KIND_MY) {
        GameGlobal::_dwScore += _pStgChecker->_iScorePoint;
    }

    adios();
    if (_createActorDispatcher) { //弾解放予約
        _pDispatcher_EnemyMeshShots001->adios(60 * 5);
    }

    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
}

int EnemyCeres::wasGone() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
    DELETE_POSSIBLE_NULL(_programSP);
}
