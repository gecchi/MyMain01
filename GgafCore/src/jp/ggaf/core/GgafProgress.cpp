#include "stdafx.h"
using namespace GgafCore;

GgafProgress::GgafProgress(frame* prm_pFrame_counter, int prm_num_progress) : GgafObject() ,
_progress(PROGRESS_NOTHING),       //������
_progress_prev(-1),
_progress_next(PROGRESS_NOTHING),  //�����́A���킹�邱�ƁB���킹�Ȃ��ƁA����update���ɔz��C���f�b�N�X�͈͊O�ɂȂ邽�߁B
_pFrame_counter(prm_pFrame_counter)
{
    _num_progress = prm_num_progress;
    _paFrame_progress_changed = NEW frame[_num_progress+1];
    for (int i = 0; i < _num_progress+1; i++) {
        _paFrame_progress_changed[i] = (*_pFrame_counter);
    }
}
void GgafProgress::reset() {
    _progress_prev = -1;
    _progress = PROGRESS_NOTHING;
    _progress_next = PROGRESS_NOTHING;
    _paFrame_progress_changed[PROGRESS_NOTHING] = (*_pFrame_counter);
}

void GgafProgress::reset(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 1 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::reset �i���ԍ����͈͊O�ł��Breset(1�`"<<_num_progress<<")�ł��B�����Fprm_progress="<<prm_progress<<"");
    }
#endif
    _progress_prev = _progress;
    _progress = prm_progress;
    _progress_next = prm_progress;
    _paFrame_progress_changed[prm_progress] = (*_pFrame_counter);
}

void GgafProgress::setNothing() {
    _progress_prev = _progress;
    _progress = PROGRESS_NOTHING;
    _progress_next = PROGRESS_NOTHING;
    _paFrame_progress_changed[PROGRESS_NOTHING] = (*_pFrame_counter);
}

frame GgafProgress::getFrameWhenChanged(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::getFrameWhenChanged �i���ԍ����͈͊O�ł��B�i���ԍ��͈͂�(0�`"<<_num_progress<<")�ł��B�����Fprm_progress="<<prm_progress<<"");
    }
#endif
    return (_paFrame_progress_changed[prm_progress]);
}

void GgafProgress::change(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 1 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::change �i���ԍ����͈͊O�ł��B�g�p�\�Ȑi���ԍ���(1�`"<<_num_progress<<")�ł��B�����Fprm_progress="<<prm_progress<<"");
    }
#endif
    _progress_next = prm_progress;
}

void GgafProgress::changeNothing() {
    _progress_next = PROGRESS_NOTHING;
}

void GgafProgress::changeNext() {
    _progress_next = _progress+1;
#ifdef MY_DEBUG
    if (_progress_next < 1 || _progress_next > _num_progress) {
        throwGgafCriticalException("GgafProgress::changeNext �i���ԍ����{�P�Ŕ͈͊O�ɂȂ�܂����B�g�p�\�Ȑi���ԍ���(1�`"<<_num_progress<<")�ł��B_progress="<<_progress<<"");
    }
#endif
}


bool GgafProgress::isJustChangedTo(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::isJustChangedTo �i���ԍ����͈͊O�ł��B\nisJustChangedTo �����̎g�p�\�Ȑi���ԍ���(0�`"<<_num_progress<<")�ł��B�����Fprm_progress="<<prm_progress<<"");
    }
#endif
    if (_progress != _progress_prev) {
        if (prm_progress == _progress) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool GgafProgress::isJustChangedFrom(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::isJustChangedFrom �i���ԍ����͈͊O�ł��B\nisJustChangedFrom �����̎g�p�\�Ȑi���ԍ���(0�`"<<_num_progress<<")�ł��B�����Fprm_progress="<<prm_progress<<"");
    }
#endif
    if (_progress != _progress_prev) {
        if (prm_progress == _progress_prev) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

progress GgafProgress::getProgOnChange() {
    if (_progress != _progress_prev) {
        return _progress;
    } else {
        return 0; // = false
    }
}

progress GgafProgress::getFromProgOnChange() {
    if (_progress != _progress_prev) {
        return _progress_prev;
    } else {
        return 0; // = false
    }
}

progress GgafProgress::getProgWhenWillChange() {
    if (_progress != _progress_next) {
        return _progress;
    } else {
        return 0; // = false
    }
}

progress GgafProgress::getToProgWhenWillChange() {
    if (_progress != _progress_next) {
        return _progress_next;
    } else {
        return 0; // = false
    }
}


void GgafProgress::update() {
    //�i���𔽉f����
    if (_progress != _progress_next) {
        _paFrame_progress_changed[_progress_next] = (*_pFrame_counter) - 1;
    }
    _progress_prev = _progress;
    _progress = _progress_next;

}

GgafProgress::~GgafProgress() {
    DELETEARR_IMPOSSIBLE_NULL(_paFrame_progress_changed);

}

