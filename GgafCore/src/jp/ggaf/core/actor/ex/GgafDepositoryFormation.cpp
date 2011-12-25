#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafDepositoryFormation::GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, NULL)
{
    _class_name = "GgafDepositoryFormation";
    _pDepo = NULL;
    _is_called_up = false;
    _is_all_called_up = false;
}
void GgafDepositoryFormation::setFormationAbleActorDepository(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationAbleActorDepository ���Ƀf�|�W�g���͓o�^�ς݂ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo && prm_pDepo->_pSubFirst) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationAbleActorDepository �s���ȃf�|�W�g���ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);

    }

#endif
    _pDepo = prm_pDepo;
    //�c���Ɏ�ʂ𐳂����`���邽�߂Ƀf�|�W�g����ʈ��p��
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));

    if (_pDepo->getSubFirst()) {

    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationAbleActorDepository("<<prm_pDepo->getName()<<") �����f�|�W�g���̃T�u�����݂��܂��� this="<<getName());
    }
}


GgafActor* GgafDepositoryFormation::callUpUntil(int prm_formation_sub_num) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::callUpUntil "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationAbleActorDepository���K�v�ł��B"<<
                                   "this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    _is_called_up = true;
    if (prm_formation_sub_num < _num_sub) {
        _is_all_called_up = true;
        return NULL; //��������ȏ�callUpUntil�s��
    } else {
        GgafMainActor* pActor = _pDepo->dispatch();
        if (pActor) {
            _num_sub++;
            _is_all_called_up = false;
            pActor->_pFormation = this;
            _listFllower.addLast(pActor, false);
            return (GgafActor*)pActor;
        } else {
            _is_all_called_up = true;
            return NULL; //��������ȏ�callUpUntil�s��
        }
    }
}

void GgafDepositoryFormation::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    }

    if (_listFllower.length() == 0) {
        if (_is_all_called_up) {
            //��������ȏ�callUpUntil�s��
            //�����o�[��0�̏ꍇ�͂���Ȃ�
            sayonara(_offset_frames_end);
        } else {
            //�����o�[��0�����A�܂��ǉ����B
            return;
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
void GgafDepositoryFormation::onEnded() {
    GgafFormation::onEnded();
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
