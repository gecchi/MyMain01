#include "stdafx.h"
#include "jp/ggaf/core/util/GgafCurtain.h"

using namespace GgafCore;

GgafCurtain::GgafCurtain(float prm_curtain_length) : GgafObject() {
    _curtain_length = prm_curtain_length;
    _now_curtain_length = 0.0f; //ç≈èâÇÕäJÇ¢ÇƒÇ¢Ç‹Ç∑
    _state = OPENED;
    _opening_velocity = 0.0f;
    _closing_velocity = 0.0f;
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

void GgafCurtain::close(float prm_closing_velocity) {
    _closing_velocity = prm_closing_velocity;
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
        _now_curtain_length += _closing_velocity;
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

