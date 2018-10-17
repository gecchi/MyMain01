#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafActorDepository::GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafDestructActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafActorDepository;
    _class_name = "GgafActorDepository";
    setHitAble(false);
}

void GgafActorDepository::put(GgafActor* prm_pChild) {
    if (_pChildFirst == nullptr) {
        //��ʂ������p��
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_pChild->getDefaultKind());
    } else {
#ifdef MY_DEBUG
        if (getDefaultKind() != prm_pChild->getDefaultKind()) {
            throwGgafCriticalException("�قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"
                                       "�z��="<<getDefaultKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
                                       "����="<<prm_pChild->getDefaultKind()<<"["<<prm_pChild->getName()<<"]");
        }
#endif
    }
    prm_pChild->_pDependenceDepository = this;
    prm_pChild->inactivate(); //�����񊈓��ɁB
    GgafDestructActor::appendChild(prm_pChild);
}

void GgafActorDepository::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    if (_pChildFirst == nullptr) {
        return;
    }
    //GgafActorDepository �̃��Z�b�g�́A�z����S�Ĕ񊈓���ԂƂ��A
    //�ʏ�A�N�^�[�̏���t���[���Ŋ�����ԂƂȂ邱�Ƃ��}���邽�߂�
    //_frame_of_life_when_activation = 0 ��ݒ�
    GgafActor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->isActive()) {
            //TODO:�E�E�E������ƔY�݂ǂ���A���̏���������ׂ����H
            pActor->inactivateImmed();
            pActor->onInactive();
        } else {
            //inactive �Ɠ��t���[���A�܂��� inactive �\�������� active �\�肪�����Ă�
            //inactivate() �̎��s�ɂ��A������̂ق��������̂ŋ����񊈓��ƂȂ�B
            pActor->inactivate();
        }
        pActor->reset(); //���Z�b�g
        if (pActor->isLast()) {
            break;
        } else {
            pActor = pActor->getNext();
            continue;
        }
    }
}

void GgafActorDepository::end(frame prm_offset_frames) {
    frame end_frame_delay = prm_offset_frames + (_child_num*2) + 1; //�����o�[�����ɏ����x�点��B
    //����end()���s�ς݂̏ꍇ�A��葁��end()����Ȃ�ΗL���Ƃ���
    if (_frame_of_life < _frame_of_life_when_end &&
                         _frame_of_life_when_end < _frame_of_life + end_frame_delay + GGAF_END_DELAY) {
        //����end()���s�ς݂ł���A����ɍ���w��̂������� _frame_of_life_when_end �ɓ��B���邽�ߖ�������B
        return;
    }
    _frame_of_life_when_end = _frame_of_life + end_frame_delay + GGAF_END_DELAY;
    inactivateDelay(prm_offset_frames); //�w��t���[���ɂ�inactivate���s����͓̂���

    GgafActor* pElementTemp = _pChildFirst;
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
