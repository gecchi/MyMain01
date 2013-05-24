#include "stdafx.h"
#include "jp/ggaf/core/actor/ex/GgafDepositoryFormation.h"

#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"


using namespace GgafCore;

GgafDepositoryFormation::GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafDepositoryFormation";
    _pDepo = nullptr;
    _can_call_up = true;
    _was_all_destroyed = false;
}
void GgafDepositoryFormation::setFormationMember(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember ���Ƀf�|�W�g���͓o�^�ς�("<<_pDepo->getName()<<")�ł��B\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember �s���ȃf�|�W�g���ł��B\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo->getSubFirst()) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember("<<prm_pDepo->getName()<<") �����f�|�W�g���̃T�u�����݂��܂���B\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo->getPlatformScene()) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember("<<prm_pDepo->getName()<<") �����f�|�W�g�����V�[���ɖ������ł��B\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
#endif
    _pDepo = prm_pDepo;
    //�c���Ɏ�ʂ𐳂����`���邽�߂Ƀf�|�W�g����ʈ��p��
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
}

void GgafDepositoryFormation::processFinal() {
//    _TRACE_("processFinal() "<<getActiveFrame()<<":before----->");
//    for (int i = 0; i < _listFollower.length(); i++) {
//        _TRACE_("processFinal() _listFollower["<<i<<"]="<<_listFollower.getFromFirst(i)->getName()<<"("<<_listFollower.getFromFirst(i)<<")");
//    }
//    _TRACE_("processFinal() "<<getActiveFrame()<<"<-----");
    if (_listFollower.length() > 0) {
        //�ґ������o�[�󋵃`�F�b�N
        GgafActor* pFollower;
        for (int i = 0; i < _listFollower.length(); i++) { //
            pFollower = _listFollower.getCurrent();
            if (_can_live_flg) {
                if (pFollower->_is_active_flg) {
                    _listFollower.next();
                } else if (pFollower->_will_activate_after_flg && (pFollower->_frame_of_life <= pFollower->_frame_of_life_when_activation)) {
                    //�����Ɋ����\��ł��c��
                    _listFollower.next();
                } else {
                    //�ґ������o�[����O��
//                    _TRACE_("i="<<i<<" �������o�[��"<<_listFollower.length()<<" �����Ă��ꂩ��"<<_listFollower.getCurrent()->getName()<<"�������o�[����O���܂��I(X)");
                    _listFollower.getCurrent()->_pFormation = nullptr;
                    _listFollower.remove(); //remove() ���A�V���ȃJ�����g�v�f�� next �̗v�f�ɂȂ�B
                }
            } else {
                //�ґ������o�[����O��
//                 _TRACE_("i="<<i<<" �������o�[��"<<_listFollower.length()<<" ������"<<_listFollower.getCurrent()->getName()<<"�������o�[����O���܂��I(A)");
                _listFollower.getCurrent()->_pFormation = nullptr;
                _listFollower.remove();//remove() ���A�V���ȃJ�����g�v�f�� next �̗v�f�ɂȂ�B
            }
        }
    }

    if (_listFollower.length() == 0) {
        if (_can_call_up == false && _was_all_sayonara == false) {
            //�ґ������o�[��0���A
            //��������ȏ� callUp �s�ŁAonSayonaraAll()�R�[���o�b�N�����s�̏ꍇ
            onSayonaraAll(); //�R�[���o�b�N
            sayonara(_offset_frames_end); //�ґ����̂�����Ȃ�B
            _was_all_sayonara = true;
        }
    }
}

GgafActor* GgafDepositoryFormation::callUpMember(int prm_formation_sub_num) {
    if (_can_call_up == false || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return nullptr;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::callUpUntil "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationMember���K�v�ł��B"<<
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
        if (_listFollower.getCurrent()->_pFormation == this) {
            _listFollower.getCurrent()->sayonara();
            _listFollower.getCurrent()->_pFormation = nullptr;
        } else {
            throwGgafCriticalException("GgafDepositoryFormation::sayonaraFollwer() _listFollower�Ɏ��g��formation�Ǘ��ł͂Ȃ������o�[�����܂����I\n"<<
                                       " this="<<getName()<<"("<<this<<") \n"<<
                                       " _listFollower.getCurrent()="<<(_listFollower.getCurrent()->getName())<<"("<<(_listFollower.getCurrent())<<") \n"<<
                                       " _listFollower.getCurrent()->_pFormation="<<(_listFollower.getCurrent()->_pFormation->getName())<<"("<<(_listFollower.getCurrent()->_pFormation)<<") ");
        }
        _listFollower.remove();
    }

}

GgafDepositoryFormation::~GgafDepositoryFormation() {

}
