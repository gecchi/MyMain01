#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorDispatcherDispatcher::GgafActorDispatcherDispatcher(const char* prm_name) : GgafActorDispatcher(prm_name) {
    _class_name = "GgafActorDispatcherDispatcher";
    setHitAble(false);
}


void GgafActorDispatcherDispatcher::addSubLast(GgafActor* prm_pSub) {
    if (prm_pSub->_obj_class & Obj_GgafActorDispatcher) {
        //OK
	} else {
		throwGgafCriticalException("GgafActorDispatcherDispatcher::addSubLast ���� prm_pSub("<<prm_pSub->getName()<<") �� �f�B�X�p�b�`���[�łȂ���΂����܂���");
    }
    if (_pSubFirst == NULL) {
        //�ŏ��̃f�B�X�p�b�`���[�o�^
        if (prm_pSub->_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDispatcherDispatcher::addSubLast ���� prm_pSub("<<prm_pSub->getName()<<") �̃f�B�X�p�b�`���[�ɓo�^�����o�[�����Ȃ����߁A��ʂ������p���܂���");
        }
        //�f�B�X�p�b�`���[�̎�ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDispatcherDispatcher::addSubLast �قȂ��ʂ̃f�B�X�p�b�`���[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pDependenceDispcher = this;
//    prm_pSub->inactivateImmediately();
    GgafDummyActor::addSubLast(prm_pSub);
}
