#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCurtain::GgafCurtain(GgafScene* prm_pScene) : GgafObject() {
    _pScene = prm_pScene;
    _curtain_length = 1.0f;
    _now_curtain_length = 0.0f; //最初は開いています
    _state = OPENED;
    _opening_velocity = 0.0f;
    _closeing_velocity = 0.0f;

}

void GgafCurtain::open(float prm_opening_velocity) {
    _opening_velocity = prm_opening_velocity;
    _state = OPEN;
}

void GgafCurtain::open() {
    _now_curtain_length = 0.0f;
    _state = OPENED;
    processOpenDone();
}

void GgafCurtain::close(float prm_closeing_velocity) {
    _closeing_velocity = prm_closeing_velocity;
    _state = CLOSE;
}

void GgafCurtain::close() {
    _now_curtain_length = _curtain_length;
    _state = CLOSED;
    processCloseDone();
}


void GgafCurtain::behave() {

    if (_state == OPEN) {
        processOpenBegin();
        _state = OPENING;
    } else if (_state == OPENING) {
        _now_curtain_length -= _opening_velocity;
        if (_now_curtain_length < 0) {
            _now_curtain_length = 0.0f;
            _state = OPENED;
            processOpenDone();
        } else {
            processOpening();
        }

    } else if (_state == CLOSE) {
        processCloseBegin();
        _state = CLOSING;
    } else if (_state == CLOSING) {
        _now_curtain_length += _closeing_velocity;
        if (_now_curtain_length > _curtain_length) {
            _now_curtain_length = _curtain_length;
            _state = CLOSED;
            processCloseDone();
        } else {
            processClosing();
        }
    }

}
GgafCurtain::~GgafCurtain() {
}

