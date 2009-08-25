#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _pSourceActor = NULL;
}
void StraightLaserChip::initialize() {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _pMover->setVxMoveVelocity(100000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}

void StraightLaserChip::onActive() {
    //�E�E�E
    _X_onActive = _X;
    _Y_onActive = _Y;
    _Z_onActive = _Z;
    _RX = _pSourceActor->_RX;
    _RY = _pSourceActor->_RY;
    _RZ = _pSourceActor->_RZ;
    _X = 0;
    _Y = 0;
    _Z = 0;

    //�o����
    _chip_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
        }
    }

    _pDispatcher->_num_chip_active++;

    GgafDx9GeometricActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);
    //����FK����낤�Ƃ��Ă�̂��H�I�E�E�E�E

    if (_pChip_front != NULL) {
        processPreJudgement();

    } else {
        _rev_pos_Z = 0;
    }

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

