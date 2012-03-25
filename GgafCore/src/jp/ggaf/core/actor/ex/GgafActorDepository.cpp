#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafActorDepository::GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafDummyActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafActorDepository;
    _class_name = "GgafActorDepository";
    setHitAble(false);
}


void GgafActorDepository::addSubLast(GgafActor* prm_pSub) {

    if (_pSubFirst == NULL) {
        //種別を引き継ぐ
        _pStatus->set(STAT_DEFAULT_ACTOR_KIND, prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
    } else {
#ifdef MY_DEBUG
        if (_pStatus->get(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafActorDepository::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pDependenceDepository = this;
    prm_pSub->inactivateImmed(); //強制非活動に
    GgafDummyActor::addSubLast(prm_pSub);
}

void GgafActorDepository::onReset() {
    _TRACE_("GgafActorDepository::onReset() ["<<getName()<<"]");
    if (_pSubFirst == NULL) {
        return;
    }
    GgafMainActor* pActor = getSubFirst();
    while (true) {
        pActor->inactivate();
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
        if (_frame_of_life_when_end < _frame_of_life + end_frame_delay + GGAF_SAYONARA_DELAY) {
            //今回指定の方が遅いフレーム指定であるため無視する。
            return;
        }
    }
    _will_end_after_flg = true;
    _frame_of_life_when_end = _frame_of_life + end_frame_delay + GGAF_SAYONARA_DELAY;
    inactivateDelay(prm_offset_frames); //指定フレームにはinactivateが行われるのは同じ

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


//＜最適化案＞
//TODO:GgafActorDepositoryは、GgafGroupHeadを継承して、
//特別なGgafGroupHeadという扱いにすればアクターの数を減らせれるのではないか
//場合によりけりか、あとで考える。
