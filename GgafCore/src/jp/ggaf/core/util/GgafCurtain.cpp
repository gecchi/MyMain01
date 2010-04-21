#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCurtain::GgafCurtain(int prm_curtain_length) : GgafObject() {
    _curtain_length = prm_curtain_length;
    _now_curtain_length = prm_curtain_length; //ç≈èâÇÕï¬Ç∂ÇƒÇ¢ÇÈ
    _opening_velocity = 0;
    _closeing_velocity = 0;

}

void GgafCurtain::open(int prm_opening_velocity) {
    _opening_velocity = prm_opening_velocity;
    _state = OPEN;
}

void GgafCurtain::close(int prm_closeing_velocity) {
    _closeing_velocity = prm_closeing_velocity;
    _state = CLOSE;
}

void GgafCurtain::behave() {

    if (_state == OPEN) {
        processOpenBegin();
        _state = OPENING;
    } else if (_state == OPENING) {
        _now_curtain_length -= _opening_velocity;
        if (_now_curtain_length < 0) {
            _now_curtain_length = 0;
            _state = OPENED;
            processOpenDone();
        } else {
            processOpening();
        }

    } else if (_state == CLOSE) {
        processOpenBegin();
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

