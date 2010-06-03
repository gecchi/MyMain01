#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9FixedVelocitySplineProgram::GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor)
  : GgafDx9SplineProgram(prm_pActor) {
    _paDistace_to = NULL;
    _paFrame_need_at = NULL;
    _is_executing = false;
    _option = 0;

    _X_begin = 0;
    _Y_begin = 0;
    _Z_begin = 0;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
    _fFrame_executing = 0;
    _fFrame_next_point = 0;
    _point_index = 0;
    //_fSPPointFrame = 0;
    _angFaceMove = ANGLE360;
    _veloMvUnit = LEN_UNIT;
}

GgafDx9FixedVelocitySplineProgram::GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor,
                                                                     GgafDx9Spline3D* prm_sp,
                                                                     angvelo prm_angFaceMove)
                                                    : GgafDx9SplineProgram(prm_pActor,
                                                                           prm_sp) {
    _angFaceMove = prm_angFaceMove;
    init();
}

GgafDx9FixedVelocitySplineProgram::GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor,
                                                                     double prm_paaCriteriaPoints[][3],
                                                                     int prm_point_num,
                                                                     double prm_accuracy,
                                                                     angvelo prm_angFaceMove )

                                                    : GgafDx9SplineProgram(prm_pActor,
                                                                           prm_paaCriteriaPoints,
                                                                           prm_point_num,
                                                                           prm_accuracy)  {
    _angFaceMove = prm_angFaceMove;
    init();
}

void GgafDx9FixedVelocitySplineProgram::init() {

    //各点の時点の、距離と必要なフレーム数を予め全部求めておく

    // prm_paaCriteriaPoints[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // prm_point_num = 3          //基点の数
    // prm_accuracy = 0.25(=1/4)  //補完点精度
    //
    // の場合、下図のようになります。
    //
    // X:基点
    // o:基点間の補完点（スプライン曲線通過点）
    // X--o: 移動予定の座標線
    // _paDistace_to[] : 現在の補完点から、次の補完点までの距離
    // _paFrame_need_at[] : 始点から補完点到達に必要なフレーム数の配列
    //
    // sp._rnum は合計の点の数を返す。したがって sp._rnum = 9 になる。
    // prm_accuracy が綺麗な分数にならない場合、基点上に補完点が繰るかとか、全然わからないので、sp._rnumを必ず使用せよ
    // 下図は綺麗に重なった場合の図である。
    //
    //                           ＜速さは  _veloMvUnit = 1000＞
    //
    //               _paFrame_need_at[1] 必要なフレーム数
    //                     ||              _paFrame_need_at[5]
    //                   <--->                      ||                 _paFrame_need_at[8]
    //                   <----------------------------->                      ||
    //                   <------------------------------------------------------->
    //
    //              _paDistace_to[1]      _paDistace_to[5]         _paDistace_to[8]
    //                    ||                     ||                         ||
    //                   <--->                <------->                  <------->
    //                  X----o----o----o-----X--------o---------o--------o-------X
    //                  ^                    ^        ^                          ^
    //                  |                    |        |                          |
    //            (sp._X_compute[0],         | (sp._X_compute[5],        sp._X_compute[8]
    //             sp._Y_compute[0],         |  sp._Y_compute[5],        sp._Y_compute[8]
    //             sp._Z_compute[0])         |  sp._Z_compute[5])        sp._Z_compute[8]
    //                  |                    |                                   |
    // (prm_paaCriteriaPoints[0][0],   (prm_paaCriteriaPoints[1][0],    (prm_paaCriteriaPoints[2][0],
    //  prm_paaCriteriaPoints[0][1],    prm_paaCriteriaPoints[1][1],     prm_paaCriteriaPoints[2][1],
    //  prm_paaCriteriaPoints[0][2])    prm_paaCriteriaPoints[1][2])     prm_paaCriteriaPoints[2][2])
    //   = (1000,2000,3000)             = (2000,1000,0)                    = (3900, 0, 1000)
    //
    //                 <--------------------------------------------------------->
    //                         ずっと veloMoveUnit の速度で移動とした場合を計算
    //


    _veloMvUnit = LEN_UNIT; //速度1000とした場合の、各区間のフレーム数を求める
    _paDistace_to = NEW int[_sp->_rnum];
    _paFrame_need_at = NEW float[_sp->_rnum];

    int x_from, y_from, z_from;
    int x_to, y_to, z_to;

    x_to = _sp->_X_compute[0];
    y_to = _sp->_Y_compute[0];
    z_to = _sp->_Z_compute[0];

    _paFrame_need_at[0] = 0;

    for (int t = 1; t < _sp->_rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_X_compute[t];
        y_to = _sp->_Y_compute[t];
        z_to = _sp->_Z_compute[t];
        _paDistace_to[t] = GgafDx9Util::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );

        //距離 paDistaceTo[t] を、速度 _veloMvUnit(=1000) で移動するのに必要なフレーム数を求める。
        //時間＝距離÷速さ
        _paFrame_need_at[t] = _paFrame_need_at[t-1] + (float)(1.0*_paDistace_to[t] / _veloMvUnit);

    }

}

void GgafDx9FixedVelocitySplineProgram::begin(int prm_option) {

    if (_sp != NULL) {
        _is_executing = true;
        _option = prm_option;
        _fFrame_executing = 0;
        _fFrame_next_point = 0.0;
        _point_index = 0;
        if (_option == 2) {
            _X_begin = _sp->_X_compute[0] - _pActor_target->_X ;
            _Y_begin = _sp->_Y_compute[0] - _pActor_target->_Y;
            _Z_begin = _sp->_Z_compute[0] - _pActor_target->_Z;
            _SIN_RzMv_begin = GgafDx9Util::SIN[_pActor_target->_pMover->_angRzMv/ANGLE_RATE];
            _COS_RzMv_begin = GgafDx9Util::COS[_pActor_target->_pMover->_angRzMv/ANGLE_RATE];
            _SIN_RyMv_begin = GgafDx9Util::SIN[_pActor_target->_pMover->_angRyMv/ANGLE_RATE];
            _COS_RyMv_begin = GgafDx9Util::COS[_pActor_target->_pMover->_angRyMv/ANGLE_RATE];
        } else if (_option == 1) {
            _X_begin = _sp->_X_compute[0] - _pActor_target->_X ;
            _Y_begin = _sp->_Y_compute[0] - _pActor_target->_Y;
            _Z_begin = _sp->_Z_compute[0] - _pActor_target->_Z;
        }
    }
}




void GgafDx9FixedVelocitySplineProgram::behave() {
    if (_is_executing) {
        GgafDx9GeometryMover* _pActorMover = _pActor_target->_pMover;


        //変わり目
        if (_fFrame_executing >= _fFrame_next_point) {

            if (_option == 2) {
                //    並行移動 ＞ Z軸回転 ＞ Y軸回転
                //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
                _pActorMover->setStopTarget_RzRyMvAng(
                        ((_sp->_X_compute[_point_index] * _COS_RzMv_begin + _sp->_Y_compute[_point_index] * -_SIN_RzMv_begin) * _COS_RyMv_begin + _sp->_Z_compute[_point_index] * _SIN_RyMv_begin) - _X_begin,
                        (_sp->_X_compute[_point_index] * _SIN_RzMv_begin + _sp->_Y_compute[_point_index] * _COS_RzMv_begin) - _Y_begin,
                        ((_sp->_X_compute[_point_index] * _COS_RzMv_begin + _sp->_Y_compute[_point_index] * -_SIN_RzMv_begin) * -_SIN_RyMv_begin + _sp->_Z_compute[_point_index] * _COS_RyMv_begin) - _Z_begin
                    );
            } else if (_option == 1) {
                //相対座標ターゲット
                _pActorMover->setStopTarget_RzRyMvAng(_sp->_X_compute[_point_index] - _X_begin,
                                                    _sp->_Y_compute[_point_index] - _Y_begin,
                                                    _sp->_Z_compute[_point_index] - _Z_begin);
            } else {
                //絶対座標ターゲット
                _pActorMover->setStopTarget_RzRyMvAng(_sp->_X_compute[_point_index],
                                                    _sp->_Y_compute[_point_index],
                                                    _sp->_Z_compute[_point_index]);
            }
            if (_pActorMover->getRzMvAngDistance(_pActorMover->_angTargetRzMv, TURN_CLOSE_TO) > 0) {
                _pActorMover->setRzMvAngVelo(_angFaceMove);
            } else {
                _pActorMover->setRzMvAngVelo(-_angFaceMove);
            }
            if (_pActorMover->getRyMvAngDistance(_pActorMover->_angTargetRyMv, TURN_CLOSE_TO) > 0) {
                _pActorMover->setRyMvAngVelo(_angFaceMove);
            } else {
                _pActorMover->setRyMvAngVelo(-_angFaceMove);
            }


            if (_point_index == 0) {
                //始点へ行く！
                if (_option == 2) {
                    //    並行移動 ＞ Z軸回転 ＞ Y軸回転
                    //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                    //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                    //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                    //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |

                    _paDistace_to[0] = GgafDx9Util::getDistance(
                                            (double)_pActor_target->_X,
                                            (double)_pActor_target->_Y,
                                            (double)_pActor_target->_Z,
                                            ((_sp->_X_compute[0] * _COS_RzMv_begin + _sp->_Y_compute[0] * -_SIN_RzMv_begin) * _COS_RyMv_begin + _sp->_Z_compute[0] * _SIN_RyMv_begin) - _X_begin,
                                            (_sp->_X_compute[0] * _SIN_RzMv_begin + _sp->_Y_compute[0] * _COS_RzMv_begin) - _Y_begin,
                                            ((_sp->_X_compute[0] * _COS_RzMv_begin + _sp->_Y_compute[0] * -_SIN_RzMv_begin) * -_SIN_RyMv_begin + _sp->_Z_compute[0] * _COS_RyMv_begin) - _Z_begin
                                         );
                } else if (_option == 1) {
                    //相対座標ターゲット
                    _paDistace_to[0] = GgafDx9Util::getDistance(
                                            (double)_pActor_target->_X,
                                            (double)_pActor_target->_Y,
                                            (double)_pActor_target->_Z,
                                            _sp->_X_compute[0] - _X_begin,
                                            _sp->_Y_compute[0] - _Y_begin,
                                            _sp->_Z_compute[0] - _Z_begin
                                         );
                } else {
                    //絶対座標ターゲット
                    _paDistace_to[0] = GgafDx9Util::getDistance(
                                            (double)_pActor_target->_X,
                                            (double)_pActor_target->_Y,
                                            (double)_pActor_target->_Z,
                                            _sp->_X_compute[0],
                                            _sp->_Y_compute[0],
                                            _sp->_Z_compute[0]
                                         );
                }


                //始点までに必要なフレーム数取得
                _paFrame_need_at[0] =  (float)(1.0*_paDistace_to[0] / _veloMvUnit);
                _fFrame_next_point = _paFrame_need_at[0];
            } else {
                //次の補完点までに必要なフレーム数を更新
                _fFrame_next_point = _paFrame_need_at[0] + _paFrame_need_at[_point_index];
            }

            _point_index++;
            if ( _point_index == _sp->_rnum) {
                //終了
                _is_executing = false;
                return;
            }
        }

        //キャラの速度が1000ならば、_fFrame_executing ++;
        //キャラの速度が2000ならば  _fFrame_executing += 2.0;
        //キャラの速度が500ならば、 _fFrame_executing += 0.5
        _fFrame_executing = _fFrame_executing +  (1.0*_pActorMover->_veloMv / LEN_UNIT);
    }

}
GgafDx9FixedVelocitySplineProgram::~GgafDx9FixedVelocitySplineProgram() {
    DELETEARR_POSSIBLE_NULL(_paDistace_to);
    DELETEARR_POSSIBLE_NULL(_paFrame_need_at);
}
