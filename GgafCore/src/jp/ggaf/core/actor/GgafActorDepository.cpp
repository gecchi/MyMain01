#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorDepository::GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafDummyActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafActorDepository;
    _class_name = "GgafActorDepository";
    setHitAble(false);
}


void GgafActorDepository::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //��ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDepository::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pDependenceDepository = this;
    prm_pSub->inactivateImmediately(); //�����񊈓���
    GgafDummyActor::addSubLast(prm_pSub);
}

void GgafActorDepository::onReset() {
    _TRACE_("GgafActorDepository::onReset() ["<<getName()<<"]");
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
//TODO:GgafActorDepository�́AGgafGroupHead���p�����āA
//���ʂ�GgafGroupHead�Ƃ��������ɂ���΃A�N�^�[�̐������点���̂ł͂Ȃ���
//�ꍇ�ɂ�肯�肩�A���Ƃōl����B
