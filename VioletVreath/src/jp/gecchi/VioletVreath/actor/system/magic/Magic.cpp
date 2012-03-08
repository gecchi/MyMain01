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
             magic_time   prm_time_of_effect_base  , float prm_fRatetime_of_effecting,
             magic_point  prm_keep_cost_base       , float prm_fRatekeep_cost_
                ) : GgafMainActor(prm_name, NULL) {
//    GgafDxGeometricActor* prm_pCaster,
//     GgafDxGeometricActor* prm_pReceiver) : GgafDxBoardSetActor(prm_name, "magic") {
    pMP_ = prm_pMP;
    new_level_ = 0;
    last_level_ = 0;
    level_ = 0;
    max_level_ = prm_max_level;
    cost_base_             = prm_cost_base;
    time_of_casting_base_  = prm_time_of_casting_base;
    time_of_invoking_base_ = prm_time_of_invoking_base;
    time_of_effect_base   = prm_time_of_effect_base;
    keep_cost_base_        = prm_keep_cost_base;

    fRate_cost_               = prm_fRate_cost;
    fRate_time_of_casting_    = prm_fRate_time_of_casting;
    fRate_time_of_invoking_   = prm_fRate_time_of_invoking;
    fRatetime_of_effecting_  = prm_fRatetime_of_effecting;
    fRatekeep_cost_          = prm_fRatekeep_cost_;

    //飛びレベル差別情報を設定
    interest_cost_[0] = 0;
    interest_time_of_casting_[0] = 0;
    interest_time_of_invoking_[0] = 0;
    for (int i = 1; i <= max_level_; i++) {
        interest_cost_[i]             = (cost_base_ * i) * fRate_cost_;
        interest_time_of_casting_[i]  = (time_of_casting_base_ * i) *  fRate_time_of_casting_;
        interest_time_of_invoking_[i] = (time_of_invoking_base_ * i) *  fRate_time_of_invoking_;
    }

    //各レベル別持続時間及び、維持コストを予め設定
    lvinfo_[0].is_working_ = false;
    lvinfo_[0].remainingtime_of_effect_ = 0;
    lvinfo_[0].time_of_effect_ = 0;
    lvinfo_[0].keep_cost_ = 0;
    for (int i = 1; i <= max_level_; i++) {
        lvinfo_[i].is_working_ = false;
        lvinfo_[i].remainingtime_of_effect_ = 0;
        lvinfo_[i].time_of_effect_ = time_of_effect_base + ((i-1) * time_of_effect_base * fRatetime_of_effecting_);
        lvinfo_[i].keep_cost_      = keep_cost_base_      + ((i-1) * keep_cost_base_ * fRatekeep_cost_);
    }

    time_of_next_state_ = 0;

    is_working_ = false;
    rr_ = 0.0f;
    velo_rr_ = 0.0f;

    useProgress(MAGIC_STATE_ABANDONING);
    _pProg->set(MAGIC_STATE_NOTHING);
}

void Magic::save(stringstream& sts) {
    sts << max_level_  << " " <<
           level_      << " " <<
           new_level_  << " " <<
           last_level_ << " ";
    for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
        sts <<  lvinfo_[lv].is_working_               << " " <<
                lvinfo_[lv].remainingtime_of_effect_ << " " <<
                lvinfo_[lv].time_of_effect_           << " " <<
                lvinfo_[lv].keep_cost_                << " " <<
                lvinfo_[lv].pno_                      << " ";
    }
}

void Magic::load(stringstream& sts) {
    sts >> max_level_
        >> level_
        >> new_level_
        >> last_level_;

    for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
        sts >> lvinfo_[lv].is_working_
            >> lvinfo_[lv].remainingtime_of_effect_
            >> lvinfo_[lv].time_of_effect_
            >> lvinfo_[lv].keep_cost_
            >> lvinfo_[lv].pno_;
    }
    effect(level_); //MAGIC_EFFECT_NOTHINGだからOKと思う
}

void Magic::rollOpen() {
    velo_rr_ = 0.1;
}
void Magic::rollClose() {
    velo_rr_ = -0.01;
}

int Magic::chkCastAble(int prm_new_level) {
    if (_pProg->get() == MAGIC_STATE_INVOKING) {
        return MAGIC_CAST_NG_INVOKING_NOW; //発動中のため実行不可
    } else if (_pProg->get() == MAGIC_STATE_CASTING) {
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
            break;
        }
        case MAGIC_CAST_NG_MP_IS_SHORT: {
            break;
        }
        case MAGIC_CAST_NOTHING: {
            break;
        }
        case MAGIC_CAST_CANCEL: {
            is_working_ = false;
            new_level_ = prm_new_level;
            _pProg->change(MAGIC_STATE_NOTHING);
            break;
        }
        case MAGIC_CAST_OK_LEVELUP: {
            is_working_ = true;
            new_level_ = prm_new_level;
            _pProg->change(MAGIC_STATE_CASTING);
            break;
        }
        case MAGIC_CAST_OK_LEVELDOWN: {
            is_working_ = true;
            effect(prm_new_level);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
            is_working_ = true;
            new_level_ = prm_new_level;
            _pProg->change(MAGIC_STATE_CASTING);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
            is_working_ = true;
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
            break;
        }
        case MAGIC_INVOKE_NG_MP_IS_SHORT: {
            break;
        }
        case MAGIC_INVOKE_OK_LEVELUP: {
            new_level_ = prm_new_level;
            _pProg->change(MAGIC_STATE_INVOKING);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELDOWN: {
            is_working_ = true;
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
            lvinfo_[level_].is_working_ = false;
            //レベル更新
            last_level_ = level_;
            level_ = prm_level;
            _pProg->change(MAGIC_STATE_EFFECT_BEGEIN);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            //現在魔法レベルは停止して
            lvinfo_[level_].is_working_ = false;
            //レベル更新
            last_level_ = level_;
            level_ = prm_level;
            _pProg->change(MAGIC_STATE_EFFECT_BEGEIN);
            break;
        }
    }
    return r;
}

void Magic::cancel() {
    new_level_ = level_;
    is_working_ = false;
    _pProg->change(MAGIC_STATE_NOTHING);
}

void Magic::processBehavior() {
    rr_ += velo_rr_;
    if (rr_ < 0.0f) {
        rr_ = 0.0f;
        velo_rr_ = 0.0f;
    }
    if (rr_ > 1.0f) {
        rr_ = 1.0f;
        velo_rr_ = 0.0f;
    }
    if (is_working_) {

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
                    time_of_next_state_ = interest_time_of_casting_[new_level_- level_];
                    processCastBegin(level_, new_level_);  //コールバック
                }

                //詠唱中
                processCastingBehavior(level_, new_level_); //コールバック

                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //詠唱終了
                    processCastFinish(level_, new_level_);  //コールバック
                    invoke(new_level_);
                }
                break;
            }
            /////////////////////////////////////// 発動
            case MAGIC_STATE_INVOKING: {
                if (_pProg->isJustChanged()) {
                    //発動開始、
                    //発動終了時間設定
                    time_of_next_state_ = interest_time_of_invoking_[new_level_- level_];
                    processInvokeBegin(level_, new_level_);     //コールバック
                }

                //発動中
                processInvokeingBehavior(level_, new_level_);  //コールバック

                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //発動終了
                    processInvokeFinish(level_, new_level_); //コールバック
                    effect(new_level_);
                }
                break;
            }
            /////////////////////////////////////// 持続
            case MAGIC_STATE_EFFECT_BEGEIN: { //持続開始
                if (level_ == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING);
                    break;
                } else if (last_level_ < level_) {
                    //レベルアップだった場合
                    //飛び越された間のレベルは停止して効果持続終了残り時間を満タンを設定
                    for (int lv = last_level_+1; lv <= level_-1; lv++) {
                        lvinfo_[lv].is_working_ = false; //停止し
                        lvinfo_[lv].remainingtime_of_effect_ = lvinfo_[lv].time_of_effect_; //持続時間を満タン
                    }
                    pMP_->dec(interest_cost_[level_-last_level_]); //MP消費
                } else if (last_level_ > level_) {
                    //レベルダウンだった場合
                    //飛び越された間のレベルは停止して効果持続終了残り時間をリセットを設定
                    for (int lv = level_+1 ; lv <= last_level_-1; lv++) {
                        lvinfo_[lv].is_working_ = false; //停止し
                        lvinfo_[lv].remainingtime_of_effect_ = 0; //果持続終了残り時間を0
                    }

                    if (keep_cost_base_ == 0) { //維持コストがかからない魔法の場合は
                        if (lvinfo_[last_level_].time_of_effect_ > 0) {
                            //基本コストの60%還元。但し残効果持続の割合を乗ずる。早くレベルダウンしたほうがお得にするため。
                            pMP_->inc( cost_base_*(last_level_-level_)*0.6*
                                       (1.0*lvinfo_[last_level_].remainingtime_of_effect_ / lvinfo_[last_level_].time_of_effect_) );
                        }
                    }
                } else {
                    _TRACE_("last_level_＝＝level_①");
                }


                if (level_ == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                    break;
                }

                //今回の新たなレベルを設定
                lvinfo_[level_].is_working_ = true;
                if (last_level_ < level_) {
                    //レベルアップだった場合
                    lvinfo_[level_].remainingtime_of_effect_ = lvinfo_[level_].time_of_effect_; //今回持続時間を満タン
                } else if (last_level_ > level_) {
                    //レベルダウンだった場合、今回持続時間は前回の続き
                } else {
                    _TRACE_("last_level_＝＝level_②");
                }
                //効果持続開始
                processEffectBegin(last_level_, level_); //コールバック

                _pProg->set(MAGIC_STATE_EFFECTING);
            }   //↓break 無しの落下(falldown).
                //↓
            case MAGIC_STATE_EFFECTING: { //持続中
                processEffectingBehavior(last_level_, level_); //コールバック

                lvinfo_[level_].remainingtime_of_effect_ --; //効果持続残り時間減少

                //維持コストがかかる場合の処理
                if (keep_cost_base_ != 0) {
                    pMP_->inc(-1*lvinfo_[level_].keep_cost_); //維持コスト減少
                    //MP枯渇？
                    if (pMP_->_val <= 0) {
                        //MP枯渇による持続終了時
                        pMP_->_val = 0;
                        for (int lv = 1; lv <= level_; lv++) { //全レベルリセットを設定
                             lvinfo_[lv].is_working_ = false;           //停止し
                             lvinfo_[lv].remainingtime_of_effect_ = 0; //効果持続終了残り時間を0
                        }
                        new_level_ = 0;
                        last_level_ = level_;
                        level_ = new_level_;
                        processEffectFinish(last_level_); //コールバック MP枯渇による魔法終了
                        _pProg->change(MAGIC_STATE_NOTHING); //レベルダウン(0レベル指定)による魔法終了
                        break;
                    }
                }

                //持続時間満期処理
                if (lvinfo_[level_].remainingtime_of_effect_ == 0) {
                    effect(level_-1);//レベルダウン(-1)を行う。
                    if (level_ == 0) { //現レベルが１で、レベルダウン(-1)によりnothingになった場合
                        processEffectFinish(last_level_); //コールバック
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
