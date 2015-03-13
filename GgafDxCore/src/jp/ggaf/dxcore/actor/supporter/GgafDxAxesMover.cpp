#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_x,_y,_z)にそれぞれの移動増分が
// 加算される。

GgafDxAxesMover::GgafDxAxesMover(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {
    _pAsstA = nullptr;
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

GgafDxAxesMoverAssistantA* GgafDxAxesMover::asst() {
    return _pAsstA ? _pAsstA : _pAsstA = NEW GgafDxAxesMoverAssistantA(this);
}

void GgafDxAxesMover::behave() {
    if (_pAsstA) {
        _pAsstA->behave();
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
        const velo last_velo_vx_mv = _velo_vx_mv;
        const velo new_velo_vx_mv = _grv_mv_max_velo * (dx * 1.0 / _grv_mv_stop_renge);
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
        const velo new_velo_vy_mv = _grv_mv_max_velo * (dy * 1.0 / _grv_mv_stop_renge);
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
        const velo new_velo_vz_mv = _grv_mv_max_velo * (dz * 1.0 / _grv_mv_stop_renge);
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

int GgafDxAxesMover::dot(int prm_vX, int prm_vY, int prm_vZ) {
    return (prm_vX * _velo_vx_mv) + (prm_vY *_velo_vy_mv) + (prm_vZ*_velo_vz_mv);
}

void GgafDxAxesMover::forceVxMvVeloRange(velo prm_velo_vx_mv01, velo prm_velo_vx_mv02) {
    if (prm_velo_vx_mv01 < prm_velo_vx_mv02) {
        _top_velo_vx_mv = prm_velo_vx_mv02;
        _bottom_velo_vx_mv = prm_velo_vx_mv01;
    } else {
        _top_velo_vx_mv = prm_velo_vx_mv01;
        _bottom_velo_vx_mv = prm_velo_vx_mv02;
    }
    setVxMvVelo(_velo_vx_mv); //再設定して範囲内に補正
}

void GgafDxAxesMover::setVxMvVelo(velo prm_velo_vx_mv) {
    if (prm_velo_vx_mv > _top_velo_vx_mv) {
        _velo_vx_mv = _top_velo_vx_mv;
    } else if (prm_velo_vx_mv < _bottom_velo_vx_mv) {
        _velo_vx_mv = _bottom_velo_vx_mv;
    } else {
        _velo_vx_mv = prm_velo_vx_mv;
    }
}

void GgafDxAxesMover::addVxMvVelo(velo prm_velo_vx_mv) {
    _velo_vx_mv += prm_velo_vx_mv;
    if (_velo_vx_mv > _top_velo_vx_mv) {
        _velo_vx_mv = _top_velo_vx_mv;
    } else if (_velo_vx_mv < _bottom_velo_vx_mv) {
        _velo_vx_mv = _bottom_velo_vx_mv;
    }
}

void GgafDxAxesMover::setVxMvAcce(acce prm_acce_vx_mv) {
    if (prm_acce_vx_mv > _top_acce_vx_mv) {
        _acce_vx_mv = _top_acce_vx_mv;
    } else if (prm_acce_vx_mv < _bottom_acce_vx_mv) {
        _acce_vx_mv = _bottom_acce_vx_mv;
    } else {
        _acce_vx_mv = prm_acce_vx_mv;
    }
}

void GgafDxAxesMover::addVxMvAcce(acce prm_acce_vx_mv) {
    setVxMvAcce(_acce_vx_mv + prm_acce_vx_mv);
}

void GgafDxAxesMover::forceVxMvAcceRange(acce prm_acce_vx_mv01, acce prm_acce_vx_mv02) {
    if (prm_acce_vx_mv01 < prm_acce_vx_mv02) {
        _top_acce_vx_mv = prm_acce_vx_mv02;
        _bottom_acce_vx_mv = prm_acce_vx_mv01;
    } else {
        _top_acce_vx_mv = prm_acce_vx_mv01;
        _bottom_acce_vx_mv = prm_acce_vx_mv02;
    }
    setVxMvAcce(_acce_vx_mv); //再設定して範囲内に補正
}

void GgafDxAxesMover::forceVyMvVeloRange(velo prm_velo_vy_mv01, velo prm_velo_vy_mv02) {
    if (prm_velo_vy_mv01 < prm_velo_vy_mv02) {
        _top_velo_vy_mv = prm_velo_vy_mv02;
        _bottom_velo_vy_mv = prm_velo_vy_mv01;
    } else {
        _top_velo_vy_mv = prm_velo_vy_mv01;
        _bottom_velo_vy_mv = prm_velo_vy_mv02;
    }
    setVyMvVelo(_velo_vy_mv); //再設定して範囲内に補正
}

void GgafDxAxesMover::setVyMvVelo(velo prm_velo_vy_mv) {
    if (prm_velo_vy_mv > _top_velo_vy_mv) {
        _velo_vy_mv = _top_velo_vy_mv;
    } else if (prm_velo_vy_mv < _bottom_velo_vy_mv) {
        _velo_vy_mv = _bottom_velo_vy_mv;
    } else {
        _velo_vy_mv = prm_velo_vy_mv;
    }
}

void GgafDxAxesMover::addVyMvVelo(velo prm_velo_vy_mv) {
    _velo_vy_mv += prm_velo_vy_mv;
    if (_velo_vy_mv > _top_velo_vy_mv) {
        _velo_vy_mv = _top_velo_vy_mv;
    } else if (_velo_vy_mv < _bottom_velo_vy_mv) {
        _velo_vy_mv = _bottom_velo_vy_mv;
    }
}

void GgafDxAxesMover::setVyMvAcce(acce prm_acce_vy_mv) {
    if (prm_acce_vy_mv > _top_acce_vy_mv) {
        _acce_vy_mv = _top_acce_vy_mv;
    } else if (prm_acce_vy_mv < _bottom_acce_vy_mv) {
        _acce_vy_mv = _bottom_acce_vy_mv;
    } else {
        _acce_vy_mv = prm_acce_vy_mv;
    }
}

void GgafDxAxesMover::addVyMvAcce(acce prm_acce_vy_mv) {
    setVyMvAcce(_acce_vy_mv + prm_acce_vy_mv);
}

void GgafDxAxesMover::forceVyMvAcceRange(acce prm_acce_vy_mv01, acce prm_acce_vy_mv02) {
    if (prm_acce_vy_mv01 < prm_acce_vy_mv02) {
        _top_acce_vy_mv = prm_acce_vy_mv02;
        _bottom_acce_vy_mv = prm_acce_vy_mv01;
    } else {
        _top_acce_vy_mv = prm_acce_vy_mv01;
        _bottom_acce_vy_mv = prm_acce_vy_mv02;
    }
    setVyMvAcce(_acce_vy_mv); //再設定して範囲内に補正
}

void GgafDxAxesMover::forceVzMvVeloRange(velo prm_velo_vz_mv01, velo prm_velo_vz_mv02) {
    if (prm_velo_vz_mv01 < prm_velo_vz_mv02) {
        _top_velo_vz_mv = prm_velo_vz_mv02;
        _bottom_velo_vz_mv = prm_velo_vz_mv01;
    } else {
        _top_velo_vz_mv = prm_velo_vz_mv01;
        _bottom_velo_vz_mv = prm_velo_vz_mv02;
    }
    setVzMvVelo(_velo_vz_mv); //再設定して範囲内に補正
}

void GgafDxAxesMover::setVzMvVelo(velo prm_velo_vz_mv) {
    if (prm_velo_vz_mv > _top_velo_vz_mv) {
        _velo_vz_mv = _top_velo_vz_mv;
    } else if (prm_velo_vz_mv < _bottom_velo_vz_mv) {
        _velo_vz_mv = _bottom_velo_vz_mv;
    } else {
        _velo_vz_mv = prm_velo_vz_mv;
    }
}

void GgafDxAxesMover::addVzMvVelo(velo prm_velo_vz_mv) {
    _velo_vz_mv += prm_velo_vz_mv;
    if (_velo_vz_mv > _top_velo_vz_mv) {
        _velo_vz_mv = _top_velo_vz_mv;
    } else if (_velo_vz_mv < _bottom_velo_vz_mv) {
        _velo_vz_mv = _bottom_velo_vz_mv;
    }
}

void GgafDxAxesMover::setVzMvAcce(acce prm_acce_vz_mv) {
    if (prm_acce_vz_mv > _top_acce_vz_mv) {
        _acce_vz_mv = _top_acce_vz_mv;
    } else if (prm_acce_vz_mv < _bottom_acce_vz_mv) {
        _acce_vz_mv = _bottom_acce_vz_mv;
    } else {
        _acce_vz_mv = prm_acce_vz_mv;
    }
}

void GgafDxAxesMover::addVzMvAcce(acce prm_acce_vz_mv) {
    setVzMvAcce(_acce_vz_mv + prm_acce_vz_mv);
}

void GgafDxAxesMover::forceVzMvAcceRange(acce prm_acce_vz_mv01, acce prm_acce_vz_mv02) {
    if (prm_acce_vz_mv01 < prm_acce_vz_mv02) {
        _top_acce_vz_mv = prm_acce_vz_mv02;
        _bottom_acce_vz_mv = prm_acce_vz_mv01;
    } else {
        _top_acce_vz_mv = prm_acce_vz_mv01;
        _bottom_acce_vz_mv = prm_acce_vz_mv02;
    }
    setVzMvAcce(_acce_vz_mv); //再設定して範囲内に補正
}

void GgafDxAxesMover::forceVxyzMvVeloRange(velo prm_velo_vxyz_mv01, velo prm_velo_vxyz_mv02) {
    if (prm_velo_vxyz_mv01 < prm_velo_vxyz_mv02) {
        _top_velo_vx_mv = prm_velo_vxyz_mv02;
        _bottom_velo_vx_mv = prm_velo_vxyz_mv01;
        _top_velo_vy_mv = prm_velo_vxyz_mv02;
        _bottom_velo_vy_mv = prm_velo_vxyz_mv01;
        _top_velo_vz_mv = prm_velo_vxyz_mv02;
        _bottom_velo_vz_mv = prm_velo_vxyz_mv01;
    } else {
        _top_velo_vx_mv = prm_velo_vxyz_mv01;
        _bottom_velo_vx_mv = prm_velo_vxyz_mv02;
        _top_velo_vy_mv = prm_velo_vxyz_mv01;
        _bottom_velo_vy_mv = prm_velo_vxyz_mv02;
        _top_velo_vz_mv = prm_velo_vxyz_mv01;
        _bottom_velo_vz_mv = prm_velo_vxyz_mv02;
    }
    //再設定して範囲内に補正
    setVxMvVelo(_velo_vx_mv);
    setVyMvVelo(_velo_vy_mv);
    setVzMvVelo(_velo_vz_mv);
}

void GgafDxAxesMover::forceVxyzMvAcceRange(acce prm_acce_vxyz_mv01, acce prm_acce_vxyz_mv02) {
    forceVxMvAcceRange(prm_acce_vxyz_mv01, prm_acce_vxyz_mv02);
    forceVyMvAcceRange(prm_acce_vxyz_mv01, prm_acce_vxyz_mv02);
    forceVzMvAcceRange(prm_acce_vxyz_mv01, prm_acce_vxyz_mv02);
}

void GgafDxAxesMover::setVxyzMvVelo(velo prm_velo_vx_mv, velo prm_velo_vy_mv, velo prm_velo_vz_mv) {
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

void GgafDxAxesMover::setVxyzMvAcce(acce prm_acce_vx_mv, acce prm_acce_vy_mv, acce prm_acce_vz_mv) {
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

coord GgafDxAxesMover::setVxAcceByT(frame prm_target_frames, velo prm_target_velo) {
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

coord GgafDxAxesMover::setVyAcceByT(frame prm_target_frames, velo prm_target_velo) {
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

coord GgafDxAxesMover::setVzAcceByT(frame prm_target_frames, velo prm_target_velo) {
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

void GgafDxAxesMover::execGravitationMvSequenceTwd(coord prm_tx, coord prm_ty, coord prm_tz,
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

void GgafDxAxesMover::execGravitationMvSequenceTwd(const GgafDxGeometricActor* prm_pActor_target,
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

void GgafDxAxesMover::execGravitationMvSequenceTwd(const GgafDxGeometricActor* prm_pActor_target,
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

void GgafDxAxesMover::takeoverMvFrom(GgafDxAxesMover* const prm_pAxsMver) {
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

void GgafDxAxesMover::stopMv() {
    setZeroVxyzMvVelo();
    setZeroVxyzMvAcce();
    stopGravitationMvSequence();
    if (_pAsstA) {
        _pAsstA->stopSlidingMv();
    }
}

void GgafDxAxesMover::resetMv() {
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

GgafDxAxesMover::~GgafDxAxesMover() {
    GGAF_DELETE_NULLABLE(_pAsstA);
}
