#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"



using namespace GgafLib;

LaserChipDepository::LaserChipDepository(const char* prm_name) :
        GgafCore::ActorDepository(prm_name) {
    _class_name = "LaserChipDepository";
    _num_continual_dispatch_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = true;
    _num_chip_max = 0;
    _num_chip_interval = 1;
    _num_chip_dispatch_able = 0;
    _pChip_prev_dispatch = nullptr;
    _frame_of_behaving_prev_dispatch = 0;

    _num_interval_frame_count = _num_chip_interval; //��������̓C���^�[�o���Ȃǖ���
    _num_continual_dispatch_max = _num_chip_max;
    _pEffectActor = nullptr;
}

void LaserChipDepository::config(int prm_num_continual_dispatch_max,
                                 uint32_t prm_num_chip_interval,
                                 GgafDx::FigureActor* prm_pEffectActor) {
    _num_continual_dispatch_max = prm_num_continual_dispatch_max;
    _num_chip_interval = prm_num_chip_interval;
    _pEffectActor = prm_pEffectActor;
    if (_pEffectActor) {
        _pEffectActor->inactivate();
    }
}

LaserChip* LaserChipDepository::dispatch(int prm_offset_frames) {
    if (_num_continual_dispatch_count > _num_continual_dispatch_max) { //_num_continual_dispatch_max�A�����ˎ��A�e�؂�ɂ���(_num_interval_frame_count�����Z�b�g)�B
        _is_tear_laser = true;
        _pChip_prev_dispatch = nullptr;
        _frame_of_behaving_prev_dispatch = 0;
        _num_continual_dispatch_count = 0;
        _num_interval_frame_count = 1; //�R�R�ɏ������������Ƃɂ����ɂP�t���[���e�؂�Ȃ̂łP��ݒ�
        return nullptr;
    } else if (_num_interval_frame_count < _num_chip_interval) { //_num_chip_interval�t���[���ȓ��Ȃ̂Œe�؂�ɂ���B
        _is_tear_laser = true;
        _num_interval_frame_count++;
        return nullptr;
    } else if (_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_dispatch_able) {
        _is_tear_laser = true;
        _pChip_prev_dispatch = nullptr;
        _frame_of_behaving_prev_dispatch = 0;
        _num_continual_dispatch_count = 0;
        _num_interval_frame_count++;
        return nullptr;
    } else {
        LaserChip* const pChip = (LaserChip*)GgafCore::ActorDepository::dispatch(prm_offset_frames);
        if (pChip) {
            if (_pChip_prev_dispatch) {
                //�ȑO��dispatch()�����`�b�v
                if ( ( _frame_of_behaving_prev_dispatch+1 == _pChip_prev_dispatch->getBehaveingFrame()  &&  _pChip_prev_dispatch->isActive() ) ||
                       _frame_of_behaving_prev_dispatch   == _pChip_prev_dispatch->getBehaveingFrame()
                ) {
                    //���t���[����dispatch() �����͂P�t���[�����ŘA����dispatch() �̏ꍇ�A���Ƃ݂Ȃ�
                    _num_continual_dispatch_count++;
                    pChip->_pChip_infront = _pChip_prev_dispatch;
                    _pChip_prev_dispatch->_pChip_behind = pChip;
                    pChip->_pChip_behind = nullptr;
                    _is_tear_laser = false;
                } else {
                    //�A���͐؂�Ă�
                    _num_continual_dispatch_count = 0;
                    pChip->_pChip_infront = nullptr;
                    pChip->_pChip_behind = nullptr;
                    _is_tear_laser = true;
                }
            } else {
                //dispatch()����
                pChip->_pChip_infront = nullptr;
                pChip->_pChip_behind = nullptr;
                _is_tear_laser = false;
            }
            _pChip_prev_dispatch = pChip;
            _frame_of_behaving_prev_dispatch = pChip->getBehaveingFrame();
            //16��Ɉ��� �n�` �q�b�g����̃`�b�v�Ƃ���
            if (_num_continual_dispatch_count % 16U == 0) {
                pChip->_can_chikei_hit = true;
            } else {
                pChip->_can_chikei_hit = false;
            }
            return pChip;

        } else {
            //dispatch()�^�C�~���O�ł�������dispatch()�o���Ȃ������ꍇ
            _num_continual_dispatch_count = 0;
            _is_tear_laser = true;
            _pChip_prev_dispatch = nullptr;
            _frame_of_behaving_prev_dispatch = 0;
            _num_interval_frame_count++;
            return nullptr;
        }
    }
}

void LaserChipDepository::processFinal() {
    //���˒��G�t�F�N�g�\���؂�ւ�
    if (_pEffectActor) {
        if (_pChip_prev_dispatch && _frame_of_behaving_prev_dispatch == _pChip_prev_dispatch->getBehaveingFrame()) {
            if (_pEffectActor->_is_active_flg == false) {
                _pEffectActor->activate();
            }
        } else {
            if (_pEffectActor->_is_active_flg) {
                _pEffectActor->inactivate();
            }
        }
    }
}
void LaserChipDepository::put(GgafCore::Actor* prm_pChild) {
#ifdef MY_DEBUG
    if (!prm_pChild->instanceOf(Obj_LaserChip)) {
        throwCriticalException("LaserChipDepository::put() �����ɂ� LaserChip ��n���Ă��������Bprm_pChild="<<prm_pChild->getName()<<"("<<prm_pChild<<")");
    }
#endif
    LaserChip* pLaserChip = (LaserChip*)prm_pChild;
    _num_chip_max ++;
    _num_continual_dispatch_max++;
    _num_chip_dispatch_able = _num_chip_max/4; //�e�؂�̎� _num_chip_max/4 ���܂��Ă��甭��
    pLaserChip->_pDepo = this;
    GgafCore::ActorDepository::put(pLaserChip);
}

void LaserChipDepository::onReset() {
    _is_tear_laser = true;
    _num_continual_dispatch_count = 0;
    _num_chip_active = 0;
    _frame_of_behaving_prev_dispatch = 0;
    GgafCore::ActorDepository::onReset();
}

LaserChipDepository::~LaserChipDepository() {
    _TRACE_("LaserChipDepository::~LaserChipDepository()");
}
