#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FormationActor::FormationActor(const char* prm_name, frame prm_offset_frames_end) :
    GgafDxGeometricActor(prm_name, NULL, NULL)
{
    _obj_class |= Obj_FormationActor;
    _class_name = "FormationActor";
    _offset_frames_end = prm_offset_frames_end;
    _num_sub = 0;
    setHitAble(false);
    _is_init = false;
    _pDepo = NULL;
    _num_destory = 0;
//    _num_inactive = 0;
    _is_called_up = false;
    _was_all_destroyed = false;
}
void FormationActor::setFormationAbleActorDepository(GgafActorDepository* prm_pDepo) {
    _pDepo = prm_pDepo;
#ifdef MY_DEBUG
    GgafMainActor* pActor = _pDepo->getSubFirst();
    if (pActor) {
        //�ŏ��̂P�ڂ̗v�f����IFormationAble�`�F�b�N
         IFormationAble* pIFormationAbleActor = dynamic_cast<IFormationAble*>(pActor);
         if (pIFormationAbleActor) {
             //OK
         } else {
             throwGgafCriticalException("FormationActor::setFormationAbleActorDepository("<<prm_pDepo->getName()<<")  IFormationAble*�փN���X�L���X�g���s�B"<<
                                        "_pDepo->getSubFirst()="<<pActor->getName()<<" �̃N���X���� IFormationAble �������܂���Bpublic �p�����ĉ������B this="<<getName()<<" _num_sub="<<_num_sub);
         }

    } else {
        throwGgafCriticalException("FormationActor::setFormationAbleActorDepository("<<prm_pDepo->getName()<<") �����f�|�W�g���̃T�u�����݂��܂��� this="<<getName());
     }
#endif
}

void FormationActor::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        throwGgafCriticalException("FormationActor::addSubLast("<<prm_pSub->getName()<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
    if (_pDepo) {
        _TRACE_("���x���� FormationActor::addSubLast("<<prm_pSub->getName()<<") Depository�w�胂�[�h���� addSubLast ����ƑS�Ŕ���͏o���܂���B�Ӑ}�I�ł����HcallUp()�͕s�v�ł����H "<<
                "this="<<getName()<<" _num_sub="<<_num_sub);
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
    if (prm_pSub->_obj_class & Obj_GgafDxGeometricActor) {
        _num_sub++;
        IFormationAble* p = dynamic_cast<IFormationAble*>(prm_pSub);
#ifdef MY_DEBUG
        if (p == NULL) {
            throwGgafCriticalException("FormationActor::addSubLast IFormationAble*�փN���X�L���X�g���s�Bprm_pSub="<<prm_pSub->getName()<<" �̃N���X���� IFormationAble �������܂���Bpublic �p�����ĉ������B"<<
                                       " this="<<getName()<<" _num_sub="<<_num_sub);
        }
#endif
        p->_pFormation = this;
        _listFllower.addLast((GgafMainActor*)prm_pSub, false);
    } else {
        _TRACE_("���x���� FormationActor::addSubLast("<<prm_pSub->getName()<<") Obj_GgafDxGeometricActor �ȊO�̃A�N�^�[���ǉ�����܂��BFormationActor�g�p�Ӑ}�͐������ł����H�B"<<
                "this="<<getName()<<" _num_sub="<<_num_sub);
    }
    GgafDxGeometricActor::addSubLast(prm_pSub);
}

GgafDxGeometricActor* FormationActor::callUp() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("FormationActor::callUp "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationAbleActorDepository���K�v�ł��B"<<
                                   "this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    GgafMainActor* pActor = _pDepo->dispatch();
    if (pActor) {
#ifdef MY_DEBUG
        if (pActor->_obj_class & Obj_GgafDxGeometricActor) {
            //OK
        } else {
            throwGgafCriticalException("FormationActor::callUp() Obj_GgafDxGeometricActor �ȊO�̃A�N�^�[�����o����܂����B"<<
                                       "this="<<getName()<<" pActor="<<pActor->getName()<<" _num_sub="<<_num_sub);
        }
#endif
        _num_sub++;
        IFormationAble* p = dynamic_cast<IFormationAble*>(pActor);
#ifdef MY_DEBUG
        if (p == NULL) {
            throwGgafCriticalException("FormationActor::callUp() IFormationAble*�փN���X�L���X�g���s�BpActor="<<pActor->getName()<<" �̃N���X���� IFormationAble �������܂���Bpublic �p�����ĉ������B"<<
                                       "this="<<getName()<<" _num_sub="<<_num_sub);
        }
#endif
        p->_pFormation = this;
        _listFllower.addLast(pActor, false);
    }
    _is_called_up = true;
    return (GgafDxGeometricActor*)pActor;
}

void FormationActor::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (_pDepo) {
//            _TRACE_("FormationActor::processJudgement() this="<<getName()<<" _is_called_up="<<_is_called_up<<" _num_sub="<<_num_sub<<" _num_inactive="<<_num_inactive);
            if (_is_called_up && _num_sub == 0) { //�f�|�W�g�����[�h���A�����Ȃ�؂��Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I��
//                _TRACE_("FormationActor::processJudgement()  this="<<getName()<<" sayonara("<<_offset_frames_end<<");");
                sayonara(_offset_frames_end);
            }
        } else {
            if (getSubFirst() == NULL) {          //�z�����Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I��
                sayonara(_offset_frames_end);
            }
        }
    }

    if (_listFllower.length() == 0) {
        if (_num_sub > 0) {
            sayonara(_offset_frames_end);
        } else {
            return;
        }
    } else {
        GgafMainActor* pFllower = _listFllower.getCurrent();
        int num_follwer = _listFllower.length();
        for (int i = 0; i < num_follwer; i++) {
            if (_can_live_flg && (pFllower->_is_active_flg || pFllower->_will_activate_after_flg)) {
                pFllower = _listFllower.next();
            } else {
                _listFllower.remove();
            }
        }
    }


}
void FormationActor::onGarbaged() {
    sayonaraFollwer();
}

void FormationActor::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
#ifdef MY_DEBUG
    if (_pDepo) {
        _TRACE_("FormationActor::sayonaraFollwer �������c�����܂܁AFormationActor �̕�����ɏ�����Ă��܂��BwasInactiveFollower() �R�[���R��͂���܂��񂩁H "<<
                "this="<<getName()<<" _num_sub="<<_num_sub<<" _listFllower.length()="<<_listFllower.length());
    }
#endif
    while (_listFllower.length() > 0) {

        IFormationAble* p = dynamic_cast<IFormationAble*>(_listFllower.getCurrent());
#ifdef MY_DEBUG
        if (p == NULL) {
            throwGgafCriticalException("FormationActor::sayonaraFollwer IFormationAble*�փN���X�L���X�g���s�B_listFllower.getCurrent()="<<_listFllower.getCurrent()->getName()<<" �̃N���X���� IFormationAble �������܂���Bpublic �p�����ĉ������B this="<<getName()<<" _num_sub="<<_num_sub);
        }
#endif
        if (p->_pFormation == this) {
            _TRACE_("FormationActor::sayonaraFollwer _listFllower��"<<_listFllower.getCurrent()->getName()<<"��sayonara���܂��B");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

FormationActor::~FormationActor() {

}
