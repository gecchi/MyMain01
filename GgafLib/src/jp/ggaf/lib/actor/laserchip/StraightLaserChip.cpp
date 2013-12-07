#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
//    _pPosSourceActor = nullptr;
//    _pAngleSourceActor = nullptr;
    _pSourceActor = nullptr;
    _pSource_x = &_x;
    _pSource_y = &_y;
    _pSource_z = &_z;
    _pSource_rx = &_rx;
    _pSource_ry = &_ry;
    _pSource_rz = &_rz;
    _pSource_vX = &_pKuroko->_vX;
    _pSource_vY = &_pKuroko->_vY;
    _pSource_vZ = &_pKuroko->_vZ;
    _veloMv = 100000;
}

void StraightLaserChip::processBehavior() {
    if (_pSourceActor) {
        if (_pSourceActor->wasDeclaredEnd()) {
            _pSourceActor = nullptr;
            _pSource_x = &_x;
            _pSource_y = &_y;
            _pSource_z = &_z;
            _pSource_rx = &_rx;
            _pSource_ry = &_ry;
            _pSource_rz = &_rz;
            _pSource_vX = &_pKuroko->_vX;
            _pSource_vY = &_pKuroko->_vY;
            _pSource_vZ = &_pKuroko->_vZ;
        } else {
            _rx = (*_pSource_rx);
            _ry = (*_pSource_ry);
            _rz = (*_pSource_rz);
            velo v = _veloMv * (velo)getActiveFrame();
            _x = (*_pSource_x) + ((*_pSource_vX) * v );
            _y = (*_pSource_y) + ((*_pSource_vY) * v );
            _z = (*_pSource_z) + ((*_pSource_vZ) * v );
        }
    }
}

void StraightLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

StraightLaserChip::~StraightLaserChip() {

}

