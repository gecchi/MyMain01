#include "jp/ggaf/dx/actor/supporter/GeoDriver.h"

#include "jp/ggaf/dx/actor/supporter/GeoDriverAssistantA.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;
// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_x,_y,_z)にそれぞれの移動増分が
// 加算される。

GeoDriver::GeoDriver(GeometricActor* prm_pActor) : GgafCore::Object(),
_pActor(prm_pActor) {
    _pAsstMv = nullptr;
    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _velo_vx_mv = 0;
    //X軸方向移動速度上限
    _top_velo_vx_mv = INT_MAX;
    //X軸方向移動速度下限
    _bottom_velo_vx_mv = INT_MIN;
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acce_vx_mv = 0;
    _top_acce_vx_mv = INT_MAX;
    _bottom_acce_vx_mv = INT_MIN;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _velo_vy_mv = 0;
    //Y軸方向移動速度上限
    _top_velo_vy_mv = INT_MAX;
    //Y軸方向移動速度下限
    _bottom_velo_vy_mv = INT_MIN;
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acce_vy_mv = 0;

    _top_acce_vy_mv = INT_MAX;
    _bottom_acce_vy_mv = INT_MIN;

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _velo_vz_mv = 0;
    //Z軸方向移動速度上限
    _top_velo_vz_mv = INT_MAX;
    //Z軸方向移動速度下限
    _bottom_velo_vz_mv = INT_MIN;
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acce_vz_mv = 0;
    _top_acce_vz_mv = INT_MAX;
    _bottom_acce_vz_mv = INT_MIN;

    _grv_mv_target_x = 0;
    _grv_mv_target_y = 0;
    _grv_mv_target_z = 0;
    _grv_mv_pActor_target = nullptr;
    _grv_mv_max_velo = 1000;
    _grv_mv_acce = 1000;
    _grv_mv_stop_renge = 1000;
    _grv_mv_flg = false;
}

GeoDriverAssistantA* GeoDriver::asst() {
    return _pAsstMv ? _pAsstMv : _pAsstMv = NEW GeoDriverAssistantA(this);
}

void GeoDriver::behave() {
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
        const velo last_velo_vx_mv = _velo_vx_mv;
        const velo new_velo_vx_mv = _grv_mv_max_velo * (dx * inv_grv_mv_stop_renge);
        if (last_velo_vx_mv - x_acce <= new_velo_vx_mv &&
                                        new_velo_vx_mv <= last_velo_vx_mv + x_acce) {
            _velo_vx_mv = new_velo_vx_mv;
        } else {
            if (last_velo_vx_mv - x_acce > new_velo_vx_mv) {
                _velo_vx_mv = last_velo_vx_mv - x_acce;
            } else if (new_velo_vx_mv > last_velo_vx_mv + x_acce) {
                _velo_vx_mv = last_velo_vx_mv + x_acce;
            }
        }

        const velo last_velo_vy_mv = _velo_vy_mv;
        const velo new_velo_vy_mv = _grv_mv_max_velo * (dy * inv_grv_mv_stop_renge);
        if (last_velo_vy_mv - y_acce <= new_velo_vy_mv &&
                                        new_velo_vy_mv <= last_velo_vy_mv + y_acce) {
            _velo_vy_mv = new_velo_vy_mv;
        } else {
            if (last_velo_vy_mv - y_acce > new_velo_vy_mv) {
                _velo_vy_mv = last_velo_vy_mv - y_acce;
            } else if (new_velo_vy_mv > last_velo_vy_mv + y_acce) {
                _velo_vy_mv = last_velo_vy_mv + y_acce;
            }
        }

        const velo last_velo_vz_mv = _velo_vz_mv;
        const velo new_velo_vz_mv = _grv_mv_max_velo * (dz * inv_grv_mv_stop_renge);
        if (last_velo_vz_mv - z_acce <= new_velo_vz_mv &&
                                        new_velo_vz_mv <= last_velo_vz_mv + z_acce) {
            _velo_vz_mv = new_velo_vz_mv;
        } else {
            if (last_velo_vz_mv - z_acce > new_velo_vz_mv) {
                _velo_vz_mv = last_velo_vz_mv - z_acce;
            } else if (new_velo_vz_mv > last_velo_vz_mv + z_acce) {
                _velo_vz_mv = last_velo_vz_mv + z_acce;
            }
        }
    }

    _velo_vx_mv += _acce_vx_mv;
    if (_velo_vx_mv > _top_velo_vx_mv) {
        _velo_vx_mv = _top_velo_vx_mv;
    } else if (_velo_vx_mv < _bottom_velo_vx_mv) {
        _velo_vx_mv = _bottom_velo_vx_mv;
    }
    _velo_vy_mv += _acce_vy_mv;
    if (_velo_vy_mv > _top_velo_vy_mv) {
        _velo_vy_mv = _top_velo_vy_mv;
    } else if (_velo_vy_mv < _bottom_velo_vy_mv) {
        _velo_vy_mv = _bottom_velo_vy_mv;
    }
    _velo_vz_mv += _acce_vz_mv;
    if (_velo_vz_mv > _top_velo_vz_mv) {
        _velo_vz_mv = _top_velo_vz_mv;
    } else if (_velo_vz_mv < _bottom_velo_vz_mv) {
        _velo_vz_mv = _bottom_velo_vz_mv;
    }

    //Actorに反映
    _pActor->_x += _velo_vx_mv;
    _pActor->_y += _velo_vy_mv;
    _pActor->_z += _velo_vz_mv;
}

int GeoDriver::dot(int prm_vX, int prm_vY, int prm_vZ) {
    return (prm_vX * _velo_vx_mv) + (prm_vY *_velo_vy_mv) + (prm_vZ*_velo_vz_mv);
}


void GeoDriver::setVxMvVelo(velo prm_velo_vx_mv) {
    if (prm_velo_vx_mv > _top_velo_vx_mv) {
        _velo_vx_mv = _top_velo_vx_mv;
    } else if (prm_velo_vx_mv < _bottom_velo_vx_mv) {
        _velo_vx_mv = _bottom_velo_vx_mv;
    } else {
        _velo_vx_mv = prm_velo_vx_mv;
    }
}

void GeoDriver::addVxMvVelo(velo prm_velo_vx_mv) {
    _velo_vx_mv += prm_velo_vx_mv;
    if (_velo_vx_mv > _top_velo_vx_mv) {
        _velo_vx_mv = _top_velo_vx_mv;
    } else if (_velo_vx_mv < _bottom_velo_vx_mv) {
        _velo_vx_mv = _bottom_velo_vx_mv;
    }
}

void GeoDriver::forceVxMvVeloRange(velo prm_velo_vx_mv01, velo prm_velo_vx_mv02) {
    if (prm_velo_vx_mv01 < prm_velo_vx_mv02) {
        _top_velo_vx_mv = prm_velo_vx_mv02;
        _bottom_velo_vx_mv = prm_velo_vx_mv01;
    } else {
        _top_velo_vx_mv = prm_velo_vx_mv01;
        _bottom_velo_vx_mv = prm_velo_vx_mv02;
    }
    setVxMvVelo(_velo_vx_mv); //再設定して範囲内に補正
}

void GeoDriver::setVxMvAcce(acce prm_acce_vx_mv) {
    if (prm_acce_vx_mv > _top_acce_vx_mv) {
        _acce_vx_mv = _top_acce_vx_mv;
    } else if (prm_acce_vx_mv < _bottom_acce_vx_mv) {
        _acce_vx_mv = _bottom_acce_vx_mv;
    } else {
        _acce_vx_mv = prm_acce_vx_mv;
    }
}

void GeoDriver::addVxMvAcce(acce prm_acce_vx_mv) {
    setVxMvAcce(_acce_vx_mv + prm_acce_vx_mv);
}

void GeoDriver::forceVxMvAcceRange(acce prm_acce_vx_mv01, acce prm_acce_vx_mv02) {
    if (prm_acce_vx_mv01 < prm_acce_vx_mv02) {
        _top_acce_vx_mv = prm_acce_vx_mv02;
        _bottom_acce_vx_mv = prm_acce_vx_mv01;
    } else {
        _top_acce_vx_mv = prm_acce_vx_mv01;
        _bottom_acce_vx_mv = prm_acce_vx_mv02;
    }
    setVxMvAcce(_acce_vx_mv); //再設定して範囲内に補正
}


void GeoDriver::setVyMvVelo(velo prm_velo_vy_mv) {
    if (prm_velo_vy_mv > _top_velo_vy_mv) {
        _velo_vy_mv = _top_velo_vy_mv;
    } else if (prm_velo_vy_mv < _bottom_velo_vy_mv) {
        _velo_vy_mv = _bottom_velo_vy_mv;
    } else {
        _velo_vy_mv = prm_velo_vy_mv;
    }
}

void GeoDriver::addVyMvVelo(velo prm_velo_vy_mv) {
    _velo_vy_mv += prm_velo_vy_mv;
    if (_velo_vy_mv > _top_velo_vy_mv) {
        _velo_vy_mv = _top_velo_vy_mv;
    } else if (_velo_vy_mv < _bottom_velo_vy_mv) {
        _velo_vy_mv = _bottom_velo_vy_mv;
    }
}

void GeoDriver::forceVyMvVeloRange(velo prm_velo_vy_mv01, velo prm_velo_vy_mv02) {
    if (prm_velo_vy_mv01 < prm_velo_vy_mv02) {
        _top_velo_vy_mv = prm_velo_vy_mv02;
        _bottom_velo_vy_mv = prm_velo_vy_mv01;
    } else {
        _top_velo_vy_mv = prm_velo_vy_mv01;
        _bottom_velo_vy_mv = prm_velo_vy_mv02;
    }
    setVyMvVelo(_velo_vy_mv); //再設定して範囲内に補正
}
void GeoDriver::setVyMvAcce(acce prm_acce_vy_mv) {
    if (prm_acce_vy_mv > _top_acce_vy_mv) {
        _acce_vy_mv = _top_acce_vy_mv;
    } else if (prm_acce_vy_mv < _bottom_acce_vy_mv) {
        _acce_vy_mv = _bottom_acce_vy_mv;
    } else {
        _acce_vy_mv = prm_acce_vy_mv;
    }
}

void GeoDriver::addVyMvAcce(acce prm_acce_vy_mv) {
    setVyMvAcce(_acce_vy_mv + prm_acce_vy_mv);
}

void GeoDriver::forceVyMvAcceRange(acce prm_acce_vy_mv01, acce prm_acce_vy_mv02) {
    if (prm_acce_vy_mv01 < prm_acce_vy_mv02) {
        _top_acce_vy_mv = prm_acce_vy_mv02;
        _bottom_acce_vy_mv = prm_acce_vy_mv01;
    } else {
        _top_acce_vy_mv = prm_acce_vy_mv01;
        _bottom_acce_vy_mv = prm_acce_vy_mv02;
    }
    setVyMvAcce(_acce_vy_mv); //再設定して範囲内に補正
}


void GeoDriver::setVzMvVelo(velo prm_velo_vz_mv) {
    if (prm_velo_vz_mv > _top_velo_vz_mv) {
        _velo_vz_mv = _top_velo_vz_mv;
    } else if (prm_velo_vz_mv < _bottom_velo_vz_mv) {
        _velo_vz_mv = _bottom_velo_vz_mv;
    } else {
        _velo_vz_mv = prm_velo_vz_mv;
    }
}

void GeoDriver::addVzMvVelo(velo prm_velo_vz_mv) {
    _velo_vz_mv += prm_velo_vz_mv;
    if (_velo_vz_mv > _top_velo_vz_mv) {
        _velo_vz_mv = _top_velo_vz_mv;
    } else if (_velo_vz_mv < _bottom_velo_vz_mv) {
        _velo_vz_mv = _bottom_velo_vz_mv;
    }
}

void GeoDriver::forceVzMvVeloRange(velo prm_velo_vz_mv01, velo prm_velo_vz_mv02) {
    if (prm_velo_vz_mv01 < prm_velo_vz_mv02) {
        _top_velo_vz_mv = prm_velo_vz_mv02;
        _bottom_velo_vz_mv = prm_velo_vz_mv01;
    } else {
        _top_velo_vz_mv = prm_velo_vz_mv01;
        _bottom_velo_vz_mv = prm_velo_vz_mv02;
    }
    setVzMvVelo(_velo_vz_mv); //再設定して範囲内に補正
}

void GeoDriver::setVzMvAcce(acce prm_acce_vz_mv) {
    if (prm_acce_vz_mv > _top_acce_vz_mv) {
        _acce_vz_mv = _top_acce_vz_mv;
    } else if (prm_acce_vz_mv < _bottom_acce_vz_mv) {
        _acce_vz_mv = _bottom_acce_vz_mv;
    } else {
        _acce_vz_mv = prm_acce_vz_mv;
    }
}

void GeoDriver::addVzMvAcce(acce prm_acce_vz_mv) {
    setVzMvAcce(_acce_vz_mv + prm_acce_vz_mv);
}

void GeoDriver::forceVzMvAcceRange(acce prm_acce_vz_mv01, acce prm_acce_vz_mv02) {
    if (prm_acce_vz_mv01 < prm_acce_vz_mv02) {
        _top_acce_vz_mv = prm_acce_vz_mv02;
        _bottom_acce_vz_mv = prm_acce_vz_mv01;
    } else {
        _top_acce_vz_mv = prm_acce_vz_mv01;
        _bottom_acce_vz_mv = prm_acce_vz_mv02;
    }
    setVzMvAcce(_acce_vz_mv); //再設定して範囲内に補正
}

void GeoDriver::forceVxyzMvVeloRange(velo prm_velo_vxyz_mv01, velo prm_velo_vxyz_mv02) {
    if (prm_velo_vxyz_mv01 < prm_velo_vxyz_mv02) {
        _top_velo_vx_mv    = _top_velo_vy_mv    = _top_velo_vz_mv    = prm_velo_vxyz_mv02;
        _bottom_velo_vx_mv = _bottom_velo_vy_mv = _bottom_velo_vz_mv = prm_velo_vxyz_mv01;
    } else {
        _top_velo_vx_mv    = _top_velo_vy_mv    = _top_velo_vz_mv    = prm_velo_vxyz_mv01;
        _bottom_velo_vx_mv = _bottom_velo_vy_mv = _bottom_velo_vz_mv = prm_velo_vxyz_mv02;
    }
    //再設定して範囲内に補正
    setVxMvVelo(_velo_vx_mv);
    setVyMvVelo(_velo_vy_mv);
    setVzMvVelo(_velo_vz_mv);
}

void GeoDriver::forceVxyzMvAcceRange(acce prm_acce_vxyz_mv01, acce prm_acce_vxyz_mv02) {
    if (prm_acce_vxyz_mv01 < prm_acce_vxyz_mv02) {
        _top_acce_vx_mv    = _top_acce_vy_mv    = _top_acce_vz_mv    = prm_acce_vxyz_mv02;
        _bottom_acce_vx_mv = _bottom_acce_vy_mv = _bottom_acce_vz_mv = prm_acce_vxyz_mv01;
    } else {
        _top_acce_vx_mv    = _top_acce_vy_mv     = _top_acce_vz_mv   = prm_acce_vxyz_mv01;
        _bottom_acce_vx_mv =  _bottom_acce_vy_mv =_bottom_acce_vz_mv = prm_acce_vxyz_mv02;
    }
    //再設定して範囲内に補正
    setVxMvAcce(_acce_vx_mv);
    setVyMvAcce(_acce_vy_mv);
    setVzMvAcce(_acce_vz_mv);
}

void GeoDriver::setVxyzMvVelo(velo prm_velo_vx_mv, velo prm_velo_vy_mv, velo prm_velo_vz_mv) {
    if (prm_velo_vx_mv > _top_velo_vx_mv) {
        _velo_vx_mv = _top_velo_vx_mv;
    } else if (prm_velo_vx_mv < _bottom_velo_vx_mv) {
        _velo_vx_mv = _bottom_velo_vx_mv;
    } else {
        _velo_vx_mv = prm_velo_vx_mv;
    }
    if (prm_velo_vy_mv > _top_velo_vy_mv) {
        _velo_vy_mv = _top_velo_vy_mv;
    } else if (prm_velo_vy_mv < _bottom_velo_vy_mv) {
        _velo_vy_mv = _bottom_velo_vy_mv;
    } else {
        _velo_vy_mv = prm_velo_vy_mv;
    }
    if (prm_velo_vz_mv > _top_velo_vz_mv) {
        _velo_vz_mv = _top_velo_vz_mv;
    } else if (prm_velo_vz_mv < _bottom_velo_vz_mv) {
        _velo_vz_mv = _bottom_velo_vz_mv;
    } else {
        _velo_vz_mv = prm_velo_vz_mv;
    }
}

void GeoDriver::setVxyzMvVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo) {
    float vx, vy, vz;
    UTIL::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    setVxyzMvVelo(vx*prm_velo, vy*prm_velo, vz*prm_velo);
}

void GeoDriver::setVxyzMvVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo) {
    float vx, vy, vz;
    UTIL::getNormalizedVector(prm_tx - _pActor->_x,
                              prm_ty - _pActor->_y,
                              prm_tz - _pActor->_z,
                              vx, vy, vz);
    setVxyzMvVelo(vx*prm_velo, vy*prm_velo, vz*prm_velo);
}

void GeoDriver::setVxyzMvAcce(acce prm_acce_vx_mv, acce prm_acce_vy_mv, acce prm_acce_vz_mv) {
    if (prm_acce_vx_mv > _top_acce_vx_mv) {
        _acce_vx_mv = _top_acce_vx_mv;
    } else if (prm_acce_vx_mv < _bottom_acce_vx_mv) {
        _acce_vx_mv = _bottom_acce_vx_mv;
    } else {
        _acce_vx_mv = prm_acce_vx_mv;
    }
    if (prm_acce_vy_mv > _top_acce_vy_mv) {
        _acce_vy_mv = _top_acce_vy_mv;
    } else if (prm_acce_vy_mv < _bottom_acce_vy_mv) {
        _acce_vy_mv = _bottom_acce_vy_mv;
    } else {
        _acce_vy_mv = prm_acce_vy_mv;
    }
    if (prm_acce_vz_mv > _top_acce_vz_mv) {
        _acce_vz_mv = _top_acce_vz_mv;
    } else if (prm_acce_vz_mv < _bottom_acce_vz_mv) {
        _acce_vz_mv = _bottom_acce_vz_mv;
    } else {
        _acce_vz_mv = prm_acce_vz_mv;
    }
}

coord GeoDriver::setVxAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_vx_mv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setVxMvAcce(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_vx_mv + prm_target_velo) * prm_target_frames) / 2 ;
}

coord GeoDriver::setVyAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_vy_mv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setVyMvAcce(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_vy_mv + prm_target_velo) * prm_target_frames) / 2 ;
}

coord GeoDriver::setVzAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _velo_vz_mv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setVzMvAcce(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_velo_vz_mv + prm_target_velo) * prm_target_frames) / 2 ;
}

void GeoDriver::execGravitationMvSequenceTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                        velo prm_max_velo,
                                        acce prm_acce,
                                        int prm_stop_renge ) {
    _grv_mv_target_x = prm_tx;
    _grv_mv_target_y = prm_ty;
    _grv_mv_target_z = prm_tz;
    _grv_mv_pActor_target = nullptr;
    _grv_mv_max_velo = prm_max_velo;
    _grv_mv_acce = prm_acce;
    _grv_mv_stop_renge = prm_stop_renge;
    _grv_mv_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}

void GeoDriver::execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
                                        velo prm_max_velo,
                                        acce prm_acce,
                                        int prm_stop_renge ) {
    _grv_mv_target_x = 0;
    _grv_mv_target_y = 0;
    _grv_mv_target_z = 0;
    _grv_mv_pActor_target = prm_pActor_target;
    _grv_mv_max_velo = prm_max_velo;
    _grv_mv_acce = prm_acce;
    _grv_mv_stop_renge = prm_stop_renge;
    _grv_mv_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}

void GeoDriver::execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
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

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}

void GeoDriver::takeoverMvFrom(GeoDriver* const prm_pAxsMver) {
    // X軸方向移動速度
    _velo_vx_mv = prm_pAxsMver->_velo_vx_mv;
    // X軸方向移動速度上限
    _top_velo_vx_mv = prm_pAxsMver->_top_velo_vx_mv;
    // X軸方向移動速度下限
    _bottom_velo_vx_mv = prm_pAxsMver->_bottom_velo_vx_mv;
    // X軸方向移動加速度
    _acce_vx_mv = prm_pAxsMver->_acce_vx_mv;
    // X軸方向移動加速度上限
    _top_acce_vx_mv = prm_pAxsMver->_top_acce_vx_mv;
    // X軸方向移動加速度下限
    _bottom_acce_vx_mv = prm_pAxsMver->_bottom_acce_vx_mv;
    // Y軸方向移動速度
    _velo_vy_mv = prm_pAxsMver->_velo_vy_mv;
    // Y軸方向移動速度上限
    _top_velo_vy_mv = prm_pAxsMver->_top_velo_vy_mv;
    // Y軸方向移動速度下限
    _bottom_velo_vy_mv = prm_pAxsMver->_bottom_velo_vy_mv;
    // Y軸方向移動加速度
    _acce_vy_mv = prm_pAxsMver->_acce_vy_mv;
    // Y軸方向移動加速度上限
    _top_acce_vy_mv = prm_pAxsMver->_top_acce_vy_mv;
    // Y軸方向移動加速度下限
    _bottom_acce_vy_mv = prm_pAxsMver->_bottom_acce_vy_mv;
    // Z軸方向移動速度
    _velo_vz_mv = prm_pAxsMver->_velo_vz_mv;
    // Z軸方向移動速度上限
    _top_velo_vz_mv = prm_pAxsMver->_top_velo_vz_mv;
    // Z軸方向移動速度下限
    _bottom_velo_vz_mv = prm_pAxsMver->_bottom_velo_vz_mv;
    // Z軸方向移動加速度
    _acce_vz_mv = prm_pAxsMver->_acce_vz_mv;
    // Z軸方向移動加速度上限
    _top_acce_vz_mv = prm_pAxsMver->_top_acce_vz_mv;
    // Z軸方向移動加速度下限
    _bottom_acce_vz_mv = prm_pAxsMver->_bottom_acce_vz_mv;
}

void GeoDriver::stopMv() {
    setZeroVxyzMvVelo();
    setZeroVxyzMvAcce();
    stopGravitationMvSequence();
    if (_pAsstMv) {
        _pAsstMv->stopSliding();
    }
}

void GeoDriver::resetMv() {
    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _velo_vx_mv = 0;
    //X軸方向移動速度上限
    _top_velo_vx_mv = INT_MAX;
    //X軸方向移動速度下限
    _bottom_velo_vx_mv = INT_MIN;
    //X軸方向移動速度の加速度
    _acce_vx_mv = 0;
    _top_acce_vx_mv = INT_MAX;
    _bottom_acce_vx_mv = INT_MIN;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _velo_vy_mv = 0;
    //Y軸方向移動速度上限
    _top_velo_vy_mv = INT_MAX;
    //Y軸方向移動速度下限
    _bottom_velo_vy_mv = INT_MIN;
    //Y軸方向移動速度の加速度
    _acce_vy_mv = 0;

    _top_acce_vy_mv = INT_MAX;
    _bottom_acce_vy_mv = INT_MIN;

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _velo_vz_mv = 0;
    //Z軸方向移動速度上限
    _top_velo_vz_mv = INT_MAX;
    //Z軸方向移動速度下限
    _bottom_velo_vz_mv = INT_MIN;
    //Z軸方向移動速度の加速度
    _acce_vz_mv = 0;
    _top_acce_vz_mv = INT_MAX;
    _bottom_acce_vz_mv = INT_MIN;

    _grv_mv_flg = false;
}

GeoDriver::~GeoDriver() {
    GGAF_DELETE_NULLABLE(_pAsstMv);
}
