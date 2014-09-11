#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* const prm_pKuroko_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKuroko_target) {
    _pFixedVeloSplManuf = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
    _ang_rz_mv_begin = prm_pKuroko_target->_ang_rz_mv;
    _ang_ry_mv_begin = prm_pKuroko_target->_ang_ry_mv;
}

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(GgafDxKuroko* const prm_pKuroko_target,
                                                                 SplineLine* prm_pSpl,
                                                                 angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKuroko_target) { //nullptrで渡す事により、_is_created_pManufacture が falseになる
    _pFixedVeloSplManuf = NEW FixedVelocitySplineManufacture(NEW SplineSource(prm_pSpl), prm_angveloRzRyMv);
    _pFixedVeloSplManuf->calculate(); //忘れないように。いずれこのタイプは消す
    _pManufacture = _pFixedVeloSplManuf; //基底メンバーセット。忘れないように。いずれこのタイプは消す

    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
    _ang_rz_mv_begin = prm_pKuroko_target->_ang_rz_mv;
    _ang_ry_mv_begin = prm_pKuroko_target->_ang_ry_mv;
}
void FixedVelocitySplineKurokoLeader::getPointCoord(int prm_point_index, coord& out_x, coord& out_y, coord& out_z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedVeloSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedVelocitySplineKurokoLeader::getPointCoord ポイントのインデックスオーバー。"<<
                                   "補完点数="<<(_pFixedVeloSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    SplineLine* pSpl = _pFixedVeloSplManuf->_sp;
    double dx = _flip_x*pSpl->_x_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_x + _offset_x;
    double dy = _flip_y*pSpl->_y_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_y + _offset_y;
    double dz = _flip_z*pSpl->_z_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_z + _offset_z;
    if (_option == RELATIVE_DIRECTION) {
        if (_is_leading == false) {
            GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
            _sinRzMv_begin = ANG_SIN(pKuroko_target->_ang_rz_mv);
            _cosRzMv_begin = ANG_COS(pKuroko_target->_ang_rz_mv);
            _sinRyMv_begin = ANG_SIN(pKuroko_target->_ang_ry_mv);
            _cosRyMv_begin = ANG_COS(pKuroko_target->_ang_ry_mv);
            if (!_is_fix_start_pos) {
                _x_start = _pActor_target->_x;
                _y_start = _pActor_target->_y;
                _z_start = _pActor_target->_z;
            }
        }
        //    平行移動 ＞ Z軸回転 ＞ Y軸回転 の 平行移動部分 tx,ty,tz
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_x = ((dx * _cosRzMv_begin + dy * -_sinRzMv_begin) *  _cosRyMv_begin + dz * _sinRyMv_begin) + _x_start;
        out_y =  (dx * _sinRzMv_begin + dy *  _cosRzMv_begin)                                          + _y_start;
        out_z = ((dx * _cosRzMv_begin + dy * -_sinRzMv_begin) * -_sinRyMv_begin + dz * _cosRyMv_begin) + _z_start;

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
    } else { //ABSOLUTE_COORD
        //絶対座標ターゲット
        out_x = dx;
        out_y = dy;
        out_z = dz;
    }
}

void FixedVelocitySplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pFixedVeloSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        _ang_rz_mv_begin = _pActor_target->getKuroko()->_ang_rz_mv;
        _ang_ry_mv_begin = _pActor_target->getKuroko()->_ang_ry_mv;
        restart();
    } else {
        throwGgafCriticalException("FixedVelocitySplineKurokoLeader::start Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}
void FixedVelocitySplineKurokoLeader::restart() {
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。

    SplineLine* pSpl = _pFixedVeloSplManuf->_sp;
    double p0x = _flip_x * pSpl->_x_compute[0] * _pFixedVeloSplManuf->_rate_x + _offset_x;
    double p0y = _flip_y * pSpl->_y_compute[0] * _pFixedVeloSplManuf->_rate_y + _offset_y;
    double p0z = _flip_z * pSpl->_z_compute[0] * _pFixedVeloSplManuf->_rate_z + _offset_z;
    if (!_is_fix_start_pos) {
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
                                       0.0, 0.0, 0.0,
                                       p0x, p0y, p0z
                                  );
    } else if (_option == RELATIVE_COORD) {
        _distance_to_begin = UTIL::getDistance(
                                       0.0, 0.0, 0.0,
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
}
void FixedVelocitySplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
        //変わり目
        if (_leadning_fFrames >= _fFrame_of_next) {
            _point_index++;
            if ( _point_index == _pFixedVeloSplManuf->_sp->_rnum) {
                if (_cnt_loop == _max_loop) {
                    //終了
                    _is_leading = false;
                    return;
                } else {
                    //ループ
                    _cnt_loop++;
                    restart();
                    _point_index++;
                }
            }
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            pKuroko_target->turnMvAngTwd(x, y, z,
                                         _pFixedVeloSplManuf->_angveloRzRyMv, 0,
                                         _pFixedVeloSplManuf->_turn_way,
                                         _pFixedVeloSplManuf->_turn_optimize);
            if (_point_index == 0) {
                //最初の必然ブレイク、始点へ行く
                //始点までに必要なフレーム数取得
                _fFrame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit);
            } else {
                //始点以外の場合次の補完点までに必要なフレーム数を更新
                _fFrame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit) +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
             }
        }
        //キャラの速度が1000ならば、_leadning_fFrames ++;
        //キャラの速度が2000ならば  _leadning_fFrames += 2.0;
        //キャラの速度が500ならば、 _leadning_fFrames += 0.5
//        _leadning_fFrames += (1.0*pKuroko_target->_velo_mv / LEN_UNIT);
        _leadning_fFrames += (pKuroko_target->_velo_mv * (1.0 / LEN_UNIT));
    }
}

FixedVelocitySplineKurokoLeader::~FixedVelocitySplineKurokoLeader() {
}
