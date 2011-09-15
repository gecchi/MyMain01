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
    _is_called_up = false;
    _was_all_destroyed = false;
}
void FormationActor::setActorDepository(GgafActorDepository* prm_pDepo) {
    _pDepo = prm_pDepo;
}

void FormationActor::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        throwGgafCriticalException("FormationActor::addSubLast("<<prm_pSub->getName()<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
    if (_pDepo) {
        throwGgafCriticalException("FormationActor::addSubLast("<<prm_pSub->getName()<<") Depository�w�胂�[�h���́AaddSubLast�ł͂Ȃ���callUp���ĉ����� this="<<getName());
    }
#endif
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

GgafDx9GeometricActor* FormationActor::callUp() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("FormationActor::callUp "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetActorDepository���K�v�ł��B");
    }
#endif
    GgafMainActor* pActor = _pDepo->dispatch();
    if (pActor) {
        _num_sub++;
    }
    _is_called_up = true;
    return (GgafDx9GeometricActor*)pActor;
}

void FormationActor::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (_pDepo) {
//            _TRACE_("FormationActor::processJudgement() this="<<getName()<<" _is_called_up="<<_is_called_up<<" _num_sub="<<_num_sub<<" _num_inactive="<<_num_inactive);
            if (_is_called_up && _num_sub == 0) { //�f�|�W�g������؂��Ȃ��ꍇ�A�t�H�[���[�V�������g���폜
//                _TRACE_("FormationActor::processJudgement()  this="<<getName()<<" sayonara("<<_offset_frames_end<<");");
                sayonara(_offset_frames_end);
            }
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
        _was_all_destroyed = true;
        wasDestroyedFormation(prm_pActor);
    }
}

void FormationActor::wasInactiveFollower() {
//    _TRACE_("FormationActor::wasInactiveFollower() this="<<getName()<<" _num_sub="<<_num_sub<<" _num_inactive="<<_num_inactive);
    if (_pDepo) {
        _num_inactive++;
        if (_num_sub == _num_inactive) {
            sayonara(_offset_frames_end);
        }
//        _TRACE_("FormationActor::wasInactiveFollower() this="<<getName()<<" _num_sub="<<_num_sub<<" _num_inactive++ _num_inactive="<<_num_inactive);
    }
}

FormationActor::~FormationActor() {
}
