#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"

using namespace GgafDx;

VehicleLeader::VehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::GeometricActor* prm_pActor_target) :
        GgafCore::Object() {
    _pManufacture = prm_pManufacture;
    if (!_pManufacture->_is_calculated) {
        _pManufacture->calculate();
    }
    _pActor_target = prm_pActor_target;
    _option = ABSOLUTE_COORD;
    _x_start_in_loop = 0;
    _y_start_in_loop = 0;
    _z_start_in_loop = 0;
    _offset_x = 0;
    _offset_y = 0;
    _offset_z = 0;
    _flip_x = 1;
    _flip_y = 1;
    _flip_z = 1;
    _sinRx_begin = 0.0f;
    _cosRx_begin = 0.0f;
    _sinRz_begin = 0.0f;
    _cosRz_begin = 0.0f;
    _sinRy_begin = 0.0f;
    _cosRy_begin = 0.0f;

    _was_started = false;
    _is_leading = false;
    _distance_to_begin = 0;
    _cnt_loop = 0;
    _max_loop = 1;
    _is_force_start_pos = false;
    _is_fix_pos = false;
    _is_force_start_ang = false;
//    _is_loop_ang_by_face = true;
    _turn_smooth = false;
}

void VehicleLeader::getPointCoord(int prm_point_index, coord& out_x, coord& out_y, coord& out_z) {
#ifdef MY_DEBUG
    if (prm_point_index >= _pManufacture->_pCurve->_rnum) {
        throwCriticalException("ポイントのインデックスオーバー。"
                                   "補完点数="<<(_pManufacture->_pCurve->_rnum)<<" prm_point_index="<<prm_point_index);
    }
#endif
    const CurveSource* const pCurve = _pManufacture->_pCurve;
    const double dx = _flip_x*pCurve->_x_compute[prm_point_index]*_pManufacture->_rate_x + _offset_x;
    const double dy = _flip_y*pCurve->_y_compute[prm_point_index]*_pManufacture->_rate_y + _offset_y;
    const double dz = _flip_z*pCurve->_z_compute[prm_point_index]*_pManufacture->_rate_z + _offset_z;
    //次の補間点（or制御点)に移動方角を向ける
    if (_option == RELATIVE_COORD_DIRECTION) {
        if (_is_leading) {
            //移動車両さんが先導中(leading中)
            //startされているので、未来の補間点座標が確定している
            //    平行移動 ＞ X軸回転 ＞ Z軸回転 ＞ Y軸回転
            // | cosRz*cosRy                                                                       sinRz                                       cosRz*-sinRy                                                                        0 |
            // | cosRx*-sinRz*cosRy + sinRx*sinRy                                                  cosRx*cosRz                                 cosRx*-sinRz*-sinRy + sinRx*cosRy                                                   0 |
            // | -sinRx*-sinRz*cosRy + cosRx*sinRy                                                 -sinRx*cosRz                                -sinRx*-sinRz*-sinRy + cosRx*cosRy                                                  0 |
            // | (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*cosRy + ((dy*sinRx + dz*cosRx))*sinRy  (dx*sinRz + (dy*cosRx + dz*-sinRx)*cosRz)   (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*-sinRy + ((dy*sinRx + dz*cosRx))*cosRy   1 |
            const double dx_cosRz_begin = dx*_cosRz_begin;
            const double dy_cosRx_begin = dy*_cosRx_begin;
            const double dz_sinRx_begin = dz*_sinRx_begin;
            const double dy_sinRx_begin = dy*_sinRx_begin;
            const double dz_cosRx_begin = dz*_cosRx_begin;
            out_x = ((dx_cosRz_begin  + (dy_cosRx_begin + -dz_sinRx_begin)*-_sinRz_begin)* _cosRy_begin + ((dy_sinRx_begin + dz_cosRx_begin))*_sinRy_begin ) + _x_start_in_loop;
            out_y = ((dx*_sinRz_begin + (dy_cosRx_begin + -dz_sinRx_begin)* _cosRz_begin)                                                                  ) + _y_start_in_loop;
            out_z = ((dx_cosRz_begin  + (dy_cosRx_begin + -dz_sinRx_begin)*-_sinRz_begin)*-_sinRy_begin + ((dy_sinRx_begin + dz_cosRx_begin))*_cosRy_begin ) + _z_start_in_loop;
        } else {
            //移動車両さんが先導していない(not leading 中)
            //まだ start されていないので、未来の補間点座標が未確定
            //この場合、仮に今ココで start された場合の座標を計算して返す
            const double sinRx_now = ANG_SIN(_pActor_target->_rx);
            const double cosRx_now = ANG_COS(_pActor_target->_rx);
            const double sinRz_now = ANG_SIN(_pActor_target->_rz);
            const double cosRz_now = ANG_COS(_pActor_target->_rz);
            const double sinRy_now = ANG_SIN(_pActor_target->_ry);
            const double cosRy_now = ANG_COS(_pActor_target->_ry);
            const double dx_cosRz_now = dx*cosRz_now;
            const double dy_cosRx_now = dy*cosRx_now;
            const double dz_sinRx_now = dz*sinRx_now;
            const double dy_sinRx_now = dy*sinRx_now;
            const double dz_cosRx_now = dz*cosRx_now;
            //    平行移動 ＞ X軸回転 ＞ Z軸回転 ＞ Y軸回転
            if (_is_force_start_pos) {
                out_x = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)* cosRy_now + ((dy_sinRx_now + dz_cosRx_now))*sinRy_now ) + 0;
                out_y = ((dx*sinRz_now + (dy_cosRx_now + -dz_sinRx_now)* cosRz_now)                                                        ) + 0;
                out_z = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)*-sinRy_now + ((dy_sinRx_now + dz_cosRx_now))*cosRy_now ) + 0;
            } else {
                out_x = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)* cosRy_now + ((dy_sinRx_now + dz_cosRx_now))*sinRy_now ) + _pActor_target->_x;
                out_y = ((dx*sinRz_now + (dy_cosRx_now + -dz_sinRx_now)* cosRz_now)                                                        ) + _pActor_target->_y;
                out_z = ((dx_cosRz_now + (dy_cosRx_now + -dz_sinRx_now)*-sinRz_now)*-sinRy_now + ((dy_sinRx_now + dz_cosRx_now))*cosRy_now ) + _pActor_target->_z;
            }


        }
    } else if (_option == RELATIVE_COORD) {
        //相対座標ターゲット
        if (_is_leading) {
            //移動車両さんが先導中(leading中)
            out_x = dx + _x_start_in_loop;
            out_y = dy + _y_start_in_loop;
            out_z = dz + _z_start_in_loop;
        } else {
            //移動車両さんが先導していない(not leading 中)
            if (_is_force_start_pos) {
                out_x = dx + 0;
                out_y = dy + 0;
                out_z = dz + 0;
            } else {
                out_x = dx + _pActor_target->_x;
                out_y = dy + _pActor_target->_y;
                out_z = dz + _pActor_target->_z;
            }
        }
    } else { //RELATIVE_COORD_DIRECTION
        //絶対座標ターゲット
        out_x = dx;
        out_y = dy;
        out_z = dz;
    }
}

void VehicleLeader::restart() {
    const CurveSource* const pCurve = _pManufacture->_pCurve;
    const double p0x = _flip_x * pCurve->_x_compute[0] * _pManufacture->_rate_x + _offset_x;
    const double p0y = _flip_y * pCurve->_y_compute[0] * _pManufacture->_rate_y + _offset_y;
    const double p0z = _flip_z * pCurve->_z_compute[0] * _pManufacture->_rate_z + _offset_z;
//    if (_cnt_loop >= 2) {
//        //２周目以降は setStartPosition() が設定されていても、効力はなくなる。
//        _is_force_start_pos = false;
//        _is_force_start_ang = false;
//    }
    if (_is_fix_pos) {
        //開始座標は何ループしても固定。
    } else {
        if (_is_force_start_pos) {
            //開始座標(_x_start_in_loop, _y_start_in_loop, _z_start_in_loop)は、
            //別途 setStartPosition() により設定済み
            _is_force_start_pos = false;
        } else {
            if (_cnt_loop == 1) {
                //１週目は正に今の座標が開始座標
                _x_start_in_loop = _pActor_target->_x;
                _y_start_in_loop = _pActor_target->_y;
                _z_start_in_loop = _pActor_target->_z;
            } else {
                //２週目以降は、開始座標は、前回の論理最終座標が、開始座標
                coord end_x, end_y, end_z;
                getPointCoord(getPointNum()-1, end_x, end_y, end_z);
                _x_start_in_loop = end_x;
                _y_start_in_loop = end_y;
                _z_start_in_loop = end_z;
            }
        }
    }

    if (_is_force_start_ang) {
        //_rz_mv_start, _ry_mv_start、は
        //別途 setStartAngle() により設定済みの場合は、
        //アクターの今の向きに関係なく、設定済みの向きとなる
        _is_force_start_ang = false;
    } else {
        if (_cnt_loop == 1) {
//            if (_is_loop_ang_by_face) {
//                //setLoopAngleByFaceAng() 設定済みの場合（デフォルト)
                //１週目はアクターが正に今向いている方向が開始移動方向
                angle rx_mv_start = _pActor_target->_rx;
                angle rz_mv_start = _pActor_target->_rz;
                angle ry_mv_start = _pActor_target->_ry;
                _sinRx_begin = ANG_SIN(rx_mv_start);
                _cosRx_begin = ANG_COS(rx_mv_start);
                _sinRz_begin = ANG_SIN(rz_mv_start);
                _cosRz_begin = ANG_COS(rz_mv_start);
                _sinRy_begin = ANG_SIN(ry_mv_start);
                _cosRy_begin = ANG_COS(ry_mv_start);
//            } else {
//                //setLoopAngleByMvAng() 設定済みの場合
//                //１週目はアクターの移動方向が開始移動方向
//                GgafDx::LocoVehicle* pActorLocoVehicle = _pActor_target->getLocoVehicle();
//                angle rx_mv_start = D0ANG;
//                angle rz_mv_start = pActorLocoVehicle->_rz_mv;
//                angle ry_mv_start = pActorLocoVehicle->_ry_mv;
//                _sinRx_begin = ANG_SIN(rx_mv_start);
//                _cosRx_begin = ANG_COS(rx_mv_start);
//                _sinRz_begin = ANG_SIN(rz_mv_start);
//                _cosRz_begin = ANG_COS(rz_mv_start);
//                _sinRy_begin = ANG_SIN(ry_mv_start);
//                _cosRy_begin = ANG_COS(ry_mv_start);
//            }
        } else {
            //２週目以降は、そのまま;
        }
    }

//    if (_option == RELATIVE_COORD_DIRECTION) {
//        _distance_to_begin = UTIL::getDistance(0.0, 0.0, 0.0,
//                                               p0x, p0y, p0z );
//    } else if (_option == RELATIVE_COORD) {
//        _distance_to_begin = UTIL::getDistance(0.0, 0.0, 0.0,
//                                               p0x, p0y, p0z );
//    } else { //ABSOLUTE_COORD
//        _distance_to_begin = UTIL::getDistance(
//                                (double)(_pActor_target->_x),
//                                (double)(_pActor_target->_y),
//                                (double)(_pActor_target->_z),
//                                p0x, p0y, p0z
//                             );
//   }
    if (_option == ABSOLUTE_COORD) {
        _distance_to_begin = UTIL::getDistance(
                                (double)(_pActor_target->_x),
                                (double)(_pActor_target->_y),
                                (double)(_pActor_target->_z),
                                p0x, p0y, p0z
                             );
    } else {
        _distance_to_begin = 0;
    }
}

void VehicleLeader::setManufacture(CurveManufacture* prm_pManufacture) {
    _pManufacture = prm_pManufacture;
    _pActor_target = nullptr;
    _option = ABSOLUTE_COORD;
    _offset_x = 0;
    _offset_y = 0;
    _offset_z = 0;
    _flip_x = 1;
    _flip_y = 1;
    _flip_z = 1;
    _was_started = false;
    _is_leading = false;
}

void VehicleLeader::adjustCoordOffset(coord prm_offset_x, coord prm_offset_y, coord prm_offset_z) {
    _offset_x = prm_offset_x;
    _offset_y = prm_offset_y;
    _offset_z = prm_offset_z;
}

void VehicleLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pManufacture) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        restart();
    } else {
        throwCriticalException("Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}

void VehicleLeader::stop() {
    _is_leading = false;
}

void VehicleLeader::setAbsoluteBeginCoord() {
    VehicleLeader::getPointCoord(0, _pActor_target->_x, _pActor_target->_y, _pActor_target->_z);
}

coord VehicleLeader::getSegmentDistance(int prm_index) {
#ifdef MY_DEBUG
    if (prm_index < 0 || prm_index > (_pManufacture->_pCurve->_rnum -1)) {
        throwCriticalException("prm_index="<<prm_index<<" は、範囲外です._pActor_target="<< _pActor_target <<"["<< _pActor_target->getName() <<"]");
    }
#endif
    if (prm_index == 0) {
        return _distance_to_begin;
    } else {
        return _pManufacture->_paDistance_to[prm_index];
    }
}

coord VehicleLeader::getTotalDistance() {
    return _pManufacture->_total_distance + _distance_to_begin;
}

int VehicleLeader::getPointNum() {
    return _pManufacture->_pCurve->_rnum;
}

void VehicleLeader::setStartAngle(angle prm_rx, angle prm_ry, angle prm_rz) {
    _is_force_start_ang = true;
    angle rx_mv_start = UTIL::simplifyAng(prm_rx);
    angle rz_mv_start = UTIL::simplifyAng(prm_rz);
    angle ry_mv_start = UTIL::simplifyAng(prm_ry);
    _sinRx_begin = ANG_SIN(rx_mv_start);
    _cosRx_begin = ANG_COS(rx_mv_start);
    _sinRz_begin = ANG_SIN(rz_mv_start);
    _cosRz_begin = ANG_COS(rz_mv_start);
    _sinRy_begin = ANG_SIN(ry_mv_start);
    _cosRy_begin = ANG_COS(ry_mv_start);
}

VehicleLeader::~VehicleLeader() {
//    if (_is_created_pManufacture) {
//        CurveSource* pCurveSrc = _pManufacture->_pCurveSrc;
//        GGAF_DELETE(pCurveSrc);
//        GGAF_DELETE(_pManufacture);
//    }
}
