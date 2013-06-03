#include "stdafx.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/core/util/GgafStatus.h"


using namespace GgafCore;

GgafActorDepositoryStore::GgafActorDepositoryStore(const char* prm_name, GgafStatus* prm_pStat) : GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "GgafActorDepositoryStore";
    setHitAble(false);
}

void GgafActorDepositoryStore::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (prm_pSub->instanceOf(Obj_GgafActorDepository)) {
        //OK
    } else {
        throwGgafCriticalException("GgafActorDepositoryStore::addSubLast this="<<getName()<<" ���� prm_pSub("<<prm_pSub->getName()<<") �� �f�|�W�g���łȂ���΂����܂���");
    }
    if (_pSubFirst == nullptr) {
        if (prm_pSub->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND) == 0U) {
            _TRACE_("���x���� GgafActorDepositoryStore::addSubLast ���� this="<<getName()<<" prm_pSub("<<prm_pSub->getName()<<") �� �̎�ʂ�0�ł����Ӑ}���Ă��܂����H");
        }
    }
#endif
    GgafActorDepository::addSubLast(prm_pSub);
}

void GgafActorDepositoryStore::processFinal() {
    GgafActorDepository* pSubDepository = (GgafActorDepository*)getSubFirst();
    while (true) {
        if (pSubDepository->_is_active_flg && !(pSubDepository->_will_inactivate_after_flg)) {
            bool is_inactive_all = false; //�S�����o�[���񊈓��̏ꍇtrue
            GgafMainActor* pActor = (GgafMainActor*)(pSubDepository->getSubFirst()->getPrev()); //���K���猩��(�A�N�e�B�u�͌��ɉ񂳂�Ă��邽�߃u���C�N�m���������j
            while (true) {
                if (pActor->_is_active_flg) {
                    break;
                }
                if (pActor->_is_first_flg) {
                    is_inactive_all = true;
                    break;
                }
                pActor = pActor->getPrev();
            }

            if (is_inactive_all) {
                pSubDepository->inactivate();
            }
        }
        if (pSubDepository->_is_last_flg) {
            break;
        }
        pSubDepository = (GgafActorDepository*)(pSubDepository->getNext());
    }
}
