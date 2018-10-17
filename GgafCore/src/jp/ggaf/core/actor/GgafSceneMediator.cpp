#include "jp/ggaf/core/actor/GgafSceneMediator.h"

#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafSceneMediator::GgafSceneMediator(GgafScene* prm_pScene_platform) : GgafActor("SceneMediator", nullptr),
_pScene_platform(nullptr)
{
    _obj_class |= Obj_GgafSceneMediator;
    _class_name = "GgafSceneMediator";
    _pScene_platform = prm_pScene_platform;
    setHitAble(false);
}

void GgafSceneMediator::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    GgafScene* s = getPlatformScene();
    if (s) {
        s->throwEventUpperTree(prm_no, this); //自分より上位は居ない。そこで所属シーンへ投げる
    }
}

void GgafSceneMediator::remove() {
    throwGgafCriticalException("Error! GgafSceneMediatorはremove()によって削除は行えません！");
}

GgafGroupHead* GgafSceneMediator::appendGroupChild(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        throwGgafCriticalException("Error! GgafSceneMediator::appendGroupChild 所属済みを無理やり移動させようとしています。\n"
                " extract() を行ってから出来ないですか？ prm_pMainActor="<<NODE_INFO_P(prm_pMainActor)<<"/this="<<NODE_INFO);
    }
    GgafGroupHead* pChildGroupActor = searchChildGroupHead(prm_kind); //子に同じ種別団長が居るか探す
    if (!pChildGroupActor) {
        //子に同じ種別団長がいない場合、団長を新たに作成
        pChildGroupActor = NEW GgafGroupHead(prm_kind);
        appendChild(pChildGroupActor);
        pChildGroupActor->setMySceneMediator(this);
    }
    pChildGroupActor->appendChild(prm_pMainActor);
    prm_pMainActor->setMyGroupHead(pChildGroupActor);
    prm_pMainActor->setMySceneMediator(this);
    return pChildGroupActor;
}

GgafGroupHead* GgafSceneMediator::appendGroupChild(GgafMainActor* prm_pMainActor) {
    return appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GgafGroupHead* GgafSceneMediator::searchChildGroupHead(kind_t prm_kind) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pChildActor = _pChildFirst;
        GgafGroupHead* pChildGroupHead_ret = nullptr;
        do {
            if (pChildActor->instanceOf(Obj_GgafGroupHead)) {
                pChildGroupHead_ret = (GgafGroupHead*)pChildActor;
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

void GgafSceneMediator::updateActiveInTheTree() {
    GgafScene* pPlatform = getPlatformScene();
    if (pPlatform) {
        if (pPlatform->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        throwGgafCriticalException("_is_active_in_the_tree_flg 更新できません。 this="<<NODE_INFO);
    }
}

GgafGod* GgafSceneMediator::askGod() {
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

GgafActor* GgafSceneMediator::search(hashval prm_name_hash) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pPrev = this;
        GgafActor* pCur = getChildFirst();

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
GgafSceneMediator::~GgafSceneMediator() {
}
