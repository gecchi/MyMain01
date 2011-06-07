#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
// ＜軸方向移動: VxMv VyMv VzMv＞
// 上記の移動体系とはまったく別に、独立して X軸、Y軸、Z軸に平行な移動指定ができる。
// 「X軸方向移動速度」「Y軸方向移動速度」「Z軸方向移動速度」を設定すると、毎フレーム(_X,_Y,_Z)にそれぞれの移動増分が
// 加算される。



GgafDx9MvTransporter::GgafDx9MvTransporter(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _veloVxMv = 0;
    //X軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVxMv = 256 * LEN_UNIT;
    //X軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVxMv = -256 * LEN_UNIT;
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVxMv = 0;
    _acceTopVxMv = 256 * LEN_UNIT;
    _acceBottomVxMv = -256 * LEN_UNIT;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _veloVyMv = 0;
    //Y軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVyMv = 256 * LEN_UNIT;
    //Y軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVyMv = -256 * LEN_UNIT;
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVyMv = 0;

    _acceTopVyMv = 256 * LEN_UNIT;
    _acceBottomVyMv = -256 * LEN_UNIT;

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _veloVzMv = 0;
    //Z軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVzMv = 256 * LEN_UNIT;
    //Z軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVzMv = -256 * LEN_UNIT;
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVzMv = 0;
    _acceTopVzMv = 256 * LEN_UNIT;
    _acceBottomVzMv = -256 * LEN_UNIT;

    _gravitation_mv_seq_target_X = 0;
    _gravitation_mv_seq_target_Y = 0;
    _gravitation_mv_seq_target_Z = 0;
    _gravitation_mv_seq_pActor_target = NULL;
    _gravitation_mv_seq_max_velo = 1000;
    _gravitation_mv_seq_acce = 1000;
    _gravitation_mv_seq_stop_renge = 1000;
    _gravitation_mv_seq_flg = false;

}

void GgafDx9MvTransporter::behave() {



    if(_gravitation_mv_seq_flg) {
        int dX, dY, dZ;
        if (_gravitation_mv_seq_pActor_target) {
            dX = _gravitation_mv_seq_pActor_target->_X - _pActor->_X;
            dY = _gravitation_mv_seq_pActor_target->_Y - _pActor->_Y;
            dZ = _gravitation_mv_seq_pActor_target->_Z - _pActor->_Z;
        } else {
            dX = _gravitation_mv_seq_target_X - _pActor->_X;
            dY = _gravitation_mv_seq_target_Y - _pActor->_Y;
            dZ = _gravitation_mv_seq_target_Z - _pActor->_Z;
        }

        velo last_veloVxMv = _veloVxMv;
        velo new_veloVxMv = _gravitation_mv_seq_max_velo * (dX * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVxMv - _gravitation_mv_seq_acce <= new_veloVxMv &&
                                                        new_veloVxMv <= last_veloVxMv + _gravitation_mv_seq_acce) {
            _veloVxMv = new_veloVxMv;
        } else {
            if (last_veloVxMv - _gravitation_mv_seq_acce > new_veloVxMv) {
                _veloVxMv = last_veloVxMv - _gravitation_mv_seq_acce;
            } else if (new_veloVxMv > last_veloVxMv + _gravitation_mv_seq_acce) {
                _veloVxMv = last_veloVxMv + _gravitation_mv_seq_acce;
            }
        }

        velo last_veloVyMv = _veloVyMv;
        velo new_veloVyMv = _gravitation_mv_seq_max_velo * (dY * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVyMv - _gravitation_mv_seq_acce <= new_veloVyMv &&
                                                        new_veloVyMv <= last_veloVyMv + _gravitation_mv_seq_acce) {
            _veloVyMv = new_veloVyMv;
        } else {
            if (last_veloVyMv - _gravitation_mv_seq_acce > new_veloVyMv) {
                _veloVyMv = last_veloVyMv - _gravitation_mv_seq_acce;
            } else if (new_veloVyMv > last_veloVyMv + _gravitation_mv_seq_acce) {
                _veloVyMv = last_veloVyMv + _gravitation_mv_seq_acce;
            }
        }

        velo last_veloVzMv = _veloVzMv;
        velo new_veloVzMv = _gravitation_mv_seq_max_velo * (dZ * 1.0 / _gravitation_mv_seq_stop_renge);
        if (last_veloVzMv - _gravitation_mv_seq_acce <= new_veloVzMv &&
                                                        new_veloVzMv <= last_veloVzMv + _gravitation_mv_seq_acce) {
            _veloVzMv = new_veloVzMv;
        } else {
            if (last_veloVzMv - _gravitation_mv_seq_acce > new_veloVzMv) {
                _veloVzMv = last_veloVzMv - _gravitation_mv_seq_acce;
            } else if (new_veloVzMv > last_veloVzMv + _gravitation_mv_seq_acce) {
                _veloVzMv = last_veloVzMv + _gravitation_mv_seq_acce;
            }
        }
    }


    //X軸方向移動加速度の処理
    _veloVxMv += _acceVxMv;
    setVxMvVelo(_veloVxMv);
    //Y軸方向移動加速度の処理
    _veloVyMv += _acceVyMv;
    setVyMvVelo(_veloVyMv);
    //Z軸方向移動加速度の処理
    _veloVzMv += _acceVzMv;
    setVzMvVelo(_veloVzMv);

    //Actorに反映
    _pActor->_X += _veloVxMv;
    _pActor->_Y += _veloVyMv;
    _pActor->_Z += _veloVzMv;


}


int GgafDx9MvTransporter::dot(int prm_vX, int prm_vY, int prm_vZ) {
    return (prm_vX * _veloVxMv) + (prm_vY *_veloVyMv) + (prm_vZ*_veloVzMv);
}
void GgafDx9MvTransporter::forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02) {
    if (prm_veloVxMv01 < prm_veloVxMv02) {
        _veloTopVxMv = prm_veloVxMv02;
        _veloBottomVxMv = prm_veloVxMv01;
    } else {
        _veloTopVxMv = prm_veloVxMv01;
        _veloBottomVxMv = prm_veloVxMv02;
    }
    setVxMvVelo(_veloVxMv); //再設定して範囲内に補正
}

void GgafDx9MvTransporter::setVxMvVelo(velo prm_veloVxMv) {
    if (prm_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (prm_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    } else {
        _veloVxMv = prm_veloVxMv;
    }
}

void GgafDx9MvTransporter::addVxMvVelo(velo prm_veloVxMv) {
    _veloVxMv += prm_veloVxMv;
    if (_veloVxMv > _veloTopVxMv) {
        _veloVxMv = _veloTopVxMv;
    } else if (_veloVxMv < _veloBottomVxMv) {
        _veloVxMv = _veloBottomVxMv;
    }
}

void GgafDx9MvTransporter::setVxMvAcce(acce prm_acceVxMv) {
    if (prm_acceVxMv > _acceTopVxMv) {
        _acceVxMv = _acceTopVxMv;
    } else if (prm_acceVxMv < _acceBottomVxMv) {
        _acceVxMv = _acceBottomVxMv;
    } else {
        _acceVxMv = prm_acceVxMv;
    }
}

void GgafDx9MvTransporter::addVxMvAcce(acce prm_acceVxMv) {
    setVxMvAcce(_acceVxMv + prm_acceVxMv);
}


void GgafDx9MvTransporter::forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02) {
    if (prm_acceVxMv01 < prm_acceVxMv02) {
        _acceTopVxMv = prm_acceVxMv02;
        _acceBottomVxMv = prm_acceVxMv01;
    } else {
        _acceTopVxMv = prm_acceVxMv01;
        _acceBottomVxMv = prm_acceVxMv02;
    }
    setVxMvAcce(_acceVxMv); //再設定して範囲内に補正
}


void GgafDx9MvTransporter::forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02) {
    if (prm_veloVyMv01 < prm_veloVyMv02) {
        _veloTopVyMv = prm_veloVyMv02;
        _veloBottomVyMv = prm_veloVyMv01;
    } else {
        _veloTopVyMv = prm_veloVyMv01;
        _veloBottomVyMv = prm_veloVyMv02;
    }
    setVyMvVelo(_veloVyMv); //再設定して範囲内に補正
}

void GgafDx9MvTransporter::setVyMvVelo(velo prm_veloVyMv) {
    if (prm_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (prm_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    } else {
        _veloVyMv = prm_veloVyMv;
    }
}

void GgafDx9MvTransporter::addVyMvVelo(velo prm_veloVyMv) {
    _veloVyMv += prm_veloVyMv;
    if (_veloVyMv > _veloTopVyMv) {
        _veloVyMv = _veloTopVyMv;
    } else if (_veloVyMv < _veloBottomVyMv) {
        _veloVyMv = _veloBottomVyMv;
    }
}

void GgafDx9MvTransporter::setVyMvAcce(acce prm_acceVyMv) {
    if (prm_acceVyMv > _acceTopVyMv) {
        _acceVyMv = _acceTopVyMv;
    } else if (prm_acceVyMv < _acceBottomVyMv) {
        _acceVyMv = _acceBottomVyMv;
    } else {
        _acceVyMv = prm_acceVyMv;
    }
}

void GgafDx9MvTransporter::addVyMvAcce(acce prm_acceVyMv) {
    setVyMvAcce(_acceVyMv + prm_acceVyMv);
}


void GgafDx9MvTransporter::forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02) {
    if (prm_acceVyMv01 < prm_acceVyMv02) {
        _acceTopVyMv = prm_acceVyMv02;
        _acceBottomVyMv = prm_acceVyMv01;
    } else {
        _acceTopVyMv = prm_acceVyMv01;
        _acceBottomVyMv = prm_acceVyMv02;
    }
    setVyMvAcce(_acceVyMv); //再設定して範囲内に補正
}

void GgafDx9MvTransporter::forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02) {
    if (prm_veloVzMv01 < prm_veloVzMv02) {
        _veloTopVzMv = prm_veloVzMv02;
        _veloBottomVzMv = prm_veloVzMv01;
    } else {
        _veloTopVzMv = prm_veloVzMv01;
        _veloBottomVzMv = prm_veloVzMv02;
    }
    setVzMvVelo(_veloVzMv); //再設定して範囲内に補正
}

void GgafDx9MvTransporter::setVzMvVelo(velo prm_veloVzMv) {
    if (prm_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (prm_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    } else {
        _veloVzMv = prm_veloVzMv;
    }
}

void GgafDx9MvTransporter::addVzMvVelo(velo prm_veloVzMv) {
    _veloVzMv += prm_veloVzMv;
    if (_veloVzMv > _veloTopVzMv) {
        _veloVzMv = _veloTopVzMv;
    } else if (_veloVzMv < _veloBottomVzMv) {
        _veloVzMv = _veloBottomVzMv;
    }
}

void GgafDx9MvTransporter::setVzMvAcce(acce prm_acceVzMv) {
    if (prm_acceVzMv > _acceTopVzMv) {
        _acceVzMv = _acceTopVzMv;
    } else if (prm_acceVzMv < _acceBottomVzMv) {
        _acceVzMv = _acceBottomVzMv;
    } else {
        _acceVzMv = prm_acceVzMv;
    }
}

void GgafDx9MvTransporter::addVzMvAcce(acce prm_acceVzMv) {
    setVzMvAcce(_acceVzMv + prm_acceVzMv);
}


void GgafDx9MvTransporter::forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02) {
    if (prm_acceVzMv01 < prm_acceVzMv02) {
        _acceTopVzMv = prm_acceVzMv02;
        _acceBottomVzMv = prm_acceVzMv01;
    } else {
        _acceTopVzMv = prm_acceVzMv01;
        _acceBottomVzMv = prm_acceVzMv02;
    }
    setVzMvAcce(_acceVzMv); //再設定して範囲内に補正
}



void GgafDx9MvTransporter::forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02) {
    forceVxMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
    forceVyMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
    forceVzMvVeloRange(prm_veloVxyzMv01, prm_veloVxyzMv02);
}
void GgafDx9MvTransporter::forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02) {
    forceVxMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVyMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
    forceVzMvAcceRange(prm_acceVxyzMv01, prm_acceVxyzMv02);
}











void GgafDx9MvTransporter::execGravitationVxyzMvSequence(
        int prm_tX, int prm_tY, int prm_tZ,
        velo prm_max_velo,
        acce prm_acce,
        int prm_stop_renge
        ) {
    _gravitation_mv_seq_target_X = prm_tX;
    _gravitation_mv_seq_target_Y = prm_tY;
    _gravitation_mv_seq_target_Z = prm_tZ;
    _gravitation_mv_seq_pActor_target = NULL;
    _gravitation_mv_seq_max_velo = prm_max_velo;
    _gravitation_mv_seq_acce = prm_acce;
    _gravitation_mv_seq_stop_renge = prm_stop_renge;
    _gravitation_mv_seq_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}

void GgafDx9MvTransporter::execGravitationVxyzMvSequence(
        GgafDx9GeometricActor* prm_pActor_target,
        velo prm_max_velo,
        acce prm_acce,
        int prm_stop_renge
        ) {
    _gravitation_mv_seq_target_X = 0;
    _gravitation_mv_seq_target_Y = 0;
    _gravitation_mv_seq_target_Z = 0;
    _gravitation_mv_seq_pActor_target = prm_pActor_target;
    _gravitation_mv_seq_max_velo = prm_max_velo;
    _gravitation_mv_seq_acce = prm_acce;
    _gravitation_mv_seq_stop_renge = prm_stop_renge;
    _gravitation_mv_seq_flg = true;

    forceVxMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVyMvVeloRange(-prm_max_velo, prm_max_velo);
    forceVzMvVeloRange(-prm_max_velo, prm_max_velo);
}



void GgafDx9MvTransporter::takeoverMvFrom(GgafDx9MvTransporter* prm_pMvTransporter) {

    // X軸方向移動速度
    _veloVxMv = prm_pMvTransporter->_veloVxMv;
    // X軸方向移動速度上限
    _veloTopVxMv = prm_pMvTransporter->_veloTopVxMv;
    // X軸方向移動速度下限
    _veloBottomVxMv = prm_pMvTransporter->_veloBottomVxMv;
    // X軸方向移動加速度
    _acceVxMv = prm_pMvTransporter->_acceVxMv;
    // X軸方向移動加速度上限
    _acceTopVxMv = prm_pMvTransporter->_acceTopVxMv;
    // X軸方向移動加速度下限
    _acceBottomVxMv = prm_pMvTransporter->_acceBottomVxMv;
    // Y軸方向移動速度
    _veloVyMv = prm_pMvTransporter->_veloVyMv;
    // Y軸方向移動速度上限
    _veloTopVyMv = prm_pMvTransporter->_veloTopVyMv;
    // Y軸方向移動速度下限
    _veloBottomVyMv = prm_pMvTransporter->_veloBottomVyMv;
    // Y軸方向移動加速度
    _acceVyMv = prm_pMvTransporter->_acceVyMv;
    // Y軸方向移動加速度上限
    _acceTopVyMv = prm_pMvTransporter->_acceTopVyMv;
    // Y軸方向移動加速度下限
    _acceBottomVyMv = prm_pMvTransporter->_acceBottomVyMv;
    // Z軸方向移動速度
    _veloVzMv = prm_pMvTransporter->_veloVzMv;
    // Z軸方向移動速度上限
    _veloTopVzMv = prm_pMvTransporter->_veloTopVzMv;
    // Z軸方向移動速度下限
    _veloBottomVzMv = prm_pMvTransporter->_veloBottomVzMv;
    // Z軸方向移動加速度
    _acceVzMv = prm_pMvTransporter->_acceVzMv;
    // Z軸方向移動加速度上限
    _acceTopVzMv = prm_pMvTransporter->_acceTopVzMv;
    // Z軸方向移動加速度下限
    _acceBottomVzMv = prm_pMvTransporter->_acceBottomVzMv;

}

void GgafDx9MvTransporter::resetMv() {


    //X軸方向移動速度（X移動座標増分）＝ 0 px/fream
    _veloVxMv = 0;
    //X軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVxMv = 256 * LEN_UNIT;
    //X軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVxMv = -256 * LEN_UNIT;
    //X軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVxMv = 0;
    _acceTopVxMv = 256 * LEN_UNIT;
    _acceBottomVxMv = -256 * LEN_UNIT;
    //Y軸方向移動速度（Y移動座標増分）＝ 0 px/fream
    _veloVyMv = 0;
    //Y軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVyMv = 256 * LEN_UNIT;
    //Y軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVyMv = -256 * LEN_UNIT;
    //Y軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVyMv = 0;

    _acceTopVyMv = 256 * LEN_UNIT;
    _acceBottomVyMv = -256 * LEN_UNIT;

    //Z軸方向移動速度（Z移動座標増分）＝ 0 px/fream
    _veloVzMv = 0;
    //Z軸方向移動速度上限 ＝ 256 px/fream
    _veloTopVzMv = 256 * LEN_UNIT;
    //Z軸方向移動速度下限 ＝ 256 px/fream
    _veloBottomVzMv = -256 * LEN_UNIT;
    //Z軸方向移動速度の加速度 ＝ 0 px/fream^2  (加速無し)
    _acceVzMv = 0;
    _acceTopVzMv = 256 * LEN_UNIT;
    _acceBottomVzMv = -256 * LEN_UNIT;
}

GgafDx9MvTransporter::~GgafDx9MvTransporter() {
}
