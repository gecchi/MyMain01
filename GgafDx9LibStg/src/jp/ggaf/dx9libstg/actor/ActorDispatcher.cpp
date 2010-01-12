#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ActorDispatcher::ActorDispatcher(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "ActorDispatcher";
    setBumpable(false);
}


void ActorDispatcher::enter(GgafActor* prm_pSub) {
    addSubLast(prm_pSub);
    if (prm_pSub->_pStatus) {
        //Ží•Ê‚ðˆø‚«Œp‚®
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    }
}
