#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prm_pKurokoA_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKurokoA_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _SIN_RzMv_begin = 0;
    _COS_RzMv_begin = 0;
    _SIN_RyMv_begin = 0;
    _COS_RyMv_begin = 0;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}
FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(GgafDxKurokoA* prm_pKurokoA_target,
                                                           SplineLine* prmpSpl,
                                                           frame prm_spent_frame,
                                                           angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKurokoA_target) {  //nullptrで渡す事により、_is_created_pManufacture が falseになる

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prmpSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//これも忘れないように。いずれこのタイプは消す
    _pManufacture = _pFixedFrameSplManuf;

    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}

void FixedFrameSplineKurokoLeader::getPointCoord(int prm_point_index, coord &out_X, coord& out_Y, coord& out_Z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedFrameSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedFrameSplineKurokoLeader::getPointCoord ポイントのインデックスオーバー。"<<
                                   "補完点数="<<(_pFixedFrameSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
    double dx = _flip_X*pSpl->_X_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_X + _offset_X;
    double dy = _flip_Y*pSpl->_Y_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_Y + _offset_Y;
    double dz = _flip_Z*pSpl->_Z_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_Z + _offset_Z;
    //次の補間点（or制御点)に移動方角を向ける
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading == false) {
            GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
            _COS_RzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
            _SIN_RyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
            _COS_RyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
            _X_begin = _pActor_target->_X;
            _Y_begin = _pActor_target->_Y;
            _Z_begin = _pActor_target->_Z;
        }
        //    平行移動 ＞ Z軸回転 ＞ Y軸回転
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_X = ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) *  _COS_RyMv_begin + dz*_SIN_RyMv_begin) + _X_begin;
        out_Y =  (dx*_SIN_RzMv_begin + dy* _COS_RzMv_begin)                                          + _Y_begin;
        out_Z = ((dx*_COS_RzMv_begin + dy*-_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz*_COS_RyMv_begin) + _Z_begin;
    } else if (_option == RELATIVE_COORD) {
        //相対座標ターゲット
        out_X = dx + _X_begin;
        out_Y = dy + _Y_begin;
        out_Z = dz + _Z_begin;
    } else { //RELATIVE_DIRECTION
        //絶対座標ターゲット
        out_X = dx;
        out_Y = dy;
        out_Z = dz;
    }
}

void FixedFrameSplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pFixedFrameSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        restart();
    } else {
        throwGgafCriticalException("FixedFrameSplineKurokoLeader::start Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}
void FixedFrameSplineKurokoLeader::restart() {
    _leading_frames = 0;
    _hosei_frames = 0;
    _point_index = 0;
    _prev_point_index = -1;
    SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
    double P0X = (_flip_X * pSpl->_X_compute[0] * _pFixedFrameSplManuf->_rate_X) + _offset_X;
    double P0Y = (_flip_Y * pSpl->_Y_compute[0] * _pFixedFrameSplManuf->_rate_Y) + _offset_Y;
    double P0Z = (_flip_Z * pSpl->_Z_compute[0] * _pFixedFrameSplManuf->_rate_Z) + _offset_Z;
    _X_begin = _pActor_target->_X;
    _Y_begin = _pActor_target->_Y;
    _Z_begin = _pActor_target->_Z;
    if (_option == RELATIVE_DIRECTION) {
        _SIN_RzMv_begin = ANG_SIN(_pActor_target->_pKurokoA->_angRzMv);
        _COS_RzMv_begin = ANG_COS(_pActor_target->_pKurokoA->_angRzMv);
        _SIN_RyMv_begin = ANG_SIN(_pActor_target->_pKurokoA->_angRyMv);
        _COS_RyMv_begin = ANG_COS(_pActor_target->_pKurokoA->_angRyMv);
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
                                (double)(_pActor_target->_X),
                                (double)(_pActor_target->_Y),
                                (double)(_pActor_target->_Z),
                                P0X, P0Y, P0Z
                             );
    }
    //始点へ行く特別処理。
    //始点への距離(_distance_to_begin) がわかっているので、
    //
    // 始点への速度 = (velo)(_distance_to_begin / _pFixedFrameSplManuf->_fFrame_of_segment)
    //
    //としたいが、
    //_pFixedFrameSplManuf->_fFrame_of_segment は、現座標～始点 を除いた
    //計算で求めているので、補完点数が少ない場合、費やされるフレーム合計の誤差が大きい。
    //そこで始点への距離0とみなせる場合には、現座標～始点 をなかったコトにする。
    //そうでなければ仕方ないので、費やされるフレーム合計の誤差を認める仕様とする。
    if (ABS(_distance_to_begin) <= PX_C(1)) {
        //始点への距離が無い、間引く。
        //_TRACE_("＜警告＞FixedFrameSplineKurokoLeader::start("<<prm_option<<") _pActor_target="<<_pActor_target->getName()<<
        //    " 現座標～始点[0]への距離は 0 であるため、現座標～始点への移動プロセスはカットされます。");
        _hosei_frames = _pFixedFrameSplManuf->_fFrame_of_segment;
        //これにより、_point_index は、初回いきなり1から始まる。
    } else {
        _TRACE_("＜警告＞FixedFrameSplineKurokoLeader::restart("<<_option<<") _pActor_target="<<_pActor_target->getName()<<
            " 現座標～始点[0]への距離("<<_distance_to_begin<<" coord)が離れているため、現座標～始点への移動プロセスとしてセグメントが＋１されます。"<<
            "そのため、合計移動フレーム時間に誤差(+"<<_pFixedFrameSplManuf->_fFrame_of_segment<<"フレーム)が生じます。ご了承くださいませ。");
        _hosei_frames = 0;
        //これにより、_point_index は、初回0から始まる。
    }

}

void FixedFrameSplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
        //現在の点INDEX
        _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_fFrame_of_segment;
        if ( _point_index == _pFixedFrameSplManuf->_sp->_rnum) {
            if (_cnt_loop == _max_loop) {
                //終了
                _is_leading = false;
                return;
            } else {
                //ループ
                _cnt_loop++;
                restart();
                _point_index = (_leading_frames+_hosei_frames) / _pFixedFrameSplManuf->_fFrame_of_segment;
            }
        }

        //変わり目
        if (_prev_point_index != _point_index) {
            _prev_point_index = _point_index;
            coord X, Y, Z;
            getPointCoord(_point_index, X, Y, Z);
            pKurokoA_target->turnMvAngTwd(X, Y, Z,
                                          _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                          _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            if (_point_index == 0) {
                //現座標と開始が離れている。
                //誤差も仕方ないので _fFrame_of_segment で始点に移動する速度を付与
                pKurokoA_target->setMvVelo((velo)(_distance_to_begin / _pFixedFrameSplManuf->_fFrame_of_segment));
            } else {
                pKurokoA_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index]);
            }
        }
        _leading_frames++;
    }

}
FixedFrameSplineKurokoLeader::~FixedFrameSplineKurokoLeader() {

}
