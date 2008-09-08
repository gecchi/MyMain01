#include "stdafx.h"

StgMover::StgMover(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryMover(prm_pActor) {

	//XY平面移動方角X成分単位ベクトル = 0
	_vX_XYMove = 0;

	//XY平面移動方角Y成分単位ベクトル = 0
	_vY_XYMove = 0;

	//XY平面移動速度（XY平面移動座標増分） = 1 px/fream
	_iVelocity_XYMove = LEN_UNIT;  //1フレームにLEN_UNIT(＝1px)進む

	//XY平面移動速度上限 = 256 px/fream
	_iTopVelocity_XYMove = 256*LEN_UNIT;  //_iVelocity_XYMove が 256000(=256px) を上回る移動量であっても、強制的に座標増分は 256px に抑えられる。

	//XY平面移動速度下限 = 0   px/fream
	_iBottomVelocity_XYMove = -256*LEN_UNIT; //_iVelocity_XYMove が -256000(-256px) を下回る移動量があっても、強制的に座標増分は -256000px に抑えられる。

	//XY平面移動加速度（XY平面移動速度の増分） = 0 px/fream^2
	_iAcceleration_XYMoveVelocity = 0; //_iVelocity_XYMove の増分。デフォルトは加速無し

	//XY平面移動方角 = 0 angle
	_angXYMove = 0;	//0 angle は ３時の方向に移動

	//XY平面移動方角の角速度 = 0 angle/fream
	_angVelocity_XYMoveAngle = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。

	//XY平面移動方角の角速度上限 = +360,000 angle/fream
	_angTopVelocity_XYMoveAngle = ANGLE360;  //_angVelocity_XYMoveAngle の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する

	//XY平面移動方角の角速度下限 = -360,000 angle/fream
	_angBottomVelocity_XYMoveAngle = ANGLE360*-1; //_angVelocity_XYMoveAngle の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する

	//XY平面移動方角の角加速度 = 0 angle/fream^2
	_angAcceleration_XYMoveAngleVelocity = 0;     //_angVelocity_XYMoveAngle の増分。デフォルトは移動方角の角加速度無し

	//目標XY平面移動方角への自動制御フラグ = 無効
	_auto_xymove_angle_target_Flg = false;
	//目標のXY平面移動方角
	_angTarget_XYMove = 0;


	//XY平面移動方角に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
	_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。

	_iVelocity_ZMove = 0;         //Z軸XY平面移動速度（Z移動座標増分）＝ 0 px/fream
	_iTopVelocity_ZMove = 256*LEN_UNIT;  //Z軸XY平面移動速度上限 ＝ 256 px/fream
	_iBottomVelocity_ZMove = -256*LEN_UNIT; //Z軸XY平面移動速度下限 ＝ 256 px/fream
	_iAcceleration_ZMoveVelocity = 0;     //Z軸XY平面移動速度の加速度 ＝ 0 px/fream^2  (加速無し)

}



void StgMover::behave() {

	GgafDx9GeometryMover::behave();

	//Z軸加速度の処理
	_iVelocity_ZMove += _iAcceleration_ZMoveVelocity;
	setZMoveVelocity(_iVelocity_ZMove);


	//加速度の処理
	_iVelocity_XYMove += _iAcceleration_XYMoveVelocity;

	setXYMoveVelocity(_iVelocity_XYMove);

	//目標XY平面移動方角アングル自動制御機能使用時の場合
	if (_auto_xymove_angle_target_Flg) {

		_angVelocity_XYMoveAngle += _angAcceleration_XYMoveAngleVelocity;
		setXYMoveAngleVelocity(_angVelocity_XYMoveAngle);

		if (_angVelocity_XYMoveAngle > 0) { //反時計回りの場合
			angle angDistance = getDistanceFromXYMoveAngleTo(_angTarget_XYMove, TURN_COUNTERCLOCKWISE);
			if (_angVelocity_XYMoveAngle > angDistance) { //目標を行き過ぎてしまいそう･･･な日
				addXYMoveAngle(angDistance);
				_auto_xymove_angle_target_Flg = false; //フラグを戻して終了
			} else {
				addXYMoveAngle(_angVelocity_XYMoveAngle);
			}
		} else if (_angVelocity_XYMoveAngle < 0) { //時計回りの場合

			angle angDistance = getDistanceFromXYMoveAngleTo(_angTarget_XYMove, TURN_CLOCKWISE);
			if (_angVelocity_XYMoveAngle < angDistance) {
				addXYMoveAngle(angDistance);
				_auto_xymove_angle_target_Flg = false; //フラグを戻して終了
			} else {
				addXYMoveAngle(_angVelocity_XYMoveAngle);
			}
		} else {
			//_angVelocity_XYMoveAngle==0
			addXYMoveAngle(0);
		}
		if (_auto_xymove_angle_target_Flg == false) {
			_angTopVelocity_XYMoveAngle = ANGLE360;       //XY平面移動方角の角速度上限 ＝ 360,000 angle/fream
			_angBottomVelocity_XYMoveAngle = ANGLE360*-1;  //XY平面移動方角の角速度下限 ＝ -360,000 angle/fream
			_angAcceleration_XYMoveAngleVelocity = 0;  //XY平面移動方向角、角加速度を０へ
			setXYMoveAngleVelocity(0);               //XY平面移動方向角、角速度を０へ
		}

	} else {
		//フレーム毎のXY平面移動方角旋廻の処理
		_angVelocity_XYMoveAngle += _angAcceleration_XYMoveAngleVelocity;
		addXYMoveAngle(_angVelocity_XYMoveAngle);
	}



	//Actorに反映
	_pActor->_X += _vX_XYMove*_iVelocity_XYMove/LEN_UNIT;
	_pActor->_Y += _vY_XYMove*_iVelocity_XYMove/LEN_UNIT;
	_pActor->_Z += _iVelocity_ZMove;
}



void StgMover::setXYMoveVelocityRenge(int prm_iVelocity01_XYMove, int prm_iVelocity02_XYMove) {
	if (prm_iVelocity01_XYMove < prm_iVelocity02_XYMove) {
		_iTopVelocity_XYMove = prm_iVelocity02_XYMove;
		_iBottomVelocity_XYMove = prm_iVelocity01_XYMove;
	} else {
		_iTopVelocity_XYMove = prm_iVelocity01_XYMove;
		_iBottomVelocity_XYMove = prm_iVelocity02_XYMove;
	}
}



void StgMover::setXYMoveVelocity(int prm_iVelocity_XYMove) {
	if (prm_iVelocity_XYMove > _iTopVelocity_XYMove) {
		_iVelocity_XYMove = _iTopVelocity_XYMove;
	} else if (prm_iVelocity_XYMove < _iBottomVelocity_XYMove) {
		_iVelocity_XYMove = _iBottomVelocity_XYMove;
	} else {
		_iVelocity_XYMove = prm_iVelocity_XYMove;
	}
}

void StgMover::setXYMoveAcceleration(int prm_iAcceleration_XYMoveVelocity) {
	_iAcceleration_XYMoveVelocity = prm_iAcceleration_XYMoveVelocity;
}

void StgMover::setXYMoveAngle(int prm_tX, int prm_tY) {
	setXYMoveAngle(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void StgMover::setXYMoveAngle(angle prm_angXYMove) {
	int angSimple = prm_angXYMove;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_angXYMove = angSimple;
	_vX_XYMove = GgafDx9Util::_aCos_UnitLen[angSimple];
	_vY_XYMove = GgafDx9Util::_aSin_UnitLen[angSimple];
	if (_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg) {
		setAxisRotAngle(AXIS_Z, angSimple);
	}
}

void StgMover::addXYMoveAngle(angle prm_angDistance_XYMoveAngle) {
	angle angOffset_XYMove = prm_angDistance_XYMoveAngle;
	if (_angBottomVelocity_XYMoveAngle > prm_angDistance_XYMoveAngle) {
		angOffset_XYMove = _angBottomVelocity_XYMoveAngle;
	} else if (prm_angDistance_XYMoveAngle > _angTopVelocity_XYMoveAngle) {
		angOffset_XYMove = _angTopVelocity_XYMoveAngle;
	}
	setXYMoveAngle(_angXYMove + angOffset_XYMove);
}

void StgMover::setXYMoveAngleVelocity(angle prm_angVelocity_XYMoveAngle) {
	if (prm_angVelocity_XYMoveAngle > _angTopVelocity_XYMoveAngle) {
		_angVelocity_XYMoveAngle = _angTopVelocity_XYMoveAngle;
	} else if (prm_angVelocity_XYMoveAngle < _angBottomVelocity_XYMoveAngle) {
		_angVelocity_XYMoveAngle = _angBottomVelocity_XYMoveAngle;
	} else {
		_angVelocity_XYMoveAngle = prm_angVelocity_XYMoveAngle;
	}
}

void StgMover::setXYMoveAngleAcceleration(angle prm_angAcceleration_XYMoveAngleVelocity) {
	_angAcceleration_XYMoveAngleVelocity = prm_angAcceleration_XYMoveAngleVelocity;
}


void StgMover::setXYMoveAngleVelocityRenge(angle prm_angVelocity01_XYMoveAngle, angle prm_angVelocity02_XYMoveAngle) {
	if (prm_angVelocity01_XYMoveAngle < prm_angVelocity02_XYMoveAngle) {
		_angTopVelocity_XYMoveAngle = prm_angVelocity02_XYMoveAngle;
		_angBottomVelocity_XYMoveAngle = prm_angVelocity01_XYMoveAngle;
	} else {
		_angTopVelocity_XYMoveAngle = prm_angVelocity01_XYMoveAngle;
		_angBottomVelocity_XYMoveAngle = prm_angVelocity02_XYMoveAngle;
	}
}


void StgMover::setTargetXYMoveAngle(angle prm_angTarget_XYMove) {
	int angSimple = prm_angTarget_XYMove;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_auto_xymove_angle_target_Flg = true;
	_angTarget_XYMove = angSimple;
}

void StgMover::setTargetXYMoveAngle(int prm_tX, int prm_tY) {
	setTargetXYMoveAngle(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

angle StgMover::getDistanceFromXYMoveAngleTo(int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromXYMoveAngleTo(
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}


angle StgMover::getDistanceFromXYMoveAngleTo(angle prm_angTarget_XYMove, int prm_iWay) {
	if (prm_iWay ==  TURN_CLOSE_TO) { //近いほう回転
		if (0 <= _angXYMove && _angXYMove < ANGLE180) {
			if (0 <= prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove) {
				return -1*(_angXYMove - prm_angTarget_XYMove);
			} else if (prm_angTarget_XYMove == _angXYMove) {
				//重なってる場合
				return 0;
			} else if (_angXYMove < prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove+ANGLE180) {
				return prm_angTarget_XYMove - _angXYMove;
			} else if (prm_angTarget_XYMove == _angXYMove+ANGLE180) {
				//正反対を向いている（＝距離は等しい）
				//仕方ないので正の値とする。
				return ANGLE180;
			} else if (_angXYMove+ANGLE180 < prm_angTarget_XYMove && prm_angTarget_XYMove <= ANGLE360) {
				return -1*(_angXYMove+(ANGLE360 - prm_angTarget_XYMove));
			} else {
				//おかしい
				_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
				throw_GgafCriticalException("StgMover::behave() XY平面移動方角アングル値か、ターゲットアングル値が範囲外です(1)。");
			}
		} else if(ANGLE180 <= _angXYMove && _angXYMove <= ANGLE360) {
			if (0 <= prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove-ANGLE180) {
				return ANGLE360 - _angXYMove + prm_angTarget_XYMove;
			} else if (prm_angTarget_XYMove == _angXYMove-ANGLE180) {
				//正反対を向いている（＝距離は等しい）
				//仕方ないので正の値とする。
				return ANGLE180;
			} else if (_angXYMove-ANGLE180 < prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove) {
				return -1*(_angXYMove - prm_angTarget_XYMove);
			} else if (_angXYMove == prm_angTarget_XYMove) {
				//重なってる場合
				return 0;
			} else if (_angXYMove < prm_angTarget_XYMove && prm_angTarget_XYMove <= ANGLE360) {
				return prm_angTarget_XYMove - _angXYMove;
			} else {
				//おかしい
				_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
				throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY平面移動方角アングル値か、ターゲットアングル値が範囲外です(2)。");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
		if (0 <= _angXYMove && _angXYMove < prm_angTarget_XYMove) {
			return (prm_angTarget_XYMove - _angXYMove);
		} else if (prm_angTarget_XYMove < _angXYMove && _angXYMove < ANGLE360) {
			return ANGLE360 - _angXYMove + prm_angTarget_XYMove;
		} else if (_angXYMove == prm_angTarget_XYMove) {
			//重なってる場合
			return 0;
		}else {
			//おかしい
			_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
			throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY平面移動方角アングル値か、ターゲットアングル値が範囲外です(3)。");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //時計回りの場合
		if (0 <= _angXYMove && _angXYMove < prm_angTarget_XYMove) {
			return -1*( _angXYMove + ANGLE360 - prm_angTarget_XYMove);
		} else if (prm_angTarget_XYMove < _angXYMove && _angXYMove < ANGLE360) {
			return -1*(_angXYMove - prm_angTarget_XYMove);
		} else if (_angXYMove == prm_angTarget_XYMove) {
			//重なってる場合
			return 0;
		}else {
			//おかしい
			_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
			throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY平面移動方角アングル値か、ターゲットアングル値が範囲外です(4)。");
		}
	}

	_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
	throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() 何故かしら角の距離が求めれません。(1)");

}

void StgMover::setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove) {
	if (prm_iVelocity01_ZMove < prm_iVelocity02_ZMove) {
		_iTopVelocity_ZMove = prm_iVelocity02_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity01_ZMove;
	} else {
		_iTopVelocity_ZMove = prm_iVelocity01_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity02_ZMove;
	}
}



void StgMover::setZMoveVelocity(int prm_iVelocity_ZMove) {
	if (prm_iVelocity_ZMove > _iTopVelocity_ZMove) {
		_iVelocity_ZMove = _iTopVelocity_ZMove;
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
