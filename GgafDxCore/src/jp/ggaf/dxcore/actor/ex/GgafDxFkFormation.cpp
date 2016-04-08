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
void GgafDxFkFormation::registerFormationFkBase(GgafDxGeometricActor* prm_pFkBase) {
    if (_pSubFirst == nullptr) { //�ŏ��̂P��
        //�{�t�H�[���[�V�����I�u�W�F�N�g���̂̎�ʂ��m��
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND,
                      prm_pFkBase->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pFkBase->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("�قȂ��ʂ�FK�x�[�X�A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pFkBase->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pFkBase->getName()<<"]");
        }
#endif
    }
    GgafFormation::addSubLast(prm_pFkBase);
}

void GgafDxFkFormation::addFormationMember(GgafDxGeometricActor* prm_pMember,
                                           int prm_x_init_local,
                                           int prm_y_init_local,
                                           int prm_z_init_local,
                                           int prm_rx_init_local,
                                           int prm_ry_init_local,
                                           int prm_rz_init_local) {

#ifdef MY_DEBUG
    if (wasDeclaredEnd() || willInactivateAfter()) {
        //�I����҂̂�
        throwGgafCriticalException(": "<<
                                   "���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
    if (getSubFirst() == nullptr) {
        throwGgafCriticalException(": "<<
                                   "FK�x�[�X�A�N�^�[�����܂���BaddFormationBase() ���Ă��������Bthis="<<getName());
    }
#endif
    GgafDxGeometricActor* pFkBase = (GgafDxGeometricActor*)(getSubFirst());
    ++_num_formation_member;
    prm_pMember->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
    pFkBase->addSubGroupAsFk(prm_pMember,
                             prm_x_init_local,
                             prm_y_init_local,
                             prm_z_init_local,
                             prm_rx_init_local,
                             prm_ry_init_local,
                             prm_rz_init_local);
    prm_pMember->inactivate(); //�t�H�[���[�V�����Ȃ̂�CallUp��҂���
}

void GgafDxFkFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || willInactivateAfter()) {
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
    if (wasDeclaredEnd() || willInactivateAfter()) {
        //�I����҂̂�
        return nullptr;
    }
    if (_can_call_up) {
                                 //FkBase     -> GroupHead   ->Actor
        GgafActor* pFirstActor = getSubFirst()->getSubFirst()->getSubFirst(); //���̐擪�A�N�^�[
        if (_pIte) {
            _pIte = _pIte->getNext();
            if (_pIte == pFirstActor) { //�P������
                _can_call_up = false;
                return nullptr;
            }
        } else {
            //����
            _pIte = pFirstActor;
        }
        _pIte->activate();
        if (_pIte->getNext() == pFirstActor) {
            //�������̐擪�A�N�^�[�Ȃ�A����(_pIte)�͍Ō�̈��
            _can_call_up = false;
        }
        return (GgafDxGeometricActor*)_pIte;
    } else {
        return nullptr;
    }
}

GgafDxFkFormation::~GgafDxFkFormation() {

}
