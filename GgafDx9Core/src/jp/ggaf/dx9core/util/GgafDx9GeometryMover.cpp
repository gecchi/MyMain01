#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9GeometryMover::GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

    for (int i = 0; i < 3; i++) { // i=0:X軸、1:Y軸、2:Z軸 を表す

        //軸回転方角
        _angRot[i] = 0; //0 angle は ３時の方角を向いている
        //軸回転方角の角速度（軸回転方角の増分）= 0 angle/fream
        _angveloRot[i] = 0; //1フレームに加算される軸回転方角の角増分。デフォルトは軸回転方角の角増分無し、つまり振り向き無し。
        //軸回転方角の角速度上限 ＝ 360,000 angle/fream
        _angveloTopRot[i] = ANGLE360; //_angveloRot[n] の増分の上限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する
        //軸回転方角の角速度下限 ＝ -360,000 angle/fream
        _angveloBottomRot[i] = ANGLE360 * -1; //_angveloRot[n] の増分の下限。デフォルトは1フレームで好きな軸回転方角に振り向く事が出来る事を意味する
        //軸回転方角の角加速度（角速度の増分） ＝ 0 angle/fream^2
        _angacceRot[i] = 0; //_angveloRot[n] の増分。デフォルトは軸回転方角の角加速度無し
        //目標軸回転方角への自動制御フラグ = 無効
        _auto_rot_angle_targeting_flg[i] = false;
        //目標の軸回転方角
        _angAutoTargetRot[i] = 0; //目標軸回転方角への自動制御フラグ = 無効、の場合は無意味
        //目標の軸回転方角自動停止機能が有効になる回転方向
        _auto_rot_angle_target_allow_way[i] = TURN_BOTH;
        //目標の軸回転方角自動停止機能が有効になる角速度（回転正負共通）
        _auto_rot_angle_target_allow_velocity[i] = ANGLE180;
    }

    //////////////////////////////////////////////////////
    //キャラの移動方角単位ベクトル
    _vX = _vY = _vZ = 0.0;
    //移動方角のZ軸回転
    _angRzMove = 0;
    //移動方角のY軸回転
    _angRyMove = 0;
    //移動速度
    _veloMove = 0;
    //移動速度上限 = 256 px/fream
    _veloTopMove = 256 * LEN_UNIT; //_veloMove が 256000(=256px) を上回る移動量であっても、強制的に座標増分は 256px に抑えられる。
    //移動速度下限 = 0   px/fream
    _veloBottomMove = -256 * LEN_UNIT; //_veloMove が -256000(-256px) を下回る移動量があっても、強制的に座標増分は -256000px に抑えられる。
    //移動加速度（移動速度の増分） = 0 px/fream^2
    _accMove = 0; //_veloMove の増分。デフォルトは加速無し

    /////コピー元begin
    //移動方角（Z軸回転）の角速度 = 0 angle/fream
    _angveloRzMove = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Z軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRzTopMove = ANGLE360; //_angveloRzMove の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRzBottomMove = ANGLE360 * -1; //_angveloRzMove の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角加速度 = 0 angle/fream^2
    _angacceRzMove = 0; //_angveloRzMove の増分。デフォルトは移動方角の角加速度無し
    //目標移動方角（Z軸回転）への自動制御フラグ = 無効
    _auto_move_angle_rz_target_flg = false;
    //目標の移動方角（Z軸回転）
    _angAutoTargetRzMove = 0;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる回転方向
    _auto_move_angle_rz_target_allow_way = TURN_BOTH;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _auto_move_angle_rz_target_allow_velocity = ANGLE180;
    //移動方角（Z軸回転）に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
    _synchronize_ZRotAngle_to_RzMoveAngle_flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。
    ////コピー元end

    /////コピー元begin
    //移動方角（Y軸回転）の角速度 = 0 angle/fream
    _angveloRyMove = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Y軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRyTopMove = ANGLE360; //_angveloRyMove の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRyBottomMove = ANGLE360 * -1; //_angveloRyMove の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角加速度 = 0 angle/fream^2
    _angacceRyMove = 0; //_angveloRyMove の増分。デフォルトは移動方角の角加速度無し
    //目標移動方角（Y軸回転）への自動制御フラグ = 無効
    _auto_move_angle_ry_target_flg = false;
    //目標の移動方角（Y軸回転）
    _angAutoTargetRyMove = 0;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる回転方向
    _auto_move_angle_ry_target_allow_way = TURN_BOTH;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _auto_move_angle_ry_target_allow_velocity = ANGLE180;
    //移動方角（Y軸回転）に伴いZ軸回転方角の同期を取る機能フラグ ＝ 無効
    _synchronize_YRotAngle_to_RyMoveAngle_flg = false; //有効の場合は、移動方角を設定するとZ軸回転方角が同じになる。
    ////コピー元end

    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _veloVxMove = 0;
    //X軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVxMove = 256 * LEN_UNIT;
    //X軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVxMove = -256 * LEN_UNIT;
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVxMove = 0;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _veloVyMove = 0;
    //Y軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVyMove = 256 * LEN_UNIT;
    //Y軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVyMove = -256 * LEN_UNIT;
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVyMove = 0;
    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _veloVzMove = 0;
    //Z軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVzMove = 256 * LEN_UNIT;
    //Z軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVzMove = -256 * LEN_UNIT;
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVzMove = 0;
}

void GgafDx9GeometryMover::behave() {
    static angle angDistance;
    for (int i = 0; i < 3; i++) {
        if (_auto_rot_angle_targeting_flg[i]) {
            _angveloRot[i] += _angacceRot[i];
            setRotAngleVelocity(i, _angveloRot[i]);

            if (_angveloRot[i] > 0) { //反時計回りの場合
                angDistance = getDistanceFromRotAngleTo(i, _angAutoTargetRot[i], TURN_COUNTERCLOCKWISE);
                if (_angveloRot[i] > angDistance && _auto_rot_angle_target_allow_way[i] != TURN_CLOCKWISE
                        && _auto_rot_angle_target_allow_velocity[i] >= _angveloRot[i]) {
                    addRotAngle(i, angDistance);
                    _auto_rot_angle_targeting_flg[i] = false; //フラグを戻して終了
                } else {
                    addRotAngle(i, _angveloRot[i]);
                }
            } else if (_angveloRot[i] < 0) { //時計回りの場合
                angDistance = getDistanceFromRotAngleTo(i, _angAutoTargetRot[i], TURN_CLOCKWISE);
                if (_angveloRot[i] < angDistance && _auto_rot_angle_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _auto_rot_angle_target_allow_velocity[i] <= _angveloRot[i]) { //目標を行き過ぎてしまいそう･･･な日
                    addRotAngle(i, angDistance);
                    _auto_rot_angle_targeting_flg[i] = false; //フラグを戻して終了
                } else {
                    addRotAngle(i, _angveloRot[i]);
                }
            } else {
                //_angveloRot[i] == 0
                addRotAngle(i, 0);
            }

            if (_auto_rot_angle_targeting_flg[i] == false) {
                //目標方向に到達した時の処理
                //_angveloTopRot[i] = ANGLE360; //軸回転方角の角速度上限 ＝ 360,000 angle/fream
                //_angveloBottomRot[i] = ANGLE360 * -1; //軸回転方角の角速度下限 ＝ -360,000 angle/fream

                //目標方向に到達した時、停止処理を行なう
                _angacceRot[i] = 0; //軸回転方向角、角速度を０へ
                setRotAngleVelocity(i, 0); //軸回転方向角、角加速度を０へ
            }

        } else {
            //if (_angacceRot[i] != 0) {
            //フレーム毎の軸回転方角旋廻の処理
            _angveloRot[i] += _angacceRot[i];
            addRotAngle(i, _angveloRot[i]);
            //}
        }
    }

    //Actorに反映
    _pActor->_RX = _angRot[AXIS_X];
    _pActor->_RY = _angRot[AXIS_Y];
    _pActor->_RZ = _angRot[AXIS_Z];

    ///////////////////////////////////////////////////Mover
    //X軸方向移動加速度の処理
    _veloVxMove += _acceVxMove;
    setVxMoveVelocity(_veloVxMove);
    //Y軸方向移動加速度の処理
    _veloVyMove += _acceVyMove;
    setVyMoveVelocity(_veloVyMove);
    //Z軸方向移動加速度の処理
    _veloVzMove += _acceVzMove;
    setVzMoveVelocity(_veloVzMove);

    //移動加速度の処理
    _veloMove += _accMove;
    setMoveVelocity(_veloMove);
    ///////////
    //目標移動方角（Z軸回転）アングル自動停止機能使用時の場合
    if (_auto_move_angle_rz_target_flg) {

        _angveloRzMove += _angacceRzMove;
        setRzMoveAngleVelocity(_angveloRzMove);

        if (_angveloRzMove > 0) { //反時計回りの場合
            angle angDistance = getDistanceFromRzMoveAngleTo(_angAutoTargetRzMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRzMove > angDistance && _auto_move_angle_rz_target_allow_way != TURN_CLOCKWISE
                    && _auto_move_angle_rz_target_allow_velocity >= _angveloRzMove) { //目標を行き過ぎてしまいそう･･･な日
                addRzMoveAngle(angDistance);
                _auto_move_angle_rz_target_flg = false; //フラグを戻して終了
            } else {
                addRzMoveAngle(_angveloRzMove);
            }
        } else if (_angveloRzMove < 0) { //時計回りの場合

            angle angDistance = getDistanceFromRzMoveAngleTo(_angAutoTargetRzMove, TURN_CLOCKWISE);
            if (_angveloRzMove < angDistance && _auto_move_angle_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_auto_move_angle_rz_target_allow_velocity <= _angveloRzMove) {
                addRzMoveAngle(angDistance);
                _auto_move_angle_rz_target_flg = false; //フラグを戻して終了
            } else {
                addRzMoveAngle(_angveloRzMove);
            }
        } else {
            addRzMoveAngle(0);
        }
        if (_auto_move_angle_rz_target_flg == false) {
            //_angveloRzTopMove = ANGLE360; //移動方角（Z軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRzBottomMove = ANGLE360 * -1; //移動方角（Z軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRzMove = 0; //Z軸移動方向角、角加速度を０へ
            setRzMoveAngleVelocity(0); //Z軸移動方向角、角速度を０へ
        }

    } else {
        //if (_angacceRzMove != 0) {
        //フレーム毎の移動方角（Z軸回転）旋廻の処理
        _angveloRzMove += _angacceRzMove;
        addRzMoveAngle(_angveloRzMove);
        //}
    }
    ////////////////
    //目標移動方角（Y軸回転）アングル自動停止機能使用時の場合
    if (_auto_move_angle_ry_target_flg) {

        _angveloRyMove += _angacceRyMove;
        setRyMoveAngleVelocity(_angveloRyMove);

        if (_angveloRyMove > 0) { //反時計回りの場合
            angle angDistance = getDistanceFromRyMoveAngleTo(_angAutoTargetRyMove, TURN_COUNTERCLOCKWISE);
            if (_angveloRyMove > angDistance &&
                _auto_move_angle_ry_target_allow_way != TURN_CLOCKWISE &&
                _auto_move_angle_ry_target_allow_velocity >= _angveloRyMove)
            { //目標を行き過ぎてしまいそう･･･な日
                addRyMoveAngle(angDistance);
                _auto_move_angle_ry_target_flg = false; //フラグを戻して終了
            } else {
                addRyMoveAngle(_angveloRyMove);
            }
        } else if (_angveloRyMove < 0) { //時計回りの場合

            angle angDistance = getDistanceFromRyMoveAngleTo(_angAutoTargetRyMove, TURN_CLOCKWISE);
            if (_angveloRyMove < angDistance &&
                _auto_move_angle_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_auto_move_angle_ry_target_allow_velocity <= _angveloRyMove)
            {
                addRyMoveAngle(angDistance);
                _auto_move_angle_ry_target_flg = false; //フラグを戻して終了
            } else {
                addRyMoveAngle(_angveloRyMove);
            }
        } else {
            //_angveloRyMove==0
            addRyMoveAngle(0);
        }
        if (_auto_move_angle_ry_target_flg == false) {
            //_angveloRyTopMove = ANGLE360; //移動方角（Y軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRyBottomMove = ANGLE360*-1; //移動方角（Y軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRyMove = 0; //Y軸移動方向角、角加速度を０へ
            setRyMoveAngleVelocity(0); //Y軸移動方向角、角速度を０へ
        }
    } else {
        //if (_angacceRyMove != 0) {
        //フレーム毎の移動方角（Y軸回転）旋廻の処理
        _angveloRyMove += _angacceRyMove;
        addRyMoveAngle(_angveloRyMove);
        //}
    }
    ///////////////

    //Actorに反映
    _pActor->_X += (_vX * _veloMove + _veloVxMove);
    _pActor->_Y += (_vY * _veloMove + _veloVyMove);
    _pActor->_Z += (_vZ * _veloMove + _veloVzMove);

}

angle GgafDx9GeometryMover::simplifyAngle(angle prm_ang) {
    static angle angSimple;
    angSimple = prm_ang;
    while (angSimple >= ANGLE360) {
        angSimple -= ANGLE360;
    }
    while (angSimple < 0) {
        angSimple += ANGLE360;
    }
    return angSimple;
}

void GgafDx9GeometryMover::setRotAngle(int prm_axis, angle prm_angRot) {
    _angRot[prm_axis] = simplifyAngle(prm_angRot);
}

void GgafDx9GeometryMover::setRotAngle(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRotAngleZY(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _angRot[AXIS_Z],
                   _angRot[AXIS_Y]
                 );
}

void GgafDx9GeometryMover::addRotAngle(int prm_axis, angle prm_angDistance) {
    static angle angOffsetrot_RotAngle;
    angOffsetrot_RotAngle = prm_angDistance;
    if (_angveloBottomRot[prm_axis] > prm_angDistance) {
        angOffsetrot_RotAngle = _angveloBottomRot[prm_axis];
    } else if (prm_angDistance > _angveloTopRot[prm_axis]) {
        angOffsetrot_RotAngle = _angveloTopRot[prm_axis];
    }
    setRotAngle(prm_axis, _angRot[prm_axis] + angOffsetrot_RotAngle);
}

void GgafDx9GeometryMover::setRotAngleVelocity(int prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopRot[prm_axis]) {
        _angveloRot[prm_axis] = _angveloTopRot[prm_axis];
    } else if (prm_angveloRot < _angveloBottomRot[prm_axis]) {
        _angveloRot[prm_axis] = _angveloBottomRot[prm_axis];
    } else {
        _angveloRot[prm_axis] = prm_angveloRot;
    }
}

void GgafDx9GeometryMover::setRotAngleVelocityRenge(int prm_axis,
                                                    angvelo prm_angveloRot01,
                                                    angvelo prm_angveloRot02) {
    if (prm_angveloRot01 < prm_angveloRot02) {
        _angveloTopRot[prm_axis] = prm_angveloRot02;
        _angveloBottomRot[prm_axis] = prm_angveloRot01;
    } else {
        _angveloTopRot[prm_axis] = prm_angveloRot01;
        _angveloBottomRot[prm_axis] = prm_angveloRot02;
    }
    setRotAngleVelocity(prm_axis, _angveloRot[prm_axis]); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setRotAngleAcceleration(int prm_axis, angacce prm_angacceRot) {
    _angacceRot[prm_axis] = prm_angacceRot;
}

void GgafDx9GeometryMover::setAutoTargetRotAngleV(int prm_axis,
                                                  int prm_tX,
                                                  int prm_tY,
                                                  int prm_way_allow,
                                                  angvelo prm_angveloAllowRyMove) {
    setAutoTargetRotAngle(
      prm_axis,
      GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
      prm_way_allow,
      prm_angveloAllowRyMove
    );
}

void GgafDx9GeometryMover::setAutoTargetRotAngle(int prm_axis,
                                                 angle prm_angAutoTargetRot,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllow) {
    _auto_rot_angle_targeting_flg[prm_axis] = true;
    _angAutoTargetRot[prm_axis] = simplifyAngle(prm_angAutoTargetRot);
    _auto_rot_angle_target_allow_way[prm_axis] = prm_way_allow;
    _auto_rot_angle_target_allow_velocity[prm_axis] = prm_angveloAllow;
}

angle GgafDx9GeometryMover::getDistanceFromRotAngleTo(int prm_axis, int prm_tX, int prm_tY, int prm_way) {
    return getDistanceFromRotAngleTo(prm_axis, GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY
            - (_pActor->_Y)), prm_way);
}

angle GgafDx9GeometryMover::getDistanceFromRotAngleTo(int prm_axis, angle prm_angAutoTargetRot, int prm_way) {
    static angle _angAutoTargetRot;
    _angAutoTargetRot = simplifyAngle(prm_angAutoTargetRot);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRot[prm_axis] && _angRot[prm_axis] < ANGLE180) {
            if (0 <= _angAutoTargetRot && _angAutoTargetRot < _angRot[prm_axis]) {
                return -1 * (_angRot[prm_axis] - _angAutoTargetRot);
            } else if (_angAutoTargetRot == _angRot[prm_axis]) {
                //重なってる場合
                return 0;
            } else if (_angRot[prm_axis] < _angAutoTargetRot && _angAutoTargetRot < _angRot[prm_axis]
                    + ANGLE180) {
                return _angAutoTargetRot - _angRot[prm_axis];
            } else if (_angAutoTargetRot == _angRot[prm_axis] + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRot[prm_axis] + ANGLE180 < _angAutoTargetRot && _angAutoTargetRot <= ANGLE360) {
                return -1 * (_angRot[prm_axis] + (ANGLE360 - _angAutoTargetRot));
            } else {
                //おかしい
                _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angAutoTargetRot=" << _angAutoTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRot[prm_axis] && _angRot[prm_axis] <= ANGLE360) {
            if (0 <= _angAutoTargetRot && _angAutoTargetRot < _angRot[prm_axis] - ANGLE180) {
                return ANGLE360 - _angRot[prm_axis] + _angAutoTargetRot;
            } else if (_angAutoTargetRot == _angRot[prm_axis] - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRot[prm_axis] - ANGLE180 < _angAutoTargetRot && _angAutoTargetRot
                    < _angRot[prm_axis]) {
                return -1 * (_angRot[prm_axis] - _angAutoTargetRot);
            } else if (_angRot[prm_axis] == _angAutoTargetRot) {
                //重なってる場合
                return 0;
            } else if (_angRot[prm_axis] < _angAutoTargetRot && _angAutoTargetRot <= ANGLE360) {
                return _angAutoTargetRot - _angRot[prm_axis];
            } else {
                //おかしい
                _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angAutoTargetRot=" << _angAutoTargetRot);
                throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRot[prm_axis] && _angRot[prm_axis] < _angAutoTargetRot) {
            return (_angAutoTargetRot - _angRot[prm_axis]);
        } else if (_angAutoTargetRot < _angRot[prm_axis] && _angRot[prm_axis] < ANGLE360) {
            return ANGLE360 - _angRot[prm_axis] + _angAutoTargetRot;
        } else if (_angRot[prm_axis] == _angAutoTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angAutoTargetRot=" << _angAutoTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRot[prm_axis] && _angRot[prm_axis] < _angAutoTargetRot) {
            return -1 * (_angRot[prm_axis] + ANGLE360 - _angAutoTargetRot);
        } else if (_angAutoTargetRot < _angRot[prm_axis] && _angRot[prm_axis] < ANGLE360) {
            return -1 * (_angRot[prm_axis] - _angAutoTargetRot);
        } else if (_angRot[prm_axis] == _angAutoTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angAutoTargetRot=" << _angAutoTargetRot);
            throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRotAngleTo() 現在の軸回転方角アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }
    _TRACE_("_angRot["<<prm_axis<<"]=" << _angRot[prm_axis] << "/_angAutoTargetRot=" << _angAutoTargetRot);
    throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRotAngleTo() 何故かしら角の距離が求めれません。(2)");
}

////////////////////////////////////////////////////////Mover


void GgafDx9GeometryMover::setMoveVelocityRenge(int prm_veloMove01, int prm_veloMove02) {
    if (prm_veloMove01 < prm_veloMove02) {
        _veloTopMove = prm_veloMove02;
        _veloBottomMove = prm_veloMove01;
    } else {
        _veloTopMove = prm_veloMove01;
        _veloBottomMove = prm_veloMove02;
    }
    setMoveVelocity(_veloMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setMoveVelocity(int prm_veloMove) {
    if (prm_veloMove > _veloTopMove) {
        _veloMove = _veloTopMove;
    } else if (prm_veloMove < _veloBottomMove) {
        _veloMove = _veloBottomMove;
    } else {
        _veloMove = prm_veloMove;
    }
}

void GgafDx9GeometryMover::addMoveVelocity(int prm_veloMove_Offset) {
    setMoveVelocity(_veloMove + prm_veloMove_Offset);
}

void GgafDx9GeometryMover::setMoveAcceleration(int prm_acceMove) {
    _accMove = prm_acceMove;
}

////コピー元begin

void GgafDx9GeometryMover::setRzMoveAngle(int prm_tX, int prm_tY) {
    setRzMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRzMoveAngle(angle prm_angle) {
    _angRzMove = simplifyAngle(prm_angle);
    GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    if (_synchronize_ZRotAngle_to_RzMoveAngle_flg) {
        setRotAngle(AXIS_Z, _angRzMove);
    }
}

void GgafDx9GeometryMover::addRzMoveAngle(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMove > prm_angDistance) {
        angOffset = _angveloRzBottomMove;
    } else if (prm_angDistance > _angveloRzTopMove) {
        angOffset = _angveloRzTopMove;
    }
    setRzMoveAngle(_angRzMove + angOffset);
}

void GgafDx9GeometryMover::setRzMoveAngleVelocity(angvelo prm_angveloRzMove) {
    if (prm_angveloRzMove > _angveloRzTopMove) {
        _angveloRzMove = _angveloRzTopMove;
    } else if (prm_angveloRzMove < _angveloRzBottomMove) {
        _angveloRzMove = _angveloRzBottomMove;
    } else {
        _angveloRzMove = prm_angveloRzMove;
    }
}

void GgafDx9GeometryMover::setRzMoveAngleAcceleration(angacce prm_angacceRzMove) {
    _angacceRzMove = prm_angacceRzMove;
}

void GgafDx9GeometryMover::setRzMoveAngleVelocityRenge(angvelo prm_angveloRzMove01,
                                                       angvelo prm_angveloRzMove02) {
    if (prm_angveloRzMove01 < prm_angveloRzMove02) {
        _angveloRzTopMove = prm_angveloRzMove02;
        _angveloRzBottomMove = prm_angveloRzMove01;
    } else {
        _angveloRzTopMove = prm_angveloRzMove01;
        _angveloRzBottomMove = prm_angveloRzMove02;
    }
    setRzMoveAngleVelocity(_angveloRzMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setAutoTargetRzMoveAngle(angle prm_angAutoTargetRzMove,
                                                int prm_way_allow,
                                                angvelo prm_angveloAllowRyMove) {
    _auto_move_angle_rz_target_flg = true;
    _angAutoTargetRzMove = simplifyAngle(prm_angAutoTargetRzMove);
    _auto_move_angle_rz_target_allow_way = prm_way_allow;
    _auto_move_angle_rz_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setAutoTargetRzMoveAngleV(int prm_tX,
                                                 int prm_tY,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMove) {
    setAutoTargetRzMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getDistanceFromRzMoveAngleTo(int prm_tX, int prm_tY, int prm_way) {
    return getDistanceFromRzMoveAngleTo(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getDistanceFromRzMoveAngleTo(angle prm_angAutoTargetRzMove, int prm_way) {
    angle angAutoTargetRzMove = simplifyAngle(prm_angAutoTargetRzMove);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRzMove && _angRzMove < ANGLE180) {
            if (0 <= angAutoTargetRzMove && angAutoTargetRzMove < _angRzMove) {
                return -1 * (_angRzMove - angAutoTargetRzMove);
            } else if (angAutoTargetRzMove == _angRzMove) {
                //重なってる場合
                return 0;
            } else if (_angRzMove < angAutoTargetRzMove && angAutoTargetRzMove < _angRzMove + ANGLE180) {
                return angAutoTargetRzMove - _angRzMove;
            } else if (angAutoTargetRzMove == _angRzMove + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRzMove + ANGLE180 < angAutoTargetRzMove && angAutoTargetRzMove <= ANGLE360) {
                return -1 * (_angRzMove + (ANGLE360 - angAutoTargetRzMove));
            } else {
                //おかしい
                _TRACE_("_angRzMove=" << _angRzMove << "/angAutoTargetRzMove=" << angAutoTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRzMove && _angRzMove <= ANGLE360) {
            if (0 <= angAutoTargetRzMove && angAutoTargetRzMove < _angRzMove - ANGLE180) {
                return ANGLE360 - _angRzMove + angAutoTargetRzMove;
            } else if (angAutoTargetRzMove == _angRzMove - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRzMove - ANGLE180 < angAutoTargetRzMove && angAutoTargetRzMove < _angRzMove) {
                return -1 * (_angRzMove - angAutoTargetRzMove);
            } else if (_angRzMove == angAutoTargetRzMove) {
                //重なってる場合
                return 0;
            } else if (_angRzMove < angAutoTargetRzMove && angAutoTargetRzMove <= ANGLE360) {
                return angAutoTargetRzMove - _angRzMove;
            } else {
                //おかしい
                _TRACE_("_angRzMove=" << _angRzMove << "/angAutoTargetRzMove=" << angAutoTargetRzMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRzMoveAngleTo() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRzMove && _angRzMove < angAutoTargetRzMove) {
            return (angAutoTargetRzMove - _angRzMove);
        } else if (angAutoTargetRzMove < _angRzMove && _angRzMove < ANGLE360) {
            return ANGLE360 - _angRzMove + angAutoTargetRzMove;
        } else if (_angRzMove == angAutoTargetRzMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMove=" << _angRzMove << "/angAutoTargetRzMove=" << angAutoTargetRzMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRzMoveAngleTo() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRzMove && _angRzMove < angAutoTargetRzMove) {
            return -1 * (_angRzMove + ANGLE360 - angAutoTargetRzMove);
        } else if (angAutoTargetRzMove < _angRzMove && _angRzMove < ANGLE360) {
            return -1 * (_angRzMove - angAutoTargetRzMove);
        } else if (_angRzMove == angAutoTargetRzMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMove=" << _angRzMove << "/angAutoTargetRzMove=" << angAutoTargetRzMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRzMoveAngleTo() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }

    _TRACE_("_angRzMove=" << _angRzMove << "/angAutoTargetRzMove=" << angAutoTargetRzMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRzMoveAngleTo() 何故かしら角の距離が求めれません。(1)");

}

////コピー元end

////コピー元begin

void GgafDx9GeometryMover::setRyMoveAngle(int prm_tX, int prm_tY) {
    setRyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void GgafDx9GeometryMover::setRyMoveAngle(angle prm_angle) {
    _angRyMove = simplifyAngle(prm_angle);
    GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    if (_synchronize_YRotAngle_to_RyMoveAngle_flg) {
        setRotAngle(AXIS_Y, _angRyMove);
    }
}

void GgafDx9GeometryMover::addRyMoveAngle(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMove > prm_angDistance) {
        angOffset = _angveloRyBottomMove;
    } else if (prm_angDistance > _angveloRyTopMove) {
        angOffset = _angveloRyTopMove;
    }
    setRyMoveAngle(_angRyMove + angOffset);
}

void GgafDx9GeometryMover::setRyMoveAngleVelocity(angvelo prm_angveloRyMove) {
    if (prm_angveloRyMove > _angveloRyTopMove) {
        _angveloRyMove = _angveloRyTopMove;
    } else if (prm_angveloRyMove < _angveloRyBottomMove) {
        _angveloRyMove = _angveloRyBottomMove;
    } else {
        _angveloRyMove = prm_angveloRyMove;
    }
}

void GgafDx9GeometryMover::setRyMoveAngleAcceleration(angacce prm_angacceRyMove) {
    _angacceRyMove = prm_angacceRyMove;
}

void GgafDx9GeometryMover::setRyMoveAngleVelocityRenge(angvelo prm_angveloRyMove01,
                                                       angvelo prm_angveloRyMove02) {
    if (prm_angveloRyMove01 < prm_angveloRyMove02) {
        _angveloRyTopMove = prm_angveloRyMove02;
        _angveloRyBottomMove = prm_angveloRyMove01;
    } else {
        _angveloRyTopMove = prm_angveloRyMove01;
        _angveloRyBottomMove = prm_angveloRyMove02;
    }
    setRyMoveAngleVelocity(_angveloRyMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setAutoTargetRyMoveAngle(angle prm_angAutoTargetRyMove,
                                                int prm_way_allow,
                                                angvelo prm_angveloAllowRyMove) {
    _auto_move_angle_ry_target_flg = true;
    _angAutoTargetRyMove = simplifyAngle(prm_angAutoTargetRyMove);
    _auto_move_angle_ry_target_allow_way = prm_way_allow;
    _auto_move_angle_ry_target_allow_velocity = prm_angveloAllowRyMove;
}

void GgafDx9GeometryMover::setAutoTargetRyMoveAngleV(int prm_tX,
                                                 int prm_tY,
                                                 int prm_way_allow,
                                                 angvelo prm_angveloAllowRyMove) {
    setAutoTargetRyMoveAngle(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_way_allow);
}

angle GgafDx9GeometryMover::getDistanceFromRyMoveAngleTo(int prm_tX, int prm_tY, int prm_way) {
    return getDistanceFromRyMoveAngleTo(GgafDx9Util::getAngle2D(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
                                        prm_way);
}

angle GgafDx9GeometryMover::getDistanceFromRyMoveAngleTo(angle prm_angAutoTargetRyMove, int prm_way) {
    static angle angAutoTargetRyMove;
    angAutoTargetRyMove = simplifyAngle(prm_angAutoTargetRyMove);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRyMove && _angRyMove < ANGLE180) {
            if (0 <= angAutoTargetRyMove && angAutoTargetRyMove < _angRyMove) {
                return -1 * (_angRyMove - angAutoTargetRyMove);
            } else if (angAutoTargetRyMove == _angRyMove) {
                //重なってる場合
                return 0;
            } else if (_angRyMove < angAutoTargetRyMove && angAutoTargetRyMove < _angRyMove + ANGLE180) {
                return angAutoTargetRyMove - _angRyMove;
            } else if (angAutoTargetRyMove == _angRyMove + ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRyMove + ANGLE180 < angAutoTargetRyMove && angAutoTargetRyMove <= ANGLE360) {
                return -1 * (_angRyMove + (ANGLE360 - angAutoTargetRyMove));
            } else {
                //おかしい
                _TRACE_("_angRyMove=" << _angRyMove << "/angAutoTargetRyMove=" << angAutoTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::behave() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。");
            }
        } else if (ANGLE180 <= _angRyMove && _angRyMove <= ANGLE360) {
            if (0 <= angAutoTargetRyMove && angAutoTargetRyMove < _angRyMove - ANGLE180) {
                return ANGLE360 - _angRyMove + angAutoTargetRyMove;
            } else if (angAutoTargetRyMove == _angRyMove - ANGLE180) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return ANGLE180;
            } else if (_angRyMove - ANGLE180 < angAutoTargetRyMove && angAutoTargetRyMove < _angRyMove) {
                return -1 * (_angRyMove - angAutoTargetRyMove);
            } else if (_angRyMove == angAutoTargetRyMove) {
                //重なってる場合
                return 0;
            } else if (_angRyMove < angAutoTargetRyMove && angAutoTargetRyMove <= ANGLE360) {
                return angAutoTargetRyMove - _angRyMove;
            } else {
                //おかしい
                _TRACE_("_angRyMove=" << _angRyMove << "/angAutoTargetRyMove=" << angAutoTargetRyMove);
                throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRyMoveAngleTo() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRyMove && _angRyMove < angAutoTargetRyMove) {
            return (angAutoTargetRyMove - _angRyMove);
        } else if (angAutoTargetRyMove < _angRyMove && _angRyMove < ANGLE360) {
            return ANGLE360 - _angRyMove + angAutoTargetRyMove;
        } else if (_angRyMove == angAutoTargetRyMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMove=" << _angRyMove << "/angAutoTargetRyMove=" << angAutoTargetRyMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRyMoveAngleTo() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。");
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRyMove && _angRyMove < angAutoTargetRyMove) {
            return -1 * (_angRyMove + ANGLE360 - angAutoTargetRyMove);
        } else if (angAutoTargetRyMove < _angRyMove && _angRyMove < ANGLE360) {
            return -1 * (_angRyMove - angAutoTargetRyMove);
        } else if (_angRyMove == angAutoTargetRyMove) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMove=" << _angRyMove << "/angAutoTargetRyMove=" << angAutoTargetRyMove);
            throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRyMoveAngleTo() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。");
        }
    }

    _TRACE_("_angRyMove=" << _angRyMove << "/angAutoTargetRyMove=" << angAutoTargetRyMove);
    throwGgafCriticalException("GgafDx9GeometryMover::getDistanceFromRyMoveAngleTo() 何故かしら角の距離が求めれません。(1)");

}

////コピー元end

void GgafDx9GeometryMover::setRzRyMoveAngle(angle prm_angRz, angle prm_angRy) {
    _angRzMove = simplifyAngle(prm_angRz);
    _angRyMove = simplifyAngle(prm_angRy);
    GgafDx9Util::getNormalizeVectorZY(_angRzMove, _angRyMove, _vX, _vY, _vZ);
    if (_synchronize_ZRotAngle_to_RzMoveAngle_flg) {
        setRotAngle(AXIS_Z, _angRzMove);
    }
    if (_synchronize_YRotAngle_to_RyMoveAngle_flg) {
        setRotAngle(AXIS_Y, _angRyMove);
    }

}

void GgafDx9GeometryMover::setMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
    GgafDx9Util::getRotAngleZY(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _vX,
                   _vY,
                   _vZ,
                   _angRzMove,
                   _angRyMove
                 );
}

void GgafDx9GeometryMover::setAutoTargetMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
    angle angRz_Target;
    angle angRy_Target;

    GgafDx9Util::getRotAngleZY(
                   prm_tX - _pActor->_X,
                   prm_tY - _pActor->_Y,
                   prm_tZ - _pActor->_Z,
                   _dummy1,
                   _dummy2,
                   _dummy3,
                   angRz_Target,
                   angRy_Target
                 );
    setAutoTargetRzMoveAngle(angRz_Target);
    setAutoTargetRyMoveAngle(angRy_Target);
}

void GgafDx9GeometryMover::setVxMoveVelocityRenge(velo prm_veloVxMove01, velo prm_veloVxMove02) {
    if (prm_veloVxMove01 < prm_veloVxMove02) {
        _veloTopVxMove = prm_veloVxMove02;
        _veloBottomVxMove = prm_veloVxMove01;
    } else {
        _veloTopVxMove = prm_veloVxMove01;
        _veloBottomVxMove = prm_veloVxMove02;
    }
    setVxMoveVelocity(_veloVxMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVxMoveVelocity(velo prm_veloVxMove) {
    if (prm_veloVxMove > _veloTopVxMove) {
        _veloVxMove = _veloTopVxMove;
    } else if (prm_veloVxMove < _veloBottomVxMove) {
        _veloVxMove = _veloBottomVxMove;
    } else {
        _veloVxMove = prm_veloVxMove;
    }
}

void GgafDx9GeometryMover::setVxMoveAcceleration(acce prm_acceVxMove) {
    _acceVxMove = prm_acceVxMove;
}

void GgafDx9GeometryMover::setVyMoveVelocityRenge(velo prm_veloVyMove01, velo prm_veloVyMove02) {
    if (prm_veloVyMove01 < prm_veloVyMove02) {
        _veloTopVyMove = prm_veloVyMove02;
        _veloBottomVyMove = prm_veloVyMove01;
    } else {
        _veloTopVyMove = prm_veloVyMove01;
        _veloBottomVyMove = prm_veloVyMove02;
    }
    setVyMoveVelocity(_veloVyMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVyMoveVelocity(velo prm_veloVyMove) {
    if (prm_veloVyMove > _veloTopVyMove) {
        _veloVyMove = _veloTopVyMove;
    } else if (prm_veloVyMove < _veloBottomVyMove) {
        _veloVyMove = _veloBottomVyMove;
    } else {
        _veloVyMove = prm_veloVyMove;
    }
}

void GgafDx9GeometryMover::setVyMoveAcceleration(acce prm_acceVyMove) {
    _acceVyMove = prm_acceVyMove;
}

void GgafDx9GeometryMover::setVzMoveVelocityRenge(velo prm_veloVzMove01, velo prm_veloVzMove02) {
    if (prm_veloVzMove01 < prm_veloVzMove02) {
        _veloTopVzMove = prm_veloVzMove02;
        _veloBottomVzMove = prm_veloVzMove01;
    } else {
        _veloTopVzMove = prm_veloVzMove01;
        _veloBottomVzMove = prm_veloVzMove02;
    }
    setVzMoveVelocity(_veloVzMove); //再設定して範囲内に補正
}

void GgafDx9GeometryMover::setVzMoveVelocity(velo prm_veloVzMove) {
    if (prm_veloVzMove > _veloTopVzMove) {
        _veloVzMove = _veloTopVzMove;
    } else if (prm_veloVzMove < _veloBottomVzMove) {
        _veloVzMove = _veloBottomVzMove;
    } else {
        _veloVzMove = prm_veloVzMove;
    }
}

void GgafDx9GeometryMover::setVzMoveAcceleration(acce prm_acceVzMove) {
    _acceVzMove = prm_acceVzMove;
}

GgafDx9GeometryMover::~GgafDx9GeometryMover() {
}
