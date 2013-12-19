#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_x,_y,_z)にそれぞれの移動増分が
// 加算される。

GgafDxAxesMover::GgafDxAxesMover(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {
    _pHlprA = nullptr;
    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _veloVxMv = 0;
    //X軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVxMv = PX_C(256);
    //X軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVxMv = -PX_C(256);
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVxMv = 0;
    _acceTopVxMv = PX_C(256);
    _acceBottomVxMv = -PX_C(256);
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _veloVyMv = 0;
    //Y軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVyMv = PX_C(256);
    //Y軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVyMv = -PX_C(256);
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVyMv = 0;

    _acceTopVyMv = PX_C(256);
    _acceBottomVyMv = -PX_C(256);

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _veloVzMv = 0;
    //Z軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVzMv = PX_C(256);
    //Z軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVzMv = -PX_C(256);
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVzMv = 0;
    _acceTopVzMv = PX_C(256);
    _acceBottomVzMv = -PX_C(256);

    _gravitation_mv_seq_target_x = 0;
    _gravitation_mv_seq_target_y = 0;
    _gravitation_mv_seq_target_z = 0;
    _gravitation_mv_seq_pActor_target = nullptr;
    _gravitation_mv_seq_max_velo = 1000;
    _gravitation_mv_seq_acce = 1000;
    _gravitation_mv_seq_stop_renge = 1000;
    _gravitation_mv_seq_flg = false;

}

GgafDxAxesMoverHelperA* GgafDxAxesMover::hlprA() {
    return _pHlprA ? _pHlprA : _pHlprA = NEW GgafDxAxesMoverHelperA(this);
}

void GgafDxAxesMover::behave() {
    if (_pHlprA) {
        _pHlprA->behave();
    }

    if(_gravitation_mv_seq_flg) {
        coord dX, dY, dZ;
        if (_gravitation_mv_seq_pActor_target) {
            dX = _gravitation_mv_seq_pActor_target->_x - _pActor->_x;
            dY = _gravitation_mv_seq_pActor_target->_y - _pActor->_y;
            dZ = _gravitation_mv_seq_pActor_target->_z - _pActor->_z;
        } else {
            dX = _gravitation_mv_seq_target_x - _pActor->_x;
            dY = _gravitation_mv_seq_target_y - _pActor->_y;
            dZ = _gravitation_mv_seq_target_z - _pActor->_z;
        }
        coord dX_abs = ABS(dX);
        coord dY_abs = ABS(dY);
        coord dZ_abs = ABS(dZ);
        coord dmax = MAX3(dX_abs, dY_abs, dZ_abs);//距離簡易計算
        if (dmax > _gravitation_mv_seq_max_velo) {
            double rr = 1.0*_gravitation_mv_seq_max_velo / dmax;
            dX *= rr;
            dY *= rr;
            dZ *= rr;
        }
        double r_acce = 1.7*_gravitation_mv_seq_acce / dmax;
        acce X_acce = r_acce * dX_abs;
        acce Y_acce = r_acce * dY_abs;
        acce Z_acce = r_acce * dZ_abs;
        if (X_acce > _gravitation_mv_seq_acce) {
            X_acce = _gravitation_mv_seq_acce;
        }
        if (Y_acce > _gravitation_mv_seq_acce) {
            Y_acce = _gravitation_mv_seq_acce;
        }
        if (Z_acce > _gravitation_mv_seq_acce) {
            Z_acce = _gravitation_mv_seq_acce;
        }
        velo last_veloVxMv = _veloVxMv;
        velo new_veloVxMv = _gravitation_mv_seq_max_velo * (dX * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVxMv - X_acce <= new_veloVxMv &&
                                      new_veloVxMv <= last_veloVxMv + X_acce) {
            _veloVxMv = new_veloVxMv;
        } else {
            if (last_veloVxMv - X_acce > new_veloVxMv) {
                _veloVxMv = last_veloVxMv - X_acce;
            } else if (new_veloVxMv > last_veloVxMv + X_acce) {
                _veloVxMv = last_veloVxMv + X_acce;
            }
        }

        velo last_veloVyMv = _veloVyMv;
        velo new_veloVyMv = _gravitation_mv_seq_max_velo * (dY * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVyMv - Y_acce <= new_veloVyMv &&
                                      new_veloVyMv <= last_veloVyMv + Y_acce) {
            _veloVyMv = new_veloVyMv;
        } else {
            if (last_veloVyMv - Y_acce > new_veloVyMv) {
                _veloVyMv = last_veloVyMv - Y_acce;
            } else if (new_veloVyMv > last_veloVyMv + Y_acce) {
                _veloVyMv = last_veloVyMv + Y_acce;
            }
        }

        velo last_veloVzMv = _veloVzMv;
        velo new_veloVzMv = _gravitation_mv_seq_max_velo * (dZ * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVzMv - Z_acce <= new_veloVzMv &&
                                      new_veloVzMv <= last_veloVzMv + Z_acce) {
            _veloVzMv = new_veloVzMv;
        } else {
            if (last_veloVzMv - Z_acce > new_veloVzMv) {
                _veloVzMv = last_veloVzMv - Z_acce;
            } else if (new_veloVzMv > last_veloVzMv + Z_acce) {
                _veloVzMv = last_veloVzMv + Z_acce;
            }
        }
    }

    _veloVxMv += _acceVxMv;
    if (_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    }
    _veloVyMv += _acceVyMv;
    if (_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    }
    _veloVzMv += _acceVzMv;
    if (_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    }

    //Actorに反映
    _pActor->_x += _veloVxMv;
    _pActor->_y += _veloVyMv;
    _pActor->_z += _veloVzMv;
}

int GgafDxAxesMover::dot(int prm_vX, int prm_vY, int prm_vZ) {
    return (prm_vX * _veloVxMv) + (prm_vY *_veloVyMv) + (prm_vZ*_veloVzMv);
}

void GgafDxAxesMover::forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02) {
    if (prm_veloVxMv01 < prm_veloVxMv02) {
        _veloTopVxMv = prm_veloVxMv02;
        _veloBottomVxMv = prm_veloVxMv01;
    } else {
        _veloTopVxMv = prm_veloVxMv01;
        _veloBottomVxMv = prm_veloVxMv02;
    }
    setVxMvVelo(_veloVxMv); //再設定して範囲内に補正
}

void GgafDxAxesMover::setVxMvVelo(velo prm_veloVxMv) {
    if (prm_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (prm_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    } else {
        _veloVxMv = prm_veloVxMv;
    }
}

void GgafDxAxesMover::addVxMvVelo(velo prm_veloVxMv) {
    _veloVxMv += prm_veloVxMv;
    if (_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    }
}

void GgafDxAxesMover::setVxMvAcce(acce prm_acceVxMv) {
    if (prm_acceVxMv > _acceTopVxMv) {
        _acceVxMv = _acceTopVxMv;
    } else if (prm_acceVxMv < _acceBottomVxMv) {
        _acceVxMv = _acceBottomVxMv;
    } else {
        _acceVxMv = prm_acceVxMv;
    }
}

void GgafDxAxesMover::addVxMvAcce(acce prm_acceVxMv) {
    setVxMvAcce(_acceVxMv + prm_acceVxMv);
}

void GgafDxAxesMover::forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02) {
    if (prm_acceVxMv01 < prm_acceVxMv02) {
        _acceTopVxMv = prm_acceVxMv02;
        _acceBottomVxMv = prm_acceVxMv01;
    } else {
        _acceTopVxMv = prm_acceVxMv01;
        _acceBottomVxMv = prm_acceVxMv02;
    }
    setVxMvAcce(_acceVxMv); //再設定して範囲内に補正
}

void GgafDxAxesMover::forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02) {
    if (prm_veloVyMv01 < prm_veloVyMv02) {
        _veloTopVyMv = prm_veloVyMv02;
        _veloBottomVyMv = prm_veloVyMv01;
    } else {
        _veloTopVyMv = prm_veloVyMv01;
        _veloBottomVyMv = prm_veloVyMv02;
    }
    setVyMvVelo(_veloVyMv); //再設定して範囲内に補正
}

void GgafDxAxesMover::setVyMvVelo(velo prm_veloVyMv) {
    if (prm_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (prm_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    } else {
        _veloVyMv = prm_veloVyMv;
    }
}

void GgafDxAxesMover::addVyMvVelo(velo prm_veloVyMv) {
    _veloVyMv += prm_veloVyMv;
    if (_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    }
}

void GgafDxAxesMover::setVyMvAcce(acce prm_acceVyMv) {
    if (prm_acceVyMv > _acceTopVyMv) {
        _acceVyMv = _acceTopVyMv;
    } else if (prm_acceVyMv < _acceBottomVyMv) {
        _acceVyMv = _acceBottomVyMv;
    } else {
        _acceVyMv = prm_acceVyMv;
    }
}

void GgafDxAxesMover::addVyMvAcce(acce prm_acceVyMv) {
    setVyMvAcce(_acceVyMv + prm_acceVyMv);
}

void GgafDxAxesMover::forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02) {
    if (prm_acceVyMv01 < prm_acceVyMv02) {
        _acceTopVyMv = prm_acceVyMv02;
        _acceBottomVyMv = prm_acceVyMv01;
    } else {
        _acceTopVyMv = prm_acceVyMv01;
        _acceBottomVyMv = prm_acceVyMv02;
    }
    setVyMvAcce(_acceVyMv); //再設定して範囲内に補正
}

void GgafDxAxesMover::forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02) {
    if (prm_veloVzMv01 < prm_veloVzMv02) {
        _veloTopVzMv = prm_veloVzMv02;
        _veloBottomVzMv = prm_veloVzMv01;
    } else {
        _veloTopVzMv = prm_veloVzMv01;
        _veloBottomVzMv = prm_veloVzMv02;
    }
    setVzMvVelo(_veloVzMv); //再設定して範囲内に補正
}

void GgafDxAxesMover::setVzMvVelo(velo prm_veloVzMv) {
    if (prm_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (prm_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    } else {
        _veloVzMv = prm_veloVzMv;
    }
}

void GgafDxAxesMover::addVzMvVelo(velo prm_veloVzMv) {
    _veloVzMv += prm_veloVzMv;
    if (_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    }
}

void GgafDxAxesMover::setVzMvAcce(acce prm_acceVzMv) {
    if (prm_acceVzMv > _acceTopVzMv) {
        _acceVzMv = _acceTopVzMv;
    } else if (prm_acceVzMv < _acceBottomVzMv) {
        _acceVzMv = _acceBottomVzMv;
    } else {
        _acceVzMv = prm_acceVzMv;
    }
}

void GgafDxAxesMover::addVzMvAcce(acce prm_acceVzMv) {
    setVzMvAcce(_acceVzMv + prm_acceVzMv);
}

void GgafDxAxesMover::forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02) {
    if (prm_acceVzMv01 < prm_acceVzMv02) {
        _acceTopVzMv = prm_acceVzMv02;
        _acceBottomVzMv = prm_acceVzMv01;
    } else {
        _acceTopVzMv = prm_acceVzMv01;
        _acceBottomVzMv = prm_acceVzMv02;
    }
    setVzMvAcce(_acceVzMv); //再設定して範囲内に補正
}

void GgafDxAxesMover::forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02) {
    if (prm_veloVxyzMv01 < prm_veloVxyzMv02) {
        _veloTopVxMv = prm_veloVxyzMv02;
        _veloBottomVxMv = prm_veloVxyzMv01;
        _veloTopVyMv = prm_veloVxyzMv02;
        _veloBottomVyMv = prm_veloVxyzMv01;
        _veloTopVzMv = prm_veloVxyzMv02;
        _veloBottomVzMv = prm_veloVxyzMv01;
    } else {
        _veloTopVxMv = prm_veloVxyzMv01;
        _veloBottomVxMv = prm_veloVxyzMv02;
        _veloTopVyMv = prm_veloVxyzMv01;
        _veloBottomVyMv = prm_veloVxyzMv02;
        _veloTopVzMv = prm_veloVxyzMv01;
        _veloBottomVzMv = prm_veloVxyzMv02;
    }
    //再設定して範囲内に補正
    setVxMvVelo(_veloVxMv);
    setVyMvVelo(_veloVyMv);
    setVzMvVelo(_veloVzMv);
}
void GgafDxAxesMover::forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02) {
    forceVxMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVyMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVzMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
}

void GgafDxAxesMover::setVxyzMvVelo(velo prm_veloVxMv, velo prm_veloVyMv, velo prm_veloVzMv) {
    if (prm_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (prm_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    } else {
        _veloVxMv = prm_veloVxMv;
    }
    if (prm_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (prm_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    } else {
        _veloVyMv = prm_veloVyMv;
    }
    if (prm_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (prm_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    } else {
        _veloVzMv = prm_veloVzMv;
    }
}

void GgafDxAxesMover::setVxyzMvAcce(acce prm_acceVxMv, acce prm_acceVyMv, acce prm_acceVzMv) {
    if (prm_acceVxMv > _acceTopVxMv) {
        _acceVxMv = _acceTopVxMv;
    } else if (prm_acceVxMv < _acceBottomVxMv) {
        _acceVxMv = _acceBottomVxMv;
    } else {
        _acceVxMv = prm_acceVxMv;
    }
    if (prm_acceVyMv > _acceTopVyMv) {
        _acceVyMv = _acceTopVyMv;
    } else if (prm_acceVyMv < _acceBottomVyMv) {
        _acceVyMv = _acceBottomVyMv;
    } else {
        _acceVyMv = prm_acceVyMv;
    }
    if (prm_acceVzMv > _acceTopVzMv) {
        _acceVzMv = _acceTopVzMv;
    } else if (prm_acceVzMv < _acceBottomVzMv) {
        _acceVzMv = _acceBottomVzMv;
    } else {
        _acceVzMv = prm_acceVzMv;
    }
}

void GgafDxAxesMover::execGravitationMvSequenceTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                                 velo prm_max_velo,
                                                 acce prm_acce,
                                                 int prm_stop_renge ) {
    _gravitation_mv_seq_target_x = prm_tx;
    _gravitation_mv_seq_target_y = prm_ty;
    _gravitation_mv_seq_target_z = prm_tz;
    _gravitation_mv_seq_pActor_target = nullptr;
    _gravitation_mv_seq_max_velo = prm_max_velo;
    _gravitation_mv_seq_acce = prm_acce;
    _gravitation_mv_seq_stop_renge = prm_stop_renge;
    _gravitation_mv_seq_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}

void GgafDxAxesMover::execGravitationMvSequenceTwd(GgafDxGeometricActor* prm_pActor_target,
                                                 velo prm_max_velo,
                                                 acce prm_acce,
                                                 int prm_stop_renge ) {
    _gravitation_mv_seq_target_x = 0;
    _gravitation_mv_seq_target_y = 0;
    _gravitation_mv_seq_target_z = 0;
    _gravitation_mv_seq_pActor_target = prm_pActor_target;
    _gravitation_mv_seq_max_velo = prm_max_velo;
    _gravitation_mv_seq_acce = prm_acce;
    _gravitation_mv_seq_stop_renge = prm_stop_renge;
    _gravitation_mv_seq_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}

void GgafDxAxesMover::takeoverMvFrom(GgafDxAxesMover* const prmpAxsMver_) {

    // X軸方向移動速度
    _veloVxMv = prmpAxsMver_->_veloVxMv;
    // X軸方向移動速度上限
    _veloTopVxMv = prmpAxsMver_->_veloTopVxMv;
    // X軸方向移動速度下限
    _veloBottomVxMv = prmpAxsMver_->_veloBottomVxMv;
    // X軸方向移動加速度
    _acceVxMv = prmpAxsMver_->_acceVxMv;
    // X軸方向移動加速度上限
    _acceTopVxMv = prmpAxsMver_->_acceTopVxMv;
    // X軸方向移動加速度下限
    _acceBottomVxMv = prmpAxsMver_->_acceBottomVxMv;
    // Y軸方向移動速度
    _veloVyMv = prmpAxsMver_->_veloVyMv;
    // Y軸方向移動速度上限
    _veloTopVyMv = prmpAxsMver_->_veloTopVyMv;
    // Y軸方向移動速度下限
    _veloBottomVyMv = prmpAxsMver_->_veloBottomVyMv;
    // Y軸方向移動加速度
    _acceVyMv = prmpAxsMver_->_acceVyMv;
    // Y軸方向移動加速度上限
    _acceTopVyMv = prmpAxsMver_->_acceTopVyMv;
    // Y軸方向移動加速度下限
    _acceBottomVyMv = prmpAxsMver_->_acceBottomVyMv;
    // Z軸方向移動速度
    _veloVzMv = prmpAxsMver_->_veloVzMv;
    // Z軸方向移動速度上限
    _veloTopVzMv = prmpAxsMver_->_veloTopVzMv;
    // Z軸方向移動速度下限
    _veloBottomVzMv = prmpAxsMver_->_veloBottomVzMv;
    // Z軸方向移動加速度
    _acceVzMv = prmpAxsMver_->_acceVzMv;
    // Z軸方向移動加速度上限
    _acceTopVzMv = prmpAxsMver_->_acceTopVzMv;
    // Z軸方向移動加速度下限
    _acceBottomVzMv = prmpAxsMver_->_acceBottomVzMv;

}

void GgafDxAxesMover::resetMv() {
    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _veloVxMv = 0;
    //X軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVxMv = PX_C(256);
    //X軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVxMv = -PX_C(256);
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVxMv = 0;
    _acceTopVxMv = PX_C(256);
    _acceBottomVxMv = -PX_C(256);
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _veloVyMv = 0;
    //Y軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVyMv = PX_C(256);
    //Y軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVyMv = -PX_C(256);
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVyMv = 0;

    _acceTopVyMv = PX_C(256);
    _acceBottomVyMv = -PX_C(256);

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _veloVzMv = 0;
    //Z軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVzMv = PX_C(256);
    //Z軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVzMv = -PX_C(256);
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVzMv = 0;
    _acceTopVzMv = PX_C(256);
    _acceBottomVzMv = -PX_C(256);

    _gravitation_mv_seq_flg = false;
}

GgafDxAxesMover::~GgafDxAxesMover() {
    GGAF_DELETE_NULLABLE(_pHlprA);
}
