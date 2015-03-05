#include "jp/ggaf/core/GgafProgress.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include <stdarg.h>

using namespace GgafCore;

GgafProgress::GgafProgress(frame* prm_p_frame_counter, int prm_num_progress) :
    GgafObject() ,
    _progress(PROGRESS_NOTHING),       //ここと
    _progress_prev(PROGRESS_NULL),
    _progress_next(PROGRESS_NOTHING),  //ここは、合わせること。合わせないと、初回update時に配列インデックス範囲外になるため。
    _p_frame_counter(prm_p_frame_counter),
    _num_progress(prm_num_progress)
{
    _pa_frame_of_progress_changed = NEW frame[_num_progress+1+1];
    for (int i = 0; i < _num_progress+1+1; i++) {
        _pa_frame_of_progress_changed[i] = (*_p_frame_counter);
    }
}
void GgafProgress::reset() {
    _progress_prev = PROGRESS_NULL;
    _progress = PROGRESS_NOTHING;
    _progress_next = PROGRESS_NOTHING;
    _pa_frame_of_progress_changed[PROGRESS_NOTHING+1] = (*_p_frame_counter);
}

void GgafProgress::reset(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::reset 進捗番号が範囲外です。reset(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    _progress_prev = PROGRESS_NULL;
    _progress = prm_progress;
    _progress_next = prm_progress;
    _pa_frame_of_progress_changed[prm_progress+1] = (*_p_frame_counter);
}

void GgafProgress::setNothing() {
    _progress_prev = _progress;
    _progress = PROGRESS_NOTHING;
    _progress_next = PROGRESS_NOTHING;
    _pa_frame_of_progress_changed[PROGRESS_NOTHING+1] = (*_p_frame_counter);
}

frame GgafProgress::getFrameWhenChanged(progress prm_progress) const {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::getFrameWhenChanged 進捗番号が範囲外です。進捗番号範囲は(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    return (_pa_frame_of_progress_changed[prm_progress+1]);
}

void GgafProgress::change(progress prm_progress) {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::change 進捗番号が範囲外です。使用可能な進捗番号は(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
    }
#endif
    _progress_next = prm_progress;
}

void GgafProgress::changeProbab(uint32_t prm_p1, progress prm_progress1, ...) {
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
            throwGgafCriticalException("GgafProgress::changeProbab p_sum="<<p_sum<<" 確率の合計がぴったり100になりません。（va_argで変な場所を読み込んだかも）");
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
        throwGgafCriticalException("GgafProgress::changeProbab p_sum="<<p_sum<<" 確率の合計がぴったり100になりません。");
    }
#endif
}

//void GgafProgress::changeProbab(uint32_t prm_p1, progress prm_progress1, ...) {
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
//        throwGgafCriticalException("GgafProgress::changeProbab 合計が100%になってない。");
//    }
//#endif
//}

void GgafProgress::changeNothing() {
    _progress_next = PROGRESS_NOTHING;
}

void GgafProgress::changeNext() {
#ifdef MY_DEBUG
    if (_progress_next == _progress+1) {
        _TRACE_("＜警告＞ gafProgress::changeNext 既に _progress="<<_progress<<" _progress_next="<<_progress_next<<" です。連続で changeNext() していませんか？");
    }
#endif
    _progress_next = _progress+1;
#ifdef MY_DEBUG
    if (_progress_next < 0 || _progress_next > _num_progress) {
        throwGgafCriticalException("GgafProgress::changeNext 進捗番号が＋１で範囲外になりました。使用可能な進捗番号は(1～"<<_num_progress<<")です。_progress="<<_progress<<"");
    }
#endif
}


bool GgafProgress::isJustChangedTo(progress prm_progress) const {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::isJustChangedTo 進捗番号が範囲外です。\nisJustChangedTo 引数の使用可能な進捗番号は(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
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

bool GgafProgress::isJustChangedFrom(progress prm_progress) const {
#ifdef MY_DEBUG
    if (prm_progress < 0 || prm_progress > _num_progress) {
        throwGgafCriticalException("GgafProgress::isJustChangedFrom 進捗番号が範囲外です。\nisJustChangedFrom 引数の使用可能な進捗番号は(0～"<<_num_progress<<")です。引数：prm_progress="<<prm_progress<<"");
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

progress GgafProgress::getProgOnChange() const {
    if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
        return _progress;
    } else {
        return PROGRESS_NULL;
    }
}

progress GgafProgress::getFromProgOnChange() const {
    if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
        return _progress_prev;
    } else {
        return PROGRESS_NULL;
    }
}

progress GgafProgress::getProgWhenProgWillChange() const {
    if (_progress != _progress_next) {
        return _progress;
    } else {
        return PROGRESS_NULL;
    }
}

progress GgafProgress::getToProgWhenProgWillChange() const {
    if (_progress != _progress_next) {
        return _progress_next;
    } else {
        return PROGRESS_NULL;
    }
}

void GgafProgress::update() {
    //進捗を反映する
    if (_progress != _progress_next) {
        _pa_frame_of_progress_changed[_progress_next+1] = (*_p_frame_counter) - 1;
    }
    _progress_prev = _progress;
    _progress = _progress_next;
}

GgafProgress::~GgafProgress() {
    GGAF_DELETEARR(_pa_frame_of_progress_changed);
}

