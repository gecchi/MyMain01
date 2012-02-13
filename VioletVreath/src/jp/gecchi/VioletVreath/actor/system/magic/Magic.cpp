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

    //��у��x�����ʏ���ݒ�
    _interest_cost[0] = 0;
    _interest_time_of_casting[0] = 0;
    _interest_time_of_invoking[0] = 0;
    for (int i = 1; i <= _max_level; i++) {
        _interest_cost[i]             = (_cost_base * i) * _fRate_cost;
        _interest_time_of_casting[i]  = (_time_of_casting_base * i) *  _fRate_time_of_casting;
        _interest_time_of_invoking[i] = (_time_of_invoking_base * i) *  _fRate_time_of_invoking;
    }

    //�e���x���ʎ������ԋy�сA�ێ��R�X�g��\�ߐݒ�
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
    effect(_level); //MAGIC_EFFECT_NOTHING������OK�Ǝv��
}

void Magic::rollOpen() {
    _velo_rr = 0.1;
}
void Magic::rollClose() {
    _velo_rr = -0.01;
}

int Magic::chkCastAble(int prm_new_level) {
    if (_pProg->get() == MAGIC_STATE_INVOKING) {
        return MAGIC_CAST_NG_INVOKING_NOW; //�������̂��ߎ��s�s��
    } else if (_pProg->get() == MAGIC_STATE_CASTING) {
        //���̃��x�����r�����ɉr���Ď��s
        if (_level > prm_new_level) {
            return MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN; //�ĉr�����x���_�E��OK
        } else if (_level < prm_new_level) {
            if (_interest_cost[prm_new_level-_level] < _pMP->get()) {
                return MAGIC_CAST_OK_CANCEL_AND_LEVELUP; //�ĉr�����x���A�b�vOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MP������Ȃ����߁A�ĉr�����x���A�b�v�s��
            }
        } else { //_level==prm_new_level
            return MAGIC_CAST_CANCEL; //�r���L�����Z��
        }
    } else {
        //�ҋ@��Ԃ����ʎ������ɉr�����s
        if (_level > prm_new_level) {
            return MAGIC_CAST_OK_LEVELDOWN; //�r�����x���_�E��OK
        } else if (_level < prm_new_level) {
            if (_interest_cost[prm_new_level-_level] < _pMP->get()) {
                return MAGIC_CAST_OK_LEVELUP; //�r�����x���A�b�vOK
            } else {
                return MAGIC_CAST_NG_MP_IS_SHORT; //MP������Ȃ����߁A�ĉr�����x���A�b�v�s��
            }
        } else { //_level==prm_new_level
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
        //�������̂��ߎ��s�s��
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
            //���ݖ��@���x���͒�~����
            _lvinfo[_level]._is_working = false;
            //���x���X�V
            _last_level = _level;
            _level = prm_level;
            _pProg->change(MAGIC_STATE_EFFECT_BEGEIN);
            break;
        }
        case MAGIC_EFFECT_OK_LEVELDOWN: {
            //���ݖ��@���x���͒�~����
            _lvinfo[_level]._is_working = false;
            //���x���X�V
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
            /////////////////////////////////////// �ҋ@
            case MAGIC_STATE_STAND_BY: {
                break;
            }
            /////////////////////////////////////// �r��
            case MAGIC_STATE_CASTING: {
                if (_pProg->isJustChanged()) { //�r���J�n
                    //�r���J�n
                    //�r���I�����Ԃ��v�Z
                    _time_of_next_state = _interest_time_of_casting[_new_level- _level];
                    processCastBegin(_level, _new_level);  //�R�[���o�b�N
                }

                //�r����
                processCastingBehavior(_level, _new_level); //�R�[���o�b�N

                if (_pProg->getFrameInProgress() >= _time_of_next_state) {
                    //�r���I��
                    processCastFinish(_level, _new_level);  //�R�[���o�b�N
                    invoke(_new_level);
                }
                break;
            }
            /////////////////////////////////////// ����
            case MAGIC_STATE_INVOKING: {
                if (_pProg->isJustChanged()) {
                    //�����J�n�A
                    //�����I�����Ԑݒ�
                    _time_of_next_state = _interest_time_of_invoking[_new_level- _level];
                    processInvokeBegin(_level, _new_level);     //�R�[���o�b�N
                }

                //������
                processInvokeingBehavior(_level, _new_level);  //�R�[���o�b�N

                if (_pProg->getFrameInProgress() >= _time_of_next_state) {
                    //�����I��
                    processInvokeFinish(_level, _new_level); //�R�[���o�b�N
                    effect(_new_level);
                }
                break;
            }
            /////////////////////////////////////// ����
            case MAGIC_STATE_EFFECT_BEGEIN: { //�����J�n
                if (_level == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING);
                    break;
                } else if (_last_level < _level) {
                    //���x���A�b�v�������ꍇ
                    //��щz���ꂽ�Ԃ̃��x���͒�~���Č��ʎ����I���c�莞�Ԃ𖞃^����ݒ�
                    for (int lv = _last_level+1; lv <= _level-1; lv++) {
                        _lvinfo[lv]._is_working = false; //��~��
                        _lvinfo[lv]._remaining_time_of_effect = _lvinfo[lv]._time_of_effect; //�������Ԃ𖞃^��
                    }
                    _pMP->dec(_interest_cost[_level-_last_level]); //MP����
                } else if (_last_level > _level) {
                    //���x���_�E���������ꍇ
                    //��щz���ꂽ�Ԃ̃��x���͒�~���Č��ʎ����I���c�莞�Ԃ����Z�b�g��ݒ�
                    for (int lv = _level+1 ; lv <= _last_level-1; lv++) {
                        _lvinfo[lv]._is_working = false; //��~��
                        _lvinfo[lv]._remaining_time_of_effect = 0; //�ʎ����I���c�莞�Ԃ�0
                    }

                    if (_keep_cost_base == 0) { //�ێ��R�X�g��������Ȃ����@�̏ꍇ��
                        if (_lvinfo[_last_level]._time_of_effect > 0) {
                            //��{�R�X�g��60%�Ҍ��B�A���c���ʎ����̊������悸��B�������x���_�E�������ق��������ɂ��邽�߁B
                            _pMP->inc( _cost_base*(_last_level-_level)*0.6*
                                       (1.0*_lvinfo[_last_level]._remaining_time_of_effect / _lvinfo[_last_level]._time_of_effect) );
                        }
                    }
                } else {
                    _TRACE_("_last_level����_level�@");
                }


                if (_level == 0) {
                    _pProg->change(MAGIC_STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                    break;
                }

                //����̐V���ȃ��x����ݒ�
                _lvinfo[_level]._is_working = true;
                if (_last_level < _level) {
                    //���x���A�b�v�������ꍇ
                    _lvinfo[_level]._remaining_time_of_effect = _lvinfo[_level]._time_of_effect; //���񎝑����Ԃ𖞃^��
                } else if (_last_level > _level) {
                    //���x���_�E���������ꍇ�A���񎝑����Ԃ͑O��̑���
                } else {
                    _TRACE_("_last_level����_level�A");
                }
                //���ʎ����J�n
                processEffectBegin(_last_level, _level); //�R�[���o�b�N

                _pProg->set(MAGIC_STATE_EFFECTING);
            }   //��break �����̗���(falldown).
                //��
            case MAGIC_STATE_EFFECTING: { //������
                processEffectingBehavior(_last_level, _level); //�R�[���o�b�N

                _lvinfo[_level]._remaining_time_of_effect --; //���ʎ����c�莞�Ԍ���

                //�ێ��R�X�g��������ꍇ�̏���
                if (_keep_cost_base != 0) {
                    _pMP->inc(-1*_lvinfo[_level]._keep_cost); //�ێ��R�X�g����
                    //MP�͊��H
                    if (_pMP->_val <= 0) {
                        //MP�͊��ɂ�鎝���I����
                        _pMP->_val = 0;
                        for (int lv = 1; lv <= _level; lv++) { //�S���x�����Z�b�g��ݒ�
                             _lvinfo[lv]._is_working = false;           //��~��
                             _lvinfo[lv]._remaining_time_of_effect = 0; //���ʎ����I���c�莞�Ԃ�0
                        }
                        _new_level = 0;
                        _last_level = _level;
                        _level = _new_level;
                        processEffectFinish(_last_level); //�R�[���o�b�N MP�͊��ɂ�閂�@�I��
                        _pProg->change(MAGIC_STATE_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                        break;
                    }
                }

                //�������Ԗ�������
                if (_lvinfo[_level]._remaining_time_of_effect == 0) {
                    effect(_level-1);//���x���_�E��(-1)���s���B
                    if (_level == 0) { //�����x�����P�ŁA���x���_�E��(-1)�ɂ��nothing�ɂȂ����ꍇ
                        processEffectFinish(_last_level); //�R�[���o�b�N
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
