#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

LaserChipDispatcherDispatcher::LaserChipDispatcherDispatcher(const char* prm_name) : GgafActorDispatcher(prm_name) {
    _class_name = "LaserChipDispatcherDispatcher";
}

void LaserChipDispatcherDispatcher::processBehavior() {
}

LaserChipDispatcher* LaserChipDispatcherDispatcher::employ() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("LaserChipDispatcherDispatcher::employ() éqÇ™Ç†ÇËÇ‹ÇπÇÒ");
        }
#endif
        GgafMainActor* p = GgafActorDispatcher::employ();
#ifdef MY_DEBUG
        if (p->_actor_class & Obj_GgafActorDispatcher) {
            //OK
        } else {
            throwGgafCriticalException("LaserChipDispatcherDispatcher::employ() DispatcherÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒÅB");
        }
#endif
        LaserChipDispatcher* pDispatcher = (LaserChipDispatcher*)p;
        return pDispatcher;
}

void LaserChipDispatcherDispatcher::addSubLast(LaserChipDispatcher* prm_pDispatcher_LaserChip) {
    GgafActorDispatcher::addSubLast(prm_pDispatcher_LaserChip);
}

LaserChipDispatcherDispatcher::~LaserChipDispatcherDispatcher() {
}
