#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;



FixedFrameSplineSequence::FixedFrameSplineSequence(SplineManufacture* prm_pManufacture, GgafDx9KurokoA* prmpKurokoA_target) :
        SplineSequence(prm_pManufacture, prmpKurokoA_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
}
FixedFrameSplineSequence::FixedFrameSplineSequence(GgafDx9KurokoA* prmpKurokoA_target,
                                                 Spline3D* prmpSpl,
                                                 frame prm_spent_frame,
                                                 ang_velo prm_ang_veloRzRyMv):
        SplineSequence(NULL, prmpKurokoA_target) {

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prmpSpl), prm_spent_frame, prm_ang_veloRzRyMv);
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
        Spline3D* pSpl = _pFixedFrameSplManuf->_sp;
        if (_option == RELATIVE_DIRECTION) {
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X - _pActor_target->_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y - _pActor_target->_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z - _pActor_target->_Z;
            GgafDx9KurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = GgafDx9Util::SIN[pKurokoA_target->_angRzMv/ANGLE_RATE];
            _COS_RzMv_begin = GgafDx9Util::COS[pKurokoA_target->_angRzMv/ANGLE_RATE];
            _SIN_RyMv_begin = GgafDx9Util::SIN[pKurokoA_target->_angRyMv/ANGLE_RATE];
            _COS_RyMv_begin = GgafDx9Util::COS[pKurokoA_target->_angRyMv/ANGLE_RATE];
        } else if (_option == RELATIVE_COORD) {
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X - _pActor_target->_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y - _pActor_target->_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z - _pActor_target->_Z;
        } else { //ABSOLUTE_COORD
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z;

        }
    }
}


void FixedFrameSplineSequence::behave() {
    if (_is_executing) {
        Spline3D* pSpl = _pFixedFrameSplManuf->_sp;
        GgafDx9KurokoA* pKurokoA_target = _pActor_target->_pKurokoA;

        //現在の点INDEX
        int point_index = _execute_frames/_pFixedFrameSplManuf->_frame_of_segment;
        if ( point_index == pSpl->_rnum) {
            //終了
            _is_executing = false;
            return;
        }

        //変わり目
        if (_execute_frames % _pFixedFrameSplManuf->_frame_of_segment == 0) {
            double dx = _flip_X*pSpl->_X_compute[point_index]*_pFixedFrameSplManuf->_rate_X + _offset_X;
            double dy = _flip_Y*pSpl->_Y_compute[point_index]*_pFixedFrameSplManuf->_rate_Y + _offset_Y;
            double dz = _flip_Z*pSpl->_Z_compute[point_index]*_pFixedFrameSplManuf->_rate_Z + _offset_Z;

            //次の補間点（or基点)に移動方角を向ける
            if (_option == RELATIVE_DIRECTION) {
                //    並行移動 ＞ Z軸回転 ＞ Y軸回転
                //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
                //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
                //    | sinRy                                  , 0                    , cosRy                                   , 0 |
                //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
                pKurokoA_target->execTurnMvAngSequence(
                                ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * _COS_RyMv_begin  + dz*_SIN_RyMv_begin) - _X_begin,
                                 (dx*_SIN_RzMv_begin + dy* _COS_RzMv_begin) - _Y_begin,
                                ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz*_COS_RyMv_begin) - _Z_begin,
                                _pFixedFrameSplManuf->_ang_veloRzRyMv, 0,
                                _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            } else if (_option == RELATIVE_COORD) {
                //相対座標ターゲット
                pKurokoA_target->execTurnMvAngSequence(
                                dx - _X_begin, dy - _Y_begin, dz - _Z_begin,
                                _pFixedFrameSplManuf->_ang_veloRzRyMv, 0,
                                _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            } else { //RELATIVE_DIRECTION
                //絶対座標ターゲット
                pKurokoA_target->execTurnMvAngSequence(
                                dx, dy, dz,
                                _pFixedFrameSplManuf->_ang_veloRzRyMv, 0,
                                _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);
            }

            //移動速度設定
            if (point_index == 0) {
                //_paSPMvVeloTo[0] は未定義なので、特別処理
                if (pKurokoA_target->_veloMv <= 0) {
                    pKurokoA_target->setMvVelo(1000);
                } else {
                    //なにもせん
                }
            } else {
                pKurokoA_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[point_index]);
            }
        }
        _execute_frames++;
    }

}
FixedFrameSplineSequence::~FixedFrameSplineSequence() {
    if (_pFixedFrameSplManuf->_pSplSrcCon) {

    } else {
        SplineSource* pSplSrc = _pFixedFrameSplManuf->_pSplSrc;
        DELETE_IMPOSSIBLE_NULL(pSplSrc);
        DELETE_IMPOSSIBLE_NULL(_pFixedFrameSplManuf);
    }
}
