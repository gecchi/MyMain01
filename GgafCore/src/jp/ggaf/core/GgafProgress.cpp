#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafProgress::GgafProgress(frame* prm_pFrame_count, int prm_num_progress) : GgafObject() ,
_progress(-1),       //ここと
_progress_prev(-2),
_progress_next(-1),  //ここは、合わせること。合わせないと、初回update時に配列インデックス範囲外になるため。
_pFrame_count(prm_pFrame_count)
{
    _num_progress = prm_num_progress;
    _paFrame_ProgressChanged = NEW frame[_num_progress];
    for (int i = 0; i < _num_progress; i++) {
        _paFrame_ProgressChanged[i] = (*_pFrame_count);
    }
}

int GgafProgress::get() {
    return _progress;
}
void GgafProgress::set(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::set 進捗番号が範囲外です(1～99ではない)。prm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
    }
#endif
    _progress_prev = _progress;
    _progress = prm_progress;
    _progress_next = prm_progress;
    _paFrame_ProgressChanged[prm_progress] = (*_pFrame_count);
}

frame GgafProgress::getFrameWhenChanged(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::getFrameWhenChanged 進捗番号が範囲外です(1～99ではない)。prm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
    }
#endif
    return _paFrame_ProgressChanged[prm_progress];
}

frame GgafProgress::getFrameInProgress() {
    return (*_pFrame_count) - _paFrame_ProgressChanged[_progress];
}


void GgafProgress::change(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::change 進捗番号が範囲外です(1～99ではない)。prm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
    }
#endif
    _progress_next = prm_progress;
}

void GgafProgress::changeNext() {
    _progress_next = _progress+1;
#ifdef MY_DEBUG
    if (_progress_next < 0 || _progress_next > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::changeNext 進捗番号が範囲外です(1～99ではない)。_progress_next="<<_progress_next);
    }
#endif
}


bool GgafProgress::isJustChangedTo(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::isJustChangedTo 進捗番号が範囲外です(1～99ではない)。prm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
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

bool GgafProgress::isJustChangedFrom(int prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress-1) {
        throwGgafCriticalException("GgafProgress::isJustChangedFrom 進捗番号が範囲外です(1～99ではない)。prm_progress="<<prm_progress<<" _num_progress="<<_num_progress);
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

int GgafProgress::get_WhenJustChanged() {
    if (_progress != _progress_prev) {
        return _progress;
    } else {
        return 0; // = false
    }
}

int GgafProgress::getPrev_WhenJustChanged() {
    if (_progress != _progress_prev) {
        return _progress_prev;
    } else {
        return 0; // = false
    }
}

int GgafProgress::get_WhenWillChange() {
    if (_progress != _progress_next) {
        return _progress;
    } else {
        return 0; // = false
    }
}

int GgafProgress::getNext_WhenWillChange() {
    if (_progress != _progress_next) {
        return _progress_next;
    } else {
        return 0; // = false
    }
}


void GgafProgress::update() {
    //進捗を反映する
    if (_progress != _progress_next) {
        _paFrame_ProgressChanged[_progress_next] = (*_pFrame_count);
    }
    _progress_prev = _progress;
    _progress = _progress_next;

}

GgafProgress::~GgafProgress() {
    DELETEARR_IMPOSSIBLE_NULL(_paFrame_ProgressChanged);

}

