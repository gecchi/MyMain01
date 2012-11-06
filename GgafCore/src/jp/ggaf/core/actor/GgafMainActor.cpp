#include "stdafx.h"

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
    pActor->setSceneDirector(NULL); //�ēA�N�^�[���Z�b�g
    return pActor;
}

void GgafMainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (getParent()) {
    } else {
        throwGgafCriticalException("GgafMainActor::updateActiveInTheTree() _is_active_in_the_tree_flg �X�V�ł��܂���B name="<<getName()<<" this="<<this);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void GgafMainActor::setSceneDirector(GgafDirector* prm_pDirector) {
    _pDirector = prm_pDirector;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->instanceOf(Obj_GgafMainActor)) {
                ((GgafMainActor*)(pActor))->setSceneDirector(prm_pDirector);
            } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
                ((GgafGroupHead*)(pActor))->setSceneDirector(prm_pDirector);
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
            if (pActor->instanceOf(Obj_GgafMainActor)) {
                ((GgafMainActor*)(pActor))->setGroupHead(prm_pGroupHead);
            } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
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


GgafGroupHead* GgafMainActor::getMyGroupHead() {
    if (_pGroupHead == NULL) {
        if (_pParent == NULL) {
            return NULL;
        } else if (_pParent->instanceOf(Obj_GgafMainActor)) {
            _pGroupHead = ((GgafMainActor*)(_pParent))->getMyGroupHead();
            return _pGroupHead;
        } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
            return (GgafGroupHead*)_pParent;
        } else {
            return NULL;
        }
    } else {
        return _pGroupHead;
    }
}


GgafDirector* GgafMainActor::getSceneDirector() {
    if (_pDirector == NULL) {
        if (_pParent == NULL) {
            _pDirector = GgafGod::_pGod->_pUniverse->getDirector(); //���̐��̊ēA�N�^�[�ɉ�����
            _TRACE_("�y�x���zGgafMainActor::getSceneDirector �������Ă��Ȃ����߁ADirector���Ƃ�܂���I("<<getName()<<")�B�����ŉ������ł��̐�(Universe)��Director��Ԃ��܂����B�ŏI�I�ɁA�e�A�N�^�[���V�[���ɏ�������΁A���̎��ɍX�V����Ă��j�Z�ł��B�m�F���ĉ������B");
        } else {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pDirector = ((GgafMainActor*)(_pParent))->getSceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pDirector = ((GgafGroupHead*)(_pParent))->getSceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafDirector)) { //���肦�񂩂�
                return (GgafDirector*)_pParent;
            } else {
                _pDirector = NULL;
            }
           _pDirector = GgafGod::_pGod->_pUniverse->getDirector(); //���̐��̊ēA�N�^�[�ɉ�����
            _TRACE_("�y�x���zGgafMainActor::getSceneDirector ���̃c���[�ɂ�Director�����܂���I("<<getName()<<")�B�����ŉ������ł��̐�(Universe)��Director��Ԃ��܂����B�ŏI�I�ɁA�e�A�N�^�[���V�[���ɏ�������΁A���̎��ɍX�V����Ă��j�Z�ł��B�m�F���ĉ������B");
        }
    }
    return _pDirector;
}


GgafGroupHead* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pDirector) {
        //_TRACE_("�y�x���zGgafDirector::addSubGroup("<<getName()<<") ���ł�"<<prm_pMainActor->_pDirector->_pScene_Platform->getName()<<"�V�[���̊ēɏ������Ă��܂��B���A"<<_pScene_Platform->getName()<<"�V�[���̊ēɏ�芷���܂�");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
    if (pMyGroupHead != NULL && pMyGroupHead->_kind == prm_kind) {
        //���g�̒c����ʂƈ�����ʂ������ꍇ�A
        addSubLast(prm_pMainActor); //�P���ɃT�u�ɒǉ���OK
        prm_pMainActor->setGroupHead(pMyGroupHead);
        prm_pMainActor->setSceneDirector(getSceneDirector()); //�ēA�N�^�[���Z�b�g
        prm_pMainActor->setPlatformScene(getPlatformScene()); //�����V�[�����Z�b�g
        return pMyGroupHead;
    } else {
        //���g�̎�ʂƈႤ�ꍇ
        GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //�T�u�ɓ�����ʒc�������邩�T��
        if (pSubGroupActor == NULL) {
            //�T�u�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬
            pSubGroupActor = NEW GgafGroupHead(prm_kind);
            addSubLast(pSubGroupActor);
        } else {
            //�T�u�ɓ�����ʒc���������ꍇ�A���̒c���̃T�u��
        }
        pSubGroupActor->addSubLast(prm_pMainActor); //�c���̃T�u�ɒǉ�
        prm_pMainActor->setGroupHead(pSubGroupActor);
        prm_pMainActor->setSceneDirector(getSceneDirector()); //�ēA�N�^�[���Z�b�g
        prm_pMainActor->setPlatformScene(getPlatformScene()); //�����V�[�����Z�b�g
        return pSubGroupActor;
    }
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    //_pStatus->get() ��int �^�����A�Ⴆ���̐��ɂȂ��Ă����Ƃ��Ă��A�r�b�g�̏��ɉe���͂Ȃ�
    //���������� actorkind �փL���X�g���Ă����Ȃ��B
    return addSubGroup((actorkind)(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)), prm_pMainActor);
}

GgafGroupHead* GgafMainActor::searchSubGroupHead(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupHead_ret = NULL;
        do {
            if (pSubActor->instanceOf(Obj_GgafGroupHead)) {
                pSubGroupHead_ret = (GgafGroupHead*)pSubActor;
                if (pSubGroupHead_ret->_kind == prm_kind && pSubGroupHead_ret->_will_end_after_flg == false) {
                    return pSubGroupHead_ret;
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
