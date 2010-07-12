#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9FormationActor::GgafDx9FormationActor(const char* prm_name, DWORD prm_frame_offset_end) :
    GgafDx9GeometricActor(prm_name, NULL)
{
    _actor_class |= Obj_GgafDx9FormationActor;
    _class_name = "FormationsActor";
    _frame_offset_end = prm_frame_offset_end;
    setHitAble(false);
}


void GgafDx9FormationActor::addSubLast(GgafActor* prm_pSub) {

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
    GgafDx9GeometricActor::addSubLast(prm_pSub);
}

GgafDx9FormationActor::~GgafDx9FormationActor() {
}