#include "jp/ggaf/dx/actor/supporter/GeoVehicle.h"

#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;

GeoVehicle::GeoVehicle(GeometricActor* prm_pActor)  : ActorVehicle(prm_pActor) {
    _velo_x = 0;
    _velo_y = 0;
    _velo_z = 0;
    _acce_x = 0;
    _acce_y = 0;
    _acce_z = 0;
    //à⁄ìÆë¨ìxè„å¿
    _top_velo = INT_MAX;
    //à⁄ìÆë¨ìxâ∫å¿
    _bottom_velo = 0;
    //à⁄ìÆâ¡ë¨ìxè„å¿
    _top_acce = INT_MAX;
    //à⁄ìÆâ¡ë¨ìxâ∫å¿
    _bottom_acce = 0;

    _velo = 0;
    _acce = 0;
}


void GeoVehicle::forceVeloRange(velo prm_velo01, velo prm_velo02) {
    if (prm_velo01 < prm_velo02) {
        _top_velo = prm_velo02;
        _bottom_velo = prm_velo01;
    } else {
        _top_velo = prm_velo01;
        _bottom_velo = prm_velo02;
    }
#ifdef MY_DEBUG
    if (_top_velo == 0 ) {
        _TRACE_("ÅyåxçêÅzGeoVehicle::forceVeloRange() ÅB_top_velo Ç™ 0 Ç¡ÇƒÇ®Ç©ÇµÇ¢ÇÃÇ≈ÇÕÅH prm_velo01="<<prm_velo01<<",prm_velo02="<<prm_velo02<<"");
    }
#endif
    //çƒê›íËÇµÇƒîÕàÕì‡Ç…ï‚ê≥
    setVelo(_velo_x, _velo_y, _velo_z);
}

void GeoVehicle::forceAcceRange(acce prm_acce01, acce prm_acce02) {
    if (prm_acce01 < prm_acce02) {
        _top_acce = prm_acce02;
        _bottom_acce = prm_acce01;
    } else {
        _top_acce = prm_acce01;
        _bottom_acce = prm_acce02;
    }
    //çƒê›íËÇµÇƒîÕàÕì‡Ç…ï‚ê≥
    setAcce(_acce_x, _acce_y, _acce_z);
}


void GeoVehicle::setVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo) {
    double vx = prm_tx - _pActor->_x;
    double vy = prm_ty - _pActor->_y;
    double vz = prm_tz - _pActor->_z;
    double p = vx*vx + vy*vy + vz*vz;
    if (ZEROd_EQ(p)) {
        if (_acce == 0) {
            _velo_x = _bottom_velo;
            _velo_y = 0;
            _velo_z = 0;
            _velo = _bottom_velo;
            return;
        }
        p = 1.0*_acce_x*_acce_x + 1.0*_acce_y*_acce_y + 1.0*_acce_z*_acce_z;
        if (ZEROd_EQ(p)) {
            _velo_x = _bottom_velo;
            _velo_y = 0;
            _velo_z = 0;
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
    if (velo_xyz == 0) {
        _velo_x = _bottom_velo;
        _velo_y = 0;
        _velo_z = 0;
        _velo = _bottom_velo;
    } else {
        double t = (velo_xyz / sqrt(p));
        _velo_x = t * vx;
        _velo_y = t * vy;
        _velo_z = t * vz;
        _velo = velo_xyz;
    }
}

void GeoVehicle::setVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo) {
    float vx, vy, vz;
    UTIL::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    setVelo(vx*prm_velo, vy*prm_velo, vz*prm_velo);
}

void GeoVehicle::setVelo(velo prm_velo_x, velo prm_velo_y, velo prm_velo_z) {
    double p = 1.0*prm_velo_x*prm_velo_x + 1.0*prm_velo_y*prm_velo_y + 1.0*prm_velo_z*prm_velo_z;
    if (ZEROd_EQ(p)) {
        if (_acce == 0) {
            _velo_x = _bottom_velo;
            _velo_y = 0;
            _velo_z = 0;
            _velo = _bottom_velo;
            return;
        }
        p = 1.0*_acce_x*_acce_x + 1.0*_acce_y*_acce_y + 1.0*_acce_z*_acce_z;
        if (ZEROd_EQ(p)) {
            _velo_x = _bottom_velo;
            _velo_y = 0;
            _velo_z = 0;
            _velo = _bottom_velo;
            return;
        }
    }
    double velo_xyz = sqrt(p);
    if (velo_xyz > _top_velo) {
        double t = _top_velo/velo_xyz;
        _velo_x = t * prm_velo_x;
        _velo_y = t * prm_velo_y;
        _velo_z = t * prm_velo_z;
        _velo = _top_velo;
        return;
    } else if (velo_xyz < _bottom_velo) {
        double t = _bottom_velo/velo_xyz;
        _velo_x = t * prm_velo_x;
        _velo_y = t * prm_velo_y;
        _velo_z = t * prm_velo_z;
        _velo = _bottom_velo;
        return;
    } else {
        double t = 1.0;
        _velo_x = t * prm_velo_x;
        _velo_y = t * prm_velo_y;
        _velo_z = t * prm_velo_z;
        _velo = velo_xyz;
        return;
    }
}
void GeoVehicle::setVeloZero() {
    setVelo(0,0,0);
}

void GeoVehicle::setAcceTwd(coord prm_tx, coord prm_ty, coord prm_tz, acce prm_acce) {
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
        _acce_x = _bottom_acce;
        _acce_y = 0;
        _acce_z = 0;
        _acce = _bottom_acce;
    } else {
        double t = (acce_xyz / sqrt(vx*vx + vy*vy + vz*vz));
        _acce_x = t * vx;
        _acce_y = t * vy;
        _acce_z = t * vz;
        _acce = acce_xyz;
    }
}

void GeoVehicle::setAcce(acce prm_acce_x, acce prm_acce_y, acce prm_acce_z) {
    double p = 1.0 * prm_acce_x * prm_acce_x + 1.0 * prm_acce_y * prm_acce_y + 1.0 * prm_acce_z * prm_acce_z;
    if (ZEROd_EQ(p)) {
        _acce_x = _bottom_acce;
        _acce_y = 0;
        _acce_z = 0;
        _acce = _bottom_acce;
    } else {
        double acce_xyz = sqrt(p);
        if (acce_xyz > _top_acce) {
            double t = _top_acce/acce_xyz;
            _acce_x = t * prm_acce_x;
            _acce_y = t * prm_acce_y;
            _acce_z = t * prm_acce_z;
            _acce = _top_acce;
        } else if (acce_xyz < _bottom_acce) {
            double t = _bottom_acce/acce_xyz;
            _acce_x = t * prm_acce_x;
            _acce_y = t * prm_acce_y;
            _acce_z = t * prm_acce_z;
            _acce = _bottom_acce;
        } else {
            double t = 1.0;
            _acce_x = t * prm_acce_x;
            _acce_y = t * prm_acce_y;
            _acce_z = t * prm_acce_z;
            _acce = acce_xyz;
            return;
        }
    }
}
void GeoVehicle::setAcceZero() {
    _acce_x = _bottom_acce;
    _acce_y = 0;
    _acce_z = 0;
    _acce = _bottom_acce;
}


void GeoVehicle::behave() {
    if (_acce != 0) {
        setVelo(_velo_x+_acce_x, _velo_y+_acce_y, _velo_z+_acce_z);
    }
    //ActorÇ…îΩâf
    _pActor->_x += _velo_x;
    _pActor->_y += _velo_y;
    _pActor->_z += _velo_z;
}


GeoVehicle::~GeoVehicle() {
}
