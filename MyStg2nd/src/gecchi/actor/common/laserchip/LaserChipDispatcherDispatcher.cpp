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
            throwGgafCriticalException("LaserChipDispatcherDispatcher::employ() �q������܂���");
        }
#endif
        LaserChipDispatcher* pDispatcher = (LaserChipDispatcher*)getSubFirst();

        while(true) {
            if (pDispatcher->_is_active_flg == false &&
                pDispatcher->_is_active_flg_in_next_frame == false &&
                pDispatcher->_on_change_to_inactive_flg == false)
            {
                //pActor->activate(); //activate�͌Ăь��Ŗ����I�ɍs���悤�ɂ���
                pDispatcher->moveLast(); //���K�ɉ�
                break;//�擾�I
            } else {   //���������A�����́A���t���[�������\��̏ꍇ�͌�����
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
