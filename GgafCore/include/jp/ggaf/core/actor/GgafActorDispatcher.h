#ifndef ACTORDISPATCHER_H_
#define ACTORDISPATCHER_H_
namespace GgafCore {

/**
 * アクター発送者クラス .
 * 子に予めアクターを登録(addSubLast メソッド)しておく。<BR>
 * employ() 空いているアクターを取得する。<BR>
 * アクターは使い終わったらinactivate()する。<BR>
 * 敵弾など、何度も使いまわし、かつオブジェクト数制限したい場合等に有効。ストックと考えても良い。<BR>
 * もともとポリラインのような連続して連結された固まりを管理したかった。<BR>
 * 連続employ()の場合、次のemploy()のアクターは必ず隣同士となっています。<BR>
 * (旧RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorDispatcher : public GgafDummyActor {

public:
    GgafActorDispatcher(const char* prm_name);

//    /**
//     * 暇そうなアクター発送者メンバー（play中、またはplay予約されていない）が居れば、
//     * アクター発送者の一番先頭に移動させます。<BR>
//     * TODO:これは負荷がかかるのであまりやりたくない、Laser以外はなんでもいいはず
//     * ＜OverRide です＞<BR>
//     */
//    virtual void processBehavior() override {
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
     * メンバーを登録します.
     * 具体的には、addSubLast() を呼び出し、種別を引き継ぎます。
     * 最初に登録したアクターが、本ディスパッチャーの種別となるため、同じ種別をaddSubLastしてください。
     * @param prm_pSub 登録アクター
     */
    virtual void addSubLast(GgafActor* prm_pSub);


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
     * アクター取り出し .
     * アクター発送者の暇そうなメンバー（active中、またはactive予約されていない）がいれば取得する。<BR>
     * 暇なメンバーが居ない場合 NULL が返ります。<BR>
     * 取得できる場合、ポインタを返すと共に、そのアクターはアクター発送者のサブの一番後ろに移動されます。<BR>
     * @return アクター発送者の暇そうなメンバーアクター
     */
    virtual GgafCore::GgafMainActor* employ() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDispatcher::getFreeOne() 子がありません");
        }
#endif
        static GgafMainActor* pActor;
        pActor = getSubFirst();

        while(true) {
            if (pActor->isActive() || pActor->_is_active_flg_in_next_frame || pActor->_on_change_to_inactive_flg) {
                //今活動中、或いは、次フレーム活動予定の場合は見送る
                if (pActor->isLast()) {
                    pActor = NULL;
                    break;
                } else {
                    pActor = pActor->getNext();
                    continue;
                }
            } else {
                //pActor->activate(); //activateは呼び元で明示的に行うようにした
                pActor->moveLast(); //取得！
                break;
            }
        }
        return pActor;
    }

    virtual ~GgafActorDispatcher() {
    }
};

}
#endif /*ACTORDISPATCHER_H_*/
