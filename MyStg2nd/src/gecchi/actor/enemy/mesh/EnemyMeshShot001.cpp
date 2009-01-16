#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMeshShot001::EnemyMeshShot001(string prm_name, string prm_model) : DefaultMeshEnemyActor(prm_name, prm_model) {
	_class_name = "EnemyMeshShot001";

	declareStop();

	/** 出現時の初速 */
	_iMoveVelocity_1st = 10000;
	/** 出現時の加速度（負で遅くなる） */
	_iMoveAcceleration_1st = -150;
	/** 自身が出現してから、時機の方向に方向転換を開始するフレーム */
	_dwFrame_TurnBegin = 50;
	/** 移動速度上限 */
	_iMoveVelocity_Top = 30000;
	/** 最低保証移動速度 */
	_iMoveVelocity_Bottom = 0;
	/** 方向転換に費やすことができるフレーム数 */
	_dwFrameInterval_Turn = 100;
	/** 方向転換中の角速度アングル値 */
	_angVelocity_Turn = 5000;
	/** 方向転換を開始（_dwFrame_TurnBegin）から再設定される加速度 */
	_iMoveAcceleration_2nd = 300;

	_dwFrame_switchedToPlay = 0;
}

void EnemyMeshShot001::initialize() {
	_pGeoMover -> setXMoveVelocityRenge(_iMoveVelocity_Top, _iMoveVelocity_Bottom);
	_pGeoMover -> _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = true;
	_pGeoMover -> _synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = true;


	_pChecker -> useHitAreaBoxNum(1);
	_pChecker -> setHitAreaBox(0, -10000, -10000, 10000, 10000);
	setBumpableAlone(true);
}



void EnemyMeshShot001::processBehavior() {
	if (switchedToPlay()) {
		//出現時
		_pGeoMover -> setMoveVelocity(_iMoveVelocity_1st);
		_pGeoMover -> setMoveAcceleration(_iMoveAcceleration_1st);

		_dwFrame_switchedToPlay = 0;
		setBumpableAlone(true);
	} else {

//		_pGeoMover->setMoveAngle(
//				GameGlobal::_pMyShip->_X,
//				GameGlobal::_pMyShip->_Y,
//				GameGlobal::_pMyShip->_Z
//				);

//		angle angRz_Target;
//		angle angRy_Target;
//		double dummy1,dummy2,dummy3;
//		GgafDx9Util::getRotAngleZY(
//				GameGlobal::_pMyShip->_X - _X,
//				GameGlobal::_pMyShip->_Y - _Y,
//				GameGlobal::_pMyShip->_Z - _Z,
//				angRz_Target,
//				angRy_Target
//				);
//		_pGeoMover -> setMoveAngleRz(angRz_Target);
//		_pGeoMover -> setMoveAngleRy(angRy_Target);

		_dwFrame_switchedToPlay++;
		//方向転換開始
		if (_dwFrame_switchedToPlay == _dwFrame_TurnBegin) {
			angle angRz_Target;
			angle angRy_Target;
			GgafDx9Util::getRotAngleZY(
					GameGlobal::_pMyShip->_X - _X,
					GameGlobal::_pMyShip->_Y - _Y,
					GameGlobal::_pMyShip->_Z - _Z,
					angRz_Target,
					angRy_Target
				);
			if (_pGeoMover->getDistanceFromMoveAngleRzTo(angRz_Target, TURN_CLOSE_TO) > 0) {
				_pGeoMover -> setMoveAngleRzVelocity(_angVelocity_Turn);
			} else {
				_pGeoMover -> setMoveAngleRzVelocity(-1 * _angVelocity_Turn);
			}
			if (_pGeoMover->getDistanceFromMoveAngleRyTo(angRy_Target, TURN_CLOSE_TO) > 0) {
				_pGeoMover -> setMoveAngleRyVelocity(_angVelocity_Turn);
			} else {
				_pGeoMover -> setMoveAngleRyVelocity(-1 * _angVelocity_Turn);
			}
			_pGeoMover -> setTargetMoveAngleRy(angRy_Target);
			_pGeoMover -> setTargetMoveAngleRz(angRz_Target);

			_pGeoMover -> setMoveAcceleration(_iMoveAcceleration_2nd);
		}


		//方向転換終了
		if (_dwFrame_switchedToPlay == _dwFrame_TurnBegin+_dwFrameInterval_Turn) {
			_pGeoMover -> setMoveAngleRzVelocity(0);
			_pGeoMover -> setMoveAngleRyVelocity(0);
			_pGeoMover -> _auto_move_angle_ry_target_Flg = false;
			_pGeoMover -> _auto_move_angle_rz_target_Flg = false;
		}


	}



	//nextAnimationFrame();
	//座標に反映
	_pGeoMover -> behave();

}

void EnemyMeshShot001::processJudgement() {
	if (isOffScreen()) {
		declareStop();
		//declareFinishLife();
	}
}

bool EnemyMeshShot001::isOffScreen() {
	if (_X < _X_OffScreenLeft) {
		return true;
	} else {
		if (_X > _X_OffScreenRight) {
			return true;
		} else {
			if (_Y > _Y_OffScreenTop) {
				return true;
			} else {
				if (_Y < _Y_OffScreenBottom) {
					return true;
				} else {
					if (_Z < GgafDx9God::_dCamZ*LEN_UNIT*10) {
						return true;
					} else {
						if (_Z > -1* GgafDx9God::_dCamZ*LEN_UNIT*10) {
							return true;
						} else {
							return false;
						}
					}
				}
			}
		}
	}
}

void EnemyMeshShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
	//_TRACE_("EnemyMeshShot001ヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	setBumpableAlone(false);
	declareStop();
	EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
	if (pExplo001 != NULL) {
		pExplo001->setGeometry(this);
		pExplo001->declarePlay();
	}
}


EnemyMeshShot001::~EnemyMeshShot001() {
}
