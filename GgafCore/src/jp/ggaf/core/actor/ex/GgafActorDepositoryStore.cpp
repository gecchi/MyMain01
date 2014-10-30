#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafActorDepositoryStore::GgafActorDepositoryStore(const char* prm_name, GgafStatus* prm_pStat) : GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "GgafActorDepositoryStore";
    setHitAble(false);
}

void GgafActorDepositoryStore::put(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (prm_pSub->instanceOf(Obj_GgafActorDepository)) {
        //OK
    } else {
        throwGgafCriticalException("GgafActorDepositoryStore::addSubLast this="<<getName()<<" 引数 prm_pSub("<<prm_pSub->getName()<<") は デポジトリでなければいけません");
    }
    if (_pSubFirst == nullptr) {
        if (prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND) == 0U) {
            _DTRACE_("＜警告＞ GgafActorDepositoryStore::addSubLast 引数 this="<<getName()<<" prm_pSub("<<prm_pSub->getName()<<") は の種別が0ですが意図していますか？");
        }
    }
#endif
    GgafActorDepository::put(prm_pSub);
}

void GgafActorDepositoryStore::processFinal() {
    GgafActor* pSubDepository = getSubFirst(); //子はデポジトリのはず
    while (pSubDepository) {
        if (pSubDepository->_is_active_flg && !(pSubDepository->_will_inactivate_after_flg)) {
            bool is_inactive_all = false; //全メンバーが非活動の場合true
            GgafActor* pActor = pSubDepository->getSubFirst()->getPrev(); //お尻から見る(アクティブは後ろに回されているためブレイク確立が高い）
            while (true) {
                if (pActor->_is_active_flg || pActor->_will_activate_after_flg) {
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
                pSubDepository->inactivate();
            }
        }
        if (pSubDepository->_is_last_flg) {
            break;
        }
        pSubDepository = pSubDepository->getNext();
    }
}

