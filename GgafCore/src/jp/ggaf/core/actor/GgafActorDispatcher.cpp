#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorDispatcher::GgafActorDispatcher(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "GgafActorDispatcher";
    setHitAble(false);
}


void GgafActorDispatcher::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //��ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDispatcher::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pDependenceDispcher = this;
    prm_pSub->inactivateImmediately();
    GgafDummyActor::addSubLast(prm_pSub);
}

//���œK���ā�
//TODO:GgafActorDispatcher�́AGgafGroupActor���p�����āA
//���ʂ�GgafGroupActor�Ƃ��������ɂ���΃A�N�^�[�̐������点���̂ł͂Ȃ���
//�ꍇ�ɂ�肯�肩
