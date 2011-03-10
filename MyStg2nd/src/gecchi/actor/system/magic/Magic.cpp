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
    _pMP = NULL; //initialize()�Őݒ肷��B
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

    //��у��x�����ʏ���ݒ�
    _interest_cost[0] = 0;
    _interest_time_of_casting[0] = 0;
    _interest_time_of_invoking[0] = 0;
    for (int i = 1; i <= _max_level; i++) {
        _interest_cost[i]             = (_cost_base * i) * _fRate_cost;
        _interest_time_of_casting[i]  = (_time_of_casting_base * i) *  prm_fRate_time_of_casting;
        _interest_time_of_invoking[i] = (_time_of_invoking_base * i) *  prm_fRate_time_of_invoking;
    }

    //�e���x���ʎ������ԋy�сA�ێ��R�X�g��\�ߐݒ�
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
    _pMP = &(P_MYSHIP_SCENE->_pEnagyBar->_amount); //MP�ɓ�����AmountGraph
}


void Magic::rollOpen() {
    _velo_rr = 0.1;
}
void Magic::rollClose() {
    _velo_rr = -0.02;
}

int Magic::chkExecuteAble(int prm_new_level) {
    if (_pProgress->get() == MAGIC_INVOKING) {
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
void Magic::execute(int prm_new_level) {
    int r = chkExecuteAble(prm_new_level);
    if (r > 0) {
        _new_level = prm_new_level;

        _is_working = true;
        if (r == MAGIC_EXECUTE_OK_LEVELUP) {
            //���x���A�b�v
                        _pProgress->change(MAGIC_STAND_BY);
        } else if (r == MAGIC_EXECUTE_OK_LEVELDOWN) {
            //���x���_�E��
            //TODO:MP����
            //���݂��~��
            _lvinfo[_level]._is_working = false;
            _lvinfo[_level]._remaining_time_of_effect = 0;
            //��щz��
            for (int i = _level-1; i <= prm_new_level+1; i--) {
                _lvinfo[i]._is_working = false; //��~��
                _lvinfo[i]._remaining_time_of_effect = 0;
            }
            //�V�����Ⴂ���x����ݒ�
            _lvinfo[prm_new_level]._is_working = true;
            processOnLevelDown(_level, prm_new_level); //���ʂ̏������s

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
            /////////////////////////////////////// �ҋ@
            case MAGIC_STAND_BY:
                _pProgress->change(MAGIC_CASTING);
                break;

            /////////////////////////////////////// �r��
            case MAGIC_CASTING:
                if (_pProgress->isJustChanged()) {
                    //�r���J�n�A�r���I�����Ԃ��v�Z
                    _time_of_next_state = _interest_time_of_casting[_new_level- _level];
                    processCastBegin(_level, _new_level);
                }
                //�r����
                processCastingBehavior(_level, _new_level);

                if (_pProgress->getActivePartFrameInProgress() >= _time_of_next_state) {
                    //�r���I��
                    processCastFinish(_level, _new_level);
                    _pProgress->change(MAGIC_INVOKING);
                }
                break;

            /////////////////////////////////////// ����
            case MAGIC_INVOKING:
                if (_pProgress->isJustChanged()) {
                    //�����J�n�A
                    //�����I�����Ԑݒ�
                    _time_of_next_state = _interest_time_of_invoking[_new_level- _level];

                    processInvokeBegin(_level, _new_level);
                }
                //������
                processInvokeingBehavior(_level, _new_level);

                if (_pProgress->getActivePartFrameInProgress() >= _time_of_next_state) {
                    //�����I��
                    //���x���ύX�K�p
                    _last_level = _level;
                    _level = _new_level;

                    //�ȑO���~��
                    _lvinfo[_last_level]._is_working = false;
                    //��щz���͎������Ԃ𖞃^����ݒ�
                    for (int i = _last_level+1; i <= _level-1; i++) {
                        _lvinfo[i]._is_working = false; //��~��
                        _lvinfo[i]._remaining_time_of_effect = _lvinfo[i]._time_of_effect; //�������Ԃ𖞃^��
                    }
                    //���񃌃x����ݒ�
                    _lvinfo[_level]._is_working = true;
                    _lvinfo[_level]._remaining_time_of_effect = _lvinfo[_level]._time_of_effect; //�������Ԃ𖞃^��
                    _pMP->dec(_interest_cost[_new_level-_level]); //MP����

                    processInvokeFinish(_last_level, _level);
                    _pProgress->change(MAGIC_EFFECTING);
                }
                break;

            /////////////////////////////////////// ����
            case MAGIC_EFFECTING:
                if (_pProgress->isJustChanged()) {
                    //�����J�n
                    processEffectBegin(_level);
                }
                //������
                _lvinfo[_level]._remaining_time_of_effect --;     //���ʎ����c�莞��
                _pMP->inc(-1*_lvinfo[_level]._keep_cost); //�ێ��R�X�g
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
