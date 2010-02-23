#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

LaserChipDispatcherDispatcher::LaserChipDispatcherDispatcher(const char* prm_name) : GgafActorDispatcher(prm_name) {
    _class_name = "LaserChipDispatcherDispatcher";
}

void LaserChipDispatcherDispatcher::processBehavior() {
}

LaserChipDispatcher* LaserChipDispatcherDispatcher::employ() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("LaserChipDispatcherDispatcher::employ() 子がありません");
        }
#endif
        LaserChipDispatcher* pDispatcher = (LaserChipDispatcher*)getSubFirst();

        while(true) {
            if (pDispatcher->_is_active_flg == false &&
                pDispatcher->_is_active_flg_in_next_frame == false &&
                pDispatcher->_on_change_to_inactive_flg == false)
            {
                //pActor->activate(); //activateは呼び元で明示的に行うようにした
                pDispatcher->moveLast(); //お尻に回す
                break;//取得！
            } else {   //今活動中、或いは、次フレーム活動予定の場合は見送る
                if (pDispatcher->isLast()) {
                    pDispatcher = NULL;
                    break;
                } else {
                    pDispatcher = (LaserChipDispatcher*)pDispatcher->getNext();
                    continue;
                }
            }
        }
        return pDispatcher;

}

void LaserChipDispatcherDispatcher::addSubLast(LaserChipDispatcher* prm_pDispatcher_LaserChip) {
    GgafActorDispatcher::addSubLast(prm_pLaserChip);
}

LaserChipDispatcherDispatcher::~LaserChipDispatcherDispatcher() {
}
