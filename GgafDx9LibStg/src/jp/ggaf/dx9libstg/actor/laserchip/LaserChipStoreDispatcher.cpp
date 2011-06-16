#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

LaserChipStoreDispatcher::LaserChipStoreDispatcher(const char* prm_name) : GgafActorStore(prm_name) {
    _class_name = "LaserChipStoreDispatcher";
}

void LaserChipStoreDispatcher::processBehavior() {
}

LaserChipStore* LaserChipStoreDispatcher::dispatch() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("LaserChipStoreDispatcher::dispatch() éqÇ™Ç†ÇËÇ‹ÇπÇÒ");
        }
#endif
        GgafMainActor* p = GgafActorStore::dispatch();
#ifdef MY_DEBUG
        if (p->_obj_class & Obj_GgafActorStore) {
            //OK
        } else {
            throwGgafCriticalException("LaserChipStoreDispatcher::dispatch() StoreÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒÅB");
        }
#endif
        LaserChipStore* pStore = (LaserChipStore*)p;
        return pStore;
}

void LaserChipStoreDispatcher::addSubLast(LaserChipStore* prm_pStore_LaserChip) {
    GgafActorStore::addSubLast(prm_pStore_LaserChip);
}

LaserChipStoreDispatcher::~LaserChipStoreDispatcher() {
}
