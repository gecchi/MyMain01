#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFormationActor::GgafDxFormationActor(const char* prm_name, frame prm_offset_frames_end) :
    GgafDxGeometricActor(prm_name, NULL, NULL)
{
    _obj_class |= Obj_GgafFormation;
    _class_name = "GgafDxFormationActor";
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
void GgafDxFormationActor::setFormationAbleActorDepository(GgafActorDepository* prm_pDepo) {
    _pDepo = prm_pDepo;
    GgafMainActor* pActor = _pDepo->getSubFirst();
    if (pActor) {
//        //�ŏ��̂P�ڂ̗v�f����IFormationAble�`�F�b�N
//         IFormationAble* pIFormationAbleActor = dynamic_cast<IFormationAble*>(pActor);
//         if (pIFormationAbleActor) {
//             //OK
//         } else {
//             throwGgafCriticalException("GgafDxFormationActor::setFormationAbleActorDepository("<<prm_pDepo->getName()<<")  IFormationAble*�փN���X�L���X�g���s�B"<<
//                                        "_pDepo->getSubFirst()="<<pActor->getName()<<" �̃N���X���� IFormationAble �������܂���Bpublic �p�����ĉ������B this="<<getName()<<" _num_sub="<<_num_sub);
//         }

    } else {
        throwGgafCriticalException("GgafDxFormationActor::setFormationAbleActorDepository("<<prm_pDepo->getName()<<") �����f�|�W�g���̃T�u�����݂��܂��� this="<<getName());
    }
}

void GgafDxFormationActor::addSubLast(GgafActor* prm_pSub) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        throwGgafCriticalException("GgafDxFormationActor::addSubLast("<<prm_pSub->getName()<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�T�u�ɒǉ����邱�Ƃ͂��������ł��傤�Bthis="<<getName());
    }
    if (_pDepo) {
        _TRACE_("���x���� GgafDxFormationActor::addSubLast("<<prm_pSub->getName()<<") Depository�w�胂�[�h���� addSubLast ����ƑS�Ŕ���͏o���܂���B�Ӑ}�I�ł����HcallUp()�͕s�v�ł����H "<<
                "this="<<getName()<<" _num_sub="<<_num_sub);
    }
    if (_pSubFirst == NULL) {
        //��ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        //�����ʂ��`�F�b�N
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafDxFormationActor::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��Bthis="<<getName()<<"("<<this<<") \n"<<
                                       "�z��kind="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" _pSubFirst="<<_pSubFirst->getName()<<" \n"<<
                                       "����kind="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<" prm_pSub="<<prm_pSub->getName()<<"("<<prm_pSub<<")");
        }
    }
    if (prm_pSub->_obj_class & Obj_GgafDxGeometricActor) {
        _num_sub++;
        ((GgafDxGeometricActor*)prm_pSub)->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
        _listFllower.addLast((GgafDxGeometricActor*)prm_pSub, false); //�t�H�[���[�V���������o�[�Ƃ��ē����ێ�
    } else {
        _TRACE_("���x���� GgafDxFormationActor::addSubLast("<<prm_pSub->getName()<<") Obj_GgafDxGeometricActor �ȊO�̃A�N�^�[���ǉ�����܂��BGgafDxFormationActor�g�p�Ӑ}�͐������ł����H�B"<<
                "this="<<getName()<<" _num_sub="<<_num_sub);
    }
    GgafDxGeometricActor::addSubLast(prm_pSub);
}

GgafDxGeometricActor* GgafDxFormationActor::callUp() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDxFormationActor::callUp "<<getName()<<"�́ADepository���w�肳��Ă܂���BsetFormationAbleActorDepository���K�v�ł��B"<<
                                   "this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    GgafMainActor* pActor = _pDepo->dispatch();
    if (pActor) {
        if (pActor->_obj_class & Obj_GgafDxGeometricActor) {
            //OK
        } else {
            throwGgafCriticalException("GgafDxFormationActor::callUp() Obj_GgafDxGeometricActor �ȊO�̃A�N�^�[�����o����܂����B"<<
                                       "this="<<getName()<<" pActor="<<pActor->getName()<<" _num_sub="<<_num_sub);
        }
        _num_sub++;
//        IFormationAble* p = dynamic_cast<IFormationAble*>(pActor);
//        if (p == NULL) {
//            throwGgafCriticalException("GgafDxFormationActor::callUp() IFormationAble*�փN���X�L���X�g���s�BpActor="<<pActor->getName()<<" �̃N���X���� IFormationAble �������܂���Bpublic �p�����ĉ������B"<<
//                                       "this="<<getName()<<" _num_sub="<<_num_sub);
//        }
//        p->_pFormation = this;
        ((GgafDxGeometricActor*)pActor)->_pFormation = this;
        _listFllower.addLast((GgafDxGeometricActor*)pActor, false);
    }
    _is_called_up = true;
    return (GgafDxGeometricActor*)pActor;
}

void GgafDxFormationActor::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //�I����҂̂�
    } else {
        if (_pDepo) {
            if (_is_called_up && _num_sub == 0) { //�f�|�W�g�����[�h���A�����Ȃ�؂��Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I��
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
            //�ߋ��ɂP�x�ł��ǉ�������A�����o�[��0�̏ꍇ�͂���Ȃ�
            sayonara(_offset_frames_end);
        } else {
            //�����o�[��0�����A�ߋ��ɂP�x���ǉ����Ă��Ȃ��B�܂�A�������゠����B
            return;
        }
    } else {
        //�s���|�C���^�̃`�F�b�N
        GgafDxGeometricActor* pFllower = _listFllower.getCurrent();
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
void GgafDxFormationActor::onGarbaged() {
    GgafDxGeometricActor::onGarbaged();
    sayonaraFollwer();
}

void GgafDxFormationActor::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
#ifdef MY_DEBUG
    if (_pDepo) {
        _TRACE_("GgafDxFormationActor::sayonaraFollwer �������c�����܂܁AGgafDxFormationActor �̕�����ɏ�����Ă��܂��BwasInactiveFollower() �R�[���R��͂���܂��񂩁H "<<
                "this="<<getName()<<" _num_sub="<<_num_sub<<" _listFllower.length()="<<_listFllower.length());
    }
#endif
    while (_listFllower.length() > 0) {

//        IFormationAble* p = dynamic_cast<IFormationAble*>(_listFllower.getCurrent());
//        if (p == NULL) {
//            throwGgafCriticalException("GgafDxFormationActor::sayonaraFollwer IFormationAble*�փN���X�L���X�g���s�B_listFllower.getCurrent()="<<_listFllower.getCurrent()->getName()<<" �̃N���X���� IFormationAble �������܂���Bpublic �p�����ĉ������B this="<<getName()<<" _num_sub="<<_num_sub);
//        }
//        if (p->_pFormation == this) {
//            _TRACE_("GgafDxFormationActor::sayonaraFollwer _listFllower��"<<_listFllower.getCurrent()->getName()<<"��sayonara���܂��B");
//            _listFllower.getCurrent()->sayonara();
//        }

        GgafDxGeometricActor* pFllower =  _listFllower.getCurrent();
        if (pFllower->_pFormation == this) {
            _TRACE_("GgafDxFormationActor::sayonaraFollwer _listFllower��"<<_listFllower.getCurrent()->getName()<<"��sayonara���܂��B");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

GgafDxFormationActor::~GgafDxFormationActor() {

}
