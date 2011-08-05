#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

//FixedFrameSplineManufacture::FixedFrameSplineManufacture(GgafDx9GeometricActor* prm_pActor)
// : SplineManufacture(prm_pActor) {
//    _SPframe_segment = 0;
//    _paDistace_to = NULL;
//    _paSPMvVeloTo = NULL;
//    _is_executing = false;
//    _option = 0;
//    _SIN_RzMv_begin = 0;
//    _COS_RzMv_begin = 0;
//    _SIN_RyMv_begin = 0;
//    _COS_RyMv_begin = 0;
//    _ang_veloRzRyMv = ANGLE360;
//}
//
//FixedFrameSplineManufacture::FixedFrameSplineManufacture(GgafDx9GeometricActor* prm_pActor,
//                                                               double prm_paaCriteriaPoints[][3],
//                                                               int prm_point_num,
//                                                               double prm_accuracy,
//                                                               frame prm_spent_frame,
//                                                               ang_velo prm_ang_veloRzRyMv )
//
//                                        : SplineManufacture(prm_pActor,
//                                                               prm_paaCriteriaPoints,
//                                                               prm_point_num,
//                                                               prm_accuracy)      {
//    _spent_frame = prm_spent_frame;
//    _ang_veloRzRyMv = prm_ang_veloRzRyMv;
//    init();
//}
//
//FixedFrameSplineManufacture::FixedFrameSplineManufacture(GgafDx9GeometricActor* prm_pActor,
//                                                               Spline3D* prm_sp,
//                                                               frame prm_spent_frame,
//                                                               ang_velo prm_ang_veloRzRyMv)
//
//                                         : SplineManufacture(prm_pActor,
//                                                                prm_sp) {
//    _spent_frame = prm_spent_frame;
//    _ang_veloRzRyMv = prm_ang_veloRzRyMv;
//    init();
//}
//FixedFrameSplineManufacture::FixedFrameSplineManufacture(Spline3D* prm_sp) : SplineManufacture(prm_sp) {
//    init();
//}

FixedFrameSplineManufacture::FixedFrameSplineManufacture(char* prm_idstr, const char* prm_sourceid) :
        SplineManufacture(prm_idstr, prm_sourceid) {
    init();
}


void FixedFrameSplineManufacture::init() {
    //各点の時点の、距離と速度を予め全部求めておく

    // prm_paaCriteriaPoints[2][3] = { {1000,2000,3000}, {2000,1000,0}, {3900, 0, 1000} }
    // prm_point_num = 3          //基点の数
    // prm_accuracy = 0.25(=1/4)  //補完点精度
    // prm_spent_frame = 120      //費やすフレーム
    // の場合、下図のようになります。
    //
    // X:基点
    // o:基点間の補完点（スプライン曲線通過点）
    // X--o: 移動予定の座標線
    // _paDistace_to[] : 次の補完点までの距離
    // paSPMvVeloTo[] : 次の補完点到達に必要な速度
    //
    // sp._rnum は合計の点の数を返す。したがって sp._rnum = 9 になる。
    // prm_accuracy が綺麗な分数にならない場合、基点上に補完点が繰るかとか、全然わからないので、sp._rnumを必ず使用せよ
    // 下図は綺麗に重なった場合の図である。
    //
    //      v = paSPMvVeloTo[1]                              v = paSPMvVeloTo[8]
    //               paSPDistaceTo[1]     paSPDistaceTo[5]          paSPDistaceTo[8]
    //                    ||                     ||                         ||
    //                   <-->                 <------>                    <----->
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
    //                                 120Frame費やして移動(=prm_spent_frame)
    //                  <-->
    //                  frm_segment = １区間は 120/8 Frame = prm_spent_frame / (sp._rnum-1);

    //１区間の使用可能フレーム
    _SPframe_segment = 1.0*_spent_frame / (_sp->_rnum-1);
    if (_SPframe_segment < 1) {
        _SPframe_segment = 1;
    }
    _paDistace_to = NEW coord[_sp->_rnum];
    _paSPMvVeloTo = NEW velo[_sp->_rnum];
    calculate();
}
void FixedFrameSplineManufacture::calculate() {
    coord x_from, y_from, z_from;
    coord x_to, y_to, z_to;

    x_to = _sp->_X_compute[0]*_rate_X + _offset_X;
    y_to = _sp->_Y_compute[0]*_rate_Y + _offset_Y;
    z_to = _sp->_Z_compute[0]*_rate_Z + _offset_Z;
    for (int t = 1; t < _sp->_rnum; t ++) {
        x_from = x_to;
        y_from = y_to;
        z_from = z_to;
        x_to = _sp->_X_compute[t]*_rate_X + _offset_X;
        y_to = _sp->_Y_compute[t]*_rate_Y + _offset_Y;
        z_to = _sp->_Z_compute[t]*_rate_Z + _offset_Z;
        _paDistace_to[t] = GgafDx9Util::getDistance(
                                    x_from,
                                    y_from,
                                    z_from,
                                    x_to,
                                    y_to,
                                    z_to
                                 );

        //距離 paDistaceTo[t] を、時間frm_segment で移動するために必要な速度を求める。
        //速さ＝距離÷時間
        _paSPMvVeloTo[t] = (velo)(_paDistace_to[t] / _SPframe_segment);
    }
    _paSPMvVeloTo[0] = 1000;

//
//    for (int t = 0; t < _sp->_rnum; t ++) {
//        _TRACE_((float)_sp->_X_compute[t]<<"  "<< (float)_sp->_Y_compute[t]<<"  "<< (float)_sp->_Z_compute[t]);
//    }

}

void FixedFrameSplineManufacture::adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z) {
    _rate_X = prm_rate_X;
    _rate_Y = prm_rate_Y;
    _rate_Z = prm_rate_Z;
    //次の補完点までの距離のテーブル、次の補完点到達に必要な移動速度のテーブル再計算
    calculate();
}


//void FixedFrameSplineManufacture::begin(int prm_option) {
//    if (_sp) {
//        _is_executing = true;
//        _option = prm_option;
//        _SPframe = 0;
//        velo v = _pActor_target->_pKurokoA->_veloMv;
//        if (v == 0) {
//            _paSPMvVeloTo[0] = 1000;
//        } else {
//            _paSPMvVeloTo[0] = v;
//        }
//
//        if (_option == 2) {
//            _X_begin = _sp->_X_compute[0]*_rate_X + _offset_X - _pActor_target->_X ;
//            _Y_begin = _sp->_Y_compute[0]*_rate_Y + _offset_Y - _pActor_target->_Y;
//            _Z_begin = _sp->_Z_compute[0]*_rate_Z + _offset_Z - _pActor_target->_Z;
//            _SIN_RzMv_begin = GgafDx9Util::SIN[_pActor_target->_pKurokoA->_angRzMv/ANGLE_RATE];
//            _COS_RzMv_begin = GgafDx9Util::COS[_pActor_target->_pKurokoA->_angRzMv/ANGLE_RATE];
//            _SIN_RyMv_begin = GgafDx9Util::SIN[_pActor_target->_pKurokoA->_angRyMv/ANGLE_RATE];
//            _COS_RyMv_begin = GgafDx9Util::COS[_pActor_target->_pKurokoA->_angRyMv/ANGLE_RATE];
//        } else if (_option == 1) {
//            _X_begin = _sp->_X_compute[0]*_rate_X + _offset_X - _pActor_target->_X;
//            _Y_begin = _sp->_Y_compute[0]*_rate_Y + _offset_Y - _pActor_target->_Y;
//            _Z_begin = _sp->_Z_compute[0]*_rate_Z + _offset_Z - _pActor_target->_Z;
//        } else {
//            _X_begin = _sp->_X_compute[0]*_rate_X + _offset_X;
//            _Y_begin = _sp->_Y_compute[0]*_rate_Y + _offset_Y;
//            _Z_begin = _sp->_Z_compute[0]*_rate_Z + _offset_Z;
//
//        }
//    }
//}


//void FixedFrameSplineManufacture::behave() {
//    if (_is_executing) {
//        GgafDx9KurokoA* _pKurokoA = _pActor_target->_pKurokoA;
//
//        //現在の点INDEX
//        int SPPointIndex = _SPframe/_SPframe_segment;
//        if ( SPPointIndex == _sp->_rnum) {
//            //終了
//            _is_executing = false;
//            return;
//        }
//
//        //変わり目
//        if (_SPframe % _SPframe_segment == 0) {
//            double dx = _sp->_X_compute[SPPointIndex]*_rate_X + _offset_X;
//            double dy = _sp->_Y_compute[SPPointIndex]*_rate_Y + _offset_Y;
//            double dz = _sp->_Z_compute[SPPointIndex]*_rate_Z + _offset_Z;
//
//
//            //次の補間点（or基点)に移動方角を向ける
//            if (_option == 2) {
//                //    並行移動 ＞ Z軸回転 ＞ Y軸回転
//                //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
//                //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
//                //    | sinRy                                  , 0                    , cosRy                                   , 0 |
//                //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
//                _pKurokoA->execTurnMvAngSequence(
//                                ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * _COS_RyMv_begin + dz * _SIN_RyMv_begin) - _X_begin,
//                                (dx * _SIN_RzMv_begin + dy * _COS_RzMv_begin) - _Y_begin,
//                                ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz * _COS_RyMv_begin) - _Z_begin,
//                                _ang_veloRzRyMv, 0,
//                                TURN_CLOSE_TO, true
//                              );
//            } else if (_option == 1) {
//                //相対座標ターゲット
//                _pKurokoA->execTurnMvAngSequence(
//                                dx - _X_begin, dy - _Y_begin, dz - _Z_begin,
//                                _ang_veloRzRyMv, 0,
//                                TURN_CLOSE_TO, true
//                              );
//            } else {
//                //絶対座標ターゲット
//                _pKurokoA->execTurnMvAngSequence(
//                                dx, dy, dz,
//                                _ang_veloRzRyMv, 0,
//                                TURN_CLOSE_TO, true
//                              );
//            }
//            _pActor_target->_pKurokoA->setMvVelo(_paSPMvVeloTo[SPPointIndex]);
//        }
//        _SPframe++;
//    }
//
//}

SplineProgram* FixedFrameSplineManufacture::createSplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor) {
    return NEW FixedFrameSplineProgram(this, prm_pForWhichActor);
}
FixedFrameSplineManufacture::~FixedFrameSplineManufacture() {
    //イニシャライズされる前に解放されるかもしれない
    DELETEARR_POSSIBLE_NULL(_paDistace_to);
    //イニシャライズされる前に解放されるかもしれない
    DELETEARR_POSSIBLE_NULL(_paSPMvVeloTo);
}
