#include "stdafx.h"
using namespace GgafCore;

GgafActorDepositoryStore::GgafActorDepositoryStore(const char* prm_name, GgafStatus* prm_pStat) : GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "GgafActorDepositoryStore";
    setHitAble(false);
}


void GgafActorDepositoryStore::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (prm_pSub->_obj_class & Obj_GgafActorDepository) {
        //OK
    } else {
        throwGgafCriticalException("GgafActorDepositoryStore::addSubLast this="<<getName()<<" 引数 prm_pSub("<<prm_pSub->getName()<<") は デポジトリでなければいけません");
    }
    if (_pSubFirst == NULL) {
        if (prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND) == 0) {
            _TRACE_("＜警告＞ GgafActorDepositoryStore::addSubLast 引数 this="<<getName()<<" prm_pSub("<<prm_pSub->getName()<<") は の種別が0ですが意図していますか？");
        }
    }
#endif
    GgafActorDepository::addSubLast(prm_pSub);
}

void GgafActorDepositoryStore::processFinal() {

    GgafMainActor* pSubDepository = getSubFirst();
    while (true) {
        if (pSubDepository->_is_active_flg && !(pSubDepository->_will_inactivate_after_flg)) {
            bool is_inactive_all = false; //全メンバーが非活動の場合true
            GgafMainActor* pActor = pSubDepository->getSubFirst()->getPrev(); //お尻から見る(アクティブは後ろに回されているためブレイク確立が高い）
            while (true) {
                if (pActor->_is_active_flg) {
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
