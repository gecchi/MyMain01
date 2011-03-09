#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Magic::Magic(const char*      prm_name,
             MagicMeter* prm_pMagicMeter,
                 magic_point* prm_pMP,
                 int          prm_max_level,
                 magic_point  prm_cost_base, float prm_fRate_cost,
                 magic_time   prm_time_of_casting_base, float prm_fRate_time_of_casting,
                 magic_time   prm_time_of_invoking_base, float prm_fRate_time_of_invoking,
                 magic_time   prm_time_of_effect_base, float prm_fRate_time_of_effecting,
                 magic_point  prm_keep_cost_base, float prm_fRate_keep_cost
                ) : GgafObject() {
//    GgafDx9GeometricActor* prm_pCaster,
//     GgafDx9GeometricActor* prm_pReceiver) : GgafDx9BoardSetActor(prm_name, "magic") {
    _name = NEW char[20];
    strcpy(_name, prm_name);
    _pMP = prm_pMP;
    _pMagicMeter = prm_pMagicMeter;
    _new_level = 0;
    _level = 0;
    _max_level = prm_max_level;

//    _cost = _cost_base;

//    _time_of_casting = _time_of_casting_base;
//    _cast_speed = 100;

//    _left_time_to_expire =  _time_of_invoking;

    _cost_base             = prm_cost_base;
    _time_of_casting_base  = prm_time_of_casting_base;
    _time_of_invoking_base = prm_time_of_invoking_base;
    _time_of_effect_base   = prm_time_of_effect_base;
    _keep_cost_base        = prm_keep_cost_base;

    _fRate_cost               = prm_fRate_cost;
    _fRate_time_of_casting    = prm_fRate_time_of_casting;
    _fRate_time_of_invoking   = prm_fRate_time_of_invoking;
    _fRate_time_of_effecting  = prm_fRate_time_of_effecting;
    _fRate_keep_cost          = prm_fRate_keep_cost;

    //維持コストを予め設定
    for (int i = 0; i < _max_level; i++) {
        _lvinfo[i]._keep_cost = _keep_cost_base +  (i * _keep_cost_base * _fRate_keep_cost);
    }


    _executing_time = 0;
    _time_of_next_state = 0;
    _state = MAGIC_NOTHING;
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


bool Magic::execute(int prm_new_level) {
    if (_level == prm_new_level) {
        return false;
    } else {
        _new_level = prm_new_level;
        _is_leveling = true;
        _state = MAGIC_STAND_BY;
        return true;
    }
}
void Magic::cast() {
    _executing_time = 0;
    _time_of_next_state = _time_of_casting_base +  ( ((_new_level-1) - _level) * _time_of_casting_base * _fRate_time_of_casting);
    _state = MAGIC_CASTING;
    processCastBegin();
}

void Magic::invoke() {
    _executing_time = 0;
    _time_of_next_state = _time_of_invoking_base +  ( ((_new_level-1) - _level) * _time_of_invoking_base * _fRate_time_of_invoking);
    _lvinfo[_new_level]._is_working = true;
    _lvinfo[_new_level]._working_time = 0;

    _left_time_to_expire = _time_of_invoking;
    _state = MAGIC_INVOKING;
    processInvokeBegin();
}

void Magic::effect() {
    for (int i = 0; i < _new_level - _level; i++) {
        _lvinfo[_new_level+i]._remaining_time_of_effect = _time_of_effect_base +  i * _time_of_effect_base * _fRate_time_of_effecting;
    }
    _state = MAGIC_EXPIRING;
    processEffectBegin();
}

void Magic::abandon(int prm_last_level) {
    _lvinfo[prm_last_level]._is_effecting = false;
    processOnAbandon(prm_last_level);
    if (_level > 0) {
        _level--; //レベルダウン
    } else {

    }
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
////    for (int i = 0; i < _max_level; i++) {
//        if (_lvinfo[_level]._is_effecting) {
//            _lvinfo[_level]._remaining_time_of_effect --;
////            _lvinfo[i]._working_time ++;
//            if (_lvinfo[_level]._remaining_time_of_effect <= 0) {
//                abandon(_level);
//            }
//        }
////    }
    if (_is_leveling) {
        _executing_time++;
        switch (_state) {
            case MAGIC_STAND_BY:
                cast();       //詠唱開始
                break;
            case MAGIC_CASTING:
                if (_executing_time >= _time_of_next_state) {
                    invoke(); //発動開始
                } else {
                    processCastingBehavior();
                }
                break;
            case MAGIC_INVOKING:
                if (_executing_time >= _time_of_next_state) {
                    effect();  //持続開始
                } else {
                    processInvokeingBehavior();
                }
                break;
            case MAGIC_EFFECTING:
                _lvinfo[_level]._remaining_time_of_effect --;     //効果持続残り時間
                (*_pMP) -= _lvinfo[_level]._keep_cost;            //維持コスト
                if (_lvinfo[_level]._remaining_time_of_effect <= 0) { // || _pEnagyBar->_value <= 0.0) {
                    abandon(_level);
                } else {
                    processEffectingBehavior();
                }
                break;
            default :
                _TRACE_("Magic::processBehavior おかしいですぜ _state="<<_state);
                break;
        }
    }

}

void Magic::cancel() {
    _new_level = _level;
    _is_leveling = false;
    _state = MAGIC_NOTHING;
}

void Magic::commit() {
    if (_is_leveling) {
        _level = _new_level;
        _is_leveling = false;
        _lvinfo[_level]._is_working = true;
        _lvinfo[_level]._working_time = 0;
        _state = MAGIC_NOTHING;
    }
}

Magic::~Magic() {
    DELETEARR_IMPOSSIBLE_NULL(_name);
}
