#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafDeositoryFormation::GgafDeositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, NULL)
{
    _class_name = "GgafDeositoryFormation";
    _pDepo = NULL;
    _is_called_up = false;
}
void GgafDeositoryFormation::setFormationAbleActorDepository(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDeositoryFormation::setFormationAbleActorDepository ���Ƀf�|�W�g���͓o�^�ς݂ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo && _pDepo->_pSubFirst) {
        //OK
    } else {
        throwGgafCriticalException("GgafDeositoryFormation::setFormationAbleActorDepository �s���ȃf�|�W�g���ł��B\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);

    }

#endif
    _pDepo = prm_pDepo;
    //�f�|�W�g����ʈ��p��
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));


    GgafActor* pActor = _pDepo->getSubFirst();
    if (pActor) {

    } else {
        throwGgafCriticalException("GgafDeositoryFormation::setFormationAbleActorDepository("<<prm_pDepo->getName()<<") �����f�|�W�g���̃T�u�����݂��܂��� this="<<getName());
    }
}


GgafActor* GgafDeositoryFormation::callUp() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDeositoryFormation::callUp "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationAbleActorDepository���K�v�ł��B"<<
                                   "this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    GgafActor* pActor = _pDepo->dispatch();
    if (pActor) {
        _num_sub++;

        pActor->_pFormation = this;
        _listFllower.addLast(pActor, false);
    }
    _is_called_up = true;
    return (GgafActor*)pActor;
}

void GgafDeositoryFormation::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (_is_called_up && _num_sub == 0) { //�f�|�W�g�����[�h���A�����Ȃ�؂��Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I��
            sayonara(_offset_frames_end);
        }
    }

    if (_listFllower.length() == 0) {
        if (_num_sub > 0) {
            //�ߋ��ɂP�x�ł��ǉ�������A�����o�[��0�̏ꍇ�͂���Ȃ�
            sayonara(_offset_frames_end);
        } else {
            //�����o�[��0�����A�ߋ��ɂP�x���ǉ����Ă��Ȃ��B
            //�܂�A��������ł���̂ł��̂܂܁B
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
void GgafDeositoryFormation::onGarbaged() {
    GgafActor::onGarbaged();
    sayonaraFollwer();
}
void GgafDeositoryFormation::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
    while (_listFllower.length() > 0) {
        GgafActor* pFllower =  _listFllower.getCurrent();
        if (pFllower->_pFormation == this) {
            _TRACE_("GgafFormation::sayonaraFollwer _listFllower��"<<_listFllower.getCurrent()->getName()<<"��sayonara���܂��B");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

GgafDeositoryFormation::~GgafDeositoryFormation() {

}
