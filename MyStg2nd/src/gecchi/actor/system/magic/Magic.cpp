#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Magic::Magic(const char*      prm_name,
                 int          prm_max_level,
                 magic_point  prm_cost_base,
                 magic_time   prm_time_of_casting_base,
                 magic_time   prm_time_of_invoking) : GgafObject() {
//    GgafDx9GeometricActor* prm_pCaster,
//     GgafDx9GeometricActor* prm_pReceiver) : GgafDx9BoardSetActor(prm_name, "magic") {
    _name = NEW char[20];
    strcpy(_name, prm_name);

    _new_level = 0;
    _level = 0;
    _max_level = prm_max_level;
    _cost_base = prm_cost_base;
    _cost = _cost_base;
    _time_of_casting_base = prm_time_of_casting_base;
    _time_of_casting = _time_of_casting_base;
    _cast_speed = 100;
    _time_of_invoking = prm_time_of_invoking;
    _left_time_to_expire =  _time_of_invoking;
    _state = MAGIC_STAND_BY;
    _is_leveling = false;
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

bool Magic::setLevel(int prm_new_level) {
    if (_level == prm_new_level) {
        return false;
    } else {
        _new_level = prm_new_level;
        _is_leveling = true;
        return true;
    }
}
void Magic::cast() {
    _time_of_casting = _time_of_casting_base;
    _state = MAGIC_CASTING;
    processCastBegin();
}

void Magic::invoke() {
    _lvinfo[_new_level]._is_working = true;
    _lvinfo[_new_level]._working_time = 0;

    _left_time_to_expire = _time_of_invoking;
    _state = MAGIC_INVOKING;
    processInvokeBegin();
}

void Magic::expire() {
    _state = MAGIC_EXPIRING;
    processExpireBegin();
}

void Magic::abandon(int prm_last_level) {
    _lvinfo[prm_last_level]._is_working = false;
    processOnAbandon(prm_last_level);
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
    for (int i = 0; i < _max_level; i++) {
        if (_lvinfo[i]._is_working) {
            _lvinfo[i]._working_time ++;
            if (_lvinfo[i]._time_of_abandon < _lvinfo[i]._working_time) {
                abandon(i);
            }
        }
    }
    if (_is_leveling) {
        switch (_state) {
            case MAGIC_STAND_BY:
                break;
            case MAGIC_CASTING:
                _time_of_casting -= _cast_speed;
                if (_time_of_casting < 0) {
                    invoke();
                } else {
                    processCastingBehavior();
                }
                break;
            case MAGIC_INVOKING:
                _left_time_to_expire -= _cast_speed;
                if (_left_time_to_expire < 0) {
                    expire();
                } else {
                    processInvokeingBehavior();
                }
                break;
            case MAGIC_EXPIRING:
                processExpiringBehavior();
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
        _lvinfo[_level]._is_working = true;
        _lvinfo[_level]._working_time = 0;
        _state = MAGIC_STAND_BY;
    }
}

Magic::~Magic() {
    DELETEARR_IMPOSSIBLE_NULL(_name);
}
