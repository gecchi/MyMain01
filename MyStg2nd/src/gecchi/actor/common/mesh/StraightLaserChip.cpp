#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
//    _pPosSourceActor = NULL;
//    _pAngleSourceActor = NULL;
}

void StraightLaserChip::initialize() {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _veloMove = 10000;
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
    _dwActiveFrame = 0;
}

void StraightLaserChip::onActive() {
    LaserChip::onActive();
    _dwActiveFrame = 0;
}

void StraightLaserChip::processBehavior() {
    _dwActiveFrame++;
    _RX = (*_pSource_RX);
    _RY = (*_pSource_RY);
    _RZ = (*_pSource_RZ);
    double vX,vY,vZ;
    GgafDx9Util::getNormalizeVectorZY(_RZ, _RY, vX, vY, vZ);

    _X = (*_pSource_X) + (vX * 1.0 * _veloMove * _dwActiveFrame);
    _Y = (*_pSource_Y) + (vY * 1.0 * _veloMove * _dwActiveFrame);
    _Z = (*_pSource_Z) + (vZ * 1.0 * _veloMove * _dwActiveFrame);

    //���W�ɔ��f
    //_pMover->behave();
/*
    //���Ԓn�_�ɂ������蔻��
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pStgChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //���Ԃ̓����蔻��
      _pStgChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pStgChecker->getHitAreaBoxs()->disable(1);

    }
*/

}

void StraightLaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivate();
    }

    //���[�U�[���  1:���� 2:���� 3:�擪 �i�������擪�͖������D��j
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActive()) {
                if (_pChip_front->_pChip_front) {
                    _chip_kind = 2; //���ԃe�N�X�`��
                } else {
                    _chip_kind = 3; //�擪�e�N�X�`��
                }
            } else {
                _chip_kind = 1; //���ˌ��̖����e�N�X�`��
            }
        } else {
            _chip_kind = 1; //�����e�N�X�`��
        }
    } else {
        _chip_kind = 4; //�����`�悵�����Ȃ�
    }


    GgafDx9GeometricActor::getWorldMatrix_ScMvRxRzRy(this, _matWorld);
}


StraightLaserChip::~StraightLaserChip() {

}

