#include "jp/ggaf/core/Phase.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"
#include <stdarg.h>

using namespace GgafCore;

Phase::Phase(frame* prm_p_frame_counter) :
    Object() ,
    _phase(GGAF_PHASE_NOTHING),       //������
    _phase_prev(GGAF_PHASE_NULL),
    _phase_next(GGAF_PHASE_NOTHING),  //�����́A���킹�邱�ƁB���킹�Ȃ��ƁA����update���ɔz��C���f�b�N�X�͈͊O�ɂȂ邽�߁B
    _p_frame_counter(prm_p_frame_counter)
{
    _map_changed_frame[_phase] = (*_p_frame_counter);
}

void Phase::reset() {
    _phase_prev = GGAF_PHASE_NULL;
    _phase = GGAF_PHASE_NOTHING;
    _phase_next = GGAF_PHASE_NOTHING;
    _map_changed_frame[_phase] = (*_p_frame_counter);
}

void Phase::reset(phase prm_phase) {
#ifdef MY_DEBUG
    if (prm_phase < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase="<<prm_phase<<"");
    }
#endif
    _phase_prev = GGAF_PHASE_NULL;
    _phase = prm_phase;
    _phase_next = prm_phase;
    _map_changed_frame[_phase] = (*_p_frame_counter);
}

void Phase::setNothing() {
    _phase_prev = _phase;
    _phase = GGAF_PHASE_NOTHING;
    _phase_next = GGAF_PHASE_NOTHING;
    _map_changed_frame[_phase] = (*_p_frame_counter);
}

frame Phase::getFrameWhenChanged(phase prm_phase) {
#ifdef MY_DEBUG
    if (prm_phase < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase="<<prm_phase<<"");
    }
#endif
    return (_map_changed_frame[prm_phase]);
}

void Phase::change(phase prm_phase) {
#ifdef MY_DEBUG
    if (prm_phase < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase="<<prm_phase<<"");
    }
#endif
    _phase_next = prm_phase;
}

void Phase::changeProbab(uint32_t prm_p1, phase prm_phase1, ...) {
    uint32_t r = (uint32_t)(RND(1,100));
    if (prm_p1 >= r) {
        change(prm_phase1);
        return;
    }
    uint32_t p_sum = (uint32_t)prm_p1;
    va_list args;
    va_start(args, prm_phase1);
    while (p_sum < 100) {
        p_sum += va_arg(args, uint32_t);
#ifdef MY_DEBUG
        if (p_sum > 100) {
            throwCriticalException("p_sum="<<p_sum<<" �m���̍��v���҂�����100�ɂȂ�܂���B�iva_arg�ŕςȏꏊ��ǂݍ��񂾂����j");
            return;
         }
#endif
        phase prog = va_arg(args, phase);
        if (p_sum >= r) {
            change(prog);
            return;
        }
    }
    va_end(args);
#ifdef MY_DEBUG
    if (p_sum != 100) {
        throwCriticalException("p_sum="<<p_sum<<" �m���̍��v���҂�����100�ɂȂ�܂���B");
    }
#endif
}

//void Phase::changeProbab(uint32_t prm_p1, phase prm_phase1, ...) {
//    uint32_t r = (uint32_t)(RND(1,100));
//    if (prm_p1 <= r) {
//        change(prm_phase1);
//        return;
//    }
//    uint32_t p_sum = (uint32_t)prm_p1;
//
//    va_list args;
//    va_start(args, prm_phase1);
//    while(p_sum < 100) {
//        p_sum += va_arg(args, uint32_t);
//        phase prog = va_arg(args, phase);
//        if (p_sum <= r) {
//            change(prog);
//            return;
//        }
//    }
//    va_end(args);
//#ifdef MY_DEBUG
//    if (p_sum != 100) {
//        throwCriticalException("���v��100%�ɂȂ��ĂȂ��B");
//    }
//#endif
//}

void Phase::changeNothing() {
    _phase_next = GGAF_PHASE_NOTHING;
}

void Phase::changeNext() {
#ifdef MY_DEBUG
    if (_phase_next == _phase+1) {
        throwCriticalException("���� _phase="<<_phase<<" _phase_next="<<_phase_next<<" �ł��B�A���� changeNext() ���Ă��܂��񂩁H");
    }
#endif
    _phase_next = _phase + 1;
#ifdef MY_DEBUG
    if (_phase_next < 0) {
        throwCriticalException("�t�F�[�Y�ԍ����{�P�ŁA�Ȃ������̐��ł��͈͊O�ɂȂ�܂����B_phase="<<_phase<<"");
    }
#endif
}


bool Phase::hasJustChangedTo(phase prm_phase) const {
#ifdef MY_DEBUG
    if (prm_phase < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase="<<prm_phase<<"");
    }
#endif
    if (_phase != _phase_prev && _phase_prev >= GGAF_PHASE_NOTHING) {
        if (prm_phase == _phase) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Phase::hasJustChangedFrom(phase prm_phase) const {
#ifdef MY_DEBUG
    if (prm_phase < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase="<<prm_phase<<"");
    }
#endif
    if (_phase != _phase_prev && _phase_prev >= GGAF_PHASE_NOTHING) {
        if (prm_phase == _phase_prev) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

phase Phase::getPhaseOnChange() const {
    if (_phase != _phase_prev && _phase_prev >= GGAF_PHASE_NOTHING) {
        return _phase;
    } else {
        return GGAF_PHASE_NULL;
    }
}

phase Phase::getFromPhaseOnChange() const {
    if (_phase != _phase_prev && _phase_prev >= GGAF_PHASE_NOTHING) {
        return _phase_prev;
    } else {
        return GGAF_PHASE_NULL;
    }
}

phase Phase::getPhaseWhenPhaseWillChange() const {
    if (_phase != _phase_next) {
        return _phase;
    } else {
        return GGAF_PHASE_NULL;
    }
}

phase Phase::getToPhaseWhenPhaseWillChange() const {
    if (_phase != _phase_next) {
        return _phase_next;
    } else {
        return GGAF_PHASE_NULL;
    }
}

void Phase::update() {
    //�i���𔽉f����
    phase prog = _phase;
    phase prog_next = _phase_next;
    if (prog != prog_next) {
        _map_changed_frame[prog_next] = (*_p_frame_counter) - 1;
    }
    _phase_prev = prog;
    _phase = prog_next;
}

Phase::~Phase() {
}

