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
    _pSource_X = &_X;
    _pSource_Y = &_Y;
    _pSource_Z = &_Z;
    _pSource_RX = &_RX;
    _pSource_RY = &_RY;
    _pSource_RZ = &_RZ;
    _pSource_vX = &_pKurokoA->_vX;
    _pSource_vY = &_pKurokoA->_vY;
    _pSource_vZ = &_pKurokoA->_vZ;
    _veloMv = 100000;
}

void StraightLaserChip::processBehavior() {
    _RX = (*_pSource_RX);
    _RY = (*_pSource_RY);
    _RZ = (*_pSource_RZ);
    _X = (*_pSource_X) + ((*_pSource_vX) * _veloMv * (int)getActiveFrame());
    //_TRACE_("(*_pSource_X)="<<(*_pSource_X)<<" (*_pSource_vX)="<<(*_pSource_vX)<<" _veloMv="<<_veloMv<<" getActiveFrame()="<<getActiveFrame()<<" _X="<<_X);
    _Y = (*_pSource_Y) + ((*_pSource_vY) * _veloMv * (int)getActiveFrame());
    _Z = (*_pSource_Z) + ((*_pSource_vZ) * _veloMv * (int)getActiveFrame());
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

