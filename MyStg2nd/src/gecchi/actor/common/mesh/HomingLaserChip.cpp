#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "HomingLaserChip";
}

void HomingLaserChip::initialize() {
    //�����ݒ�ł��B
    //30px/frame �̈ړ����x
    //�����蔻�肠��B
    //����0.99
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    _pMover->setMoveVelocity(30000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.99;
}


void HomingLaserChip::onActive() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;

    //���[�U�[�`�b�v�o��������
    if (pChip_front == NULL) {
        //���g���擪�̏ꍇ
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_vX = _pMover->_vX;
        _begining_vY = _pMover->_vY;
        _begining_vZ = _pMover->_vZ;
        _begining_RzMoveAngle = _pMover->_angRzMove;
        _begining_RyMoveAngle = _pMover->_angRyMove;

    } else {
        _begining_X = pChip_front->_begining_X;
        _begining_Y = pChip_front->_begining_Y;
        _begining_Z = pChip_front->_begining_Z;
        _begining_vX = pChip_front->_begining_vX;
        _begining_vY = pChip_front->_begining_vY;
        _begining_vZ = pChip_front->_begining_vZ;
        _begining_RzMoveAngle = pChip_front->_begining_RzMoveAngle;
        _begining_RyMoveAngle = pChip_front->_begining_RyMoveAngle;

        _X = _begining_X;
        _Y = _begining_Y;
        _Z = _begining_Z;
        _pMover->_vX = _begining_vX;
        _pMover->_vY = _begining_vY;
        _pMover->_vZ = _begining_vZ;
        _pMover->_angRzMove = _begining_RzMoveAngle;
        _pMover->_angRyMove = _begining_RyMoveAngle;
    }




}

void HomingLaserChip::onInactive() {
    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onInactive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onInactive();
}

void HomingLaserChip::processBehavior() {
    //���[�U�[�`�b�v����������
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    _dwActiveFrame++;
    //���W�ɔ��f
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;
    if (_dwActiveFrame > 1) {
        //ActorDispatcher::employ() ��
        //�擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ������B
        //���������āA���[�U�[�̐擪���珇�Ԃ�processBehavior() ���Ă΂�邽�߁A�ȉ��̂悤�ɂ����
        //����q���ɂȂ�B
        if (pChip_front == NULL) {
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;

            processBehaviorHeadChip();
        } else {

            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;

            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
        }
    }
}

void HomingLaserChip::processJudgement() {
    LaserChip::processJudgement();
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

HomingLaserChip::~HomingLaserChip() {
}

