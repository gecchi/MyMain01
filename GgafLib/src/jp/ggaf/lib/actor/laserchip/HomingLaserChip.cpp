#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "HomingLaserChip";
    _is_leader = false;

    _begining_x = _x;
    _begining_y = _y;
    _begining_z = _z;
    _begining_rx = _rx;
    _begining_ry = _ry;
    _begining_rz = _rz;
    _prev_x = _x;
    _prev_y = _y;
    _prev_z = _z;
    _prev_rx = _rx;
    _prev_ry = _ry;
    _prev_rz = _rz;
    _is_fix_begin_pos = true;
}

void HomingLaserChip::onActive() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;

    //���[�U�[�`�b�v�o��������
    if (pChip_front == nullptr) {
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front == nullptr");
        _is_leader = true;
        //���g���擪�̏ꍇ
        _begining_x = _x;
        _begining_y = _y;
        _begining_z = _z;
        _begining_rx = _rx;
        _begining_ry = _ry;
        _begining_rz = _rz;
    } else {
        _is_leader = false;
        //_TRACE_("HomingLaserChip::onActive() "<<getName()<<" pChip_front =="<<(pChip_front->getName()));
        _begining_x = pChip_front->_begining_x;
        _begining_y = pChip_front->_begining_y;
        _begining_z = pChip_front->_begining_z;
        _begining_rx = pChip_front->_begining_rx;
        _begining_ry = pChip_front->_begining_ry;
        _begining_rz = pChip_front->_begining_rz;
        if (_is_fix_begin_pos) {
            _x = _begining_x;
            _y = _begining_y;
            _z = _begining_z;
            _rx = _begining_rx;
            _ry = _begining_ry;
            _rz = _begining_rz;
        }
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
        LaserChip* pChip_behind = _pChip_behind;
        //���ԃ`�b�v�������̏ꍇ
        //���g�̃`�b�v���������邱�Ƃɂ��A���[�U�[�̐���Ȃ��\�����Q������Ă��܂��B
        //�����O�̐擪�ȊO�̃`�b�v�́A��O�ɒǏ]���Ă邾���Ȃ̂ŁA���ԃ`�b�v Mover �����p�����[�^�͕s��B
        //����`�b�v���V���Ȑ擪�`�b�v�ƂȂ郌�[�U�[�\���̃O���[�v�� getKuroko()->behave() �œ�����p�������邽�߂ɁA
        //�V���Ȑ擪�`�b�v�֌��݂̈ړ������ƈړ����x�̏���`�B����K�v������B
        if (pChip_behind) {
            int D = (int)(sqrt(
                              (
                                ((double)(pChip_behind->_x - _x)) * ((double)(pChip_behind->_x - _x))
                              ) + (
                                ((double)(pChip_behind->_y - _y)) * ((double)(pChip_behind->_y - _y))
                              ) + (
                                ((double)(pChip_behind->_z - _z)) * ((double)(pChip_behind->_z - _z))
                              )
                            )
                         );
            pChip_behind->getKuroko()->setMvVelo(D); //���������x�ɂȂ�
            pChip_behind->getKuroko()->setMvAngTwd(this);
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
            GgafDxKuroko* const pChip_behind_pKuroko = _pChip_behind->getKuroko();
            GgafDxKuroko* const pChip_front_pKuroko = _pChip_front->getKuroko();
            pChip_behind_pKuroko->_vX = pChip_front_pKuroko->_vX;
            pChip_behind_pKuroko->_vY = pChip_front_pKuroko->_vY;
            pChip_behind_pKuroko->_vZ = pChip_front_pKuroko->_vZ;
            pChip_behind_pKuroko->_angRzMv = pChip_front_pKuroko->_angRzMv;
            pChip_behind_pKuroko->_angRyMv = pChip_front_pKuroko->_angRyMv;
            pChip_behind_pKuroko->_veloMv =  pChip_front_pKuroko->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 2 �ł���ɂ��ւ�炸�A_pChip_front �� _pChip_behind ���������݂��܂���");
        }
    } else if (_chip_kind == 4) {
        if (_pChip_behind) {
            GgafDxKuroko* const pChip_behind_pKuroko = _pChip_behind->getKuroko();
            GgafDxKuroko* pKuroko = getKuroko();
            pChip_behind_pKuroko->_vX = pKuroko->_vX;
            pChip_behind_pKuroko->_vY = pKuroko->_vY;
            pChip_behind_pKuroko->_vZ = pKuroko->_vZ;
            pChip_behind_pKuroko->_angRzMv = pKuroko->_angRzMv;
            pChip_behind_pKuroko->_angRyMv = pKuroko->_angRyMv;
            pChip_behind_pKuroko->_veloMv  = pKuroko->_veloMv;
        } else {
            //throwGgafCriticalException("HomingLaserChip::onInactive() _chip_kind == 4 �ł���ɂ��ւ�炸�A_pChip_behind �����݂��܂���");
        }
    }
    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void HomingLaserChip::processBehavior() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    //���W�ɔ��f
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;
    if (getActiveFrame() > 1) {
        //GgafActorDepository::dispatch() ��
        //�擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ������B
        //���������āA���[�U�[�̐擪���珇�Ԃ�processBehavior() ���Ă΂�邽�߁A�ȉ��̂悤�ɂ����
        //����q���ɂȂ�B
        if (pChip_front == nullptr) {
            //�{���̐擪�`�b�v���A�����͂ɂ킩�擪�`�b�v�̏ꍇ�̋��ʏ���
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            processBehaviorHeadChip(); //�擪�`�b�v�݈̂ړ�����
        } else {
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _x  = pChip_front->_prev_x;
            _y  = pChip_front->_prev_y;
            _z  = pChip_front->_prev_z;
            _rx = pChip_front->_prev_rx;
            _ry = pChip_front->_prev_ry;
            _rz = pChip_front->_prev_rz;
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

HomingLaserChip::~HomingLaserChip() {
}

