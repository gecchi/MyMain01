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
        //種別を引き継ぐ
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->getDefaultKind());
    } else {
#ifdef MY_DEBUG
        if (getDefaultKind() != prm_pSub->getDefaultKind()) {
            throwGgafCriticalException("異なる種別のアクターを登録しようとしています。 \n"
                                       "想定="<<getDefaultKind()<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"
                                       "引数="<<prm_pSub->getDefaultKind()<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pDependenceDepository = this;
    prm_pSub->inactivate(); //強制非活動に。
    GgafDestructActor::addSubLast(prm_pSub);
}

void GgafActorDepository::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    if (_pSubFirst == nullptr) {
        return;
    }
    //GgafActorDepository のリセットは、配下を全て非活動状態とし、
    //通常アクターの初回フレームで活動状態となることも抑えるために
    //_frame_of_life_when_activation = 0 を設定
    GgafActor* pActor = getSubFirst();
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

void GgafActorDepository::end(frame prm_offset_frames) {
    frame end_frame_delay = prm_offset_frames + (_sub_num*2) + 1; //メンバーを順に少し遅らせる。
    //既にend()実行済みの場合、より早くend()するならば有効とする
    if (_frame_of_life < _frame_of_life_when_end &&
                         _frame_of_life_when_end < _frame_of_life + end_frame_delay + GGAF_END_DELAY) {
        //既にend()実行済みであり、さらに今回指定のよりも早く _frame_of_life_when_end に到達するため無視する。
        return;
    }
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
