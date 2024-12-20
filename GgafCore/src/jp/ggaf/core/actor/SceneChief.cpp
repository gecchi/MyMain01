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
        s->throwEventUpperTree(prm_event_val, this); //自分より上位は居ない。そこで所属シーンへ投げる
    }
}

void SceneChief::remove() {
    throwCriticalException("Error! SceneChiefはremove()によって削除は行えません！");
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
        throwCriticalException("_is_active_in_the_tree_flg 更新できません。 this="<<NODE_INFO);
    }
}

Caretaker* SceneChief::askCaretaker() {
    if (_pCaretaker == nullptr) {
#ifdef MY_DEBUG
        if (getPlatformScene() == nullptr) {
            throwCriticalException("管理者はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
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
                return pCur; //おしまい
            } else {
                pPrev = pCur;
            }
            if (pPrev == pCur->getParent()) {
                //上から降りて来た場合
                goto susume;
            } else if (pPrev == pCur->getPrev()) {
                //左からに進んで来た場合
                goto susume;
            } else {
                //下から上がってきた場合
                //右へ行く事を試みる
                if (pCur->_is_last_flg) {
                    //と思ったら右端だったので、上に戻る
                    pCur = pCur->getParent();
                } else {
                    //右へ行けるので、行く！
                    pCur = pCur->getNext();
                }
                continue;
            }
susume:
            //降りれるならば降りる
            if (pCur->getChildFirst()) {
                pCur = pCur->getChildFirst();
            } else {
                //降りれない場合は右へ行く事を試みる
                if (pCur->_is_last_flg) {
                    //と思ったら右端だったので、上に戻る
                    pCur = pCur->getParent();
                } else {
                    //右へ行けるので、行く！
                    pCur = pCur->getNext();
                }
            }
        }
        return nullptr;
    }
}
SceneChief::~SceneChief() {
}
