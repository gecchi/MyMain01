#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorDispatcher::GgafActorDispatcher(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "GgafActorDispatcher";
    setHitAble(false);
}


void GgafActorDispatcher::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDispatcher::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pDependenceDispcher = this;
    prm_pSub->inactivateImmediately();
    GgafDummyActor::addSubLast(prm_pSub);
}

//＜最適化案＞
//TODO:GgafActorDispatcherは、GgafGroupActorを継承して、
//特別なGgafGroupActorという扱いにすればアクターの数を減らせれるのではないか
//場合によりけりか
