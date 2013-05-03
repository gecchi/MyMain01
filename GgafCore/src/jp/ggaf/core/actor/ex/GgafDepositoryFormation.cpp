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
void GgafDepositoryFormation::setFormationMemberDepo(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepo ���Ƀf�|�W�g���͓o�^�ς݂ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo && prm_pDepo->_pSubFirst) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepo �s���ȃf�|�W�g���ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);

    }
#endif
    _pDepo = prm_pDepo;
    //�c���Ɏ�ʂ𐳂����`���邽�߂Ƀf�|�W�g����ʈ��p��
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
#ifdef MY_DEBUG
    if (_pDepo->getSubFirst()) {

    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepo("<<prm_pDepo->getName()<<") �����f�|�W�g���̃T�u�����݂��܂��� this="<<getName());
    }
#endif
}

void GgafDepositoryFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return;
    }

    if (_listFollower.length() == 0) {
        if (_can_call_up) {
            //�ґ������o�[��0�����A�܂� callUp �̍Œ��B
            return;
        } else {
            //�ґ������o�[��0���A
            //��������ȏ� callUp �s�́A
            //�ґ����̂�����Ȃ�
            onSayonaraAll(); //�R�[���o�b�N
            sayonara(_offset_frames_end);
            _was_all_sayonara = true;
        }
    } else {
        //�ґ������o�[�󋵃`�F�b�N
        GgafActor* pFollower = _listFollower.getCurrent();
        for (int i = 0; i < _listFollower.length(); i++) {
            if (_can_live_flg) {
                if (pFollower->_is_active_flg) {
                    pFollower = _listFollower.next();
                } else if (pFollower->_will_activate_after_flg && (pFollower->_frame_of_life <= pFollower->_frame_of_life_when_activation)) {
                    //�����Ɋ����\��ł��c��
                    pFollower = _listFollower.next();
                } else {
                    //�ґ������o�[����O��
//					_TRACE_("�������o�[��"<<_listFollower.length()<<" �����Ă��ꂩ��"<<_listFollower.getCurrent()->getName()<<"�������o�[����O���܂��I(X)");
                    _listFollower.remove(); //remove() ���A�V���ȃJ�����g�v�f�� next �̗v�f�ɂȂ�B
                }
            } else {
                //�ґ������o�[����O��
//                 _TRACE_("�������o�[��"<<_listFollower.length()<<" ������"<<_listFollower.getCurrent()->getName()<<"�������o�[����O���܂��I(A)");
                _listFollower.remove();//remove() ���A�V���ȃJ�����g�v�f�� next �̗v�f�ɂȂ�B
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
        throwGgafCriticalException("GgafDepositoryFormation::callUpUntil "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationMemberDepo���K�v�ł��B"<<
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
            _listFollower.addLast(pActor, false);
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
    if (_listFollower.length() == 0) {
        return;
    }
    while (_listFollower.length() > 0) {
        GgafActor* pFollower =  _listFollower.getCurrent();
        if (pFollower->_pFormation == this) {
            _TRACE_("GgafDepositoryFormation::sayonaraFollwer _listFollower��"<<_listFollower.getCurrent()->getName()<<"��sayonara���܂��B");
            _listFollower.getCurrent()->sayonara();
        }
        _listFollower.remove();
    }

}

GgafDepositoryFormation::~GgafDepositoryFormation() {

}
