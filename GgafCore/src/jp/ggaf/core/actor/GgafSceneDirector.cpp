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
        s->throwEventUpperTree(prm_no, this); //自分より上位は居ない。そこで所属シーンへ投げる
    }
}

void GgafSceneDirector::remove() {
    throwGgafCriticalException("Error! GgafSceneDirectorはremove()によって削除は行えません！");
}

GgafGroupHead* GgafSceneDirector::addSubGroup(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneDirector) {
        prm_pMainActor->extract();
    }
    GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //サブに同じ種別団長が居るか探す
    if (pSubGroupActor) {
        //サブに同じ種別団長がいた場合、その団長のサブへ
        pSubGroupActor->addSubLast(prm_pMainActor);
        prm_pMainActor->setMyGroupHead(pSubGroupActor);
        prm_pMainActor->setMySceneDirector(this);
        prm_pMainActor->setPlatformScene(_pScene_platform);
        return pSubGroupActor;
    } else {
        //サブに同じ種別団長がいない場合、団長を新たに作成
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
        throwGgafCriticalException("_is_active_in_the_tree_flg 更新できません。 this="<<NODE_INFO);
    }
}

GgafGod* GgafSceneDirector::askGod() {
    if (_pGod == nullptr) {
#ifdef MY_DEBUG
        if (getPlatformScene() == nullptr) {
            throwGgafCriticalException("神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pGod = getPlatformScene()->askGod();
    }
    return _pGod;
}

GgafSceneDirector::~GgafSceneDirector() {
}
