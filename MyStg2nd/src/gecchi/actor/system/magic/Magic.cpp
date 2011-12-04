#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    MAGIC_NOTHING = 1,
    MAGIC_STAND_BY   ,
    MAGIC_CASTING    ,
    MAGIC_INVOKING   ,
    MAGIC_EFFECT_BEGEIN,
    MAGIC_EFFECTING  ,
    MAGIC_ABANDONING ,

};

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

    useProgress(MAGIC_ABANDONING);
    _pProg->set(MAGIC_NOTHING);
}


void Magic::rollOpen() {
    _velo_rr = 0.1;
}
void Magic::rollClose() {
    _velo_rr = -0.01;
}

int Magic::chkExecuteAble(int prm_new_level) {
    if (_pProg->get() == MAGIC_INVOKING) {
        //�������̂��ߎ��s�s��
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
void Magic::cast(int prm_new_level) {
    int r = chkExecuteAble(prm_new_level);
    switch (r) {
        case MAGIC_EXECUTE_THE_SAME_LEVEL: {
            break;
        }
        case MAGIC_EXECUTE_NG_MP_IS_SHORT: {
            break;
        }
        case MAGIC_EXECUTE_NG_INVOKING: {
            break;
        }
        case MAGIC_EXECUTE_OK_LEVELUP: {
            _is_working = true;
            _new_level = prm_new_level;
            _pProg->change(MAGIC_CASTING);
            break;
        }
        case MAGIC_EXECUTE_OK_LEVELDOWN: {
            _is_working = true;
            effect(prm_new_level);
            break;
        }
    }
}

void Magic::invoke(int prm_new_level) {
    int r = chkExecuteAble(prm_new_level);
    switch (r) {
        case MAGIC_EXECUTE_THE_SAME_LEVEL: {
            break;
        }
        case MAGIC_EXECUTE_NG_MP_IS_SHORT: {
            break;
        }
        case MAGIC_EXECUTE_NG_INVOKING: {
            break;
        }
        case MAGIC_EXECUTE_OK_LEVELUP: {
            _is_working = true;
            _new_level = prm_new_level;
            _pProg->change(MAGIC_INVOKING);
            break;
        }
        case MAGIC_EXECUTE_OK_LEVELDOWN: {
            _is_working = true;
            effect(prm_new_level);
            break;
        }
    }
}
void Magic::effect(int prm_level) {
    //���ݖ��@���x���͒�~����
    _lvinfo[_level]._is_working = false;
    //���x���X�V
    _last_level = _level;
    _level = prm_level;
    _pProg->change(MAGIC_EFFECT_BEGEIN);
}

void Magic::cancel() {
    _new_level = _level;
    _is_working = false;
    _pProg->change(MAGIC_NOTHING);
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
            case MAGIC_STAND_BY: {
                break;
            }
            /////////////////////////////////////// �r��
            case MAGIC_CASTING: {
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
            case MAGIC_INVOKING: {
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
            case MAGIC_EFFECT_BEGEIN: { //�����J�n
                if (_last_level < _level) {
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
                    for (int lv = _last_level+1; lv <= _level-1; lv++) {
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
                }

                if (_level == 0) {
                    _pProg->change(MAGIC_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                    break;
                }

                //����̐V���ȃ��x����ݒ�
                _lvinfo[_level]._is_working = true;
                _lvinfo[_level]._remaining_time_of_effect = _lvinfo[_level]._time_of_effect; //�������Ԃ𖞃^��
                //���ʎ����J�n
                processEffectBegin(_last_level, _level); //�R�[���o�b�N

                _pProg->set(MAGIC_EFFECTING);
            }   //��break �����̗���(falldown).
                //��
            case MAGIC_EFFECTING: { //������
                processEffectingBehavior(_last_level, _level); //�R�[���o�b�N

                _lvinfo[_level]._remaining_time_of_effect --; //���ʎ����c�莞�Ԍ���

                if (_keep_cost_base != 0) { //�ێ��R�X�g��������ꍇ
                    _pMP->inc(-1*_lvinfo[_level]._keep_cost); //�ێ��R�X�g����
                    if (_pMP->_val <= 0) {//MP�͊�
                        //MP�͊��ɂ�鎝���I����
                        _pMP->_val = 0;
                        //���Z�b�g��ݒ�
                        for (int lv = 1; lv <= _level; lv++) {
                         _lvinfo[lv]._is_working = false; //��~��
                         _lvinfo[lv]._remaining_time_of_effect = 0; //���ʎ����I���c�莞�Ԃ�0
                        }
                        _last_level = _level;
                        _level = 0;
                        _pProg->change(MAGIC_NOTHING); //MP�͊��ɂ�閂�@�I��
                        break;
                    }
                }

                if (_lvinfo[_level]._remaining_time_of_effect <= 0) { //�������Ԗ���
                    _lvinfo[_level]._is_working = false;           //�����@�͒�~����
                    _lvinfo[_level]._remaining_time_of_effect = 0; //���ʎ����I���c�莞�Ԃ�0
                    //���x���_�E��(-1)���s���B
                    if (_level == 1) { //�����x�����P�̏ꍇ
                        _last_level = _level;
                        _level = 0;
                        processEffectFinish(_last_level); //�R�[���o�b�N
                        _pProg->change(MAGIC_NOTHING); //���x���_�E��(0���x���w��)�ɂ�閂�@�I��
                        break;
                    } else {   //�����x����2�ȏ�̏ꍇ
                        _last_level = _level;
                        _level = _new_level;
                        _pProg->change(MAGIC_EFFECT_BEGEIN);      //�������Ԗ������x���_�E��
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
