#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "HomingLaserChip";
    _is_leader = false;
}

void HomingLaserChip::initialize() {
    //�����ݒ�ł��B
    //30px/frame �̈ړ����x
    //�����蔻�肠��B
    //����0.99
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    _pKurokoA->setMvVelo(30000);
    _fAlpha = 0.99;
}


void HomingLaserChip::onActive() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;

    //���[�U�[�`�b�v�o��������
    if (pChip_front == NULL) {
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front == NULL");
        _is_leader = true;
        //���g���擪�̏ꍇ
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_RX = _RX;
        _begining_RY = _RY;
        _begining_RZ = _RZ;
    } else {
        _is_leader = false;
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front =="<<(pChip_front->getName()));
        _begining_X = pChip_front->_begining_X;
        _begining_Y = pChip_front->_begining_Y;
        _begining_Z = pChip_front->_begining_Z;
        _begining_RX = pChip_front->_begining_RX;
        _begining_RY = pChip_front->_begining_RY;
        _begining_RZ = pChip_front->_begining_RZ;

        _X = _begining_X;
        _Y = _begining_Y;
        _Z = _begining_Z;
        _RX = _begining_RX;
        _RY = _begining_RY;
        _RZ = _begining_RZ;
    }




}

void HomingLaserChip::onInactive() {



    //���[�U�[�`�b�v����������
    //      -==========<>            ���[�U�[��
    //
    //      -= === === === <>        ����Ȃӂ��ɕ��f����Ă��܂��B
    //
    //    | -=|===|===|===|<> |      ���}�̓��[�U�[���I�u�W�F�N�g�ŋ�؂�������̐}
    //
    //    <--><--><--><--><-->^
    //    ^   ^   ^   ^   ^   |
    //    |   |   |   |   |   |
    //    |   |   |   |   |    `----- 4:��[�`�b�v(��\���ŁA���Ԑ擪�`�b�v��\�����邽�߂����ɑ���)
    //    |   |   |   |    `----- 3:���Ԑ擪�`�b�v(�\�����������̐擪)
    //    |   |   |    `----- 2:���ԃ`�b�v
    //    |   |    `----- 2:���ԃ`�b�v
    //    |    `----- 2:���ԃ`�b�v
    //     `----- 1:�����`�b�v
    //

    //_TRACE_("A HomingLaserChip::onInactive() _chip_kind ="<<_chip_kind <<")");
    if (_chip_kind == 1) {

    } else if (_chip_kind == 2) {
        //���ԃ`�b�v�������̏ꍇ
        //���g�̃`�b�v���������邱�Ƃɂ��A���[�U�[�̐���Ȃ��\�����Q������Ă��܂��B
        //�����O�̐擪�ȊO�̃`�b�v�́A��O�ɒǏ]���Ă邾���Ȃ̂ŁA���ԃ`�b�v Mover �����p�����[�^�͕s��B
        //����`�b�v���V���Ȑ擪�`�b�v�ƂȂ郌�[�U�[�\���̃O���[�v�� _pKurokoA->behave() �œ�����p�������邽�߂ɁA
        //�V���Ȑ擪�`�b�v�֌��݂̈ړ������ƈړ����x�̏���`�B����K�v������B
        if (_pChip_behind) {
            int D = (int)(GgafUtil::sqrt_fast(
                              (
                                ((double)(_pChip_behind->_X - _X)) * ((double)(_pChip_behind->_X - _X))
                              ) + (
                                ((double)(_pChip_behind->_Y - _Y)) * ((double)(_pChip_behind->_Y - _Y))
                              ) + (
                                ((double)(_pChip_behind->_Z - _Z)) * ((double)(_pChip_behind->_Z - _Z))
                              )
                            )
                         );
            _pChip_behind->_pKurokoA->setMvVelo(D); //���������x�ɂȂ�
            _pChip_behind->_pKurokoA->setMvAng(this);
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 2 �ł���ɂ��ւ�炸�A_pChip_behind�����݂��܂���");
        }
    } else if (_chip_kind == 3) {
        //���Ԑ擪�`�b�v�������̏ꍇ
        //�w�ǂ̏ꍇ�A�擪���珇�ɏ����Ă����͂��ł���B
        //�s���������Ƃ͒��ԃ`�b�v�������̏ꍇ�Ɠ����ŁA����`�b�v�֏���`�B����K�v������B
        //��[�`�b�v Mover �����p�����[�^�̈ړ������ƈړ����x�̏����R�s�[���邱�Ƃ�OK
        //�v�Z���x���҂�
        if (_pChip_behind && _pChip_front) {
            _pChip_behind->_pKurokoA->_vX = _pChip_front->_pKurokoA->_vX;
            _pChip_behind->_pKurokoA->_vY = _pChip_front->_pKurokoA->_vY;
            _pChip_behind->_pKurokoA->_vZ = _pChip_front->_pKurokoA->_vZ;
            _pChip_behind->_pKurokoA->_angRzMv = _pChip_front->_pKurokoA->_angRzMv;
            _pChip_behind->_pKurokoA->_angRyMv = _pChip_front->_pKurokoA->_angRyMv;
            _pChip_behind->_pKurokoA->_veloMv = _pChip_front->_pKurokoA->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 2 �ł���ɂ��ւ�炸�A_pChip_front �� _pChip_behind ���������݂��܂���");
        }
    } else if (_chip_kind == 4) {
        if (_pChip_behind) {
            _pChip_behind->_pKurokoA->_vX = _pKurokoA->_vX;
            _pChip_behind->_pKurokoA->_vY = _pKurokoA->_vY;
            _pChip_behind->_pKurokoA->_vZ = _pKurokoA->_vZ;
            _pChip_behind->_pKurokoA->_angRzMv = _pKurokoA->_angRzMv;
            _pChip_behind->_pKurokoA->_angRyMv = _pKurokoA->_angRyMv;
            _pChip_behind->_pKurokoA->_veloMv = _pKurokoA->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 4 �ł���ɂ��ւ�炸�A_pChip_behind �����݂��܂���");
        }
    }
    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void HomingLaserChip::processBehavior() {
    LaserChip::processBehavior();

    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    //���W�ɔ��f
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;
    if (getActivePartFrame() > 1) {
        //GgafActorDepository::dispatch() ��
        //�擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ������B
        //���������āA���[�U�[�̐擪���珇�Ԃ�processBehavior() ���Ă΂�邽�߁A�ȉ��̂悤�ɂ����
        //����q���ɂȂ�B
        if (pChip_front == NULL) {
            //�{���̐擪�`�b�v���A�����͂ɂ킩�擪�`�b�v�̏ꍇ�̋��ʏ���
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;

            processBehaviorHeadChip(); //�擪�`�b�v�݈̂ړ�����
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

void HomingLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void HomingLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDxUtil::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

HomingLaserChip::~HomingLaserChip() {
}
