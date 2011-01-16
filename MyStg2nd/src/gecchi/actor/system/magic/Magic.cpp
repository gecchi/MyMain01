#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Magic::Magic(const char* prm_name, int prm_max_level) : GgafObject() {
//    GgafDx9GeometricActor* prm_pCaster,
//     GgafDx9GeometricActor* prm_pReceiver) : GgafDx9BoardSetActor(prm_name, "magic") {
    _name = NEW char[20];
    strcpy(_name, prm_name);
    _new_level = 0;
    _level = 0;
    _max_level = prm_max_level;
    _cost = 10000000;
    _cast_speed = 60;
    _duration = 1;
    _state = MAGIC_STAND_BY;
    _pCaster = NULL;
    _pReceiver = NULL;
    _rr = 0.0f;
    _velo_rr = 0.0f;
}
void Magic::rollOpen() {
    _velo_rr = 0.1;
}
void Magic::rollClose() {
    _velo_rr = -0.02;
}

void Magic::setLevel(int prm_new_level) {
    if (_level == prm_new_level) {
        return;
    }
    _new_level = prm_new_level;
    _is_leveling = true;
    if (_level < prm_new_level) {
        cast();
    } else {
        abandon();
    }
}
void Magic::cast() {
    _dec_cost = _cost / _cast_speed;
    _state = MAGIC_CASTING;
    processCastBegin();
}

void Magic::invoke() {
    _state = MAGIC_INVOKEING;
    processInvokeBegin();
}

void Magic::expire() {
    _state = MAGIC_EXPIRING;
    processExpireBegin();
}

void Magic::abandon() {
    _state = MAGIC_ABANDONING;
    processAbandonBegin();
}

void Magic::behave() {
    _rr += _velo_rr;
    if (_rr < 0.0f) {
        _rr = 0.0f;
        _velo_rr = 0.0f;
    }
    if (_rr > 1.0f) {
        _rr = 1.0f;
        _velo_rr = 0.0f;
    }
    if (_is_leveling) {
        switch (_state) {
            case MAGIC_STAND_BY:
                break;
            case MAGIC_CASTING:
                _cost = _cost - _dec_cost;
                if (_cost < 0) {
                    invoke();
                } else {
                    processCastingBehavior();
                }
                break;
            case MAGIC_INVOKEING:
                _duration --;
                if (_duration < 0) {
                    expire();
                } else {
                    processInvokeingBehavior();
                }
                break;
            case MAGIC_EXPIRING:
                processExpiringBehavior();
                break;
            case MAGIC_ABANDONING:
                processAbandoningBehavior();
                break;
            default :
                _TRACE_("Magic::processBehavior ‚¨‚©‚µ‚¢‚Å‚·‚º _state="<<_state);
                break;
        }
    }

}

void Magic::cancel() {
    _new_level = _level;
    _is_leveling = false;
    _state = MAGIC_STAND_BY;
}

void Magic::commit() {
    if (_is_leveling) {
        _level = _new_level;
        _is_leveling = false;
        _state = MAGIC_STAND_BY;
    }
}

Magic::~Magic() {
	DELETEARR_IMPOSSIBLE_NULL(_name);
}
