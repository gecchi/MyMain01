#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafProgress::GgafProgress(frame* prm_pFrame_behaving, int prm_num) : GgafObject() ,
_progress(-1),
_progress_prev(-2),
_progress_nextframe(-3),
_pFrame_behaving(prm_pFrame_behaving)
{
    _paFrame_ProgressChange = NEW frame[prm_num];
    DWORD x = UINT_MAX/2;
    for (int i = 0; i < prm_num; i++) {
        _paFrame_ProgressChange[i] = x; //有りえないフレームなら良い
    }
}


int GgafProgress::get() {
    return _progress;
}

frame GgafProgress::getFrameAtChanged(int prm_progress) {
    return _paFrame_ProgressChange[prm_progress];
}

frame GgafProgress::getActivePartFrameIn() {
    return (*_pFrame_behaving)+1 - _paFrame_ProgressChange[_progress];
}


void GgafProgress::change(int prm_progress) {
    _progress_nextframe = prm_progress;
    _paFrame_ProgressChange[prm_progress] = (*_pFrame_behaving)+1;
}

void GgafProgress::changeNext() {
    _progress_nextframe = _progress+1;
    _paFrame_ProgressChange[_progress+1] = (*_pFrame_behaving)+1;
}


bool GgafProgress::onActive(int prm_progress) {
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

bool GgafProgress::onInactive(int prm_progress) {
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


int GgafProgress::getOnActive() {
    if (_progress != _progress_prev) {
        return _progress;
    } else {
        return 0; // = false
    }
}

int GgafProgress::getOnInactive() {
    if (_progress != _progress_prev) {
        return _progress_prev;
    } else {
        return 0; // = false
    }
}

void GgafProgress::update() {
    //進捗を反映する
    _progress_prev = _progress;
    _progress = _progress_nextframe;

}

GgafProgress::~GgafProgress() {
    DELETEARR_IMPOSSIBLE_NULL(_paFrame_ProgressChange);

}

