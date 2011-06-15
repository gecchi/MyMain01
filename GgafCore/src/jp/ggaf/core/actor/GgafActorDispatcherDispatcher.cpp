#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorDispatcherDispatcher::GgafActorDispatcherDispatcher(const char* prm_name) : GgafActorDispatcher(prm_name) {
    _class_name = "GgafActorDispatcherDispatcher";
    setHitAble(false);
}


void GgafActorDispatcherDispatcher::addSubLast(GgafActor* prm_pSub) {
    if (prm_pSub->_obj_class & Obj_GgafActorDispatcher) {
        //OK
	} else {
		throwGgafCriticalException("GgafActorDispatcherDispatcher::addSubLast 引数 prm_pSub("<<prm_pSub->getName()<<") は ディスパッチャーでなければいけません");
    }
    if (_pSubFirst == NULL) {
        //最初のディスパッチャー登録
        if (prm_pSub->_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDispatcherDispatcher::addSubLast 引数 prm_pSub("<<prm_pSub->getName()<<") のディスパッチャーに登録メンバーが居ないため、種別が引き継げません");
        }
        //ディスパッチャーの種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDispatcherDispatcher::addSubLast 異なる種別のディスパッチャーを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
    }
    prm_pSub->_pDependenceDispcher = this;
//    prm_pSub->inactivateImmediately();
    GgafDummyActor::addSubLast(prm_pSub);
}
