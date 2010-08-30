#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

LaserChipDispatcher::LaserChipDispatcher(const char* prm_name) : GgafActorDispatcher(prm_name) {
    _class_name = "LaserChipDispatcher";
    _num_continual_employ_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = true;
    _num_chip_max = 0;
    _num_chip_interval = 20;
    _pChip_prev_employ = NULL;
    _frame_of_behaving_prev_employ = 0;

    _num_interval_frame_count = _num_chip_interval; //��������̓C���^�[�o���Ȃǖ���
    _num_continual_employ_max = _num_chip_max;
    _pEffectActor_Irradiate = NULL;
}

void LaserChipDispatcher::config(int prm_num_continual_employ_max,
                                 UINT32 prm_num_chip_interval,
                                 GgafDx9Core::GgafDx9DrawableActor* prm_pEffectActor_Irradiate) {
    _num_continual_employ_max = prm_num_continual_employ_max;
    _num_chip_interval = prm_num_chip_interval;
    _pEffectActor_Irradiate = prm_pEffectActor_Irradiate;
    if (_pEffectActor_Irradiate) {
        _pEffectActor_Irradiate->inactivateImmediately();
    }
}


LaserChip* LaserChipDispatcher::employ() {
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
        LaserChip* pChip = (LaserChip*)GgafActorDispatcher::employ();
        if (pChip != NULL) {
            pChip->activate();
            if (_pChip_prev_employ != NULL) {
                //�ȑO��employ()�����`�b�v
                if (_frame_of_behaving_prev_employ+1 == _pChip_prev_employ->getBehaveingFrame()) {
                    //2�t���[���A����employ�̏ꍇ�A���Ƃ݂Ȃ�
                    _num_continual_employ_count++;
                    pChip->_pChip_front = _pChip_prev_employ;
                    _pChip_prev_employ->_pChip_behind = pChip;
                    _is_tear_laser = false;
                } else {
                    //2�t���[���A����employ�o���ĂȂ��ꍇ�A���͐؂�Ă�
                    _num_continual_employ_count = 0;
                    pChip->_pChip_front = NULL;
                    _pChip_prev_employ->_pChip_behind = NULL;
                    _is_tear_laser = true;
                }
            } else {
                //employ()����
                pChip->_pChip_front = NULL;
                _is_tear_laser = false;
            }
            _pChip_prev_employ = pChip;
            _frame_of_behaving_prev_employ = pChip->getBehaveingFrame();

            return pChip;

        } else {
            //employ()�^�C�~���O�ł�������employ()�o���Ȃ������ꍇ
            _num_continual_employ_count = 0;
            _is_tear_laser = true;
            _pChip_prev_employ = NULL;
            _frame_of_behaving_prev_employ = 0;
            _num_interval_frame_count++;
            return NULL;
        }
    }
}

void LaserChipDispatcher::processFinal() {
//TODO:
    if (_pEffectActor_Irradiate) {
        if (_pChip_prev_employ && _frame_of_behaving_prev_employ == _pChip_prev_employ->getBehaveingFrame()) {
            //_TRACE_("_frame_of_behaving_prev_employ="<<_frame_of_behaving_prev_employ<<" ==? "<<_pChip_prev_employ->getBehaveingFrame()<<" _is_active_flg="<<_is_active_flg);
            if (_pEffectActor_Irradiate->_is_active_flg == false) {
                //_TRACE_("OKOKOKOK");
                _pEffectActor_Irradiate->activate();
            }
        } else {
            if (_pEffectActor_Irradiate->_is_active_flg) {
                _pEffectActor_Irradiate->inactivate();
            }
        }
    }
}

void LaserChipDispatcher::addSubLast(LaserChip* prm_pLaserChip) {
    _num_chip_max ++;
    _num_continual_employ_max++;
    prm_pLaserChip->_pDispatcher = this;
    GgafActorDispatcher::addSubLast(prm_pLaserChip);
}

LaserChipDispatcher::~LaserChipDispatcher() {
}
