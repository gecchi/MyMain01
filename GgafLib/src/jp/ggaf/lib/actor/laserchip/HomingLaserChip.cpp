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
    _begining_ang_rz_mv = getKuroko()->_ang_rz_mv;
    _begining_ang_ry_mv = getKuroko()->_ang_ry_mv;
    _begining_velo_mv   = getKuroko()->_velo_mv;
    _prev_x = _x;
    _prev_y = _y;
    _prev_z = _z;
    _prev_rx = _rx;
    _prev_ry = _ry;
    _prev_rz = _rz;
    _prev_ang_rz_mv = getKuroko()->_ang_rz_mv;
    _prev_ang_ry_mv = getKuroko()->_ang_ry_mv;
    _prev_velo_mv   = getKuroko()->_velo_mv;
    _is_fix_begin_pos = true;
}

void HomingLaserChip::onActive() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
    LaserChip::onActive();
    GgafDxKuroko* pKuroko = getKuroko();
    HomingLaserChip* pChip_infront =  (HomingLaserChip*)_pChip_infront;
    //���[�U�[�`�b�v�o��������
    if (pChip_infront == nullptr) {
        //_TRACE_(FUNC_NAME<<" "<<getName()<<" pChip_infront == nullptr");
        _is_leader = true;
        //���g���擪�̏ꍇ
        _begining_x = _x;
        _begining_y = _y;
        _begining_z = _z;
        _begining_rx = _rx;
        _begining_ry = _ry;
        _begining_rz = _rz;
        _begining_ang_rz_mv = pKuroko->_ang_rz_mv;
        _begining_ang_ry_mv = pKuroko->_ang_ry_mv;
        _begining_velo_mv   = pKuroko->_velo_mv;
    } else {
        _is_leader = false;
        //_TRACE_(FUNC_NAME<<" "<<getName()<<" pChip_infront =="<<(pChip_infront->getName()));
        _begining_x = pChip_infront->_begining_x;
        _begining_y = pChip_infront->_begining_y;
        _begining_z = pChip_infront->_begining_z;
        _begining_rx = pChip_infront->_begining_rx;
        _begining_ry = pChip_infront->_begining_ry;
        _begining_rz = pChip_infront->_begining_rz;
        _begining_ang_rz_mv = pChip_infront->_begining_ang_rz_mv;
        _begining_ang_ry_mv = pChip_infront->_begining_ang_ry_mv;
        _begining_velo_mv   = pChip_infront->_begining_velo_mv;
        if (_is_fix_begin_pos) {
            _x = _begining_x;
            _y = _begining_y;
            _z = _begining_z;
            _rx = _begining_rx;
            _ry = _begining_ry;
            _rz = _begining_rz;
            pKuroko->setRzRyMvAng(_begining_ang_rz_mv, _begining_ang_ry_mv);
            pKuroko->setMvVelo(_begining_velo_mv);
        }
    }
}

void HomingLaserChip::onInactive() {
    //_TRACE_("A HomingLaserChip::onInactive() _chip_kind ="<<_chip_kind <<")");
    LaserChip* pChip_behind = _pChip_behind;
    GgafDxKuroko* pKuroko = getKuroko();


    if (pChip_behind) {
        //�擪�����������Ă��Ȃ��̂ŁA
        //�����l�����Ȃ��ƁA����`�b�v�����̏�Œ�~���Ă��܂��B
        //����`�b�v�ֈړ��̂��߂̏��𖳗����ݒ肵�Ĉړ����p��������B
        //��[�`�b�v Mover �����p�����[�^�̈ړ������ƈړ����x�̏����R�s�[���邱�Ƃ�OK
        GgafDxKuroko* pChip_behind_pKuroko = pChip_behind->getKuroko();
        pChip_behind->_rx = _rx;
        pChip_behind->_ry = _ry;
        pChip_behind->_rz = _rz;
        pChip_behind_pKuroko->setRzRyMvAng(pKuroko->_ang_rz_mv, pKuroko->_ang_ry_mv);
        pChip_behind_pKuroko->setMvVelo(pKuroko->_velo_mv);
    }

    LaserChip::onInactive(); //�Ȃ����ؒf����
}

void HomingLaserChip::processBehavior() {
    //�Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
    //���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
    //���W�ɔ��f
    const HomingLaserChip* const pChip_infront =  (HomingLaserChip*)_pChip_infront;
    GgafDxKuroko* pKuroko = getKuroko();
    if (getActiveFrame() > 1) {
        //GgafActorDepository::dispatch() ��
        //�擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ������B
        //���������āA���[�U�[�̐擪���珇�Ԃ�processBehavior() ���Ă΂�邽�߁A�ȉ��̂悤�ɂ����
        //����q���ɂȂ�B
        if (pChip_infront == nullptr) {
            //�{���̐擪�`�b�v���A�����͂ɂ킩�擪�`�b�v�̏ꍇ�̋��ʏ���
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_ang_rz_mv = pKuroko->_ang_rz_mv;
            _prev_ang_ry_mv = pKuroko->_ang_ry_mv;
            _prev_velo_mv   = pKuroko->_velo_mv;
            processBehaviorHeadChip(); //�擪�`�b�v�݈̂ړ�����
        } else {
            //�擪�ȊO�̃`�b�v����q������
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_ang_rz_mv = pKuroko->_ang_rz_mv;
            _prev_ang_ry_mv = pKuroko->_ang_ry_mv;
            _prev_velo_mv   = pKuroko->_velo_mv;
            _x  = pChip_infront->_prev_x;
            _y  = pChip_infront->_prev_y;
            _z  = pChip_infront->_prev_z;
            _rx = pChip_infront->_prev_rx;
            _ry = pChip_infront->_prev_ry;
            _rz = pChip_infront->_prev_rz;
            pKuroko->setRzRyMvAng(pChip_infront->_prev_ang_rz_mv, pChip_infront->_prev_ang_ry_mv);
            pKuroko->setMvVelo(pChip_infront->_prev_velo_mv);
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

