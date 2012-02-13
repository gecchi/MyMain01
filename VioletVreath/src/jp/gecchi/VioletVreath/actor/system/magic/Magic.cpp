#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Magic::Magic(const char*  prm_name, AmountGraph* prm_pMP,
             int          prm_max_level,
             magic_point  prm_cost_base            , float prm_fRate_cost             ,
             magic_time   prm_time_of_casting_base , float prm_fRate_time_of_casting  ,
             magic_time   prm_time_of_invoking_base, float prm_fRate_time_of_invoking ,
             magic_time   prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
             magic_point  prm_keep_cost_base       , float prm_fRate_keep_cost
                ) : GgafMainActor(prm_name, NULL) {
//    GgafDxGeometricActor* prm_pCaster,
//     GgafDxGeometricActor* prm_pReceiver) : GgafDxBoardSetActor(prm_name, "magic") {
    _pMP = prm_pMP;
    _new_level = 0;
    _last_level = 0;
    _level = 0;
    _max_level = prm_max_level;
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
        _interest_time_of_casting[i]  = (_time_of_casting_base * i) *  _fRate_time_of_casting;
        _interest_time_of_invoking[i] = (_time_of_invoking_base * i) *  _fRate_time_of_invoking;
    }

    //各レベル別持続時間及び、維持コストを予め設定
    _lvinfo[0]._is_working = false;
    _lvinfo[0]._remaining_time_of_effect = 0;
    _lvinfo[0]._time_of_effect = 0;
    _lvinfo[0]._keep_cost = 0;
    for (int i = 1; i <= _max_level; i++) {
        _lvinfo[i]._is_working = false;
        _lvinfo[i]._remaining_time_of_effect = 0;
        _lvinfo[i]._time_of_effect = _time_of_effect_base + ((i-1) * _time_of_effect_base * _fRate_time_of_effecting);
        _lvinfo[i]._keep_cost      = _keep_cost_base      + ((i-1) * _keep_cost_base * _fRate_keep_cost);
    }

    _time_of_next_state = 0;

    _is_working = false;
    _rr = 0.0f;
    _velo_rr = 0.0f;

    useProgress(MAGIC_STATE_ABANDONING);
    _pProg->set(MAGIC_STATE_NOTHING);
}

void Magic::save(stringstream& sts) {
    sts << _max_level  << " " <<
           _level      << " " <<
           _new_level  << " " <<
           _last_level << " ";
    for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
        sts <<  _lvinfo[lv]._is_working               << " " <<
                _lvinfo[lv]._remaining_time_of_effect << " " <<
                _lvinfo[lv]._time_of_effect           << " " <<
                _lvinfo[lv]._keep_cost                << " " <<
                _lvinfo[lv]._pno                      << " ";
    }
}

void Magic::load(stringstream& sts) {
    sts >> _max_level
        >> _level
        >> _new_level
        >> _last_level;

    for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
        sts >> _lvinfo[lv]._is_working
            >> _lvinfo[lv]._remaining_time_of_effect
            >> _lvinfo[lv]._time_of_effect
            >> _lvinfo[lv]._keep_cost
            >> _lvinfo[lv]._pno;
    }
    effect(_level); //MAGIC_EFFECT_NOTHINGだからOKと思う
}

void Magic::rollOpen() {
    _velo_rr = 0.1;
}
void Magic::rollClose() {
    _velo_rr = -0.01;
}

int Magic::chkCastAble(int prm_new_level) {
    if (_pProg->get() == MAGIC_STATE_INVOKING) {
        return MAGIC_CAST_NG_INVOKING_NOW; //発動中のため実行不可
    } else if (_pProg->get() == MAGIC_STATE_CASTING) {
        //他のレベルを詠唱中に詠唱再実行
        if (_level > prm_new_level) {
            return MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN; //再詠唱レベルダウンOK
        } else if (_level < prm_new_level) {
            if (_interest_cost[prm_new_level-_level] < _pMP->get()) {
                return MAGIC_CAST_OK_CANCEL_AND_LEVELUP; //再詠唱レベルアップOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MPが足りないため、再詠唱レベルアップ不可
            }
        } else { //_level==prm_new_level
            return MAGIC_CAST_CANCEL; //詠唱キャンセル
        }
    } else {
        //待機状態か効果持続中に詠唱実行
        if (_level > prm_new_level) {
            return MAGIC_CAST_OK_LEVELDOWN; //詠唱レベルダウンOK
        } else if (_level < prm_new_level) {
            if (_interest_cost[prm_new_level-_level] < _pMP->get()) {
                return MAGIC_CAST_OK_LEVELUP; //詠唱レベルアップOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MPが足りないため、再詠唱レベルアップ不可
            }
        } else { //_level==prm_new_level
            return MAGIC_CAST_NOTHING; //何もしない。
        }
    }
}
int Magic::cast(int prm_new_level) {
    int r = chkCastAble(prm_new_level);
    switch (r) {
        case MAGIC_CAST_NG_INVOKING_NOW: {
            break;
        }
        case MAGIC_CAST_NG_MP_IS_SHORT: {
            break;
        }
        case MAGIC_CAST_NOTHING: {
            break;
        }
        case MAGIC_CAST_CANCEL: {
            _is_working = false;
            _new_level = prm_new_level;
            _pProg->change(MAGIC_STATE_NOTHING);
            break;
        }
        case MAGIC_CAST_OK_LEVELUP: {
            _is_working = true;
            _new_level = prm_new_level;
            _pProg->change(MAGIC_STATE_CASTING);
            break;
        }
        case MAGIC_CAST_OK_LEVELDOWN: {
            _is_working = true;
            effect(prm_new_level);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
            _is_working = true;
            _new_level = prm_new_level;
            _pProg->change(MAGIC_STATE_CASTING);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
            _is_working = true;
            effect(prm_new_level);
            break;
        }
    }
    return r;
}

int Magic::chkInvokeAble(int prm_new_level) {
    if (_pProg->get() == MAGIC_STATE_INVOKING) {
        //発動中のため実行不可
        return MAGIC_INVOKE_NG_INVOKING_NOW;
    } else {
        if (_level > prm_new_level) {
            return MAGIC_INVOKE_OK_LEVELDOWN;
        } else if (_level < prm_new_level) {
            if (_interest_cost[prm_new_level-_level] < _pMP->get()) {
                return MAGIC_INVOKE_OK_LEVELUP;
            } else {
                return MAGIC_INVOKE_NG_MP_IS_SHORT;
            }
        } else { //_level==prm_new_level
            return MAGIC_INVOKE_NOTHING;
        }
    }
}

int Magic::chkEffectAble(int prm_level) {
    if (_level > prm_level) {
        return MAGIC_EFFECT_OK_LEVELDOWN;
    } else if (_level < prm_level) {
        if (_interest_cost[prm_level-_level] < _pMP->get()) {
            return MAGIC_EFFECT_OK_LEVELUP;
        } else {
            return MAGIC_EFFECT_NG_MP_IS_SHORT;
        }
    } else { //_level==prm_new_level
        return MAGIC_EFFECT_NOTHING;
    }
}


int Magic::invoke(int prm_new_level) {
    int r = chkInvokeAble(prm_new_level);
    switch (r) {
        case MAGIC_INVOKE_NG_INVOKING_NOW: {
            break;
        }
        case MAGIC_INVOKE_NG_MP_IS_SHORT: {
            break;
        }
        case MAGIC_INVOKE_OK_LEVELUP: {
            _new_level = prm_new_level;
            _pProg->change(MAGIC_STATE_INVOKING);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELDOWN: {
            _is_working = true;
            effect(prm_new_level);
            break;
        }
        case MAGIC_INVOKE_NOTHING: {
            break;
        }
    }
    return r;
}
int Magic::effect(int prm_level) {
    int r = chkEffectAble(prm_level);

    switch (r) {
        case MAGIC_EFFECT_NG_MP_IS_SHORT: {
            break;
        }
        case MAGIC_EFFECT_NOTHING: {
            break;
        }
        case MAGIC_EFFECT_OK_LEVELUP: {
            //現在魔法レベルは停止して
            _lvinfo[_level]._is_working = false;
            //レベル更新
            _last_level = _level;
            _level = prm_level;
            _pProg->change(MAGIC_STATE_EFFECT_BEGEIN);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            //現在魔法レベルは停止して
            _lvinfo[_level]._is_working = false;
            //レベル更新
            _last_level = _level;
            _level = prm_level;
            _pProg->change(MAGIC_STATE_EFFECT_BEGEIN);
            break;
        }
    }
    return r;
}

void Magic::cancel() {
    _new_level = _level;
    _is_working = false;
    _pProg->change(MAGIC_STATE_NOTHING);
}

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
    if (_is_working) {

        switch (_pProg->get()) {
            /////////////////////////////////////// 待機
            case MAGIC_STATE_STAND_BY: {
                break;
            }
            /////////////////////////////////////// 詠唱
            case MAGIC_STATE_CASTING: {
                if (_pProg->isJustChanged()) { //詠唱開始
                    //詠唱開始
                    //詠唱終了時間を計算
                    _time_of_next_state = _interest_time_of_casting[_new_level- _level];
                    processCastBegin(_level, _new_level);  //コールバック
                }

                //詠唱中
                processCastingBehavior(_level, _new_level); //コールバック

                if (_pProg->getFrameInProgress() >= _time_of_next_state) {
                    //詠唱終了
                    processCastFinish(_level, _new_level);  //コールバック
                    invoke(_new_level);
                }
                break;
            }
            /////////////////////////////////////// 発動
            case MAGIC_STATE_INVOKING: {
                if (_pProg->isJustChanged()) {
                    //発動開始、
                    //発動終了時間設定
                    _time_of_next_state = _interest_time_of_invoking[_new_level- _level];
                    processInvokeBegin(_level, _new_level);     //コールバック
                }

                //発動中
                processInvokeingBehavior(_level, _new_level);  //コールバック

                if (_pProg->getFrameInProgress() >= _time_of_next_state) {
                    //発動終了
                    processInvokeFinish(_level, _new_level); //コールバック
                    effect(_new_level);
                }
                break;
            }
            /////////////////////////////////////// 持続
            case MAGIC_STATE_EFFECT_BEGEIN: { //持続開始
                if (_level == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING);
                    break;
                } else if (_last_level < _level) {
                    //レベルアップだった場合
                    //飛び越された間のレベルは停止して効果持続終了残り時間を満タンを設定
                    for (int lv = _last_level+1; lv <= _level-1; lv++) {
                        _lvinfo[lv]._is_working = false; //停止し
                        _lvinfo[lv]._remaining_time_of_effect = _lvinfo[lv]._time_of_effect; //持続時間を満タン
                    }
                    _pMP->dec(_interest_cost[_level-_last_level]); //MP消費
                } else if (_last_level > _level) {
                    //レベルダウンだった場合
                    //飛び越された間のレベルは停止して効果持続終了残り時間をリセットを設定
                    for (int lv = _level+1 ; lv <= _last_level-1; lv++) {
                        _lvinfo[lv]._is_working = false; //停止し
                        _lvinfo[lv]._remaining_time_of_effect = 0; //果持続終了残り時間を0
                    }

                    if (_keep_cost_base == 0) { //維持コストがかからない魔法の場合は
                        if (_lvinfo[_last_level]._time_of_effect > 0) {
                            //基本コストの60%還元。但し残効果持続の割合を乗ずる。早くレベルダウンしたほうがお得にするため。
                            _pMP->inc( _cost_base*(_last_level-_level)*0.6*
                                       (1.0*_lvinfo[_last_level]._remaining_time_of_effect / _lvinfo[_last_level]._time_of_effect) );
                        }
                    }
                } else {
                    _TRACE_("_last_level＝＝_level①");
                }


                if (_level == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                    break;
                }

                //今回の新たなレベルを設定
                _lvinfo[_level]._is_working = true;
                if (_last_level < _level) {
                    //レベルアップだった場合
                    _lvinfo[_level]._remaining_time_of_effect = _lvinfo[_level]._time_of_effect; //今回持続時間を満タン
                } else if (_last_level > _level) {
                    //レベルダウンだった場合、今回持続時間は前回の続き
                } else {
                    _TRACE_("_last_level＝＝_level②");
                }
                //効果持続開始
                processEffectBegin(_last_level, _level); //コールバック

                _pProg->set(MAGIC_STATE_EFFECTING);
            }   //↓break 無しの落下(falldown).
                //↓
            case MAGIC_STATE_EFFECTING: { //持続中
                processEffectingBehavior(_last_level, _level); //コールバック

                _lvinfo[_level]._remaining_time_of_effect --; //効果持続残り時間減少

                //維持コストがかかる場合の処理
                if (_keep_cost_base != 0) {
                    _pMP->inc(-1*_lvinfo[_level]._keep_cost); //維持コスト減少
                    //MP枯渇？
                    if (_pMP->_val <= 0) {
                        //MP枯渇による持続終了時
                        _pMP->_val = 0;
                        for (int lv = 1; lv <= _level; lv++) { //全レベルリセットを設定
                             _lvinfo[lv]._is_working = false;           //停止し
                             _lvinfo[lv]._remaining_time_of_effect = 0; //効果持続終了残り時間を0
                        }
                        _new_level = 0;
                        _last_level = _level;
                        _level = _new_level;
                        processEffectFinish(_last_level); //コールバック MP枯渇による魔法終了
                        _pProg->change(MAGIC_STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                        break;
                    }
                }

                //持続時間満期処理
                if (_lvinfo[_level]._remaining_time_of_effect == 0) {
                    effect(_level-1);//レベルダウン(-1)を行う。
                    if (_level == 0) { //現レベルが１で、レベルダウン(-1)によりnothingになった場合
                        processEffectFinish(_last_level); //コールバック
                        _pProg->change(MAGIC_STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                        break;
                    }
                }
                break;
            }
            default :
                break;
        }
    }

}
Magic::~Magic() {
}
