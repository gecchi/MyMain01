#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"

#include "jp/ggaf/dx/actor/supporter/CoordVehicleAssistant.h"
#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;
// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_x,_y,_z)にそれぞれの移動増分が
// 加算される。

CoordVehicle::CoordVehicle(GeometricActor* prm_pActor)  : ActorVehicle(prm_pActor) {
    _pAsstMv = nullptr;
    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _velo_x = 0;
    //X軸方向移動速度上限
    _top_velo_x = INT_MAX;
    //X軸方向移動速度下限
    _bottom_velo_x = INT_MIN;
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acce_x = 0;
    _top_acce_x = INT_MAX;
    _bottom_acce_x = INT_MIN;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _velo_y = 0;
    //Y軸方向移動速度上限
    _top_velo_y = INT_MAX;
    //Y軸方向移動速度下限
    _bottom_velo_y = INT_MIN;
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acce_y = 0;

    _top_acce_y = INT_MAX;
    _bottom_acce_y = INT_MIN;

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _velo_z = 0;
    //Z軸方向移動速度上限
    _top_velo_z = INT_MAX;
    //Z軸方向移動速度下限
    _bottom_velo_z = INT_MIN;
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acce_z = 0;
    _top_acce_z = INT_MAX;
    _bottom_acce_z = INT_MIN;

    _grv_mv_target_x = 0;
    _grv_mv_target_y = 0;
    _grv_mv_target_z = 0;
    _grv_mv_pActor_target = nullptr;
    _grv_mv_max_velo = 1000;
    _grv_mv_acce = 1000;
    _grv_mv_stop_renge = 1000;
    _grv_mv_flg = false;
}

CoordVehicleAssistant* CoordVehicle::asst() {
    return _pAsstMv ? _pAsstMv : _pAsstMv = NEW CoordVehicleAssistant(this);
}

void CoordVehicle::behave() {
    if (_pAsstMv) {
        _pAsstMv->behave();
    }

    if(_grv_mv_flg) {
        coord dx, dy, dz;
        if (_grv_mv_pActor_target) {
            //_grv_mv_pActor_target 指定時の _grv_mv_target_(xyz) は、_grv_mv_pActor_targetからの補正相対座標
            dx = (_grv_mv_pActor_target->_x + _grv_mv_target_x) - _pActor->_x;
            dy = (_grv_mv_pActor_target->_y + _grv_mv_target_y) - _pActor->_y;
            dz = (_grv_mv_pActor_target->_z + _grv_mv_target_z) - _pActor->_z;
        } else {
            //_grv_mv_pActor_target 未定時の _grv_mv_target_(xyz) は、絶対座標
            dx = _grv_mv_target_x - _pActor->_x;
            dy = _grv_mv_target_y - _pActor->_y;
            dz = _grv_mv_target_z - _pActor->_z;
        }
        const coord dx_abs = ABS(dx);
        const coord dy_abs = ABS(dy);
        const coord dz_abs = ABS(dz);
        const coord dmax = MAX3(dx_abs, dy_abs, dz_abs);//距離簡易計算
        if (dmax > _grv_mv_max_velo) {
            double rr = 1.0*_grv_mv_max_velo / dmax;
            dx *= rr;
            dy *= rr;
            dz *= rr;
        }
        const double r_acce = 1.7*_grv_mv_acce / dmax;
        acce x_acce = r_acce * dx_abs;
        acce y_acce = r_acce * dy_abs;
        acce z_acce = r_acce * dz_abs;
        if (x_acce > _grv_mv_acce) {
            x_acce = _grv_mv_acce;
        }
        if (y_acce > _grv_mv_acce) {
            y_acce = _grv_mv_acce;
        }
        if (z_acce > _grv_mv_acce) {
            z_acce = _grv_mv_acce;
        }

        double inv_grv_mv_stop_renge = 1.0 / _grv_mv_stop_renge;
        const velo last_velo_x = _velo_x;
        const velo new_velo_x = _grv_mv_max_velo * (dx * inv_grv_mv_stop_renge);
        if (last_velo_x - x_acce <= new_velo_x &&
                                        new_velo_x <= last_velo_x + x_acce) {
            _velo_x = new_velo_x;
        } else {
            if (last_velo_x - x_acce > new_velo_x) {
                _velo_x = last_velo_x - x_acce;
            } else if (new_velo_x > last_velo_x + x_acce) {
                _velo_x = last_velo_x + x_acce;
            }
        }

        const velo last_velo_y = _velo_y;
        const velo new_velo_y = _grv_mv_max_velo * (dy * inv_grv_mv_stop_renge);
        if (last_velo_y - y_acce <= new_velo_y &&
                                        new_velo_y <= last_velo_y + y_acce) {
            _velo_y = new_velo_y;
        } else {
            if (last_velo_y - y_acce > new_velo_y) {
                _velo_y = last_velo_y - y_acce;
            } else if (new_velo_y > last_velo_y + y_acce) {
                _velo_y = last_velo_y + y_acce;
            }
        }

        const velo last_velo_z = _velo_z;
        const velo new_velo_z = _grv_mv_max_velo * (dz * inv_grv_mv_stop_renge);
        if (last_velo_z - z_acce <= new_velo_z &&
                                        new_velo_z <= last_velo_z + z_acce) {
            _velo_z = new_velo_z;
        } else {
            if (last_velo_z - z_acce > new_velo_z) {
                _velo_z = last_velo_z - z_acce;
            } else if (new_velo_z > last_velo_z + z_acce) {
                _velo_z = last_velo_z + z_acce;
            }
        }
    }


//    double vxvx = in_x * in_x;
//    double vyvy = in_y * in_y;
//    double vzvz = in_z * in_z;
//    double t = 1.0/sqrt(vzvz+vyvy+vxvx);
//    out_x = t*in_x;
//    out_y = t*in_y;
//    out_z = t*in_z;


    _velo_x += _acce_x;
    if (_velo_x > _top_velo_x) {
        _velo_x = _top_velo_x;
    } else if (_velo_x < _bottom_velo_x) {
        _velo_x = _bottom_velo_x;
    }
    _velo_y += _acce_y;
    if (_velo_y > _top_velo_y) {
        _velo_y = _top_velo_y;
    } else if (_velo_y < _bottom_velo_y) {
        _velo_y = _bottom_velo_y;
    }
    _velo_z += _acce_z;
    if (_velo_z > _top_velo_z) {
        _velo_z = _top_velo_z;
    } else if (_velo_z < _bottom_velo_z) {
        _velo_z = _bottom_velo_z;
    }



    //Actorに反映
    _pActor->_x += _velo_x;
    _pActor->_y += _velo_y;
    _pActor->_z += _velo_z;
}

int CoordVehicle::dot(int prm_vX, int prm_vY, int prm_vZ) {
    return (prm_vX * _velo_x) + (prm_vY *_velo_y) + (prm_vZ*_velo_z);
}

void CoordVehicle::setVeloX(velo prm_velo_x) {
    if (prm_velo_x > _top_velo_x) {
        _velo_x = _top_velo_x;
    } else if (prm_velo_x < _bottom_velo_x) {
        _velo_x = _bottom_velo_x;
    } else {
        _velo_x = prm_velo_x;
    }
}

void CoordVehicle::addVeloX(velo prm_velo_x) {
    _velo_x += prm_velo_x;
    if (_velo_x > _top_velo_x) {
        _velo_x = _top_velo_x;
    } else if (_velo_x < _bottom_velo_x) {
        _velo_x = _bottom_velo_x;
    }
}

void CoordVehicle::forceVeloXRange(velo prm_velo_x01, velo prm_velo_x02) {
    if (prm_velo_x01 < prm_velo_x02) {
        _top_velo_x = prm_velo_x02;
        _bottom_velo_x = prm_velo_x01;
    } else {
        _top_velo_x = prm_velo_x01;
        _bottom_velo_x = prm_velo_x02;
    }
    setVeloX(_velo_x); //再設定して範囲内に補正
}

void CoordVehicle::setAcceX(acce prm_acce_x) {
    if (prm_acce_x > _top_acce_x) {
        _acce_x = _top_acce_x;
    } else if (prm_acce_x < _bottom_acce_x) {
        _acce_x = _bottom_acce_x;
    } else {
        _acce_x = prm_acce_x;
    }
}

void CoordVehicle::addAcceX(acce prm_acce_x) {
    setAcceX(_acce_x + prm_acce_x);
}

void CoordVehicle::forceAcceXRange(acce prm_acce_x01, acce prm_acce_x02) {
    if (prm_acce_x01 < prm_acce_x02) {
        _top_acce_x = prm_acce_x02;
        _bottom_acce_x = prm_acce_x01;
    } else {
        _top_acce_x = prm_acce_x01;
        _bottom_acce_x = prm_acce_x02;
    }
    setAcceX(_acce_x); //再設定して範囲内に補正
}


void CoordVehicle::setVeloY(velo prm_velo_y) {
    if (prm_velo_y > _top_velo_y) {
        _velo_y = _top_velo_y;
    } else if (prm_velo_y < _bottom_velo_y) {
        _velo_y = _bottom_velo_y;
    } else {
        _velo_y = prm_velo_y;
    }
}

void CoordVehicle::addVeloY(velo prm_velo_y) {
    _velo_y += prm_velo_y;
    if (_velo_y > _top_velo_y) {
        _velo_y = _top_velo_y;
    } else if (_velo_y < _bottom_velo_y) {
        _velo_y = _bottom_velo_y;
    }
}

void CoordVehicle::forceVeloYRange(velo prm_velo_y01, velo prm_velo_y02) {
    if (prm_velo_y01 < prm_velo_y02) {
        _top_velo_y = prm_velo_y02;
        _bottom_velo_y = prm_velo_y01;
    } else {
        _top_velo_y = prm_velo_y01;
        _bottom_velo_y = prm_velo_y02;
    }
    setVeloY(_velo_y); //再設定して範囲内に補正
}

void CoordVehicle::setAcceY(acce prm_acce_y) {
    if (prm_acce_y > _top_acce_y) {
        _acce_y = _top_acce_y;
    } else if (prm_acce_y < _bottom_acce_y) {
        _acce_y = _bottom_acce_y;
    } else {
        _acce_y = prm_acce_y;
    }
}

void CoordVehicle::addAcceY(acce prm_acce_y) {
    setAcceY(_acce_y + prm_acce_y);
}

void CoordVehicle::forceAcceYRange(acce prm_acce_y01, acce prm_acce_y02) {
    if (prm_acce_y01 < prm_acce_y02) {
        _top_acce_y = prm_acce_y02;
        _bottom_acce_y = prm_acce_y01;
    } else {
        _top_acce_y = prm_acce_y01;
        _bottom_acce_y = prm_acce_y02;
    }
    setAcceY(_acce_y); //再設定して範囲内に補正
}

void CoordVehicle::setVeloZ(velo prm_velo_z) {
    if (prm_velo_z > _top_velo_z) {
        _velo_z = _top_velo_z;
    } else if (prm_velo_z < _bottom_velo_z) {
        _velo_z = _bottom_velo_z;
    } else {
        _velo_z = prm_velo_z;
    }
}

void CoordVehicle::addVeloZ(velo prm_velo_z) {
    _velo_z += prm_velo_z;
    if (_velo_z > _top_velo_z) {
        _velo_z = _top_velo_z;
    } else if (_velo_z < _bottom_velo_z) {
        _velo_z = _bottom_velo_z;
    }
}

void CoordVehicle::forceVeloZRange(velo prm_velo_z01, velo prm_velo_z02) {
    if (prm_velo_z01 < prm_velo_z02) {
        _top_velo_z = prm_velo_z02;
        _bottom_velo_z = prm_velo_z01;
    } else {
        _top_velo_z = prm_velo_z01;
        _bottom_velo_z = prm_velo_z02;
    }
    setVeloZ(_velo_z); //再設定して範囲内に補正
}

void CoordVehicle::setAcceZ(acce prm_acce_z) {
    if (prm_acce_z > _top_acce_z) {
        _acce_z = _top_acce_z;
    } else if (prm_acce_z < _bottom_acce_z) {
        _acce_z = _bottom_acce_z;
    } else {
        _acce_z = prm_acce_z;
    }
}

void CoordVehicle::addAcceZ(acce prm_acce_z) {
    setAcceZ(_acce_z + prm_acce_z);
}

void CoordVehicle::forceAcceZRange(acce prm_acce_z01, acce prm_acce_z02) {
    if (prm_acce_z01 < prm_acce_z02) {
        _top_acce_z = prm_acce_z02;
        _bottom_acce_z = prm_acce_z01;
    } else {
        _top_acce_z = prm_acce_z01;
        _bottom_acce_z = prm_acce_z02;
    }
    setAcceZ(_acce_z); //再設定して範囲内に補正
}

void CoordVehicle::forceVeloXYZRange(velo prm_velo_vxyz_mv01, velo prm_velo_vxyz_mv02) {
    if (prm_velo_vxyz_mv01 < prm_velo_vxyz_mv02) {
        _top_velo_x    = _top_velo_y    = _top_velo_z    = prm_velo_vxyz_mv02;
        _bottom_velo_x = _bottom_velo_y = _bottom_velo_z = prm_velo_vxyz_mv01;
    } else {
        _top_velo_x    = _top_velo_y    = _top_velo_z    = prm_velo_vxyz_mv01;
        _bottom_velo_x = _bottom_velo_y = _bottom_velo_z = prm_velo_vxyz_mv02;
    }
    //再設定して範囲内に補正
    setVeloX(_velo_x);
    setVeloY(_velo_y);
    setVeloZ(_velo_z);
}

void CoordVehicle::forceAcceXYZRange(acce prm_acce_vxyz_mv01, acce prm_acce_vxyz_mv02) {
    if (prm_acce_vxyz_mv01 < prm_acce_vxyz_mv02) {
        _top_acce_x    = _top_acce_y    = _top_acce_z    = prm_acce_vxyz_mv02;
        _bottom_acce_x = _bottom_acce_y = _bottom_acce_z = prm_acce_vxyz_mv01;
    } else {
        _top_acce_x    = _top_acce_y     = _top_acce_z   = prm_acce_vxyz_mv01;
        _bottom_acce_x =  _bottom_acce_y =_bottom_acce_z = prm_acce_vxyz_mv02;
    }
    //再設定して範囲内に補正
    setAcceX(_acce_x);
    setAcceY(_acce_y);
    setAcceZ(_acce_z);
}

void CoordVehicle::setVeloXYZ(velo prm_velo_x, velo prm_velo_y, velo prm_velo_z) {
    if (prm_velo_x > _top_velo_x) {
        _velo_x = _top_velo_x;
    } else if (prm_velo_x < _bottom_velo_x) {
        _velo_x = _bottom_velo_x;
    } else {
        _velo_x = prm_velo_x;
    }
    if (prm_velo_y > _top_velo_y) {
        _velo_y = _top_velo_y;
    } else if (prm_velo_y < _bottom_velo_y) {
        _velo_y = _bottom_velo_y;
    } else {
        _velo_y = prm_velo_y;
    }
    if (prm_velo_z > _top_velo_z) {
        _velo_z = _top_velo_z;
    } else if (prm_velo_z < _bottom_velo_z) {
        _velo_z = _bottom_velo_z;
    } else {
        _velo_z = prm_velo_z;
    }
}

void CoordVehicle::setVeloXYZTwd(angle prm_rz, angle prm_ry, velo prm_velo) {
    double vx, vy, vz;
    UTIL::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    setVeloXYZ(vx*prm_velo, vy*prm_velo, vz*prm_velo);
}

void CoordVehicle::setVeloXYZTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo) {
    double vx, vy, vz;
    UTIL::getNormalizedVector(prm_tx - _pActor->_x,
                              prm_ty - _pActor->_y,
                              prm_tz - _pActor->_z,
                              vx, vy, vz);
    setVeloXYZ(vx*prm_velo, vy*prm_velo, vz*prm_velo);
}

void CoordVehicle::setAcceXYZ(acce prm_acce_x, acce prm_acce_y, acce prm_acce_z) {
    if (prm_acce_x > _top_acce_x) {
        _acce_x = _top_acce_x;
    } else if (prm_acce_x < _bottom_acce_x) {
        _acce_x = _bottom_acce_x;
    } else {
        _acce_x = prm_acce_x;
    }
    if (prm_acce_y > _top_acce_y) {
        _acce_y = _top_acce_y;
    } else if (prm_acce_y < _bottom_acce_y) {
        _acce_y = _bottom_acce_y;
    } else {
        _acce_y = prm_acce_y;
    }
    if (prm_acce_z > _top_acce_z) {
        _acce_z = _top_acce_z;
    } else if (prm_acce_z < _bottom_acce_z) {
        _acce_z = _bottom_acce_z;
    } else {
        _acce_z = prm_acce_z;
    }
}

coord CoordVehicle::setAcceXByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_x, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setAcceX(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_x + prm_target_velo) * prm_target_frames) / 2 ;
}

coord CoordVehicle::setAcceYByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_y, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setAcceY(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_y + prm_target_velo) * prm_target_frames) / 2 ;
}

coord CoordVehicle::setAcceZByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_z, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setAcceZ(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_z + prm_target_velo) * prm_target_frames) / 2 ;
}

void CoordVehicle::execGravitationMvSequenceTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                              velo prm_max_velo,
                                              acce prm_acce,
                                              coord prm_stop_renge ) {
    _grv_mv_target_x = prm_tx;
    _grv_mv_target_y = prm_ty;
    _grv_mv_target_z = prm_tz;
    _grv_mv_pActor_target = nullptr;
    _grv_mv_max_velo = prm_max_velo;
    _grv_mv_acce = prm_acce;
    _grv_mv_stop_renge = prm_stop_renge;
    _grv_mv_flg = true;

    forceVeloXRange(-prm_max_velo, prm_max_velo);
    forceVeloYRange(-prm_max_velo, prm_max_velo);
    forceVeloZRange(-prm_max_velo, prm_max_velo);
}

void CoordVehicle::execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
                                              velo prm_max_velo,
                                              acce prm_acce,
                                              coord prm_stop_renge ) {
    _grv_mv_target_x = 0;
    _grv_mv_target_y = 0;
    _grv_mv_target_z = 0;
    _grv_mv_pActor_target = prm_pActor_target;
    _grv_mv_max_velo = prm_max_velo;
    _grv_mv_acce = prm_acce;
    _grv_mv_stop_renge = prm_stop_renge;
    _grv_mv_flg = true;

    forceVeloXRange(-prm_max_velo, prm_max_velo);
    forceVeloYRange(-prm_max_velo, prm_max_velo);
    forceVeloZRange(-prm_max_velo, prm_max_velo);
}

void CoordVehicle::execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
                                              coord prm_local_offset_tx, coord prm_local_offset_ty, coord prm_local_offset_tz,
                                              velo prm_max_velo,
                                              acce prm_acce,
                                              coord prm_stop_renge) {
    _grv_mv_target_x = prm_local_offset_tx;
    _grv_mv_target_y = prm_local_offset_ty;
    _grv_mv_target_z = prm_local_offset_tz;
    _grv_mv_pActor_target = prm_pActor_target;
    _grv_mv_max_velo = prm_max_velo;
    _grv_mv_acce = prm_acce;
    _grv_mv_stop_renge = prm_stop_renge;
    _grv_mv_flg = true;

    forceVeloXRange(-prm_max_velo, prm_max_velo);
    forceVeloYRange(-prm_max_velo, prm_max_velo);
    forceVeloZRange(-prm_max_velo, prm_max_velo);
}

void CoordVehicle::takeoverFrom(CoordVehicle* const prm_pAxsMver) {
    // X軸方向移動速度
    _velo_x = prm_pAxsMver->_velo_x;
    // X軸方向移動速度上限
    _top_velo_x = prm_pAxsMver->_top_velo_x;
    // X軸方向移動速度下限
    _bottom_velo_x = prm_pAxsMver->_bottom_velo_x;
    // X軸方向移動加速度
    _acce_x = prm_pAxsMver->_acce_x;
    // X軸方向移動加速度上限
    _top_acce_x = prm_pAxsMver->_top_acce_x;
    // X軸方向移動加速度下限
    _bottom_acce_x = prm_pAxsMver->_bottom_acce_x;
    // Y軸方向移動速度
    _velo_y = prm_pAxsMver->_velo_y;
    // Y軸方向移動速度上限
    _top_velo_y = prm_pAxsMver->_top_velo_y;
    // Y軸方向移動速度下限
    _bottom_velo_y = prm_pAxsMver->_bottom_velo_y;
    // Y軸方向移動加速度
    _acce_y = prm_pAxsMver->_acce_y;
    // Y軸方向移動加速度上限
    _top_acce_y = prm_pAxsMver->_top_acce_y;
    // Y軸方向移動加速度下限
    _bottom_acce_y = prm_pAxsMver->_bottom_acce_y;
    // Z軸方向移動速度
    _velo_z = prm_pAxsMver->_velo_z;
    // Z軸方向移動速度上限
    _top_velo_z = prm_pAxsMver->_top_velo_z;
    // Z軸方向移動速度下限
    _bottom_velo_z = prm_pAxsMver->_bottom_velo_z;
    // Z軸方向移動加速度
    _acce_z = prm_pAxsMver->_acce_z;
    // Z軸方向移動加速度上限
    _top_acce_z = prm_pAxsMver->_top_acce_z;
    // Z軸方向移動加速度下限
    _bottom_acce_z = prm_pAxsMver->_bottom_acce_z;
}

void CoordVehicle::stop() {
    setXYZZero();
    setAcceXYZZero();
    stopGravitationMvSequence();
    if (_pAsstMv) {
        _pAsstMv->stopSliding();
    }
}

void CoordVehicle::reset() {
    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _velo_x = 0;
    //X軸方向移動速度上限
    _top_velo_x = INT_MAX;
    //X軸方向移動速度下限
    _bottom_velo_x = INT_MIN;
    //X軸方向移動速度の加速度
    _acce_x = 0;
    _top_acce_x = INT_MAX;
    _bottom_acce_x = INT_MIN;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _velo_y = 0;
    //Y軸方向移動速度上限
    _top_velo_y = INT_MAX;
    //Y軸方向移動速度下限
    _bottom_velo_y = INT_MIN;
    //Y軸方向移動速度の加速度
    _acce_y = 0;

    _top_acce_y = INT_MAX;
    _bottom_acce_y = INT_MIN;

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _velo_z = 0;
    //Z軸方向移動速度上限
    _top_velo_z = INT_MAX;
    //Z軸方向移動速度下限
    _bottom_velo_z = INT_MIN;
    //Z軸方向移動速度の加速度
    _acce_z = 0;
    _top_acce_z = INT_MAX;
    _bottom_acce_z = INT_MIN;

    _grv_mv_flg = false;
}

CoordVehicle::~CoordVehicle() {
    GGAF_DELETE_NULLABLE(_pAsstMv);
}
