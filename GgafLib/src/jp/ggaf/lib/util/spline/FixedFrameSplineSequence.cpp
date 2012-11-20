#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;



FixedFrameSplineSequence::FixedFrameSplineSequence(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prmpKurokoA_target) :
        SplineSequence(prm_pManufacture, prmpKurokoA_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
}
FixedFrameSplineSequence::FixedFrameSplineSequence(GgafDxKurokoA* prmpKurokoA_target,
                                                 SplineLine* prmpSpl,
                                                 frame prm_spent_frame,
                                                 angvelo prm_angveloRzRyMv):
        SplineSequence(nullptr, prmpKurokoA_target) {  //nullptrで渡す事により、_is_created_pManufacture が falseになる

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prmpSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//これも忘れないように。いずれこのタイプは消す
    _pManufacture = _pFixedFrameSplManuf;

    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
}


void FixedFrameSplineSequence::exec(SplinTraceOption prm_option) {
    if (_pFixedFrameSplManuf) {

        _is_executing = true;
        _option = prm_option;
        _execute_frames = 0;
        SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
        double P0X = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X;
        double P0Y = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y;
        double P0Z = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z;
        _X_begin = _pActor_target->_X;
        _Y_begin = _pActor_target->_Y;
        _Z_begin = _pActor_target->_Z;
        if (_option == RELATIVE_DIRECTION) {
            GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
            _COS_RzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
            _SIN_RyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
            _COS_RyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
            _distance_to_begin = UTIL::getDistance(
                                           0.0  , 0.0  , 0.0  ,
                                           P0X, P0Y, P0Z
                                      );
        } else if (_option == RELATIVE_COORD) {
            _distance_to_begin = UTIL::getDistance(
                                           0.0  , 0.0  , 0.0  ,
                                           P0X, P0Y, P0Z
                                      );
        } else { //ABSOLUTE_COORD
            _distance_to_begin = UTIL::getDistance(
                                    _pActor_target->_X,
                                    _pActor_target->_Y,
                                    _pActor_target->_Z,
                                    _X_begin,
                                    _Y_begin,
                                    _Z_begin
                                 );
        }
    }
}


void FixedFrameSplineSequence::behave() {
    if (_is_executing) {
        SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
        GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;

        //現在の点INDEX
        _point_index = _execute_frames/_pFixedFrameSplManuf->_frame_of_segment;
        if ( _point_index == pSpl->_rnum) {
            //終了
            _is_executing = false;
            return;
        }

        //変わり目
        if (_execute_frames % _pFixedFrameSplManuf->_frame_of_segment == 0) {
            double dx = _flip_X*pSpl->_X_compute[_point_index]*_pFixedFrameSplManuf->_rate_X + _offset_X;
            double dy = _flip_Y*pSpl->_Y_compute[_point_index]*_pFixedFrameSplManuf->_rate_Y + _offset_Y;
            double dz = _flip_Z*pSpl->_Z_compute[_point_index]*_pFixedFrameSplManuf->_rate_Z + _offset_Z;

            //次の補間点（or制御点)に移動方角を向ける
            if (_option == RELATIVE_DIRECTION) {
                //    並行移動 ＞ Z軸回転 ＞ Y軸回転
                //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
                pKurokoA_target->execTurnMvAngSequence(
                                    ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) *  _COS_RyMv_begin + dz*_SIN_RyMv_begin) + _X_begin,
                                     (dx*_SIN_RzMv_begin + dy* _COS_RzMv_begin)                                          + _Y_begin,
                                    ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz*_COS_RyMv_begin) + _Z_begin,
                                    _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                    _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            } else if (_option == RELATIVE_COORD) {
                //相対座標ターゲット
                pKurokoA_target->execTurnMvAngSequence(
                                    dx + _X_begin,
                                    dy + _Y_begin,
                                    dz + _Z_begin,
                                    _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                    _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            } else { //RELATIVE_DIRECTION
                //絶対座標ターゲット
                pKurokoA_target->execTurnMvAngSequence(
                                    dx, dy, dz,
                                    _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                    _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);
            }

            //移動速度設定
            if (_point_index == 0) {
                //_paSPMvVeloTo[0] は未定義なので、特別処理
                if (pKurokoA_target->_veloMv <= 0) {
                    //もし、現在速度が0の場合、始点に到達するために無理やり速度を 1000 にする。
                    _TRACE_("[警告]  FixedFrameSplineSequence::behave() "<<pKurokoA_target->_pActor->getName()<<" の速度を無理やり速度を 1000 にしました。意図してますか？");
                    pKurokoA_target->setMvVelo(1000);
                } else {
                    //なにもせん
                }
            } else {
                pKurokoA_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index]);
            }
        }
        _execute_frames++;
    }

}
FixedFrameSplineSequence::~FixedFrameSplineSequence() {

}
