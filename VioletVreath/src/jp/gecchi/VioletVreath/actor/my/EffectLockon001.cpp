#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockon001::EffectLockon001(const char* prm_name, const char* prm_model_id) :
        DefaultSpriteSetActor(prm_name, prm_model_id, nullptr) {
    _class_name = "EffectLockon001";
    pTarget_ = nullptr;
    inactivateImmed();
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnable(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ����ɋ���
    setSpecialDrawDepth(1); //�`�揇�����őO�ʕ`��ɋ����B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽�߁B
    setAlpha(0.9);          //�����������邽�߁A�J�����O��OFF���邽�ߓ����I�u�W�F�N�g�����ɂ���B

    setHitAble(false); //�����蔻�薳��
    _pSeTx->set(0, "WAVE_LOCKON_001"); //���ʉ���`
    useProgress(LOCKON001_PROG_RELEASE);
}

void EffectLockon001::initialize() {
}


void EffectLockon001::onReset() {
    _pProg->reset(LOCKON001_PROG_RELEASE);
}

void EffectLockon001::onActive() {
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
}

void EffectLockon001::processBehavior() {
}

void EffectLockon001::processJudgement() {
}

void EffectLockon001::onInactive() {
}


EffectLockon001::~EffectLockon001() {
}

//
//DEBUG���[�h�A�v���I�����̃c���[�\�����A
//pTarget_���s���ɂȂ�ꍇ���A�K�v�ȂƂ��ɃR�����g���O���Ďg�p�B
//
//
//void EffectLockon001::dump() {
//    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"] Target="<<(pTarget_==nullptr?"nullptr":pTarget_->getName())<<" "<<
//                                                                               "@"<<frame_of_behaving_since_onActive_<<
//                                                                               "/"<<
//                                                                               frame_of_behaving_<<
//                                                                               "/"<<
//                                                                               frame_of_life_<<
//                                                                               ","<<
//                                                                               was_initialize_flg_<<
//                                                                               ","<<
//                                                                               can_live_flg_<<
//                                                                               is_active_flg_<<
//                                                                               ","<<
//                                                                               _will_activate_after_flg<<
//                                                                               "("<<frame_of_life_when_activation_<<")"<<
//                                                                               on_change_to_active_flg_<<
//                                                                               ","<<
//                                                                               will_inactivate_after_flg_<<
//                                                                               "("<<frame_of_life_when_inactivation_<<")"<<
//                                                                               on_change_to_inactive_flg_<<
//                                                                               ","<<
//                                                                               will_end_after_flg_<<
//                                                                               "("<<(frame_of_life_when_end_==MAX_FRAME ? 0 : frame_of_life_when_end_)<<")"<<
//                                                                               ","<<
//                                                                               _was_paused_flg<<
//                                                                               was_paused_flg_in_next_frame_<<
//                                                                               will_mv_first_in_next_frame_flg_<<
//                                                                               will_mv_last_in_next_frame_flg_
//                                                                               );
//
//    GgafActor* pActor_tmp = pSubFirst_;
//    if (pSubFirst_) {
//        while (true) {
//            pActor_tmp->dump("\t\t\t\t\t\t\t\t�b");
//            if (pActor_tmp->_pNext) {
//                pActor_tmp = pActor_tmp->_pNext;
//            } else {
//                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��nullptr���Ă��܂�");
//                break;
//            }
//            if (pActor_tmp->is_first_flg_) {
//                _TRACE_("\t\t\t\t\t\t\t\t����");
//                break;
//            }
//        }
//    }
//}


//void EffectLockon001::dump(std::string prm_parent) {
//    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"] Target="<<(pTarget_==nullptr?"nullptr":pTarget_->getName())<<" "<<
//                                                                         "@"<<frame_of_behaving_since_onActive_<<
//                                                                         "/"<<
//                                                                         frame_of_behaving_<<
//                                                                         "/"<<
//                                                                         frame_of_life_<<
//                                                                         ","<<
//                                                                         was_initialize_flg_<<
//                                                                         ","<<
//                                                                         can_live_flg_<<
//                                                                         is_active_flg_<<
//                                                                         ","<<
//                                                                         _will_activate_after_flg<<
//                                                                         "("<<frame_of_life_when_activation_<<")"<<
//                                                                         on_change_to_active_flg_<<
//                                                                         ","<<
//                                                                         will_inactivate_after_flg_<<
//                                                                         "("<<frame_of_life_when_inactivation_<<")"<<
//                                                                         on_change_to_inactive_flg_<<
//                                                                         ","<<
//                                                                         will_end_after_flg_<<
//                                                                         "("<<(frame_of_life_when_end_==MAX_FRAME ? 0 : frame_of_life_when_end_)<<")"<<
//                                                                         ","<<
//                                                                         _was_paused_flg<<
//                                                                         was_paused_flg_in_next_frame_<<
//                                                                         will_mv_first_in_next_frame_flg_<<
//                                                                         will_mv_last_in_next_frame_flg_
//                                                                         );
//
//    GgafActor* pActor_tmp = pSubFirst_;
//    if (pSubFirst_) {
//        while (true) {
//            pActor_tmp->dump(prm_parent + "�b");
//            if (pActor_tmp->_pNext) {
//                pActor_tmp = pActor_tmp->_pNext;
//            } else {
//                _TRACE_("�y�x���z"<<_class_name<<"("<<this<<")["<<getName()<<"]��next��nullptr���Ă��܂�");
//                break;
//            }
//            if (pActor_tmp->is_first_flg_) {
//                _TRACE_(prm_parent+"����");
//                break;
//            }
//        }
//    }
//}

