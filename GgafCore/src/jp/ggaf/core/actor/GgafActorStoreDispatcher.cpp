#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorStoreDispatcher::GgafActorStoreDispatcher(const char* prm_name) : GgafActorStore(prm_name) {
    _class_name = "GgafActorStoreDispatcher";
    setHitAble(false);
}


void GgafActorStoreDispatcher::addSubLast(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (prm_pSub->_obj_class & Obj_GgafActorStore) {
        //OK
    } else {
        throwGgafCriticalException("GgafActorStoreDispatcher::addSubLast ���� prm_pSub("<<prm_pSub->getName()<<") �� �f�B�X�p�b�`���[�łȂ���΂����܂���");
    }
    if (_pSubFirst == NULL) {
        if (prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND) == 0) {
            _TRACE_("���x���� GgafActorStoreDispatcher::addSubLast ���� prm_pSub("<<prm_pSub->getName()<<") �� �̎�ʂ�0�ł����Ӑ}���Ă��܂����H");
        }
    }
#endif
    GgafActorStore::addSubLast(prm_pSub);
}

void GgafActorStoreDispatcher::processFinal() {

    GgafMainActor* pSubStore = getSubFirst();
    while (true) {
        if (pSubStore->_is_active_flg && !(pSubStore->_will_inactivate_after_flg)) {
            bool is_inactive_all = false; //�S�����o�[���񊈓��̏ꍇtrue
            GgafMainActor* pActor = pSubStore->getSubFirst()->getPrev(); //���K���猩��(�A�N�e�B�u�͌��ɉ񂳂�Ă��邽�߃u���C�N�m���������j
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
                pSubStore->inactivate();
            }
        }
        if (pSubStore->_is_last_flg) {
            break;
        }
        pSubStore = pSubStore->getNext();
    }
}
