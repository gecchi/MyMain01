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
    _is_init = false;
    _num_sub = 0;
    _pDepo = NULL;
    _num_destory = 0;
    _num_inactive = 0;
}
void FormationActor::setActorDepository(GgafActorDepository* prm_pDepo) {
    _pDepo = prm_pDepo;
}

void FormationActor::addSubLast(GgafActor* prm_pSub) {
    if (_pDepo) {
        throwGgafCriticalException("FormationActor::addSubLast("<<prm_pSub->getName()<<") Depository�w�胂�[�h���́AaddSubLast�ł͂Ȃ��ā`callUp");
    } else {
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
}

GgafDx9GeometricActor* FormationActor::callUp() {
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("FormationActor::callUp "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetActorDepository���K�v�ł��B");
    }
#endif
    _num_sub++;
    GgafMainActor* pActor = _pDepo->dispatch();
    return (GgafDx9GeometricActor*)pActor;
}

void FormationActor::processJudgement() {
    if (!_pDepo) {
        if (wasDeclaredEnd() || _will_inactivate_after_flg) {
            //�I����҂̂�
        } else {
            if (getSubFirst() == NULL) {
                sayonara(_offset_frames_end);
            }
        }
    }
}


void FormationActor::wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor) {
    _num_destory++;
    if (_num_sub == _num_destory) {
        wasDestroyedFormation(prm_pActor);
    }
}

void FormationActor::wasInactiveFollower(GgafDx9GeometricActor* prm_pActor) {
    if (_pDepo) {
        _num_inactive++;
        if (_num_sub == _num_inactive) {
            sayonara(_offset_frames_end);
        }
    }

}

FormationActor::~FormationActor() {
}
