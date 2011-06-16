#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9FormationActor::GgafDx9FormationActor(const char* prm_name, frame prm_offset_frames_end) :
    GgafDx9GeometricActor(prm_name, NULL)
{
    _obj_class |= Obj_GgafDx9FormationActor;
    _class_name = "FormationsActor";
    _offset_frames_end = prm_offset_frames_end;
    setHitAble(false);
    _num_sub = 0;
}


void GgafDx9FormationActor::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));

    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorStore::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    _num_sub++;
    GgafDx9GeometricActor::addSubLast(prm_pSub);
}


void GgafDx9FormationActor::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        if (getSubFirst() == NULL) {
            sayonara(_offset_frames_end);
        }
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
