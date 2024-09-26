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
        //種別を引き継ぐ
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_pChild->getDefaultKind());
    } else {
#ifdef MY_DEBUG
        if (getDefaultKind() != prm_pChild->getDefaultKind()) {
            throwCriticalException("異なる種別のアクターを登録しようとしています。 \n"
                                       "想定="<<getDefaultKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
                                       "引数="<<prm_pChild->getDefaultKind()<<"["<<prm_pChild->getName()<<"]");
        }
#endif
    }
    prm_pChild->_pDependenceDepository = this;
    prm_pChild->inactivate(); //強制非活動に。
    DestructActor::appendChild(prm_pChild);
}

void ActorDepository::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    if (_pChildFirst == nullptr) {
        return;
    }
    //ActorDepository のリセットは、配下を全て非活動状態とし、
    //通常アクターの初回フレームで活動状態となることも抑えるために
    //_frame_of_life_when_activation = 0 を設定
    Actor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->isActive()) {
            //TODO:・・・ちょっと悩みどころ、この処理を入れるべきか？
            pActor->inactivateImmed();
            pActor->onInactive();
        } else {
            //inactive と同フレーム、または inactive 予定よりも後に active 予定があっても
            //inactivate() の実行により、こちらのほうが強いので強制非活動となる。
            pActor->inactivate();
        }
        pActor->reset(); //リセット
        if (pActor->isLast()) {
            break;
        } else {
            pActor = pActor->getNext();
            continue;
        }
    }
}

void ActorDepository::end(frame prm_offset_frames) {
    frame end_frame_delay = prm_offset_frames + (_child_num*2) + 1; //メンバーを順に少し遅らせる。
    //既にend()実行済みの場合、より早くend()するならば有効とする
    if (_frame_of_life < _frame_of_life_when_end &&
                         _frame_of_life_when_end < _frame_of_life + end_frame_delay + GgafCore::Config::END_DELAY_FRAME) {
        //既にend()実行済みであり、さらに今回指定のよりも早く _frame_of_life_when_end に到達するため無視する。
        return;
    }
    _frame_of_life_when_end = _frame_of_life + end_frame_delay + GgafCore::Config::END_DELAY_FRAME;
    inactivateDelay(prm_offset_frames); //指定フレームにはinactivateが行われるのは同じ

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

