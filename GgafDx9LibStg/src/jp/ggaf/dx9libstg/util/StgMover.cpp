#include "stdafx.h"

StgMover::StgMover(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryMover(prm_pActor) {

	//キャラの移動方角単位ベクトル
	_vX = _vY = _vZ = 0.0;

	//移動方角のZ軸回転
	_angRz_Move = 0;
	//移動方角のY軸回転
	_angRy_Move = 0;

	//Rz平面移動方角X成分単位ベクトル = 0
//	_vX_Move = 0;

	//Rz平面移動方角Y成分単位ベクトル = 0
//	_vY_Move = 0;

	//移動速度
	_iVelocity_Move = 0;

	//移動速度上限 = 256 px/fream
	_iTopAngVelocity_Move = 256*LEN_UNIT;  //_iVelocity_Move が 256000(=256px) を上回る移動量であっても、強制的に座標増分は 256px に抑えられる。

	//移動速度下限 = 0   px/fream
	_iBottomVelocity_Move = -256*LEN_UNIT; //_iVelocity_Move が -256000(-256px) を下回る移動量があっても、強制的に座標増分は -256000px に抑えられる。

	//移動加速度（移動速度の増分） = 0 px/fream^2
	_iAcceleration_MoveVelocity = 0; //_iVelocity_Move の増分。デフォルトは加速無し

	//Rz平面移動方角 = 0 angle
	//_angRz_Move = 0;	//0 angle は ３時の方向に移動

	//Rz平面移動方角の角速度 = 0 angle/fream
	_angVelocity_MoveAngleRz = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。

	//Rz平面移動方角の角速度上限 = +360,000 angle/fream
	_angTopAngVelocity_MoveAngleRz = ANGLE360;  //_angVelocity_MoveAngleRz の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する

	//Rz平面移動方角の角速度下限 = -360,000 angle/fream
	_angBottomVelocity_MoveAngleRz = ANGLE360*-1; //_angVelocity_MoveAngleRz の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する

	//Rz平面移動方角の角加速度 = 0 angle/fream^2
	_angAcceleration_MoveAngleRzVelocity = 0;     //_angVelocity_MoveAngleRz の増分。デフォルトは移動方角の角加速度無し

	//目標Rz平面移動方角への自動制御フラグ = 無効
	_auto_move_angle_rz_target_Flg = false;
	//目標のRz平面移動方角
	_angRzTarget_Move = 0;
	//目標のRz平面移動方角自動停止機能が有効になる回転方向
	_auto_move_angle_rz_target_allow_way = TURN_BOTH;
	//目標のRz平面移動方角自動停止機能が有効になる移動方角角速度(角速度正負共通)
	_auto_move_angle_rz_target_allow_velocity = ANGLE180;

	//Rz平面移動方角に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
	_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。

	_iVelocity_ZMove = 0;         //Z軸Rz平面移動速度（Z移動座標増分）＝ 0 px/fream
	_iTopAngVelocity_ZMove = 256*LEN_UNIT;  //Z軸Rz平面移動速度上限 ＝ 256 px/fream
	_iBottomVelocity_ZMove = -256*LEN_UNIT; //Z軸Rz平面移動速度下限 ＝ 256 px/fream
	_iAcceleration_ZMoveVelocity = 0;     //Z軸Rz平面移動速度の加速度 ＝ 0 px/fream^2  (加速無し)

}



void StgMover::behave() {

	GgafDx9GeometryMover::behave();

	//Z軸加速度の処理
	_iVelocity_ZMove += _iAcceleration_ZMoveVelocity;
	setZMoveVelocity(_iVelocity_ZMove);

	//加速度の処理
	_iVelocity_Move += _iAcceleration_MoveVelocity;

	setMoveVelocity(_iVelocity_Move);

	//目標Rz平面移動方角アングル自動停止機能使用時の場合
	if (_auto_move_angle_rz_target_Flg) {

		_angVelocity_MoveAngleRz += _angAcceleration_MoveAngleRzVelocity;
		setMoveAngleRzVelocity(_angVelocity_MoveAngleRz);

		if (_angVelocity_MoveAngleRz > 0) { //反時計回りの場合
			angle angDistance = getDistanceFromMoveAngleRzTo(_angRzTarget_Move, TURN_COUNTERCLOCKWISE);
			if (_angVelocity_MoveAngleRz > angDistance &&
				_auto_move_angle_rz_target_allow_way != TURN_CLOCKWISE &&
				_auto_move_angle_rz_target_allow_velocity >= _angVelocity_MoveAngleRz)
			{ //目標を行き過ぎてしまいそう･･･な日
				addMoveAngleRz(angDistance);
				_auto_move_angle_rz_target_Flg = false; //フラグを戻して終了
			} else {
				addMoveAngleRz(_angVelocity_MoveAngleRz);
			}
		} else if (_angVelocity_MoveAngleRz < 0) { //時計回りの場合

			angle angDistance = getDistanceFromMoveAngleRzTo(_angRzTarget_Move, TURN_CLOCKWISE);
			if (_angVelocity_MoveAngleRz < angDistance &&
				_auto_move_angle_rz_target_allow_way != TURN_COUNTERCLOCKWISE &&
				-1*_auto_move_angle_rz_target_allow_velocity <= _angVelocity_MoveAngleRz)
			{
				addMoveAngleRz(angDistance);
				_auto_move_angle_rz_target_Flg = false; //フラグを戻して終了
			} else {
				addMoveAngleRz(_angVelocity_MoveAngleRz);
			}
		} else {
			//_angVelocity_MoveAngleRz==0
			addMoveAngleRz(0);
		}
		if (_auto_move_angle_rz_target_Flg == false) {
			_angTopAngVelocity_MoveAngleRz = ANGLE360;       //Rz平面移動方角の角速度上限 ＝ 360,000 angle/fream
			_angBottomVelocity_MoveAngleRz = ANGLE360*-1;  //Rz平面移動方角の角速度下限 ＝ -360,000 angle/fream
			_angAcceleration_MoveAngleRzVelocity = 0;  //Rz平面移動方向角、角加速度を０へ
			setMoveAngleRzVelocity(0);               //Rz平面移動方向角、角速度を０へ
		}

	} else {
		//if (_angAcceleration_MoveAngleRzVelocity != 0) {
			//フレーム毎のRz平面移動方角旋廻の処理
			_angVelocity_MoveAngleRz += _angAcceleration_MoveAngleRzVelocity;
			addMoveAngleRz(_angVelocity_MoveAngleRz);
		//}
	}



	//Actorに反映
	_pActor->_X += _vX*_iVelocity_Move;
	_pActor->_Y += _vY*_iVelocity_Move;
	_pActor->_Z += (_vZ*_iVelocity_Move + _iVelocity_ZMove);
}



void StgMover::setMoveVelocityRenge(int prm_iVelocity01_Move, int prm_iVelocity02_Move) {
	if (prm_iVelocity01_Move < prm_iVelocity02_Move) {
		_iTopAngVelocity_Move = prm_iVelocity02_Move;
		_iBottomVelocity_Move = prm_iVelocity01_Move;
	} else {
		_iTopAngVelocity_Move = prm_iVelocity01_Move;
		_iBottomVelocity_Move = prm_iVelocity02_Move;
	}
	setMoveVelocity(_iVelocity_Move); //再設定して範囲内に補正
}



void StgMover::setMoveVelocity(int prm_iVelocity_Move) {
	if (prm_iVelocity_Move > _iTopAngVelocity_Move) {
		_iVelocity_Move = _iTopAngVelocity_Move;
	} else if (prm_iVelocity_Move < _iBottomVelocity_Move) {
		_iVelocity_Move = _iBottomVelocity_Move;
	} else {
		_iVelocity_Move = prm_iVelocity_Move;
	}
}

void StgMover::setMoveAcceleration(int prm_iAcceleration_MoveVelocity) {
	_iAcceleration_MoveVelocity = prm_iAcceleration_MoveVelocity;
}

void StgMover::setMoveAngleRz(int prm_tX, int prm_tY) {
	setMoveAngleRz(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void StgMover::setXYZMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
	GgafDx9Util::getRotAngleZY(
			prm_tX - _pActor->_X,
			prm_tY - _pActor->_Y,
			prm_tZ - _pActor->_Z,
			_vX,
			_vY,
			_vZ,
			_angRz_Move,
			_angRy_Move
		);
}

void StgMover::setMoveAngleRz(angle prm_angle) {
	_angRz_Move = simplifyAngle(prm_angle);
	//0でいいのか！！！だめだ
	GgafDx9Util::getNormalizeVectorZY(_angRz_Move, _angRy_Move, _vX, _vY, _vZ);

	if (_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg) {
		setAxisRotAngle(AXIS_Z, _angRz_Move);
	}
}

void StgMover::setMoveAngleRy(angle prm_angle) {
	_angRy_Move = simplifyAngle(prm_angle);
	//0でいいのか！！！だめだ
	GgafDx9Util::getNormalizeVectorZY(_angRz_Move, _angRy_Move, _vX, _vY, _vZ);
}


void StgMover::addMoveAngleRz(angle prm_angDistance_MoveAngleRz) {
	angle angOffset_Move = prm_angDistance_MoveAngleRz;
	if (_angBottomVelocity_MoveAngleRz > prm_angDistance_MoveAngleRz) {
		angOffset_Move = _angBottomVelocity_MoveAngleRz;
	} else if (prm_angDistance_MoveAngleRz > _angTopAngVelocity_MoveAngleRz) {
		angOffset_Move = _angTopAngVelocity_MoveAngleRz;
	}
	setMoveAngleRz(_angRz_Move + angOffset_Move);
}

void StgMover::setMoveAngleRzVelocity(angle prm_angVelocity_MoveAngleRz) {
	if (prm_angVelocity_MoveAngleRz > _angTopAngVelocity_MoveAngleRz) {
		_angVelocity_MoveAngleRz = _angTopAngVelocity_MoveAngleRz;
	} else if (prm_angVelocity_MoveAngleRz < _angBottomVelocity_MoveAngleRz) {
		_angVelocity_MoveAngleRz = _angBottomVelocity_MoveAngleRz;
	} else {
		_angVelocity_MoveAngleRz = prm_angVelocity_MoveAngleRz;
	}
}

void StgMover::setMoveAngleRzAcceleration(angle prm_angAcceleration_MoveAngleRzVelocity) {
	_angAcceleration_MoveAngleRzVelocity = prm_angAcceleration_MoveAngleRzVelocity;
}


void StgMover::setMoveAngleRzVelocityRenge(angle prm_angVelocity01_MoveAngleRz, angle prm_angVelocity02_MoveAngleRz) {
	if (prm_angVelocity01_MoveAngleRz < prm_angVelocity02_MoveAngleRz) {
		_angTopAngVelocity_MoveAngleRz = prm_angVelocity02_MoveAngleRz;
		_angBottomVelocity_MoveAngleRz = prm_angVelocity01_MoveAngleRz;
	} else {
		_angTopAngVelocity_MoveAngleRz = prm_angVelocity01_MoveAngleRz;
		_angBottomVelocity_MoveAngleRz = prm_angVelocity02_MoveAngleRz;
	}
	setMoveAngleRzVelocity(_angVelocity_MoveAngleRz); //再設定して範囲内に補正
}


void StgMover::setTargetMoveAngleRz(angle prm_angRzTarget_Move, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	_auto_move_angle_rz_target_Flg = true;
	_angRzTarget_Move = simplifyAngle(prm_angRzTarget_Move);
	_auto_move_angle_rz_target_allow_way = prm_iAllowRotWay;
	_auto_move_angle_rz_target_allow_velocity = prm_angAllowVelocity;
}

void StgMover::setTargetMoveAngleRzV(int prm_tX, int prm_tY, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	setTargetMoveAngleRz(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_iAllowRotWay);
}

angle StgMover::getDistanceFromMoveAngleRzTo(int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromMoveAngleRzTo(
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}


angle StgMover::getDistanceFromMoveAngleRzTo(angle prm_angRzTarget_Move, int prm_iWay) {
	angle angTarget_Move = simplifyAngle(prm_angRzTarget_Move);
	if (prm_iWay ==  TURN_CLOSE_TO) { //近いほう回転
		if (0 <= _angRz_Move && _angRz_Move < ANGLE180) {
			if (0 <= angTarget_Move && angTarget_Move < _angRz_Move) {
				return -1*(_angRz_Move - angTarget_Move);
			} else if (angTarget_Move == _angRz_Move) {
				//重なってる場合
				return 0;
			} else if (_angRz_Move < angTarget_Move && angTarget_Move < _angRz_Move+ANGLE180) {
				return angTarget_Move - _angRz_Move;
			} else if (angTarget_Move == _angRz_Move+ANGLE180) {
				//正反対を向いている（＝距離は等しい）
				//仕方ないので正の値とする。
				return ANGLE180;
			} else if (_angRz_Move+ANGLE180 < angTarget_Move && angTarget_Move <= ANGLE360) {
				return -1*(_angRz_Move+(ANGLE360 - angTarget_Move));
			} else {
				//おかしい
				_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::behave() Rz平面移動方角アングル値か、ターゲットアングル値が範囲外です(1)。");
			}
		} else if(ANGLE180 <= _angRz_Move && _angRz_Move <= ANGLE360) {
			if (0 <= angTarget_Move && angTarget_Move < _angRz_Move-ANGLE180) {
				return ANGLE360 - _angRz_Move + angTarget_Move;
			} else if (angTarget_Move == _angRz_Move-ANGLE180) {
				//正反対を向いている（＝距離は等しい）
				//仕方ないので正の値とする。
				return ANGLE180;
			} else if (_angRz_Move-ANGLE180 < angTarget_Move && angTarget_Move < _angRz_Move) {
				return -1*(_angRz_Move - angTarget_Move);
			} else if (_angRz_Move == angTarget_Move) {
				//重なってる場合
				return 0;
			} else if (_angRz_Move < angTarget_Move && angTarget_Move <= ANGLE360) {
				return angTarget_Move - _angRz_Move;
			} else {
				//おかしい
				_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() Rz平面移動方角アングル値か、ターゲットアングル値が範囲外です(2)。");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
		if (0 <= _angRz_Move && _angRz_Move < angTarget_Move) {
			return (angTarget_Move - _angRz_Move);
		} else if (angTarget_Move < _angRz_Move && _angRz_Move < ANGLE360) {
			return ANGLE360 - _angRz_Move + angTarget_Move;
		} else if (_angRz_Move == angTarget_Move) {
			//重なってる場合
			return 0;
		}else {
			//おかしい
			_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() Rz平面移動方角アングル値か、ターゲットアングル値が範囲外です(3)。");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //時計回りの場合
		if (0 <= _angRz_Move && _angRz_Move < angTarget_Move) {
			return -1*( _angRz_Move + ANGLE360 - angTarget_Move);
		} else if (angTarget_Move < _angRz_Move && _angRz_Move < ANGLE360) {
			return -1*(_angRz_Move - angTarget_Move);
		} else if (_angRz_Move == angTarget_Move) {
			//重なってる場合
			return 0;
		}else {
			//おかしい
			_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() Rz平面移動方角アングル値か、ターゲットアングル値が範囲外です(4)。");
		}
	}

	_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
	throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() 何故かしら角の距離が求めれません。(1)");

}

void StgMover::setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove) {
	if (prm_iVelocity01_ZMove < prm_iVelocity02_ZMove) {
		_iTopAngVelocity_ZMove = prm_iVelocity02_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity01_ZMove;
	} else {
		_iTopAngVelocity_ZMove = prm_iVelocity01_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity02_ZMove;
	}
	setZMoveVelocity(_iVelocity_ZMove); //再設定して範囲内に補正
}


void StgMover::setZMoveVelocity(int prm_iVelocity_ZMove) {
	if (prm_iVelocity_ZMove > _iTopAngVelocity_ZMove) {
		_iVelocity_ZMove = _iTopAngVelocity_ZMove;
	} else if (prm_iVelocity_ZMove < _iBottomVelocity_ZMove) {
		_iVelocity_ZMove = _iBottomVelocity_ZMove;
	} else {
		_iVelocity_ZMove = prm_iVelocity_ZMove;
	}
}

void StgMover::setZMoveAcceleration(int prm_iAcceleration_ZMoveVelocity) {
	_iAcceleration_ZMoveVelocity = prm_iAcceleration_ZMoveVelocity;
}


StgMover::~StgMover() {
}
