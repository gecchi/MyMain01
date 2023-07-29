#include "jp/ggaf/core/actor/SceneChief.h"

#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/MainActor.h"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

SceneChief::SceneChief(Scene* prm_pScene_platform) : Actor("SceneChief"),
_pScene_platform(nullptr)
{
    _obj_class |= Obj_ggaf_SceneChief;
    _class_name = "SceneChief";
    _pScene_platform = prm_pScene_platform;
    setHitAble(false);
}

void SceneChief::throwEventUpperTree(eventval prm_event_val, void* prm_pSource) {
    Scene* s = getPlatformScene();
    if (s) {
        s->throwEventUpperTree(prm_event_val, this); //��������ʂ͋��Ȃ��B�����ŏ����V�[���֓�����
    }
}

void SceneChief::remove() {
    throwCriticalException("Error! SceneChief��remove()�ɂ���č폜�͍s���܂���I");
}

GroupHead* SceneChief::appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneChief) {
        throwCriticalException("Error! SceneChief::appendGroupChild �����ς݂𖳗����ړ������悤�Ƃ��Ă��܂��B\n"
                " extract() ���s���Ă���o���Ȃ��ł����H prm_pMainActor="<<NODE_INFO_P(prm_pMainActor)<<"/this="<<NODE_INFO);
    }
    GroupHead* pChildGroupActor = searchChildGroupHead(prm_kind); //�q�ɓ�����ʒc�������邩�T��
    if (!pChildGroupActor) {
        //�q�ɓ�����ʒc�������Ȃ��ꍇ�A�c����V���ɍ쐬
        pChildGroupActor = NEW GroupHead(prm_kind);
        appendChild(pChildGroupActor);
        pChildGroupActor->setSceneChief(this);
    }
    pChildGroupActor->appendChild(prm_pMainActor);
    prm_pMainActor->setGroupHead(pChildGroupActor);
    prm_pMainActor->setSceneChief(this);
    return pChildGroupActor;
}

GroupHead* SceneChief::appendGroupChild(MainActor* prm_pMainActor) {
    return appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GroupHead* SceneChief::searchChildGroupHead(kind_t prm_kind) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        Actor* pChildActor = _pChildFirst;
        GroupHead* pChildGroupHead_ret = nullptr;
        do {
            if (pChildActor->instanceOf(Obj_ggaf_GroupHead)) {
                pChildGroupHead_ret = (GroupHead*)pChildActor;
                if (pChildGroupHead_ret->_kind == prm_kind && pChildGroupHead_ret->_frame_of_life_when_end == 0) {
                    return pChildGroupHead_ret;
                }
            }
            if (pChildActor->_is_last_flg) {
                break;
            } else {
                pChildActor = pChildActor->_pNext;
            }
        } while (true);

        return nullptr;
    }
}

void SceneChief::updateActiveInTheTree() {
    Scene* pPlatform = getPlatformScene();
    if (pPlatform) {
        if (pPlatform->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        throwCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���B this="<<NODE_INFO);
    }
}

Caretaker* SceneChief::askCaretaker() {
    if (_pCaretaker == nullptr) {
#ifdef MY_DEBUG
        if (getPlatformScene() == nullptr) {
            throwCriticalException("�Ǘ��҂͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pCaretaker = getPlatformScene()->askCaretaker();
    }
    return _pCaretaker;
}

Actor* SceneChief::search(hashval prm_name_hash) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        Actor* pPrev = this;
        Actor* pCur = getChildFirst();

        while (pCur != this) {
            if (pCur->_name_hash == prm_name_hash) {
                return pCur; //�����܂�
            } else {
                pPrev = pCur;
            }
            if (pPrev == pCur->getParent()) {
                //�ォ��~��ė����ꍇ
                goto susume;
            } else if (pPrev == pCur->getPrev()) {
                //������ɐi��ŗ����ꍇ
                goto susume;
            } else {
                //������オ���Ă����ꍇ
                //�E�֍s���������݂�
                if (pCur->_is_last_flg) {
                    //�Ǝv������E�[�������̂ŁA��ɖ߂�
                    pCur = pCur->getParent();
                } else {
                    //�E�֍s����̂ŁA�s���I
                    pCur = pCur->getNext();
                }
                continue;
            }
susume:
            //�~����Ȃ�΍~���
            if (pCur->getChildFirst()) {
                pCur = pCur->getChildFirst();
            } else {
                //�~���Ȃ��ꍇ�͉E�֍s���������݂�
                if (pCur->_is_last_flg) {
                    //�Ǝv������E�[�������̂ŁA��ɖ߂�
                    pCur = pCur->getParent();
                } else {
                    //�E�֍s����̂ŁA�s���I
                    pCur = pCur->getNext();
                }
            }
        }
        return nullptr;
    }
}
SceneChief::~SceneChief() {
}
