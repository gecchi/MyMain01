﻿#ifndef ACTORDISPATCHER_H_
#define ACTORDISPATCHER_H_
namespace GgafCore {

/**
 * アクター発送者クラス .
 * ツリーの子に予め幾つかアクターを登録(addSubLast)してストックする。<BR>
 * employ() メソッドで、ストックの活動していないアクター探して提供する。<BR>
 * アクターは使い終わったらinactivate()すると、ストックに戻ったことになる。<BR>
 * 弾など何度も使いまわしたいアクターや、出現数制限したい場合等に有効となるハズである。<BR>
 * 連続employ()の場合、次のemploy()のアクターは必ず隣同士となっているという法則がある。<BR>
 * これは、employ()したアクターは、ストック並びの一番最後に回されるため。<BR>
 * ポリライン（レーザー）のひと纏まりの単位として使用できるかもしれない、と目論む。<BR>
 * (旧RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorDispatcher : public GgafDummyActor {

public:
    GgafActorDispatcher(const char* prm_name);

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
     * ＜使用例＞
     * <code>
     * GgafMainActor* pActor = pDispatcher->employForce();
     * if (pActor != NULL) {
     *     //アクターの初期処理
     *     //・・・
     *
     *     pActor->active();
     * }
     *
     * </code>
     * @return アクター発送者の暇そうなメンバーアクター
     */
    virtual GgafCore::GgafMainActor* employ() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDispatcher::employ() 子がありません");
        }
#endif
        static GgafMainActor* pActor;
        pActor = getSubFirst();

        for (int i = 0; i <= 100000; i++) {
            if (pActor->_is_active_flg == false &&  pActor->_is_active_flg_in_next_frame == false &&  pActor->_on_change_to_inactive_flg == false) {
                //pActor->activate(); //activateは呼び元で明示的に行うようにした
                pActor->moveLast(); //お尻に回す
                break;//取得！
            } else {   //今活動中、或いは、次フレーム活動予定の場合は見送る
                if (pActor->isLast()) {
                    pActor = NULL;
                    break;
                } else {
                    pActor = pActor->getNext();
                    continue;
                }
            }
#ifdef MY_DEBUG
            if (i == 100000) {
                throwGgafCriticalException("GgafActorDispatcher::employ() 末尾フラグが見つかりません。循環ループしている可能性があります。");
            }
#endif
        }
        return pActor;
    }

    /**
     * 強制的にアクター取り出し .
     * employ() を試みて取り出せない場合、強制的に先頭のアクターを返します。
     * 注意：取り出し後、アクターに active() としても、そのアクターが既に
     * isActive() == true の状態もありうるため、onActive() コールバックは
     * 呼ばれない可能性がある。
     * 強制的にonActive() コールバックを呼び出したい場合に次のようなコードに
     * しなければいけないかも知れない。
     * <code>
     * GgafMainActor* pActor = pDispatcher->employForce();
     * if (pActor->isActive()) {
     *     pActor->inactivateImmediately();
     *     pActor->onInactive();
     * }
     * pActor->active();
     * </code>
     *
     * @return
     */
    virtual GgafCore::GgafMainActor* employForce() {
        GgafMainActor* pActor = employ();
        if (pActor == NULL) {
            pActor = getSubFirst();
        }
        return pActor;

    }

    virtual ~GgafActorDispatcher() {
    }
};

}
#endif /*ACTORDISPATCHER_H_*/
