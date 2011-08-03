#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorStore::GgafActorStore(const char* prm_name) : GgafDummyActor(prm_name) {
    _obj_class |= Obj_GgafActorStore;
    _class_name = "GgafActorStore";
    setHitAble(false);
}


void GgafActorStore::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorStore::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pDependenceStore = this;
    prm_pSub->inactivateImmediately(); //強制非活動に
    GgafDummyActor::addSubLast(prm_pSub);
}

void GgafActorStore::onReset() {
    _TRACE_("GgafActorStore::onReset() ["<<getName()<<"]");
    if (_pSubFirst == NULL) {
        return;
    }
    GgafMainActor* pActor = getSubFirst();
    while (true) {
        pActor->inactivate();
        if (pActor->isLast()) {
            break;
        } else {
            pActor = pActor->getNext();
            continue;
        }
    }
}



//＜最適化案＞
//TODO:GgafActorStoreは、GgafGroupHeadを継承して、
//特別なGgafGroupHeadという扱いにすればアクターの数を減らせれるのではないか
//場合によりけりか、あとで考える。
