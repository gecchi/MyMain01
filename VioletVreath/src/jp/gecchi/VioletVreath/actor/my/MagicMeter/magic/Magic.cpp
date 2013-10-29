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

    //�e���x���ʎ������ԋy�сA�R�X�g�A�r�����ԁA�������ԁA���ʎ������ԁA�ێ��R�X�g��\�ߐݒ�
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

    //���x�������
    lvdiff_[0].r_cost_lv_diff_             = 0.0; //���x�����O�ɃR�X�g�͖����B
    lvdiff_[0].r_time_of_casting_lv_diff_  = 0.0;
    lvdiff_[0].r_time_of_invoking_lv_diff_ = 0.0;
    lvdiff_[1].r_cost_lv_diff_             = 1.0;  //���x�����P�Ƀ{�[�i�X���T�͖����B
    lvdiff_[1].r_time_of_casting_lv_diff_  = 1.0;
    lvdiff_[1].r_time_of_invoking_lv_diff_ = 1.0;
    lvdiff_[2].r_cost_lv_diff_             = r_cost_lv_diff_base_; //���x�����Q�ŏ��߂Ă����ɂȂ�B
    lvdiff_[2].r_time_of_casting_lv_diff_  = r_time_of_casting_lv_diff_base_;
    lvdiff_[2].r_time_of_invoking_lv_diff_ = r_time_of_invoking_lv_diff_base_;
    for (int i = 2; i <= MMETER_MAX_LEVEL; i++) { //���x������������Ƃ�肨���B
        lvdiff_[i].r_cost_lv_diff_             = lvdiff_[i-1].r_cost_lv_diff_            * r_cost_lv_diff_base_;
        lvdiff_[i].r_time_of_casting_lv_diff_  = lvdiff_[i-1].r_time_of_casting_lv_diff_ * r_time_of_casting_lv_diff_base_;
        lvdiff_[i].r_time_of_invoking_lv_diff_ = lvdiff_[i-1].r_time_of_invoking_lv_diff_* r_time_of_invoking_lv_diff_base_;
    }

    _TRACE_("Magic::Magic "<<getName()<<" �̃��x���A�b�v���̐��l");
    //���x���A�b�v���̃R�X�g�A�r�����ԁA�������Ԃ�\�ߌv�Z
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
             _TRACE_("Magic::Magic["<<getName()<<"] level_up_cost_["<<now_lv<<"��"<<target_lv<<"]="<<level_up_cost_[now_lv][target_lv]);
        }
    }
    for (int now_lv = 0; now_lv <= MMETER_MAX_LEVEL; now_lv++) {
        for (int target_lv = now_lv; target_lv <= MMETER_MAX_LEVEL; target_lv++) {
             _TRACE_("Magic::Magic["<<getName()<<"] level_up_time_of_casting_["<<now_lv<<"��"<<target_lv<<"]="<<level_up_time_of_casting_[now_lv][target_lv]);
        }
    }
    for (int now_lv = 0; now_lv <= MMETER_MAX_LEVEL; now_lv++) {
        for (int target_lv = now_lv; target_lv <= MMETER_MAX_LEVEL; target_lv++) {
            _TRACE_("Magic::Magic["<<getName()<<"] level_up_time_of_invoking_["<<now_lv<<"��"<<target_lv<<"]="<<level_up_time_of_invoking_[now_lv][target_lv]);
        }
    }
#endif

    //���x���_�E�����͗��p��������̂ŁA���
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
    //�e���x���ʎ������ԋy�сA�ێ��R�X�g��\�ߐݒ�
    lvinfo_[0].remainingtime_of_effect_ = MAX_MAGIC_TIME;
    lvinfo_[1].remainingtime_of_effect_ = 0;
    for (int i = 2; i <= max_level_; i++) {
        lvinfo_[i].remainingtime_of_effect_ = 0;
        effect(0); //�e���@���x��0�����s
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
    effect(level_); //MAGIC_EFFECT_NOTHING������OK�Ǝv��
}

int Magic::chkCastAble(int prm_new_level) {
    if (_pProg->get() == STATE_INVOKING) {
        return MAGIC_CAST_NG_INVOKING_NOW; //�������̂��ߎ��s�s��
    } else if (_pProg->get() == STATE_CASTING) {
        //���̃��x�����r�����ɉr���Ď��s
        if (level_ > prm_new_level) {
            return MAGIC_CAST_CANCEL_AND_LEVELDOWN; //�r���L�����Z�����x���_�E��OK
        } else if (level_ < prm_new_level) {
            if (level_up_cost_[level_][prm_new_level] <= *pMP_) {
                return MAGIC_CAST_OK_CANCEL_AND_LEVELUP; //�r���L�����Z���ĉr�����x���A�b�vOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MP������Ȃ����߁A�ĉr�����x���A�b�v�s��
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_CANCEL; //�r���L�����Z��
        }
    } else {
        //�ҋ@��Ԃ����ʎ������ɉr�����s
        if (level_ > prm_new_level) {
            return MAGIC_CAST_LEVELDOWN; //�r�����x���_�E��OK
        } else if (level_ < prm_new_level) {
            if (level_up_cost_[level_][prm_new_level] <= *pMP_) {
                return MAGIC_CAST_OK_LEVELUP; //�r�����x���A�b�vOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MP������Ȃ����߁A�r�����x���A�b�v�s��
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_NOTHING; //�������Ȃ��B
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
            //���ʔ������̂��߉r���s�������̂ŁA�������Ȃ��B
            break;
        }
        case MAGIC_CAST_NG_MP_IS_SHORT: {
            //MP�����Ȃ��r���s�������̂ŁA�������Ȃ��B
            break;
        }
        case MAGIC_CAST_NOTHING: {
            //���݂̃��x���Ɠ������x�����r�����悤�Ƃ��Ă���A�������Ȃ��B
            break;
        }
        case MAGIC_CAST_CANCEL: {
            //���̃��x�����r�����ɍĉr�����s�����Ƃ��Ă���
            //�ĉr���̃��x�����A���݂̌��ʎ������x���Ɠ������x�����w�肵�����߁A
            //�r�����~(�L�����Z��)�����ɂȂ�B
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_CAST_CANCEL!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_CAST_OK_LEVELUP: {
            //���݂̌��ʎ������x����荂�����x�����r�����悤�Ƃ��Ă���B
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_CAST_OK_LEVELUP!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_CASTING);
            break;
        }
        case MAGIC_CAST_LEVELDOWN: {
            //���݂̌��ʎ������x�����Ⴂ���x�����r�����悤�Ƃ��Ă���B
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_CAST_LEVELDOWN!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_CASTING);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
            //���̃��x�����r�����ɍĉr�����s�����Ƃ��Ă���
            //�ĉr���̃��x�����A���݂̌��ʎ������x����荂���B
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_CAST_OK_CANCEL_AND_LEVELUP!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_RE_CASTING);
            break;
        }
        case MAGIC_CAST_CANCEL_AND_LEVELDOWN: {
            //���̃��x�����r�����ɍĉr�����s�����Ƃ��Ă���
            //�ĉr���̃��x�����A���݂̌��ʎ������x�����Ⴂ�B
            _TRACE_("Magic::cast("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_CAST_CANCEL_AND_LEVELDOWN!");
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
        //�������̂��ߎ��s�s��
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
            //���蓾�Ȃ�
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" �� MAGIC_INVOKE_NG_INVOKING_NOW �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
            break;
        }
        case MAGIC_INVOKE_NG_MP_IS_SHORT: {
            _TRACE_("Magic::invoke("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_INVOKE_NG_MP_IS_SHORT!");
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELUP: {
            _TRACE_("Magic::invoke("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_INVOKE_OK_LEVELUP!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_INVOKING);
            break;
        }
        case MAGIC_INVOKE_OK_LEVELDOWN: {
            _TRACE_("Magic::invoke("<<prm_new_level<<") ["<<getName()<<"] ���聨MAGIC_INVOKE_OK_LEVELDOWN!");
            new_level_nextframe_ = prm_new_level;
            _pProg->change(STATE_INVOKING);
            break;
        }
        case MAGIC_INVOKE_NOTHING: {
            //���蓾�Ȃ�
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" �� MAGIC_INVOKE_NOTHING �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
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
            //throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" �� MAGIC_EFFECT_NG_MP_IS_SHORT �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
            //���肤��
            _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] ���聨MAGIC_EFFECT_NG_MP_IS_SHORT�Achange(STATE_NOTHING)");
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_EFFECT_NOTHING: {
            if (prm_level == 0) {
                //effect(0) �̏����B�R���� onReset�ōs���鏉�����B
                _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] ���聨MAGIC_EFFECT_NOTHING�A�Ȃɂ����܂���");
            } else {
                throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" �� MAGIC_EFFECT_NOTHING �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
            }
            break;
        }
        case MAGIC_EFFECT_OK_LEVELUP: {
            _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] ���聨MAGIC_EFFECT_OK_LEVELUP�Achange(STATE_EFFECT_START)");
            //���x���X�V
            last_level_nextframe_ = level_;
            level_nextframe_ = prm_level;
            _pProg->change(STATE_EFFECT_START);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            _TRACE_("Magic::effect("<<prm_level<<") ["<<getName()<<"] ���聨MAGIC_EFFECT_OK_LEVELDOWN�Achange(STATE_RE_EFFECT)");
            //���x���X�V
            last_level_nextframe_ = level_;
            level_nextframe_ = prm_level;
            _pProg->change(STATE_RE_EFFECT); //���� STATE_EFFECT_START �̂���
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
        /////////////////////////////////////// �ҋ@
        case STATE_NOTHING: {
            if (_pProg->isJustChanged()) {
                if (_pProg->isJustChangedFrom(STATE_CASTING)) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] �r���L�����Z���I���I");
                    processCastingCancel(level_); //�R�[���o�b�N
                } else if (_pProg->isJustChangedFrom(STATE_INVOKING)) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] �����L�����Z���I���I");
                    processInvokingCancel(level_); //�R�[���o�b�N
                }
            }
            break;
        }

        /////////////////////////////////////// �r�����L�����Z���ĉr��
        case STATE_RE_CASTING: {
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] �r���L�����Z���ĉr���I");
            processCastingCancel(level_); //�R�[���o�b�N
            _pProg->change(STATE_CASTING);
            break;
        }
        /////////////////////////////////////// �r����
        case STATE_CASTING: {
            if (_pProg->isJustChanged()) { //�r���J�n
                time_of_next_state_ = level_up_time_of_casting_[level_][new_level_]; //�r���I������
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] STATE_CASTING begin new_level_="<<new_level_<<" level_="<<level_<<" time_of_next_state_="<<time_of_next_state_<<"");
                processCastBegin(level_, new_level_);  //�R�[���o�b�N
            }
            //�r��������
            processCastingBehavior(level_, new_level_); //�R�[���o�b�N
            if (level_ > new_level_ || _pProg->getFrameInProgress() >= time_of_next_state_) {
                //���x���_�E�����͑����ŁA���邢�͉r���I����
                int r = invoke(new_level_);
                processCastFinish(level_, new_level_, r);  //�R�[���o�b�N
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] �r��(STATE_CASTING)�X�e�[�^�X�I���I");
            }
            break;
        }

        /////////////////////////////////////// ������
        case STATE_INVOKING: {
            if (_pProg->isJustChanged()) { //�����J�n
                time_of_next_state_ = level_up_time_of_invoking_[level_][new_level_]; //�����I������
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] STATE_INVOKING begin new_level_="<<new_level_<<" level_="<<level_<<" time_of_next_state_="<<time_of_next_state_<<"");
                processInvokeBegin(level_, new_level_);     //�R�[���o�b�N
            }
            //����������
            processInvokingBehavior(level_, new_level_);  //�R�[���o�b�N
            if (level_ > new_level_ || _pProg->getFrameInProgress() >= time_of_next_state_) {
                //���x���_�E�����͑����ŁA���邢�͔����I��
                int r = effect(new_level_);
                processInvokeFinish(level_, new_level_, r); //�R�[���o�b�N
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] ����(STATE_INVOKING)�X�e�[�^�X�I���I");
            }
            break;
        }

        /////////////////////////////////////// �������A�������x���_�E���Ď����J�n
        case STATE_RE_EFFECT: {
            _pProg->change(STATE_EFFECT_START);
            break;
        }
        /////////////////////////////////////// �����J�n
        case STATE_EFFECT_START: {
            if (_pProg->isJustChanged()) { //�����J�n
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] STATE_EFFECT_START begin");

                processEffectBegin(last_level_, level_); //���ʎ����J�n�R�[���o�b�N

                //MP����v�Z
                if (last_level_ < level_) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] ���x���A�b�v�������Blast_level_="<<last_level_<<" level_="<<level_);
                    //���x���A�b�v�������ꍇ
                    //���ʎ������Ԑݒ�B��щz���ꂽ�Ԃ̃��x�������ʎ����I���c�莞�Ԃ𖞃^����ݒ�
                    for (int lv = last_level_+1; lv <= level_; lv++) {
                        lvinfo_[lv].remainingtime_of_effect_ = lvinfo_[lv].time_of_effect_; //�������Ԃ𖞃^��
                    }

                    *pMP_ -= level_up_cost_[last_level_][level_]; //MP����
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] "<<level_up_cost_[last_level_][level_]<<"MP����("<<((*pMP_)+level_up_cost_[last_level_][level_])<<"��"<<(*pMP_)<<")");
                    if (*pMP_ < 0) {
                        *pMP_ = 0;
                    }
                } else if (last_level_ > level_) {
                    _TRACE_("Magic::processBehavior() ["<<getName()<<"] ���x���_�E���������Blast_level_="<<last_level_<<" level_="<<level_);
                    //���x���_�E���������ꍇ
                    if (keep_cost_base_ == 0) { //�ێ��R�X�g��������Ȃ����@�̏ꍇ��
                        if (lvinfo_[last_level_].time_of_effect_ > 0) {
                            //MP�Ҍ�
                            magic_point rmp = calcReduceMp(last_level_, level_);
                            *pMP_ += rmp;
                            _TRACE_("Magic::processBehavior() ["<<getName()<<"] "<<rmp<<"MP�Ҍ�("<<((*pMP_)-rmp)<<"��"<<(*pMP_)<<")");
                            if (*pMP_ > MY_SHIP_MAX_MP) {
                                *pMP_ = MY_SHIP_MAX_MP;
                            }
                        }
                    }

                    //��щz���ꂽ�Ԃ̃��x���͒�~���Č��ʎ����I���c�莞�Ԃ����Z�b�g��ݒ�
                    for (int lv = last_level_; lv >= level_+1; lv--) {
                        lvinfo_[lv].remainingtime_of_effect_ = 0; //���ʎ����I���c�莞�Ԃ�0
                    }
                    //level_�̌��ʎ������Ԃ͑O�̑���
                } else {
                    //last_level_ == level_
                }

            }

            //�����������͂����ɏ����͋L�q���Ȃ����ƁB
            _pProg->change(STATE_NOTHING);
            break;
        }

        default :
            break;
    }
    ///////////////////////////////////////

    if (temp_hold_status_ != -1) {
        //�ꎞ�ޔ��X�e�[�^�X������ꍇ�A���Ƃɖ߂�
        if (temp_hold_status_ == STATE_CASTING) {
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] �������Ԗ������x���_�E�����ɉr�����������̂ł����Ŏ����ĉr���I cast("<<temp_hold_new_level_<<")");
            cast(temp_hold_new_level_); //�ĉr��
        } else if (temp_hold_status_  == STATE_INVOKING) {
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] �������Ԗ������x���_�E�����ɉr�����������̂ł����Ŏ����Ĕ����I invoke("<<temp_hold_new_level_<<")");
            invoke(temp_hold_new_level_); //�Ĕ���
        }
        temp_hold_status_ = -1;
    }
    //���@���ʒ��E�E�E
    processEffectingBehavior(last_level_, level_); //�R�[���o�b�N

    do { //break �E�o�p
    if (level_ > 0) {
        if (_pProg->isJustChangedTo(STATE_EFFECT_START) && time_of_effect_base_ == 0) {
            //���������@�̂��ߏI��
            for (int lv = 1; lv <= level_; lv++) { //�S���x�����Z�b�g��ݒ�
                 lvinfo_[lv].remainingtime_of_effect_ = 0; //���ʎ����I���c�莞�Ԃ�0
            }
            effect(0);
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] ���������@�̂��߁A�����Ȃ莝���I���Blast_level_="<<last_level_<<" level_="<<level_);
            break;
        }

        //���������@�ȊO
        //���ʎ������@�i�R�X�g�v�Z�j
        //�ێ��R�X�g����H
        if (keep_cost_base_ != 0) {
            //�ێ��R�X�g��������ꍇ
            *pMP_ += -1*lvinfo_[level_].keep_cost_; //�ێ��R�X�g����
            //MP�͊��H
            if (*pMP_ <= 0) {
                //MP�͊��ɂ�鎝���I����
                *pMP_ = 0;
                for (int lv = 1; lv <= level_; lv++) { //�S���x�����Z�b�g��ݒ�
                     lvinfo_[lv].remainingtime_of_effect_ = 0; //���ʎ����I���c�莞�Ԃ�0
                }
                effect(0);
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] MP�͊��ɂ�鎝���I���B");
                break;
            }
        }

        lvinfo_[level_].remainingtime_of_effect_ --;   //���ʎ����c�莞�Ԍ���
        if (lvinfo_[level_].remainingtime_of_effect_ == 0) { //�����H
            //�������Ԗ����Ń��x���_�E������
             _TRACE_("Magic::processBehavior() ["<<getName()<<"] �������Ԗ������� lv="<<level_<<"��"<<(level_-1)<<"");
            //effect(level_-1); �������Ȃ������̂�܂�܂����A
            //�������Ԗ����ɂ�郌�x���_�E���́A����ɂ�郌�x���_�E���Ƃ͏󋵂������قȂ�A
            //��ʃ��x�����r�����A�܂��͔������������ꍇ effect �̌�ɁA�X�e�[�^�X�����ɖ߂��K�v������B
            if (prog == STATE_CASTING) {
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] ���ʎ������E�E�E�E�A���݉r�����Ŏ������Ԗ��������Beffect() ��ĉr���\��");
                temp_hold_status_ = _pProg->get(); //�����ŁA���X�e�[�^�X���ꎞ�ޔ�(���ꂵ���E�E�E)
                temp_hold_new_level_ = new_level_; //�r�����͔������悤�Ƃ��Ă����V���x�����ێ�
            } else if (prog == STATE_INVOKING) {
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] ���ʎ������E�E�E�E�A���ݔ������Ŏ������Ԗ��������Beffect() �㔭���\��");
                temp_hold_status_ = _pProg->get(); //�����ŁA���X�e�[�^�X���ꎞ�ޔ�(���ꂵ���E�E�E)
                temp_hold_new_level_ = new_level_; //�r�����͔������悤�Ƃ��Ă����V���x�����ێ�
            } else {
                //STATE_EFFECT_START
                _TRACE_("Magic::processBehavior() ["<<getName()<<"] ���ʎ������E�E�E�E�A���ʂɎ������Ԗ������� (^_^)");
            }
            effect(level_-1);
            _TRACE_("Magic::processBehavior() ["<<getName()<<"] �������Ԗ����Ŏ����I���B");
            break;
        }
    }
    } while(false);


    //_TRACE_("Magic::processBehavior() F="<<getBehaveingFrame()<<" after _pProg->get()="<<_pProg->get());

}

magic_point Magic::calcReduceMp(int prm_now_level, int prm_target_down_level) {
    //�R�X�g�Ҍ��B
    //���̌v�Z���ł́A���x��0 > �ő僌�x���A�b�v �� ���x��0�փ��x���_�E�� ��f�����s���ƁA
    //���X�����Ƃ����v�Z�B
    //�e���x���̎c��̌��ʎ������Ԃ̊������l������B
    //_TRACE_("calcReduceMp!!!");
    //_TRACE_("prm_now_level="<<prm_now_level<<" prm_target_down_level="<<prm_target_down_level);
    magic_point mp = 0;
    for (int lv = prm_now_level; lv > prm_target_down_level; lv--) {
        double utilization_rate = lvinfo_[lv].time_of_effect_ == 0 ? 0.0 : (1.0*lvinfo_[lv].remainingtime_of_effect_ / lvinfo_[lv].time_of_effect_); //�g�p��
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
