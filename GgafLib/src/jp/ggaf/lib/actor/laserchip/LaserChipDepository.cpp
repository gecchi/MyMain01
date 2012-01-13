#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChipDepository::LaserChipDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "LaserChipDepository";
    _num_continual_employ_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = true;
    _num_chip_max = 0;
    _num_chip_interval = 1;
    _pChip_prev_employ = NULL;
    _frame_of_behaving_prev_employ = 0;

    _num_interval_frame_count = _num_chip_interval; //��������̓C���^�[�o���Ȃǖ���
    _num_continual_employ_max = _num_chip_max;
    _pEffectActor_Irradiate = NULL;
}

void LaserChipDepository::config(int prm_num_continual_employ_max,
                                 UINT32 prm_num_chip_interval,
                                 GgafDxCore::GgafDxDrawableActor* prm_pEffectActor_Irradiate) {
    _num_continual_employ_max = prm_num_continual_employ_max;
    _num_chip_interval = prm_num_chip_interval;
    _pEffectActor_Irradiate = prm_pEffectActor_Irradiate;
    if (_pEffectActor_Irradiate) {
        _pEffectActor_Irradiate->inactivateImmed();
    }
}


LaserChip* LaserChipDepository::dispatch(frame prm_offset_frames) {
    if (_num_continual_employ_count > _num_continual_employ_max) { //_num_continual_employ_max�A�����ˎ��A�e�؂�ɂ���(_num_interval_frame_count�����Z�b�g)�B
        _is_tear_laser = true;
        _pChip_prev_employ = NULL;
        _frame_of_behaving_prev_employ = 0;
        _num_continual_employ_count = 0;
        _num_interval_frame_count = 0;
        return NULL;
    } else if (_num_interval_frame_count < _num_chip_interval) { //_num_chip_interval�t���[���ȓ��Ȃ̂Œe�؂�ɂ���B
        _is_tear_laser = true;
        _num_interval_frame_count++;
        return NULL;
    } else if (_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_max/4) { //�e�؂�̎� _num_chip_max/4 ���܂��Ă��甭��
        _is_tear_laser = true;
        _pChip_prev_employ = NULL;
        _frame_of_behaving_prev_employ = 0;
        _num_continual_employ_count = 0;
        _num_interval_frame_count++;
        return NULL;
    } else {
        LaserChip* pChip = (LaserChip*)GgafActorDepository::dispatch(prm_offset_frames);
        if (pChip) {
            if (_pChip_prev_employ) {
                //�ȑO��dispatch()�����`�b�v
                if (_frame_of_behaving_prev_employ+1 == _pChip_prev_employ->getBehaveingFrame()) {
                    //2�t���[���A����employ�̏ꍇ�A���Ƃ݂Ȃ�
                    _num_continual_employ_count++;
                    pChip->_pChip_front = _pChip_prev_employ;
                    _pChip_prev_employ->_pChip_behind = pChip;
                    pChip->_pChip_behind = NULL;
                    _is_tear_laser = false;
                } else {
                    //2�t���[���A����employ�o���ĂȂ��ꍇ�A���͐؂�Ă�
                    _num_continual_employ_count = 0;
                    pChip->_pChip_front = NULL;
                    pChip->_pChip_behind = NULL;
                    //_pChip_prev_employ->_pChip_behind = NULL;
                    _is_tear_laser = true;
                }
            } else {
                //dispatch()����
                pChip->_pChip_front = NULL;
                pChip->_pChip_behind = NULL;
                _is_tear_laser = false;
            }
            _pChip_prev_employ = pChip;
            _frame_of_behaving_prev_employ = pChip->getBehaveingFrame();
            //20��Ɉ��͒n�`�q�b�g����̃`�b�v�Ƃ���
            if (_num_continual_employ_count % 20 == 0) {
                pChip->_can_chikei_hit = true;
            } else {
                pChip->_can_chikei_hit = false;
            }
            return pChip;

        } else {
            //dispatch()�^�C�~���O�ł�������dispatch()�o���Ȃ������ꍇ
            _num_continual_employ_count = 0;
            _is_tear_laser = true;
            _pChip_prev_employ = NULL;
            _frame_of_behaving_prev_employ = 0;
            _num_interval_frame_count++;
            return NULL;
        }
    }
}

void LaserChipDepository::processFinal() {
    //���˒��G�t�F�N�g�\���؂�ւ�
    if (_pEffectActor_Irradiate) {
        if (_pChip_prev_employ && _frame_of_behaving_prev_employ == _pChip_prev_employ->getBehaveingFrame()) {
            if (_pEffectActor_Irradiate->_is_active_flg == false) {
                _pEffectActor_Irradiate->activate();
            }
        } else {
            if (_pEffectActor_Irradiate->_is_active_flg) {
                _pEffectActor_Irradiate->inactivate();
            }
        }
    }
}

void LaserChipDepository::addSubLast(LaserChip* prm_pLaserChip) {
    _num_chip_max ++;
    _num_continual_employ_max++;
    prm_pLaserChip->_pDepo = this;
    GgafActorDepository::addSubLast(prm_pLaserChip);
}

void LaserChipDepository::onReset() {
    _is_tear_laser = true;
    _num_continual_employ_count = 0;
    _num_chip_active = 0;
    _frame_of_behaving_prev_employ = 0;
    GgafActorDepository::onReset();
}

LaserChipDepository::~LaserChipDepository() {
    _TRACE_("LaserChipDepository::~LaserChipDepository()");
}
