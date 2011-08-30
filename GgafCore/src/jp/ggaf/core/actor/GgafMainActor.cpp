#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name, GgafStatus* prm_pStat) :
        GgafActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    _pGroupHead = NULL;
    _pDirector = NULL;
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setMyDirector(NULL); //�ēA�N�^�[���Z�b�g
    pActor->setScenePlatform(NULL); //�����V�[�����Z�b�g
    return pActor;
}

//bool GgafMainActor::isActive() {
//    if (GgafActor::isActive() && getPlatformScene() && getPlatformScene()->isActive()) {
//        return true;
//    } else {
//        return false;
//    }
//}

void GgafMainActor::setMyDirector(GgafDirector* prm_pDirector) {
    _pDirector = prm_pDirector;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setMyDirector(prm_pDirector);
            } else if (pActor->_obj_class & Obj_GgafGroupHead) {
                ((GgafGroupHead*)(pActor))->setMyDirector(prm_pDirector);
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}

void GgafMainActor::setGroupHead(GgafGroupHead* prm_pGroupHead) {
    _pGroupHead = prm_pGroupHead;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setGroupHead(prm_pGroupHead);
            } else if (pActor->_obj_class & Obj_GgafGroupHead) {
                //�X���[����
                //���ʃc���[��GgafGroupHead������΁A���̃c���[�ɂ͉e�������Ȃ����ƂƂ���
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}
//��setGroupHead�œK���ă�����
//�ȉ��̂悤�ȍ\���̏ꍇ�AGgafGroupHead�͓����ł���͂��B
//TODO:���܂����āAGgafGroupHead(088C6D48)�̔r���͂ł��Ȃ���
//
//   �bGgafGroupHead(088C6EA0)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   �b�bEnemyCirce(088C5E50)[EnemyCirce](-66856,-154236,26350)@13883,1,101,101,0(0)
//   �b�b�bGgafGroupHead(088C6D48)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   �b�b�b�bEnemyVesta(08826070)[EnemyVesta1](-197896,-154236,296217)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C2610)[EnemyVesta2](203010,-154759,157390)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C3150)[EnemyVesta3](64184,-154236,-243517)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C3C90)[EnemyVesta4](-336722,-153712,-104690)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C47D0)[EnemyVesta5](-66384,145763,26578)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C5310)[EnemyVesta6](-67327,-454235,26121)@13883,1,101,101,0(0)
//   �b�b�b����
//   �b�b����
//   �b����


GgafGroupHead* GgafMainActor::getMyGroupHead() {
    if (_pGroupHead == NULL) {
#ifdef MY_DEBUG
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::getGroupActor �������Ă��Ȃ����߁AGroupActor���Ƃ�܂���I("<<getName()<<")");
        }
#endif
        if (_pParent->_obj_class & Obj_GgafMainActor) {
            _pGroupHead = ((GgafMainActor*)(_pParent))->getMyGroupHead();
        } else if (_pParent->_obj_class & Obj_GgafGroupHead) {
            return (GgafGroupHead*)_pParent;
        }
    }
    return _pGroupHead;
}


GgafDirector* GgafMainActor::getDirector() {
    if (_pDirector == NULL) {
        if (_pParent == NULL) {
            _pDirector = GgafGod::_pGod->_pUniverse->getDirector(); //���̐��̊ēA�N�^�[�ɉ�����
            _TRACE_("�y�x���zGgafMainActor::getDirector �������Ă��Ȃ����߁ADirector���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(Universe)��Director��Ԃ��܂���");
        } else {
            if (_pParent->_obj_class & Obj_GgafMainActor) {
                _pDirector = ((GgafMainActor*)(_pParent))->getDirector();
            } else if (_pParent->_obj_class & Obj_GgafGroupHead) {
                _pDirector = ((GgafGroupHead*)(_pParent))->getDirector();
            } else if (_pParent->_obj_class & Obj_GgafDirector) { //���肦�񂩂�
                return (GgafDirector*)_pParent;
            } else {
                _pDirector = NULL;
            }
           _pDirector = GgafGod::_pGod->_pUniverse->getDirector(); //���̐��̊ēA�N�^�[�ɉ�����
            _TRACE_("�y�x���zGgafMainActor::getDirector ���̃c���[�ɂ�Director�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(Universe)��Director��Ԃ��܂���");
        }
    }
    return _pDirector;
}



GgafGroupHead* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pDirector) {
        //_TRACE_("�y�x���zGgafDirector::addSubGroup("<<getName()<<") ���ł�"<<prm_pMainActor->_pDirector->_pScene_Platform->getName()<<"�V�[���̊ēɏ������Ă��܂��B���A"<<_pScene_Platform->getName()<<"�V�[���̊ēɏ�芷���܂�");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind);
    if (pSubGroupActor == NULL) {
        pSubGroupActor = NEW GgafGroupHead(prm_kind);
        addSubLast(pSubGroupActor);
    } else {
       //OK
    }
    pSubGroupActor->addSubLast(prm_pMainActor);
    prm_pMainActor->setGroupHead(pSubGroupActor);
    prm_pMainActor->setMyDirector(getDirector()); //�ēA�N�^�[���Z�b�g
    prm_pMainActor->setScenePlatform(getPlatformScene()); //�����V�[�����Z�b�g
    return pSubGroupActor;
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}


GgafGroupHead* GgafMainActor::searchSubGroupHead(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupActor_ret = NULL;
        do {
            if (pSubActor->_obj_class & Obj_GgafGroupHead) {
                pSubGroupActor_ret = (GgafGroupHead*)pSubActor;
                if (pSubGroupActor_ret->_kind == prm_kind) {
                    return pSubGroupActor_ret;
                }
            }
            if (pSubActor->_is_last_flg) {
                return NULL;
            } else {
                pSubActor = pSubActor->_pNext;
            }
        } while (true);
    }
}


GgafGod* GgafMainActor::askGod() {
    if (_pGod == NULL) {
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

actorkind GgafMainActor::getKind() {
    return getMyGroupHead()->_kind;
}



GgafMainActor::~GgafMainActor() {
}
