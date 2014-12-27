#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafActorDepository::GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafDestructActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafActorDepository;
    _class_name = "GgafActorDepository";
    setHitAble(false);
}

void GgafActorDepository::put(GgafActor* prm_pSub) {
    if (_pSubFirst == nullptr) {
        //��ʂ������p��
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDepository::addSubLast �قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"<<
                                       "�z��="<<getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "����="<<prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pDependenceDepository = this;
    prm_pSub->inactivate(); //�����񊈓��� _will_activate_after_flg = false; �ɂȂ�B
    GgafDestructActor::addSubLast(prm_pSub);
}

void GgafActorDepository::onReset() {
    _TRACE_("GgafActorDepository::onReset() ["<<getName()<<"]");
    if (_pSubFirst == nullptr) {
        return;
    }
    GgafActor* pActor = getSubFirst();
    while (pActor) {
        pActor->reset();
        if (pActor->isActive()) {
            //TODO:�E�E�E������ƔY�݂ǂ���
            pActor->inactivateImmed();
            pActor->_will_activate_after_flg = false;
            pActor->onInactive();
        } else {
            //TODO:�E�E�E������ƔY�݂ǂ���
            pActor->_will_activate_after_flg = false;
        }
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

    GgafActor* pElementTemp = _pSubFirst;
    while (pElementTemp) {
        end_frame_delay -= 2;
        pElementTemp->end(end_frame_delay);
        if (pElementTemp->_is_last_flg) {
            break;
        } else {
            pElementTemp = pElementTemp->_pNext;
        }
    }
}


//���œK���ā�
//TODO:GgafActorDepository�́AGgafGroupHead���p�����āA
//���ʂ�GgafGroupHead�Ƃ��������ɂ���΃A�N�^�[�̐������点���̂ł͂Ȃ���
//�ꍇ�ɂ�肯�肩�A���Ƃōl����B
