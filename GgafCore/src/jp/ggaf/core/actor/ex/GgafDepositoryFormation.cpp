#include "stdafx.h"
using namespace GgafCore;

GgafDepositoryFormation::GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafDepositoryFormation";
    _pDepo = nullptr;
    _can_call_up = true;
    _was_all_destroyed = false;
}
void GgafDepositoryFormation::setFormationMemberDepository(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepository ���Ƀf�|�W�g���͓o�^�ς݂ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo && prm_pDepo->_pSubFirst) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepository �s���ȃf�|�W�g���ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);

    }
#endif
    _pDepo = prm_pDepo;
    //�c���Ɏ�ʂ𐳂����`���邽�߂Ƀf�|�W�g����ʈ��p��
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
#ifdef MY_DEBUG
    if (_pDepo->getSubFirst()) {

    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepository("<<prm_pDepo->getName()<<") �����f�|�W�g���̃T�u�����݂��܂��� this="<<getName());
    }
#endif
}

void GgafDepositoryFormation::processFinal() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    }

    if (_listFllower.length() == 0) {
        if (_can_call_up) {
            //�����o�[��0�����A�܂��ǉ����B
            return;
        } else {
            //��������ȏ�callUpUntil�s��
            //�����o�[��0�̏ꍇ�͂���Ȃ�
            sayonara(_offset_frames_end);
        }
    } else {
        //�s���|�C���^�̃`�F�b�N
        GgafActor* pFllower = _listFllower.getCurrent();
        int num_follwer = _listFllower.length();
        for (int i = 0; i < num_follwer; i++) {
            if (_can_live_flg && (pFllower->_is_active_flg || pFllower->_will_activate_after_flg)) {
                pFllower = _listFllower.next();
            } else {
                _listFllower.remove();
            }
        }
    }
}

GgafActor* GgafDepositoryFormation::callUpMember(int prm_formation_sub_num) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return nullptr;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::callUpUntil "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationMemberDepository���K�v�ł��B"<<
                                   "this="<<getName()<<" _num_formation_member="<<_num_formation_member);
    }
#endif
    if (prm_formation_sub_num <= _num_formation_member) {
        _can_call_up = false;
        return nullptr; //��������ȏ�callUpUntil�s��
    } else {
        GgafMainActor* pActor = _pDepo->dispatch();
        if (pActor) {
            _num_formation_member++;
            _can_call_up = true;
            pActor->_pFormation = this;
            _listFllower.addLast(pActor, false);
            return (GgafActor*)pActor;
        } else {
            _can_call_up = false;
            return nullptr; //��������ȏ�callUpUntil�s��
        }
    }
}

bool GgafDepositoryFormation::canCallUp() {
    return _can_call_up;
}

void GgafDepositoryFormation::onEnd() {
    GgafFormation::onEnd();
    sayonaraFollwer();
}
void GgafDepositoryFormation::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
    while (_listFllower.length() > 0) {
        GgafActor* pFllower =  _listFllower.getCurrent();
        if (pFllower->_pFormation == this) {
            _TRACE_("GgafDepositoryFormation::sayonaraFollwer _listFllower��"<<_listFllower.getCurrent()->getName()<<"��sayonara���܂��B");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

GgafDepositoryFormation::~GgafDepositoryFormation() {

}
