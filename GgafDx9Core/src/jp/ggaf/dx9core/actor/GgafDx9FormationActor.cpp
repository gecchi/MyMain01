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
    _num_sub = 0;
}


void GgafDx9FormationActor::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));

    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDispatcher::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
	_num_sub++;
    GgafDx9GeometricActor::addSubLast(prm_pSub);
}


void GgafDx9FormationActor::processBehavior() {


}

void GgafDx9FormationActor::processJudgement() {
    if (getSubFirst() == NULL) {
        inactivate();
        sayonara(_frame_offset_end);
    }
}


void GgafDx9FormationActor::wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor) {
    _num_sub--;
    if (_num_sub == 0) {
        wasDestroyedFormation(prm_pActor);
    }
}



GgafDx9FormationActor::~GgafDx9FormationActor() {
}
