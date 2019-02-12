#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

ActorDepositoryStore::ActorDepositoryStore(const char* prm_name, Status* prm_pStat) : ActorDepository(prm_name, prm_pStat) {
    _class_name = "ActorDepositoryStore";
    setHitAble(false);
}

void ActorDepositoryStore::put(Actor* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->instanceOf(Obj_ggaf_ActorDepository)) {
        //OK
    } else {
        throwCriticalException("this="<<getName()<<" ���� prm_pChild("<<prm_pChild->getName()<<") �� �f�|�W�g���łȂ���΂����܂���");
    }
    if (_pChildFirst == nullptr) {
        if (prm_pChild->getDefaultKind() == 0U) {
            _TRACE_("���x���� ActorDepositoryStore::appendChild ���� this="<<getName()<<" prm_pChild("<<prm_pChild->getName()<<") �� �̎�ʂ�0�ł����Ӑ}���Ă��܂����H");
        }
    }
#endif
    ActorDepository::put(prm_pChild);
}

void ActorDepositoryStore::processFinal() {
    Actor* pChildDepository = getChildFirst(); //�q�̓f�|�W�g���̂͂�
    while (pChildDepository) {
        if (pChildDepository->_is_active_flg && !(pChildDepository->willInactivateAfter())) {
            bool is_inactive_all = false; //�S�����o�[���񊈓��̏ꍇtrue
            Actor* pActor = pChildDepository->getChildFirst()->getPrev(); //���K���猩��(�A�N�e�B�u�͌��ɉ񂳂�Ă��邽�߃u���C�N�m���������j
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

