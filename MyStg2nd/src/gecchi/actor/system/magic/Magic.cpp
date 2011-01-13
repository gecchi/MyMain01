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
    _level = 0;
    _max_level = prm_max_level;
    _cost = 10000000;
    _cast_speed = 60;
    _duration = 1;
    _state = MAGIC_STAND_BY;
    _pCaster = NULL;
    _pReceiver = NULL;

}

void Magic::setLevel(int prm_new_level) {
    if (_level == prm_new_level) {
        return;
    } else {
        _velo_move_level = (_level-prm_new_level)*0.1;//10ƒtƒŒ‚Å
    }
    _prev_level = _level;
    _level = prm_new_level;
    _flevel = _prev_level;
    _is_move_level = true;
}


void Magic::behave() {
    if (_is_move_level) {
        _flevel += _velo_move_level;
        if (_level < _flevel) {
            _flevel = _level;
            _is_move_level = false;
        }
    }
    if (_pCaster->isActive() && _pReceiver->isActive() ) {
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
            default :
                _TRACE_("Magic::processBehavior ‚¨‚©‚µ‚¢‚Å‚·‚º _state="<<_state);
                break;
        }
    } else {
        if (_state != MAGIC_ABANDONING) {
            abandon();
        } else {
            processAbandoningBehavior();
        }
    }

}


Magic::~Magic() {
}
