#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prm_pKurokoA_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKurokoA_target) {
    _pFixedVeloSplManuf = (FixedVelocitySplineManufacture*)prm_pManufacture;
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
}

FixedVelocitySplineKurokoLeader::FixedVelocitySplineKurokoLeader(GgafDxKurokoA* prm_pKurokoA_target,
                                                                 SplineLine* prmpSpl,
                                                                 angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKurokoA_target) { //nullptrで渡す事により、_is_created_pManufacture が falseになる
    _pFixedVeloSplManuf = NEW FixedVelocitySplineManufacture(NEW SplineSource(prmpSpl), prm_angveloRzRyMv);
    _pFixedVeloSplManuf->calculate(); //忘れないように。いずれこのタイプは消す
    _pManufacture = _pFixedVeloSplManuf; //基底メンバーセット。忘れないように。いずれこのタイプは消す

    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = -1;//最初は始点[0]に向かうので、始点前の-1になる。
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
}
void FixedVelocitySplineKurokoLeader::getPointCoord(int prm_point_index, coord& out_X, coord& out_Y, coord& out_Z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pFixedVeloSplManuf->_sp->_rnum) {
        throwGgafCriticalException("FixedVelocitySplineKurokoLeader::getPointCoord ポイントのインデックスオーバー。"<<
                                   "補完点数="<<(_pFixedVeloSplManuf->_sp->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif


    SplineLine* pSpl = _pFixedVeloSplManuf->_sp;
    double dx = _flip_X*pSpl->_X_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_X + _offset_X;
    double dy = _flip_Y*pSpl->_Y_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_Y + _offset_Y;
    double dz = _flip_Z*pSpl->_Z_compute[prm_point_index]*_pFixedVeloSplManuf->_rate_Z + _offset_Z;
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
        //    平行移動 ＞ Z軸回転 ＞ Y軸回転 の 平行移動部分 tx,ty,tz
        //    | cosRz*cosRy                            , sinRz                , cosRz*-sinRy                            , 0 |
        //    | -sinRz*cosRy                           , cosRz                , -sinRz*-sinRy                           , 0 |
        //    | sinRy                                  , 0                    , cosRy                                   , 0 |
        //    | (dx*cosRz + dy*-sinRz)*cosRy + dz*sinRy, (dx*sinRz + dy*cosRz), (dx*cosRz + dy*-sinRz)*-sinRy + dz*cosRy, 1 |
        out_X = ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) *  _COS_RyMv_begin + dz * _SIN_RyMv_begin) + _X_begin;
        out_Y =  (dx * _SIN_RzMv_begin + dy *  _COS_RzMv_begin)                                            + _Y_begin;
        out_Z = ((dx * _COS_RzMv_begin + dy * -_SIN_RzMv_begin) * -_SIN_RyMv_begin + dz * _COS_RyMv_begin) + _Z_begin;

    } else if (_option == RELATIVE_COORD) {
        //相対座標ターゲット
        out_X = dx + _X_begin;
        out_Y = dy + _Y_begin;
        out_Z = dz + _Z_begin;
    } else { //ABSOLUTE_COORD
        //絶対座標ターゲット
        out_X = dx;
        out_Y = dy;
        out_Z = dz;
    }
}

void FixedVelocitySplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pFixedVeloSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
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
    double P0X = _flip_X * pSpl->_X_compute[0] * _pFixedVeloSplManuf->_rate_X + _offset_X;
    double P0Y = _flip_Y * pSpl->_Y_compute[0] * _pFixedVeloSplManuf->_rate_Y + _offset_Y;
    double P0Z = _flip_Z * pSpl->_Z_compute[0] * _pFixedVeloSplManuf->_rate_Z + _offset_Z;
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
                                       0.0, 0.0, 0.0,
                                       P0X, P0Y, P0Z
                                  );
    } else if (_option == RELATIVE_COORD) {
        _distance_to_begin = UTIL::getDistance(
                                       0.0, 0.0, 0.0,
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
}
void FixedVelocitySplineKurokoLeader::behave() {
    if (_is_leading) {
        GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
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

            coord X, Y, Z;
            getPointCoord(_point_index, X, Y, Z);
            pKurokoA_target->turnMvAngTwd(X, Y, Z,
                                          _pFixedVeloSplManuf->_angveloRzRyMv, 0,
                                          _pFixedVeloSplManuf->_turn_way,
                                          _pFixedVeloSplManuf->_turn_optimize);
            if (_point_index == 0) {
                //最初の必然ブレイク、始点へ行く
                //始点までに必要なフレーム数取得
                _fFrame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_veloMvUnit);
            } else {

                //始点以外の場合次の補完点までに必要なフレーム数を更新
                _fFrame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_veloMvUnit) +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
             }
        }

        //キャラの速度が1000ならば、_leadning_fFrames ++;
        //キャラの速度が2000ならば  _leadning_fFrames += 2.0;
        //キャラの速度が500ならば、 _leadning_fFrames += 0.5
        _leadning_fFrames += (1.0*pKurokoA_target->_veloMv / LEN_UNIT);
    }
}

FixedVelocitySplineKurokoLeader::~FixedVelocitySplineKurokoLeader() {
}
