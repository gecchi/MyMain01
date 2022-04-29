#include "jp/ggaf/core/Phase.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"
#include <stdarg.h>

using namespace GgafCore;

Phase::Phase(frame* prm_p_frame_counter) :
    Object() ,
    _phase_no(GGAF_PHASE_NOTHING),       //������
    _phase_no_prev(GGAF_PHASE_NULL),
    _phase_no_next(GGAF_PHASE_NOTHING),  //�����́A���킹�邱�ƁB���킹�Ȃ��ƁA����update���ɔz��C���f�b�N�X�͈͊O�ɂȂ邽�߁B
    _p_frame_counter(prm_p_frame_counter)
{
    _map_phase_no_changed_frame[_phase_no] = (*_p_frame_counter);
}

void Phase::reset() {
    _phase_no_prev = GGAF_PHASE_NULL;
    _phase_no = GGAF_PHASE_NOTHING;
    _phase_no_next = GGAF_PHASE_NOTHING;
    _map_phase_no_changed_frame[_phase_no] = (*_p_frame_counter);
}

void Phase::reset(int prm_phase_no) {
#ifdef MY_DEBUG
    if (prm_phase_no < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase_no="<<prm_phase_no<<"");
    }
#endif
    _phase_no_prev = GGAF_PHASE_NULL;
    _phase_no = prm_phase_no;
    _phase_no_next = prm_phase_no;
    _map_phase_no_changed_frame[_phase_no] = (*_p_frame_counter);
}

void Phase::setNothing() {
    _phase_no_prev = _phase_no;
    _phase_no = GGAF_PHASE_NOTHING;
    _phase_no_next = GGAF_PHASE_NOTHING;
    _map_phase_no_changed_frame[_phase_no] = (*_p_frame_counter);
}

frame Phase::getFrameWhenChanged(int prm_phase_no) {
#ifdef MY_DEBUG
    if (prm_phase_no < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase_no="<<prm_phase_no<<"");
    }
#endif
    return (_map_phase_no_changed_frame[prm_phase_no]);
}

void Phase::change(int prm_phase_no) {
#ifdef MY_DEBUG
    if (prm_phase_no < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase_no="<<prm_phase_no<<"");
    }
#endif
    _phase_no_next = prm_phase_no;
}

void Phase::changeProbab(uint32_t prm_p1, int prm_phase_no1, ...) {
    uint32_t r = (uint32_t)(RND(1,100));
    if (prm_p1 >= r) {
        change(prm_phase_no1);
        return;
    }
    uint32_t p_sum = (uint32_t)prm_p1;
    va_list args;
    va_start(args, prm_phase_no1);
    while (p_sum < 100) {
        p_sum += va_arg(args, uint32_t);
#ifdef MY_DEBUG
        if (p_sum > 100) {
            throwCriticalException("p_sum="<<p_sum<<" �m���̍��v���҂�����100�ɂȂ�܂���B�iva_arg�ŕςȏꏊ��ǂݍ��񂾂����j");
            return;
         }
#endif
        int phs = va_arg(args, int);
        if (p_sum >= r) {
            change(phs);
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

//void Phase::changeProbab(uint32_t prm_p1, int prm_phase_no1, ...) {
//    uint32_t r = (uint32_t)(RND(1,100));
//    if (prm_p1 <= r) {
//        change(prm_phase_no1);
//        return;
//    }
//    uint32_t p_sum = (uint32_t)prm_p1;
//
//    va_list args;
//    va_start(args, prm_phase_no1);
//    while(p_sum < 100) {
//        p_sum += va_arg(args, uint32_t);
//        int phs = va_arg(args, int);
//        if (p_sum <= r) {
//            change(phs);
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
    _phase_no_next = GGAF_PHASE_NOTHING;
}

void Phase::changeNext() {
#ifdef MY_DEBUG
    if (_phase_no_next == _phase_no+1) {
        throwCriticalException("���� _phase_no="<<_phase_no<<" _phase_no_next="<<_phase_no_next<<" �ł��B�A���� changeNext() ���Ă��܂��񂩁H");
    }
#endif
    _phase_no_next = _phase_no + 1;
#ifdef MY_DEBUG
    if (_phase_no_next < 0) {
        throwCriticalException("�t�F�[�Y�ԍ����{�P�ŁA�Ȃ������̐��ł��͈͊O�ɂȂ�܂����B_phase_no="<<_phase_no<<"");
    }
#endif
}


bool Phase::hasJustChangedTo(int prm_phase_no) const {
#ifdef MY_DEBUG
    if (prm_phase_no < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase_no="<<prm_phase_no<<"");
    }
#endif
    if (_phase_no != _phase_no_prev && _phase_no_prev >= GGAF_PHASE_NOTHING) {
        if (prm_phase_no == _phase_no) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Phase::hasJustChangedFrom(int prm_phase_no) const {
#ifdef MY_DEBUG
    if (prm_phase_no < 0) {
        throwCriticalException("�t�F�[�Y�ԍ������ł��B�����Fprm_phase_no="<<prm_phase_no<<"");
    }
#endif
    if (_phase_no != _phase_no_prev && _phase_no_prev >= GGAF_PHASE_NOTHING) {
        if (prm_phase_no == _phase_no_prev) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int Phase::getWhenChanged() const {
    if (_phase_no != _phase_no_prev && _phase_no_prev >= GGAF_PHASE_NOTHING) {
        return _phase_no;
    } else {
        return GGAF_PHASE_NULL;
    }
}

int Phase::getPrevWhenChanged() const {
    if (_phase_no != _phase_no_prev && _phase_no_prev >= GGAF_PHASE_NOTHING) {
        return _phase_no_prev;
    } else {
        return GGAF_PHASE_NULL;
    }
}

int Phase::getWillChangeNextFrame() const {
    if (_phase_no != _phase_no_next) {
        return _phase_no;
    } else {
        return GGAF_PHASE_NULL;
    }
}

int Phase::getPrevWillChangeNextFrame() const {
    if (_phase_no != _phase_no_next) {
        return _phase_no_next;
    } else {
        return GGAF_PHASE_NULL;
    }
}

void Phase::update() {
    //�i���𔽉f����
    int phs = _phase_no;
    int phs_next = _phase_no_next;
    if (phs != phs_next) {
        _map_phase_no_changed_frame[phs_next] = (*_p_frame_counter) - 1;
    }
    _phase_no_prev = phs;
    _phase_no = phs_next;
}

Phase::~Phase() {
}

