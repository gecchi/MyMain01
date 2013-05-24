#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepositoryStore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChipDepositoryStore::LaserChipDepositoryStore(const char* prm_name, GgafStatus* prm_pStat) :
        GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "LaserChipDepositoryStore";
}

void LaserChipDepositoryStore::processBehavior() {
}

LaserChipDepository* LaserChipDepositoryStore::dispatch(int prm_offset_frames) {
#ifdef MY_DEBUG
        if (_pSubFirst == nullptr) {
            throwGgafCriticalException("LaserChipDepositoryStore::dispatch() éqÇ™Ç†ÇËÇ‹ÇπÇÒ");
        }
#endif
        GgafMainActor* p = GgafActorDepository::dispatch(prm_offset_frames);
#ifdef MY_DEBUG
        if (p->instanceOf(Obj_GgafActorDepository)) {
            //OK
        } else {
            throwGgafCriticalException("LaserChipDepositoryStore::dispatch() DepositoryÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒÅB");
        }
#endif
        LaserChipDepository* pDepo = (LaserChipDepository*)p;
        return pDepo;
}

void LaserChipDepositoryStore::addSubLast(LaserChipDepository* prm_pDepo_LaserChip) {
    GgafActorDepository::addSubLast(prm_pDepo_LaserChip);
}

LaserChipDepositoryStore::~LaserChipDepositoryStore() {
}
