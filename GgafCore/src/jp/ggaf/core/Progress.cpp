#include "jp/ggaf/core/Progress.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"
#include <stdarg.h>

using namespace GgafCore;

Progress::Progress(frame* prm_p_frame_counter) :
    Object() ,
    _progress(PROGRESS_NOTHING),       //ここと
    _progress_prev(PROGRESS_NULL),
    _progress_next(PROGRESS_NOTHING),  //ここは、合わせること。合わせないと、初回update時に配列インデックス範囲外になるため。
    _p_frame_counter(prm_p_frame_counter)
{
    _map_changed_frame[_progress] = (*_p_frame_counter);
}

void Progress::reset() {
    _progress_prev = PROGRESS_NULL;
    _progress = PROGRESS_NOTHING;
    _progress_next = PROGRESS_NOTHING;
    _map_changed_frame[_progress] = (*_p_frame_counter);
}

void Progress::reset(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0) {
        throwCriticalException("進捗番号が負です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    _progress_prev = PROGRESS_NULL;
    _progress = prm_progress;
    _progress_next = prm_progress;
    _map_changed_frame[_progress] = (*_p_frame_counter);
}

void Progress::setNothing() {
    _progress_prev = _progress;
    _progress = PROGRESS_NOTHING;
    _progress_next = PROGRESS_NOTHING;
    _map_changed_frame[_progress] = (*_p_frame_counter);
}

frame Progress::getFrameWhenChanged(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0) {
        throwCriticalException("進捗番号が負です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    return (_map_changed_frame[prm_progress]);
}

void Progress::change(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0) {
        throwCriticalException("進捗番号が負です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    _progress_next = prm_progress;
}

void Progress::changeProbab(uint32_t prm_p1, progress prm_progress1, ...) {
    uint32_t r = (uint32_t)(RND(1,100));
    if (prm_p1 >= r) {
        change(prm_progress1);
        return;
    }
    uint32_t p_sum = (uint32_t)prm_p1;
    va_list args;
    va_start(args, prm_progress1);
    while (p_sum < 100) {
        p_sum += va_arg(args, uint32_t);
#ifdef MY_DEBUG
        if (p_sum > 100) {
            throwCriticalException("p_sum="<<p_sum<<" 確率の合計がぴったり100になりません。（va_argで変な場所を読み込んだかも）");
            return;
         }
#endif
        progress prog = va_arg(args, progress);
        if (p_sum >= r) {
            change(prog);
            return;
        }
    }
    va_end(args);
#ifdef MY_DEBUG
    if (p_sum != 100) {
        throwCriticalException("p_sum="<<p_sum<<" 確率の合計がぴったり100になりません。");
    }
#endif
}

//void Progress::changeProbab(uint32_t prm_p1, progress prm_progress1, ...) {
//    uint32_t r = (uint32_t)(RND(1,100));
//    if (prm_p1 <= r) {
//        change(prm_progress1);
//        return;
//    }
//    uint32_t p_sum = (uint32_t)prm_p1;
//
//    va_list args;
//    va_start(args, prm_progress1);
//    while(p_sum < 100) {
//        p_sum += va_arg(args, uint32_t);
//        progress prog = va_arg(args, progress);
//        if (p_sum <= r) {
//            change(prog);
//            return;
//        }
//    }
//    va_end(args);
//#ifdef MY_DEBUG
//    if (p_sum != 100) {
//        throwCriticalException("合計が100%になってない。");
//    }
//#endif
//}

void Progress::changeNothing() {
    _progress_next = PROGRESS_NOTHING;
}

void Progress::changeNext() {
#ifdef MY_DEBUG
    if (_progress_next == _progress+1) {
        throwCriticalException("既に _progress="<<_progress<<" _progress_next="<<_progress_next<<" です。連続で changeNext() していませんか？");
    }
#endif
    _progress_next = _progress + 1;
#ifdef MY_DEBUG
    if (_progress_next < 0) {
        throwCriticalException("進捗番号が＋１で、なぜか負の数です範囲外になりました。_progress="<<_progress<<"");
    }
#endif
}


bool Progress::hasJustChangedTo(progress prm_progress) const {
#ifdef MY_DEBUG
    if (prm_progress < 0) {
        throwCriticalException("進捗番号が負です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
        if (prm_progress == _progress) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Progress::hasJustChangedFrom(progress prm_progress) const {
#ifdef MY_DEBUG
    if (prm_progress < 0) {
        throwCriticalException("進捗番号が負です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
        if (prm_progress == _progress_prev) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

progress Progress::getProgOnChange() const {
    if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
        return _progress;
    } else {
        return PROGRESS_NULL;
    }
}

progress Progress::getFromProgOnChange() const {
    if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
        return _progress_prev;
    } else {
        return PROGRESS_NULL;
    }
}

progress Progress::getProgWhenProgWillChange() const {
    if (_progress != _progress_next) {
        return _progress;
    } else {
        return PROGRESS_NULL;
    }
}

progress Progress::getToProgWhenProgWillChange() const {
    if (_progress != _progress_next) {
        return _progress_next;
    } else {
        return PROGRESS_NULL;
    }
}

void Progress::update() {
    //進捗を反映する
    if (_progress != _progress_next) {
        _map_changed_frame[_progress_next] = (*_p_frame_counter) - 1;
    }
    _progress_prev = _progress;
    _progress = _progress_next;
}

Progress::~Progress() {
}

