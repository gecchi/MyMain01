#include "jp/ggaf/dx/actor/ex/FkFormation.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"


using namespace GgafDx;

FkFormation::FkFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafCore::Formation(prm_name, prm_offset_frames_end)
{
    _class_name = "FkFormation";
    _pIte = nullptr;
    _can_called_up = true;
}
void FkFormation::registerFormationFkBase(GeometricActor* prm_pFkBase) {
    if (_pChildFirst == nullptr) { //�ŏ��̂P��
        //�{�t�H�[���[�V�����I�u�W�F�N�g���̂̎�ʂ��m��
//        getStatus()->set(STAT_DEFAULT_ACTOR_KIND,
//                      prm_pFkBase->getCheckerKind());
        setDefaultKind(prm_pFkBase->getCheckerKind());
    } else {
#ifdef MY_DEBUG
        if (getCheckerKind() != prm_pFkBase->getCheckerKind()) {
            throwCriticalException("�قȂ��ʂ�FK�x�[�X�A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"
                                       "�z��="<<getCheckerKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
                                       "����="<<prm_pFkBase->getCheckerKind()<<"["<<prm_pFkBase->getName()<<"]");
        }
#endif
    }
    GgafCore::Formation::appendChild(prm_pFkBase);
}

void FkFormation::appendFormationMember(GeometricActor* prm_pMember,
                                        int prm_x_init_local,
                                        int prm_y_init_local,
                                        int prm_z_init_local,
                                        int prm_rx_init_local,
                                        int prm_ry_init_local,
                                        int prm_rz_init_local) {

#ifdef MY_DEBUG
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //�I����҂̂�
        throwCriticalException(": ���Ɏ��ɂ䂭��߂�Formation�ł��B�q�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
    if (getChildFirst() == nullptr) {
        throwCriticalException(": FK�x�[�X�A�N�^�[�����܂���BaddFormationBase() ���Ă��������Bthis="<<getName());
    }
#endif
    GeometricActor* pFkBase = (GeometricActor*)(getChildFirst());
    _num_formation_member++;
    prm_pMember->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
    pFkBase->appendChildAsFk(prm_pMember,
                              prm_x_init_local,
                              prm_y_init_local,
                              prm_z_init_local,
                              prm_rx_init_local,
                              prm_ry_init_local,
                              prm_rz_init_local);
    prm_pMember->inactivate(); //�t�H�[���[�V�����Ȃ̂�CalledUp��҂���
}

void FkFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || isInactivateScheduled()) {
        //�I����҂̂�
    } else {
        GgafCore::MainActor* pFkBase = (GgafCore::MainActor*)(getChildFirst()); //FK�x�[�X
        if (pFkBase) {
            if (pFkBase->getChildFirst() == nullptr) { //FK�x�[�X�̔z�����Ȃ����
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

void FkFormation::onEnd() {
    GgafCore::Formation::onEnd();
}

GeometricActor* FkFormation::calledUpMember(int prm_formation_child_num) {
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //�I����҂̂�
        return nullptr;
    }
    if (_can_called_up) {
                                 //FkBase      ->Actor
        GgafCore::Actor* pFirstActor = getChildFirst()->getChildFirst(); //���̐擪�A�N�^�[
        if (_pIte) {
            _pIte = _pIte->getNext();
        } else {
            //����
            _pIte = pFirstActor;
            if (!_pIte) {
                //�����o�[���ǉ�����ĂȂ�
                _TRACE_("�y�x���z FkFormation::calledUpMember() �����o�[���ǉ�����Ă܂���B���������̂ł́H�Bthis="<<NODE_INFO);
                _can_called_up = false; //���񂩂� calledUpMember() �s��
                _num_formation_member = 0;
                return nullptr;
            }
        }
        _num_called_up++;
        _pIte->activate();
        if (_pIte->getNext() == pFirstActor) {
            //�������̐擪�A�N�^�[�Ȃ�A����(_pIte)�͍Ō�̈��
            _can_called_up = false;
        }

        if (_pIte->getNext() == pFirstActor) {
            //�Ō�̂P��
            _can_called_up = false; //���񂩂� calledUpMember() �s��
            _num_formation_member = _num_called_up; //destroyedFollower �ґ��S�Ŕ���̈׍Đݒ�
        }
        if (prm_formation_child_num <= _num_called_up) {
            //������ɒB����
            _can_called_up = false; //���񂩂� calledUpMember() �s��
            _num_formation_member = _num_called_up; //destroyedFollower �ґ��S�Ŕ���̈׍Đݒ�
        }
        return (GeometricActor*)_pIte;
    } else {
        return nullptr;
    }
}

FkFormation::~FkFormation() {

}
