#include "jp/ggaf/core/actor/GgafSceneDirector.h"

#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafSceneDirector::GgafSceneDirector(GgafScene* prm_pScene_platform) : GgafActor(std::string(std::string(prm_pScene_platform->getName()) + "'s SceneDirector").c_str(), nullptr) {
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
    throwGgafCriticalException("Error! GgafSceneDirector��remove()�ɂ���č폜�͍s���܂���I");
}

GgafGroupHead* GgafSceneDirector::addSubGroup(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneDirector) {
        prm_pMainActor->extract();
    }
    GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //�T�u�ɓ�����ʒc�������邩�T��
    if (pSubGroupActor) {
        //�T�u�ɓ�����ʒc���������ꍇ�A���̒c���̃T�u��
        pSubGroupActor->addSubLast(prm_pMainActor);
        prm_pMainActor->setMyGroupHead(pSubGroupActor);
        prm_pMainActor->setMySceneDirector(this);
        prm_pMainActor->setPlatformScene(_pScene_platform);
        return pSubGroupActor;
    } else {
        //�T�u�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬
        GgafGroupHead* pNewSubGroupActor = NEW GgafGroupHead(prm_kind);
        addSubLast(pNewSubGroupActor);
        pNewSubGroupActor->addSubLast(prm_pMainActor);
        prm_pMainActor->setMyGroupHead(pNewSubGroupActor);
        pNewSubGroupActor->setMySceneDirector(this);
        pNewSubGroupActor->setPlatformScene(_pScene_platform);
        return pNewSubGroupActor;
    }

}

GgafGroupHead* GgafSceneDirector::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}

GgafGroupHead* GgafSceneDirector::searchSubGroupHead(kind_t prm_kind) {
    if (_pSubFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupHead_ret = nullptr;
        do {
            if (pSubActor->instanceOf(Obj_GgafGroupHead)) {
                pSubGroupHead_ret = (GgafGroupHead*)pSubActor;
                if (pSubGroupHead_ret->_kind == prm_kind && pSubGroupHead_ret->_frame_of_life_when_end == 0) {
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
        throwGgafCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���B this="<<NODE_INFO);
    }
}

GgafGod* GgafSceneDirector::askGod() {
    if (_pGod == nullptr) {
#ifdef MY_DEBUG
        if (getPlatformScene() == nullptr) {
            throwGgafCriticalException("�_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getPlatformScene()->askGod();
    }
    return _pGod;
}

GgafSceneDirector::~GgafSceneDirector() {
}
