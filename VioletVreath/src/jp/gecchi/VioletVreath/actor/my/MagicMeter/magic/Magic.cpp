#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Magic::Magic(const char*  prm_name, AmountGraph* prm_pMP,
             int          prm_max_level,
             magic_point  prm_cost_base            , double prm_r_cost             ,
             magic_time   prm_time_of_casting_base , double prm_r_time_of_casting  ,
             magic_time   prm_time_of_invoking_base, double prm_r_time_of_invoking ,
             magic_time   prm_time_of_effect_base  , double prm_r_each_lv_time_of_effecting,
             magic_point  prm_keep_cost_base       , double prm_r_each_lv_keep_cost) : GgafMainActor(prm_name, NULL) {
//    GgafDxGeometricActor* prm_pCaster,
//     GgafDxGeometricActor* prm_pReceiver) : GgafDxBoardSetActor(prm_name, "magic") {
    pMP_ = prm_pMP;
    new_level_  = 0;
    last_level_ = 0;
    level_      = 0;
    prev_frame_level_ = level_;
    max_level_               = prm_max_level;
    cost_base_               = prm_cost_base;
    time_of_casting_base_    = prm_time_of_casting_base;
    time_of_invoking_base_   = prm_time_of_invoking_base;
    time_of_effect_base_     = prm_time_of_effect_base;
    keep_cost_base_          = prm_keep_cost_base;

    r_cost_              = prm_r_cost;
    r_time_of_casting_   = prm_r_time_of_casting;
    r_time_of_invoking_  = prm_r_time_of_invoking;

    r_each_lv_time_of_effecting_ = prm_r_each_lv_time_of_effecting;
    r_keep_cost_                 = prm_r_each_lv_keep_cost;


    //飛びレベル差別情報を設定
    interest_cost_[0] = 0;
    interest_time_of_casting_[0] = 0;
    interest_time_of_invoking_[0] = 0;
    for (int i = 1; i <= max_level_; i++) {
        interest_cost_[i]             = (cost_base_ * i) * r_cost_;
        interest_time_of_casting_[i]  = (time_of_casting_base_ * i) * r_time_of_casting_;
        interest_time_of_invoking_[i] = (time_of_invoking_base_ * i) * r_time_of_invoking_;
    }

    //各レベル別持続時間及び、維持コストを予め設定
    lvinfo_[0].remainingtime_of_effect_ = 0;
    lvinfo_[0].time_of_effect_ = 0;
    lvinfo_[0].keep_cost_ = 0;
    lvinfo_[1].remainingtime_of_effect_ = 0;
    lvinfo_[1].time_of_effect_ = time_of_effect_base_;
    lvinfo_[1].keep_cost_ = keep_cost_base_;

    for (int i = 2; i <= max_level_; i++) {
        lvinfo_[i].remainingtime_of_effect_ = 0;
        lvinfo_[i].time_of_effect_ = lvinfo_[i-1].time_of_effect_ * r_each_lv_time_of_effecting_;
        lvinfo_[i].keep_cost_      = lvinfo_[i-1].keep_cost_      * r_keep_cost_;
    }
    time_of_next_state_ = 0;
    is_working_ = false;
    useProgress(STATE_ABANDONING);
}

void Magic::init() {

}

void Magic::onReset() {
    new_level_  = 0;
    last_level_ = 0;
    level_      = 0;
    //各レベル別持続時間及び、維持コストを予め設定
    lvinfo_[0].remainingtime_of_effect_ = 0;
    lvinfo_[1].remainingtime_of_effect_ = 0;
    for (int i = 2; i <= max_level_; i++) {
        lvinfo_[i].remainingtime_of_effect_ = 0;
    }
    time_of_next_state_ = 0;
    is_working_ = false;
    _pProg->set(STATE_NOTHING);
}

void Magic::save(std::stringstream& sts) {
    sts << max_level_  << " " <<
           level_      << " " <<
           new_level_  << " " <<
           last_level_ << " ";
    for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
        sts <<  lvinfo_[lv].remainingtime_of_effect_ << " " <<
                lvinfo_[lv].time_of_effect_           << " " <<
                lvinfo_[lv].keep_cost_                << " " <<
                lvinfo_[lv].pno_                      << " ";
    }
}

void Magic::load(std::stringstream& sts) {
    sts >> max_level_
        >> level_
        >> new_level_
        >> last_level_;

    for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
        sts >> lvinfo_[lv].remainingtime_of_effect_
            >> lvinfo_[lv].time_of_effect_
            >> lvinfo_[lv].keep_cost_
            >> lvinfo_[lv].pno_;
    }
    effect(level_); //MAGIC_EFFECT_NOTHINGだからOKと思う
}

int Magic::chkCastAble(int prm_new_level) {
    if (_pProg->get() == STATE_INVOKING || _pProg->get() == STATE_INVOKE_BEGIN) {
        return MAGIC_CAST_NG_INVOKING_NOW; //発動中のため実行不可
    } else if (_pProg->get() == STATE_CASTING || _pProg->get() == STATE_CAST_BEGIN) {
        //他のレベルを詠唱中に詠唱再実行
        if (level_ > prm_new_level) {
            return MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN; //再詠唱レベルダウンOK
        } else if (level_ < prm_new_level) {
            if (interest_cost_[prm_new_level-level_] < pMP_->get()) {
                return MAGIC_CAST_OK_CANCEL_AND_LEVELUP; //再詠唱レベルアップOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MPが足りないため、再詠唱レベルアップ不可
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_CANCEL; //詠唱キャンセル
        }
    } else {
        //待機状態か効果持続中に詠唱実行
        if (level_ > prm_new_level) {
            return MAGIC_CAST_OK_LEVELDOWN; //詠唱レベルダウンOK
        } else if (level_ < prm_new_level) {
            if (interest_cost_[prm_new_level-level_] < pMP_->get()) {
                return MAGIC_CAST_OK_LEVELUP; //詠唱レベルアップOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MPが足りないため、再詠唱レベルアップ不可
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_NOTHING; //何もしない。
        }
    }
}
int Magic::cast(int prm_new_level) {
    int r = chkCastAble(prm_new_level);
    switch (r) {
        case MAGIC_CAST_NG_INVOKING_NOW: {
            //効果発動中のため詠唱不可だったので、何もしない。
            break;
        }
        case MAGIC_CAST_NG_MP_IS_SHORT: {
            //MPが少なく詠唱不可だったので、何もしない。
            break;
        }
        case MAGIC_CAST_NOTHING: {
            //現在のレベルと同じレベルを詠唱しようとしている、何もしない。
            break;
        }
        case MAGIC_CAST_CANCEL: {
            //他のレベルを詠唱中に再詠唱を行おうとしている
            //再詠唱のレベルが、現在の効果持続レベルと同じレベルを指定したため、
            //詠唱中止(キャンセル)扱いになる。
            is_working_ = false;
            new_level_ = prm_new_level;
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_CAST_OK_LEVELUP: {
            //現在の効果持続レベルより高いレベルを詠唱しようとしている。
            is_working_ = true;
            new_level_ = prm_new_level;
            _pProg->change(STATE_CAST_BEGIN);
            break;
        }
        case MAGIC_CAST_OK_LEVELDOWN: {
            //現在の効果持続レベルより低いレベルを詠唱しようとしている。
            is_working_ = true;
            effect(prm_new_level);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
            //他のレベルを詠唱中に再詠唱を行おうとしている
            //再詠唱のレベルが、現在の効果持続レベルより高い。
            is_working_ = true;
            new_level_ = prm_new_level;
            _pProg->change(STATE_CAST_BEGIN);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
            //他のレベルを詠唱中に再詠唱を行おうとしている
            //再詠唱のレベルが、現在の効果持続レベルより低い。
            is_working_ = true;
            effect(prm_new_level);
            break;
        }
    }
    return r;
}

int Magic::chkInvokeAble(int prm_new_level) {
    if (_pProg->get() == STATE_INVOKING || _pProg->get() == STATE_INVOKE_BEGIN) {
        //発動中のため実行不可
        return MAGIC_INVOKE_NG_INVOKING_NOW;
    } else {
        if (level_ > prm_new_level) {
            return MAGIC_INVOKE_OK_LEVELDOWN;
        } else if (level_ < prm_new_level) {
            if (interest_cost_[prm_new_level-level_] < pMP_->get()) {
                return MAGIC_INVOKE_OK_LEVELUP;
            } else {
                return MAGIC_INVOKE_NG_MP_IS_SHORT;
            }
        } else { //level_==prm_new_level
            return MAGIC_INVOKE_NOTHING;
        }
    }
}

int Magic::chkEffectAble(int prm_level) {
    if (level_ > prm_level) {
        return MAGIC_EFFECT_OK_LEVELDOWN;
    } else if (level_ < prm_level) {
        if (interest_cost_[prm_level-level_] < pMP_->get()) {
            return MAGIC_EFFECT_OK_LEVELUP;
        } else {
            return MAGIC_EFFECT_NG_MP_IS_SHORT;
        }
    } else { //level_==prm_new_level
        return MAGIC_EFFECT_NOTHING;
    }
}


int Magic::invoke(int prm_new_level) {
    int r = chkInvokeAble(prm_new_level);
    switch (r) {
        case MAGIC_INVOKE_NG_INVOKING_NOW: {
            //あり得ない
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" が MAGIC_INVOKE_NG_INVOKING_NOW は、このタイミングであり得ないはずです。");
            break;
        }
        case MAGIC_INVOKE_NG_MP_IS_SHORT: {
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELUP: {
            new_level_ = prm_new_level;
            _pProg->change(STATE_INVOKE_BEGIN);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELDOWN: {
            is_working_ = true;
            effect(prm_new_level);
            break;
        }
        case MAGIC_INVOKE_NOTHING: {
            //あり得ない
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" が MAGIC_INVOKE_NOTHING は、このタイミングであり得ないはずです。");
            break;
        }
    }
    return r;
}
int Magic::effect(int prm_level) {
    int r = chkEffectAble(prm_level);

    switch (r) {
        case MAGIC_EFFECT_NG_MP_IS_SHORT: {
            throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" が MAGIC_EFFECT_NG_MP_IS_SHORT は、このタイミングであり得ないはずです。");
            break;
        }
        case MAGIC_EFFECT_NOTHING: {
            throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" が MAGIC_EFFECT_NOTHING は、このタイミングであり得ないはずです。");
            break;
        }
        case MAGIC_EFFECT_OK_LEVELUP: {
            is_working_ = true;
            //レベル更新
            last_level_ = level_;
            level_ = prm_level;
            _pProg->change(STATE_EFFECT_BEGIN);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            is_working_ = true;
            //レベル更新
            last_level_ = level_;
            level_ = prm_level;
            _pProg->change(STATE_EFFECT_BEGIN);
            break;
        }
    }
    return r;
}

void Magic::cancel() {
    new_level_ = level_;
    is_working_ = false;
    _pProg->change(STATE_NOTHING);
}

void Magic::processBehavior() {
    prev_frame_level_ = level_;
    if (is_working_) {

        switch (_pProg->get()) {
            /////////////////////////////////////// 待機
            case STATE_NOTHING: {
                break;
            }

            /////////////////////////////////////// 詠唱開始
            case STATE_CAST_BEGIN: {
                //詠唱終了時間を計算
                time_of_next_state_ = interest_time_of_casting_[new_level_- level_];
                processCastBegin(level_, new_level_);  //コールバック
                _pProg->set(STATE_CASTING);
                //↓ fall down ↓
            }
            /////////////////////////////////////// 詠唱中
            case STATE_CASTING: {
                processCastingBehavior(level_, new_level_); //コールバック

                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //詠唱終了
                    int now_lv = level_;
                    int new_lv = new_level_;
                    int r = invoke(new_level_);
                    processCastFinish(now_lv, new_lv, r);  //コールバック
                }
                break;
            }
            /////////////////////////////////////// 発動開始
            case STATE_INVOKE_BEGIN : {
                //発動終了時間設定
                time_of_next_state_ = interest_time_of_invoking_[new_level_- level_];
                processInvokeBegin(level_, new_level_);     //コールバック

                _pProg->set(STATE_INVOKING);
                //↓ fall down ↓
            }

            /////////////////////////////////////// 発動中
            case STATE_INVOKING: {
                processInvokingBehavior(level_, new_level_);  //コールバック
                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //発動終了
                    int now_lv = level_;
                    int new_lv = new_level_;
                    int r = effect(new_level_);
                    processInvokeFinish(now_lv, new_lv, r); //コールバック
                }
                break;
            }
            /////////////////////////////////////// 持続開始
            case STATE_EFFECT_BEGIN: {
                //MP消費計算
                if (last_level_ < level_) {
                    //レベルアップだった場合
                    //飛び越された間のレベルは停止して効果持続終了残り時間を満タンを設定
                    for (int lv = last_level_+1; lv <= level_-1; lv++) {
                        lvinfo_[lv].remainingtime_of_effect_ = lvinfo_[lv].time_of_effect_; //持続時間を満タン
                    }
                    pMP_->dec(interest_cost_[level_-last_level_]); //MP消費
                } else if (last_level_ > level_) {
                    //レベルダウンだった場合

                    if (keep_cost_base_ == 0) { //維持コストがかからない魔法の場合は
                        if (lvinfo_[last_level_].time_of_effect_ > 0) {
                            //MP還元
                            pMP_->inc(calcReduceMp(last_level_, level_));
                        }
                    }

                    //飛び越された間のレベルは停止して効果持続終了残り時間をリセットを設定
                    for (int lv = level_+1 ; lv <= last_level_-1; lv++) {
                        lvinfo_[lv].remainingtime_of_effect_ = 0; //果持続終了残り時間を0
                    }
                } else {
                }


                if (level_ == 0) {
                    _pProg->change(STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                    break;
                }

                //今回の新たなレベルを設定
                if (last_level_ < level_) {
                    //レベルアップだった場合
                    lvinfo_[level_].remainingtime_of_effect_ = lvinfo_[level_].time_of_effect_; //今回持続時間を満タン
                } else if (last_level_ > level_) {
                    //レベルダウンだった場合、今回持続時間は前回の続き
                } else {
                    _TRACE_("last_level_＝＝level_�A");
                }
                //効果持続開始
                processEffectBegin(last_level_, level_); //コールバック

                _pProg->set(STATE_EFFECTING);
                break;
            }

            default :
                break;
        }
        /////////////////////////////////////// 持続中
        //case STATE_EFFECTING:
        if (_pProg->get() != STATE_NOTHING) {

            if (time_of_effect_base_ == 0) {
                //即効性魔法
                if (level_ > 0) {
                    for (int lv = 1; lv <= level_; lv++) { //全レベルリセットを設定
                         lvinfo_[lv].remainingtime_of_effect_ = 0; //効果持続終了残り時間を0
                    }
                    new_level_ = 0;
                    last_level_ = level_;
                    level_ = new_level_;
                    processEffectFinish(last_level_); //コールバック MP枯渇による魔法終了
                    _pProg->change(STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                }
            } else {
                //効果持続魔法
                if (level_ > 0) {
                    processEffectingBehavior(last_level_, level_); //コールバック
                    lvinfo_[level_].remainingtime_of_effect_ --; //効果持続残り時間減少


                    if (keep_cost_base_ != 0) {
                        //維持コストがかかる場合の処理
                        pMP_->inc(-1*lvinfo_[level_].keep_cost_); //維持コスト減少
                        //MP枯渇？
                        if (pMP_->get() <= 0) {
                            //MP枯渇による持続終了時
                            pMP_->set(0);
                            for (int lv = 1; lv <= level_; lv++) { //全レベルリセットを設定
                                 lvinfo_[lv].remainingtime_of_effect_ = 0; //効果持続終了残り時間を0
                            }
                            new_level_ = 0;
                            last_level_ = level_;
                            level_ = new_level_;
                            processEffectFinish(last_level_); //コールバック MP枯渇による魔法終了
                            _pProg->change(STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                        }
                    }
                }

                if (level_ > 0) {
                    //持続時間満期処理
                    if (lvinfo_[level_].remainingtime_of_effect_ == 0) {
                        effect(level_-1); //レベルダウン(-1)を行う。
                        if (level_ == 0) { //現レベルが１で、レベルダウン(-1)によりnothingになった場合
                            processEffectFinish(last_level_); //コールバック
                            _pProg->change(STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                        }
                    }
                }
            }

        }
    }

}

magic_point Magic::calcReduceMp(int prm_now_level, int prm_target_down_level) {
    //コスト還元。
    //この計算式では、レベル0 > MAXレベルアップ ＞ レベル0へレベルダウン を素早く行うと、
    //ロス無しという計算。
    //各レベルの残りの効果持続時間の割合も考慮する。
    magic_point mp = 0;
    magic_point rcost_pre_lv = interest_cost_[max_level_]/max_level_;
    for (int lv = prm_now_level; lv > prm_target_down_level; lv--) {
        mp += rcost_pre_lv*(1.0*lvinfo_[lv].remainingtime_of_effect_ / lvinfo_[lv].time_of_effect_);
    }
    return mp;
}

magic_time Magic::calcTotalEffecTime(int prm_now_level, int prm_target_up_level) {
    magic_time sum = 0;
    for (int i = prm_now_level+1; i <= prm_target_up_level; i++) {
        sum += lvinfo_[i].time_of_effect_;
    }
    return sum;
}

Magic::~Magic() {
}
