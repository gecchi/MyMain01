#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

FormationActor::FormationActor(const char* prm_name, frame prm_offset_frames_end) :
    GgafDx9GeometricActor(prm_name, NULL, NULL)
{
    _obj_class |= Obj_FormationActor;
    _class_name = "FormationActor";
    _offset_frames_end = prm_offset_frames_end;
    setHitAble(false);
    _num_sub = 0;
}


void FormationActor::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //��ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));

    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("FormationActor::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��Bthis="<<getName()<<"("<<this<<") \n"<<
                                       "�z��kind="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" _pSubFirst="<<_pSubFirst->getName()<<" \n"<<
                                       "����kind="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" prm_pSub="<<prm_pSub->getName()<<"("<<prm_pSub<<")");
        }
    }
    _num_sub++;
    GgafDx9GeometricActor::addSubLast(prm_pSub);
}


void FormationActor::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (getSubFirst() == NULL) {
            sayonara(_offset_frames_end);
        }
    }
}


void FormationActor::wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor) {
    _num_sub--;
    if (_num_sub == 0) {
        wasDestroyedFormation(prm_pActor);
    }
}



FormationActor::~FormationActor() {
}
