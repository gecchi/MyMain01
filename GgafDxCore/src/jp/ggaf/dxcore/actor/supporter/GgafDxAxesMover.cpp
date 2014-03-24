#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverHelperA.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
// ���������ړ�: VxMv VyMv VzMv��
// ��L�̈ړ��̌n�Ƃ͂܂������ʂɁA�Ɨ����� X���AY���AZ���ɕ��s�Ȉړ��w�肪�ł���B
// �uX�������ړ����x�v�uY�������ړ����x�v�uZ�������ړ����x�v��ݒ肷��ƁA���t���[��(_x,_y,_z)�ɂ��ꂼ��̈ړ�������
// ���Z�����B

GgafDxAxesMover::GgafDxAxesMover(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {
    _pHlprA = nullptr;
    //X�������ړ����x�iX�ړ����W�����j�� 0 px/fream
    _veloVxMv = 0;
    //X�������ړ����x���
    _veloTopVxMv = INT_MAX;
    //X�������ړ����x����
    _veloBottomVxMv = INT_MIN;
    //X�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVxMv = 0;
    _acceTopVxMv = INT_MAX;
    _acceBottomVxMv = INT_MIN;
    //Y�������ړ����x�iY�ړ����W�����j�� 0 px/fream
    _veloVyMv = 0;
    //Y�������ړ����x���
    _veloTopVyMv = INT_MAX;
    //Y�������ړ����x����
    _veloBottomVyMv = INT_MIN;
    //Y�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVyMv = 0;

    _acceTopVyMv = INT_MAX;
    _acceBottomVyMv = INT_MIN;

    //Z�������ړ����x�iZ�ړ����W�����j�� 0 px/fream
    _veloVzMv = 0;
    //Z�������ړ����x���
    _veloTopVzMv = INT_MAX;
    //Z�������ړ����x����
    _veloBottomVzMv = INT_MIN;
    //Z�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVzMv = 0;
    _acceTopVzMv = INT_MAX;
    _acceBottomVzMv = INT_MIN;

    _grv_mv_target_x = 0;
    _grv_mv_target_y = 0;
    _grv_mv_target_z = 0;
    _grv_mv_pActor_target = nullptr;
    _grv_mv_max_velo = 1000;
    _grv_mv_acce = 1000;
    _grv_mv_stop_renge = 1000;
    _grv_mv_flg = false;

}

GgafDxAxesMoverHelperA* GgafDxAxesMover::hlprA() {
    return _pHlprA ? _pHlprA : _pHlprA = NEW GgafDxAxesMoverHelperA(this);
}

void GgafDxAxesMover::behave() {
    if (_pHlprA) {
        _pHlprA->behave();
    }

    if(_grv_mv_flg) {
        coord dX, dY, dZ;
        if (_grv_mv_pActor_target) {
            dX = _grv_mv_pActor_target->_x - _pActor->_x;
            dY = _grv_mv_pActor_target->_y - _pActor->_y;
            dZ = _grv_mv_pActor_target->_z - _pActor->_z;
        } else {
            dX = _grv_mv_target_x - _pActor->_x;
            dY = _grv_mv_target_y - _pActor->_y;
            dZ = _grv_mv_target_z - _pActor->_z;
        }
        coord dX_abs = ABS(dX);
        coord dY_abs = ABS(dY);
        coord dZ_abs = ABS(dZ);
        coord dmax = MAX3(dX_abs, dY_abs, dZ_abs);//�����ȈՌv�Z
        if (dmax > _grv_mv_max_velo) {
            double rr = 1.0*_grv_mv_max_velo / dmax;
            dX *= rr;
            dY *= rr;
            dZ *= rr;
        }
        double r_acce = 1.7*_grv_mv_acce / dmax;
        acce X_acce = r_acce * dX_abs;
        acce Y_acce = r_acce * dY_abs;
        acce Z_acce = r_acce * dZ_abs;
        if (X_acce > _grv_mv_acce) {
            X_acce = _grv_mv_acce;
        }
        if (Y_acce > _grv_mv_acce) {
            Y_acce = _grv_mv_acce;
        }
        if (Z_acce > _grv_mv_acce) {
            Z_acce = _grv_mv_acce;
        }
        velo last_veloVxMv = _veloVxMv;
        velo new_veloVxMv = _grv_mv_max_velo * (dX * 1.0 / _grv_mv_stop_renge);
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
        velo new_veloVyMv = _grv_mv_max_velo * (dY * 1.0 / _grv_mv_stop_renge);
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
        velo new_veloVzMv = _grv_mv_max_velo * (dZ * 1.0 / _grv_mv_stop_renge);
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

    //Actor�ɔ��f
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
    setVxMvVelo(_veloVxMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
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
    setVxMvAcce(_acceVxMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxAxesMover::forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02) {
    if (prm_veloVyMv01 < prm_veloVyMv02) {
        _veloTopVyMv = prm_veloVyMv02;
        _veloBottomVyMv = prm_veloVyMv01;
    } else {
        _veloTopVyMv = prm_veloVyMv01;
        _veloBottomVyMv = prm_veloVyMv02;
    }
    setVyMvVelo(_veloVyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
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
    setVyMvAcce(_acceVyMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void GgafDxAxesMover::forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02) {
    if (prm_veloVzMv01 < prm_veloVzMv02) {
        _veloTopVzMv = prm_veloVzMv02;
        _veloBottomVzMv = prm_veloVzMv01;
    } else {
        _veloTopVzMv = prm_veloVzMv01;
        _veloBottomVzMv = prm_veloVzMv02;
    }
    setVzMvVelo(_veloVzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
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
    setVzMvAcce(_acceVzMv); //�Đݒ肵�Ĕ͈͓��ɕ␳
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
    //�Đݒ肵�Ĕ͈͓��ɕ␳
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
coord GgafDxAxesMover::setVxAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _veloVxMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setVxMvAcce(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_veloVxMv + prm_target_velo) * prm_target_frames) / 2 ;
}
coord GgafDxAxesMover::setVyAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _veloVyMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setVyMvAcce(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_veloVyMv + prm_target_velo) * prm_target_frames) / 2 ;
}
coord GgafDxAxesMover::setVzAcceByT(frame prm_target_frames, velo prm_target_velo) {
    double acc = UTIL::getAcceByTv(prm_target_frames, _veloVzMv, prm_target_velo);
    if (acc > 0.0) {
        acc += 0.5;
    } else if (acc < 0.0) {
        acc -= 0.5;
    }
    setVzMvAcce(acc);
    //  D = (1/2) (Vo + Vt) Te
    return ((_veloVzMv + prm_target_velo) * prm_target_frames) / 2 ;
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

void GgafDxAxesMover::execGravitationMvSequenceTwd(GgafDxGeometricActor* prm_pActor_target,
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

void GgafDxAxesMover::takeoverMvFrom(GgafDxAxesMover* const prmpAxsMver_) {

    // X�������ړ����x
    _veloVxMv = prmpAxsMver_->_veloVxMv;
    // X�������ړ����x���
    _veloTopVxMv = prmpAxsMver_->_veloTopVxMv;
    // X�������ړ����x����
    _veloBottomVxMv = prmpAxsMver_->_veloBottomVxMv;
    // X�������ړ������x
    _acceVxMv = prmpAxsMver_->_acceVxMv;
    // X�������ړ������x���
    _acceTopVxMv = prmpAxsMver_->_acceTopVxMv;
    // X�������ړ������x����
    _acceBottomVxMv = prmpAxsMver_->_acceBottomVxMv;
    // Y�������ړ����x
    _veloVyMv = prmpAxsMver_->_veloVyMv;
    // Y�������ړ����x���
    _veloTopVyMv = prmpAxsMver_->_veloTopVyMv;
    // Y�������ړ����x����
    _veloBottomVyMv = prmpAxsMver_->_veloBottomVyMv;
    // Y�������ړ������x
    _acceVyMv = prmpAxsMver_->_acceVyMv;
    // Y�������ړ������x���
    _acceTopVyMv = prmpAxsMver_->_acceTopVyMv;
    // Y�������ړ������x����
    _acceBottomVyMv = prmpAxsMver_->_acceBottomVyMv;
    // Z�������ړ����x
    _veloVzMv = prmpAxsMver_->_veloVzMv;
    // Z�������ړ����x���
    _veloTopVzMv = prmpAxsMver_->_veloTopVzMv;
    // Z�������ړ����x����
    _veloBottomVzMv = prmpAxsMver_->_veloBottomVzMv;
    // Z�������ړ������x
    _acceVzMv = prmpAxsMver_->_acceVzMv;
    // Z�������ړ������x���
    _acceTopVzMv = prmpAxsMver_->_acceTopVzMv;
    // Z�������ړ������x����
    _acceBottomVzMv = prmpAxsMver_->_acceBottomVzMv;

}
void GgafDxAxesMover::stopMv() {
    setZeroVxyzMvVelo();
    setZeroVxyzMvAcce();
    stopGravitationMvSequence();
    if (_pHlprA) {
        _pHlprA->stopSlidingMv();
    }
}
void GgafDxAxesMover::resetMv() {
    //X�������ړ����x�iX�ړ����W�����j�� 0 px/fream
    _veloVxMv = 0;
    //X�������ړ����x��� �� 256 px/fream
    _veloTopVxMv = INT_MAX;
    //X�������ړ����x���� �� 256 px/fream
    _veloBottomVxMv = INT_MIN;
    //X�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVxMv = 0;
    _acceTopVxMv = INT_MAX;
    _acceBottomVxMv = INT_MIN;
    //Y�������ړ����x�iY�ړ����W�����j�� 0 px/fream
    _veloVyMv = 0;
    //Y�������ړ����x��� �� 256 px/fream
    _veloTopVyMv = INT_MAX;
    //Y�������ړ����x���� �� 256 px/fream
    _veloBottomVyMv = INT_MIN;
    //Y�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVyMv = 0;

    _acceTopVyMv = INT_MAX;
    _acceBottomVyMv = INT_MIN;

    //Z�������ړ����x�iZ�ړ����W�����j�� 0 px/fream
    _veloVzMv = 0;
    //Z�������ړ����x��� �� 256 px/fream
    _veloTopVzMv = INT_MAX;
    //Z�������ړ����x���� �� 256 px/fream
    _veloBottomVzMv = INT_MIN;
    //Z�������ړ����x�̉����x �� 0 px/fream^2  (��������)
    _acceVzMv = 0;
    _acceTopVzMv = INT_MAX;
    _acceBottomVzMv = INT_MIN;

    _grv_mv_flg = false;
}

GgafDxAxesMover::~GgafDxAxesMover() {
    GGAF_DELETE_NULLABLE(_pHlprA);
}