#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name) : GgafActor(prm_name) {
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    _pGroupActor = NULL;
    _pLordActor = NULL;
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setLordActor(NULL); //�Ǘ��҃A�N�^�[���Z�b�g
    pActor->setScenePlatform(NULL); //�����V�[�����Z�b�g
    return pActor;
}

bool GgafMainActor::isActive() {
    if (GgafActor::isActive() && getPlatformScene() && getPlatformScene()->isActive()) {
        return true;
    } else {
        return false;
    }
}

void GgafMainActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setLordActor(prm_pLordActor);
            } else if (pActor->_obj_class & Obj_GgafGroupActor) {
                ((GgafGroupActor*)(pActor))->setLordActor(prm_pLordActor);
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}

void GgafMainActor::setGroupActor(GgafGroupActor* prm_pGroupActor) {
    _pGroupActor = prm_pGroupActor;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setGroupActor(prm_pGroupActor);
            } else if (pActor->_obj_class & Obj_GgafGroupActor) {
                //�X���[����
                //���ʃc���[��GgafGroupActor������΁A���̃c���[�ɂ͉e�������Ȃ����ƂƂ���
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}
//��setGroupActor�œK���ă�����
//�ȉ��̂悤�ȍ\���̏ꍇ�AGgafGroupActor�͓����ł���͂��B
//TODO:���܂����āAGgafGroupActor(088C6D48)�̔r���͂ł��Ȃ���
//
//   �bGgafGroupActor(088C6EA0)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   �b�bEnemyCirce(088C5E50)[EnemyCirce](-66856,-154236,26350)@13883,1,101,101,0(0)
//   �b�b�bGgafGroupActor(088C6D48)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   �b�b�b�bEnemyVesta(08826070)[EnemyVesta1](-197896,-154236,296217)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C2610)[EnemyVesta2](203010,-154759,157390)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C3150)[EnemyVesta3](64184,-154236,-243517)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C3C90)[EnemyVesta4](-336722,-153712,-104690)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C47D0)[EnemyVesta5](-66384,145763,26578)@13883,1,101,101,0(0)
//   �b�b�b�bEnemyVesta(088C5310)[EnemyVesta6](-67327,-454235,26121)@13883,1,101,101,0(0)
//   �b�b�b����
//   �b�b����
//   �b����


GgafGroupActor* GgafMainActor::getGroupActor() {
    if (_pGroupActor == NULL) {
#ifdef MY_DEBUG
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::getGroupActor �������Ă��Ȃ����߁AGroupActor���Ƃ�܂���I("<<getName()<<")");
        }
#endif
        if (_pParent->_obj_class & Obj_GgafMainActor) {
            _pGroupActor = ((GgafMainActor*)(_pParent))->getGroupActor();
        } else if (_pParent->_obj_class & Obj_GgafGroupActor) {
            return (GgafGroupActor*)_pParent;
        }
    }
    return _pGroupActor;
}


GgafLordActor* GgafMainActor::getLordActor() {
    if (_pLordActor == NULL) {
        if (_pParent == NULL) {
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor(); //���̐��̊Ǘ��҃A�N�^�[�ɉ�����
            _TRACE_("�y�x���zGgafMainActor::getLordActor �������Ă��Ȃ����߁ALordActor���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(Universe)��LordActor��Ԃ��܂���");
        } else {
            if (_pParent->_obj_class & Obj_GgafMainActor) {
                _pLordActor = ((GgafMainActor*)(_pParent))->getLordActor();
            } else if (_pParent->_obj_class & Obj_GgafGroupActor) {
                _pLordActor = ((GgafGroupActor*)(_pParent))->getLordActor();
            } else if (_pParent->_obj_class & Obj_GgafLordActor) { //���肦�񂩂�
                return (GgafLordActor*)_pParent;
            } else {
                _pLordActor = NULL;
            }
           _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor(); //���̐��̊Ǘ��҃A�N�^�[�ɉ�����
            _TRACE_("�y�x���zGgafMainActor::getLordActor ���̃c���[�ɂ�LordActor�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(Universe)��LordActor��Ԃ��܂���");
        }
    }
    return _pLordActor;
}



GgafGroupActor* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor) {
        //_TRACE_("�y�x���zGgafLordActor::addSubGroup("<<getName()<<") ���ł�"<<prm_pMainActor->_pLordActor->_pScene_Platform->getName()<<"�V�[���̊Ǘ��҂ɏ������Ă��܂��B���A"<<_pScene_Platform->getName()<<"�V�[���̊Ǘ��҂ɏ�芷���܂�");
        prm_pMainActor->extract();
    }
    GgafGroupActor* pSubGroupActor = getSubGroupActor(prm_kind);
    if (pSubGroupActor == NULL) {
        pSubGroupActor = NEW GgafGroupActor(prm_kind);
        addSubLast(pSubGroupActor);
    } else {
       //OK
    }
    pSubGroupActor->addSubLast(prm_pMainActor);
    prm_pMainActor->setGroupActor(pSubGroupActor);
    prm_pMainActor->setLordActor(getLordActor()); //�Ǘ��҃A�N�^�[���Z�b�g
    prm_pMainActor->setScenePlatform(getPlatformScene()); //�����V�[�����Z�b�g
    return pSubGroupActor;
}

GgafGroupActor* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}


GgafGroupActor* GgafMainActor::getSubGroupActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupActor* pSubGroupActor_ret = NULL;
        do {
            if (pSubActor->_obj_class & Obj_GgafGroupActor) {
                pSubGroupActor_ret = (GgafGroupActor*)pSubActor;
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
    return getGroupActor()->_kind;
}



GgafMainActor::~GgafMainActor() {
}
