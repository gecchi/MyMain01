#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _pSourceActor = nullptr;
    source_x = _x;
    source_y = _y;
    source_z = _y;
    source_rx = _rx;
    source_ry = _ry;
    source_rz = _rz;
    _pSource_x = &_x;
    _pSource_y = &_y;
    _pSource_z = &_z;
    _pSource_rx = &_rx;
    _pSource_ry = &_ry;
    _pSource_rz = &_rz;
    _veloMv = 100000;
}

void StraightLaserChip::processSettlementBehavior() {
    //各アクターの座標移動が完了した後に実行したい
    if (_pSourceActor) {
        //発射元アクターが消失する場合
        if (_pSourceActor->wasDeclaredEnd()) {
            _pSourceActor = nullptr;
            //バックアップ
            source_x = (*_pSource_x);
            source_y = (*_pSource_y);
            source_z = (*_pSource_z);
            source_rx = (*_pSource_rx);
            source_ry = (*_pSource_ry);
            source_rz = (*_pSource_rz);
            //不正ポインタを回避するため元のメンバー参照に戻しておく
            _pSource_x = &_x;
            _pSource_y = &_y;
            _pSource_z = &_z;
            _pSource_rx = &_rx;
            _pSource_ry = &_ry;
            _pSource_rz = &_rz;
        }
    }

    if (_pSourceActor) {
        //発射元アクターが活動中の場合
        _rx = (*_pSource_rx);
        _ry = (*_pSource_ry);
        _rz = (*_pSource_rz);
        float vx, vy, vz;
        UTIL::convRzRyToVector(_rz, _ry,
                                vx, vy, vz);
        velo v = _veloMv * ((velo)getActiveFrame()-1);
        _x = (*_pSource_x) + (vx * v );
        _y = (*_pSource_y) + (vy * v );
        _z = (*_pSource_z) + (vz * v );
    } else {
        //発射元アクターが非活動中の場合
        _rx = source_x;
        _ry = source_y;
        _rz = source_z;
        float vx, vy, vz;
        UTIL::convRzRyToVector(source_rz, source_ry,
                                vx, vy, vz);
        velo v = _veloMv * ((velo)getActiveFrame()-1);
        _x = source_x + (vx * v );
        _y = source_y + (vy * v );
        _z = source_z + (vz * v );
    }

    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void StraightLaserChip::setMvVelo(coord prm_velo) {
    _veloMv = prm_velo;
}

StraightLaserChip::~StraightLaserChip() {

}

