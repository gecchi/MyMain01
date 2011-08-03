#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorStore::GgafActorStore(const char* prm_name) : GgafDummyActor(prm_name) {
    _obj_class |= Obj_GgafActorStore;
    _class_name = "GgafActorStore";
    setHitAble(false);
}


void GgafActorStore::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //��ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorStore::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pDependenceStore = this;
    prm_pSub->inactivateImmediately(); //�����񊈓���
    GgafDummyActor::addSubLast(prm_pSub);
}

void GgafActorStore::onReset() {
    _TRACE_("GgafActorStore::onReset() ["<<getName()<<"]");
    if (_pSubFirst == NULL) {
        return;
    }
    GgafMainActor* pActor = getSubFirst();
    while (true) {
        pActor->inactivate();
        if (pActor->isLast()) {
            break;
        } else {
            pActor = pActor->getNext();
            continue;
        }
    }
}



//���œK���ā�
//TODO:GgafActorStore�́AGgafGroupHead���p�����āA
//���ʂ�GgafGroupHead�Ƃ��������ɂ���΃A�N�^�[�̐������点���̂ł͂Ȃ���
//�ꍇ�ɂ�肯�肩�A���Ƃōl����B
