#include "jp/ggaf/core/actor/SceneChief.h"

#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/MainActor.h"
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