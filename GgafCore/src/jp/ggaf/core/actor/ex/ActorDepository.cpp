#include "jp/ggaf/core/actor/ex/ActorDepository.h"

#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

ActorDepository::ActorDepository(const char* prm_name) : DestructActor(prm_name) {
    _obj_class |= Obj_ggaf_ActorDepository;
    _class_name = "ActorDepository";
    setHitAble(false);
}

void ActorDepository::put(Actor* prm_pChild) {
    if (_pChildFirst == nullptr) {
        //��ʂ������p��
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_pChild->getDefaultKind());
    } else {
#ifdef MY_DEBUG
        if (getDefaultKind() != prm_pChild->getDefaultKind()) {
            throwCriticalException("�قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"
                                       "�z��="<<getDefaultKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
                                       "����="<<prm_pChild->getDefaultKind()<<"["<<prm_pChild->getName()<<"]");
        }
#endif
    }
    prm_pChild->_pDependenceDepository = this;
    prm_pChild->inactivate(); //�����񊈓��ɁB
    DestructActor::appendChild(prm_pChild);
}

void ActorDepository::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    if (_pChildFirst == nullptr) {
        return;
    }
    //ActorDepository �̃��Z�b�g�́A�z����S�Ĕ񊈓���ԂƂ��A
    //�ʏ�A�N�^�[�̏���t���[���Ŋ�����ԂƂȂ邱�Ƃ��}���邽�߂�
    //_frame_of_life_when_activation = 0 ��ݒ�
    Actor* pActor = getChildFirst();
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

void ActorDepository::end(frame prm_offset_frames) {
    frame end_frame_delay = prm_offset_frames + (_child_num*2) + 1; //�����o�[�����ɏ����x�点��B
    //����end()���s�ς݂̏ꍇ�A��葁��end()����Ȃ�ΗL���Ƃ���
    if (_frame_of_life < _frame_of_life_when_end &&
                         _frame_of_life_when_end < _frame_of_life + end_frame_delay + GgafCore::Config::END_DELAY_FRAME) {
        //����end()���s�ς݂ł���A����ɍ���w��̂������� _frame_of_life_when_end �ɓ��B���邽�ߖ�������B
        return;
    }
    _frame_of_life_when_end = _frame_of_life + end_frame_delay + GgafCore::Config::END_DELAY_FRAME;
    inactivateDelay(prm_offset_frames); //�w��t���[���ɂ�inactivate���s����͓̂���

    Actor* pElementTemp = _pChildFirst;
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

