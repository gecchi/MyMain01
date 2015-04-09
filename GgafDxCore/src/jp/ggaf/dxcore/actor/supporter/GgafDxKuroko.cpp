#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

#include <math.h>
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantC.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKuroko::GgafDxKuroko(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {
    _pAsstA = nullptr;
    _pAsstB = nullptr;
    _pAsstC = nullptr;
    reset();
}
GgafDxKurokoAssistantA* GgafDxKuroko::asstA() {
    return _pAsstA ? _pAsstA : _pAsstA = NEW GgafDxKurokoAssistantA(this);
}
GgafDxKurokoAssistantB* GgafDxKuroko::asstB() {
    return _pAsstB ? _pAsstB : _pAsstB = NEW GgafDxKurokoAssistantB(this);
}
GgafDxKurokoAssistantC* GgafDxKuroko::asstC() {
    return _pAsstC ? _pAsstC : _pAsstC = NEW GgafDxKurokoAssistantC(this);
}

void GgafDxKuroko::reset() {
    GGAF_DELETE_NULLABLE(_pAsstA);
    GGAF_DELETE_NULLABLE(_pAsstB);
    GGAF_DELETE_NULLABLE(_pAsstC);

    _actor_ang_face[0] = &(_pActor->_rx);
    _actor_ang_face[1] = &(_pActor->_ry);
    _actor_ang_face[2] = &(_pActor->_rz);

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
        _is_targeting_ang_face[ax] = false;
        //目標正面方角への自動停止フラグ = 無効
        _ang_face_targeting_stop_flg[ax] = false;
        //目標の正面方角
        _target_ang_face[ax] = 0; //目標正面方角への自動制御フラグ = 無効、の場合は無意味
        //目標の正面方角自動停止機能が有効になる回転方向
        _ang_face_stop_allow_way[ax] = TURN_BOTH;
        //目標の正面方角自動停止機能が有効になる角速度（回転正負共通）
        _ang_face_stop_allow_angvelo[ax] = D360ANG;
    }

    //////////////////////////////////////////////////////
    //キャラの移動方角単位ベクトル
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //移動方角のZ軸回転
    _ang_rz_mv = 0;
    //移動方角のY軸回転
    _ang_ry_mv = 0;
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
    _is_targeting_ang_rz_mv = false;
    //目標移動方角（Z軸回転）への自動停止フラグ = 無効
    _ang_rz_mv_targeting_stop_flg = false;

    //目標の移動方角（Z軸回転）
    _target_ang_rz_mv = 0;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる回転方向
    _ang_rz_mv_stop_allow_way = TURN_BOTH;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _ang_rz_mv_stop_allow_angvelo = D360ANG;
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
    _is_targeting_ang_ry_mv = false;
    //目標移動方角（Y軸回転）への自動停止フラグ = 無効
    _ang_ry_mv_targeting_stop_flg = false;
    //目標の移動方角（Y軸回転）
    _target_ang_ry_mv = 0;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる回転方向
    _ang_ry_mv_stop_allow_way = TURN_BOTH;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _ang_ry_mv_stop_allow_angvelo = D360ANG;
    //移動方角（Y軸回転）に伴いZ正面方角の同期を取る機能フラグ ＝ 無効
    _relate_RyFaceAng_with_RyMvAng_flg = false; //有効の場合は、移動方角を設定するとZ正面方角が同じになる。

    _taget_face_ang_alltime_flg = false;
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_tx = 0;
    _taget_face_ang_alltime_ty = 0;
    _taget_face_ang_alltime_tz = 0;
    _taget_face_ang_alltime_angVelo = 0;
    _taget_face_ang_alltime_angAcce = 0;
    _taget_face_ang_alltime_way = TURN_CLOSE_TO;
    _taget_face_ang_alltime_optimize_ang = true;
}

void GgafDxKuroko::behave() {
    if (_pAsstA) {
        _pAsstA->behave();
    }
    if (_pAsstB) {
        _pAsstB->behave();
    }
    if (_pAsstC) {
        _pAsstC->behave();
    }

    //正面方角処理
    for (axis ax = 0; ax < 3; ax++) {

        _angvelo_face[ax] += _angacce_face[ax];
        if (_angvelo_face[ax] > _top_angvelo_face[ax]) {
            _angvelo_face[ax] = _top_angvelo_face[ax];
        } else if (_angvelo_face[ax] < _bottom_angvelo_face[ax]) {
            _angvelo_face[ax] = _bottom_angvelo_face[ax];
        }

        if (_is_targeting_ang_face[ax]) { //ターゲット方向がある場合

            if (_angvelo_face[ax] > 0) { //反時計回りの場合
                const angle angDistance = getFaceAngDistance(ax, _target_ang_face[ax], TURN_COUNTERCLOCKWISE);
                if (_angvelo_face[ax] > angDistance && _ang_face_stop_allow_way[ax] != TURN_CLOCKWISE &&
                        _ang_face_stop_allow_angvelo[ax] >= _angvelo_face[ax]) {
                    _angvelo_face[ax] = angDistance;
                    if (_ang_face_targeting_stop_flg[ax]) {
                        _is_targeting_ang_face[ax] = false; //フラグを戻して終了
                        _ang_face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    // なにもしなくてよい
                }
            } else if (_angvelo_face[ax] < 0) { //時計回りの場合
                const angle angDistance = getFaceAngDistance(ax, _target_ang_face[ax], TURN_CLOCKWISE);
                if (_angvelo_face[ax] < angDistance && _ang_face_stop_allow_way[ax] != TURN_COUNTERCLOCKWISE
                        && -1 * _ang_face_stop_allow_angvelo[ax] <= _angvelo_face[ax]) { //目標を行き過ぎてしまいそう・・・な日
                    _angvelo_face[ax] = angDistance;
                    if (_ang_face_targeting_stop_flg[ax]) {
                        _is_targeting_ang_face[ax] = false; //フラグを戻して終了
                        _ang_face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    // なにもしなくてよい
                }
            } else {
                //_angvelo_face[ax] == 0
                const angle angDistance = getFaceAngDistance(ax, _target_ang_face[ax], TURN_CLOSE_TO);
                if (angDistance == 0) {
                    if (_ang_face_targeting_stop_flg[ax]) {
                        _is_targeting_ang_face[ax] = false; //フラグを戻して終了
                        _ang_face_targeting_stop_flg[ax] = false;
                    }
                } else {
                    _TRACE_("＜警告＞GgafDxKuroko::behave() : _angvelo_face["<<ax<<"]="<<_angvelo_face[ax]<<" で、ターゲットまでの距離angDistance="<<angDistance<<" なので、"<<
                            "いつまでもターゲットに到達しないのではないだろうか？_pActor="<<_pActor->getName()<<"("<<_pActor<<")（要確認）");
                }
            }

            //Actorに反映
            (*(_actor_ang_face[ax])) = UTIL::simplifyAng((*(_actor_ang_face[ax])) + _angvelo_face[ax]);
            if (_is_targeting_ang_face[ax] == false) {
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
            (*(_actor_ang_face[ax])) = UTIL::simplifyAng((*(_actor_ang_face[ax])) +  _angvelo_face[ax]);
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
    if (_is_targeting_ang_rz_mv) {

        _angvelo_rz_mv += _angacce_rz_mv;
        setRzMvAngVelo(_angvelo_rz_mv);

        if (_angvelo_rz_mv > 0) { //反時計回りの場合
            const angle angDistance = getRzMvAngDistance(_target_ang_rz_mv, TURN_COUNTERCLOCKWISE);
            if (_angvelo_rz_mv > angDistance && _ang_rz_mv_stop_allow_way != TURN_CLOCKWISE
                    && _ang_rz_mv_stop_allow_angvelo >= _angvelo_rz_mv) { //目標を行き過ぎてしまいそう・・・な日
                addRzMvAng(angDistance);
                if (_ang_rz_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ang_rz_mv = false; //フラグを戻して終了
                    _ang_rz_mv_targeting_stop_flg = false;
                }
            } else {
                addRzMvAng(_angvelo_rz_mv);
            }
        } else if (_angvelo_rz_mv < 0) { //時計回りの場合

            const angle angDistance = getRzMvAngDistance(_target_ang_rz_mv, TURN_CLOCKWISE);
            if (_angvelo_rz_mv < angDistance && _ang_rz_mv_stop_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_ang_rz_mv_stop_allow_angvelo <= _angvelo_rz_mv) {
                addRzMvAng(angDistance);
                if (_ang_rz_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ang_rz_mv = false; //フラグを戻して終了
                    _ang_rz_mv_targeting_stop_flg = false;
                }
            } else {
                addRzMvAng(_angvelo_rz_mv);
            }
        } else {
            const angle angDistance = getRzMvAngDistance(_target_ang_rz_mv, TURN_CLOSE_TO);
            if (angDistance == 0) {
                addRzMvAng(angDistance);
                if (_ang_rz_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ang_rz_mv = false; //フラグを戻して終了
                    _ang_rz_mv_targeting_stop_flg = false;
                }
            } else {
                _TRACE_("＜警告＞GgafDxKuroko::behave() : _angvelo_rz_mv="<<_angvelo_rz_mv<<" で、ターゲットまでの距離angDistance="<<angDistance<<" なので、"<<
                        "いつまでもターゲットに到達しないのではないだろうか？_pActor="<<_pActor->getName()<<"("<<_pActor<<")（要確認）");
            }
        }
        if (_is_targeting_ang_rz_mv == false) {
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
    if (_is_targeting_ang_ry_mv) {

        _angvelo_ry_mv += _angacce_ry_mv;
        setRyMvAngVelo(_angvelo_ry_mv);

        if (_angvelo_ry_mv > 0) { //現在は反時計回りの場合
            angle angDistance = getRyMvAngDistance(_target_ang_ry_mv, TURN_COUNTERCLOCKWISE);
            if (_angvelo_ry_mv > angDistance &&
                _ang_ry_mv_stop_allow_way != TURN_CLOCKWISE &&
                _ang_ry_mv_stop_allow_angvelo >= _angvelo_ry_mv)
            { //目標を行き過ぎてしまいそう・・・な日
                addRyMvAng(angDistance);
                if (_ang_ry_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ang_ry_mv = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_angvelo_ry_mv);
            }
        } else if (_angvelo_ry_mv < 0) { //現在は時計回りの場合

            angle angDistance = getRyMvAngDistance(_target_ang_ry_mv, TURN_CLOCKWISE);
            if (_angvelo_ry_mv < angDistance &&
                _ang_ry_mv_stop_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_ang_ry_mv_stop_allow_angvelo <= _angvelo_ry_mv)
            {
                addRyMvAng(angDistance);
                if (_ang_ry_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ang_ry_mv = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_angvelo_ry_mv);
            }
        } else { //_angvelo_ry_mv==0
            angle angDistance = getRyMvAngDistance(_target_ang_ry_mv, TURN_CLOSE_TO);
            if (angDistance == 0) {
                addRyMvAng(angDistance);
                if (_ang_ry_mv_targeting_stop_flg) { //停止指定ありならば
                    _is_targeting_ang_ry_mv = false; //フラグを戻して終了
                    _ang_ry_mv_targeting_stop_flg = false;
                }
            } else {
                _TRACE_("＜警告＞GgafDxKuroko::behave() : _angvelo_ry_mv="<<_angvelo_ry_mv<<" で、ターゲットまでの距離angDistance="<<angDistance<<" なので、"<<
                        "いつまでもターゲットに到達しないのではないだろうか？_pActor="<<_pActor->getName()<<"("<<_pActor<<")（要確認）");
            }
        }
        if (_is_targeting_ang_ry_mv == false) {
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
    if (_taget_face_ang_alltime_flg && _is_targeting_ang_face[AXIS_Z] == false && _is_targeting_ang_face[AXIS_Y] == false) {
        if (_taget_face_ang_alltime_pActor) {
            keepOnTurningFaceAngTwd(
                    _taget_face_ang_alltime_pActor,
                    _taget_face_ang_alltime_angVelo,
                    _taget_face_ang_alltime_angAcce,
                    _taget_face_ang_alltime_way,
                    _taget_face_ang_alltime_optimize_ang);
        } else {
            keepOnTurningFaceAngTwd(
                    _taget_face_ang_alltime_pActor->_x,
                    _taget_face_ang_alltime_pActor->_y,
                    _taget_face_ang_alltime_pActor->_z,
                    _taget_face_ang_alltime_angVelo,
                    _taget_face_ang_alltime_angAcce,
                    _taget_face_ang_alltime_way,
                    _taget_face_ang_alltime_optimize_ang);
        }

    }
    //Actorに反映
    _pActor->_x += (coord)(_vX * _velo_mv);
    _pActor->_y += (coord)(_vY * _velo_mv);
    _pActor->_z += (coord)(_vZ * _velo_mv);
}

void GgafDxKuroko::setFaceAngVelo(axis prm_axis, angvelo prm_angvelo) {
    if (prm_angvelo > _top_angvelo_face[prm_axis]) {
        _angvelo_face[prm_axis] = _top_angvelo_face[prm_axis];
    } else if (prm_angvelo < _bottom_angvelo_face[prm_axis]) {
        _angvelo_face[prm_axis] = _bottom_angvelo_face[prm_axis];
    } else {
        _angvelo_face[prm_axis] = prm_angvelo;
    }
}

void GgafDxKuroko::setRollPitchYawFaceAngVelo(angvelo prm_axis_x_angvelo,
                                              angvelo prm_axis_z_angvelo,
                                              angvelo prm_axis_y_angvelo) {
    setFaceAngVelo(AXIS_X, prm_axis_x_angvelo);
    setFaceAngVelo(AXIS_Z, prm_axis_z_angvelo);
    setFaceAngVelo(AXIS_Y, prm_axis_y_angvelo);
}

void GgafDxKuroko::forceFaceAngVeloRange(axis prm_axis,
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

void GgafDxKuroko::setFaceAngAcce(axis prm_axis, angacce prm_angacce) {
    _angacce_face[prm_axis] = prm_angacce;
}

void GgafDxKuroko::setStopTargetFaceAngTwd(axis prm_axis,
                                           coord prm_tx,
                                           coord prm_ty,
                                           int prm_way_allow,
                                           angvelo prm_angvelo_allow) {
    setStopTargetFaceAng(
      prm_axis,
      UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
      prm_way_allow,
      prm_angvelo_allow
    );
}

void GgafDxKuroko::setStopTargetFaceAng(axis prm_axis,
                                        angle prm_ang_target,
                                        int prm_way_allow,
                                        angvelo prm_angvelo_allow) {
    _is_targeting_ang_face[prm_axis] = true;
    _ang_face_targeting_stop_flg[prm_axis] = true;
    _target_ang_face[prm_axis] = UTIL::simplifyAng(prm_ang_target);
    _ang_face_stop_allow_way[prm_axis] = prm_way_allow;
    _ang_face_stop_allow_angvelo[prm_axis] = prm_angvelo_allow;
}

angle GgafDxKuroko::getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way) {
    return getFaceAngDistance(
               prm_axis,
               UTIL::getAngle2D(prm_tx-(_pActor->_x), prm_ty-(_pActor->_y)),
               prm_way);
}

angle GgafDxKuroko::getFaceAngDistance(axis prm_axis, angle prm_ang_target, int prm_way) {
    return UTIL::getAngDiff( (*(_actor_ang_face[prm_axis])),  prm_ang_target, prm_way);
}

void GgafDxKuroko::forceMvVeloRange(velo prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDxKuroko::forceMvVeloRange(velo prm_velo_mv01, velo prm_velo_mv02) {
    if (prm_velo_mv01 < prm_velo_mv02) {
        _top_velo_mv = prm_velo_mv02;
        _bottom_velo_mv = prm_velo_mv01;
    } else {
        _top_velo_mv = prm_velo_mv01;
        _bottom_velo_mv = prm_velo_mv02;
    }
    setMvVelo(_velo_mv); //再設定して範囲内に補正
}

void GgafDxKuroko::setMvVelo(velo prm_velo_mv) {
    if (prm_velo_mv > _top_velo_mv) {
        _velo_mv = _top_velo_mv;
    } else if (prm_velo_mv < _bottom_velo_mv) {
        _velo_mv = _bottom_velo_mv;
    } else {
        _velo_mv = prm_velo_mv;
    }
}

void GgafDxKuroko::addMvVelo(velo prm_velo_mv_Offset) {
    setMvVelo(_velo_mv + prm_velo_mv_Offset);
}

void GgafDxKuroko::setMvAcce(int prm_acceMove) {
    _acc_mv = prm_acceMove;
}

frame GgafDxKuroko::setMvAcceToStop(coord prm_target_distance) {
    double acc = UTIL::getAcceToStop(prm_target_distance, _velo_mv);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    return (frame)((2.0*prm_target_distance) / _velo_mv); //使用フレーム数
}

frame GgafDxKuroko::setFaceAngAcceToStop(axis prm_axis, angle prm_target_angle_distance) {
    double acc = UTIL::getAcceToStop(prm_target_angle_distance, _angvelo_face[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacce_face[prm_axis] = acc;
    return (frame)((2.0*prm_target_angle_distance) / _angvelo_face[prm_axis]); //使用フレーム数
}

frame GgafDxKuroko::setMvAcceByD(coord prm_target_distance, velo prm_target_velo) {
    double acc = UTIL::getAcceByVd(_velo_mv, prm_target_velo, prm_target_distance);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _acc_mv = acc;
    return (frame)((1.0*prm_target_velo - _velo_mv) / acc); //使用フレーム数
}
frame GgafDxKuroko::setFaceAngAcceByD(axis prm_axis, angle prm_target_angle_distance, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByVd(prm_target_angvelo, prm_target_angle_distance, _angvelo_face[prm_axis]);
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

coord GgafDxKuroko::setMvAcceByT(frame prm_target_frames, velo prm_target_velo) {
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
angle GgafDxKuroko::setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo) {
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

void GgafDxKuroko::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _ang_rz_mv) {
        _ang_rz_mv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_ang_rz_mv, _ang_ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
}

void GgafDxKuroko::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_bottom_angvelo_rz_mv > prm_angDistance) {
        angOffset = _bottom_angvelo_rz_mv;
    } else if (prm_angDistance > _top_angvelo_rz_mv) {
        angOffset = _top_angvelo_rz_mv;
    }
    setRzMvAng(_ang_rz_mv + angOffset);
}

void GgafDxKuroko::setRzMvAngVelo(angvelo prm_angvelo_rz_mv) {
    if (prm_angvelo_rz_mv > _top_angvelo_rz_mv) {
        _angvelo_rz_mv = _top_angvelo_rz_mv;
    } else if (prm_angvelo_rz_mv < _bottom_angvelo_rz_mv) {
        _angvelo_rz_mv = _bottom_angvelo_rz_mv;
    } else {
        _angvelo_rz_mv = prm_angvelo_rz_mv;
    }
}

void GgafDxKuroko::setRzMvAngAcce(angacce prm_angacce_rz_mv) {
    _angacce_rz_mv = prm_angacce_rz_mv;
}

void GgafDxKuroko::forceRzMvAngVeloRange(angvelo prm_angvelo_rz_mv01,
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

void GgafDxKuroko::setStopTargetRzMvAng(angle prm_target_ang_rz_mv,
                                        int prm_way_allow,
                                        angvelo prm_angvelo_allow) {
    _is_targeting_ang_rz_mv = true;
    _ang_rz_mv_targeting_stop_flg = true;
    _target_ang_rz_mv = UTIL::simplifyAng(prm_target_ang_rz_mv);
    _ang_rz_mv_stop_allow_way = prm_way_allow;
    _ang_rz_mv_stop_allow_angvelo = prm_angvelo_allow;
}

angle GgafDxKuroko::getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRzMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)), prm_way);
}

angle GgafDxKuroko::getRzMvAngDistance(angle prm_target_ang_rz_mv, int prm_way) {
    return UTIL::getAngDiff(_ang_rz_mv, prm_target_ang_rz_mv, prm_way);
}


//void GgafDxKuroko::setRyMvAngTwd(coord prm_tx, coord prm_ty) {
//    setRyMvAng(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)));
//}

void GgafDxKuroko::setRyMvAng(angle prm_ang) {
    if (prm_ang != _ang_ry_mv) {
        _ang_ry_mv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_ang_rz_mv, _ang_ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ang_ry_mv;
    }
}

void GgafDxKuroko::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_bottom_angvelo_ry_mv > prm_angDistance) {
        angOffset = _bottom_angvelo_ry_mv;
    } else if (prm_angDistance > _top_angvelo_ry_mv) {
        angOffset = _top_angvelo_ry_mv;
    }
    setRyMvAng(_ang_ry_mv + angOffset);
}

void GgafDxKuroko::setRyMvAngVelo(angvelo prm_angvelo_ry_mv) {
    if (prm_angvelo_ry_mv > _top_angvelo_ry_mv) {
        _angvelo_ry_mv = _top_angvelo_ry_mv;
    } else if (prm_angvelo_ry_mv < _bottom_angvelo_ry_mv) {
        _angvelo_ry_mv = _bottom_angvelo_ry_mv;
    } else {
        _angvelo_ry_mv = prm_angvelo_ry_mv;
    }
}

void GgafDxKuroko::setRyMvAngAcce(angacce prm_angacce_ry_mv) {
    _angacce_ry_mv = prm_angacce_ry_mv;
}

void GgafDxKuroko::forceRyMvAngVeloRange(angvelo prm_angvelo_ry_mv01,
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

void GgafDxKuroko::forceRzRyMvAngVeloRange(angvelo prm_angvelo_rzry_mv01, angvelo prm_angvelo_rzry_mv02) {
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

void GgafDxKuroko::setRzRyMvAngAcce(angacce prm_angacce_rz_mv, angacce prm_angacce_ry_mv) {
    _angacce_rz_mv = prm_angacce_rz_mv;
    _angacce_ry_mv = prm_angacce_ry_mv;
}

void GgafDxKuroko::setRzRyMvAngVelo(angvelo prm_angvelo_rz_mv, angvelo prm_angvelo_ry_mv) {
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

void GgafDxKuroko::setStopTargetRyMvAng(angle prm_target_ang_ry_mv,
                                        int prm_way_allow,
                                        angvelo prm_angvelo_allow) {
    _is_targeting_ang_ry_mv = true;
    _ang_ry_mv_targeting_stop_flg = true;
    _target_ang_ry_mv = UTIL::simplifyAng(prm_target_ang_ry_mv);
    _ang_ry_mv_stop_allow_way = prm_way_allow;
    _ang_ry_mv_stop_allow_angvelo = prm_angvelo_allow;
}

angle GgafDxKuroko::getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRyMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
                                        prm_way);
}

angle GgafDxKuroko::getRyMvAngDistance(angle prm_target_ang_ry_mv, int prm_way) {
    return UTIL::getAngDiff(_ang_ry_mv, prm_target_ang_ry_mv, prm_way);
}

void GgafDxKuroko::getRzRyMvAngDistanceTwd(angle prm_target_ang_rz, angle prm_target_ang_ry, int prm_way,
                                           angle& out_d_ang_rz, angle& out_d_ang_ry) {
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        //目標に到達するためには、回り方が常に２パターンある。
        //それぞれ球面上の２点の距離を簡易近似値（速度優先のため）で比較し、近いと思われるほうを採用する。
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOSE_TO); //Rzの差
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) { //より近い方を採用
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) {
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 >= d2) { //より遠い方を採用
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        angle d1_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOCKWISE);
        angle d1_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getRzMvAngDistance(prm_target_ang_rz, TURN_CLOCKWISE);
        angle d2_angRy = getRyMvAngDistance(prm_target_ang_ry, TURN_CLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else {
        //おかしい
        throwGgafCriticalException("GgafDxKuroko::getRzRyMvAngDistanceTwd() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDxKuroko::getRzRyFaceAngDistanceTwd(angle prm_target_ang_rz, angle prm_target_ang_ry,int prm_way,
                                               angle& out_d_ang_rz, angle& out_d_ang_ry) {
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }

    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 >= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_COUNTERCLOCKWISE);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_COUNTERCLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOCKWISE);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOCKWISE);
        angle d1 = ABS(d1_angRz) + ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_ang_rz, prm_target_ang_ry);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_ang_rz, TURN_CLOCKWISE);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_ang_ry, TURN_CLOCKWISE);
        angle d2 = ABS(d2_angRz) + ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_ang_rz = d1_angRz;
            out_d_ang_ry = d1_angRy;
        } else {
            out_d_ang_rz = d2_angRz;
            out_d_ang_ry = d2_angRy;
        }
    } else {
        //おかしい
        throwGgafCriticalException("GgafDxKuroko::getRzRyMvAngDistanceTwd() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDxKuroko::setRzRyMvAng(angle prm_ang_rz, angle prm_ang_ry) {
    if (prm_ang_rz != _ang_rz_mv || prm_ang_ry !=_ang_ry_mv ) {
        _ang_rz_mv = UTIL::simplifyAng(prm_ang_rz);
        _ang_ry_mv = UTIL::simplifyAng(prm_ang_ry);
        UTIL::convRzRyToVector(_ang_rz_mv, _ang_ry_mv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ang_ry_mv;
    }
}

void GgafDxKuroko::setRzRyMvAng_by_RyRz(angle prm_ang_ryRz_Ry, angle prm_ang_ryRz_Rz) {
    angle RyRz_Ry = UTIL::simplifyAng(prm_ang_ryRz_Ry);
    angle RyRz_Rz = UTIL::simplifyAng(prm_ang_ryRz_Rz);
    float out_vY, out_vZ;
    UTIL::convRzRyToVector(RyRz_Ry, D360ANG-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    UTIL::convVectorToRzRy(_vX, _vZ, _vY, _ang_rz_mv, _ang_ry_mv);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        _pActor->_ry = _ang_ry_mv;
    }
}


void GgafDxKuroko::setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない。
    } else {
        UTIL::convVectorToRzRy( vx,  vy,  vz,
                               _vX, _vY, _vZ,
                               _ang_rz_mv, _ang_ry_mv );
        if (_relate_RzFaceAng_with_RzMvAng_flg) {
            _pActor->_rz = _ang_rz_mv;
        }
        if (_relate_RyFaceAng_with_RyMvAng_flg) {
            _pActor->_ry = _ang_ry_mv;
        }
    }
}

void GgafDxKuroko::reverseMvAng() {
    _vX = -_vX;
    _vY = -_vY;
    _vZ = -_vZ;
    _ang_rz_mv = UTIL::simplifyAng(_ang_rz_mv-D180ANG);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        _pActor->_rz = _ang_rz_mv;
    }
}

void GgafDxKuroko::setStopTargetMvAngTwd(const GgafDxGeometricActor* prm_pActor_target) {
    setStopTargetMvAngTwd(
        prm_pActor_target->_x,
        prm_pActor_target->_y,
        prm_pActor_target->_z
    );
}

void GgafDxKuroko::setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない。
    } else {
        angle angRz_Target;
        angle angRy_Target;
        float dummy1, dummy2, dummy3;

        UTIL::convVectorToRzRy(
                       vx, vy, vz,
                       dummy1, dummy2, dummy3,
                       angRz_Target, angRy_Target
                     );
        setStopTargetRzMvAng(angRz_Target);
        setStopTargetRyMvAng(angRy_Target);
    }
}

void GgafDxKuroko::turnRzRyFaceAngTo(angle prm_ang_rz_target, angle prm_ang_ry_target,
                                     angvelo prm_angvelo, angacce prm_angacce,
                                     int prm_way, bool prm_optimize_ang) {
    angle out_d_ang_rz;
    angle out_d_ang_ry;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target,prm_way,
                                   out_d_ang_rz, out_d_ang_ry);
    } else {
        out_d_ang_rz = getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way);
        out_d_ang_ry = getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way);
    }
    double drz = ABS(out_d_ang_rz);
    double dry = ABS(out_d_ang_ry);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_ang_rz > 0) {
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
        if (out_d_ang_ry > 0) {
            setFaceAngVelo(AXIS_Y, rv);
            setFaceAngAcce(AXIS_Y, ra);
        } else {
            setFaceAngVelo(AXIS_Y, -rv);
            setFaceAngAcce(AXIS_Y, -ra);
        }
    } else if (drz < dry) {
        double drr = drz / dry ;

        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ang_rz > 0) {
            setFaceAngVelo(AXIS_Z, rv);
            setFaceAngAcce(AXIS_Z, ra);
        } else {
            setFaceAngVelo(AXIS_Z, -rv);
            setFaceAngAcce(AXIS_Z, -ra);
        }
        if (out_d_ang_ry > 0) {
            setFaceAngVelo(AXIS_Y, prm_angvelo);
            setFaceAngAcce(AXIS_Y, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angvelo);
            setFaceAngAcce(AXIS_Y, -prm_angacce);
        }
    } else {
        if (out_d_ang_rz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angvelo);
            setFaceAngAcce(AXIS_Z, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angvelo);
            setFaceAngAcce(AXIS_Z, -prm_angacce);
        }
        if (out_d_ang_ry > 0) {
            setFaceAngVelo(AXIS_Y, prm_angvelo);
            setFaceAngAcce(AXIS_Y, prm_angacce);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angvelo);
            setFaceAngAcce(AXIS_Y, -prm_angacce);
        }
    }

    setStopTargetFaceAng(AXIS_Z, prm_ang_rz_target);
    setStopTargetFaceAng(AXIS_Y, prm_ang_ry_target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                  angvelo prm_angvelo, angacce prm_angacce,
                                  int prm_way, bool prm_optimize_ang) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //自身の座標に等しいので、何もしない
    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target, out_angRy_Target);

        turnRzRyFaceAngTo(out_angRz_Target, out_angRy_Target,
                          prm_angvelo, prm_angacce,
                          prm_way, prm_optimize_ang);
    }
}


void GgafDxKuroko::turnFaceAng(axis prm_axis,
                               angle prm_angular_distance,
                               angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_angular_distance);
    setFaceAngVelo(prm_axis, ABS(prm_angvelo)*s);
    setFaceAngAcce(prm_axis, ABS(prm_angacce)*s);
    setStopTargetFaceAng(prm_axis, (*(_actor_ang_face[prm_axis])) + prm_angular_distance);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}


void GgafDxKuroko::turnRzFaceAngTo(angle prm_ang_rz_target,
                                    angvelo prm_angvelo, angacce prm_angacce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Z, prm_angvelo);
        setFaceAngAcce(AXIS_Z, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angvelo);
        setFaceAngAcce(AXIS_Z, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_Z, prm_ang_rz_target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::turnRyFaceAngTo(angle prm_ang_ry_target,
                                   angvelo prm_angvelo, angacce prm_angacce,
                                   int prm_way) {
    if (getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Y, prm_angvelo);
        setFaceAngAcce(AXIS_Y, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angvelo);
        setFaceAngAcce(AXIS_Y, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_Y, prm_ang_ry_target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKuroko::rollFaceAngTo(angle prm_ang_rx_Target,
                                   angvelo prm_angvelo, angacce prm_angacce,
                                   int prm_way) {
    if (getFaceAngDistance(AXIS_X, prm_ang_rx_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_X, prm_angvelo);
        setFaceAngAcce(AXIS_X, prm_angacce);
    } else {
        setFaceAngVelo(AXIS_X, -prm_angvelo);
        setFaceAngAcce(AXIS_X, -prm_angacce);
    }
    setStopTargetFaceAng(AXIS_X, prm_ang_rx_Target);
}

void GgafDxKuroko::turnRzRyMvAngTo(angle prm_ang_rz_target, angle prm_ang_ry_target,
                                   angvelo prm_angvelo, angacce prm_angacce,
                                   int prm_way, bool prm_optimize_ang) {
    angle out_d_ang_rz;
    angle out_d_ang_ry;
    if (prm_optimize_ang) {
        getRzRyMvAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target,prm_way,
                                out_d_ang_rz, out_d_ang_ry);
    } else {
        out_d_ang_rz = getRzMvAngDistance(prm_ang_rz_target, prm_way);
        out_d_ang_ry = getRyMvAngDistance(prm_ang_ry_target, prm_way);
    }

    //Rz, Ry が、目標アングルへ同時に到達するように角速度を調整
    double drz = ABS(out_d_ang_rz);
    double dry = ABS(out_d_ang_ry);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_ang_rz > 0) {
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
        if (out_d_ang_ry > 0) {
            setRyMvAngVelo(rv);
            setRyMvAngAcce(ra);
        } else {
            setRyMvAngVelo(-rv);
            setRyMvAngAcce(-ra);
        }
    } else if (drz < dry) {
        double drr = drz / dry;

        angvelo rv = prm_angvelo*drr;
        if (rv == 0 && prm_angvelo > 0) {
            rv = ABS(prm_angvelo);
        }
        angacce ra = prm_angacce*drr;
        if (ra == 0 && prm_angacce > 0) {
            ra = ABS(prm_angacce);
        }
        if (out_d_ang_rz > 0) {
            setRzMvAngVelo(rv);
            setRzMvAngAcce(ra);
        } else {
            setRzMvAngVelo(-rv);
            setRzMvAngAcce(-ra);
        }
        if (out_d_ang_ry > 0) {
            setRyMvAngVelo(prm_angvelo);
            setRyMvAngAcce(prm_angacce);
        } else {
            setRyMvAngVelo(-prm_angvelo);
            setRyMvAngAcce(-prm_angacce);
        }
    } else {
        if (out_d_ang_rz > 0) {
            setRzMvAngVelo(prm_angvelo);
            setRzMvAngAcce(prm_angacce);
        } else {
            setRzMvAngVelo(-prm_angvelo);
            setRzMvAngAcce(-prm_angacce);
        }
        if (out_d_ang_ry > 0) {
            setRyMvAngVelo(prm_angvelo);
            setRyMvAngAcce(prm_angacce);
        } else {
            setRyMvAngVelo(-prm_angvelo);
            setRyMvAngAcce(-prm_angacce);
        }
    }
    setStopTargetRzMvAng(prm_ang_rz_target);
    setStopTargetRyMvAng(prm_ang_ry_target);
}

void GgafDxKuroko::turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                angvelo prm_angvelo, angacce prm_angacce,
                                int prm_way, bool prm_optimize_ang) {
    coord vx = prm_tx - _pActor->_x;
    coord vy = prm_ty - _pActor->_y;
    coord vz = prm_tz - _pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない。
    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target,
                               out_angRy_Target);
        turnRzRyMvAngTo(out_angRz_Target, out_angRy_Target,
                        prm_angvelo, prm_angacce,
                        prm_way, prm_optimize_ang);
    }
}

void GgafDxKuroko::turnRzMvAng(angle prm_angular_distance,
                               angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_angular_distance);
    setRzMvAngVelo(ABS(prm_angvelo) * s);
    setRzMvAngAcce(ABS(prm_angacce) * s);
    setStopTargetRzMvAng(_ang_rz_mv+prm_angular_distance);
}

void GgafDxKuroko::turnRyMvAng(angle prm_angular_distance,
                               angvelo prm_angvelo, angacce prm_angacce) {
    int s = SGN(prm_angular_distance);
    setRyMvAngVelo(ABS(prm_angvelo) * s);
    setRyMvAngAcce(ABS(prm_angacce) * s);
    setStopTargetRyMvAng(_ang_ry_mv+prm_angular_distance);
}

void GgafDxKuroko::turnRzMvAngTo(angle prm_ang_rz_target,
                                 angvelo prm_angvelo, angacce prm_angacce,
                                 int prm_way) {
    if (getRzMvAngDistance(prm_ang_rz_target, prm_way) > 0) {
        setRzMvAngVelo(prm_angvelo);
        setRzMvAngAcce(prm_angacce);
    } else {
        setRzMvAngVelo(-prm_angvelo);
        setRzMvAngAcce(-prm_angacce);
    }
    setStopTargetRzMvAng(prm_ang_rz_target);
}

void GgafDxKuroko::turnRyMvAngTo(angle prm_ang_ry_target,
                                 angvelo prm_angvelo, angacce prm_angacce,
                                 int prm_way) {
    if (getRyMvAngDistance(prm_ang_ry_target, prm_way) > 0) {
        setRyMvAngVelo(prm_angvelo);
        setRyMvAngAcce(prm_angacce);
    } else {
        setRyMvAngVelo(-prm_angvelo);
        setRyMvAngAcce(-prm_angacce);
    }
    setStopTargetRyMvAng(prm_ang_ry_target);
}

void GgafDxKuroko::takeoverMvFrom(GgafDxKuroko* const prm_pKuroko) {
    // キャラの移動方角単位ベクトル
    _vX = prm_pKuroko->_vX;
    _vY = prm_pKuroko->_vY;
    _vZ = prm_pKuroko->_vZ;
    // 移動方角のZ軸回転角
    _ang_rz_mv = prm_pKuroko->_ang_rz_mv;
    // 移動方角のY軸回転角
    _ang_ry_mv = prm_pKuroko->_ang_ry_mv;
    // 移動速度
    _velo_mv = prm_pKuroko->_velo_mv;
    // 移動速度上限
    _top_velo_mv = prm_pKuroko->_top_velo_mv;
    // 移動速度下限
    _bottom_velo_mv = prm_pKuroko->_bottom_velo_mv;
    // 移動加速度
    _acc_mv = prm_pKuroko->_acc_mv;
    // 移動躍度
    //_jerkMv = prm_pKuroko->_jerkMv;
}

void GgafDxKuroko::stopTurnMvAng() {
    _is_targeting_ang_rz_mv = false;
    _ang_rz_mv_targeting_stop_flg = false;
    _is_targeting_ang_ry_mv = false;
    _ang_ry_mv_targeting_stop_flg = false;
    if (_pAsstC) {
        _pAsstC->stopTurnMvAng();
    }
    setRzRyMvAngVelo(0, 0);
    setRzRyMvAngAcce(0, 0);
}

void GgafDxKuroko::stopTurnFaceAng() {
    _is_targeting_ang_face[AXIS_X] = false;
    _is_targeting_ang_face[AXIS_Y] = false;
    _is_targeting_ang_face[AXIS_Z] = false;
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
    if (_pAsstB) {
        _pAsstB->stopTurnFaceAng();
    }
    setFaceAngVelo(AXIS_Z, 0);
    setFaceAngVelo(AXIS_Y, 0);
    setFaceAngAcce(AXIS_Z, 0);
    setFaceAngAcce(AXIS_Y, 0);
}

bool GgafDxKuroko::isTurningFaceAng() const {
    if (_is_targeting_ang_face[AXIS_X] ||
        _is_targeting_ang_face[AXIS_Y] ||
        _is_targeting_ang_face[AXIS_Z] ) {
        return true;
    } else {
        if (_pAsstB) {
            return _pAsstB->isTurningFaceAng();
        } else {
            return false;
        }
        return false;
    }
}

bool GgafDxKuroko::isTurningMvAng() const {
    if (_is_targeting_ang_rz_mv || _is_targeting_ang_ry_mv) {
        return true;
    } else {
        if (_pAsstC) {
            return _pAsstC->isTurningMvAng();
        } else {
            return false;
        }
    }
}

void GgafDxKuroko::stopMv() {
   setMvAcce(0);
   setMvVelo(0);
   if (_pAsstA) {
       _pAsstA->stopSlidingMv();
   }
}

GgafDxKuroko::~GgafDxKuroko() {
    GGAF_DELETE_NULLABLE(_pAsstA);
    GGAF_DELETE_NULLABLE(_pAsstB);
    GGAF_DELETE_NULLABLE(_pAsstC);
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
// ２軸回転アングル値 (_ang_rz_mv, _ang_ry_mv) で表す方法の２種類用意した。クォータニオンは今のところ無し。
// _ang_rz_mv は Z軸回転角、 _ang_ry_mv は Y軸回転角 を意味している。
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
// しかしこの本クラスでは、よく使うのは２軸表現の方で、メソッドも _ang_rz_mv と _ang_ry_mv を操作するものが中心となっている。
// 実は結局内部で単位方向ベクトルを求めているのだが、座標回転計算を、整数型の _ang_rz_mv と _ang_ry_mv でさんざん行ってから、
// 最後に１回単位ベクトルを求める。という方が速いのではと考えたため、このような設計になった。
// TODO:最適化の余地だいぶ残っているハズ。またいつか。
// (_ang_rz_mv, _ang_ry_mv)をメソッドにより操作して、各フレームの最後の内部処理で方向ベクトル(_vX, _vY, _vZ) を同期させている。
// (_vX, _vY, _vZ)メンバーをメソッドを使わず直接操作すると、(_ang_rz_mv, _ang_ry_mv)との同期が崩れるので注意。
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
// _angFace[AXIS_X], _angFace[AXIS_Y], _angFace[AXIS_Z] と一致する。
// 本ライブラリでは、方向ベクトル(1, 0, 0) をキャラの「前方」と設定している。
// Xファイルなどのキャラモデルは、初期状態で正のX軸方向に向いていることを前提とする。また、モデル「上方向は」は（0, 1, 0)とする。
// ワールド変換行列の回転行列の掛ける順番は、基本的に 「X軸回転行列 > Z軸回転行列 > Y軸回転行列 > 移動行列 」 とする。
// (※  X軸 > Y軸 > Z軸 の順ではないよ！）
// よって、X軸回転角は幾ら回転させようとも、キャラが向いている方向は変わらず、残りのZ軸回転角と、Y軸回転角でキャラが向いている方向を決定することとする。
// X軸回転角はキャラのスピン、のこり２角（Z軸回転角・Y軸回転角）でキャラの「前方」方角がを決定するとした場合、
// 「正面方角」も先ほどの「移動方角」と同じように、Z軸回転角とY軸回転角（緯度と経度)の２つのアングル値
// (_angFace[AXIS_Z], _angFace[AXIS_Y])で表現できる。
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
//  もともと2Dの横スクロールシューティングを作ろうと思っており、当初 X > Z だけで設計を行っていたのが原因であるが、もうもどれない。
//  まさか、3Dシューティングにするとは自分でも思ってもみなかった・・・

// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_x,_y,_z)にそれぞれの移動増分が
// 加算される。
// （※→この機能は GgafDxAxesMover に集約され独立したクラスとなりました！）

//2010/02/19追記
// ※たまに「RyRz」という表現が存在する（「RzRy」と異なる）が、これは「Y軸回転 → Z軸回転の順番の移動方角」を表しているので注意。
//   また、「移動方角（Z軸）」を軸回転の順番の違いを明確にするため
//   「RzRyのRz」「RyRzのRz」と書いたりしているところもある。（単に「Rz」だけの場合は「RzRyのRz」を意味している）

//追記
//・滑らか移動が可能に！

//TODO:
//躍度（加加速度）の追加
//任意軸回転（クォータニオン）
//クラスの肥大化 → 平行移動支援を作った
//【メモ】を纏める
