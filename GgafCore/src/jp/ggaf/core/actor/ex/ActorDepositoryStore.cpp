#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

ActorDepositoryStore::ActorDepositoryStore(const char* prm_name) : ActorDepository(prm_name) {
    _class_name = "ActorDepositoryStore";
    setHitAble(false);
}

void ActorDepositoryStore::put(Actor* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->instanceOf(Obj_ggaf_ActorDepository)) {
        //OK
    } else {
        throwCriticalException("this="<<getName()<<" 引数 prm_pChild("<<prm_pChild->getName()<<") は デポジトリでなければいけません");
    }
    if (_pChildFirst == nullptr) {
        if (prm_pChild->getCheckerKind() == 0U) {
            _TRACE_("【警告】 ActorDepositoryStore::appendChild 引数 this="<<getName()<<" prm_pChild("<<prm_pChild->getName()<<") は の種別が0ですが意図していますか？");
        }
    }
#endif
    ActorDepository::put(prm_pChild);
}

void ActorDepositoryStore::processFinal() {
    Actor* pChildDepository = getChildFirst(); //子はデポジトリのはず
    while (pChildDepository) {
        if (pChildDepository->_is_active_flg && !(pChildDepository->isInactivateScheduled())) {
            bool is_inactive_all = false; //全メンバーが非活動の場合true
            Actor* pActor = pChildDepository->getChildFirst()->getPrev(); //お尻から見る(アクティブは後ろに回されているためブレイク確立が高い）
            while (true) {
                if (pActor->_is_active_flg || pActor->isActivateScheduled()) {
                    //dispatch の
                    //if (pActor->_is_active_flg == false && pActor->_will_activate_after_flg == false) {
                    //の対偶の条件で判定すること。
                    break;
                }
                if (pActor->_is_first_flg) {
                    is_inactive_all = true;
                    break;
                }
                pActor = pActor->getPrev();
            }

            if (is_inactive_all) {
                pChildDepository->inactivate();
            }
        }
        if (pChildDepository->_is_last_flg) {
            break;
        }
        pChildDepository = pChildDepository->getNext();
    }
}

