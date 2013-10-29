#include "stdafx.h"
#include "Magic.h"

#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Magic::Magic(const char*  prm_name, int* prm_pMP,
             int prm_max_level,
             magic_point prm_cost_base            , double prm_r_every_lv_cost             , double prm_r_cost_lv_diff_base,
             magic_time  prm_time_of_casting_base , double prm_r_every_lv_time_of_casting  , double prm_r_time_of_casting_lv_diff_base,
             magic_time  prm_time_of_invoking_base, double prm_r_every_lv_time_of_invoking , double prm_r_time_of_invoking_lv_diff_base,
             magic_time  prm_time_of_effect_base  , double prm_r_every_lv_time_of_effecting,
             magic_point prm_keep_cost_base       , double prm_r_each_lv_keep_cost) : GgafMainActor(prm_name, nullptr),
pMP_(prm_pMP),
cost_base_(prm_cost_base),
time_of_casting_base_(prm_time_of_casting_base),
time_of_invoking_base_(prm_time_of_invoking_base),
time_of_effect_base_(prm_time_of_effect_base),
keep_cost_base_(prm_keep_cost_base),
r_every_lv_cost_(prm_r_every_lv_cost),
r_every_lv_time_of_casting_(prm_r_every_lv_time_of_casting),
r_every_lv_time_of_invoking_(prm_r_every_lv_time_of_invoking),
r_every_lv_time_of_effecting_(prm_r_every_lv_time_of_effecting),
r_each_lv_keep_cost_(prm_r_each_lv_keep_cost),
r_cost_lv_diff_base_(prm_r_cost_lv_diff_base),
r_time_of_casting_lv_diff_base_(prm_r_time_of_casting_lv_diff_base),
r_time_of_invoking_lv_diff_base_(prm_r_time_of_invoking_lv_diff_base) {

    max_level_  = prm_max_level;
    new_level_  = 0;
    last_level_ = 0;
    level_      = 0;

    level_nextframe_ = 0;
    new_level_nextframe_ = 0;
    last_level_nextframe_ = 0;

    prev_frame_level_ = level_;

    //各レベル別持続時間及び、コスト、詠唱時間、発動時間、効果持続時間、維持コストを予め設定
    lvinfo_[0].remainingtime_of_effect_ = MAX_MAGIC_TIME;
    lvinfo_[0].cost_             = 0;
    lvinfo_[0].time_of_casting_  = 0;
    lvinfo_[0].time_of_invoking_ = 0;
    lvinfo_[0].time_of_effect_   = 0;
    lvinfo_[0].keep_cost_        = 0;
    lvinfo_[1].remainingtime_of_effect_ = 0;
    lvinfo_[1].cost_             = cost_base_;
    lvinfo_[1].time_of_casting_  = time_of_casting_base_;
    lvinfo_[1].time_of_invoking_ = time_of_invoking_base_;
    lvinfo_[1].time_of_effect_   = time_of_effect_base_;
    lvinfo_[1].keep_cost_        = keep_cost_base_;
    for (int i = 2; i <= MMETER_MAX_LEVEL; i++) {
        lvinfo_[i].remainingtime_of_effect_ = 0;
        lvinfo_[i].cost_             = lvinfo_[i-1].cost_             * r_every_lv_cost_;
        lvinfo_[i].time_of_casting_  = lvinfo_[i-1].time_of_casting_  * r_every_lv_time_of_casting_;
        lvinfo_[i].time_of_invoking_ = lvinfo_[i-1].time_of_invoking_ * r_every_lv_time_of_invoking_;
        lvinfo_[i].time_of_effect_   = lvinfo_[i-1].time_of_effect_   * r_every_lv_time_of_effecting_;
        lvinfo_[i].keep_cost_        = lvinfo_[i-1].keep_cost_        * r_each_lv_keep_cost_;
    }

    //レベル差情報
    lvdiff_[0].r_cost_lv_diff_             = 0.0; //レベル差０にコストは無い。
    lvdiff_[0].r_time_of_casting_lv_diff_  = 0.0;
    lvdiff_[0].r_time_of_invoking_lv_diff_ = 0.0;
    lvdiff_[1].r_cost_lv_diff_             = 1.0;  //レベル差１にボーナス特典は無い。
    lvdiff_[1].r_time_of_casting_lv_diff_  = 1.0;
    lvdiff_[1].r_time_of_invoking_lv_diff_ = 1.0;
    lvdiff_[2].r_cost_lv_diff_             = r_cost_lv_diff_base_; //レベル差２で初めてお得になる。
    lvdiff_[2].r_time_of_casting_lv_diff_  = r_time_of_casting_lv_diff_base_;
    lvdiff_[2].r_time_of_invoking_lv_diff_ = r_time_of_invoking_lv_diff_base_;
    for (int i = 2; i <= MMETER_MAX_LEVEL; i++) { //レベル差が増えるとよりお得。
        lvdiff_[i].r_cost_lv_diff_             = lvdiff_[i-1].r_cost_lv_diff_            * r_cost_lv_diff_base_;
        lvdiff_[i].r_time_of_casting_lv_diff_  = lvdiff_[i-1].r_time_of_casting_lv_diff_ * r_time_of_casting_lv_diff_base_;
        lvdiff_[i].r_time_of_invoking_lv_diff_ = lvdiff_[i-1].r_time_of_invoking_lv_diff_* r_time_of_invoking_lv_diff_base_;
    }

    _TRACE_("Magic::Magic "<<getName()<<" のレベルアップ時の数値");
    //レベルアップ時のコスト、詠唱時間、発動時間を予め計算
    for (int now_lv = 0; now_lv <= MMETER_MAX_LEVEL; now_lv++) {
        for (int target_lv = now_lv; target_lv <= MMETER_MAX_LEVEL; target_lv++) {
            level_up_cost_[now_lv][target_lv] = (target_lv == now_lv ? 0 : level_up_cost_[now_lv][target_lv-1])
                                                 + (lvinfo_[target_lv].cost_ * lvdiff_[target_lv-now_lv].r_cost_lv_diff_);
            level_up_time_of_casting_[now_lv][target_lv] = (target_lv == now_lv ? 0 : level_up_time_of_casting_[now_lv][target_lv-1])
                                                           + (lvinfo_[target_lv].time_of_casting_ * lvdiff_[target_lv-now_lv].r_time_of_casting_lv_diff_);
            level_up_time_of_invoking_[now_lv][target_lv] = (target_lv == now_lv ? 0 : level_up_time_of_invoking_[now_lv][target_lv-1])
                                                            + (lvinfo_[target_lv].time_of_invoking_ * lvdiff_[target_lv-now_lv].r_time_of_invoking_lv_diff_);
        }
    }
#ifdef MY_DEBUG
    for (int now_lv = 0; now_lv <= MMETER_MAX_LEVEL; now_lv++) {
        for (int target_lv = now_lv; target_lv <= MMETER_MAX_LEVEL; target_lv++) {
             _TRACE_("Magic::Magic["<<getName()<<"] level_up_cost_["<<now_lv<<"→"<<target_lv<<"]="<<level_up_cost_[now_lv][target_lv]);
        }
    }
    for (int now_lv = 0; now_lv <= MMETER_MAX_LEVEL; now_lv++) {
        for (int target_lv = now_lv; target_lv <= MMETER_MAX_LEVEL; target_lv++) {
             _TRACE_("Magic::Magic["<<getName()<<"] level_up_time_of_casting_["<<now_lv<<"→"<<target_lv<<"]="<<level_up_time_of_casting_[now_lv][target_lv]);
        }
    }
    for (int now_lv = 0; now_lv <= MMETER_MAX_LEVEL; now_lv++) {
        for (int target_lv = now_lv; target_lv <= MMETER_MAX_LEVEL; target_lv++) {
            _TRACE_("Magic::Magic["<<getName()<<"] level_up_time_of_invoking_["<<now_lv<<"→"<<target_lv<<"]="<<level_up_time_of_invoking_[now_lv][target_lv]);
        }
    }
#endif

    //レベルダウン時は利用率があるので、難しい
    time_of_next_state_ = 0;
    useProgress(_BANPEI_-1);
    temp_hold_status_ = -1;
    temp_hold_new_level_ = 0;
    last_cast_ = MAGIC_CAST_NOTHING;
    last_invoke_ = MAGIC_INVOKE_NOTHING;
    last_effect_ = MAGIC_EFFECT_NOTHING;

}

void Magic::init() {
}

void Magic::onReset() {
    _TRACE_("Magic::onReset() ["<<getName()<<"] ");
    new_level_  = 0;
    last_level_ = 0;
    level_      = 0;
    prev_frame_level_ = level_;

    level_nextframe_ = 0;
    new_level_nextframe_ = 0;
    last_level_nextframe_ = 0;

    last_cast_ = MAGIC_CAST_NOTHING;
    last_invoke_ = MAGIC_INVOKE_NOTHING;
    last_effect_ = MAGIC_EFFECT_NOTHING;

    _pProg->reset(STATE_NOTHING);
    //各レベル別持続時間及び、維持コストを予め設定
    lvinfo_[0].remainingtime_of_effect_ = MAX_MAGIC_TIME;
    lvinfo_[1].remainingtime_of_effect_ = 0;
    for (int i = 2; i <= max_level_; i++) {
        lvinfo_[i].remainingtime_of_effect_ = 0;
        effect(0); //各魔法レベル0を実行
    }
    time_of_next_state_ = 0;
    temp_hold_status_ = -1;
    temp_hold_new_level_ = 0;
}

void Magic::save(std::stringstream& sts) {
    sts << max_level_  << " " <<
           level_      << " " <<
           new_level_  << " " <<
           last_level_ << " ";
    for (int lv = 0; lv < MMETER_MAX_LEVEL+1; lv++) {
        sts <<  lvinfo_[lv].remainingtime_of_effect_ << " " <<
                lvinfo_[lv].time_of_effect_          << " " <<
                lvinfo_[lv].keep_cost_               << " " <<
                lvinfo_[lv].pno_                     << " ";
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
    if (_pProg->get() == STATE_INVOKING) {
        return MAGIC_CAST_NG_INVOKING_NOW; //発動中のため実行不可
    } else if (_pProg->get() == STATE_CASTING) {
        //他のレベルを詠唱中に詠唱再実行
        if (level_ > prm_new_level) {
            return MAGIC_CAST_CANCEL_AND_LEVELDOWN; //詠唱キャンセルレベルダウンOK
        } else if (level_ < prm_new_level) {
            if (level_up_cost_[level_][prm_new_level] <= *pMP_) {
                return MAGIC_CAST_OK_CANCEL_AND_LEVELUP; //詠唱キャンセル再詠唱レベルアップOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MPが足りないため、再詠唱レベルアップ不可
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_CANCEL; //詠唱キャンセル
        }
    } else {
        //待機状態か効果持続中に詠唱実行
        if (level_ > prm_new_level) {
            return MAGIC_CAST_LEVELDOWN; //詠唱レベルダウンOK
        } else if (level_ < prm_new_level) {
            if (level_up_cost_[level_][prm_new_level] <= *pMP_) {
                return MAGIC_CAST_OK_LEVELUP; //詠唱レベルアップOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MPが足りないため、詠唱レベルアップ不可
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_NOTHING; //何もしない。
        }
    }
}

int Magic::cast(int prm_new_level) {
    last_cast_ = MAGIC_CAST_NOTHING;
    last_invoke_ = MAGIC_INVOKE_NOTHING;
    last_effect_ = MAGIC_EFFECT_NOTHING;

    int last_cast = chkCastAble(prm_new_level);
    switch (last_cast) {
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
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_CAST_CANCEL!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_CAST_OK_LEVELUP: {
            //現在の効果持続レベルより高いレベルを詠唱しようとしている。
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_CAST_OK_LEVELUP!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_CASTING);
            break;
        }
        case MAGIC_CAST_LEVELDOWN: {
            //現在の効果持続レベルより低いレベルを詠唱しようとしている。
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_CAST_LEVELDOWN!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_CASTING);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
            //他のレベルを詠唱中に再詠唱を行おうとしている
            //再詠唱のレベルが、現在の効果持続レベルより高い。
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_CAST_OK_CANCEL_AND_LEVELUP!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_RE_CASTING);
            break;
        }
        case MAGIC_CAST_CANCEL_AND_LEVELDOWN: {
            //他のレベルを詠唱中に再詠唱を行おうとしている
            //再詠唱のレベルが、現在の効果持続レベルより低い。
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_CAST_CANCEL_AND_LEVELDOWN!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_RE_CASTING);
            break;
        }
    }
    last_cast_ = last_cast;
    return last_cast_;
}

int Magic::chkInvokeAble(int prm_new_level) {
    if (_pProg->get() == STATE_INVOKING) {
        //発動中のため実行不可
        return MAGIC_INVOKE_NG_INVOKING_NOW;
    } else {
        if (level_ > prm_new_level) {
            return MAGIC_INVOKE_OK_LEVELDOWN;
        } else if (level_ < prm_new_level) {
            if (level_up_cost_[level_][prm_new_level] <= *pMP_) {
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
        if (level_up_cost_[level_][prm_level] <= *pMP_) {
            return MAGIC_EFFECT_OK_LEVELUP;
        } else {
            return MAGIC_EFFECT_NG_MP_IS_SHORT;
        }
    } else {
        //level_==prm_new_level
        return MAGIC_EFFECT_NOTHING;
    }
}

int Magic::invoke(int prm_new_level) {
    last_cast_ = MAGIC_CAST_NOTHING;
    last_invoke_ = MAGIC_INVOKE_NOTHING;
    last_effect_ = MAGIC_EFFECT_NOTHING;

    int last_invoke = chkInvokeAble(prm_new_level);
    switch (last_invoke) {
        case MAGIC_INVOKE_NG_INVOKING_NOW: {
            //あり得ない
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" が MAGIC_INVOKE_NG_INVOKING_NOW は、このタイミングであり得ないはずです。");
            break;
        }
        case MAGIC_INVOKE_NG_MP_IS_SHORT: {
            _TRACE_("Magic::invoke("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_INVOKE_NG_MP_IS_SHORT!");
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELUP: {
            _TRACE_("Magic::invoke("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_INVOKE_OK_LEVELUP!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_INVOKING);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELDOWN: {
            _TRACE_("Magic::invoke("<<prm_new_level<<") ["<<getName()<<"] 判定→MAGIC_INVOKE_OK_LEVELDOWN!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_INVOKING);
            break;
        }
        case MAGIC_INVOKE_NOTHING: {
            //あり得ない
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" が MAGIC_INVOKE_NOTHING は、このタイミングであり得ないはずです。");
            break;
        }
    }
    last_invoke_ = last_invoke;
    return last_invoke_;
}

int Magic::effect(int prm_level) {
    last_cast_ = MAGIC_CAST_NOTHING;
    last_invoke_ = MAGIC_INVOKE_NOTHING;
    last_effect_ = MAGIC_EFFECT_NOTHING;

    int last_effect = chkEffectAble(prm_level);
    switch (last_effect) {
        case MAGIC_EFFECT_NG_MP_IS_SHORT: {
            //throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" が MAGIC_EFFECT_NG_MP_IS_SHORT は、このタイミングであり得ないはずです。");
            //ありうる
            _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] 判定→MAGIC_EFFECT_NG_MP_IS_SHORT、change(STATE_NOTHING)");
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_EFFECT_NOTHING: {
            if (prm_level == 0) {
                //effect(0) の処理。コレは onResetで行われる初期化。
                _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] 判定→MAGIC_EFFECT_NOTHING、なにもしません");
            } else {
                throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" が MAGIC_EFFECT_NOTHING は、このタイミングであり得ないはずです。");
            }
            break;
        }
        case MAGIC_EFFECT_OK_LEVELUP: {
            _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] 判定→MAGIC_EFFECT_OK_LEVELUP、change(STATE_EFFECT_START)");
            //レベル更新
            last_level_nextframe_ = level_;
            level_nextframe_ = prm_level;
            _pProg->change(STATE_EFFECT_START);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] 判定→MAGIC_EFFECT_OK_LEVELDOWN、change(STATE_RE_EFFECT)");
            //レベル更新
            last_level_nextframe_ = level_;
            level_nextframe_ = prm_level;
            _pProg->change(STATE_RE_EFFECT); //現在 STATE_EFFECT_START のため
            break;
        }

    }
    last_effect_ = last_effect;
    return last_effect_;
}
void Magic::nextFrame() {
    GgafMainActor::nextFrame();
    prev_frame_level_ = level_;

    level_ = level_nextframe_;
    new_level_ = new_level_nextframe_;
    last_level_ =  last_level_nextframe_;
}
void Magic::processBehavior() {
    progress prog = _pProg->get();
    switch (prog) {
        /////////////////////////////////////// 待機
        case STATE_NOTHING: {
            if (_pProg->isJustChanged()) {
                if (_pProg->isJustChangedFrom(STATE_CASTING)) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] 詠唱キャンセル終了！");
                    processCastingCancel(level_); //コールバック
                } else if (_pProg->isJustChangedFrom(STATE_INVOKING)) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] 発動キャンセル終了！");
                    processInvokingCancel(level_); //コールバック
                }
            }
            break;
        }

        /////////////////////////////////////// 詠唱中キャンセル再詠唱
        case STATE_RE_CASTING: {
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] 詠唱キャンセル再詠唱！");
            processCastingCancel(level_); //コールバック
            _pProg->change(STATE_CASTING);
            break;
        }
        /////////////////////////////////////// 詠唱中
        case STATE_CASTING: {
            if (_pProg->isJustChanged()) { //詠唱開始
                time_of_next_state_ = level_up_time_of_casting_[level_][new_level_]; //詠唱終了時間
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] STATE_CASTING begin new_level_="<<new_level_<<" level_="<<level_<<" time_of_next_state_="<<time_of_next_state_<<"");
                processCastBegin(level_, new_level_);  //コールバック
            }
            //詠唱中処理
            processCastingBehavior(level_, new_level_); //コールバック
            if (level_ > new_level_ || _pProg->getFrameInProgress() >= time_of_next_state_) {
                //レベルダウン時は即効で、あるいは詠唱終了時
                int r = invoke(new_level_);
                processCastFinish(level_, new_level_, r);  //コールバック
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] 詠唱(STATE_CASTING)ステータス終了！");
            }
            break;
        }

        /////////////////////////////////////// 発動中
        case STATE_INVOKING: {
            if (_pProg->isJustChanged()) { //発動開始
                time_of_next_state_ = level_up_time_of_invoking_[level_][new_level_]; //発動終了時間
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] STATE_INVOKING begin new_level_="<<new_level_<<" level_="<<level_<<" time_of_next_state_="<<time_of_next_state_<<"");
                processInvokeBegin(level_, new_level_);     //コールバック
            }
            //発動中処理
            processInvokingBehavior(level_, new_level_);  //コールバック
            if (level_ > new_level_ || _pProg->getFrameInProgress() >= time_of_next_state_) {
                //レベルダウン時は即効で、あるいは発動終了
                int r = effect(new_level_);
                processInvokeFinish(level_, new_level_, r); //コールバック
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] 発動(STATE_INVOKING)ステータス終了！");
            }
            break;
        }

        /////////////////////////////////////// 持続中、強制レベルダウン再持続開始
        case STATE_RE_EFFECT: {
            _pProg->change(STATE_EFFECT_START);
            break;
        }
        /////////////////////////////////////// 持続開始
        case STATE_EFFECT_START: {
            if (_pProg->isJustChanged()) { //持続開始
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] STATE_EFFECT_START begin");

                processEffectBegin(last_level_, level_); //効果持続開始コールバック

                //MP消費計算
                if (last_level_ < level_) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] レベルアップだった。last_level_="<<last_level_<<" level_="<<level_);
                    //レベルアップだった場合
                    //効果持続時間設定。飛び越された間のレベルも効果持続終了残り時間を満タンを設定
                    for (int lv = last_level_+1; lv <= level_; lv++) {
                        lvinfo_[lv].remainingtime_of_effect_ = lvinfo_[lv].time_of_effect_; //持続時間を満タン
                    }

                    *pMP_ -= level_up_cost_[last_level_][level_]; //MP消費
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] "<<level_up_cost_[last_level_][level_]<<"MP消費("<<((*pMP_)+level_up_cost_[last_level_][level_])<<"→"<<(*pMP_)<<")");
                    if (*pMP_ < 0) {
                        *pMP_ = 0;
                    }
                } else if (last_level_ > level_) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] レベルダウンだった。last_level_="<<last_level_<<" level_="<<level_);
                    //レベルダウンだった場合
                    if (keep_cost_base_ == 0) { //維持コストがかからない魔法の場合は
                        if (lvinfo_[last_level_].time_of_effect_ > 0) {
                            //MP還元
                            magic_point rmp = calcReduceMp(last_level_, level_);
                            *pMP_ += rmp;
                            _TRACE_("Magic::processBehavior() ["<<getName()<<"] "<<rmp<<"MP還元("<<((*pMP_)-rmp)<<"→"<<(*pMP_)<<")");
                            if (*pMP_ > MY_SHIP_MAX_MP) {
                                *pMP_ = MY_SHIP_MAX_MP;
                            }
                        }
                    }

                    //飛び越された間のレベルは停止して効果持続終了残り時間をリセットを設定
                    for (int lv = last_level_; lv >= level_+1; lv--) {
                        lvinfo_[lv].remainingtime_of_effect_ = 0; //効果持続終了残り時間を0
                    }
                    //level_の効果持続時間は前の続き
                } else {
                    //last_level_ == level_
                }

            }

            //持続中処理はここに処理は記述しないこと。
            _pProg->change(STATE_NOTHING);
            break;
        }

        default :
            break;
    }
    ///////////////////////////////////////

    if (temp_hold_status_ != -1) {
        //一時退避ステータスがある場合、もとに戻す
        if (temp_hold_status_ == STATE_CASTING) {
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] 持続時間満期レベルダウン時に詠唱中だったのでここで自動再詠唱！ cast("<<temp_hold_new_level_<<")");
            cast(temp_hold_new_level_); //再詠唱
        } else if (temp_hold_status_  == STATE_INVOKING) {
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] 持続時間満期レベルダウン時に詠唱中だったのでここで自動再発動！ invoke("<<temp_hold_new_level_<<")");
            invoke(temp_hold_new_level_); //再発動
        }
        temp_hold_status_ = -1;
    }
    //魔法効果中・・・
    processEffectingBehavior(last_level_, level_); //コールバック

    do { //break 脱出用
    if (level_ > 0) {
        if (_pProg->isJustChangedTo(STATE_EFFECT_START) && time_of_effect_base_ == 0) {
            //即効性魔法のため終了
            for (int lv = 1; lv <= level_; lv++) { //全レベルリセットを設定
                 lvinfo_[lv].remainingtime_of_effect_ = 0; //効果持続終了残り時間を0
            }
            effect(0);
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] 即効性魔法のため、いきなり持続終了。last_level_="<<last_level_<<" level_="<<level_);
            break;
        }

        //即効性魔法以外
        //効果持続魔法（コスト計算）
        //維持コストあり？
        if (keep_cost_base_ != 0) {
            //維持コストがかかる場合
            *pMP_ += -1*lvinfo_[level_].keep_cost_; //維持コスト減少
            //MP枯渇？
            if (*pMP_ <= 0) {
                //MP枯渇による持続終了時
                *pMP_ = 0;
                for (int lv = 1; lv <= level_; lv++) { //全レベルリセットを設定
                     lvinfo_[lv].remainingtime_of_effect_ = 0; //効果持続終了残り時間を0
                }
                effect(0);
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] MP枯渇による持続終了。");
                break;
            }
        }

        lvinfo_[level_].remainingtime_of_effect_ --;   //効果持続残り時間減少
        if (lvinfo_[level_].remainingtime_of_effect_ == 0) { //満期？
            //持続時間満期でレベルダウン処理
             _TRACE_("Magic::processBehavior() ["<<getName()<<"] 持続時間満期処理 lv="<<level_<<"→"<<(level_-1)<<"");
            //effect(level_-1); をおこないたいのやまやまだが、
            //持続時間満期によるレベルダウンは、操作によるレベルダウンとは状況が少し異なり、
            //上位レベルを詠唱中、または発動中だった場合 effect の後に、ステータスを元に戻す必要がある。
            if (prog == STATE_CASTING) {
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] 効果持続中・・・・、現在詠唱中で持続時間満期処理。effect() 後再詠唱予約");
                temp_hold_status_ = _pProg->get(); //そこで、現ステータスを一時退避(やや苦しい・・・)
                temp_hold_new_level_ = new_level_; //詠唱又は発動しようとしていた新レベルも保持
            } else if (prog == STATE_INVOKING) {
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] 効果持続中・・・・、現在発動中で持続時間満期処理。effect() 後発動予約");
                temp_hold_status_ = _pProg->get(); //そこで、現ステータスを一時退避(やや苦しい・・・)
                temp_hold_new_level_ = new_level_; //詠唱又は発動しようとしていた新レベルも保持
            } else {
                //STATE_EFFECT_START
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] 効果持続中・・・・、普通に持続時間満期処理 (^_^)");
            }
            effect(level_-1);
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] 持続時間満期で持続終了。");
            break;
        }
    }
    } while(false);


    //_TRACE_("Magic::processBehavior() F="<<getBehaveingFrame()<<" after _pProg->get()="<<_pProg->get());

}

magic_point Magic::calcReduceMp(int prm_now_level, int prm_target_down_level) {
    //コスト還元。
    //この計算式では、レベル0 > 最大レベルアップ ＞ レベル0へレベルダウン を素早く行うと、
    //ロス無しという計算。
    //各レベルの残りの効果持続時間の割合も考慮する。
    //_TRACE_("calcReduceMp!!!");
    //_TRACE_("prm_now_level="<<prm_now_level<<" prm_target_down_level="<<prm_target_down_level);
    magic_point mp = 0;
    for (int lv = prm_now_level; lv > prm_target_down_level; lv--) {
        double utilization_rate = lvinfo_[lv].time_of_effect_ == 0 ? 0.0 : (1.0*lvinfo_[lv].remainingtime_of_effect_ / lvinfo_[lv].time_of_effect_); //使用率
        mp += (lvinfo_[lv].cost_ * utilization_rate * lvdiff_[max_level_-(prm_now_level-lv)].r_cost_lv_diff_);
        //_TRACE_(lv << ":lvinfo_["<<lv<<"].cost_="<<(lvinfo_[lv].cost_)<<" ");
        //_TRACE_(lv << ":utilization_rate="<<utilization_rate<<" ");
        //_TRACE_(lv << ":lvdiff_[max_level_-(prm_now_level-lv)]=lvdiff_["<<max_level_<<"-("<<prm_now_level<<"-"<<lv<<")]=lvdiff_["<<(max_level_-(prm_now_level-lv))<<"].r_cost_lv_diff_="<<(lvdiff_[max_level_-(prm_now_level-lv)].r_cost_lv_diff_));
        //_TRACE_(lv << ":+="<<(lvinfo_[lv].cost_ * utilization_rate * lvdiff_[max_level_-(prm_now_level-lv)].r_cost_lv_diff_));
        //_TRACE_(lv << ":mp="<<mp);
    }
//_TRACE_("return="<<mp);
    return mp;
}

Magic::~Magic() {
}
