#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
//    _pPosSourceActor = NULL;
//    _pAngleSourceActor = NULL;

    _pSource_X = &_X;
    _pSource_Y = &_Y;
    _pSource_Z = &_Z;
    _pSource_RX = &_RX;
    _pSource_RY = &_RY;
    _pSource_RZ = &_RZ;
    _pSource_vX = &_pMover->_vX;
    _pSource_vY = &_pMover->_vY;
    _pSource_vZ = &_pMover->_vZ;
    _veloMv = 100000;

}

void StraightLaserChip::initialize() {
    //下位レーザーチップでオーバーライトされている可能性あり
    _fAlpha = 0.99;
}

void StraightLaserChip::onActive() {
    LaserChip::onActive();
}

void StraightLaserChip::onInactive() {
    LaserChip::onInactive();
}

void StraightLaserChip::processBehavior() {
    LaserChip::processBehavior();

    _RX = (*_pSource_RX);
    _RY = (*_pSource_RY);
    _RZ = (*_pSource_RZ);
    _X = (*_pSource_X) + ((*_pSource_vX) * _veloMv * (int)getActivePartFrame());
    //_TRACE_("(*_pSource_X)="<<(*_pSource_X)<<" (*_pSource_vX)="<<(*_pSource_vX)<<" _veloMv="<<_veloMv<<" getActivePartFrame()="<<getActivePartFrame()<<" _X="<<_X);
    _Y = (*_pSource_Y) + ((*_pSource_vY) * _veloMv * (int)getActivePartFrame());
    _Z = (*_pSource_Z) + ((*_pSource_vZ) * _veloMv * (int)getActivePartFrame());

    //座標に反映
    //_pMover->behave();
/*
    //中間地点にも当たり判定
    static int centerX, centerY, centerZ;
    if (_pChip_front) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pCollisionChecker->setColliAAB(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //中間の当たり判定
      _pCollisionChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pCollisionChecker->getHitAreaBoxs()->disable(1);

    }
*/

}


void StraightLaserChip::processJudgement() {
    LaserChip::processJudgement();

}


StraightLaserChip::~StraightLaserChip() {

}

