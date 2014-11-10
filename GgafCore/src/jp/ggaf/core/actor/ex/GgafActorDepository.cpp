#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafActorDepository::GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafDummyActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafActorDepository;
    _class_name = "GgafActorDepository";
    setHitAble(false);
}

void GgafActorDepository::put(GgafActor* prm_pSub) {
    if (_pSubFirst == nullptr) {
        //種別を引き継ぐ
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDepository::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pDependenceDepository = this;
    prm_pSub->inactivate(); //強制非活動に _will_activate_after_flg = false; になる。
    GgafDummyActor::addSubLast(prm_pSub);
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
            //TODO:・・・ちょっと悩みどころ
            pActor->inactivateImmed();
            pActor->_will_activate_after_flg = false;
            pActor->onInactive();
        } else {
            //TODO:・・・ちょっと悩みどころ
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
    frame end_frame_delay = prm_offset_frames + (_sub_num*2) + 1; //メンバーを順に少し遅らせる。
    if (_will_end_after_flg) {
        //既にend()実行済みの場合、より早くend()するならば有効とする
        if (_frame_of_life_when_end < _frame_of_life + end_frame_delay + GGAF_END_DELAY) {
            //今回指定の方が遅いフレーム指定であるため無視する。
            return;
        }
    }
    _will_end_after_flg = true;
    _frame_of_life_when_end = _frame_of_life + end_frame_delay + GGAF_END_DELAY;
    inactivateDelay(prm_offset_frames); //指定フレームにはinactivateが行われるのは同じ

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


//＜最適化案＞
//TODO:GgafActorDepositoryは、GgafGroupHeadを継承して、
//特別なGgafGroupHeadという扱いにすればアクターの数を減らせれるのではないか
//場合によりけりか、あとで考える。
