#include "jp/ggaf/dx/actor/supporter/NaviVehicle.h"

#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;

NaviVehicle::NaviVehicle(GeometricActor* prm_pActor)  : ActorVehicle(prm_pActor) {
    _velo = 0;
    _top_velo = INT_MAX;
    _bottom_velo = 0;
    _velo_vc_x = 0;
    _velo_vc_y = 0;
    _velo_vc_z = 0;
    _acce = 0;
    _top_acce = INT_MAX;
    _bottom_acce = 0;
    _acce_vc_x = 0;
    _acce_vc_y = 0;
    _acce_vc_z = 0;
}


void NaviVehicle::forceVeloRange(velo prm_velo01, velo prm_velo02) {
#ifdef MY_DEBUG
    if (prm_velo01 < 0 || prm_velo02 < 0) {
        throwCriticalException("NaviVehicle::forceVeloRange() 負の速度を範囲設定することはできません。"
                               " prm_velo01="<<prm_velo01<<",prm_velo02="<<prm_velo02<<"");
    }
#endif
    if (prm_velo01 < prm_velo02) {
        _top_velo = prm_velo02;
        _bottom_velo = prm_velo01;
    } else {
        _top_velo = prm_velo01;
        _bottom_velo = prm_velo02;
    }
    //再設定して範囲内に補正
    setVeloByVc(_velo_vc_x, _velo_vc_y, _velo_vc_z);
}

void NaviVehicle::forceAcceRange(acce prm_acce01, acce prm_acce02) {
#ifdef MY_DEBUG
    if (prm_acce01 < 0 || prm_acce02 < 0) {
        throwCriticalException("NaviVehicle::forceAcceRange() 負の加速度を範囲設定することはできません。"
                               " prm_acce01="<<prm_acce01<<",prm_acce02="<<prm_acce02<<"");
    }
#endif
    if (prm_acce01 < prm_acce02) {
        _top_acce = prm_acce02;
        _bottom_acce = prm_acce01;
    } else {
        _top_acce = prm_acce01;
        _bottom_acce = prm_acce02;
    }
    //再設定して範囲内に補正
    setAcceByVc(_acce_vc_x, _acce_vc_y, _acce_vc_z);
}


void NaviVehicle::setVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo) {
    if (prm_velo == 0) {
        _velo_vc_x = _bottom_velo;
        _velo_vc_y = 0;
        _velo_vc_z = 0;
        _velo = _bottom_velo;
        return;
    }
    double vx = prm_tx - _pActor->_x;
    double vy = prm_ty - _pActor->_y;
    double vz = prm_tz - _pActor->_z;
    double p = vx*vx + vy*vy + vz*vz;
    if (ZEROd_EQ(p)) {
        //速度が０になってしまったら
        //加速度の方向ベクトルに最低速度を設定
        p = 1.0*_acce_vc_x*_acce_vc_x +
            1.0*_acce_vc_y*_acce_vc_y +
            1.0*_acce_vc_z*_acce_vc_z;
        if (ZEROd_EQ(p)) {
            //加速度も０なら、あきらめて _velo_vc_x に最低速度を設定
            _velo_vc_x = _bottom_velo;
            _velo_vc_y = 0;
            _velo_vc_z = 0;
            _velo = _bottom_velo;
            return;
        }
    }
    velo velo_xyz = prm_velo;
    if (prm_velo > _top_velo) {
        velo_xyz = _top_velo;
    } else if (prm_velo < _bottom_velo) {
        velo_xyz = _bottom_velo;
    }
    double t = (velo_xyz / sqrt(p));
    _velo_vc_x = t * vx;
    _velo_vc_y = t * vy;
    _velo_vc_z = t * vz;
    _velo = velo_xyz;
}

void NaviVehicle::setVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo) {
    double vx, vy, vz;
    UTIL::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    setVeloByVc(vx*prm_velo, vy*prm_velo, vz*prm_velo);
}

void NaviVehicle::setVeloByVc(velo prm_velo_vc_x, velo prm_velo_vc_y, velo prm_velo_vc_z) {
    double p = 1.0*prm_velo_vc_x*prm_velo_vc_x +
               1.0*prm_velo_vc_y*prm_velo_vc_y +
               1.0*prm_velo_vc_z*prm_velo_vc_z;
    if (ZEROd_EQ(p)) {
        //速度が０になってしまったら
        //加速度の方向ベクトルに最低速度を設定
        p = 1.0*_acce_vc_x*_acce_vc_x +
            1.0*_acce_vc_y*_acce_vc_y +
            1.0*_acce_vc_z*_acce_vc_z;
        if (ZEROd_EQ(p)) {
            //加速度も０なら、あきらめて _velo_vc_x に最低速度を設定
            _velo_vc_x = _bottom_velo;
            _velo_vc_y = 0;
            _velo_vc_z = 0;
            _velo = _bottom_velo;
            return;
        }
    }
    double velo_xyz = sqrt(p);
    if (velo_xyz > _top_velo) {
        double t = _top_velo/velo_xyz;
        _velo_vc_x = t * prm_velo_vc_x;
        _velo_vc_y = t * prm_velo_vc_y;
        _velo_vc_z = t * prm_velo_vc_z;
        _velo = _top_velo;
        return;
    } else if (velo_xyz < _bottom_velo) {
        double t = _bottom_velo/velo_xyz;
        _velo_vc_x = t * prm_velo_vc_x;
        _velo_vc_y = t * prm_velo_vc_y;
        _velo_vc_z = t * prm_velo_vc_z;
        _velo = _bottom_velo;
        return;
    } else {
        _velo_vc_x = prm_velo_vc_x;
        _velo_vc_y = prm_velo_vc_y;
        _velo_vc_z = prm_velo_vc_z;
        _velo = velo_xyz;
        return;
    }
}
void NaviVehicle::setVeloZero() {
    setVeloByVc(0,0,0);
}

void NaviVehicle::setAcceTwd(coord prm_tx, coord prm_ty, coord prm_tz, acce prm_acce) {
    acce acce_xyz = prm_acce;
    if (prm_acce > _top_acce) {
        acce_xyz = _top_acce;
    } else if (prm_acce < _bottom_acce) {
        acce_xyz = _bottom_acce;
    }
    double vx = prm_tx - _pActor->_x;
    double vy = prm_ty - _pActor->_y;
    double vz = prm_tz - _pActor->_z;
    double p = vx*vx + vy*vy + vz*vz;
    if (ZEROd_EQ(p)) {
        _acce_vc_x = _bottom_acce;
        _acce_vc_y = 0;
        _acce_vc_z = 0;
        _acce = _bottom_acce;
    } else {
        double t = (acce_xyz / sqrt(vx*vx + vy*vy + vz*vz));
        _acce_vc_x = t * vx;
        _acce_vc_y = t * vy;
        _acce_vc_z = t * vz;
        _acce = acce_xyz;
    }
}

void NaviVehicle::setAcceByVc(acce prm_acce_vc_x, acce prm_acce_vc_y, acce prm_acce_vc_z) {
    double p = 1.0 * prm_acce_vc_x * prm_acce_vc_x +
               1.0 * prm_acce_vc_y * prm_acce_vc_y +
               1.0 * prm_acce_vc_z * prm_acce_vc_z;
    if (ZEROd_EQ(p)) {
        _acce_vc_x = _bottom_acce;
        _acce_vc_y = 0;
        _acce_vc_z = 0;
        _acce = _bottom_acce;
    } else {
        double acce_xyz = sqrt(p);
        if (acce_xyz > _top_acce) {
            double t = _top_acce/acce_xyz;
            _acce_vc_x = t * prm_acce_vc_x;
            _acce_vc_y = t * prm_acce_vc_y;
            _acce_vc_z = t * prm_acce_vc_z;
            _acce = _top_acce;
        } else if (acce_xyz < _bottom_acce) {
            double t = _bottom_acce/acce_xyz;
            _acce_vc_x = t * prm_acce_vc_x;
            _acce_vc_y = t * prm_acce_vc_y;
            _acce_vc_z = t * prm_acce_vc_z;
            _acce = _bottom_acce;
        } else {
            _acce_vc_x = prm_acce_vc_x;
            _acce_vc_y = prm_acce_vc_y;
            _acce_vc_z = prm_acce_vc_z;
            _acce = acce_xyz;
            return;
        }
    }
}

void NaviVehicle::setAcceZero() {
    _acce_vc_x = _bottom_acce;
    _acce_vc_y = 0;
    _acce_vc_z = 0;
    _acce = _bottom_acce;
}

void NaviVehicle::behave() {
    if (_acce != 0) {
        setVeloByVc(_velo_vc_x+_acce_vc_x,
                    _velo_vc_y+_acce_vc_y,
                    _velo_vc_z+_acce_vc_z);
    }
    //Actorに反映
    _pActor->_x += _velo_vc_x;
    _pActor->_y += _velo_vc_y;
    _pActor->_z += _velo_vc_z;
}

NaviVehicle::~NaviVehicle() {
}
