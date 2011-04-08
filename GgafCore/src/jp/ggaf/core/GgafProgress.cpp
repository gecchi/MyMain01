#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafProgress::GgafProgress(frame* prm_pFrame_behaving, int prm_num_progress) : GgafObject() ,
_progress(-1),
_progress_prev(-2),
_progress_nextframe(-3),
_pFrame_behaving(prm_pFrame_behaving)
{
    _num_progress = prm_num_progress;
    _paFrame_ProgressChanged = NEW frame[_num_progress];
    DWORD x = UINT_MAX/2;
    for (int i = 0; i < _num_progress; i++) {
        _paFrame_ProgressChanged[i] = x; //�L�肦�Ȃ��t���[���Ȃ�ǂ�
    }
}

int GgafProgress::get() {
    return _progress;
}
void GgafProgress::set(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::set �i��ID���͈͊O�ł��Bprm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
    }
#endif
    _progress_prev = _progress;
    _progress = prm_progress;
    _progress_nextframe = prm_progress;
    _paFrame_ProgressChanged[prm_progress] = (*_pFrame_behaving);
}

frame GgafProgress::getFrameWhenChanged(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::getFrameWhenChanged �i��ID���͈͊O�ł��Bprm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
    }
#endif
    return _paFrame_ProgressChanged[prm_progress];
}

frame GgafProgress::getFrameInProgress() {
    return (*_pFrame_behaving)+1 - _paFrame_ProgressChanged[_progress];
}


void GgafProgress::change(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::change �i��ID���͈͊O�ł��Bprm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
    }
#endif
    _progress_nextframe = prm_progress;
    _paFrame_ProgressChanged[prm_progress] = (*_pFrame_behaving)+1;
}

void GgafProgress::changeNext() {
    _progress_nextframe = _progress+1;
#ifdef MY_DEBUG
    if (_progress_nextframe < 0 || _progress_nextframe > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::changeNext �i��ID���͈͊O�ł��B_progress_nextframe="<<_progress_nextframe);
    }
#endif
    _paFrame_ProgressChanged[_progress+1] = (*_pFrame_behaving)+1;
}


bool GgafProgress::wasChangedTo(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::wasChangedTo �i��ID���͈͊O�ł��Bprm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
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
bool GgafProgress::isJustChanged() {
    if (_progress != _progress_prev) {
        return true;
    } else {
        return false;
    }
}

bool GgafProgress::wasChangedFrom(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::wasChangedFrom �i��ID���͈͊O�ł��Bprm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
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

int GgafProgress::getChangedTo() {
    if (_progress != _progress_prev) {
        return _progress;
    } else {
        return 0; // = false
    }
}

int GgafProgress::getFromChange() {
    if (_progress != _progress_prev) {
        return _progress_prev;
    } else {
        return 0; // = false
    }
}

void GgafProgress::update() {
    //�i���𔽉f����
    _progress_prev = _progress;
    _progress = _progress_nextframe;

}

GgafProgress::~GgafProgress() {
    DELETEARR_IMPOSSIBLE_NULL(_paFrame_ProgressChanged);

}

