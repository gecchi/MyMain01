#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafProgress::GgafProgress(frame* prm_pFrame_count, int prm_num_progress) : GgafObject() ,
_progress(PROGRESS_NOTHING),       //ここと
_progress_prev(-1),
_progress_next(PROGRESS_NOTHING),  //ここは、合わせること。合わせないと、初回update時に配列インデックス範囲外になるため。
_pFrame_count(prm_pFrame_count)
{
    _num_progress = prm_num_progress;
    _paFrame_progress_changed = NEW frame[_num_progress+1];
    for (int i = 0; i < _num_progress+1; i++) {
        _paFrame_progress_changed[i] = (*_pFrame_count);
    }
}

progress GgafProgress::get() {
    return _progress;
}
void GgafProgress::set(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 1 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::set 進捗番号が範囲外です。set可能な進捗番号は(1～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    _progress_prev = _progress;
    _progress = prm_progress;
    _progress_next = prm_progress;
    _paFrame_progress_changed[prm_progress] = (*_pFrame_count);
}

void GgafProgress::setNothing() {
    _progress_prev = _progress;
    _progress = PROGRESS_NOTHING;
    _progress_next = PROGRESS_NOTHING;
    _paFrame_progress_changed[PROGRESS_NOTHING] = (*_pFrame_count);
}

frame GgafProgress::getFrameWhenChanged(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::getFrameWhenChanged 進捗番号が範囲外です。進捗番号範囲は(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    return (_paFrame_progress_changed[prm_progress]);
}

frame GgafProgress::getFrameInProgress() {
    return ((*_pFrame_count) - _paFrame_progress_changed[_progress]);
}


void GgafProgress::change(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 1 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::change 進捗番号が範囲外です。使用可能な進捗番号は(1～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
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
        throwGgafCriticalException("GgafProgress::changeNext 進捗番号が＋１で範囲外になりました。使用可能な進捗番号は(1～"<<_num_progress<<")です。_progress="<<_progress<<"");
    }
#endif
}


bool GgafProgress::isJustChangedTo(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::isJustChangedTo 進捗番号が範囲外です。\nisJustChangedTo 引数の使用可能な進捗番号は(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
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

bool GgafProgress::isJustChangedFrom(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::isJustChangedFrom 進捗番号が範囲外です。\nisJustChangedFrom 引数の使用可能な進捗番号は(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
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

progress GgafProgress::get_WhenJustChanged() {
    if (_progress != _progress_prev) {
        return _progress;
    } else {
        return 0; // = false
    }
}

progress GgafProgress::getPrev_WhenJustChanged() {
    if (_progress != _progress_prev) {
        return _progress_prev;
    } else {
        return 0; // = false
    }
}

progress GgafProgress::get_WhenWillChange() {
    if (_progress != _progress_next) {
        return _progress;
    } else {
        return 0; // = false
    }
}

progress GgafProgress::getNext_WhenWillChange() {
    if (_progress != _progress_next) {
        return _progress_next;
    } else {
        return 0; // = false
    }
}


void GgafProgress::update() {
    //進捗を反映する
    if (_progress != _progress_next) {
        _paFrame_progress_changed[_progress_next] = (*_pFrame_count) - 1;
    }
    _progress_prev = _progress;
    _progress = _progress_next;

}

GgafProgress::~GgafProgress() {
    DELETEARR_IMPOSSIBLE_NULL(_paFrame_progress_changed);

}

