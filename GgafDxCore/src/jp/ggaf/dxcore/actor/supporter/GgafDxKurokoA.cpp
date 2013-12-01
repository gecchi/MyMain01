#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoA::GgafDxKurokoA(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {

    for (int i = 0; i < 3; i++) { // i=0:X軸、1:Y軸、2:Z軸 を表す
        //正面方角
        _angFace[i] = 0; //0 angle は ３時の方角を向いている
        //正面方角の角速度（正面方角の増分）= 0 angle/fream
        _angveloFace[i] = 0; //1フレームに加算される正面方角の角増分。デフォルトは正面方角の角増分無し、つまり振り向き無し。
        //正面方角の角速度上限 ＝ 360,000 angle/fream
        _angveloTopFace[i] = D360ANG; //_angveloFace[n] の増分の上限。デフォルトは1フレームで好きな正面方角に振り向く事が出来る事を意味する
        //正面方角の角速度下限 ＝ -360,000 angle/fream
        _angveloBottomFace[i] = D360ANG * -1; //_angveloFace[n] の増分の下限。デフォルトは1フレームで好きな正面方角に振り向く事が出来る事を意味する
        //正面方角の角加速度（角速度の増分） ＝ 0 angle/fream^2
        _angacceFace[i] = 0; //_angveloFace[n] の増分。デフォルトは正面方角の角加速度無し

        _angjerkFace[i] = 0;
        //目標正面方角への自動向きフラグ = 無効
        _face_ang_targeting_flg[i] = false;
        //目標正面方角への自動停止フラグ = 無効
        _face_ang_targeting_stop_flg[i] = false;
        //目標の正面方角
        _angTargetFace[i] = 0; //目標正面方角への自動制御フラグ = 無効、の場合は無意味
        //目標の正面方角自動停止機能が有効になる回転方向
        _face_ang_target_allow_way[i] = TURN_BOTH;
        //目標の正面方角自動停止機能が有効になる角速度（回転正負共通）
        _face_ang_target_allow_velo[i] = D180ANG;
    }

    //////////////////////////////////////////////////////
    //キャラの移動方角単位ベクトル
    _vX = 1.0f;
    _vY = _vZ = 0.0f;
    //移動方角のZ軸回転
    _angRzMv = 0;
    //移動方角のY軸回転
    _angRyMv = 0;
    //移動速度
    _veloMv = 0;
    //移動速度上限 = 256 px/fream
    _veloTopMv = INT_MAX; //_veloMv が 256000(=256px) を上回る移動量であっても、強制的に座標増分は 256px に抑えられる。
    //移動速度下限 = 0   px/fream
    _veloBottomMv = INT_MIN; //_veloMv が -256000(-256px) を下回る移動量があっても、強制的に座標増分は -256000px に抑えられる。
    //移動加速度（移動速度の増分） = 0 px/fream^2
    _accMv = 0; //_veloMv の増分。デフォルトは加速無し

    //_jerkMv = 0;
    //移動方角（Z軸回転）の角速度 = 0 angle/fream
    _angveloRzMv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Z軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRzTopMv = D360ANG; //_angveloRzMv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRzBottomMv = D360ANG * -1; //_angveloRzMv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Z軸回転）の角加速度 = 0 angle/fream^2
    _angacceRzMv = 0; //_angveloRzMv の増分。デフォルトは移動方角の角加速度無し

    _angjerkRzMv = 0;
    //目標移動方角（Z軸回転）への自動向きフラグ = 無効
    _mv_ang_rz_target_flg = false;
    //目標移動方角（Z軸回転）への自動停止フラグ = 無効
    _mv_ang_rz_target_stop_flg = false;

    //目標の移動方角（Z軸回転）
    _angTargetRzMv = 0;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる回転方向
    _mv_ang_rz_target_allow_way = TURN_BOTH;
    //目標の移動方角（Z軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _mv_ang_rz_target_allow_velo = D180ANG;
    //移動方角（Z軸回転）に伴いZ正面方角の同期を取る機能フラグ ＝ 無効
    _relate_RzFaceAng_with_RzMvAng_flg = false; //有効の場合は、移動方角を設定するとZ正面方角が同じになる。

    //移動方角（Y軸回転）の角速度 = 0 angle/fream
    _angveloRyMv = 0; //1フレームに加算される移動方角の角増分。デフォルトは移動方角の角増分無し、つまり直線移動。
    //移動方角（Y軸回転）の角速度上限 = +360,000 angle/fream
    _angveloRyTopMv = D360ANG; //_angveloRyMv の増分の上限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角速度下限 = -360,000 angle/fream
    _angveloRyBottomMv = D360ANG * -1; //_angveloRyMv の増分の下限。デフォルトは1フレームで好きな移動方向に変更が出来る事を意味する
    //移動方角（Y軸回転）の角加速度 = 0 angle/fream^2
    _angacceRyMv = 0; //_angveloRyMv の増分。デフォルトは移動方角の角加速度無し

    _angjerkRyMv = 0;
    //目標移動方角（Y軸回転）への自動向きフラグ = 無効
    _mv_ang_ry_target_flg = false;
    //目標移動方角（Y軸回転）への自動停止フラグ = 無効
    _mv_ang_ry_target_stop_flg = false;
    //目標の移動方角（Y軸回転）
    _angTargetRyMv = 0;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる回転方向
    _mv_ang_ry_target_allow_way = TURN_BOTH;
    //目標の移動方角（Y軸回転）自動停止機能が有効になる移動方角角速度(角速度正負共通)
    _mv_ang_ry_target_allow_velo = D180ANG;
    //移動方角（Y軸回転）に伴いZ正面方角の同期を取る機能フラグ ＝ 無効
    _relate_RyFaceAng_with_RyMvAng_flg = false; //有効の場合は、移動方角を設定するとZ正面方角が同じになる。

    _slide_mv_flg = false;
    _slide_mv_endacc_flg = true;
    _slide_mv_top_velo = 0;
    _slide_mv_end_velo = 0;
    _slide_mv_target_distance = 0;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = 0;
    _slide_mv_frame_of_spent = 0;
    _slide_mv_p1 = 0;
    _slide_mv_p2 = 0;
    _slide_mv_progress = -1;


    _taget_face_ang_alltime_flg = false;
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_tx = 0;
    _taget_face_ang_alltime_ty = 0;
    _taget_face_ang_alltime_tz = 0;
    _taget_face_ang_alltime_angVelo = 0;
    _taget_face_ang_alltime_angAcce = 0;
    _taget_face_ang_alltime_way = TURN_CLOSE_TO;
    _taget_face_ang_alltime_optimize_ang = true;


    _smooth_turn_rz_faceang_flg = false;
    _smooth_turn_rz_faceang_endacc_flg = true;
    _smooth_turn_rz_faceang_top_angvelo = 0;
    _smooth_turn_rz_faceang_end_angvelo = 0;
    _smooth_turn_rz_faceang_target_distanceangle = 0;
    _smooth_turn_rz_faceang_turned_angles = 0;
    _smooth_turn_rz_faceang_angacce_a0 = 0;
    _smooth_turn_rz_faceang_targetangle_sgn = 1;
    _smooth_turn_rz_faceang_target_frames = 0;
    _smooth_turn_rz_faceang_frame_of_spent = 0;
    _smooth_turn_rz_faceang_p0 = 0;
    _smooth_turn_rz_faceang_p1 = 0;
    _smooth_turn_rz_faceang_p2 = 0;
    _smooth_turn_rz_faceang_progress = -1;
}

void GgafDxKurokoA::behave() {

    //正面方角処理
    for (int i = 0; i < 3; i++) {
        if (_face_ang_targeting_flg[i]) { //ターゲット方向がある場合
            _angveloFace[i] += _angacceFace[i];
            if (_angveloFace[i] > _angveloTopFace[i]) {
                _angveloFace[i] = _angveloTopFace[i];
            } else if (_angveloFace[i] < _angveloBottomFace[i]) {
                _angveloFace[i] = _angveloBottomFace[i];
            }

            if (_angveloFace[i] > 0) { //反時計回りの場合
                angle angDistance = getFaceAngDistance((axis)i, _angTargetFace[i], TURN_COUNTERCLOCKWISE);
                if (_angveloFace[i] > angDistance && _face_ang_target_allow_way[i] != TURN_CLOCKWISE
                        && _face_ang_target_allow_velo[i] >= _angveloFace[i]) {
                    addFaceAng((axis)i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) {
                        _face_ang_targeting_flg[i] = false; //フラグを戻して終了
                        _face_ang_targeting_stop_flg[i] = false;
                    }
                } else {
                    addFaceAng((axis)i, _angveloFace[i]);
                }
            } else if (_angveloFace[i] < 0) { //時計回りの場合
                angle angDistance = getFaceAngDistance((axis)i, _angTargetFace[i], TURN_CLOCKWISE);
                if (_angveloFace[i] < angDistance && _face_ang_target_allow_way[i] != TURN_COUNTERCLOCKWISE
                        && -1 * _face_ang_target_allow_velo[i] <= _angveloFace[i]) { //目標を行き過ぎてしまいそう・・・な日
                    addFaceAng((axis)i, angDistance);
                    if (_face_ang_targeting_stop_flg[i]) { //停止して有りならば
                        _face_ang_targeting_flg[i] = false; //フラグを戻して終了
                    }
                } else {
                    addFaceAng((axis)i, _angveloFace[i]);
                }
            } else {
                //_angveloFace[i] == 0
                addFaceAng((axis)i, 0);
            }

            if (_face_ang_targeting_flg[i] == false) {
                //目標方向に到達した時の処理
                //_angveloTopFace[i] = D360ANG; //正面方角の角速度上限 ＝ 360,000 angle/fream
                //_angveloBottomFace[i] = D360ANG * -1; //正面方角の角速度下限 ＝ -360,000 angle/fream

                //目標方向に到達した時、停止処理を行なう
                _angacceFace[i] = 0; //軸回転方向角、角速度を０へ
                setFaceAngVelo((axis)i, 0); //軸回転方向角、角加速度を０へ
            }

        } else {
            //if (_angacceFace[i] != 0) {
            //フレーム毎の正面方角旋廻の処理
            _angveloFace[i] += _angacceFace[i];
            if (_angveloFace[i] != 0) {
                addFaceAng((axis)i, _angveloFace[i]);
            }
            //}
        }
    }



    //なめらか回転シークエンス起動時
    if (_smooth_turn_rz_faceang_flg) {
        if (_smooth_turn_rz_faceang_target_frames < 0) {
            //目標距離指定の場合
            if (_smooth_turn_rz_faceang_progress == 0) {
                //回復フェーズ
                setFaceAngAcce(AXIS_Z, _smooth_turn_rz_faceang_angacce_a0);
                _smooth_turn_rz_faceang_progress++;
            } else if (_smooth_turn_rz_faceang_progress == 1) {
                //回復中
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_p0) {
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 2) {
                //加速設定
                setFaceAngAcceByD(
                    AXIS_Z,
                    _smooth_turn_rz_faceang_p1-_smooth_turn_rz_faceang_turned_angles,
                    _smooth_turn_rz_faceang_top_angvelo);
                _smooth_turn_rz_faceang_progress++;
            } else if (_smooth_turn_rz_faceang_progress == 3) {
                //加速中
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_p1) {
                    //p1 に到達すれば 等速へ
                    setFaceAngAcce(AXIS_Z, 0);
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_top_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 4) {
                //等速中
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setFaceAngAcceByD(
                        AXIS_Z,
                        _smooth_turn_rz_faceang_target_distanceangle - _smooth_turn_rz_faceang_turned_angles,
                        _smooth_turn_rz_faceang_end_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 5) {
                //減速中
                if (_pActor->getBehaveingFrame() % 4U == 0) {
                    //補正・補正・補正
                    setFaceAngAcceByD(
                            AXIS_Z,
                            _smooth_turn_rz_faceang_target_distanceangle - _smooth_turn_rz_faceang_turned_angles,
                            _smooth_turn_rz_faceang_end_angvelo);
                }
                if (_smooth_turn_rz_faceang_turned_angles >= _smooth_turn_rz_faceang_target_distanceangle) {
                    //目標距離へ到達
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_end_angvelo);
                    if (_smooth_turn_rz_faceang_endacc_flg) {
                        setFaceAngAcce(AXIS_Z, 0);
                    }
                    _smooth_turn_rz_faceang_progress++;
                    _smooth_turn_rz_faceang_flg = false; //おしまい
                }
            }
        } else {
            //目標時間指定の場合
            if (_smooth_turn_rz_faceang_progress == 0) {
                _TRACE_("_smooth_turn_rz_faceang_progress == 0");
                _TRACE_("_smooth_turn_rz_faceang_p1="<<_smooth_turn_rz_faceang_p1<<" _smooth_turn_rz_faceang_top_angvelo="<<_smooth_turn_rz_faceang_top_angvelo);
                //加速設定
                setFaceAngAcceByT(AXIS_Z, _smooth_turn_rz_faceang_p1, _smooth_turn_rz_faceang_top_angvelo);
                _smooth_turn_rz_faceang_progress++;
            } else if (_smooth_turn_rz_faceang_progress == 1) {
                _TRACE_("_smooth_turn_rz_faceang_progress == 1");
                _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<" _smooth_turn_rz_faceang_p1="<<_smooth_turn_rz_faceang_p1);
                //加速中
                if (_smooth_turn_rz_faceang_frame_of_spent >= _smooth_turn_rz_faceang_p1) {
                    //p1 に到達すれば 等速へ
                    setFaceAngAcce(AXIS_Z, 0);
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_top_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 2) {
                _TRACE_("_smooth_turn_rz_faceang_progress == 2");
                _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<"  _smooth_turn_rz_faceang_p2="<<_smooth_turn_rz_faceang_p2);
                //等速中
                if (_smooth_turn_rz_faceang_frame_of_spent >= _smooth_turn_rz_faceang_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setFaceAngAcceByT(AXIS_Z, _smooth_turn_rz_faceang_target_frames - _smooth_turn_rz_faceang_frame_of_spent, _smooth_turn_rz_faceang_end_angvelo);
                    _smooth_turn_rz_faceang_progress++;
                }
            } else if (_smooth_turn_rz_faceang_progress == 3) {

                _TRACE_("_smooth_turn_rz_faceang_progress == 3");
                _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<"  _smooth_turn_rz_faceang_target_frames="<<_smooth_turn_rz_faceang_target_frames);

                //減速中
                if (_pActor->getBehaveingFrame() % 4U == 0) {
                    //補正・補正・補正
                    setFaceAngAcceByT(AXIS_Z, _smooth_turn_rz_faceang_target_frames - _smooth_turn_rz_faceang_frame_of_spent, _smooth_turn_rz_faceang_end_angvelo);
                }

                if (_smooth_turn_rz_faceang_frame_of_spent >= _smooth_turn_rz_faceang_target_frames) {

                    _TRACE_("//目標距離へ到達");
                    _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent<<"  _smooth_turn_rz_faceang_target_frames="<<_smooth_turn_rz_faceang_target_frames);


                    //目標距離へ到達
                    setFaceAngVelo(AXIS_Z, _smooth_turn_rz_faceang_end_angvelo);
                    if (_smooth_turn_rz_faceang_endacc_flg) {
                        setFaceAngAcce(AXIS_Z, 0);
                    }
                    _smooth_turn_rz_faceang_progress++;
                    _smooth_turn_rz_faceang_flg = false; //おしまい
                }
            }
        }
    } else {
        _smooth_turn_rz_faceang_progress = -1;
    }

    if (_smooth_turn_rz_faceang_flg) {
        _smooth_turn_rz_faceang_frame_of_spent++;
        _smooth_turn_rz_faceang_turned_angles += ABS(_angveloFace[AXIS_Z]);
    } else {

    }


























    //Actorに反映
    _pActor->_rx = _angFace[AXIS_X];
    _pActor->_ry = _angFace[AXIS_Y];
    _pActor->_rz = _angFace[AXIS_Z];

    ///////////////////////////////////////////////////Mover

    //_accMv += _jerkMv;
    //移動加速度の処理
    _veloMv += _accMv;
    if (_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    }
    //なめらか移動シークエンス起動時
    if (_slide_mv_flg) {
        if (_slide_mv_target_frames < 0) {
            //目標距離指定の場合
            if (_slide_mv_progress == 0) {
                //加速設定
                setMvAcceByD(_slide_mv_p1, _slide_mv_top_velo);
                _slide_mv_progress++;
            } else if (_slide_mv_progress == 1) {
                //加速中
                if (_slide_mv_moved_distances >= _slide_mv_p1) {
                    //p1 に到達すれば 等速へ
                    setMvAcce(0);
                    setMvVelo(_slide_mv_top_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 2) {
                //等速中
                if (_slide_mv_moved_distances >= _slide_mv_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setMvAcceByD(_slide_mv_target_distance - _slide_mv_moved_distances, _slide_mv_end_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 3) {
                //減速中
                if (_pActor->getBehaveingFrame() % 8U == 0) {
                    //補正・補正・補正
                    setMvAcceByD(_slide_mv_target_distance - _slide_mv_moved_distances, _slide_mv_end_velo);
                }

                if (_slide_mv_moved_distances >= _slide_mv_target_distance) {
                    //目標距離へ到達
                    setMvVelo(_slide_mv_end_velo);
                    if (_slide_mv_endacc_flg) {
                        setMvAcce(0);
                    }
                    _slide_mv_progress++;
                    _slide_mv_flg = false; //おしまい
                }
            }
        } else {
            //目標時間指定の場合
            if (_slide_mv_progress == 0) {
                //加速設定
                setMvAcceByT(_slide_mv_p1, _slide_mv_top_velo);
                _slide_mv_progress++;
            } else if (_slide_mv_progress == 1) {
                //加速中
                if (_slide_mv_frame_of_spent >= _slide_mv_p1) {
                    //p1 に到達すれば 等速へ
                    setMvAcce(0);
                    setMvVelo(_slide_mv_top_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 2) {
                //等速中
                if (_slide_mv_frame_of_spent >= _slide_mv_p2) {
                    //p2 に到達すれば 次回フレームから減速へ
                    setMvAcceByT(_slide_mv_target_frames - _slide_mv_frame_of_spent, _slide_mv_end_velo);
                    _slide_mv_progress++;
                }
            } else if (_slide_mv_progress == 3) {
                //減速中
                if (_pActor->getBehaveingFrame() % 8U == 0) {
                    //補正・補正・補正
                    setMvAcceByT(_slide_mv_target_frames - _slide_mv_frame_of_spent, _slide_mv_end_velo);
                }

                if (_slide_mv_frame_of_spent >= _slide_mv_target_frames) {
                    //目標距離へ到達
                    setMvVelo(_slide_mv_end_velo);
                    if (_slide_mv_endacc_flg) {
                        setMvAcce(0);
                    }
                    _slide_mv_progress++;
                    _slide_mv_flg = false; //おしまい
                }
            }
        }
    } else {
        _slide_mv_progress = -1;
    }

    if (_slide_mv_flg) {
        if (_slide_mv_target_frames < 0) {
            _slide_mv_moved_distances+=ABS(_veloMv);
        } else {
            _slide_mv_frame_of_spent++;
        }
    } else {

    }

    ///////////
    //目標移動方角（Z軸回転）アングル自動停止機能使用時の場合
    if (_mv_ang_rz_target_flg) {

        _angveloRzMv += _angacceRzMv;
        setRzMvAngVelo(_angveloRzMv);

        if (_angveloRzMv > 0) { //反時計回りの場合
            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_COUNTERCLOCKWISE);
            if (_angveloRzMv > angDistance && _mv_ang_rz_target_allow_way != TURN_CLOCKWISE
                    && _mv_ang_rz_target_allow_velo >= _angveloRzMv) { //目標を行き過ぎてしまいそう・・・な日
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //停止指定ありならば
                    _mv_ang_rz_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else if (_angveloRzMv < 0) { //時計回りの場合

            angle angDistance = getRzMvAngDistance(_angTargetRzMv, TURN_CLOCKWISE);
            if (_angveloRzMv < angDistance && _mv_ang_rz_target_allow_way != TURN_COUNTERCLOCKWISE
                    && -1*_mv_ang_rz_target_allow_velo <= _angveloRzMv) {
                addRzMvAng(angDistance);
                if (_mv_ang_rz_target_stop_flg) { //停止指定ありならば
                    _mv_ang_rz_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRzMvAng(_angveloRzMv);
            }
        } else {
            addRzMvAng(0);
        }
        if (_mv_ang_rz_target_flg == false) {
            //_angveloRzTopMv = D360ANG; //移動方角（Z軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRzBottomMv = D360ANG * -1; //移動方角（Z軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRzMv = 0; //Z軸移動方向角、角加速度を０へ
            setRzMvAngVelo(0); //Z軸移動方向角、角速度を０へ
        }

    } else {
        //if (_angacceRzMv != 0) {

        _angacceRzMv += _angjerkRzMv;
        //フレーム毎の移動方角（Z軸回転）旋廻の処理
        _angveloRzMv += _angacceRzMv;
        if (_angveloRzMv != 0) {
            addRzMvAng(_angveloRzMv);
        }
        //}
    }
    ////////////////
    //目標移動方角（Y軸回転）アングル自動停止機能使用時の場合
    if (_mv_ang_ry_target_flg) {

        _angveloRyMv += _angacceRyMv;
        setRyMvAngVelo(_angveloRyMv);

        if (_angveloRyMv > 0) { //現在は反時計回りの場合
            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_COUNTERCLOCKWISE);
            if (_angveloRyMv > angDistance &&
                _mv_ang_ry_target_allow_way != TURN_CLOCKWISE &&
                _mv_ang_ry_target_allow_velo >= _angveloRyMv)
            { //目標を行き過ぎてしまいそう・・・な日
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //停止指定ありならば
                    _mv_ang_ry_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_angveloRyMv);
            }
        } else if (_angveloRyMv < 0) { //現在は時計回りの場合

            angle angDistance = getRyMvAngDistance(_angTargetRyMv, TURN_CLOCKWISE);
            if (_angveloRyMv < angDistance &&
                _mv_ang_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
                -1*_mv_ang_ry_target_allow_velo <= _angveloRyMv)
            {
                addRyMvAng(angDistance);
                if (_mv_ang_ry_target_stop_flg) { //停止指定ありならば
                    _mv_ang_ry_target_flg = false; //フラグを戻して終了
                }
            } else {
                addRyMvAng(_angveloRyMv);
            }
        } else {
            //_angveloRyMv==0
            addRyMvAng(0);
        }
        if (_mv_ang_ry_target_flg == false) {
            //_angveloRyTopMv = D360ANG; //移動方角（Y軸回転）の角速度上限 ＝ 360,000 angle/fream
            //_angveloRyBottomMv = D360ANG*-1; //移動方角（Y軸回転）の角速度下限 ＝ -360,000 angle/fream

            //目標方向に到達した時、停止処理を行なう
            _angacceRyMv = 0; //Y軸移動方向角、角加速度を０へ
            setRyMvAngVelo(0); //Y軸移動方向角、角速度を０へ
        }

    } else {
        //if (_angacceRyMv != 0) {
        _angacceRyMv += _angjerkRyMv;
        //フレーム毎の移動方角（Y軸回転）旋廻の処理
        _angveloRyMv += _angacceRyMv;
        if(_angveloRyMv != 0) {
            addRyMvAng(_angveloRyMv);
        }
        //}
    }
    ///////////////
    if (_taget_face_ang_alltime_flg && _face_ang_targeting_flg[AXIS_Z] == false && _face_ang_targeting_flg[AXIS_Y] == false) {
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
    _pActor->_x += (coord)(_vX * _veloMv);
    _pActor->_y += (coord)(_vY * _veloMv);
    _pActor->_z += (coord)(_vZ * _veloMv);
}

void GgafDxKurokoA::setFaceAng(axis prm_axis, angle prm_angFace) {
    _angFace[prm_axis] = UTIL::simplifyAng(prm_angFace);
}

void GgafDxKurokoA::setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    UTIL::convVectorToRzRy(
                   prm_tx - _pActor->_x,
                   prm_ty - _pActor->_y,
                   prm_tz - _pActor->_z,
                   _angFace[AXIS_Z],
                   _angFace[AXIS_Y]
                 );
}

void GgafDxKurokoA::addFaceAng(axis prm_axis, angle prm_angDistance) {
    angle angOffsetrot_FaceAng;
    angOffsetrot_FaceAng = prm_angDistance;
    if (_angveloBottomFace[prm_axis] > prm_angDistance) {
        angOffsetrot_FaceAng = _angveloBottomFace[prm_axis];
    } else if (prm_angDistance > _angveloTopFace[prm_axis]) {
        angOffsetrot_FaceAng = _angveloTopFace[prm_axis];
    }
    setFaceAng(prm_axis, _angFace[prm_axis] + angOffsetrot_FaceAng);
}

void GgafDxKurokoA::setFaceAngVelo(axis prm_axis, angvelo prm_angveloRot) {
    if (prm_angveloRot > _angveloTopFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloTopFace[prm_axis];
    } else if (prm_angveloRot < _angveloBottomFace[prm_axis]) {
        _angveloFace[prm_axis] = _angveloBottomFace[prm_axis];
    } else {
        _angveloFace[prm_axis] = prm_angveloRot;
    }
}

void GgafDxKurokoA::setFaceAngVelo(angvelo prm_axis_x_angveloRot,
                                   angvelo prm_axis_y_angveloRot,
                                   angvelo prm_axis_z_angveloRot) {
    setFaceAngVelo(AXIS_X, prm_axis_x_angveloRot);
    setFaceAngVelo(AXIS_Y, prm_axis_y_angveloRot);
    setFaceAngVelo(AXIS_Z, prm_axis_z_angveloRot);
}

void GgafDxKurokoA::forceFaceAngVeloRange(axis prm_axis,
                                          angvelo prm_angveloRot01,
                                          angvelo prm_angveloRot02) {
    if (prm_angveloRot01 < prm_angveloRot02) {
        _angveloTopFace[prm_axis] = prm_angveloRot02;
        _angveloBottomFace[prm_axis] = prm_angveloRot01;
    } else {
        _angveloTopFace[prm_axis] = prm_angveloRot01;
        _angveloBottomFace[prm_axis] = prm_angveloRot02;
    }
    setFaceAngVelo(prm_axis, _angveloFace[prm_axis]); //再設定して範囲内に補正
}

void GgafDxKurokoA::setFaceAngAcce(axis prm_axis, angacce prm_angacceRot) {
    _angacceFace[prm_axis] = prm_angacceRot;
}

void GgafDxKurokoA::setStopTargetFaceAngTwd(axis prm_axis,
                                            coord prm_tx,
                                            coord prm_ty,
                                            int prm_way_allow,
                                            angvelo prm_angveloAllowRyMv) {
    setStopTargetFaceAng(
      prm_axis,
      UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
      prm_way_allow,
      prm_angveloAllowRyMv
    );
}

void GgafDxKurokoA::setStopTargetFaceAng(axis prm_axis,
                                         angle prm_angTargetRot,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllow) {
    _face_ang_targeting_flg[prm_axis] = true;
    _face_ang_targeting_stop_flg[prm_axis] = true;
    _angTargetFace[prm_axis] = UTIL::simplifyAng(prm_angTargetRot);
    _face_ang_target_allow_way[prm_axis] = prm_way_allow;
    _face_ang_target_allow_velo[prm_axis] = prm_angveloAllow;
}

angle GgafDxKurokoA::getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way) {
    return getFaceAngDistance(
               prm_axis,
               UTIL::getAngle2D(prm_tx-(_pActor->_x), prm_ty-(_pActor->_y)),
               prm_way);
}

angle GgafDxKurokoA::getFaceAngDistance(axis prm_axis, angle prm_angTargetRot, int prm_way) {
    angle _angTargetRot;
    _angTargetRot = UTIL::simplifyAng(prm_angTargetRot);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < D180ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //重なってる場合
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis]
                    + D180ANG) {
                return _angTargetRot - _angFace[prm_axis];
            } else if (_angTargetRot == _angFace[prm_axis] + D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return D180ANG;
            } else if (_angFace[prm_axis] + D180ANG < _angTargetRot && _angTargetRot <= D360ANG) {
                return -1 * (_angFace[prm_axis] + (D360ANG - _angTargetRot));
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - D180ANG) {
                return D360ANG - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis] - D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -D180ANG;
            } else if (_angFace[prm_axis] - D180ANG < _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return -1 * (_angFace[prm_axis] - _angTargetRot);
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //重なってる場合
                return 0;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= D360ANG) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < D180ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return D360ANG - _angFace[prm_axis] + _angTargetRot;
            } else if (_angTargetRot == _angFace[prm_axis]) {
                //重なってる場合
                return D360ANG;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot < _angFace[prm_axis] + D180ANG) {
                return -1 * ( _angFace[prm_axis] + (D360ANG -_angTargetRot));
            } else if (_angTargetRot == _angFace[prm_axis] + D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return D180ANG;
            } else if (_angFace[prm_axis] + D180ANG < _angTargetRot && _angTargetRot <= D360ANG) {
                return _angTargetRot - _angFace[prm_axis];
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            if (0 <= _angTargetRot && _angTargetRot < _angFace[prm_axis] - D180ANG) {
                return -1 * (_angTargetRot - _angFace[prm_axis]);
            } else if (_angTargetRot == _angFace[prm_axis] - D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return -D180ANG;
            } else if (_angFace[prm_axis] - D180ANG < _angTargetRot && _angTargetRot < _angFace[prm_axis]) {
                return (D360ANG - _angFace[prm_axis]) + _angTargetRot;
            } else if (_angFace[prm_axis] == _angTargetRot) {
                //重なってる場合
                return -D360ANG;
            } else if (_angFace[prm_axis] < _angTargetRot && _angTargetRot <= D360ANG) {
                return (_angFace[prm_axis] + (D360ANG - _angTargetRot)) ;
            } else {
                //おかしい
                _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
                throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return (_angTargetRot - _angFace[prm_axis]);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            return D360ANG - _angFace[prm_axis] + _angTargetRot;
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(5)。_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angFace[prm_axis] && _angFace[prm_axis] < _angTargetRot) {
            return -1 * (_angFace[prm_axis] + D360ANG - _angTargetRot);
        } else if (_angTargetRot < _angFace[prm_axis] && _angFace[prm_axis] <= D360ANG) {
            return -1 * (_angFace[prm_axis] - _angTargetRot);
        } else if (_angFace[prm_axis] == _angTargetRot) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
            throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() 現在の正面方角アングル値か、ターゲットアングル値が範囲外です(6)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angFace["<<prm_axis<<"]=" << _angFace[prm_axis] << "/_angTargetRot=" << _angTargetRot);
    throwGgafCriticalException("GgafDxKurokoA::getFaceAngDistance() 何故かしら角の距離が求めれません。prm_wayは正しいですか？(2)。prm_way="<<prm_way<<" _pActor="<<_pActor->getName());
}

void GgafDxKurokoA::forceMvVeloRange(velo prm_velo) {
    forceMvVeloRange(-prm_velo, prm_velo);
}

void GgafDxKurokoA::forceMvVeloRange(velo prm_veloMv01, velo prm_veloMv02) {
    if (prm_veloMv01 < prm_veloMv02) {
        _veloTopMv = prm_veloMv02;
        _veloBottomMv = prm_veloMv01;
    } else {
        _veloTopMv = prm_veloMv01;
        _veloBottomMv = prm_veloMv02;
    }
    setMvVelo(_veloMv); //再設定して範囲内に補正
}

void GgafDxKurokoA::setMvVelo(velo prm_veloMv) {
    if (prm_veloMv > _veloTopMv) {
        _veloMv = _veloTopMv;
    } else if (prm_veloMv < _veloBottomMv) {
        _veloMv = _veloBottomMv;
    } else {
        _veloMv = prm_veloMv;
    }
}

void GgafDxKurokoA::addMvVelo(velo prm_veloMv_Offset) {
    setMvVelo(_veloMv + prm_veloMv_Offset);
}

void GgafDxKurokoA::setMvAcce(int prm_acceMove) {
    _accMv = prm_acceMove;
}

frame GgafDxKurokoA::setMvAcceToStop(coord prm_target_distance) {
    double acc = UTIL::getAcceToStop(prm_target_distance, _veloMv);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    return (frame)((2.0*prm_target_distance) / _veloMv); //使用フレーム数
}

frame GgafDxKurokoA::setFaceAngAcceToStop(axis prm_axis, angle prm_target_angle_distance) {
    double acc = UTIL::getAcceToStop(prm_target_angle_distance, _angveloFace[prm_axis]);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    return (frame)((2.0*prm_target_angle_distance) / _angveloFace[prm_axis]); //使用フレーム数
}

frame GgafDxKurokoA::setMvAcceByD(coord prm_target_distance, velo prm_target_velo) {
    double acc = UTIL::getAcceByD(prm_target_distance, _veloMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    return (frame)((1.0*prm_target_velo - _veloMv) / acc); //使用フレーム数
}
frame GgafDxKurokoA::setFaceAngAcceByD(axis prm_axis, angle prm_target_angle_distance, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByD(prm_target_angle_distance, _angveloFace[prm_axis], prm_target_angvelo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    return (frame)((1.0*prm_target_angvelo - _angveloFace[prm_axis]) / acc); //使用フレーム数
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

coord GgafDxKurokoA::setMvAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByT(prm_target_frames, _veloMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _accMv = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_veloMv + prm_target_velo) * prm_target_frames) / 2 ;
}
angle GgafDxKurokoA::setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo) {
    double acc = UTIL::getAcceByT(prm_target_frames, _angveloFace[prm_axis], prm_target_angvelo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    _angacceFace[prm_axis] = acc;
    //  D = (1/2) (Vo + Vt) Te
    return ((_angveloFace[prm_axis] + prm_target_angvelo) * prm_target_frames) / 2 ;
}
void GgafDxKurokoA::slideMvByDT(velo prm_end_velo, coord prm_target_distance,
                                int prm_target_frames, float prm_p1, float prm_p2,
                                bool prm_endacc_flg) {
    _slide_mv_flg = true;
    _slide_mv_p1 = (int)(prm_target_frames*prm_p1);
    _slide_mv_p2 = (int)(prm_target_frames*prm_p2);
    _slide_mv_end_velo = prm_end_velo;
    _slide_mv_target_distance = prm_target_distance;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = prm_target_frames;
    _slide_mv_frame_of_spent = 0;
    _slide_mv_progress = 0;

    //＜トップスピード(Vt) を計算＞
    //
    //    速度(v)
    //     ^
    //     |                          D:目標移動距離
    //     |                         V0:現時点の速度
    //     |                         Vt:トップスピード
    //     |                         Ve:最終速度
    //   Vt|....＿＿＿＿＿           Te:目標時間（フレーム数）
    //     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合
    //   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合
    //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
    //     |/   :         :    |
    //   V0|    :    D    :    |
    //     |    :         :    |
    //   --+----+---------+----+-----> 時間(t:フレーム)
    //   0 |  p1*Te     p2*Te  Te
    //
    // 移動距離Dは、左の台形＋中央の長方形＋右の台形 の面積である、
    // D = (1/2) (V0 + Vt) p1 Te + Vt (p2-p1)Te  +  (1/2) (Ve + Vt) (1-p2)Te
    // これをVtについて解く
    // Vt = ( 2D - p1 Te V0 + (p2 - 1) Te Ve ) / ( (p2 - p1 + 1) Te )
    _slide_mv_top_velo =
         ((2.0*prm_target_distance) - (prm_p1*prm_target_frames*_veloMv) + ((prm_p2-1.0)*prm_target_frames*prm_end_velo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}

void GgafDxKurokoA::slideMvByVD(velo prm_top_velo, velo prm_end_velo,
                                coord prm_target_distance, float prm_p1, float prm_p2,
                                bool prm_endacc_flg) {
    _slide_mv_flg = true;
    _slide_mv_endacc_flg = prm_endacc_flg;
    _slide_mv_top_velo = prm_top_velo;
    _slide_mv_end_velo = prm_end_velo;
    _slide_mv_target_distance = prm_target_distance;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = -1; //目標時間は使わない場合は負を設定しておく(条件分岐で使用)
    _slide_mv_frame_of_spent = 0;
    _slide_mv_p1 = (int)(prm_target_distance*prm_p1);
    _slide_mv_p2 = (int)(prm_target_distance*prm_p2);
    _slide_mv_progress = 0;
}


void GgafDxKurokoA::slideMvByVT(velo prm_top_velo, velo prm_end_velo,
                                int prm_target_frames, float prm_p1, float prm_p2,
                                bool prm_endacc_flg) {
    _slide_mv_flg = true;
    _slide_mv_endacc_flg = prm_endacc_flg;
    _slide_mv_top_velo = prm_top_velo;
    _slide_mv_end_velo = prm_end_velo;
    _slide_mv_target_distance = 0;
    _slide_mv_moved_distances = 0;
    _slide_mv_target_frames = prm_target_frames;
    _slide_mv_frame_of_spent = 0;
    _slide_mv_p1 = (int)(prm_target_frames*prm_p1);
    _slide_mv_p2 = (int)(prm_target_frames*prm_p1);
    _slide_mv_progress = 0;
}


//void GgafDxKurokoA::slideMv4(velo prm_end_velo, coord prm_target_distance, int prm_target_frames,
//                                                      bool prm_endacc_flg) {
//    _slide_mv_flg = true;
//    _slide_mv_p1 = (int)(prm_target_distance*1.0 / 4.0);
//    _slide_mv_p2 = (int)(prm_target_distance*3.0 / 4.0);
//    _slide_mv_end_velo = prm_end_velo;
//    _slide_mv_target_distance = prm_target_distance;
//    _slide_mv_moved_distances = 0;
//    _slide_mv_target_frames = -1; //目標時間は使わない場合は負を設定しておく(条件分岐で使用)
//    _slide_mv_frame_of_spent = 0;
//    _slide_mv_progress = 0;
//
//    //    速度
//    //     ^
//    //     |                       D:移動距離
//    //     |                      V0:現時点の速度
//    //     |                      Vt:距離1/4 ～ 3/4 の速度
//    //     |                      Ve:最終目標到達速度
//    //   Vt|....＿＿＿＿            Te:目標到達速度に達した時の時間（フレーム数）
//    //     |   /|      |＼
//    //   Ve|../.|......|..＼
//    //     | /  |      |   |
//    //     |/   |      |   |
//    //   V0| 1/4|  2/4 |1/4|
//    //     |  D |   D  | D |
//    //   --+----+------+---+-----> 時間(フレーム)
//    //   0 |   tp1    tp2  Te
//
//    // 距離は 「台形＋長方形＋台形」 の面積。ゆえに
//    // (1/4)D = (1/2) (V0 + Vt) tp1           …① 台形
//    // (2/4)D = Vt (tp2 - tp1)                …② 長方形
//    // (1/4)D = (1/2) (Ve + Vt) (Te - tp2)     …③ 台形
//
//
//    // (1/4)D = Vt tp1 -  (1/2) tp1 (Vt - V0)
//    // また、距離は 「全体の長方形 ‐ 三角形部分２つ」 の面積でもある。ゆえに
//    // D = Te Vt - (1/2) tp1 (Vt - V0) - (1/2) (Te - tp2) (Vt - Ve) …④
//
//    //①より
//    //tp1 = (D / 2 (V0 + Vt) )        …⑤
//    //③より
//    //(Te - tp2) = (D / 2 (Ve + Vt) )  …⑥
//    //⑤⑥を④へ代入
//    //D = Te Vt - D(Vt - V0) / 4 (V0 + Vt) - D(Vt - Ve) / 4 (Ve + Vt)
//    //これをVtについて解くと
//
//    //    Vt =
//    //    (sqrt((-9*V0^2+9*Ve*V0-9*Ve^2)*D^4-(4*Te*V0^3-6*Te*Ve*V0^2-6*Te*Ve^2*V0+4*Te*Ve^3)*D^3+(-4*Te^2*V0^4+8*Te^2*Ve*V0^3-12*Te^2*Ve^2*V0^2+8*Te^2*Ve^3*V0-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*V0^4+8*Te^4*Ve^3*V0^3-4*Te^4*Ve^4*V0^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*V0^3-12*Ve*V0^2-12*Ve^2*V0+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3)+(9*D^2+Te^2*(4*V0^2-4*Ve*V0+4*Ve^2))/(36*Te^2*(
//    //    sqrt((-9*V0^2+9*Ve*V0-9*Ve^2)*D^4-(4*Te*V0^3-6*Te*Ve*V0^2-6*Te*Ve^2*V0+4*Te*Ve^3)*D^3+(-4*Te^2*V0^4+8*Te^2*Ve*V0^3-12*Te^2*Ve^2*V0^2+8*Te^2*Ve^3*V0-4*Te^2*Ve^4)*D^2-4*Te^4*Ve^2*V0^4+8*Te^4*Ve^3*V0^3-4*Te^4*Ve^4*V0^2)/(4*3^(3/2)*Te^2)-
//    //    (Te^3*(8*V0^3-12*Ve*V0^2-12*Ve^2*V0+8*Ve^3)-27*D^3)/(216*Te^3))^(1/3))+(3*D-Te*(2*V0+2*Ve))/(6*Te)
//    //なんじゃこれ・・・
//
//
//
//
//
//    _slide_mv_top_velo = (8.0*prm_target_distance/prm_target_frames - _veloMv - prm_end_velo) / 6.0;
//}



bool GgafDxKurokoA::isSlidingMv() {
    return _slide_mv_flg;
}

void GgafDxKurokoA::stopSlidingMv() {
    _slide_mv_flg = false;
}

bool GgafDxKurokoA::isJustFinishSlidingMv() {
    if (_slide_mv_flg == false && _slide_mv_progress != -1) {
        return true;
    } else {
        return false;
    }
}

void GgafDxKurokoA::setRzMvAng(angle prm_ang) {
    if (prm_ang !=  _angRzMv) {
        _angRzMv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDxKurokoA::addRzMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRzBottomMv > prm_angDistance) {
        angOffset = _angveloRzBottomMv;
    } else if (prm_angDistance > _angveloRzTopMv) {
        angOffset = _angveloRzTopMv;
    }
    setRzMvAng(_angRzMv + angOffset);
}

void GgafDxKurokoA::setRzMvAngVelo(angvelo prm_angveloRzMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
}

void GgafDxKurokoA::setRzMvAngAcce(angacce prm_angacceRzMv) {
    _angacceRzMv = prm_angacceRzMv;
}

void GgafDxKurokoA::forceRzMvAngVeloRange(angvelo prm_angveloRzMv01,
                                          angvelo prm_angveloRzMv02) {
    if (prm_angveloRzMv01 < prm_angveloRzMv02) {
        _angveloRzTopMv = prm_angveloRzMv02;
        _angveloRzBottomMv = prm_angveloRzMv01;
    } else {
        _angveloRzTopMv = prm_angveloRzMv01;
        _angveloRzBottomMv = prm_angveloRzMv02;
    }
    setRzMvAngVelo(_angveloRzMv); //再設定して範囲内に補正
}

void GgafDxKurokoA::setStopTargetRzMvAng(angle prm_angTargetRzMv,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllowRyMv) {
    _mv_ang_rz_target_flg = true;
    _mv_ang_rz_target_stop_flg = true;
    _angTargetRzMv = UTIL::simplifyAng(prm_angTargetRzMv);
    _mv_ang_rz_target_allow_way = prm_way_allow;
    _mv_ang_rz_target_allow_velo = prm_angveloAllowRyMv;
}

angle GgafDxKurokoA::getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRzMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)), prm_way);
}

angle GgafDxKurokoA::getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way) {
    angle angTargetRzMv = UTIL::simplifyAng(prm_angTargetRzMv);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRzMv && _angRzMv < D180ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv) {
                //重なってる場合
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + D180ANG) {
                return angTargetRzMv - _angRzMv;
            } else if (angTargetRzMv == _angRzMv + D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return D180ANG;
            } else if (_angRzMv + D180ANG < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return -1 * (_angRzMv + (D360ANG - angTargetRzMv));
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRzMv && _angRzMv <= D360ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - D180ANG) {
                return D360ANG - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv - D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -D180ANG;
            } else if (_angRzMv - D180ANG < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return -1 * (_angRzMv - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //重なってる場合
                return 0;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return angTargetRzMv - _angRzMv;
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angRzMv && _angRzMv < D180ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv) {
                return D360ANG - _angRzMv + angTargetRzMv;
            } else if (angTargetRzMv == _angRzMv) {
                //重なってる場合
                return D360ANG;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv < _angRzMv + D180ANG) {
                return -1*(_angRzMv + (D360ANG-angTargetRzMv));
            } else if (angTargetRzMv == _angRzMv + D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return D180ANG;
            } else if (_angRzMv + D180ANG < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return angTargetRzMv - _angRzMv;
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRzMv && _angRzMv <= D360ANG) {
            if (0 <= angTargetRzMv && angTargetRzMv < _angRzMv - D180ANG) {
                return  -1*(_angRzMv - angTargetRzMv);
            } else if (angTargetRzMv == _angRzMv - D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -D180ANG;
            } else if (_angRzMv - D180ANG < angTargetRzMv && angTargetRzMv < _angRzMv) {
                return _angRzMv + (D360ANG - angTargetRzMv);
            } else if (_angRzMv == angTargetRzMv) {
                //重なってる場合
                return -D360ANG;
            } else if (_angRzMv < angTargetRzMv && angTargetRzMv <= D360ANG) {
                return angTargetRzMv + (D360ANG - _angRzMv);
            } else {
                //おかしい
                _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
                throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return (angTargetRzMv - _angRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= D360ANG) {
            return D360ANG - _angRzMv + angTargetRzMv;
        } else if (_angRzMv == angTargetRzMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(5)。_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRzMv && _angRzMv < angTargetRzMv) {
            return -1 * (_angRzMv + D360ANG - angTargetRzMv);
        } else if (angTargetRzMv < _angRzMv && _angRzMv <= D360ANG) {
            return -1 * (_angRzMv - angTargetRzMv);
        } else if (_angRzMv == angTargetRzMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
            throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(6)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRzMv=" << _angRzMv << "/angTargetRzMv=" << angTargetRzMv);
    throwGgafCriticalException("GgafDxKurokoA::getRzMvAngDistance() 何故かしら角の距離が求めれません(1)。_pActor="<<_pActor->getName());
}


//void GgafDxKurokoA::setRyMvAngTwd(coord prm_tx, coord prm_ty) {
//    setRyMvAng(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)));
//}

void GgafDxKurokoA::setRyMvAng(angle prm_ang) {
    if (prm_ang != _angRyMv) {
        _angRyMv = UTIL::simplifyAng(prm_ang);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::addRyMvAng(angle prm_angDistance) {
    angle angOffset = prm_angDistance;
    if (_angveloRyBottomMv > prm_angDistance) {
        angOffset = _angveloRyBottomMv;
    } else if (prm_angDistance > _angveloRyTopMv) {
        angOffset = _angveloRyTopMv;
    }
    setRyMvAng(_angRyMv + angOffset);
}

void GgafDxKurokoA::setRyMvAngVelo(angvelo prm_angveloRyMv) {
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDxKurokoA::setRyMvAngAcce(angacce prm_angacceRyMv) {
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDxKurokoA::forceRyMvAngVeloRange(angvelo prm_angveloRyMv01,
                                          angvelo prm_angveloRyMv02) {
    if (prm_angveloRyMv01 < prm_angveloRyMv02) {
        _angveloRyTopMv = prm_angveloRyMv02;
        _angveloRyBottomMv = prm_angveloRyMv01;
    } else {
        _angveloRyTopMv = prm_angveloRyMv01;
        _angveloRyBottomMv = prm_angveloRyMv02;
    }
    setRyMvAngVelo(_angveloRyMv); //再設定して範囲内に補正
}

void GgafDxKurokoA::forceRzRyMvAngVeloRange(angvelo prm_angveloRzRyMv01, angvelo prm_angveloRzRyMv02) {
    if (prm_angveloRzRyMv01 < prm_angveloRzRyMv02) {
        _angveloRzTopMv = prm_angveloRzRyMv02;
        _angveloRzBottomMv = prm_angveloRzRyMv01;
        _angveloRyTopMv = prm_angveloRzRyMv02;
        _angveloRyBottomMv = prm_angveloRzRyMv01;
    } else {
        _angveloRzTopMv = prm_angveloRzRyMv01;
        _angveloRzBottomMv = prm_angveloRzRyMv02;
        _angveloRyTopMv = prm_angveloRzRyMv01;
        _angveloRyBottomMv = prm_angveloRzRyMv02;
    }
    setRzMvAngVelo(_angveloRzMv); //再設定して範囲内に補正
    setRyMvAngVelo(_angveloRyMv); //再設定して範囲内に補正
}
void GgafDxKurokoA::setRzRyMvAngVelo(angvelo prm_angveloRzRyMv) {
    if (prm_angveloRzRyMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzRyMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzRyMv;
    }
    if (prm_angveloRzRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRzRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRzRyMv;
    }
}
void GgafDxKurokoA::setRzRyMvAngAcce(angacce prm_angacceRzRyMv) {
    _angacceRzMv = prm_angacceRzRyMv;
    _angacceRyMv = prm_angacceRzRyMv;
}
void GgafDxKurokoA::setRzRyMvAngAcce(angacce prm_angacceRzMv, angacce prm_angacceRyMv) {
    _angacceRzMv = prm_angacceRzMv;
    _angacceRyMv = prm_angacceRyMv;
}

void GgafDxKurokoA::setRzRyMvAngVelo(angvelo prm_angveloRzMv, angvelo prm_angveloRyMv) {
    if (prm_angveloRzMv > _angveloRzTopMv) {
        _angveloRzMv = _angveloRzTopMv;
    } else if (prm_angveloRzMv < _angveloRzBottomMv) {
        _angveloRzMv = _angveloRzBottomMv;
    } else {
        _angveloRzMv = prm_angveloRzMv;
    }
    if (prm_angveloRyMv > _angveloRyTopMv) {
        _angveloRyMv = _angveloRyTopMv;
    } else if (prm_angveloRyMv < _angveloRyBottomMv) {
        _angveloRyMv = _angveloRyBottomMv;
    } else {
        _angveloRyMv = prm_angveloRyMv;
    }
}

void GgafDxKurokoA::setStopTargetRyMvAng(angle prm_angTargetRyMv,
                                         int prm_way_allow,
                                         angvelo prm_angveloAllowRyMv) {
    _mv_ang_ry_target_flg = true;
    _mv_ang_ry_target_stop_flg = true;
    _angTargetRyMv = UTIL::simplifyAng(prm_angTargetRyMv);
    _mv_ang_ry_target_allow_way = prm_way_allow;
    _mv_ang_ry_target_allow_velo = prm_angveloAllowRyMv;
}

angle GgafDxKurokoA::getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way) {
    return getRyMvAngDistance(UTIL::getAngle2D(prm_tx - (_pActor->_x), prm_ty - (_pActor->_y)),
                                        prm_way);
}

angle GgafDxKurokoA::getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way) {
    angle angTargetRyMv;
    angTargetRyMv = UTIL::simplifyAng(prm_angTargetRyMv);
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        if (0 <= _angRyMv && _angRyMv < D180ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv) {
                //重なってる場合
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + D180ANG) {
                return angTargetRyMv - _angRyMv;
            } else if (angTargetRyMv == _angRyMv + D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return D180ANG;
            } else if (_angRyMv + D180ANG < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return -1 * (_angRyMv + (D360ANG - angTargetRyMv));
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(1)。_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRyMv && _angRyMv <= D360ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - D180ANG) {
                return D360ANG - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv - D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので負の値とする。
                return -D180ANG;
            } else if (_angRyMv - D180ANG < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return -1 * (_angRyMv - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //重なってる場合
                return 0;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return angTargetRyMv - _angRyMv;
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(2)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        if (0 <= _angRyMv && _angRyMv < D180ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv) {
                return D360ANG - _angRyMv + angTargetRyMv;
            } else if (angTargetRyMv == _angRyMv) {
                //重なってる場合
                return D360ANG;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv < _angRyMv + D180ANG) {
                return -1*(_angRyMv + (D360ANG-angTargetRyMv));
            } else if (angTargetRyMv == _angRyMv + D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return D180ANG;
            } else if (_angRyMv + D180ANG < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return angTargetRyMv - _angRyMv;
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(3)。_pActor="<<_pActor->getName());
            }
        } else if (D180ANG <= _angRyMv && _angRyMv <= D360ANG) {
            if (0 <= angTargetRyMv && angTargetRyMv < _angRyMv - D180ANG) {
                return  -1*(_angRyMv - angTargetRyMv);
            } else if (angTargetRyMv == _angRyMv - D180ANG) {
                //正反対を向いている（＝距離は等しい）
                //仕方ないので正の値とする。
                return -D180ANG;
            } else if (_angRyMv - D180ANG < angTargetRyMv && angTargetRyMv < _angRyMv) {
                return _angRyMv + (D360ANG - angTargetRyMv);
            } else if (_angRyMv == angTargetRyMv) {
                //重なってる場合
                return -D360ANG;
            } else if (_angRyMv < angTargetRyMv && angTargetRyMv <= D360ANG) {
                return angTargetRyMv + (D360ANG - _angRyMv);
            } else {
                //おかしい
                _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
                throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() 移動方角（Z軸回転）アングル値か、ターゲットアングル値が範囲外です(4)。_pActor="<<_pActor->getName());
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return (angTargetRyMv - _angRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= D360ANG) {
            return D360ANG - _angRyMv + angTargetRyMv;
        } else if (_angRyMv == angTargetRyMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(5)。_pActor="<<_pActor->getName());
        }
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        if (0 <= _angRyMv && _angRyMv < angTargetRyMv) {
            return -1 * (_angRyMv + D360ANG - angTargetRyMv);
        } else if (angTargetRyMv < _angRyMv && _angRyMv <= D360ANG) {
            return -1 * (_angRyMv - angTargetRyMv);
        } else if (_angRyMv == angTargetRyMv) {
            //重なってる場合
            return 0;
        } else {
            //おかしい
            _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
            throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() 移動方角（Y軸回転）アングル値か、ターゲットアングル値が範囲外です(6)。_pActor="<<_pActor->getName());
        }
    }
    _TRACE_("_angRyMv=" << _angRyMv << "/angTargetRyMv=" << angTargetRyMv);
    throwGgafCriticalException("GgafDxKurokoA::getRyMvAngDistance() 何故かしら角の距離が求めれません(1)。_pActor="<<_pActor->getName());
}

void GgafDxKurokoA::getRzRyMvAngDistance(int prm_way,
                                         angle prm_target_angRz, angle prm_target_angRy,
                                         angle& out_d_angRz, angle& out_d_angRy) {
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        //目標に到達するためには、回り方が常に２パターンある。
        //それぞれ球面上の２点の距離を簡易近似値（速度優先のため）で比較し、近いと思われるほうを採用する。
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOSE_TO); //Rzの差
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOSE_TO);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        angle d1_angRz = getRzMvAngDistance(prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getRyMvAngDistance(prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getRzMvAngDistance(prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getRyMvAngDistance(prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        out_d_angRz = getRzMvAngDistance(prm_target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getRyMvAngDistance(prm_target_angRy, TURN_COUNTERCLOCKWISE);
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        out_d_angRz = getRzMvAngDistance(prm_target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getRyMvAngDistance(prm_target_angRy, TURN_CLOCKWISE);
    } else {
        //おかしい
        throwGgafCriticalException("GgafDxKurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDxKurokoA::getRzRyFaceAngDistance(int prm_way,
                                           angle prm_target_angRz, angle prm_target_angRy,
                                           angle& out_d_angRz, angle& out_d_angRy) {
    if (prm_way == TURN_CLOSE_TO) { //近いほう回転
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOSE_TO);
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOSE_TO) * ((UTIL::COS[UTIL::simplifyAng(prm_target_angRz*2)/SANG_RATE]/2.0) + 0.5);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
        if (d1 <= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }

    } else if (prm_way == TURN_ANTICLOSE_TO) { //遠い方の回転
        angle d1_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d1_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d1 = ABS(d1_angRz) > ABS(d1_angRy) ? ABS(d1_angRz) : ABS(d1_angRy);
        UTIL::anotherRzRy(prm_target_angRz, prm_target_angRy);
        angle d2_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_ANTICLOSE_TO);
        angle d2_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_ANTICLOSE_TO);
        angle d2 = ABS(d2_angRz) > ABS(d2_angRy) ? ABS(d2_angRz) : ABS(d2_angRy);
        if (d1 >= d2) {
            out_d_angRz = d1_angRz;
            out_d_angRy = d1_angRy;
        } else {
            out_d_angRz = d2_angRz;
            out_d_angRy = d2_angRy;
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) { //反時計回りの場合
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_COUNTERCLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_COUNTERCLOCKWISE);
    } else if (prm_way == TURN_CLOCKWISE) { //時計回りの場合
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_target_angRz, TURN_CLOCKWISE);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_target_angRy, TURN_CLOCKWISE);
    } else {
        //おかしい
        throwGgafCriticalException("GgafDxKurokoA::getRzRyMvAngDistance() prm_way="<<prm_way<<" は想定外です。_pActor="<<_pActor->getName());
    }
}

void GgafDxKurokoA::setRzRyMvAng(angle prm_angRz, angle prm_angRy) {
    if (prm_angRz != _angRzMv || prm_angRy !=_angRyMv ) {
        _angRzMv = UTIL::simplifyAng(prm_angRz);
        _angRyMv = UTIL::simplifyAng(prm_angRy);
        UTIL::convRzRyToVector(_angRzMv, _angRyMv, _vX, _vY, _vZ);
    }
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::setRzRyMvAng_by_RyRz(angle prm_angRyRz_Ry, angle prm_angRyRz_Rz) {
    angle RyRz_Ry = UTIL::simplifyAng(prm_angRyRz_Ry);
    angle RyRz_Rz = UTIL::simplifyAng(prm_angRyRz_Rz);
    float out_vY, out_vZ;
    UTIL::convRzRyToVector(RyRz_Ry, D360ANG-RyRz_Rz, _vX, out_vY, out_vZ);
    _vY = -1.0f*out_vZ;
    _vZ = out_vY;
    UTIL::convVectorToRzRy(_vX, _vZ, _vY, _angRzMv, _angRyMv);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}


void GgafDxKurokoA::setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    UTIL::convVectorToRzRy(prm_tx - _pActor->_x,
                           prm_ty - _pActor->_y,
                           prm_tz - _pActor->_z,
                           _vX, _vY, _vZ,
                           _angRzMv, _angRyMv );
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
    if (_relate_RyFaceAng_with_RyMvAng_flg) {
        setFaceAng(AXIS_Y, _angRyMv);
    }
}

void GgafDxKurokoA::reverseMvAng() {
    _vX = -_vX;
    _vY = -_vY;
    _vZ = -_vZ;
    _angRzMv = UTIL::simplifyAng(_angRzMv-D180ANG);
    if (_relate_RzFaceAng_with_RzMvAng_flg) {
        setFaceAng(AXIS_Z, _angRzMv);
    }
}

void GgafDxKurokoA::setStopTargetMvAngTwd(GgafDxGeometricActor* prm_pActor_Target) {
    setStopTargetMvAngTwd(
        prm_pActor_Target->_x,
        prm_pActor_Target->_y,
        prm_pActor_Target->_z
    );
}

void GgafDxKurokoA::setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    angle angRz_Target;
    angle angRy_Target;
    float dummy1, dummy2, dummy3;

    UTIL::convVectorToRzRy(
                   prm_tx - _pActor->_x,
                   prm_ty - _pActor->_y,
                   prm_tz - _pActor->_z,
                   dummy1,
                   dummy2,
                   dummy3,
                   angRz_Target,
                   angRy_Target
                 );
    setStopTargetRzMvAng(angRz_Target);
    setStopTargetRyMvAng(angRy_Target);
}

void GgafDxKurokoA::turnRzRyFaceAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyFaceAngDistance(prm_way,
                               prm_angRz_Target, prm_angRy_Target,
                               out_d_angRz, out_d_angRy);
    } else {
        out_d_angRz = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way);
        out_d_angRy = getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way);
    }
    double drz = ABS(out_d_angRz);
    double dry = ABS(out_d_angRy);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_angRz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angVelo);
            setFaceAngAcce(AXIS_Z, prm_angAcce);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angVelo);
            setFaceAngAcce(AXIS_Z, -prm_angAcce);
        }
        if (out_d_angRy > 0) {
            setFaceAngVelo(AXIS_Y, prm_angVelo*drr);
            setFaceAngAcce(AXIS_Y, prm_angAcce*drr);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angVelo*drr);
            setFaceAngAcce(AXIS_Y, -prm_angAcce*drr);
        }
    } else {
        double drr = drz / dry ;
        if (out_d_angRz > 0) {
            setFaceAngVelo(AXIS_Z, prm_angVelo*drr);
            setFaceAngAcce(AXIS_Z, prm_angAcce*drr);
        } else {
            setFaceAngVelo(AXIS_Z, -prm_angVelo*drr);
            setFaceAngAcce(AXIS_Z, -prm_angAcce*drr);
        }
        if (out_d_angRy > 0) {
            setFaceAngVelo(AXIS_Y, prm_angVelo);
            setFaceAngAcce(AXIS_Y, prm_angAcce);
        } else {
            setFaceAngVelo(AXIS_Y, -prm_angVelo);
            setFaceAngAcce(AXIS_Y, -prm_angAcce);
        }
    }

    setStopTargetFaceAng(AXIS_Z, prm_angRz_Target);
    setStopTargetFaceAng(AXIS_Y, prm_angRy_Target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKurokoA::turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                   angvelo prm_angVelo, angacce prm_angAcce,
                                   int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    UTIL::convVectorToRzRy(prm_tx - _pActor->_x,
                           prm_ty - _pActor->_y,
                           prm_tz - _pActor->_z,
                           out_angRz_Target,
                           out_angRy_Target);

    turnRzRyFaceAngTo(out_angRz_Target, out_angRy_Target,
                      prm_angVelo, prm_angAcce,
                      prm_way, prm_optimize_ang);
}

void GgafDxKurokoA::turnRzFaceAngTo(angle prm_angRz_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Z, prm_angVelo);
        setFaceAngAcce(AXIS_Z, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Z, -prm_angVelo);
        setFaceAngAcce(AXIS_Z, -prm_angAcce);
    }
    setStopTargetFaceAng(AXIS_Z, prm_angRz_Target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKurokoA::turnRyFaceAngTo(angle prm_angRy_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_Y, prm_angRy_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_Y, prm_angVelo);
        setFaceAngAcce(AXIS_Y, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_Y, -prm_angVelo);
        setFaceAngAcce(AXIS_Y, -prm_angAcce);
    }
    setStopTargetFaceAng(AXIS_Y, prm_angRy_Target);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
}

void GgafDxKurokoA::turnRxSpinAngTo(angle prm_angRx_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way) {
    if (getFaceAngDistance(AXIS_X, prm_angRx_Target, prm_way) > 0) {
        setFaceAngVelo(AXIS_X, prm_angVelo);
        setFaceAngAcce(AXIS_X, prm_angAcce);
    } else {
        setFaceAngVelo(AXIS_X, -prm_angVelo);
        setFaceAngAcce(AXIS_X, -prm_angAcce);
    }
    setStopTargetFaceAng(AXIS_X, prm_angRx_Target);
}

void GgafDxKurokoA::turnRzRyMvAngTo(angle prm_angRz_Target, angle prm_angRy_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang) {
    angle out_d_angRz;
    angle out_d_angRy;
    if (prm_optimize_ang) {
        getRzRyMvAngDistance(prm_way,
                             prm_angRz_Target, prm_angRy_Target,
                             out_d_angRz, out_d_angRy);
    } else {
        out_d_angRz = getRzMvAngDistance(prm_angRz_Target, prm_way);
        out_d_angRy = getRyMvAngDistance(prm_angRy_Target, prm_way);
    }

    //Rz, Ry が、目標アングルへ同時に到達するように角速度を調整
    double drz = ABS(out_d_angRz);
    double dry = ABS(out_d_angRy);
    if (drz > dry) {
        double drr = dry / drz ;
        if (out_d_angRz > 0) {
            setRzMvAngVelo(prm_angVelo);
            setRzMvAngAcce(prm_angAcce);
        } else {
            setRzMvAngVelo(-prm_angVelo);
            setRzMvAngAcce(-prm_angAcce);
        }
        if (out_d_angRy > 0) {
            setRyMvAngVelo(prm_angVelo*drr);
            setRyMvAngAcce(prm_angAcce*drr);
        } else {
            setRyMvAngVelo(-prm_angVelo*drr);
            setRyMvAngAcce(-prm_angAcce*drr);
        }
    } else {
        double drr = drz / dry;
        if (out_d_angRz > 0) {
            setRzMvAngVelo(prm_angVelo*drr);
            setRzMvAngAcce(prm_angAcce*drr);
        } else {
            setRzMvAngVelo(-prm_angVelo*drr);
            setRzMvAngAcce(-prm_angAcce*drr);
        }
        if (out_d_angRy > 0) {
            setRyMvAngVelo(prm_angVelo);
            setRyMvAngAcce(prm_angAcce);
        } else {
            setRyMvAngVelo(-prm_angVelo);
            setRyMvAngAcce(-prm_angAcce);
        }
    }

    setStopTargetRzMvAng(prm_angRz_Target);
    setStopTargetRyMvAng(prm_angRy_Target);

}


void GgafDxKurokoA::turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                 angvelo prm_angVelo, angacce prm_angAcce,
                                 int prm_way, bool prm_optimize_ang) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    UTIL::convVectorToRzRy(prm_tx - _pActor->_x,
                           prm_ty - _pActor->_y,
                           prm_tz - _pActor->_z,
                           out_angRz_Target,
                           out_angRy_Target);
    turnRzRyMvAngTo(out_angRz_Target, out_angRy_Target,
                    prm_angVelo, prm_angAcce,
                    prm_way, prm_optimize_ang);
}


void GgafDxKurokoA::turnRzMvAngTo(angle prm_angRz_Target,
                                  angvelo prm_angVelo, angacce prm_angAcce,
                                  int prm_way) {
    if (getRzMvAngDistance(prm_angRz_Target, prm_way) > 0) {
        setRzMvAngVelo(prm_angVelo);
        setRzMvAngAcce(prm_angAcce);
    } else {
        setRzMvAngVelo(-prm_angVelo);
        setRzMvAngAcce(-prm_angAcce);
    }
    setStopTargetRzMvAng(prm_angRz_Target);

}

void GgafDxKurokoA::turnRyMvAngTo(angle prm_angRy_Target,
                                  angvelo prm_angVelo, angacce prm_angAcce,
                                  int prm_way) {
    if (getRyMvAngDistance(prm_angRy_Target, prm_way) > 0) {
        setRyMvAngVelo(prm_angVelo);
        setRyMvAngAcce(prm_angAcce);
    } else {
        setRyMvAngVelo(-prm_angVelo);
        setRyMvAngAcce(-prm_angAcce);
    }
    setStopTargetRyMvAng(prm_angRy_Target);
}


void GgafDxKurokoA::turnSmoothlyRzFaceAngByDtTo(
        angle prm_angRz_Target, int prm_way,
        angvelo prm_end_angvelo,
        int prm_target_frames, float prm_p1, float prm_p2,
        bool prm_endacc_flg) {

    angle dang = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way);
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;

    _smooth_turn_rz_faceang_flg = true;
    _smooth_turn_rz_faceang_p1 = (int)(prm_target_frames*prm_p1);
    _smooth_turn_rz_faceang_p2 = (int)(prm_target_frames*prm_p2);
    _smooth_turn_rz_faceang_end_angvelo = prm_end_angvelo;
    _smooth_turn_rz_faceang_target_distanceangle = dang;
    _smooth_turn_rz_faceang_target_frames = prm_target_frames;
    _smooth_turn_rz_faceang_frame_of_spent = 0;
    _smooth_turn_rz_faceang_progress = 0;

    //＜トップスピード(Vt) を計算＞
    //
    //    速度(v)
    //     ^
    //     |                          D:目標移動距離
    //     |                         V0:現時点の速度
    //     |                         Vt:トップスピード
    //     |                         Ve:最終速度
    //   Vt|....＿＿＿＿＿           Te:目標時間（フレーム数）
    //     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合
    //   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合
    //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
    //     |/   :         :    |
    //   V0|    :    D    :    |
    //     |    :         :    |
    //   --+----+---------+----+-----> 時間(t:フレーム)
    //   0 |  p1*Te     p2*Te  Te
    //
    // 移動距離Dは、左の台形＋中央の長方形＋右の台形 の面積である、
    // D = (1/2) (V0 + Vt) p1 Te + Vt (p2-p1)Te  +  (1/2) (Ve + Vt) (1-p2)Te
    // これをVtについて解く
    // Vt = ( 2D - p1 Te V0 + (p2 - 1) Te Ve ) / ( (p2 - p1 + 1) Te )
    _smooth_turn_rz_faceang_top_angvelo =
         ((2.0*dang) - (prm_p1*prm_target_frames*_angveloFace[AXIS_Z]) + ((prm_p2-1.0)*prm_target_frames*prm_end_angvelo))
         / ((prm_p2-prm_p1+1.0)*prm_target_frames);

}


void GgafDxKurokoA::turnSmoothlyRzFaceAngByVdTo(
        angle prm_angRz_Target, int prm_way,
        angvelo prm_top_angvelo, angvelo prm_end_angvelo,
        float prm_p1, float prm_p2,
        bool prm_endacc_flg ) {

    double target_angle_distance = getFaceAngDistance(AXIS_Z, prm_angRz_Target, prm_way); //θ
    _taget_face_ang_alltime_pActor = nullptr;
    _taget_face_ang_alltime_flg = false;
    int s_target_angle_distance = SGN(target_angle_distance);                     //θの正負
    int s_w0 = SGN(_angveloFace[AXIS_Z]); //ω0の正負

    if (s_w0 == 0 || s_target_angle_distance == s_w0) {  //正負が一致
        //【パターン１】
        //
        //        角速度(ω)                       ω0:現時点の速度      (_angveloFace[])
        //         ^                               ωt:トップスピード    (prm_top_angvelo)
        //         |                               ωe:最終速度          (prm_end_angvelo)
        //         |                                θ:目標回転距離角θ  (θ1+θ2+θ3)                     ・・・ 計算して求める
        //         |                                p1:トップスピードに達する角距離となるような、角距離(θ)に対する割合
        //         |       θ=θ1+θ2+θ3               つまり     θ1 = θ*p1 となるような p1 (0.0～1.0)
        //      ωt|....___________                 p2:減速を開始距離となるような、距離(D)に対する割合
        //         |   /|         |＼                   つまり θ1+θ2 = θ*p2 となるような p2 (0.0～1.0)
        //      ωe|../.|.........|..＼             T1: θ1     = θ*p1 に費やされる必要時間フレーム数     ・・・ 計算して求める
        //         | /  |         |    |            T2: θ1+θ2 = θ*p2 に費やされる必要時間フレーム数     ・・・ 計算して求める
        //         |/   |         |    |            Te:費やされる必要時間フレーム数                        ・・・ 計算して求める
        //      ω0|θ1 |   θ2   |θ3 |
        //         |    |         |    |
        //       --+----+---------+----+-----> 時間(t:フレーム)
        //       0 |    T1        T2   Te
        //

        double W0 = _angveloFace[AXIS_Z];
        double Wt = ABS(prm_top_angvelo) * s_target_angle_distance;
        double We = ABS(prm_end_angvelo) * s_target_angle_distance;
        _smooth_turn_rz_faceang_flg = true;
        _smooth_turn_rz_faceang_endacc_flg = prm_endacc_flg;
        _smooth_turn_rz_faceang_top_angvelo = Wt;
        _smooth_turn_rz_faceang_end_angvelo = We;
        _smooth_turn_rz_faceang_target_distanceangle = ABS(target_angle_distance);
        _smooth_turn_rz_faceang_turned_angles = 0;
        _smooth_turn_rz_faceang_targetangle_sgn = s_target_angle_distance;
        _smooth_turn_rz_faceang_target_frames = -1; //時間未使用
        _smooth_turn_rz_faceang_frame_of_spent = 0;
        _smooth_turn_rz_faceang_p0 = 0; //未使用
        _smooth_turn_rz_faceang_p1 = ABS(target_angle_distance) * prm_p1;
        _smooth_turn_rz_faceang_p2 = ABS(target_angle_distance) * prm_p2;
        _smooth_turn_rz_faceang_progress = 2; //回復フェーズを飛ばす
    } else {

        //                                                      ω0:現時点の速度      (_angveloFace[])
        //        速度(v)                                       ωt:トップスピード    (prm_top_angvelo)
        //        ^                                              ωe:最終速度          (prm_end_angvelo)
        //        |                                               θ:スタート時点の角度からの目標回転距離角                     ・・・ 計算して求める
        //        |                                              θp:角速度０になってからの目標回転距離角(θp1 + θp2 + θp3)   ・・・ 計算して求める
        //        |                                                s:角速度０になるまでの逆回転距離                             ・・・ 計算して求める
        //        |                                               p1:トップスピードに達する角距離となるような、角距離(θ)に対する割合
        //        |           θ  = (θp1-s) + θp2 + θp3                 つまり θp1 = θp*p1 となるような p1 (0.0～1.0)    引数
        //        |           θp = θp1 + θp2 + θp3            p2:減速を開始距離となるような、距離(D)に対する割合
        //     ωt|...............___________                          つまり θp1+θp2 = θp*p2 となるような p2 (0.0～1.0)  引数
        //        |            A /|         |＼B                  T0: 角速度０になるまでに費やされる必要時間フレーム数  ・・・ 計算して求める
        //        |             / |         |  ＼                 T1: θp1      = θp*p1 に費やされる必要時間フレーム数  ・・・ 計算して求める
        //        |            /  |         |    ＼               T2: θp1+θp2 = θp*p2 に費やされる必要時間フレーム数  ・・・ 計算して求める
        //        |           /   |         |      ＼             Te:費やされる必要時間フレーム数                        ・・・ 計算して求める
        //        |          /θp1|   θp2  | θp3   ＼
        //        |         /:    |         |          ＼
        //     ωe|......../.:....|.........|............＼  C
        //        |       /  :    |         |             |
        //        |      / s :    |         |             |
        //   -----+-----+----+----+---------+-------------+----------> 時間(t:フレーム)
        //      0 | s／ Ts       T1        T2            Te
        //        |／
        //     ω0| ^    <-s-><-----------θ-------------->
        //        | |
        //        | |    <--------------θp--------------->
        //        | |
        //        | |    <--θp1--><--θp2--><----θp3---->
        //        | |
        //        | 初期回復角加速度(a0)固定
        //        |
        //
        //
        //        時間 t が 0 ～ Ts 時の角速度を W とすると
        //        直線 W = a0*t - W0 より    (※初期回復角加速度(a0)は定数)
        //        t = Ts の時  W = 0  であるので
        //        0 = a0*Ts - W0
        //        Ts = W0/a0  ・・・(1)
        //        また
        //        s = (1/2) * Ts * -W0       (∵三角形の面積)
        //        これに(1)を代入
        //        s = (1/2) * (W0/a0) * -W0
        //        s = -(W0^2)/(2*a0)  ・・・(2)
        //        また
        //
        //        D + s =  Dp = (Dp1 + Dp2 + Dp3) ・・・(3)
        //        より
        //        Dp = D + (-W0^2/(2*a0))  ・・・(4)
        double W0 = _angveloFace[AXIS_Z];
        double Wt = ABS(prm_top_angvelo) * s_target_angle_distance;
        double We = ABS(prm_end_angvelo) * s_target_angle_distance;
        double a0 = 500 * -s_w0; //初期角速度の正負逆
        double s = -(W0*W0)/(2*a0);
        double Dp = s + target_angle_distance;

        _TRACE_("a0="<<a0);
        _TRACE_("s="<<s);
        _TRACE_("Dp="<<Dp);
        _smooth_turn_rz_faceang_flg = true;
        _smooth_turn_rz_faceang_endacc_flg = prm_endacc_flg;
        _smooth_turn_rz_faceang_top_angvelo = Wt;
        _smooth_turn_rz_faceang_end_angvelo = We;
        _smooth_turn_rz_faceang_target_distanceangle = ABS(Dp) + ABS(s);
        _smooth_turn_rz_faceang_turned_angles = 0;
        _smooth_turn_rz_faceang_angacce_a0 = a0;
        _smooth_turn_rz_faceang_targetangle_sgn = s_target_angle_distance;
        _smooth_turn_rz_faceang_target_frames = -1; //時間未使用
        _smooth_turn_rz_faceang_frame_of_spent = 0;
        _smooth_turn_rz_faceang_p0 = ABS(s);
        _smooth_turn_rz_faceang_p1 = ABS(s)  +  (ABS(Dp) * prm_p1);
        _smooth_turn_rz_faceang_p2 = ABS(s)  +  (ABS(Dp) * prm_p2);
        _smooth_turn_rz_faceang_progress = 0; //回復フェーズから

    }
    _TRACE_("GgafDxKurokoA::turnSmoothlyRzFaceAngByVdTo");
    _TRACE_("_smooth_turn_rz_faceang_flg="<<_smooth_turn_rz_faceang_flg);
    _TRACE_("_smooth_turn_rz_faceang_endacc_flg="<<_smooth_turn_rz_faceang_endacc_flg);
    _TRACE_("_smooth_turn_rz_faceang_top_angvelo="<<_smooth_turn_rz_faceang_top_angvelo);
    _TRACE_("_smooth_turn_rz_faceang_end_angvelo="<<_smooth_turn_rz_faceang_end_angvelo);
    _TRACE_("_smooth_turn_rz_faceang_target_distanceangle="<<_smooth_turn_rz_faceang_target_distanceangle);
    _TRACE_("_smooth_turn_rz_faceang_turned_angles="<<_smooth_turn_rz_faceang_turned_angles);
    _TRACE_("_smooth_turn_rz_faceang_angacce_a0="<<_smooth_turn_rz_faceang_angacce_a0);
    _TRACE_("_smooth_turn_rz_faceang_targetangle_sgn="<<_smooth_turn_rz_faceang_targetangle_sgn);
    _TRACE_("_smooth_turn_rz_faceang_target_frames="<<_smooth_turn_rz_faceang_target_frames);
    _TRACE_("_smooth_turn_rz_faceang_frame_of_spent="<<_smooth_turn_rz_faceang_frame_of_spent);
    _TRACE_("_smooth_turn_rz_faceang_p0="<<_smooth_turn_rz_faceang_p0);
    _TRACE_("_smooth_turn_rz_faceang_p1="<<_smooth_turn_rz_faceang_p1);
    _TRACE_("_smooth_turn_rz_faceang_p2="<<_smooth_turn_rz_faceang_p2);
    _TRACE_("_smooth_turn_rz_faceang_progress="<<_smooth_turn_rz_faceang_progress);



//    } else {  //正負がねじれ
//        //---------------------------------------------------------------------------------------------------------------------------------------------------------
//        //【パターン２】
//        //                                                          ω0:現時点の速度      (_angveloFace[])
//        //             速度(v)                                      ωt:トップスピード    (prm_top_angvelo)
//        //            ^                                             ωe:最終速度          (prm_end_angvelo)
//        //            |                                              θ:目標回転距離角θ  (θ1+θ2+θ3)                     ・・・ 計算して求める
//        //            |                                              p1:トップスピードに達する角距離となるような、角距離(θ)に対する割合
//        //            |                                                  つまり     θ1 = θ*p1 となるような p1 (0.0～1.0)
//        //            |        θ= (-s + s) + θ1 + θ2 + θ3        p2:減速を開始距離となるような、距離(D)に対する割合
//        //         ωt|.............___________                          つまり θ1+θ2 = θ*p2 となるような p2 (0.0～1.0)
//        //            |            /|         |＼                    Ts: 丁度スタート時点に戻ってくる時点に費やされる必要時間フレーム数     ・・・ 計算して求める
//        //            |           / |         |  ＼                  T1: θ1     = θ*p1 に費やされる必要時間フレーム数     ・・・ 計算して求める
//        //            |          /  |         |    ＼                T2: θ1+θ2 = θ*p2 に費やされる必要時間フレーム数     ・・・ 計算して求める
//        //        -ω0|........./θ1|   θ2   | θ3  ＼              Te:費やされる必要時間フレーム数                        ・・・ 計算して求める
//        //            |        /|   |         |        ＼
//        //         ωe|......./.|...|.........|..........＼
//        //            |      /  |   |         |           |
//        //            |     / s |   |         |           |
//        //       -----+----/----+---+---------+-----------+----------> 時間(t:フレーム)
//        //          0 |-s /     Ts  T1        T2          Te
//        //            |  /
//        //            | /
//        //            |/
//        //         ω0|
//        //            |
//        //
//        //    時間 t が 0 ～ T1 時の角速度を ω、角加速度を a とする。
//        //    直線 ω = a*t + ω0 より
//        //    t = Ts  の時  ω = -ω0  であるので
//        //    -ω0 = a*Ts + ω0
//        //    これを Ts について解くと
//        //    Ts = -(2*ω0)/a    ・・・①
//        //
//        //    直線 ω = a*t + ω0 より
//        //    t = T1  の時  ω = ωt  であるので
//        //    ωt = a*T1 + ω0
//        //    これを a について解くと
//        //    a = (ωt-ω0)/T1     ・・・②
//        //
//        //    ②を①へ代入
//        //    Ts = -(2*ω0) /( (ωt-ω0)/T1 )
//        //    Ts = (2*ω0*T1) / (ω0-ωt)      ・・・③
//        //
//        //    これより T1、T2、Te  を求める
//        //    θ = θ1 + θ2 + θ3
//        //    台形＋長方形＋台形の面積より
//        //    θ1 = (1/2) * (-ω0 + ωt) * (T1-Ts)       ・・・ ④
//        //    θ2 = (T2-T1) * ωt                       ・・・ ⑤
//        //    θ3 = (1/2) * ( ωe + ωt) * (Te-T2)       ・・・ ⑥
//        //
//        //    ③を④へ代入
//        //    θ1 = (1/2) * (-ω0 + ωt) * (T1-(  (2*ω0*T1) / (ω0-ωt)  ))
//        //    θ1 = ((ωt+ω0)*T1)/2      ・・・ ⑦
//        //
//        //    あとはパターン１同様に
//        //    ⑦より
//        //    T1= (2*θ1)/(ωt+ω0)       ・・・ ⑧
//        //
//        //    ⑧を⑤へ代入
//        //    θ2 = (T2-(  (2*θ1)/(ωt+ω0)  )) * ωt
//        //    T2 = (ωt*θ2+ω0*θ2+2*ωt*θ1) / (ωt*(ωt+ω0))    ・・・ ⑨
//        //
//        //    ⑨を⑥へ代入
//        //    θ3 = (1/2) * ( ωe + ωt) * (Te-(  (ωt*θ2+ω0*θ2+2*ωt*θ1) / (ωt*(ωt+ω0))  ))
//        //    Te = ((2*ωt^2+2*ω0*ωt)*θ3+(ωt^2+(ωe+ω0)*ωt+ω0*ωe)*θ2+(2*ωt^2+2*ωe*ωt)*θ1) / (ωt*(ωt+ω0)*(ωt+ωe))   ・・・⑩
//        //
//        //
//        //    sを求める。三角形の面積より
//        //    s = (1/2) * ((1/2) * Ts * -ω0)   ・・・⑪
//        //
//        //    ところで
//        //
//        //    Ts = (2*ω0*T1) / (ω0-ωt)       ・・・③
//        //    T1 = (2*θ1)/(ωt+ω0)            ・・・⑧
//        //    より ⑧を③へ代入して
//        //    Ts = (2*ω0* (  (2*θ1)/(ωt+ω0)  ) ) / (ω0-ωt)
//        //    Ts = (4*ω0*θ1)/((ω0-ωt)*(ωt+ω0))  ・・・⑫
//        //
//        //    この⑫を⑪へ代入して
//        //    s = (1/2) * ((1/2) * (  (4*ω0*θ1)/((ω0-ωt)*(ωt+ω0))  ) * -ω0)
//        //    s = (ω0^2*θ1) / (ωt^2-ω0^2)   ・・・⑬
//        //
//        //    ⑬⑫⑧⑨⑩より
//        //    s  = (ω0^2*θ1) / (ωt^2-ω0^2)
//        //    Ts = (4*ω0*θ1) / ((ω0-ωt)*(ωt+ω0))
//        //    T1 = (2*θ1) / (ωt+ω0)
//        //    T2 = (ωt*θ2+ω0*θ2+2*ωt*θ1) / (ωt*(ωt+ω0))
//        //    Te = ((2*ωt^2+2*ω0*ωt)*θ3+(ωt^2+(ωe+ω0)*ωt+ω0*ωe)*θ2+(2*ωt^2+2*ωe*ωt)*θ1) / (ωt*(ωt+ω0)*(ωt+ωe))
//
//        double D1 = D * prm_p1;
//        double D2 = D * (prm_p2 - prm_p1);    //D*(p2 - p1)
//        double D3 = D * (1.0 - prm_p2);       //D*(1 - p2)
//
//        double s  = (W0^2*D1) / (Wt^2-W0^2)
//        double Ts = (4*W0*D1) / ((W0-Wt)*(Wt+W0))
//        double T1 = (2*D1) / (Wt+W0)
//        double T2 = (Wt*D2+W0*D2+2*Wt*D1) / (Wt*(Wt+W0))
//        double Te = ((2*Wt^2+2*W0*Wt)*D3+(Wt^2+(We+W0)*Wt+W0*We)*D2+(2*Wt^2+2*We*Wt)*D1) / (Wt*(Wt+W0)*(Wt+We))
//
//        _smooth_turn_rz_faceang_flg = true;
//        _smooth_turn_rz_faceang_endacc_flg = prm_endacc_flg;
//        _smooth_turn_rz_faceang_top_angvelo = Wt;
//        _smooth_turn_rz_faceang_end_angvelo = We;
//        _smooth_turn_rz_faceang_target_distanceangle = D;
//        _smooth_turn_rz_faceang_target_frames = Te;
//        _smooth_turn_rz_faceang_frame_of_spent = 0;
//        _smooth_turn_rz_faceang_p1 = T1;
//        _smooth_turn_rz_faceang_p2 = T2;
//        _smooth_turn_rz_faceang_progress = 0;
//    }



}


void GgafDxKurokoA::takeoverMvFrom(GgafDxKurokoA* const prm_pKurokoA) {
    // キャラの移動方角単位ベクトル
    _vX = prm_pKurokoA->_vX;
    _vY = prm_pKurokoA->_vY;
    _vZ = prm_pKurokoA->_vZ;
    // 移動方角のZ軸回転角
    _angRzMv = prm_pKurokoA->_angRzMv;
    // 移動方角のY軸回転角
    _angRyMv = prm_pKurokoA->_angRyMv;
    // 移動速度
    _veloMv = prm_pKurokoA->_veloMv;
    // 移動速度上限
    _veloTopMv = prm_pKurokoA->_veloTopMv;
    // 移動速度下限
    _veloBottomMv = prm_pKurokoA->_veloBottomMv;
    // 移動加速度
    _accMv = prm_pKurokoA->_accMv;
    // 移動躍度
    //_jerkMv = prm_pKurokoA->_jerkMv;
}

GgafDxKurokoA::~GgafDxKurokoA() {
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
// ２軸回転アングル値 (_angRzMv, _angRyMv) で表す方法の２種類用意した。クォータニオンは今のところ無し。
// _angRzMv は Z軸回転角、 _angRyMv は Y軸回転角 を意味している。
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
// しかしこの本クラスでは、よく使うのは２軸表現の方で、メソッドも _angRzMv と _angRyMv を操作するものが中心となっている。
// 実は結局内部で単位方向ベクトルを求めているのだが、座標回転計算を、整数型の _angRzMv と _angRyMv でさんざん行ってから、
// 最後に１回単位ベクトルを求める。という方が速いのではと考えたため、このような設計になった。
// TODO:最適化の余地だいぶ残っているハズ。またいつか。
// (_angRzMv, _angRyMv)をメソッドにより操作して、各フレームの最後の内部処理で方向ベクトル(_vX, _vY, _vZ) を同期させている。
// (_vX, _vY, _vZ)メンバーをメソッドを使わず直接操作すると、(_angRzMv, _angRyMv)との同期が崩れるので注意。
// 本クラスのメソッドを使用する限りでは、そんなことは起こらない。
//
// ＜移動速度:Velo or MvVelo＞
// キャラは「移動速度」(_veloMv)を保持している。移動する方法は簡単で、基本的に毎フレーム「移動方角」に「移動速度」分動くだけ。
// 座標増分は「移動方角」(_vX, _vY, _vZ)に「移動速度」(_veloMv)を掛け算している。
// １フレーム後の座標は現在の座標から (_vX*_veloMv, _vY*_veloMv, _vZ*_veloMv) 移動した場所である。
// このベクトルに本ライブラリの単位距離(ゲーム中の長さ１と考える整数倍値）を乗じる。
// よって、(_vX*_veloMv*LEN_UNIT, _vY*_veloMv*LEN_UNIT, _vZ*_veloMv*LEN_UNIT)が１フレーム後の座標増分。

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
// （※→この機能は GgafDxKurokoB に集約され独立したクラスとなりました！）

//2010/02/19追記
// ※たまに「RyRz」という表現が存在する（「RzRy」と異なる）が、これは「Y軸回転 → Z軸回転の順番の移動方角」を表しているので注意。
//   また、「移動方角（Z軸）」を軸回転の順番の違いを明確にするため
//   「RzRyのRz」「RyRzのRz」と書いたりしているところもある。（単に「Rz」だけの場合は「RzRyのRz」を意味している）

//追記
//・滑らか移動が可能に！

//TODO:
//躍度（加加速度）の追加
//任意軸回転（クォータニオン）
//クラスの肥大化 → 黒子Bを作った
//【メモ】を纏める
