#include "stdafx.h"
using namespace std;
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
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("LaserChipDepositoryStore::dispatch() 子がありません");
        }
#endif
        GgafMainActor* p = GgafActorDepository::dispatch(prm_offset_frames);
#ifdef MY_DEBUG
        if (p->_obj_class & Obj_GgafActorDepository) {
            //OK
        } else {
            throwGgafCriticalException("LaserChipDepositoryStore::dispatch() Depositoryではありません。");
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
