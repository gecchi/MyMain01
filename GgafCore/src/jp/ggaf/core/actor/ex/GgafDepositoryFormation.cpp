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
}
void GgafDepositoryFormation::setFormationMember(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("���Ƀf�|�W�g���͓o�^�ς�("<<_pDepo->getName()<<")�ł��B\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
    if (prm_pDepo) {
        //OK
    } else {
        throwGgafCriticalException("�s���ȃf�|�W�g���ł��B\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
    if (prm_pDepo->getChildFirst()) {
        //OK
    } else {
        throwGgafCriticalException("�����f�|�W�g���̎q�����݂��܂���B\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
    if (prm_pDepo->getMySceneMediator()) {
        //OK
    } else {
        throwGgafCriticalException("�����f�|�W�g�����V�[���ɖ�����(SceneMediator�������Ȃ�)�ł��B\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
#endif
    _pDepo = prm_pDepo;
    //�c���Ɏ�ʂ𐳂����`���邽�߂Ƀf�|�W�g����ʈ��p��
    getStatus()->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->getDefaultKind());
    //TODO:���K�v���������낤���ATree����Ȃ��̂ŕs�v�ł͂Ȃ����H�H2015/02/20
}

void GgafDepositoryFormation::processFinal() {
//    _TRACE_("processFinal() "<<getActiveFrame()<<":before----->");
//    for (int i = 0; i < _listFollower.length(); i++) {
//        _TRACE_("processFinal() _listFollower["<<i<<"]="<<_listFollower.getFromFirst(i)->getName()<<"("<<_listFollower.getFromFirst(i)<<")");
//    }
//    _TRACE_("processFinal() "<<getActiveFrame()<<"<-----");




    int n = _listFollower.length();
    GgafActor* pFollower;
    for (int i = 0; i < n; i++) {
        pFollower = _listFollower.getCurrent();
        if (pFollower->isActive() || pFollower->willActivateAfter()) {
            _listFollower.next();
        } else {
            //�ґ������o�[����O��
            _listFollower.remove()->_pFormation = nullptr; //remove() ���A�V���ȃJ�����g�v�f�� next �̗v�f�ɂȂ�B
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










//    if (_listFollower.length() > 0) {
//        //�ґ������o�[�󋵃`�F�b�N
//        GgafActor* pFollower;
//        for (int i = 0; i < _listFollower.length(); i++) { //���[�v�� _listFollower.remove() ����̂ŁA���[�J���ɗ��Ƃ��Ȃ�
//            pFollower = _listFollower.getCurrent();
//            if (_can_live_flg) {
//                if (pFollower->_is_active_flg) {
//                    _listFollower.next();
//                } else if (pFollower->willActivateAfter()) {
//                    //�����Ɋ����\��ł��c��
//                    _listFollower.next();
//                } else {
//                    //�ґ������o�[����O��
////                    _TRACE_("i="<<i<<" �������o�[��"<<_listFollower.length()<<" �����Ă��ꂩ��"<<_listFollower.getCurrent()->getName()<<"�������o�[����O���܂��I(X)");
//                    _listFollower.getCurrent()->_pFormation = nullptr;
//                    _listFollower.remove(); //remove() ���A�V���ȃJ�����g�v�f�� next �̗v�f�ɂȂ�B
//                }
//            } else {
//                //�ґ������o�[����O��
////                 _TRACE_("i="<<i<<" �������o�[��"<<_listFollower.length()<<" ������"<<_listFollower.getCurrent()->getName()<<"�������o�[����O���܂��I(A)");
//                _listFollower.getCurrent()->_pFormation = nullptr;
//                _listFollower.remove();//remove() ���A�V���ȃJ�����g�v�f�� next �̗v�f�ɂȂ�B
//            }
//        }
//    }

//    if (_listFollower.length() == 0) {
//        if (_can_call_up == false && _was_all_sayonara == false) {
//            //�ґ������o�[��0���A
//            //��������ȏ� callUp �s�ŁAonSayonaraAll()�R�[���o�b�N�����s�̏ꍇ
//            onSayonaraAll(); //�R�[���o�b�N
//            sayonara(_offset_frames_end); //�ґ����̂�����Ȃ�B
//            _was_all_sayonara = true;
//        }
//    }
}

GgafActor* GgafDepositoryFormation::callUpMember(int prm_formation_child_num) {
    if (_can_call_up == false || wasDeclaredEnd() || willInactivateAfter()) {
        //�I����҂̂�
        return nullptr;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException(getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationMember���K�v�ł��B"
                                   "this="<<getName()<<" _num_formation_member="<<_num_formation_member);
    }
#endif

    if (prm_formation_child_num <= _num_formation_member) {
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

bool GgafDepositoryFormation::canCallUp() const {
    return _can_call_up;
}

void GgafDepositoryFormation::onEnd() {
    GgafFormation::onEnd();
    sayonaraFollwer();
}

void GgafDepositoryFormation::sayonaraFollwer() {
    int n = _listFollower.length();
    GgafActor* pFollower;
    for (int i = 0; i < n; i++) {
#ifdef MY_DEBUG
        if (_listFollower.getCurrent()->_pFormation != this) {
            throwGgafCriticalException("_listFollower�Ɏ��g��formation�Ǘ��ł͂Ȃ������o�[�����܂����B�Ȃ񂩉��Ă܂��B\n"
                                       " this="<<NODE_INFO<<" \n"
                                       " _listFollower.getCurrent()="<<(_listFollower.getCurrent()->getName())<<"("<<(_listFollower.getCurrent())<<") \n"
                                       " _listFollower.getCurrent()->_pFormation="<<(_listFollower.getCurrent()->_pFormation->getName())<<"("<<(_listFollower.getCurrent()->_pFormation)<<") ");

        }
#endif
        pFollower = _listFollower.remove();
        pFollower->_pFormation = nullptr;
        pFollower->sayonara();

    }


//    if (_listFollower.length() == 0) {
//        return;
//    }
//    while (_listFollower.length() > 0) {
//        if (_listFollower.getCurrent()->_pFormation == this) {
//            _listFollower.getCurrent()->sayonara();
//            _listFollower.getCurrent()->_pFormation = nullptr;
//        } else {
//            throwGgafCriticalException("_listFollower�Ɏ��g��formation�Ǘ��ł͂Ȃ������o�[�����܂����I\n"
//                                       " this="<<NODE_INFO<<" \n"
//                                       " _listFollower.getCurrent()="<<(_listFollower.getCurrent()->getName())<<"("<<(_listFollower.getCurrent())<<") \n"
//                                       " _listFollower.getCurrent()->_pFormation="<<(_listFollower.getCurrent()->_pFormation->getName())<<"("<<(_listFollower.getCurrent()->_pFormation)<<") ");
//        }
//        _listFollower.remove();
//    }

}

GgafDepositoryFormation::~GgafDepositoryFormation() {

}
