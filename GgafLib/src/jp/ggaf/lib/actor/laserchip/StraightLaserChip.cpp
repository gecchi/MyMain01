#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    LaserChip(prm_name, prm_model, prm_pStat) {
//    _pPosSourceActor = NULL;
//    _pAngleSourceActor = NULL;
    _pSourceActor = NULL;
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

void StraightLaserChip::initialize() {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
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
//    if (string(_pSourceActor->getName()) == "MY_OPTION04") {
//        _TRACE_("_pSource_RX="<<_pSource_RX<<"  (*_pSource_RX)="<<(*_pSource_RX));
//    }
    _RX = (*_pSource_RX);
    _RY = (*_pSource_RY);
    _RZ = (*_pSource_RZ);
    _X = (*_pSource_X) + ((*_pSource_vX) * _veloMv * (int)getActivePartFrame());
    //_TRACE_("(*_pSource_X)="<<(*_pSource_X)<<" (*_pSource_vX)="<<(*_pSource_vX)<<" _veloMv="<<_veloMv<<" getActivePartFrame()="<<getActivePartFrame()<<" _X="<<_X);
    _Y = (*_pSource_Y) + ((*_pSource_vY) * _veloMv * (int)getActivePartFrame());
    _Z = (*_pSource_Z) + ((*_pSource_vZ) * _veloMv * (int)getActivePartFrame());

    //���W�ɔ��f
    //_pKurokoA->behave();
/*
    //���Ԓn�_�ɂ������蔻��
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
                 ); //���Ԃ̓����蔻��
      _pCollisionChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pCollisionChecker->getHitAreaBoxs()->disable(1);

    }
*/

}

void StraightLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void StraightLaserChip::processJudgement() {
    LaserChip::processJudgement();

}


StraightLaserChip::~StraightLaserChip() {

}
