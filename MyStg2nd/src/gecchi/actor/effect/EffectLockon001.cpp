#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001::EffectLockon001(const char* prm_name, const char* prm_model_id) : DefaultSpriteSetActor(prm_name, prm_model_id) {
    _class_name = "EffectLockon001";
    //_pTarget = NULL;
    inactivateImmediately();
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    chengeEffectTechnique("DestBlendOne"); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnable(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ����ɋ���
    setSpecialDrawDepth(1); //�`�揇�����őO�ʕ`��ɋ����B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽�߁B
    setAlpha(9.9);          //�����������邽�߁A�J�����O��OFF���邽�ߓ����I�u�W�F�N�g�����ɂ���B

    setHitAble(false); //�����蔻�薳��
    _pSeTransmitter->useSe(1);                                                //�g�p���ʉ����錾
    _pSeTransmitter->set(0, "humei10", GgafRepeatSeq::nextVal("CH_humei10")); //���ʉ���`

//    _pEffectLockon001_Release = NEW EffectLockon001_Release("EffectLockon001_R", this);
//    _pEffectLockon001_Release->inactivateImmediately();
//    addSubGroup(_pEffectLockon001_Release);

    //setProgress(EffectLockon001_PROG_NOTHING);
}

void EffectLockon001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 3);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //�A�j������
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
}

void EffectLockon001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(60000); //(6000%)
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E25F��₵��2000(200%)�ɏk��
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //��]
    _pSeTransmitter->play3D(0); //���b�N�I��SE
    setGeometry(_pTarget);
    setProgress(EffectLockon001_PROG_LOCK);
}

void EffectLockon001::processBehavior() {
    if (getProgress() == EffectLockon001_PROG_LOCK) {
        if (getAlpha() < 1.0) {
             addAlpha(0.01);
         }
         if (_pScaler->_method[0] == NOSCALE) {
             //�k��������ABeat
             _pScaler->forceScaleRange(2000, 4000);
             _pScaler->beat(30, 2, 2, -1); //�������[�v
         }
         if (_pTarget) {
             if (_pTarget->isActive() || _pTarget->_will_activate_after_flg) {
                 if (abs(_pTarget->_X-_X) <= 200000 &&
                     abs(_pTarget->_Y-_Y) <= 200000 &&
                     abs(_pTarget->_Z-_Z) <= 200000) {
                     setGeometry(_pTarget);
                     _pMover->setMvVelo(0);
                 } else {
                     _pMover->setMvAng(_pTarget);
                     _pMover->setMvVelo(200000);
                 }
             } else {
                 setProgress(EffectLockon001_PROG_RELEASE);
             }
         } else {
             setProgress(EffectLockon001_PROG_RELEASE);
         }
    }

    if (getProgress() == EffectLockon001_PROG_RELEASE) {
        addAlpha(-0.04);
        if (_pScaler->_method[0] == NOSCALE || getAlpha() <= 0.0) {
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockon001::processJudgement() {

//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockon001::onInactive() {
   // setProgress(EffectLockon001_PROG_NOTHING);
}

void EffectLockon001::lockon(GgafDx9GeometricActor* prm_pTarget) {
    if (prm_pTarget == NULL || _pTarget == prm_pTarget) {
        return;
    }
    _pTarget = prm_pTarget;
    if (getProgress() == EffectLockon001_PROG_LOCK) {
    } else if (getProgress() == EffectLockon001_PROG_RELEASE) {
    }
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
    _pMover->setFaceAngVelo(AXIS_Z, 1000);   //��]
    _pSeTransmitter->play3D(0); //���b�N�I��SE
    setProgress(EffectLockon001_PROG_LOCK);
}


void EffectLockon001::releaseLockon() {
    if (isActive()) {
        if (getProgress() == EffectLockon001_PROG_RELEASE) {
            //��������
        } else if (getProgress() == EffectLockon001_PROG_LOCK) {

        }
    }
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->intoTargetScaleLinerUntil(60000, 50);//�X�P�[�����O
    _pMover->setFaceAngVelo(AXIS_Z, _pMover->_angveloFace[AXIS_Z]*-3); //�����t��]
    setProgress(EffectLockon001_PROG_RELEASE);
    _pTarget = NULL;
}

EffectLockon001::~EffectLockon001() {
}

void EffectLockon001::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"] Target="<<(_pTarget==NULL?"NULL":_pTarget->getName())<<" "<<
                                                                               "@"<<_frame_of_behaving_since_onActive<<
                                                                               "/"<<
                                                                               _frame_of_behaving<<
                                                                               "/"<<
                                                                               _frame_of_life<<
                                                                               ","<<
                                                                               _was_initialize_flg<<
                                                                               ","<<
                                                                               _can_live_flg<<
                                                                               _is_active_flg<<
                                                                               ","<<
                                                                               _will_activate_after_flg<<
                                                                               "("<<_frame_of_life_when_activation<<")"<<
                                                                               _on_change_to_active_flg<<
                                                                               ","<<
                                                                               _will_inactivate_after_flg<<
                                                                               "("<<_frame_of_life_when_inactivation<<")"<<
                                                                               _on_change_to_inactive_flg<<
                                                                               ","<<
                                                                               _will_end_after_flg<<
                                                                               "("<<_frame_of_life_when_end<<")"<<
                                                                               ","<<
                                                                               _progress<<
                                                                               "("<<_progress_nextframe<<")"<<
                                                                               ","<<
                                                                               _was_paused_flg<<
                                                                               _was_paused_flg_in_next_frame<<
                                                                               _will_mv_first_in_next_frame_flg<<
                                                                               _will_mv_last_in_next_frame_flg
                                                                               );

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t�b");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��NULL�ɂ��Ă��܂�");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_("\t\t\t\t\t\t\t\t����");
                break;
            }
        }
    }
}

void EffectLockon001::dump(string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"] Target="<<(_pTarget==NULL?"NULL":_pTarget->getName())<<" "<<
                                                                         "@"<<_frame_of_behaving_since_onActive<<
                                                                         "/"<<
                                                                         _frame_of_behaving<<
                                                                         "/"<<
                                                                         _frame_of_life<<
                                                                         ","<<
                                                                         _was_initialize_flg<<
                                                                         ","<<
                                                                         _can_live_flg<<
                                                                         _is_active_flg<<
                                                                         ","<<
                                                                         _will_activate_after_flg<<
                                                                         "("<<_frame_of_life_when_activation<<")"<<
                                                                         _on_change_to_active_flg<<
                                                                         ","<<
                                                                         _will_inactivate_after_flg<<
                                                                         "("<<_frame_of_life_when_inactivation<<")"<<
                                                                         _on_change_to_inactive_flg<<
                                                                         ","<<
                                                                         _will_end_after_flg<<
                                                                         "("<<_frame_of_life_when_end<<")"<<
                                                                         ","<<
                                                                         _progress<<
                                                                         "("<<_progress_nextframe<<")"<<
                                                                         ","<<
                                                                         _was_paused_flg<<
                                                                         _was_paused_flg_in_next_frame<<
                                                                         _will_mv_first_in_next_frame_flg<<
                                                                         _will_mv_last_in_next_frame_flg
                                                                         );

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump(prm_parent + "�b");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��NULL�ɂ��Ă��܂�");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_(prm_parent+"����");
                break;
            }
        }
    }
}

