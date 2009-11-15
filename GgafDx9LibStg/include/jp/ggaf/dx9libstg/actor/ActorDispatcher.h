#ifndef ACTORDISPATCHER_H_
#define ACTORDISPATCHER_H_
namespace GgafDx9LibStg {

/**
 * アクター発送者クラス .
 * 子に予めアクターを登録しておき（アクター発送者メンバーと呼ぶ）、空いているメンバーを取得する。<BR>
 * 取得したアクターを、アクター発送者戻す（再度使いまわしをしたい）たい時は inactivate() して下さい。本クラスが自動的に拾います。<BR>
 * 敵弾など、何度も使いまわし、かつオブジェクト数制限したい場合等に有効。ストックと考えても良い。<BR>
 * また連続employ()の場合、次のemploy()のアクターは必ず隣同士となっています。<BR>
 */
class ActorDispatcher : public GgafCore::GgafDummyActor {

public:
    StgChecker* _pStgChecker;

    ActorDispatcher(const char* prm_name);

//    /**
//     * 暇そうなアクター発送者メンバー（play中、またはplay予約されていない）が居れば、
//     * アクター発送者の一番先頭に移動させます。<BR>
//     * TODO:これは負荷がかかるのであまりやりたくない、Laser以外はなんでもいいはず
//     * ＜OverRide です＞<BR>
//     */
//    virtual void processBehavior() {
//        static GgafMainActor* pActor;
//        pActor = getSubFirst();
//        while (true) {
//            if (pActor->onChangeToInactive()) {
//                pActor->moveFirst();
//            }
//            if (pActor->isLast()) {
//                break;
//            } else {
//                pActor = pActor->getNext();
//            }
//        }
//    }

    /**
     * 子アクターへは影響させない
     */
    virtual void activateTree() {
        activate();
    }

    virtual void inactivateTree() {
        inactivate();
    }

    /**
     * 暇そうなアクター発送者のメンバー（play中、またはplay予約されていない）がいれば、activate() して取得する。<BR>
     * 暇なメンバーが居ない場合 NULL が返ります。<BR>
     * 取得できる場合、ポインタを返すと共に、そのアクターはアクター発送者のサブの一番後ろに移動されます。<BR>
     * @return 暇そうなアクター発送者のメンバーアクター
     */
    virtual GgafCore::GgafMainActor* employ() {
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("ActorDispatcher::getFreeOne() 子がありません");
        }
        static GgafMainActor* pActor;
        pActor = getSubFirst();

        while(true) {
            if (pActor->isActive() || pActor->_is_active_flg_in_next_frame || pActor->_on_change_to_inactive_flg) {
                //今活動中、或いは、次フレーム活動予定、或いは、次フレーム非活動予定の場合は見送る
                if (pActor->isLast()) {
                    pActor = NULL;
                    break;
                } else {
                    pActor = pActor->getNext();
                    continue;
                }
            } else {
                pActor->activate();
                pActor->moveLast(); //取得！
                break;
            }
        }
        return pActor;
    }

    virtual ~ActorDispatcher() {
    }
};

}
#endif /*ACTORDISPATCHER_H_*/
