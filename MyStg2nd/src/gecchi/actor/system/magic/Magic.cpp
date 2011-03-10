#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Magic::Magic(const char*  prm_name,
             int          prm_max_level,
             magic_point  prm_cost_base            , float prm_fRate_cost             ,
             magic_time   prm_time_of_casting_base , float prm_fRate_time_of_casting  ,
             magic_time   prm_time_of_invoking_base, float prm_fRate_time_of_invoking ,
             magic_time   prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
             magic_point  prm_keep_cost_base       , float prm_fRate_keep_cost
                ) : GgafMainActor(prm_name) {
//    GgafDx9GeometricActor* prm_pCaster,
//     GgafDx9GeometricActor* prm_pReceiver) : GgafDx9BoardSetActor(prm_name, "magic") {
    _name = NEW char[20];
    strcpy(_name, prm_name);
    _pMP = NULL; //initialize()で設定する。
    _new_level = 0;
    _last_level = 0;
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

    //飛びレベル差別情報を設定
    _interest_cost[0] = 0;
    _interest_time_of_casting[0] = 0;
    _interest_time_of_invoking[0] = 0;
    for (int i = 1; i <= _max_level; i++) {
        _interest_cost[i]             = (_cost_base * i) * _fRate_cost;
        _interest_time_of_casting[i]  = (_time_of_casting_base * i) *  prm_fRate_time_of_casting;
        _interest_time_of_invoking[i] = (_time_of_invoking_base * i) *  prm_fRate_time_of_invoking;
    }

    //各レベル別持続時間及び、維持コストを予め設定
    _lvinfo[0]._keep_cost = 0;
    for (int i = 1; i <= _max_level; i++) {
        _lvinfo[i]._remaining_time_of_effect = 0;
        _lvinfo[i]._time_of_effect = _time_of_effect_base +  ((i-1) * _time_of_effect_base * prm_time_of_effect_base);
        _lvinfo[i]._keep_cost = _keep_cost_base +  ((i-1) * _keep_cost_base * _fRate_keep_cost);
    }

    _time_of_next_state = 0;
    _pProgress->set(MAGIC_NOTHING);
    _is_working = false;
    _pCaster = NULL;
    _pReceiver = NULL;
    _rr = 0.0f;
    _velo_rr = 0.0f;

    useProgress();
}

void Magic::initialize()  {
    _pMP = &(P_MYSHIP_SCENE->_pEnagyBar->_amount); //MPに当たるAmountGraph
}


void Magic::rollOpen() {
    _velo_rr = 0.1;
}
void Magic::rollClose() {
    _velo_rr = -0.02;
}

int Magic::chkExecuteAble(int prm_new_level) {
    if (_pProgress->get() == MAGIC_INVOKING) {
        //発動中のため実行不可
        return MAGIC_EXECUTE_NG_INVOKING;
    } else {
        if (_level > prm_new_level) {
            return MAGIC_EXECUTE_OK_LEVELDOWN;
        } else if (_level < prm_new_level) {
            if (_interest_cost[prm_new_level-_level] < _pMP->get()) {
                return MAGIC_EXECUTE_OK_LEVELUP;
            } else {
                return MAGIC_EXECUTE_NG_MP_IS_SHORT;
            }
        } else {
            return MAGIC_EXECUTE_THE_SAME_LEVEL;
        }
    }
}
void Magic::execute(int prm_new_level) {
    int r = chkExecuteAble(prm_new_level);
    if (r > 0) {
        _new_level = prm_new_level;

        _is_working = true;
        if (r == MAGIC_EXECUTE_OK_LEVELUP) {
            //レベルアップ
                        _pProgress->change(MAGIC_STAND_BY);
        } else if (r == MAGIC_EXECUTE_OK_LEVELDOWN) {
            //レベルダウン
            //TODO:MP増加
            //現在を停止し
            _lvinfo[_level]._is_working = false;
            _lvinfo[_level]._remaining_time_of_effect = 0;
            //飛び越し
            for (int i = _level-1; i <= prm_new_level+1; i--) {
                _lvinfo[i]._is_working = false; //停止し
                _lvinfo[i]._remaining_time_of_effect = 0;
            }
            //新しい低いレベルを設定
            _lvinfo[prm_new_level]._is_working = true;
            processOnLevelDown(_level, prm_new_level); //下位の処理実行

            _pProgress->change(MAGIC_EFFECTING);
        }
    }
}



void Magic::cancel() {
    _new_level = _level;
    _is_working = false;
    _pProgress->change(MAGIC_NOTHING);
}

//void Magic::commit() {
//    if (_is_working) {
//        _level = _new_level;
//        _is_working = false;
//        _lvinfo[_level]._is_working = true;
////        _lvinfo[_level]._working_time = 0;
//        _pProgress->change(MAGIC_NOTHING);
//    }
//}



void Magic::processBehavior() {
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
//        if (_lvinfo[_level]._is_working) {
//            _lvinfo[_level]._remaining_time_of_effect --;
////            _lvinfo[i]._working_time ++;
//            if (_lvinfo[_level]._remaining_time_of_effect <= 0) {
//                abandon(_level);
//            }
//        }
////    }
    if (_is_working) {

        switch (_pProgress->get()) {
            /////////////////////////////////////// 待機
            case MAGIC_STAND_BY:
                _pProgress->change(MAGIC_CASTING);
                break;

            /////////////////////////////////////// 詠唱
            case MAGIC_CASTING:
                if (_pProgress->isJustChanged()) {
                    //詠唱開始、詠唱終了時間を計算
                    _time_of_next_state = _interest_time_of_casting[_new_level- _level];
                    processCastBegin(_level, _new_level);
                }
                //詠唱中
                processCastingBehavior(_level, _new_level);

                if (_pProgress->getActivePartFrameInProgress() >= _time_of_next_state) {
                    //詠唱終了
                    processCastFinish(_level, _new_level);
                    _pProgress->change(MAGIC_INVOKING);
                }
                break;

            /////////////////////////////////////// 発動
            case MAGIC_INVOKING:
                if (_pProgress->isJustChanged()) {
                    //発動開始、
                    //発動終了時間設定
                    _time_of_next_state = _interest_time_of_invoking[_new_level- _level];

                    processInvokeBegin(_level, _new_level);
                }
                //発動中
                processInvokeingBehavior(_level, _new_level);

                if (_pProgress->getActivePartFrameInProgress() >= _time_of_next_state) {
                    //発動終了
                    //レベル変更適用
                    _last_level = _level;
                    _level = _new_level;

                    //以前を停止し
                    _lvinfo[_last_level]._is_working = false;
                    //飛び越しは持続時間を満タンを設定
                    for (int i = _last_level+1; i <= _level-1; i++) {
                        _lvinfo[i]._is_working = false; //停止し
                        _lvinfo[i]._remaining_time_of_effect = _lvinfo[i]._time_of_effect; //持続時間を満タン
                    }
                    //今回レベルを設定
                    _lvinfo[_level]._is_working = true;
                    _lvinfo[_level]._remaining_time_of_effect = _lvinfo[_level]._time_of_effect; //持続時間を満タン
                    _pMP->dec(_interest_cost[_new_level-_level]); //MP消費

                    processInvokeFinish(_last_level, _level);
                    _pProgress->change(MAGIC_EFFECTING);
                }
                break;

            /////////////////////////////////////// 持続
            case MAGIC_EFFECTING:
                if (_pProgress->isJustChanged()) {
                    //持続開始
                    processEffectBegin(_level);
                }
                //持続中
                _lvinfo[_level]._remaining_time_of_effect --;     //効果持続残り時間
                _pMP->inc(-1*_lvinfo[_level]._keep_cost); //維持コスト
                processEffectingBehavior(_level);

                if (_lvinfo[_level]._remaining_time_of_effect <= 0) { // || _pEnagyBar->_value <= 0.0) {
                    processEffectFinish(_level);
                    _lvinfo[_level]._is_working = false;
                    if (_level > 0) {
                        execute(_level-1);
                    } else {
                        _pProgress->change(MAGIC_NOTHING);
                    }
                }
                break;

            default :
                break;
        }
    }

}
Magic::~Magic() {
    DELETEARR_IMPOSSIBLE_NULL(_name);
}
