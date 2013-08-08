#include "stdafx.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"

#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafSceneDirector::GgafSceneDirector(GgafScene* prm_pScene_platform) : GgafActor(prm_pScene_platform->getName(), nullptr) {
    _obj_class |= Obj_GgafSceneDirector;
    _class_name = "GgafSceneDirector";
    _pScene_platform = prm_pScene_platform;
    setHitAble(false);
}

void GgafSceneDirector::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    GgafScene* s = getPlatformScene();
    if (s) {
        s->throwEventUpperTree(prm_no, this); //��������ʂ͋��Ȃ��B�����ŏ����V�[���֓�����
    }
}

void GgafSceneDirector::remove() {
    throwGgafCriticalException("[GgafSceneDirector::remove] Error! GgafSceneDirector��remove()�ɂ���č폜�͍s���܂���I");
}

GgafGroupHead* GgafSceneDirector::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneDirector) {
        //_TRACE_("�y�x���zGgafSceneDirector::addSubGroup("<<getName()<<") ���ł�"<<prm_pMainActor->_pSceneDirector->_pScene_platform->getName()<<"�V�[���̊ēɏ������Ă��܂��B���A"<<_pScene_platform->getName()<<"�V�[���̊ēɏ�芷���܂�");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind);
    if (pSubGroupActor == nullptr) {
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

GgafGroupHead* GgafSceneDirector::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}

GgafGroupHead* GgafSceneDirector::searchSubGroupHead(actorkind prm_kind) {
    if (_pSubFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupHead_ret = nullptr;
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

        return nullptr;
    }
}

void GgafSceneDirector::updateActiveInTheTree() {
    if (getPlatformScene()) {
        if (_pScene_platform->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        throwGgafCriticalException("GgafSceneDirector::updateActiveInTheTree() _is_active_in_the_tree_flg �X�V�ł��܂���B name="<<getName()<<" this="<<this);
    }
}

GgafGod* GgafSceneDirector::askGod() {
    if (_pGod == nullptr) {
#ifdef MY_DEBUG
        if (getPlatformScene() == nullptr) {
            throwGgafCriticalException("GgafSceneDirector::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getPlatformScene()->askGod();
    }
    return _pGod;
}

GgafSceneDirector::~GgafSceneDirector() {
}
