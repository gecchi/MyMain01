#include "stdafx.h"

GgafDx9GeometryMover::GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor) {
	_pActor = prm_pActor;

	for (int i = 0; i < 3; i++) { // i=0:X軸、1:Y軸、2:Z軸 を表す

		//軸回転方角
		_angAxisRot[i] = 0; //0 angle は ３時の方角を向いている

		//軸回転方角の角速度（軸回転方角値の増分）= 0 angle/fream
		_angVelocity_AxisRotAngle[i]  = 0; //1フレームに加算される軸回転方角の角増分。デフォルトは軸回転方角の角増分無し、つまり振り向き無し。

		//軸回転方角の角速度上限 ＝ 360,000 angle/fream
		_angTopAngVelocity_AxisRotAngle[i]  = ANGLE360; //_angVelocity_AxisRotAngle[n] の増分の上限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する

		//軸回転方角の角速度下限 ＝ -360,000 angle/fream
		_angBottomVelocity_AxisRotAngle[i]  = ANGLE360*-1;  //_angVelocity_AxisRotAngle[n] の増分の下限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する

		//軸回転方角の角加速度（角速度の増分） ＝ 0 angle/fream^2
		_angAcceleration_AxisRotAngleVelocity[i]  = 0; //_angVelocity_AxisRotAngle[n] の増分。デフォルトは軸回転方角の角加速度無し

		//目標軸回転方角への自動制御フラグ = 無効
		_auto_rot_angle_target_Flg[i] = false;
		//目標の軸回転方角
		_angTarget_AxisRot[i] = 0; //目標軸回転方角への自動制御フラグ = 無効、の場合は無意味
		//目標の軸回転方角自動停止機能が有効になる回転方向
		_auto_rot_angle_target_allow_way[i] = TURN_BOTH;
		//目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通）
		_auto_rot_angle_target_allow_velocity[i] = ANGLE180;
	}

}

void GgafDx9GeometryMover::behave() {
	static angle angDistance;
	for (int i = 0; i < 3; i++) {
		if (_auto_rot_angle_target_Flg[i]) {
			_angVelocity_AxisRotAngle[i] += _angAcceleration_AxisRotAngleVelocity[i];
			setAxisRotAngleVelocity(i, _angVelocity_AxisRotAngle[i]);

			if (_angVelocity_AxisRotAngle[i] > 0) { //反時計回りの場合
				angDistance = getDistanceFromAxisRotAngleTo(i, _angTarget_AxisRot[i], TURN_COUNTERCLOCKWISE);
				if (_angVelocity_AxisRotAngle[i] > angDistance &&
					_auto_rot_angle_target_allow_way[i] != TURN_CLOCKWISE &&
					_auto_rot_angle_target_allow_velocity[i] >= _angVelocity_AxisRotAngle[i])
				{
					addAxisRotAngle(i, angDistance);
					_auto_rot_angle_target_Flg[i] = false; //フラグを戻して終了
				} else {
					addAxisRotAngle(i, _angVelocity_AxisRotAngle[i]);
				}
			} else if (_angVelocity_AxisRotAngle[i] < 0) { //時計回りの場合
				angDistance = getDistanceFromAxisRotAngleTo(i, _angTarget_AxisRot[i], TURN_CLOCKWISE);
				if (_angVelocity_AxisRotAngle[i] < angDistance &&
					_auto_rot_angle_target_allow_way[i] != TURN_COUNTERCLOCKWISE &&
					-1*_auto_rot_angle_target_allow_velocity[i] <= _angVelocity_AxisRotAngle[i])
				{ //目標を行き過ぎてしまいそう･･･な日
					addAxisRotAngle(i, angDistance);
					_auto_rot_angle_target_Flg[i] = false; //フラグを戻して終了
				} else {
					addAxisRotAngle(i, _angVelocity_AxisRotAngle[i]);
				}
			} else {
				//_angVelocity_AxisRotAngle[i] == 0
				addAxisRotAngle(i, 0);
			}
			if (_auto_rot_angle_target_Flg[i] == false) {
				//目標方向に到達した時の処理
				_angTopAngVelocity_AxisRotAngle[i]  = ANGLE360;  //軸回転方角の角速度上限 ＝ 360,000 angle/fream
				_angBottomVelocity_AxisRotAngle[i]  = ANGLE360*-1;  //軸回転方角の角速度下限 ＝ -360,000 angle/fream
				_angAcceleration_AxisRotAngleVelocity[i] = 0;    //軸回転方向角、角速度を０へ
				setAxisRotAngleVelocity(i, 0);                //軸回転方向角、角加速度を０へ
			}

		} else {
			//if (_angAcceleration_AxisRotAngleVelocity[i] != 0) {
				//フレーム毎の軸回転方角旋廻の処理
				_angVelocity_AxisRotAngle[i] += _angAcceleration_AxisRotAngleVelocity[i];
				addAxisRotAngle(i, _angVelocity_AxisRotAngle[i]);
			//}
		}
	}

	//Actorに反映
	_pActor->_RX = _angAxisRot[AXIS_X];
	_pActor->_RY = _angAxisRot[AXIS_Y];
	_pActor->_RZ = _angAxisRot[AXIS_Z];

}


angle GgafDx9GeometryMover::simplifyAngle(angle prm_ang) {
	angle angSimple = prm_ang;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	return angSimple;
}


void GgafDx9GeometryMover::setAxisRotAngle(int prm_iAxis, angle prm_angAxisRot) {
	_angAxisRot[prm_iAxis] = simplifyAngle(prm_angAxisRot);
}

void GgafDx9GeometryMover::addAxisRotAngle(int prm_iAxis, angle prm_angDistance_AxisRotAngle) {
	angle angOffsetrot_AxisRotAngle = prm_angDistance_AxisRotAngle;
	if (_angBottomVelocity_AxisRotAngle[prm_iAxis] > prm_angDistance_AxisRotAngle) {
		angOffsetrot_AxisRotAngle = _angBottomVelocity_AxisRotAngle[prm_iAxis];
	} else if (prm_angDistance_AxisRotAngle > _angTopAngVelocity_AxisRotAngle[prm_iAxis]) {
		angOffsetrot_AxisRotAngle = _angTopAngVelocity_AxisRotAngle[prm_iAxis];
	}
	setAxisRotAngle(prm_iAxis, _angAxisRot[prm_iAxis] + angOffsetrot_AxisRotAngle);
}

void GgafDx9GeometryMover::setAxisRotAngleVelocity(int prm_iAxis, angle prm_angVelocity_AxisRotAngle) {
	if (prm_angVelocity_AxisRotAngle > _angTopAngVelocity_AxisRotAngle[prm_iAxis]) {
		_angVelocity_AxisRotAngle[prm_iAxis] = _angTopAngVelocity_AxisRotAngle[prm_iAxis];
	} else if (prm_angVelocity_AxisRotAngle < _angBottomVelocity_AxisRotAngle[prm_iAxis]) {
		_angVelocity_AxisRotAngle[prm_iAxis] = _angBottomVelocity_AxisRotAngle[prm_iAxis];
	} else {
		_angVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity_AxisRotAngle;
	}
}

void GgafDx9GeometryMover::setAxisRotAngleVelocityRenge(int prm_iAxis, angle prm_angVelocity01_AxisRotAngle, angle prm_angVelocity02_AxisRotAngle) {
	if (prm_angVelocity01_AxisRotAngle < prm_angVelocity02_AxisRotAngle) {
		_angTopAngVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity02_AxisRotAngle;
		_angBottomVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity01_AxisRotAngle;
	} else {
		_angTopAngVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity01_AxisRotAngle;
		_angBottomVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity02_AxisRotAngle;
	}
	setAxisRotAngleVelocity(prm_iAxis, _angVelocity_AxisRotAngle[prm_iAxis]); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setAxisRotAngleAcceleration(int prm_iAxis, angle prm_angAcceleration_AxisRotAngleVelocity) {
	_angAcceleration_AxisRotAngleVelocity[prm_iAxis] = prm_angAcceleration_AxisRotAngleVelocity;
}

void GgafDx9GeometryMover::setTargetAxisRotAngleV(int prm_iAxis, int prm_tX, int prm_tY, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	setTargetAxisRotAngle(prm_iAxis, _angTarget_AxisRot[prm_iAxis] = GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_iAllowRotWay, prm_angAllowVelocity);
}


void GgafDx9GeometryMover::setTargetAxisRotAngle(int prm_iAxis, angle prm_angTarget_AxisRot, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	_auto_rot_angle_target_Flg[prm_iAxis] = true;
	_angTarget_AxisRot[prm_iAxis] = simplifyAngle(prm_angTarget_AxisRot);
	_auto_rot_angle_target_allow_way[prm_iAxis] = prm_iAllowRotWay;
	_auto_rot_angle_target_allow_velocity[prm_iAxis] = prm_angAllowVelocity;
}


angle GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo(int prm_iAxis, int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromAxisRotAngleTo(
			   prm_iAxis,
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}

angle GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo(int prm_iAxis, angle prm_angTarget_AxisRot, int prm_iWay) {
	angle angTarget_AxisRot = simplifyAngle(prm_angTarget_AxisRot);
	if (prm_iWay == TURN_CLOSE_TO) { //近いほう回転
		if (0 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < ANGLE180) {
			if (0 <= angTarget_AxisRot && angTarget_AxisRot < _angAxisRot[prm_iAxis]) {
				return -1*(_angAxisRot[prm_iAxis] - angTarget_AxisRot);
			} else if (angTarget_AxisRot == _angAxisRot[prm_iAxis]) {
				//重なってる場合
				return 0;
			} else if (_angAxisRot[prm_iAxis] < angTarget_AxisRot && angTarget_AxisRot < _angAxisRot[prm_iAxis]+ANGLE180) {
				return angTarget_AxisRot - _angAxisRot[prm_iAxis];
			} else if (angTarget_AxisRot == _angAxisRot[prm_iAxis]+ANGLE180) {
				//正反対を向いている（＝距離は等しい）
				//仕方ないので正の値とする。
				return ANGLE180;
			} else if (_angAxisRot[prm_iAxis]+ANGLE180 < angTarget_AxisRot && angTarget_AxisRot <= ANGLE360) {
				return -1*(_angAxisRot[prm_iAxis]+(ANGLE360 - angTarget_AxisRot));
			} else {
				//おかしい
				_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/angTarget_AxisRot=" << angTarget_AxisRot);
				throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。");
			}
		} else if(ANGLE180 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] <= ANGLE360) {
			if (0 <= angTarget_AxisRot && angTarget_AxisRot < _angAxisRot[prm_iAxis]-ANGLE180) {
				return ANGLE360 - _angAxisRot[prm_iAxis] + angTarget_AxisRot;
			} else if (angTarget_AxisRot == _angAxisRot[prm_iAxis]-ANGLE180) {
				//正反対を向いている（＝距離は等しい）
				//仕方ないので正の値とする。
				return ANGLE180;
			} else if (_angAxisRot[prm_iAxis]-ANGLE180 < angTarget_AxisRot && angTarget_AxisRot < _angAxisRot[prm_iAxis]) {
				return -1*(_angAxisRot[prm_iAxis] - angTarget_AxisRot);
			} else if (_angAxisRot[prm_iAxis] == angTarget_AxisRot) {
				//重なってる場合
				return 0;
			} else if (_angAxisRot[prm_iAxis] < angTarget_AxisRot && angTarget_AxisRot <= ANGLE360) {
				return angTarget_AxisRot - _angAxisRot[prm_iAxis];
			} else {
				//おかしい
				_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/angTarget_AxisRot=" << angTarget_AxisRot);
				throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
		if (0 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < angTarget_AxisRot) {
			return (angTarget_AxisRot - _angAxisRot[prm_iAxis]);
		} else if (angTarget_AxisRot < _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < ANGLE360) {
			return ANGLE360 - _angAxisRot[prm_iAxis] + angTarget_AxisRot;
		} else if (_angAxisRot[prm_iAxis] == angTarget_AxisRot) {
			//重なってる場合
			return 0;
		}else {
			//おかしい
			_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/angTarget_AxisRot=" << angTarget_AxisRot);
			throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(3)。");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //時計回りの場合
		if (0 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < angTarget_AxisRot) {
			return -1*( _angAxisRot[prm_iAxis] + ANGLE360 - angTarget_AxisRot);
		} else if (angTarget_AxisRot < _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < ANGLE360) {
			return -1*(_angAxisRot[prm_iAxis] - angTarget_AxisRot);
		} else if (_angAxisRot[prm_iAxis] == angTarget_AxisRot) {
			//重なってる場合
			return 0;
		}else {
			//おかしい
			_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/angTarget_AxisRot=" << angTarget_AxisRot);
			throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(4)。");
		}
	}
	_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/angTarget_AxisRot=" << angTarget_AxisRot);
	throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() 何故かしら角の距離が求めれません。(2)");
}

GgafDx9GeometryMover::~GgafDx9GeometryMover() {
}
