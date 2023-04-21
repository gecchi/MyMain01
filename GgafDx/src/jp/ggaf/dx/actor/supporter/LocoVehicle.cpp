#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"

#include <math.h>
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;

LocoVehicle::LocoVehicle(GeometricActor* prm_pActor) : ActorVehicle(prm_pActor) {
    _pAsstMv = nullptr;
    _pAsstFaceAng = nullptr;
    _pAsstMvAng = nullptr;
    reset();
}
LocoVehicleMvAssistant* LocoVehicle::asstMv() {
    return _pAsstMv ? _pAsstMv : _pAsstMv = NEW LocoVehicleMvAssistant(this);
}
LocoVehicleFaceAngAssistant* LocoVehicle::asstFaceAng() {
    return _pAsstFaceAng ? _pAsstFaceAng : _pAsstFaceAng = NEW LocoVehicleFaceAngAssistant(this);
}
LocoVehicleMvAngAssistant* LocoVehicle::asstMvAng() {
    return _pAsstMvAng ? _pAsstMvAng : _pAsstMvAng = NEW LocoVehicleMvAngAssistant(this);
}

void LocoVehicle::reset() {
    GGAF_DELETE_NULLABLE(_pAsstMv);
    GGAF_DELETE_NULLABLE(_pAsstFaceAng);
    GGAF_DELETE_NULLABLE(_pAsstMvAng);

    _actor_face[0] = &(_pActor->_rx);
    _actor_face[1] = &(_pActor->_ry);
    _actor_face[2] = &(_pActor->_rz);

    for (int ax = 0; ax < 3; ax++) { // i=0:X軸、1:Y軸、2:Z軸 を表す
        //正面方角の角速度（正面方角の増分）= 0 angle/fream
        _angvelo_face[ax] = 0; //1フレームに加算される正面方角の角増分。デフォルトは正面方角の角増分無し、つまり振り向き無し。
        //正面方角の角速度上限 ＝ 360,000 angle/fream
        _top_angvelo_face[ax] = D360ANG; //_angvelo_face[n] の増分の上限。デフォルトは1フレームで好きな正面方角に振り向く事が出来る事を意味する
        //正面方角の角速度下限 ＝ -360,000 angle/fream
        _bottom_angvelo_face[ax] = D360ANG * -1; //_angvelo_face[n] の増分の下限。デフォルトは1フレームで好きな正面方角に振り向く事が出来る事を意味する
        //正面方角の角加速度（角速度の増分） ＝ 0 angle/fream^2
        _angacce_face[ax] = 0; //_angvelo_face[n] の増分。デフォルトは正面方角の角加速度無し

        _angjerk_face[ax] = 0;
        //目標正面方角への自動向きフラグ = 無効
        _is_targeting_face[ax] = false;
        //目標正面方角への自動停止フラグ = 無効
        _face_targeting_stop_flg[ax] = false;
        //目標の正面方角
        _target_face[ax] = 0; //目標正面方角への自動制御フラグ = 無効、の場合は無意味
        //目標の正面方角自動停止機能が有効になる回転方向
        _face_stop_allow_way[ax] = TURN_BOTH;
        //目標の正面方角自動停止機能が有効になる角速度（回転正負共通）
        _face_stop_allow_angvelo[ax] = D360ANG;
    }

    //////////////////////////////////////////////////////
    //キャラの移動方角単位ベクトル
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //移動方角のZ軸回転
    _rz_mv = 0;
    //移動方角のY軸回転
    _ry_mv = 0;
    //移動速度
    _velo_mv = 0;
    //移動速度上限
    _top_velo_mv = INT_MAX;
    //移動速度下限
    _bottom_velo_mv = INT_MIN;
    //移動加速度（移動速度の増分） = 0 px/fream^2
    _acc_mv = 0; //_velo_mv の増分。デフォルトは加速無し

    //_jerkMv = 0;
    //移動方角（Z軸回転）の角速度 = 0 angle/fream
    _angvelo_rz_mv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Z軸回転）の角速度上限 = +360,000 angle/fream
    _top_angvelo_rz_mv = D360ANG; //_angvelo_rz_mv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角速度下限 = -360,000 angle/fream
    _bottom_angvelo_rz_mv = D360ANG * -1; //_angvelo_rz_mv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角加速度 = 0 angle/fream^2
    _angacce_rz_mv = 0; //_angvelo_rz_mv の増分。デフォルトは移動方角の角加速度無し

    _angjerk_rz_mv = 0;
    //目標移動方角（Z軸回転）への自動向きフラグ = 無効
    _is_targeting_rz_mv = false;
    //目標移動方角（Z軸回転）への自動停止フラグ = 無効
    _rz_mv_targeting_stop_flg = false;

    //目標の移動方角（Z軸回転）
    _target_rz_mv = 0;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる回転方向
    _rz_mv_stop_allow_way = TURN_BOTH;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _rz_mv_stop_allow_angvelo = D360ANG;
    //移動方角（Z軸回転）に伴いZ正面方角の同期を取る機能フラグ ＝ 無効
    _relate_RzFaceAng_with_RzMvAng_flg = false; //有効の場合は、移動方角を設定するとZ正面方角が同じになる。

    //移動方角（Y軸回転）の角速度 = 0 angle/fream
    _angvelo_ry_mv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Y軸回転）の角速度上限 = +360,000 angle/fream
    _top_angvelo_ry_mv = D360ANG; //_angvelo_ry_mv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角速度下限 = -360,000 angle/fream
    _bottom_angvelo_ry_mv = D360ANG * -1; //_angvelo_ry_mv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角加速度 = 0 angle/fream^2
    _angacce_ry_mv = 0; //_angvelo_ry_mv の増分。デフォルトは移動方角の角加速度無し

    _angjerk_ry_mv = 0;
    //目標移動方角（Y軸回転）への自動向きフラグ = 無効
    _is_targeting_ry_mv = false;
    //目標移動方角（Y軸回転）への自動停止フラグ = 無効
    _ry_mv_targeting_stop_flg = false;
    //目標の移動方角（Y軸回転）
    _target_ry_mv = 0;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる回転方向
    _ry_mv_stop_allow_way = TURN_BOTH;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _ry_mv_stop_allow_angvelo = D360ANG;
    //移動方角（Y軸回転）に伴いZ正面方角の同期を取る機能フラグ ＝ 無効
    _relate_RyFaceAng_with_RyMvAng_flg = false; //有効の場合は、移動方角を設定するとZ正面方角が同じになる。

    _taget_face_alltime_flg = false;
    _taget_face_alltime_pActor = nullptr;
    _taget_face_alltime_tx = 0;
    _taget_face_alltime_ty = 0;
    _taget_face_alltime_tz = 0;
    _taget_face_alltime_angvelo = 0;
    _taget_face_alltime_angacce = 0;
    _taget_face_alltime_way = TURN_CLOSE_TO;
    _taget_face_alltime_optimize_ang = true;
}

void LocoVehicle::behave() {
    if (_pAsstMv) {
        _pAsstMv->behave();
    }
    if (_pAsstFaceAng) {
        _pAsstFaceAng->behave();
    }
    if (_pAsstMvAng) {
        _pAsstMvAng->behave();
    }

    //正面方角処理
    for (axis ax = 0; ax < 3; ax++) {

        _angvelo_face[ax] += _angacce_face[ax];
        if (_angvelo_face[ax] > _top_angvelo_face[ax]) {
            _angvelo_face[ax] = _top_angvelo_face[ax];
        } else if (_angvelo_face[ax] < _bottom_angvelo_face[ax]) {
            _angvelo_face[ax] = _bottom_angvelo_face[ax];
        }

        if (_is_targeting_face[ax]) { //ターゲット方向がある場合

            if (_angvelo_face[ax] > 0) { //反時計回りの場合
                const angle ang_distance = getFaceAngDistance(ax, _target_face[ax], TURN_COUNTERCLOCKWISE);
                if (_angvelo_face[ax] > ang_distance && _face_stop_allow_way[ax] != TURN_CLOCKWISE &&
                        _face_stop_allow_angvelo[ax] >= _angvelo_face[ax]) {
                    _angvelo_face[ax] = ang_distance;
                    if (_face_targeting_stop_flg[ax]) {
                        _is_targeting_face[ax] = false; //フラグを戻して終了
                        _face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    // なにもしなくてよい
                }
            } else if (_angvelo_face[ax] < 0) { //時計回りの場合
                const angle ang_distance = getFaceAngDistance(ax, _target_face[ax], TURN_CLOCKWISE);
                if (_angvelo_face[ax] < ang_distance && _face_stop_allow_way[ax] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_stop_allow_angvelo[ax] <= _angvelo_face[ax]) { //目標を行き過ぎてしまいそう・・・な日
                    _angvelo_face[ax] = ang_distance;
                    if (_face_targeting_stop_flg[ax]) {
                        _is_targeting_face[ax] = false; //フラグを戻して終了
                        _face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    // なにもしなくてよい
                }
            } else {
                //_angvelo_face[ax] == 0
                const angle ang_distance = getFaceAngDistance(ax, _target_face[ax], TURN_CLOSE_TO);
                if (ang_distance == 0) {
                    if (_face_targeting_stop_flg[ax]) {
                        _is_targeting_face[ax] = false; //フラグを戻して終了
                        _face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    if (_angacce_face[ax] == 0) { //加速度も0の場合強制停止(永遠に到達しない)
                        if (_face_targeting_stop_flg[ax]) {
                            _is_targeting_face[ax] = false; //フラグを戻して終了
                            _face_targeting_stop_flg[ax] = false;
                        }
                    }
                }
            }

            //Actorに反映
            (*(_actor_face[ax])) = UTIL::simplifyAng((*(_actor_face[ax])) + _angvelo_face[ax]);
            if (_is_targeting_face[ax] == false) {
                //目標方向に到達した時の処理
                //_top_angvelo_face[ax] = D360ANG; //正面方角の角速度上限 ＝ 360,000 angle/fream
                //_bottom_angvelo_face[ax] = D360ANG * -1; //正面方角の角速度下限 ＝ -360,000 angle/fream
                //目標方向に到達した時、停止処理を行なう
                _angacce_face[ax] = 0; //軸回転方向角、角速度を０へ
                setFaceAngVelo(ax, 0); //軸回転方向角、角加速度を０へ
            }

        } else {
            //ターゲット方向が無い場合
            //Actorに反映
            (*(_actor_face[ax])) = UTIL::simplifyAng((*(_actor_face[ax])) +  _angvelo_face[ax]);
        }

    }


    ///////////////////////////////////////////////////Mover

    //_acc_mv += _jerkMv;
    //移動加速度の処理
    _velo_mv += _acc_mv;
    if (_velo_mv > _top_velo_mv) {
        _velo_mv = _top_velo_mv;
    } else if (_velo_mv < _bottom_velo_mv) {
        _velo_mv = _bottom_velo_mv;
    }

    ///////////
    //目標移動方角（Z軸回転）アングル自動停止機能使用時の場合
    if (_is_targeting_rz_mv) {

        _angvelo_rz_mv += _angacce_rz_mv;
        setRzMvAngVelo(_angvelo_rz_mv);

        if (_angvelo_rz_mv > 0) { //反時計回りの場合
            const angle ang_distance = getRzMvAngDistance(_target_rz_mv, TURN_COUNTERCLOCKWISE);
            if (_angvelo_rz_mv > ang_distance && _rz_mv_stop_allow_way != TURN_CLOCKWISE
                    && _rz_mv_stop_allow_angvelo >= _angvelo_rz_mv) { //目標を行き過ぎてしまいそう・・・な日
                addRzMvAng(ang_distance);
                if (_rz_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_rz_mv = false; //フラグを戻して終了
                    _rz_mv_targeting_stop_flg = false;
                }
            } else {
                addRzMvAng(_angvelo_rz_mv);
            }
        } else if (_angvelo_rz_mv < 0) { //時計回りの場合

            const angle ang_distance = getRzMvAngDistance(_target_rz_mv, TURN_CLOCKWISE);
            if (_angvelo_rz_mv < ang_distance && _rz_mv_stop_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_rz_mv_stop_allow_angvelo <= _angvelo_rz_mv) {
                addRzMvAng(ang_distance);
                if (_rz_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_rz_mv = false; //フラグを戻して終了
                    _rz_mv_targeting_stop_flg = false;
                }
            } else {
                addRzMvAng(_angvelo_rz_mv);
            }
        } else {
            const angle ang_distance = getRzMvAngDistance(_target_rz_mv, TURN_CLOSE_TO);
            if (ang_distance == 0) {
                addRzMvAng(ang_distance);
                if (_rz_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_rz_mv = false; //フラグを戻して終了
                    _rz_mv_targeting_stop_flg = false;
                }
            } else {
                if (_angacce_rz_mv == 0) { //加速度もない場合強制停止
                    if (_rz_mv_targeting_stop_flg) { //停止指定ありならば
                        _is_targeting_rz_mv = false; //フラグを戻して終了
                        _rz_mv_targeting_stop_flg = false;
                    }
                }
            }
        }
        if (_is_targeting_rz_mv == false) {
            //_top_angvelo_rz_mv = D360ANG; //移動方角（Z軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_bottom_angvelo_rz_mv = D360ANG * -1; //移動方角（Z軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacce_rz_mv = 0; //Z軸移動方向角、角加速度を０へ
            setRzMvAngVelo(0); //Z軸移動方向角、角速度を０へ
        }

    } else {
        //if (_angacce_rz_mv != 0) {

        _angacce_rz_mv += _angjerk_rz_mv;
        //フレーム毎の移動方角（Z軸回転）旋廻の処理
        _angvelo_rz_mv += _angacce_rz_mv;
        if (_angvelo_rz_mv != 0) {
            addRzMvAng(_angvelo_rz_mv);
        }
        //}
    }
    ////////////////
    //目標移動方角（Y軸回転）アングル自動停止機能使用時の場合
    if (_is_targeting_ry_mv) {

        _angvelo_ry_mv += _angacce_ry_mv;
        setRyMvAngVelo(_angvelo_ry_mv);

        if (_angvelo_ry_mv > 0) { //現在は反時計回りの場合
            angle ang_distance = getRyMvAngDistance(_target_ry_mv, TURN_COUNTERCLOCKWISE);
            if (_angvelo_ry_mv > ang_distance &&
                _ry_mv_stop_allow_way != TURN_CLOCKWISE &&
                _ry_mv_stop_allow_angvelo >= _angvelo_ry_mv)
            { //目標を行き過ぎてしまいそう・・・な日
                addRyMvAng(ang_distance);
                if (_ry_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ry_mv = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_angvelo_ry_mv);
            }
        } else if (_angvelo_ry_mv < 0) { //現在は時計回りの場合

            angle ang_distance = getRyMvAngDistance(_target_ry_mv, TURN_CLOCKWISE);
            if (_angvelo_ry_mv < ang_distance &&
                _ry_mv_stop_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_ry_mv_stop_allow_angvelo <= _angvelo_ry_mv)
            {
                addRyMvAng(ang_distance);
                if (_ry_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ry_mv = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_angvelo_ry_mv);
            }
        } else { //_angvelo_ry_mv==0
            angle ang_distance = getRyMvAngDistance(_target_ry_mv, TURN_CLOSE_TO);
            if (ang_distance == 0) {
                addRyMvAng(ang_distance);
                if (_ry_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ry_mv = false; //フラグを戻して終了
                    _ry_mv_targeting_stop_flg = false;
                }
            } else {
                if (_angacce_ry_mv == 0) { //加速度もない場合強制停止
                    if (_ry_mv_targeting_stop_flg) { //停止指定ありならば
                        _is_targeting_ry_mv = false; //フラグを戻して終了
                        _ry_mv_targeting_stop_flg = false;
                    }
                }
            }
        }
        if (_is_targeting_ry_mv == false) {
            //_top_angvelo_ry_mv = D360ANG; //移動方角（Y軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_bottom_angvelo_ry_mv = D360ANG*-1; //移動方角（Y軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacce_ry_mv = 0; //Y軸移動方向角、角加速度を０へ
            setRyMvAngVelo(0); //Y軸移動方向角、角速度を０へ
        }

    } else {
        //if (_angacce_ry_mv != 0) {
        _angacce_ry_mv += _angjerk_ry_mv;
        //フレーム毎の移動方角（Y軸回転）旋廻の処理
        _angvelo_ry_mv += _angacce_ry_mv;
        if(_angvelo_ry_mv != 0) {
            addRyMvAng(_angvelo_ry_mv);
        }
        //}
    }

    ///////////////
    if (_taget_face_alltime_flg && _is_targeting_face[AXIS_Z] == false && _is_targeting_face[AXIS_Y] == false) {
        if (_taget_face_alltime_pActor) {
            keepOnTurningFaceAngTwd(
                    _taget_face_alltime_pActor,
                    _taget_face_alltime_angvelo,
                    _taget_face_alltime_angacce,
                    _taget_face_alltime_way,
                    _taget_face_alltime_optimize_ang);
        } else {
            keepOnTurningFaceAngTwd(
                    _taget_face_alltime_pActor->_x,
                    _taget_face_alltime_pActor->_y,
                    _taget_face_alltime_pActor->_z,
                    _taget_face_alltime_angvelo,
                    _taget_face_alltime_angacce,
                    _taget_face_alltime_way,
                    _taget_face_alltime_optimize_ang);
        }

    }
    //Actorに反映
    _pActor->_x += (coord)(_vX * _velo_mv);
    _pActor->_y += (coord)(_vY * _velo_mv);
    _pActor->_z += (coord)(_vZ * _velo_mv);
}

void LocoVehicle::setFaceAngVelo(axis prm_axis, angvelo prm_angvelo) {
    if (prm_angvelo > _top_angvelo_face[prm_axis]) {
        _angvelo_face[prm_axis] = _top_angvelo_face[prm_axis];
    } else if (prm_angvelo < _bottom_angvelo_face[prm_axis]) {
        _angvelo_face[prm_axis] = _bottom_angvelo_face[prm_axis];
    } else {
        _angvelo_face[prm_axis] = prm_angvelo;
    }
}

void LocoVehicle::setRollPitchYawFaceAngVelo(angvelo prm_axis_x_angvelo,
                                             angvelo prm_axis_z_angvelo,
                                             angvelo prm_axis_y_angvelo) {
    setFaceAngVelo(AXIS_X, prm_axis_x_angvelo);
    setFaceAngVelo(AXIS_Z, prm_axis_z_angvelo);
    setFaceAngVelo(AXIS_Y, prm_axis_y_angvelo);
}

void LocoVehicle::forceFaceAngVeloRange(axis prm_axis,
                                        angvelo prm_angvelo01,
                                        angvelo prm_angvelo02) {
    if (prm_angvelo01 < prm_angvelo02) {
        _top_angvelo_face[prm_axis] = prm_angvelo02;
        _bottom_angvelo_face[prm_axis] = prm_angvelo01;
    } else {
        _top_angvelo_face[prm_axis] = prm_angvelo01;
        _bottom_angvelo_face[prm_axis] = prm_angvelo02;
    }
    setFaceAngVelo(prm_axis, _angvelo_face[prm_axis]); //再設定して範囲内に補正
}

void LocoVehicle::setFaceAngAcce(axis prm_axis, angacce prm_angacce) {
    _angacce_face[prm_axis] = prm_angacce;
}

void LocoVehicle::setStopTargetFaceAngTwd(axis prm_axis,
                                          coord prm_tx,
                                          coord prm_ty,
                                          int prm_allow_way,
                                          angvelo prm_allow_angvelo) {
    setStopTargetFaceAng(
      prm_axis,
      UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
      prm_allow_way,
      prm_allow_angvelo
    );
}

void LocoVehicle::setStopTargetFaceAng(axis prm_axis,
                                       angle prm_target,
                                       int prm_allow_way,
                                       angvelo prm_allow_angvelo) {
    _is_targeting_face[prm_axis] = true;
    _face_targeting_stop_flg[prm_axis] = true;
    _target_face[prm_axis] = UTIL::simplifyAng(prm_target);
    _face_stop_allow_way[prm_axis] = prm_allow_way;
    _face_stop_allow_angvelo[prm_axis] = prm_allow_angvelo;
}

angle LocoVehicle::getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way) {
    return getFaceAngDistance(
               prm_axis,
               UTIL::getAngle2D(prm_tx-(_pActor->_x), prm_ty-(_pActor->_y)),
               prm_way);
}

angle LocoVehicle::getFaceAngDistance(axis prm_axis, angle prm_target, int prm_way) {
    return UTIL::getAngDiff( (*(_actor_face[prm_axis])),  prm_target, prm_way);
}

void LocoVehicle::forceMvVeloRange(velo prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void LocoVehicle::forceMvVeloRange(velo prm_velo_mv01, velo prm_velo_mv02) {
    if (prm_velo_mv01 < prm_velo_mv02) {
        _top_velo_mv = prm_velo_mv02;
        _bottom_velo_mv = prm_velo_mv01;
    } else {
        _top_velo_mv = prm_velo_mv01;
        _bottom_velo_mv = prm_velo_mv02;
    }
    setMvVelo(_velo_mv); //再設定して範囲内に補正
}

void LocoVehicle::setMvVelo(velo prm_velo_mv) {
    if (prm_velo_mv > _top_velo_mv) {
        _velo_mv = _top_velo_mv;
    } else if (prm_velo_mv < _bottom_velo_mv) {
        _velo_mv = _bottom_velo_mv;
    } else {
        _velo_mv = prm_velo_mv;
    }
}

void LocoVehicle::addMvVelo(velo prm_velo_mv_Offset) {
    setMvVelo(_velo_mv + prm_velo_mv_Offset);
}

void LocoVehicle::setMvAcce(int prm_acceMove) {
    _acc_mv = prm_acceMove;
}

frame LocoVehicle::setMvAcceToStop(coord prm_target_distance) {
    double acc = UTIL::getAcceToStop(prm_target_distance, _velo_mv);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    return (frame)((2.0*prm_target_distance) / _velo_mv); //使用フレーム数
}

frame LocoVehicle::setFaceAngAcceToStop(axis prm_axis, angle prm_target_distance) {
    double acc = UTIL::getAcceToStop(prm_target_distance, _angvelo_face[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacce_face[prm_axis] = acc;
    return (frame)((2.0*prm_target_distance) / _angvelo_face[prm_axis]); //使用フレーム数
}

frame LocoVehicle::setMvAcceByD(coord prm_target_distance, velo prm_target_velo) {
    double acc = UTIL::getAcceByVd(_velo_mv, prm_target_velo, prm_target_distance);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    return (frame)((1.0*prm_target_velo - _velo_mv) / acc); //使用フレーム数
}
frame LocoVehicle::setFaceAngAcceByD(axis prm_axis, angle prm_target_distance, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByVd(prm_target_angvelo, prm_target_distance, _angvelo_face[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacce_face[prm_axis] = acc;
    return (frame)((1.0*prm_target_angvelo - _angvelo_face[prm_axis]) / acc); //使用フレーム数
}
    // 【補足】
    // V0 <= 0  かつ  Vt <= 0 場合、あるいは  V0 >= 0  かつ  Vt >= 0  場合は、D(目標距離)が上記式で問題ない。
    // では
    // V0 < 0   かつ  Vt > 0  場合、あるいは  V0 > 0   かつ  Vt < 0   場合は、どうなるか？
    //
    //    速度(v)
    //     ^        a:加速度
    //     |        D:移動距離（目標到達速度に達するまでに費やす距離）
    //     |       V0:現時点の速度
    //     |       Vt:目標到達速度
    //     |       Te:目標到達速度に達した時の時間（フレーム数）
    //  V0 |
    //     |＼
    //     |  ＼  傾きはa
    //     | D1 ＼
    //     |      ＼ Tc     Te
    //   --+--------＼------+---> 時間(t)
    //   0 |          ＼ D2 |
    //     |            ＼  |
    //   Vt|..............＼|
    //     |
    //
    //    D を全体の移動距離として
    //    D = D1 - D2 , v = 0 の t を Tc とする
    //
    //    D1 = (1/2) V0 Tc
    //    D2 = (1/2) -Vt (Te - Tc)
    //    D = D1 - D2 より
    //    D = (1/2) V0 Tc -  { (1/2) -Vt (Te - Tc) }
    //      = (V0 Tc + Vt Te - Vt Tc) / 2    ・・・①
    //
    //    直線 v = a t + V0 において v = 0 → t = Tc であるので
    //    0 = a Tc + V0
    //    Tc = -V0 / a
    //    これを ① へ代入
    //    D = (V0 (-V0 / a) + Vt Te - Vt (-V0 / a)) / 2 ・・・②
    //    また a = (Vt - V0) / Te であるので
    //    Te = (Vt - V0) / a これを ② へ代入
    //    よって
    //    D = (V0 (-V0 / a) + Vt ((Vt - V0) / a) - Vt (-V0 / a)) / 2
    //
    //    a について解く
    //
    //    D = ( -(V0^2) / a  + (Vt (Vt - V0)) / a + (Vt V0) / a) / 2
    //    a D = { -(V0^2) + (Vt (Vt - V0)) + (Vt V0) } / 2
    //    a = { -(V0^2) + (Vt (Vt - V0)) + (Vt V0) } / 2D
    //    a = (-(V0^2) + Vt^2 - Vt V0 + Vt V0) / 2D
    //    a = (Vt^2 - V0^2) / 2D
    //
    //    結局 a = (Vt^2 - V0^2) / 2D となるので
    //    V0 <= 0  かつ  Vt <= 0 場合、あるいは  V0 >= 0  かつ  Vt >= 0  場合と同じである

coord LocoVehicle::setMvAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_mv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_mv + prm_target_velo) * prm_target_frames) / 2 ;
}
angle LocoVehicle::setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _angvelo_face[prm_axis], prm_target_angvelo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacce_face[prm_axis] = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_angvelo_face[prm_axis] + prm_target_angvelo) * prm_target_frames) / 2 ;
}

void LocoVehicle::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _rz_mv) {
        _rz_mv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_rz_mv, _ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _rz_mv;
    }
}

void LocoVehicle::addRzMvAng(angle prm_ang) {
    angle ang_offset = prm_ang;
    if (_bottom_angvelo_rz_mv > prm_ang) {
        ang_offset = _bottom_angvelo_rz_mv;
    } else if (prm_ang > _top_angvelo_rz_mv) {
        ang_offset = _top_angvelo_rz_mv;
    }
    setRzMvAng(_rz_mv + ang_offset);
}

void LocoVehicle::setRzMvAngVelo(angvelo prm_angvelo_rz_mv) {
    if (prm_angvelo_rz_mv > _top_angvelo_rz_mv) {
        _angvelo_rz_mv = _top_angvelo_rz_mv;
    } else if (prm_angvelo_rz_mv < _bottom_angvelo_rz_mv) {
        _angvelo_rz_mv = _bottom_angvelo_rz_mv;
    } else {
        _angvelo_rz_mv = prm_angvelo_rz_mv;
    }
}

void LocoVehicle::setRzMvAngAcce(angacce prm_angacce_rz_mv) {
    _angacce_rz_mv = prm_angacce_rz_mv;
}

void LocoVehicle::forceRzMvAngVeloRange(angvelo prm_angvelo_rz_mv01,
                                    angvelo prm_angvelo_rz_mv02) {
    if (prm_angvelo_rz_mv01 < prm_angvelo_rz_mv02) {
        _top_angvelo_rz_mv = prm_angvelo_rz_mv02;
        _bottom_angvelo_rz_mv = prm_angvelo_rz_mv01;
    } else {
        _top_angvelo_rz_mv = prm_angvelo_rz_mv01;
        _bottom_angvelo_rz_mv = prm_angvelo_rz_mv02;
    }
    setRzMvAngVelo(_angvelo_rz_mv); //再設定して範囲内に補正
}

void LocoVehicle::setStopTargetRzMvAng(angle prm_target_rz_mv,
                                   int prm_allow_way,
                                   angvelo prm_allow_angvelo) {
    _is_targeting_rz_mv = true;
    _rz_mv_targeting_stop_flg = true;
    _target_rz_mv = UTIL::simplifyAng(prm_target_rz_mv);
    _rz_mv_stop_allow_way = prm_allow_way;
    _rz_mv_stop_allow_angvelo = prm_allow_angvelo;
}

angle LocoVehicle::getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRzMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)), prm_way);
}

angle LocoVehicle::getRzMvAngDistance(angle prm_target_rz_mv, int prm_way) {
    return UTIL::getAngDiff(_rz_mv, prm_target_rz_mv, prm_way);
}


//void LocoVehicle::setRyMvAngTwd(coord prm_tx, coord prm_ty) {
//    setRyMvAng(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)));
//}

void LocoVehicle::setRyMvAng(angle prm_ang) {
    if (prm_ang != _ry_mv) {
        _ry_mv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_rz_mv, _ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ry_mv;
    }
}

void LocoVehicle::addRyMvAng(angle prm_ang) {
    angle ang_offset = prm_ang;
    if (_bottom_angvelo_ry_mv > prm_ang) {
        ang_offset = _bottom_angvelo_ry_mv;
    } else if (prm_ang > _top_angvelo_ry_mv) {
        ang_offset = _top_angvelo_ry_mv;
    }
    setRyMvAng(_ry_mv + ang_offset);
}

void LocoVehicle::setRyMvAngVelo(angvelo prm_angvelo_ry_mv) {
    if (prm_angvelo_ry_mv > _top_angvelo_ry_mv) {
        _angvelo_ry_mv = _top_angvelo_ry_mv;
    } else if (prm_angvelo_ry_mv < _bottom_angvelo_ry_mv) {
        _angvelo_ry_mv = _bottom_angvelo_ry_mv;
    } else {
        _angvelo_ry_mv = prm_angvelo_ry_mv;
    }
}

void LocoVehicle::setRyMvAngAcce(angacce prm_angacce_ry_mv) {
    _angacce_ry_mv = prm_angacce_ry_mv;
}

void LocoVehicle::forceRyMvAngVeloRange(angvelo prm_angvelo_ry_mv01,
                                    angvelo prm_angvelo_ry_mv02) {
    if (prm_angvelo_ry_mv01 < prm_angvelo_ry_mv02) {
        _top_angvelo_ry_mv = prm_angvelo_ry_mv02;
        _bottom_angvelo_ry_mv = prm_angvelo_ry_mv01;
    } else {
        _top_angvelo_ry_mv = prm_angvelo_ry_mv01;
        _bottom_angvelo_ry_mv = prm_angvelo_ry_mv02;
    }
    setRyMvAngVelo(_angvelo_ry_mv); //再設定して範囲内に補正
}

void LocoVehicle::forceRzRyMvAngVeloRange(angvelo prm_angvelo_rzry_mv01, angvelo prm_angvelo_rzry_mv02) {
    if (prm_angvelo_rzry_mv01 < prm_angvelo_rzry_mv02) {
        _top_angvelo_rz_mv = prm_angvelo_rzry_mv02;
        _bottom_angvelo_rz_mv = prm_angvelo_rzry_mv01;
        _top_angvelo_ry_mv = prm_angvelo_rzry_mv02;
        _bottom_angvelo_ry_mv = prm_angvelo_rzry_mv01;
    } else {
        _top_angvelo_rz_mv = prm_angvelo_rzry_mv01;
        _bottom_angvelo_rz_mv = prm_angvelo_rzry_mv02;
        _top_angvelo_ry_mv = prm_angvelo_rzry_mv01;
        _bottom_angvelo_ry_mv = prm_angvelo_rzry_mv02;
    }
    setRzMvAngVelo(_angvelo_rz_mv); //再設定して範囲内に補正
    setRyMvAngVelo(_angvelo_ry_mv); //再設定して範囲内に補正
}

void LocoVehicle::setRzRyMvAngAcce(angacce prm_angacce_rz_mv, angacce prm_angacce_ry_mv) {
    _angacce_rz_mv = prm_angacce_rz_mv;
    _angacce_ry_mv = prm_angacce_ry_mv;
}

void LocoVehicle::setRzRyMvAngVelo(angvelo prm_angvelo_rz_mv, angvelo prm_angvelo_ry_mv) {
    if (prm_angvelo_rz_mv > _top_angvelo_rz_mv) {
        _angvelo_rz_mv = _top_angvelo_rz_mv;
    } else if (prm_angvelo_rz_mv < _bottom_angvelo_rz_mv) {
        _angvelo_rz_mv = _bottom_angvelo_rz_mv;
    } else {
        _angvelo_rz_mv = prm_angvelo_rz_mv;
    }
    if (prm_angvelo_ry_mv > _top_angvelo_ry_mv) {
        _angvelo_ry_mv = _top_angvelo_ry_mv;
    } else if (prm_angvelo_ry_mv < _bottom_angvelo_ry_mv) {
        _angvelo_ry_mv = _bottom_angvelo_ry_mv;
    } else {
        _angvelo_ry_mv = prm_angvelo_ry_mv;
    }
}

void LocoVehicle::setStopTargetRyMvAng(angle prm_target_ry_mv,
                                   int prm_allow_way,
                                   angvelo prm_allow_angvelo) {
    _is_targeting_ry_mv = true;
    _ry_mv_targeting_stop_flg = true;
    _target_ry_mv = UTIL::simplifyAng(prm_target_ry_mv);
    _ry_mv_stop_allow_way = prm_allow_way;
    _ry_mv_stop_allow_angvelo = prm_allow_angvelo;
}

angle LocoVehicle::getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRyMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)), prm_way);
}

angle LocoVehicle::getRyMvAngDistance(angle prm_target_ry_mv, int prm_way) {
    return UTIL::getAngDiff(_ry_mv, prm_target_ry_mv, prm_way);
}

void LocoVehicle::getRzRyMvAngDistanceTwd(angle prm_target_rz, angle prm_target_ry, int prm_way,
                                      angle& out_d_rz, angle& out_d_ry) {
    angle target_rz = UTIL::simplifyAng(prm_target_rz);
    angle target_ry = UTIL::simplifyAng(prm_target_ry);
    angle d1_rz = getRzMvAngDistance(target_rz, prm_way); //Rzの差
    angle d1_ry = getRyMvAngDistance(target_ry, prm_way);
    angle d1 = ABS(d1_rz) + ABS(d1_ry);
    UTIL::anotherRzRy(target_rz, target_ry);
    angle d2_rz = getRzMvAngDistance(target_rz, prm_way);
    angle d2_ry = getRyMvAngDistance(target_ry, prm_way);
    angle d2 = ABS(d2_rz) + ABS(d2_ry);

    if (prm_way == TURN_ANTICLOSE_TO) {
        if (d1 >= d2) { //より遠い方を採用
            out_d_rz = d1_rz;
            out_d_ry = d1_ry;
        } else {
            out_d_rz = d2_rz;
            out_d_ry = d2_ry;
        }
    } else {
        if (d1 <= d2) { //より近い方を採用
            out_d_rz = d1_rz;
            out_d_ry = d1_ry;
        } else {
            out_d_rz = d2_rz;
            out_d_ry = d2_ry;
        }
    }
}

void LocoVehicle::getRzRyFaceAngDistanceTwd(angle prm_target_rz, angle prm_target_ry,int prm_way,
                                        angle& out_d_rz, angle& out_d_ry) {
    angle target_rz = UTIL::simplifyAng(prm_target_rz);
    angle target_ry = UTIL::simplifyAng(prm_target_ry);
    angle d1_rz = getFaceAngDistance(AXIS_Z, target_rz, TURN_CLOSE_TO);
    angle d1_ry = getFaceAngDistance(AXIS_Y, target_ry, TURN_CLOSE_TO);
    angle d1 = ABS(d1_rz) + ABS(d1_ry);
    UTIL::anotherRzRy(target_rz, target_ry);
    angle d2_rz = getFaceAngDistance(AXIS_Z, target_rz, TURN_CLOSE_TO);
    angle d2_ry = getFaceAngDistance(AXIS_Y, target_ry, TURN_CLOSE_TO);
    angle d2 = ABS(d2_rz) + ABS(d2_ry);

    if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (d1 >= d2) {
            out_d_rz = d1_rz;
            out_d_ry = d1_ry;
        } else {
            out_d_rz = d2_rz;
            out_d_ry = d2_ry;
        }
    } else {
        if (d1 <= d2) {
            out_d_rz = d1_rz;
            out_d_ry = d1_ry;
        } else {
            out_d_rz = d2_rz;
            out_d_ry = d2_ry;
        }
    }
}

void LocoVehicle::setRzRyMvAng(angle prm_rz, angle prm_ry) {
    if (prm_rz != _rz_mv || prm_ry !=_ry_mv ) {
        _rz_mv = UTIL::simplifyAng(prm_rz);
        _ry_mv = UTIL::simplifyAng(prm_ry);
        UTIL::convRzRyToVector(_rz_mv, _ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _rz_mv;
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ry_mv;
    }
}

void LocoVehicle::setRzRyMvAng(double prm_vx, double prm_vy, double prm_vz, bool prm_opt) {
    if (prm_opt) {
        angle rz_mv1, ry_mv1;
        UTIL::convVectorToRzRy(prm_vx, prm_vy, prm_vz,
                               rz_mv1, ry_mv1 );
        angle d1_rz = getRzMvAngDistance(rz_mv1, TURN_CLOSE_TO);
        angle d1_ry = getRyMvAngDistance(ry_mv1, TURN_CLOSE_TO);
        angle d1 = ABS(d1_rz) + ABS(d1_ry);

        angle rz_mv2 = rz_mv1;
        angle ry_mv2 = ry_mv1;
        UTIL::anotherRzRy(rz_mv2, ry_mv2);
        angle d2_rz = getRzMvAngDistance(rz_mv2, TURN_CLOSE_TO);
        angle d2_ry = getRyMvAngDistance(ry_mv2, TURN_CLOSE_TO);
        angle d2 = ABS(d2_rz) + ABS(d2_ry);
        if (d1 <= d2) {
            _rz_mv = rz_mv1;
            _ry_mv = ry_mv1;
        } else {
            _rz_mv = rz_mv2;
            _ry_mv = ry_mv2;
        }
    } else {
        UTIL::convVectorToRzRy(prm_vx, prm_vy, prm_vz,
                               _rz_mv, _ry_mv );
    }
    UTIL::getNormalizedVector(prm_vx, prm_vy, prm_vz,
                             _vX, _vY, _vZ);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _rz_mv;
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ry_mv;
    }
}

void LocoVehicle::setRzRyMvAngByRyRz(angle prm_ryRz_Ry, angle prm_ryRz_Rz) {
    angle RyRz_Ry = UTIL::simplifyAng(prm_ryRz_Ry);
    angle RyRz_Rz = UTIL::simplifyAng(prm_ryRz_Rz);
    double out_vY, out_vZ;
    UTIL::convRzRyToVector(RyRz_Ry, D360ANG-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    UTIL::convVectorToRzRy(_vX, _vZ, _vY, _rz_mv, _ry_mv);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _rz_mv;
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ry_mv;
    }
}


void LocoVehicle::setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない。
    } else {
        UTIL::convVectorToRzRy(vx, vy, vz,
                               _rz_mv, _ry_mv );
        UTIL::getNormalizedVector(vx, vy, vz,
                                  _vX, _vY, _vZ);
        if (_relate_RzFaceAng_with_RzMvAng_flg) {
            _pActor->_rz = _rz_mv;
        }
        if (_relate_RyFaceAng_with_RyMvAng_flg) {
            _pActor->_ry = _ry_mv;
        }
    }
}

void LocoVehicle::reverseMvAng() {
    _vX = -_vX;
    _vY = -_vY;
    _vZ = -_vZ;
    _rz_mv = UTIL::simplifyAng(_rz_mv-D180ANG);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _rz_mv;
    }
}

void LocoVehicle::setStopTargetMvAngTwd(const GeometricActor* prm_pActor_target) {
    setStopTargetMvAngTwd(
        prm_pActor_target->_x,
        prm_pActor_target->_y,
        prm_pActor_target->_z
    );
}

void LocoVehicle::setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない。
    } else {
        angle rz_target, ry_target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               rz_target, ry_target);
        setStopTargetRzMvAng(rz_target);
        setStopTargetRyMvAng(ry_target);
    }
}

void LocoVehicle::turnRzRyFaceAngTo(angle prm_rz_target, angle prm_ry_target,
                                   angvelo prm_angvelo, angacce prm_angacce,
                                   int prm_way, bool prm_optimize_ang) {
    angle out_d_rz;
    angle out_d_ry;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistanceTwd(prm_rz_target, prm_ry_target,prm_way,
                                   out_d_rz, out_d_ry);
    } else {
        out_d_rz = getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way);
        out_d_ry = getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way);
    }
    double drz = ABS(out_d_rz);
    double dry = ABS(out_d_ry);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_rz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angvelo);
            setFaceAngAcce(AXIS_Z, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angvelo);
            setFaceAngAcce(AXIS_Z, -prm_angacce);
        }

        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ry > 0) {
            setFaceAngVelo(AXIS_Y, rv);
            setFaceAngAcce(AXIS_Y, ra);
        } else {
            setFaceAngVelo(AXIS_Y, -rv);
            setFaceAngAcce(AXIS_Y, -ra);
        }
    } else if (drz < dry) {
        double t_sin_rz = ABS(ANG_SIN(UTIL::simplifyAng(prm_rz_target)) * 0.8);// Y軸回転極座標補正。0.8は緩くするため
        double hosei = 1.0 / (1.0 - t_sin_rz); //* 0.8しているので、t_sin_rz が 1.0にならないので 0除算は起こらない。


        double drr = drz / dry ;

        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_rz > 0) {
            setFaceAngVelo(AXIS_Z, rv);
            setFaceAngAcce(AXIS_Z, ra);
        } else {
            setFaceAngVelo(AXIS_Z, -rv);
            setFaceAngAcce(AXIS_Z, -ra);
        }
        if (out_d_ry > 0) {
            setFaceAngVelo(AXIS_Y, prm_angvelo*hosei);
            setFaceAngAcce(AXIS_Y, prm_angacce*hosei);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angvelo*hosei);
            setFaceAngAcce(AXIS_Y, -prm_angacce*hosei);
        }
    } else {

        double t_sin_rz = ABS(ANG_SIN(UTIL::simplifyAng(prm_rz_target)) * 0.8);// Y軸回転極座標補正。0.8は緩くするため
        double hosei = 1.0 / (1.0 - t_sin_rz); //* 0.8しているので、t_sin_rz が 1.0にならないので 0除算は起こらない。


        if (out_d_rz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angvelo);
            setFaceAngAcce(AXIS_Z, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angvelo);
            setFaceAngAcce(AXIS_Z, -prm_angacce);
        }
        if (out_d_ry > 0) {
            setFaceAngVelo(AXIS_Y, prm_angvelo*hosei);
            setFaceAngAcce(AXIS_Y, prm_angacce*hosei);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angvelo*hosei);
            setFaceAngAcce(AXIS_Y, -prm_angacce*hosei);
        }
    }

    setStopTargetFaceAng(AXIS_Z, prm_rz_target);
    setStopTargetFaceAng(AXIS_Y, prm_ry_target);
    _taget_face_alltime_pActor = nullptr;
    _taget_face_alltime_flg = false;
}

void LocoVehicle::turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                angvelo prm_angvelo, angacce prm_angacce,
                                int prm_way, bool prm_optimize_ang) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //自身の座標に等しいので、何もしない
    } else {
        angle out_rz_Target;
        angle out_ry_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_rz_Target, out_ry_Target);

        turnRzRyFaceAngTo(out_rz_Target, out_ry_Target,
                          prm_angvelo, prm_angacce,
                          prm_way, prm_optimize_ang);
    }
}


void LocoVehicle::turnFaceAng(axis prm_axis,
                             angle prm_distance,
                             angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_distance);
    setFaceAngVelo(prm_axis, ABS(prm_angvelo)*s);
    setFaceAngAcce(prm_axis, ABS(prm_angacce)*s);
    setStopTargetFaceAng(prm_axis, (*(_actor_face[prm_axis])) + prm_distance);
    _taget_face_alltime_pActor = nullptr;
    _taget_face_alltime_flg = false;
}


void LocoVehicle::turnRzFaceAngTo(angle prm_rz_target,
                                 angvelo prm_angvelo, angacce prm_angacce,
                                 int prm_way) {
    if (getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Z, prm_angvelo);
        setFaceAngAcce(AXIS_Z, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angvelo);
        setFaceAngAcce(AXIS_Z, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_Z, prm_rz_target);
    _taget_face_alltime_pActor = nullptr;
    _taget_face_alltime_flg = false;
}

void LocoVehicle::turnRyFaceAngTo(angle prm_ry_target,
                                 angvelo prm_angvelo, angacce prm_angacce,
                                 int prm_way) {
    if (getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Y, prm_angvelo);
        setFaceAngAcce(AXIS_Y, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angvelo);
        setFaceAngAcce(AXIS_Y, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_Y, prm_ry_target);
    _taget_face_alltime_pActor = nullptr;
    _taget_face_alltime_flg = false;
}

void LocoVehicle::rollFaceAngTo(angle prm_rx_target,
                               angvelo prm_angvelo, angacce prm_angacce,
                               int prm_way) {
    if (getFaceAngDistance(AXIS_X, prm_rx_target, prm_way) > 0) {
        setFaceAngVelo(AXIS_X, prm_angvelo);
        setFaceAngAcce(AXIS_X, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_X, -prm_angvelo);
        setFaceAngAcce(AXIS_X, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_X, prm_rx_target);
}

void LocoVehicle::turnRzRyMvAngTo(angle prm_rz_target, angle prm_ry_target,
                                 angvelo prm_angvelo, angacce prm_angacce,
                                 int prm_way, bool prm_optimize_ang) {
    angle out_d_rz;
    angle out_d_ry;
    if (prm_optimize_ang) {
        getRzRyMvAngDistanceTwd(prm_rz_target, prm_ry_target,prm_way,
                                out_d_rz, out_d_ry);
    } else {
        out_d_rz = getRzMvAngDistance(prm_rz_target, prm_way);
        out_d_ry = getRyMvAngDistance(prm_ry_target, prm_way);
    }

    //Rz, Ry が、目標アングルへ同時に到達するように角速度を調整
    double drz = ABS(out_d_rz);
    double dry = ABS(out_d_ry);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_rz > 0) {
            setRzMvAngVelo(prm_angvelo);
            setRzMvAngAcce(prm_angacce);
        } else {
            setRzMvAngVelo(-prm_angvelo);
            setRzMvAngAcce(-prm_angacce);
        }
        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ry > 0) {
            setRyMvAngVelo(rv);
            setRyMvAngAcce(ra);
        } else {
            setRyMvAngVelo(-rv);
            setRyMvAngAcce(-ra);
        }
    } else if (drz < dry) {
        double t_sin_rz = ABS(ANG_SIN(UTIL::simplifyAng(prm_rz_target)) * 0.8);// Y軸回転極座標補正。0.8は緩くするため
        double hosei = 1.0 / (1.0 - t_sin_rz); //* 0.8しているので、t_sin_rz が 1.0にならないので 0除算は起こらない。
        double drr = drz / dry;
        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_rz > 0) {
            setRzMvAngVelo(rv);
            setRzMvAngAcce(ra);
        } else {
            setRzMvAngVelo(-rv);
            setRzMvAngAcce(-ra);
        }
        if (out_d_ry > 0) {
            setRyMvAngVelo(prm_angvelo*hosei);
            setRyMvAngAcce(prm_angacce*hosei);
        } else {
            setRyMvAngVelo(-prm_angvelo*hosei);
            setRyMvAngAcce(-prm_angacce*hosei);
        }
    } else {

        double t_sin_rz = ABS(ANG_SIN(UTIL::simplifyAng(prm_rz_target)) * 0.8);// Y軸回転極座標補正。0.8は緩くするため
        double hosei = 1.0 / (1.0 - t_sin_rz); //* 0.8しているので、t_sin_rz が 1.0にならないので 0除算は起こらない。
        if (out_d_rz > 0) {
            setRzMvAngVelo(prm_angvelo);
            setRzMvAngAcce(prm_angacce);
        } else {
            setRzMvAngVelo(-prm_angvelo);
            setRzMvAngAcce(-prm_angacce);
        }
        if (out_d_ry > 0) {
            setRyMvAngVelo(prm_angvelo*hosei);
            setRyMvAngAcce(prm_angacce*hosei);
        } else {
            setRyMvAngVelo(-prm_angvelo*hosei);
            setRyMvAngAcce(-prm_angacce*hosei);
        }
    }
    setStopTargetRzMvAng(prm_rz_target);
    setStopTargetRyMvAng(prm_ry_target);
}

void LocoVehicle::turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                              angvelo prm_angvelo, angacce prm_angacce,
                              int prm_way, bool prm_optimize_ang) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない。
    } else {
        angle out_rz_Target;
        angle out_ry_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_rz_Target,
                               out_ry_Target);
        turnRzRyMvAngTo(out_rz_Target, out_ry_Target,
                        prm_angvelo, prm_angacce,
                        prm_way, prm_optimize_ang);
    }
}

void LocoVehicle::turnRzMvAng(angle prm_rz_distance,
                             angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_rz_distance);
    setRzMvAngVelo(ABS(prm_angvelo) * s);
    setRzMvAngAcce(ABS(prm_angacce) * s);
    setStopTargetRzMvAng(_rz_mv+prm_rz_distance);
}

void LocoVehicle::turnRyMvAng(angle prm_ry_distance,
                             angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_ry_distance);
    setRyMvAngVelo(ABS(prm_angvelo) * s);
    setRyMvAngAcce(ABS(prm_angacce) * s);
    setStopTargetRyMvAng(_ry_mv+prm_ry_distance);
}

void LocoVehicle::turnRzMvAngTo(angle prm_rz_target,
                               angvelo prm_angvelo, angacce prm_angacce,
                               int prm_way) {
    if (getRzMvAngDistance(prm_rz_target, prm_way) > 0) {
        setRzMvAngVelo(prm_angvelo);
        setRzMvAngAcce(prm_angacce);
    } else {
        setRzMvAngVelo(-prm_angvelo);
        setRzMvAngAcce(-prm_angacce);
    }
    setStopTargetRzMvAng(prm_rz_target);
}

void LocoVehicle::turnRyMvAngTo(angle prm_ry_target,
                               angvelo prm_angvelo, angacce prm_angacce,
                               int prm_way) {
    if (getRyMvAngDistance(prm_ry_target, prm_way) > 0) {
        setRyMvAngVelo(prm_angvelo);
        setRyMvAngAcce(prm_angacce);
    } else {
        setRyMvAngVelo(-prm_angvelo);
        setRyMvAngAcce(-prm_angacce);
    }
    setStopTargetRyMvAng(prm_ry_target);
}

void LocoVehicle::takeoverFrom(LocoVehicle* const prm_pLocoVehicle) {
    // キャラの移動方角単位ベクトル
    _vX = prm_pLocoVehicle->_vX;
    _vY = prm_pLocoVehicle->_vY;
    _vZ = prm_pLocoVehicle->_vZ;
    // 移動方角のZ軸回転角
    _rz_mv = prm_pLocoVehicle->_rz_mv;
    // 移動方角のY軸回転角
    _ry_mv = prm_pLocoVehicle->_ry_mv;
    // 移動速度
    _velo_mv = prm_pLocoVehicle->_velo_mv;
    // 移動速度上限
    _top_velo_mv = prm_pLocoVehicle->_top_velo_mv;
    // 移動速度下限
    _bottom_velo_mv = prm_pLocoVehicle->_bottom_velo_mv;
    // 移動加速度
    _acc_mv = prm_pLocoVehicle->_acc_mv;
    // 移動躍度
    //_jerkMv = prm_pLocoVehicle->_jerkMv;
}

void LocoVehicle::stopTurningMvAng() {
    _is_targeting_rz_mv = false;
    _rz_mv_targeting_stop_flg = false;
    _is_targeting_ry_mv = false;
    _ry_mv_targeting_stop_flg = false;
    if (_pAsstMvAng) {
        _pAsstMvAng->stopTurning();
    }
    setRzRyMvAngVelo(0, 0);
    setRzRyMvAngAcce(0, 0);
}

void LocoVehicle::stopTurningFaceAng() {
    _is_targeting_face[AXIS_X] = false;
    _is_targeting_face[AXIS_Y] = false;
    _is_targeting_face[AXIS_Z] = false;
    _taget_face_alltime_pActor = nullptr;
    _taget_face_alltime_flg = false;
    if (_pAsstFaceAng) {
        _pAsstFaceAng->stopTurn();
    }
    setFaceAngVelo(AXIS_Z, 0);
    setFaceAngVelo(AXIS_Y, 0);
    setFaceAngAcce(AXIS_Z, 0);
    setFaceAngAcce(AXIS_Y, 0);
}

bool LocoVehicle::isTurningFaceAng() const {
    if (_is_targeting_face[AXIS_X] ||
        _is_targeting_face[AXIS_Y] ||
        _is_targeting_face[AXIS_Z] ) {
        return true;
    } else {
        if (_pAsstFaceAng) {
            return _pAsstFaceAng->isTurning();
        } else {
            return false;
        }
        return false;
    }
}

bool LocoVehicle::isTurningMvAng() const {
    if (_is_targeting_rz_mv || _is_targeting_ry_mv) {
        return true;
    } else {
        if (_pAsstMvAng) {
            return _pAsstMvAng->isTurning();
        } else {
            return false;
        }
    }
}

void LocoVehicle::stop() {
   setMvAcce(0);
   setMvVelo(0);
   if (_pAsstMv) {
       _pAsstMv->stopSliding();
   }
}

LocoVehicle::~LocoVehicle() {
    GGAF_DELETE_NULLABLE(_pAsstMv);
    GGAF_DELETE_NULLABLE(_pAsstFaceAng);
    GGAF_DELETE_NULLABLE(_pAsstMvAng);
}


// 【備忘録メモ】本クラスの考え方とコメントの単語の表現
//
// ＜２種類の方向＞
// 「キャラの方向」という言葉が曖昧なため、次の２種類の単語を定義する。「移動方角（方向）」と「正面方角（方向）」。
// 「移動方角」はキャラの進行方向のみを表現する。これは「移動速度」と伴って、キャラは座標内を移動することとする。
// 「正面方角」はキャラの向き（前方方向等）のみを表現する事とする。
// キャラクタが画面の上部から下部へ移動しても、キャラクタは下を向くとは限らず自機に向いてほしい場合もある。
// または、右にキャラを向かせて、左に移動させたいこともある。それぞれ２つの方向設定が必要。
//
// ＜移動方角の２種類の表現方法＞
// キャラが進む方向、つまり「移動方角」の方向は、原点から単位球の表面に向かって伸びるベクトル (_vX, _vY, _vZ) で表す方法と、
// ２軸回転アングル値 (_rz_mv, _ry_mv) で表す方法の２種類用意した。クォータニオンは今のところ無し。
// _rz_mv は Z軸回転角、 _ry_mv は Y軸回転角 を意味している。
// これは方向ベクトルを、緯度と経度、（仰角とアジマス）の関係に見立て、対応させようとした。
// 注意することは、Y軸回転角＝経度 は常に成り立つが、Z軸回転角＝緯度 は、Z軸回転角 → Y軸回転角の順番である場合に限り成り立つ。
// 本クラスでは、「Z軸回転 → Y軸回転の順番でのZ軸回転角・Y軸回転角」を簡略して、単に「Z軸回転角・Y軸回転角」と表現する事とする。
// それぞれを「移動方角（Z軸）」「移動方角（Y軸）」と表現する事もある。
//
// ソースコード中の、変数やメソッドの
// 「RzMv」という表記は「移動方角（Z軸）」を意味している。
// 「RyMv」という表記は「移動方角（Y軸）」を意味している。
// 「RzRyMv」という表現は「Z軸回転 → Y軸回転の順番の移動方角」を表している。
//
// Z軸回転角、Y軸回転角が両方とも0度を、方向ベクトル(1, 0, 0) の方向と定義する。
// Z軸回転角の正の増加は、Z軸の正の方向を向いて反時計回り。
// Y軸回転角の正の増加は、Y軸の正の方向を向いて反時計回り。とする。
//
// ところで数学的に「方角」は、方向ベクトル（XYZの値）で表現することが多いと思う。
// しかしこの本クラスでは、よく使うのは２軸表現の方で、メソッドも _rz_mv と _ry_mv を操作するものが中心となっている。
// 実は結局内部で単位方向ベクトルを求めているのだが、座標回転計算を、整数型の _rz_mv と _ry_mv でさんざん行ってから、
// 最後に１回単位ベクトルを求める。という方が速いのではと考えたため、このような設計になった。
// TODO:最適化の余地だいぶ残っているハズ。またいつか。
// (_rz_mv, _ry_mv)をメソッドにより操作して、各フレームの最後の内部処理で方向ベクトル(_vX, _vY, _vZ) を同期させている。
// (_vX, _vY, _vZ)メンバーをメソッドを使わず直接操作すると、(_rz_mv, _ry_mv)との同期が崩れるので注意。
// 本クラスのメソッドを使用する限りでは、そんなことは起こらない。
//
// ＜移動速度:Velo or MvVelo＞
// キャラは「移動速度」(_velo_mv)を保持している。移動する方法は簡単で、基本的に毎フレーム「移動方角」に「移動速度」分動くだけ。
// 座標増分は「移動方角」(_vX, _vY, _vZ)に「移動速度」(_velo_mv)を掛け算している。
// １フレーム後の座標は現在の座標から (_vX*_velo_mv, _vY*_velo_mv, _vZ*_velo_mv) 移動した場所である。
// このベクトルに本ライブラリの単位距離(ゲーム中の長さ１と考える整数倍値）を乗じる。
// よって、(_vX*_velo_mv*LEN_UNIT, _vY*_velo_mv*LEN_UNIT, _vZ*_velo_mv*LEN_UNIT)が１フレーム後の座標増分。

// ＜正面方角:AngFace＞
// キャラのローカル座標で向いている方角（方向）を「正面方角」と呼ぶことにする。
//「正面方角」は、ワールド変換行列の軸回転と同じ回転方法である。
// ワールド変換行列の軸回転とは、X軸回転角、Y軸回転角、Z軸回転角のことで、それぞれ、
// _face[AXIS_X], _face[AXIS_Y], _face[AXIS_Z] と一致する。
// 本ライブラリでは、方向ベクトル(1, 0, 0) をキャラの「前方」と設定している。
// Xファイルなどのキャラモデルは、初期状態で正のX軸方向に向いていることを前提とする。また、モデル「上方向は」は（0, 1, 0)とする。
// ワールド変換行列の回転行列の掛ける順番は、基本的に 「X軸回転行列 > Z軸回転行列 > Y軸回転行列 > 移動行列 」 とする。
// (※  X軸 > Y軸 > Z軸 の順ではないよ！）
// よって、X軸回転角は幾ら回転させようとも、キャラが向いている方向は変わらず、残りのZ軸回転角と、Y軸回転角でキャラが向いている方向を決定することとする。
// X軸回転角はキャラのスピン、のこり２角（Z軸回転角・Y軸回転角）でキャラの「前方」方角がを決定するとした場合、
// 「正面方角」も先ほどの「移動方角」と同じように、Z軸回転角とY軸回転角（緯度と経度)の２つのアングル値
// (_face[AXIS_Z], _face[AXIS_Y])で表現できる。
// つまり、「前方」は Z軸回転角・Y軸回転角共に0度とし、例えば「後ろ」は(Z軸回転角,Y軸回転角)=(0度,180度) と表現する。。
// 単に「Z軸回転角」などと書くと、「移動方角」のZ軸回転角なのか、「正面方角」のZ軸回転角なのか曖昧になるため、
// 「正面方角(Z軸)」「正面方角(Y軸)」と書くこととする。（※「正面方角(X軸)」もあるが、これはスピンを表し向きへの影響はしない）
// ここで注意は、１つのキャラが向いている方角に対して、常に２通りのアクセスする方法があるということ。例えば、
// 「前方(1, 0, 0)を向いて真右向き」 は (正面方角(Z軸), 正面方角(Y軸))=(0, 90度) or (180度,270度) とで表現できる。
// （※正面方角(Y軸)は左手系座標のためY軸の正方向を向いて反時計回り）
// 実は 「前方」も (0度,0度) とも (180度,180度) とも表現できるし、「真後ろ」 は (0度,180度) とも (180度,0度) とも表現できる。
// 向いている方向は同じだが、姿勢(キャラの上方向)が異なる。姿勢が異なるとまずいキャラは注意すること。
// 当然、「移動方角」でも、２通りのアクセスする方法があるのだが、こちらは姿勢が無いので見た目で分からない。
// しかし角度計算するときに影響が出る場合があるので注意が必要。


// ＜自動前方向き機能＞
// さてここで 「移動方角（Z軸）」「移動方角（Y軸）」を、それぞれ「正面方角(Z軸)」「正面方角(Y軸)」 へコピーしてやると、
// 移動方角と、キャラクタの向きの同期が簡単に取れるじゃないか！
// 「自動前方向き機能」とは、「移動方角」を設定すると、それに伴って自動的に「正面方角」を設定する事とする。
// 具体的には、以下のようにフレーム毎に、アングル値を上書きコピー（同期）。或いは差分を加算（向き方向を滑らかに描画）していく。
//  ・移動方角（Z軸） → 正面方角(Z軸)
//  ・移動方角（Y軸） → 正面方角(Y軸)
// しかし「正面方角」を設定ても「移動方角」変化しない（逆は関連しない）ので注意。

// ＜角速度:AngVelo＞
// 「移動方角（Z軸）」「移動方角（Y軸）」、「正面方角(Z軸)」「正面方角(Y軸)」には、それぞれの「角速度」を設けてある。
// 例えば90度右に向きたい場合、キャラがいきなりカクっと向きを変えては悲しいので、毎フレーム角速度だけ角を加算するようにして、
// 滑らかに向きを変えるようにする。
// 「角速度」は正負の注意が必要。正の場合は反時計回り、負の場合は時計回りになる。
// 方向転換する場合、ターゲットとなる角度への到達するアプローチは正負回転の２通りだが、
// 表現を5通りの考え方で指定できるよう設計した。
// 1.「常に反時計回で行く」 TURN_ANTICLOSE_TO
// 2.「常に時計回りで行く」 TURN_CLOCKWISE
// 3.「近い角の周り方向で行く」TURN_CLOSE_TO
// 4.「遠回りな角の周り方向で行く」TURN_ANTICLOSE_TO
// 5.「現在回っている方向そのままで行く」
// である。それぞれ用途があるので、オプション引数などで、選択できるようにしたいな。→できた。



//＜その他追記、未整理＞
//・移動速度、移動方角角速度、軸回転角角速度には、それぞれ加速度も設定できる！
//・軸回転は、本当は Z > X > Y の軸回転順番にするのが一般的のようだ。つまり前方の概念はZ軸で奥であるわけだ、なるほどわかりやすい。
//  現在の X > Z > Y は、奥はZ軸だが前方はX軸である。
//  もともと2Dの横スクロールシューティングを作ろうと思っており、当初 X > Z だけで設計を行っていたのが原因である。
//  Y軸回転する気なぞ全然なかった・・・。もう遅い。でも心の中では、基本横シュー。

// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_x,_y,_z)にそれぞれの移動増分が
// 加算される。
// （※→この機能は CoordVehicle に集約され独立したクラスとなりました！）

//2010/02/19追記
// ※たまに「RyRz」という表現が存在する（「RzRy」と異なる）が、これは「Y軸回転 → Z軸回転の順番の移動方角」を表しているので注意。
//   また、「移動方角（Z軸）」を軸回転の順番の違いを明確にするため
//   「RzRyのRz」「RyRzのRz」と書いたりしているところもある。（単に「Rz」だけの場合は「RzRyのRz」を意味している）

//追記
//・滑らか移動が可能に！

//TODO:
//躍度（加加速度）の追加
//任意軸回転（クォータニオン）
//クラスの肥大化 → 駕籠(平行移動支援)を作った
//【メモ】を纏める
