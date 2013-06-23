#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxFkFormation.h"
#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFkFormation::GgafDxFkFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafDxFkFormation";
    _pIte = nullptr;
    _can_call_up = true;
}
void GgafDxFkFormation::setFkBase(GgafDxGeometricActor* prm_pFkBase) {
    if (_pSubFirst == nullptr) { //�ŏ��̂P��
        //�{�t�H�[���[�V�����I�u�W�F�N�g���̂̎�ʂ��m��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND,
                      prm_pFkBase->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pFkBase->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafDxFkFormation::addFormationBase �قȂ��ʂ�FK�x�[�X�A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pFkBase->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pFkBase->getName()<<"]");
        }
#endif
    }
    GgafFormation::addSubLast(prm_pFkBase);
}

void GgafDxFkFormation::addFormationMemberAsFk(GgafDxGeometricActor* prm_pMember,
                                               int prm_X_init_local,
                                               int prm_Y_init_local,
                                               int prm_Z_init_local,
                                               int prm_RX_init_local,
                                               int prm_RY_init_local,
                                               int prm_RZ_init_local) {

#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        throwGgafCriticalException("GgafDxFkFormation::addFormationMemberAsFk() : "<<
                                   "���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
    if (getSubFirst() == nullptr) {
        throwGgafCriticalException("GgafDxFkFormation::addFormationMemberAsFk() : "<<
                                   "FK�x�[�X�A�N�^�[�����܂���BaddFormationBase() ���Ă��������Bthis="<<getName());
    }
#endif
    GgafDxGeometricActor* pFkBase = (GgafDxGeometricActor*)(getSubFirst());
    _num_formation_member++;
    prm_pMember->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
    pFkBase->addSubGroupAsFk(prm_pMember,
                             prm_X_init_local,
                             prm_Y_init_local,
                             prm_Z_init_local,
                             prm_RX_init_local,
                             prm_RY_init_local,
                             prm_RZ_init_local);
    prm_pMember->inactivateImmed(); //�t�H�[���[�V�����Ȃ̂�CallUp��҂���
}

void GgafDxFkFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        GgafMainActor* pFkBase = (GgafMainActor*)(getSubFirst()); //FK�x�[�X
        if (pFkBase) {
            if (pFkBase->getSubFirst() == nullptr) { //FK�x�[�X�̔z�����Ȃ����
                pFkBase->sayonara(); //FK�x�[�X���J��
            }
        } else {
            //�z����FK�x�[�X���Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I��
            onSayonaraAll(); //�R�[���o�b�N
            sayonara(_offset_frames_end);
            _was_all_sayonara = true;
        }
    }
}

void GgafDxFkFormation::onEnd() {
    GgafFormation::onEnd();
}

GgafDxGeometricActor* GgafDxFkFormation::callUpMember() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return nullptr;
    }
    if (_can_call_up) {
        if (_pIte) {
            _pIte = _pIte->getNext();
                         //FkBase     -> GroupHead   ->Actor
            if (_pIte == getSubFirst()->getSubFirst()->getSubFirst()) { //�P������
                _can_call_up = false;
                return nullptr;
            }
        } else {
                  //FkBase       -> GroupHead   ->Actor
            _pIte = getSubFirst()->getSubFirst()->getSubFirst();
        }
        _pIte->activate();
        return (GgafDxGeometricActor*)_pIte;
    } else {
        return nullptr;
    }
}

GgafDxFkFormation::~GgafDxFkFormation() {

}
