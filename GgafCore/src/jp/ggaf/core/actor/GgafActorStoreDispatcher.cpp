#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorStoreDispatcher::GgafActorStoreDispatcher(const char* prm_name) : GgafActorStore(prm_name) {
    _class_name = "GgafActorStoreDispatcher";
    setHitAble(false);
}


void GgafActorStoreDispatcher::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (prm_pSub->_obj_class & Obj_GgafActorStore) {
        //OK
    } else {
        throwGgafCriticalException("GgafActorStoreDispatcher::addSubLast 引数 prm_pSub("<<prm_pSub->getName()<<") は ディスパッチャーでなければいけません");
    }
    if (_pSubFirst == NULL) {
        if (prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND) == 0) {
            _TRACE_("＜警告＞ GgafActorStoreDispatcher::addSubLast 引数 prm_pSub("<<prm_pSub->getName()<<") は の種別が0ですが意図していますか？");
        }
    }
#endif
    GgafActorStore::addSubLast(prm_pSub);
}

void GgafActorStoreDispatcher::processFinal() {

    GgafMainActor* pSubStore = getSubFirst();
    while (true) {
        if (pSubStore->_is_active_flg && !(pSubStore->_will_inactivate_after_flg)) {
            bool is_inactive_all = false; //全メンバーが非活動の場合true
            GgafMainActor* pActor = pSubStore->getSubFirst()->getPrev(); //お尻から見る(アクティブは後ろに回されているためブレイク確立が高い）
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
                pSubStore->inactivate();
            }
        }
        if (pSubStore->_is_last_flg) {
            break;
        }
        pSubStore = pSubStore->getNext();
    }
}
