#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafActorDepositoryStore::GgafActorDepositoryStore(const char* prm_name, GgafStatus* prm_pStat) : GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "GgafActorDepositoryStore";
    setHitAble(false);
}

void GgafActorDepositoryStore::put(GgafActor* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->instanceOf(Obj_GgafActorDepository)) {
        //OK
    } else {
        throwGgafCriticalException("this="<<getName()<<" ���� prm_pChild("<<prm_pChild->getName()<<") �� �f�|�W�g���łȂ���΂����܂���");
    }
    if (_pChildFirst == nullptr) {
        if (prm_pChild->getDefaultKind() == 0U) {
            _TRACE_("���x���� GgafActorDepositoryStore::appendChild ���� this="<<getName()<<" prm_pChild("<<prm_pChild->getName()<<") �� �̎�ʂ�0�ł����Ӑ}���Ă��܂����H");
        }
    }
#endif
    GgafActorDepository::put(prm_pChild);
}

void GgafActorDepositoryStore::processFinal() {
    GgafActor* pChildDepository = getChildFirst(); //�q�̓f�|�W�g���̂͂�
    while (pChildDepository) {
        if (pChildDepository->_is_active_flg && !(pChildDepository->willInactivateAfter())) {
            bool is_inactive_all = false; //�S�����o�[���񊈓��̏ꍇtrue
            GgafActor* pActor = pChildDepository->getChildFirst()->getPrev(); //���K���猩��(�A�N�e�B�u�͌��ɉ񂳂�Ă��邽�߃u���C�N�m���������j
            while (true) {
                if (pActor->_is_active_flg || pActor->willActivateAfter()) {
                    //dispatch ��
                    //if (pActor->_is_active_flg == false && pActor->_will_activate_after_flg == false) {
                    //�̑΋�̏����Ŕ��肷�邱�ƁB
                    break;
                }
                if (pActor->_is_first_flg) {
                    is_inactive_all = true;
                    break;
                }
                pActor = pActor->getPrev();
            }

            if (is_inactive_all) {
                pChildDepository->inactivate();
            }
        }
        if (pChildDepository->_is_last_flg) {
            break;
        }
        pChildDepository = pChildDepository->getNext();
    }
}

