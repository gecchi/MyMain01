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
    r_keep_cost_         = prm_r_each_lv_keep_cost;

    //�e���x���ʎ������ԋy�сA�ێ��R�X�g��\�ߐݒ�
    lvinfo_[0].is_working_ = false;
    lvinfo_[0].remainingtime_of_effect_ = 0;
    lvinfo_[0].time_of_effect_ = 0;
    lvinfo_[0].keep_cost_ = 0;
    lvinfo_[1].is_working_ = false;
    lvinfo_[1].remainingtime_of_effect_ = 0;
    lvinfo_[1].time_of_effect_ = time_of_effect_base_;
    lvinfo_[1].keep_cost_ = keep_cost_base_;

    for (int i = 2; i <= max_level_; i++) {
        lvinfo_[i].is_working_ = false;
        lvinfo_[i].remainingtime_of_effect_ = 0;
        lvinfo_[i].time_of_effect_ = lvinfo_[i-1].time_of_effect_ * r_each_lv_time_of_effecting_;
        lvinfo_[i].keep_cost_      = lvinfo_[i-1].keep_cost_      * r_keep_cost_;
    }

    time_of_next_state_ = 0;
    is_working_ = false;

    useProgress(STATE_ABANDONING);
    _pProg->set(STATE_NOTHING);


    //��у��x�����ʏ���ݒ�
    interest_cost_[0] = 0;
    interest_time_of_casting_[0] = 0;
    interest_time_of_invoking_[0] = 0;
    for (int i = 1; i <= max_level_; i++) {
        interest_cost_[i]             = (cost_base_ * i) * r_cost_;
        interest_time_of_casting_[i]  = (time_of_casting_base_ * i) * r_time_of_casting_;
        interest_time_of_invoking_[i] = (time_of_invoking_base_ * i) * r_time_of_invoking_;
    }
}

void Magic::save(std::stringstream& sts) {
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

void Magic::load(std::stringstream& sts) {
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
    effect(level_); //MAGIC_EFFECT_NOTHING������OK�Ǝv��
}

int Magic::chkCastAble(int prm_new_level) {
    if (_pProg->get() == STATE_INVOKING || _pProg->get() == STATE_INVOKE_BEGIN) {
        return MAGIC_CAST_NG_INVOKING_NOW; //�������̂��ߎ��s�s��
    } else if (_pProg->get() == STATE_CASTING || _pProg->get() == STATE_CAST_BEGIN) {
        //���̃��x�����r�����ɉr���Ď��s
        if (level_ > prm_new_level) {
            return MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN; //�ĉr�����x���_�E��OK
        } else if (level_ < prm_new_level) {
            if (interest_cost_[prm_new_level-level_] < pMP_->get()) {
                return MAGIC_CAST_OK_CANCEL_AND_LEVELUP; //�ĉr�����x���A�b�vOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MP������Ȃ����߁A�ĉr�����x���A�b�v�s��
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_CANCEL; //�r���L�����Z��
        }
    } else {
        //�ҋ@��Ԃ����ʎ������ɉr�����s
        if (level_ > prm_new_level) {
            return MAGIC_CAST_OK_LEVELDOWN; //�r�����x���_�E��OK
        } else if (level_ < prm_new_level) {
            if (interest_cost_[prm_new_level-level_] < pMP_->get()) {
                return MAGIC_CAST_OK_LEVELUP; //�r�����x���A�b�vOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MP������Ȃ����߁A�ĉr�����x���A�b�v�s��
            }
        } else { //level_==prm_new_level
            return MAGIC_CAST_NOTHING; //�������Ȃ��B
        }
    }
}
int Magic::cast(int prm_new_level) {
    int r = chkCastAble(prm_new_level);
    switch (r) {
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
            is_working_ = false;
            new_level_ = prm_new_level;
            _pProg->change(STATE_NOTHING);
            break;
        }
        case MAGIC_CAST_OK_LEVELUP: {
            //���݂̌��ʎ������x����荂�����x�����r�����悤�Ƃ��Ă���B
            is_working_ = true;
            new_level_ = prm_new_level;
            _pProg->change(STATE_CAST_BEGIN);
            break;
        }
        case MAGIC_CAST_OK_LEVELDOWN: {
            //���݂̌��ʎ������x�����Ⴂ���x�����r�����悤�Ƃ��Ă���B
            is_working_ = true;
            effect(prm_new_level);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELUP: {
            //���̃��x�����r�����ɍĉr�����s�����Ƃ��Ă���
            //�ĉr���̃��x�����A���݂̌��ʎ������x����荂���B
            is_working_ = true;
            new_level_ = prm_new_level;
            _pProg->change(STATE_CAST_BEGIN);
            break;
        }
        case MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN: {
            //���̃��x�����r�����ɍĉr�����s�����Ƃ��Ă���
            //�ĉr���̃��x�����A���݂̌��ʎ������x�����Ⴂ�B
            is_working_ = true;
            effect(prm_new_level);
            break;
        }
    }
    return r;
}

int Magic::chkInvokeAble(int prm_new_level) {
    if (_pProg->get() == STATE_INVOKING || _pProg->get() == STATE_INVOKE_BEGIN) {
        //�������̂��ߎ��s�s��
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
            //���蓾�Ȃ�
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" �� MAGIC_INVOKE_NG_INVOKING_NOW �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
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
            //���蓾�Ȃ�
            throwGgafCriticalException("Magic::invoke("<<prm_new_level<<") "<<getName()<<" �� MAGIC_INVOKE_NOTHING �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
            break;
        }
    }
    return r;
}
int Magic::effect(int prm_level) {
    int r = chkEffectAble(prm_level);

    switch (r) {
        case MAGIC_EFFECT_NG_MP_IS_SHORT: {
            throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" �� MAGIC_EFFECT_NG_MP_IS_SHORT �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
            break;
        }
        case MAGIC_EFFECT_NOTHING: {
            throwGgafCriticalException("Magic::effect("<<prm_level<<") "<<getName()<<" �� MAGIC_EFFECT_NOTHING �́A���̃^�C�~���O�ł��蓾�Ȃ��͂��ł��B");
            break;
        }
        case MAGIC_EFFECT_OK_LEVELUP: {
            //���ݖ��@���x���͒�~����
            lvinfo_[level_].is_working_ = false;
            //���x���X�V
            last_level_ = level_;
            level_ = prm_level;
            _pProg->change(STATE_EFFECT_BEGIN);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            //���ݖ��@���x���͒�~����
            lvinfo_[level_].is_working_ = false;
            //���x���X�V
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
            /////////////////////////////////////// �ҋ@
            case STATE_NOTHING: {
                break;
            }

            /////////////////////////////////////// �r���J�n
            case STATE_CAST_BEGIN: {
                //�r���I�����Ԃ��v�Z
                time_of_next_state_ = interest_time_of_casting_[new_level_- level_];
                processCastBegin(level_, new_level_);  //�R�[���o�b�N

                _pProg->set(STATE_CASTING);
                //�� fall down ��
            }
            /////////////////////////////////////// �r����
            case STATE_CASTING: {
                processCastingBehavior(level_, new_level_); //�R�[���o�b�N

                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //�r���I��
                    int r = invoke(new_level_);
                    processCastFinish(level_, new_level_, r);  //�R�[���o�b�N
                }
                break;
            }
            /////////////////////////////////////// �����J�n
            case STATE_INVOKE_BEGIN : {
                //�����I�����Ԑݒ�
                time_of_next_state_ = interest_time_of_invoking_[new_level_- level_];
                processInvokeBegin(level_, new_level_);     //�R�[���o�b�N

                _pProg->set(STATE_INVOKING);
                //�� fall down ��
            }

            /////////////////////////////////////// ������
            case STATE_INVOKING: {
                processInvokingBehavior(level_, new_level_);  //�R�[���o�b�N

                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //�����I��
                    int r = effect(new_level_);
                    processInvokeFinish(level_, new_level_, r); //�R�[���o�b�N
                }
                break;
            }
            /////////////////////////////////////// �����J�n
            case STATE_EFFECT_BEGIN: {
                //MP����v�Z
                if (last_level_ < level_) {
                    //���x���A�b�v�������ꍇ
                    //��щz���ꂽ�Ԃ̃��x���͒�~���Č��ʎ����I���c�莞�Ԃ𖞃^����ݒ�
                    for (int lv = last_level_+1; lv <= level_-1; lv++) {
                        lvinfo_[lv].is_working_ = false; //��~��
                        lvinfo_[lv].remainingtime_of_effect_ = lvinfo_[lv].time_of_effect_; //�������Ԃ𖞃^��
                    }
                    pMP_->dec(interest_cost_[level_-last_level_]); //MP����
                } else if (last_level_ > level_) {
                    //���x���_�E���������ꍇ

                    if (keep_cost_base_ == 0) { //�ێ��R�X�g��������Ȃ����@�̏ꍇ��
                        if (lvinfo_[last_level_].time_of_effect_ > 0) {
                            //MP�Ҍ�
                            pMP_->inc(calcReduceMp(last_level_, level_));
                        }
                    }

                    //��щz���ꂽ�Ԃ̃��x���͒�~���Č��ʎ����I���c�莞�Ԃ����Z�b�g��ݒ�
                    for (int lv = level_+1 ; lv <= last_level_-1; lv++) {
                        lvinfo_[lv].is_working_ = false; //��~��
                        lvinfo_[lv].remainingtime_of_effect_ = 0; //�ʎ����I���c�莞�Ԃ�0
                    }
                } else {
                }


                if (level_ == 0) {
                    _pProg->change(STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                    break;
                }

                //����̐V���ȃ��x����ݒ�
                lvinfo_[level_].is_working_ = true;
                if (last_level_ < level_) {
                    //���x���A�b�v�������ꍇ
                    lvinfo_[level_].remainingtime_of_effect_ = lvinfo_[level_].time_of_effect_; //���񎝑����Ԃ𖞃^��
                } else if (last_level_ > level_) {
                    //���x���_�E���������ꍇ�A���񎝑����Ԃ͑O��̑���
                } else {
                    _TRACE_("last_level_����level_�A");
                }
                //���ʎ����J�n
                processEffectBegin(last_level_, level_); //�R�[���o�b�N

                _pProg->set(STATE_EFFECTING);
                //�� fall down ��
            }

            default :
                break;
        }
        /////////////////////////////////////// ������
        //case STATE_EFFECTING:
        if (time_of_effect_base_ == 0) {
            //���������@
            for (int lv = 1; lv <= level_; lv++) { //�S���x�����Z�b�g��ݒ�
                 lvinfo_[lv].is_working_ = false;          //��~��
                 lvinfo_[lv].remainingtime_of_effect_ = 0; //���ʎ����I���c�莞�Ԃ�0
            }
            new_level_ = 0;
            last_level_ = level_;
            level_ = new_level_;
            processEffectFinish(last_level_); //�R�[���o�b�N MP�͊��ɂ�閂�@�I��
            _pProg->change(STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
        } else {
            //���ʎ������@
            if (level_ > 0) {
                processEffectingBehavior(last_level_, level_); //�R�[���o�b�N
                lvinfo_[level_].remainingtime_of_effect_ --; //���ʎ����c�莞�Ԍ���


                if (keep_cost_base_ != 0) {
                    //�ێ��R�X�g��������ꍇ�̏���
                    pMP_->inc(-1*lvinfo_[level_].keep_cost_); //�ێ��R�X�g����
                    //MP�͊��H
                    if (pMP_->get() <= 0) {
                        //MP�͊��ɂ�鎝���I����
                        pMP_->set(0);
                        for (int lv = 1; lv <= level_; lv++) { //�S���x�����Z�b�g��ݒ�
                             lvinfo_[lv].is_working_ = false;           //��~��
                             lvinfo_[lv].remainingtime_of_effect_ = 0; //���ʎ����I���c�莞�Ԃ�0
                        }
                        new_level_ = 0;
                        last_level_ = level_;
                        level_ = new_level_;
                        processEffectFinish(last_level_); //�R�[���o�b�N MP�͊��ɂ�閂�@�I��
                        _pProg->change(STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                    }
                }
            }

            if (level_ > 0) {
                //�������Ԗ�������
                if (lvinfo_[level_].remainingtime_of_effect_ == 0) {
                    effect(level_-1); //���x���_�E��(-1)���s���B
                    if (level_ == 0) { //�����x�����P�ŁA���x���_�E��(-1)�ɂ��nothing�ɂȂ����ꍇ
                        processEffectFinish(last_level_); //�R�[���o�b�N
                        _pProg->change(STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                    }
                }
            }
        }
    }

}

magic_point Magic::calcReduceMp(int prm_now_level, int prm_target_down_level) {
    //�R�X�g�Ҍ��B
    //���̌v�Z���ł́A���x��0 > MAX���x���A�b�v �� ���x��0�փ��x���_�E�� ��f�����s���ƁA
    //���X�����Ƃ����v�Z�B
    //�e���x���̎c��̌��ʎ������Ԃ̊������l������B
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
