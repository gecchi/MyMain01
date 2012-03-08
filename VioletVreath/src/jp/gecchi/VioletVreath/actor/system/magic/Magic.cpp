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

    //��у��x�����ʏ���ݒ�
    interest_cost_[0] = 0;
    interest_time_of_casting_[0] = 0;
    interest_time_of_invoking_[0] = 0;
    for (int i = 1; i <= max_level_; i++) {
        interest_cost_[i]             = (cost_base_ * i) * fRate_cost_;
        interest_time_of_casting_[i]  = (time_of_casting_base_ * i) *  fRate_time_of_casting_;
        interest_time_of_invoking_[i] = (time_of_invoking_base_ * i) *  fRate_time_of_invoking_;
    }

    //�e���x���ʎ������ԋy�сA�ێ��R�X�g��\�ߐݒ�
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
    effect(level_); //MAGIC_EFFECT_NOTHING������OK�Ǝv��
}

void Magic::rollOpen() {
    velo_rr_ = 0.1;
}
void Magic::rollClose() {
    velo_rr_ = -0.01;
}

int Magic::chkCastAble(int prm_new_level) {
    if (_pProg->get() == MAGIC_STATE_INVOKING) {
        return MAGIC_CAST_NG_INVOKING_NOW; //�������̂��ߎ��s�s��
    } else if (_pProg->get() == MAGIC_STATE_CASTING) {
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
            //���ݖ��@���x���͒�~����
            lvinfo_[level_].is_working_ = false;
            //���x���X�V
            last_level_ = level_;
            level_ = prm_level;
            _pProg->change(MAGIC_STATE_EFFECT_BEGEIN);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            //���ݖ��@���x���͒�~����
            lvinfo_[level_].is_working_ = false;
            //���x���X�V
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
            /////////////////////////////////////// �ҋ@
            case MAGIC_STATE_STAND_BY: {
                break;
            }
            /////////////////////////////////////// �r��
            case MAGIC_STATE_CASTING: {
                if (_pProg->isJustChanged()) { //�r���J�n
                    //�r���J�n
                    //�r���I�����Ԃ��v�Z
                    time_of_next_state_ = interest_time_of_casting_[new_level_- level_];
                    processCastBegin(level_, new_level_);  //�R�[���o�b�N
                }

                //�r����
                processCastingBehavior(level_, new_level_); //�R�[���o�b�N

                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //�r���I��
                    processCastFinish(level_, new_level_);  //�R�[���o�b�N
                    invoke(new_level_);
                }
                break;
            }
            /////////////////////////////////////// ����
            case MAGIC_STATE_INVOKING: {
                if (_pProg->isJustChanged()) {
                    //�����J�n�A
                    //�����I�����Ԑݒ�
                    time_of_next_state_ = interest_time_of_invoking_[new_level_- level_];
                    processInvokeBegin(level_, new_level_);     //�R�[���o�b�N
                }

                //������
                processInvokeingBehavior(level_, new_level_);  //�R�[���o�b�N

                if (_pProg->getFrameInProgress() >= time_of_next_state_) {
                    //�����I��
                    processInvokeFinish(level_, new_level_); //�R�[���o�b�N
                    effect(new_level_);
                }
                break;
            }
            /////////////////////////////////////// ����
            case MAGIC_STATE_EFFECT_BEGEIN: { //�����J�n
                if (level_ == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING);
                    break;
                } else if (last_level_ < level_) {
                    //���x���A�b�v�������ꍇ
                    //��щz���ꂽ�Ԃ̃��x���͒�~���Č��ʎ����I���c�莞�Ԃ𖞃^����ݒ�
                    for (int lv = last_level_+1; lv <= level_-1; lv++) {
                        lvinfo_[lv].is_working_ = false; //��~��
                        lvinfo_[lv].remainingtime_of_effect_ = lvinfo_[lv].time_of_effect_; //�������Ԃ𖞃^��
                    }
                    pMP_->dec(interest_cost_[level_-last_level_]); //MP����
                } else if (last_level_ > level_) {
                    //���x���_�E���������ꍇ
                    //��щz���ꂽ�Ԃ̃��x���͒�~���Č��ʎ����I���c�莞�Ԃ����Z�b�g��ݒ�
                    for (int lv = level_+1 ; lv <= last_level_-1; lv++) {
                        lvinfo_[lv].is_working_ = false; //��~��
                        lvinfo_[lv].remainingtime_of_effect_ = 0; //�ʎ����I���c�莞�Ԃ�0
                    }

                    if (keep_cost_base_ == 0) { //�ێ��R�X�g��������Ȃ����@�̏ꍇ��
                        if (lvinfo_[last_level_].time_of_effect_ > 0) {
                            //��{�R�X�g��60%�Ҍ��B�A���c���ʎ����̊������悸��B�������x���_�E�������ق��������ɂ��邽�߁B
                            pMP_->inc( cost_base_*(last_level_-level_)*0.6*
                                       (1.0*lvinfo_[last_level_].remainingtime_of_effect_ / lvinfo_[last_level_].time_of_effect_) );
                        }
                    }
                } else {
                    _TRACE_("last_level_����level_�@");
                }


                if (level_ == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
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

                _pProg->set(MAGIC_STATE_EFFECTING);
            }   //��break �����̗���(falldown).
                //��
            case MAGIC_STATE_EFFECTING: { //������
                processEffectingBehavior(last_level_, level_); //�R�[���o�b�N

                lvinfo_[level_].remainingtime_of_effect_ --; //���ʎ����c�莞�Ԍ���

                //�ێ��R�X�g��������ꍇ�̏���
                if (keep_cost_base_ != 0) {
                    pMP_->inc(-1*lvinfo_[level_].keep_cost_); //�ێ��R�X�g����
                    //MP�͊��H
                    if (pMP_->_val <= 0) {
                        //MP�͊��ɂ�鎝���I����
                        pMP_->_val = 0;
                        for (int lv = 1; lv <= level_; lv++) { //�S���x�����Z�b�g��ݒ�
                             lvinfo_[lv].is_working_ = false;           //��~��
                             lvinfo_[lv].remainingtime_of_effect_ = 0; //���ʎ����I���c�莞�Ԃ�0
                        }
                        new_level_ = 0;
                        last_level_ = level_;
                        level_ = new_level_;
                        processEffectFinish(last_level_); //�R�[���o�b�N MP�͊��ɂ�閂�@�I��
                        _pProg->change(MAGIC_STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                        break;
                    }
                }

                //�������Ԗ�������
                if (lvinfo_[level_].remainingtime_of_effect_ == 0) {
                    effect(level_-1);//���x���_�E��(-1)���s���B
                    if (level_ == 0) { //�����x�����P�ŁA���x���_�E��(-1)�ɂ��nothing�ɂȂ����ꍇ
                        processEffectFinish(last_level_); //�R�[���o�b�N
                        _pProg->change(MAGIC_STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
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
