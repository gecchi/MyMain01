#include "jp/ggaf/lib/util/spline/FixedFrameSplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* const prm_pKuroko_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKuroko_target) {
    _pFixedFrameSplManuf = (FixedFrameSplineManufacture*)prm_pManufacture;
    _sinRzMv_begin = 0;
    _cosRzMv_begin = 0;
    _sinRyMv_begin = 0;
    _cosRyMv_begin = 0;
    _ang_rz_mv_begin = prm_pKuroko_target->_ang_rz_mv;
    _ang_ry_mv_begin = prm_pKuroko_target->_ang_ry_mv;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}
FixedFrameSplineKurokoLeader::FixedFrameSplineKurokoLeader(GgafDxKuroko* const prm_pKuroko_target,
                                                           SplineLine* prm_pSpl,
                                                           frame prm_spent_frame,
                                                           angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKuroko_target) {  //nullptrで渡す事により、_is_created_pManufacture が falseになる

    _pFixedFrameSplManuf = NEW FixedFrameSplineManufacture(NEW SplineSource(prm_pSpl), prm_spent_frame, prm_angveloRzRyMv);
    _pFixedFrameSplManuf->calculate();//これも忘れないように。いずれこのタイプは消す
    _pManufacture = _pFixedFrameSplManuf;

    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
    _ang_rz_mv_begin = prm_pKuroko_target->_ang_rz_mv;
    _ang_ry_mv_begin = prm_pKuroko_target->_ang_ry_mv;
    _point_index = 0;
    _prev_point_index = -1;
    _hosei_frames = 0;
}

void FixedFrameSplineKurokoLeader::getPointCoord(int prm_point_index, coord &out_x, coord& out_y, coord& out_z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedFrameSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedFrameSplineKurokoLeader::getPointCoord ポイントのインデックスオーバー。"<<
                                   "補完点数="<<(_pFixedFrameSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    SplineLine* pSpl = _pFixedFrameSplManuf->_sp;
    double dx = _flip_x*pSpl->_x_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_x + _offset_x;
    double dy = _flip_y*pSpl->_y_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_y + _offset_y;
    double dz = _flip_z*pSpl->_z_compute[prm_point_index]*_pFixedFrameSplManuf->_rate_z + _offset_z;
    //次の補間点（or制御点)に移動方角を向ける
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading == false) {
            _sinRzMv_begin = ANG_SIN(_ang_rz_mv_begin);
            _cosRzMv_begin = ANG_COS(_ang_rz_mv_begin);
            _sinRyMv_begin = ANG_SIN(_ang_ry_mv_begin);
            _cosRyMv_begin = ANG_COS(_ang_ry_mv_begin);
            if (!_is_fix_start_pos) {
                _x_start = _pActor_target->_x;
                _y_start = _pActor_target->_y;
                _z_start = _pActor_target->_z;
            }
        }
        //    平行移動 ＞ Z軸回転 ＞ Y軸回転
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_x = ((dx*_cosRzMv_begin + dy*-_sinRzMv_begin) *  _cosRyMv_begin + dz*_sinRyMv_begin) + _x_start;
        out_y =  (dx*_sinRzMv_begin + dy* _cosRzMv_begin)                                        + _y_start;
        out_z = ((dx*_cosRzMv_begin + dy*-_sinRzMv_begin) * -_sinRyMv_begin + dz*_cosRyMv_begin) + _z_start;
    } else if (_option == RELATIVE_COORD) {
        //相対座標ターゲット
        if (_is_leading == false) {
            if (!_is_fix_start_pos) {
                _x_start = _pActor_target->_x;
                _y_start = _pActor_target->_y;
                _z_start = _pActor_target->_z;
            }
        }
        out_x = dx + _x_start;
        out_y = dy + _y_start;
        out_z = dz + _z_start;
    } else { //RELATIVE_DIRECTION
        //絶対座標ターゲット
        out_x = dx;
        out_y = dy;
        out_z = dz;
    }
}

void FixedFrameSplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pFixedFrameSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        _ang_rz_mv_begin = _pActor_target->getKuroko()->_ang_rz_mv;
        _ang_ry_mv_begin = _pActor_target->getKuroko()->_ang_ry_mv;
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
    double p0x = (_flip_x * pSpl->_x_compute[0] * _pFixedFrameSplManuf->_rate_x) + _offset_x;
    double p0y = (_flip_y * pSpl->_y_compute[0] * _pFixedFrameSplManuf->_rate_y) + _offset_y;
    double p0z = (_flip_z * pSpl->_z_compute[0] * _pFixedFrameSplManuf->_rate_z) + _offset_z;
    if (_cnt_loop >= 2) {
        //２周目以降は fixStartPosition() が設定されていても、効力はなくなる。
        _is_fix_start_pos = false;
    }
    if (_is_fix_start_pos) {
        //開始座標(_x_start, _y_start, _z_start)は、
        //別途 fixStartPosition() により設定済み
    } else {
        if (_cnt_loop == 1) {
            //１週目は正に今の座標が開始座標
            _x_start = _pActor_target->_x;
            _y_start = _pActor_target->_y;
            _z_start = _pActor_target->_z;
        } else {
            //２週目以降は、開始座標は、前回の論理最終座標が、開始座標
            coord end_x, end_y, end_z;
            getPointCoord(getPointNum()-1, end_x, end_y, end_z);
            _x_start = end_x;
            _y_start = end_y;
            _z_start = end_z;
        }
    }
    if (_option == RELATIVE_DIRECTION) {
        _sinRzMv_begin = ANG_SIN(_ang_rz_mv_begin);
        _cosRzMv_begin = ANG_COS(_ang_rz_mv_begin);
        _sinRyMv_begin = ANG_SIN(_ang_ry_mv_begin);
        _cosRyMv_begin = ANG_COS(_ang_ry_mv_begin);
        _distance_to_begin = UTIL::getDistance(
                                       0.0  , 0.0  , 0.0  ,
                                       p0x, p0y, p0z
                                  );

    } else if (_option == RELATIVE_COORD) {
        _distance_to_begin = UTIL::getDistance(
                                       0.0  , 0.0  , 0.0  ,
                                       p0x, p0y, p0z
                                  );
    } else { //ABSOLUTE_COORD
        _distance_to_begin = UTIL::getDistance(
                                (double)(_pActor_target->_x),
                                (double)(_pActor_target->_y),
                                (double)(_pActor_target->_z),
                                p0x, p0y, p0z
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
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
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
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            pKuroko_target->turnMvAngTwd(x, y, z,
                                         _pFixedFrameSplManuf->_angveloRzRyMv, 0,
                                         _pFixedFrameSplManuf->_turn_way, _pFixedFrameSplManuf->_turn_optimize);

            if (_point_index == 0) {
                //現座標と開始が離れている。
                //誤差も仕方ないので _fFrame_of_segment で始点に移動する速度を付与
                pKuroko_target->setMvVelo((velo)(_distance_to_begin / _pFixedFrameSplManuf->_fFrame_of_segment));
            } else {
                pKuroko_target->setMvVelo(_pFixedFrameSplManuf->_paSPMvVeloTo[_point_index]);
            }
        }
        _leading_frames++;
    }
    //_TRACE_(_pActor_target->getBehaveingFrame()<<": "<<_leading_frames<<": _cnt_loop="<<_cnt_loop<<"  _point_index="<<_point_index<<" velo="<<_pActor_target->getKuroko()->getMvVelo()<<" xyz="<<_pActor_target->_x<<","<<_pActor_target->_y<<","<<_pActor_target->_z);
}
FixedFrameSplineKurokoLeader::~FixedFrameSplineKurokoLeader() {

}
