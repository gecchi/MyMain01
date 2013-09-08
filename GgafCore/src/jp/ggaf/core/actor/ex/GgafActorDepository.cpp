#include "stdafx.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafActorDepository::GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafDummyActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafActorDepository;
    _class_name = "GgafActorDepository";
    setHitAble(false);
}

void GgafActorDepository::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == nullptr) {
        //��ʂ������p��
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDepository::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pDependenceDepository = this;
    prm_pSub->inactivateImmed(); //�����񊈓���
    GgafDummyActor::addSubLast(prm_pSub);
//    _listDispatched.addNext(nullptr);
}

void GgafActorDepository::onReset() {
    _TRACE_("GgafActorDepository::onReset() ["<<getName()<<"]");
    if (_pSubFirst == nullptr) {
        return;
    }
    GgafActor* pActor = getSubFirst();
    while (true) {
        if (pActor->isActive()) {
            //TODO:�E�E�E������ƔY�݂ǂ���
            pActor->_on_change_to_inactive_flg = true;
            pActor->onInactive();
            pActor->_frame_of_life_when_inactivation = 0;
            pActor->_will_inactivate_after_flg = false;
        }
        pActor->inactivateImmed();
        if (pActor->isLast()) {
            break;
        } else {
            pActor = pActor->getNext();
            continue;
        }
    }
}
void GgafActorDepository::end(frame prm_offset_frames) {
    frame end_frame_delay = prm_offset_frames + (_sub_num*2) + 1; //�����o�[�����ɏ����x�点��B
    if (_will_end_after_flg) {
        //����end()���s�ς݂̏ꍇ�A��葁��end()����Ȃ�ΗL���Ƃ���
        if (_frame_of_life_when_end < _frame_of_life + end_frame_delay + GGAF_END_DELAY) {
            //����w��̕����x���t���[���w��ł��邽�ߖ�������B
            return;
        }
    }
    _will_end_after_flg = true;
    _frame_of_life_when_end = _frame_of_life + end_frame_delay + GGAF_END_DELAY;
    inactivateDelay(prm_offset_frames); //�w��t���[���ɂ�inactivate���s����͓̂���

    if (_pSubFirst) {
        GgafActor* pElementTemp = _pSubFirst;
        while(true) {
            end_frame_delay -= 2;
            pElementTemp->end(end_frame_delay);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}


//���œK���ā�
//TODO:GgafActorDepository�́AGgafGroupHead���p�����āA
//���ʂ�GgafGroupHead�Ƃ��������ɂ���΃A�N�^�[�̐������点���̂ł͂Ȃ���
//�ꍇ�ɂ�肯�肩�A���Ƃōl����B
