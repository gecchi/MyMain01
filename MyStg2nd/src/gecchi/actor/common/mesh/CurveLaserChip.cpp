#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CurveLaserChip::CurveLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "CurveLaserChip";
}

void CurveLaserChip::initialize() {
    //���ʃ��[�U�[�`�b�v�ŃI�[�o�[���C�g����Ă���\������
    _pMover->setMoveVelocity(40000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}


void CurveLaserChip::onActive() {
    LaserChip::onActive();
}

void CurveLaserChip::onInactive() {
    LaserChip::onInactive();
}

void CurveLaserChip::processBehavior() {
    _dwActiveFrame++;
    //���W�ɔ��f
    if (_dwActiveFrame > 1) {
        _pMover->behave();
    }
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

void CurveLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //�y���Ӂz4/15 ����
    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
    //processBehavior,processJudgement�� _pChip_front ���K����Ɏ��s�����B
    //�`�掞��_pChip_front���g�p���邽�߂����Őݒ肵�Ƃ��K�v������B
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

CurveLaserChip::~CurveLaserChip() {
}

