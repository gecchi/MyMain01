#include "stdafx.h"

using namespace GgafCore;

GgafDirector::GgafDirector(GgafScene* prm_pScene_platform) : GgafActor(prm_pScene_platform->getName(), NULL) {
    _obj_class |= Obj_GgafDirector;
    _class_name = "GgafDirector";

    _pScene_platform = prm_pScene_platform;
    setHitAble(false);
}

void GgafDirector::remove() {
    throwGgafCriticalException("[GgafDirector::remove] Error! GgafDirector��remove()�ɂ���č폜�͍s���܂���I");
}

GgafGroupHead* GgafDirector::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pDirector) {
        //_TRACE_("�y�x���zGgafDirector::addSubGroup("<<getName()<<") ���ł�"<<prm_pMainActor->_pDirector->_pScene_platform->getName()<<"�V�[���̊ēɏ������Ă��܂��B���A"<<_pScene_platform->getName()<<"�V�[���̊ēɏ�芷���܂�");
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
    prm_pMainActor->setSceneDirector(this);
    prm_pMainActor->setPlatformScene(_pScene_platform);
    return pSubGroupActor;
}

GgafGroupHead* GgafDirector::addSubGroup(GgafMainActor* prm_pMainActor) {
    //_pStatus->get() ��int �^�����A�Ⴆ���̐��ɂȂ��Ă����Ƃ��Ă��A�r�b�g�̏��ɉe���͂Ȃ�
    //���������� actorkind �փL���X�g���Ă����Ȃ��B
    //TODO:64bitCPU�̏ꍇ����͊�Ȃ��B���Ƃōl����E�E�E�B
    return addSubGroup((actorkind)(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)), prm_pMainActor);
}



GgafGroupHead* GgafDirector::searchSubGroupHead(actorkind prm_kind) {
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
                break;
            } else {
                pSubActor = pSubActor->_pNext;
            }
        } while (true);

        return NULL;
    }
}

void GgafDirector::updateActiveInTheTree() {
    if (getPlatformScene()) {
        if (_pScene_platform->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        throwGgafCriticalException("GgafDirector::updateActiveInTheTree() _is_active_in_the_tree_flg �X�V�ł��܂���B name="<<getName()<<" this="<<this);
    }
}

GgafGod* GgafDirector::askGod() {
    if (_pGod == NULL) {
#ifdef MY_DEBUG
        if (getPlatformScene() == NULL) {
            throwGgafCriticalException("GgafDirector::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getPlatformScene()->askGod();
    }
    return _pGod;
}

GgafDirector::~GgafDirector() {
}
