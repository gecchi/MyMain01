#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafActorDepositoryStore::GgafActorDepositoryStore(const char* prm_name, GgafStatus* prm_pStat) : GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "GgafActorDepositoryStore";
    setHitAble(false);
}

void GgafActorDepositoryStore::put(GgafActor* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->instanceOf(Obj_GgafActorDepository)) {
        //OK
    } else {
        throwGgafCriticalException("this="<<getName()<<" 引数 prm_pChild("<<prm_pChild->getName()<<") は デポジトリでなければいけません");
    }
    if (_pChildFirst == nullptr) {
        if (prm_pChild->getDefaultKind() == 0U) {
            _TRACE_("＜警告＞ GgafActorDepositoryStore::appendChild 引数 this="<<getName()<<" prm_pChild("<<prm_pChild->getName()<<") は の種別が0ですが意図していますか？");
        }
    }
#endif
    GgafActorDepository::put(prm_pChild);
}

void GgafActorDepositoryStore::processFinal() {
    GgafActor* pChildDepository = getChildFirst(); //子はデポジトリのはず
    while (pChildDepository) {
        if (pChildDepository->_is_active_flg && !(pChildDepository->willInactivateAfter())) {
            bool is_inactive_all = false; //全メンバーが非活動の場合true
            GgafActor* pActor = pChildDepository->getChildFirst()->getPrev(); //お尻から見る(アクティブは後ろに回されているためブレイク確立が高い）
            while (true) {
                if (pActor->_is_active_flg || pActor->willActivateAfter()) {
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

