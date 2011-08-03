#ifndef GGAFACTORSTORE_H_
#define GGAFACTORSTORE_H_
namespace GgafCore {

/**
 * アクターストアー（人材バンク）クラス .
 * 自アクターのサブに予め幾つかアクターを登録(addSubLast)してストックする。<BR>
 * 他からの dispatch() メソッドで、ストックの活動していないアクター探して提供する。<BR>
 * アクターは使い終わったらinactivate()すると、ストックに戻ったことになる。<BR>
 * 弾など何度も使いまわしたいアクターや、出現数制限したい場合等に有効となるハズである。<BR>
 * 連続dispatch()の場合、次のdispatch()のアクターは必ず隣同士となっているという法則がある。<BR>
 * これは、dispatch()したアクターは、ストック並びの一番最後に回されるため。<BR>
 * ポリライン（レーザー）のひと纏まりの単位として使用できるかもしれない、と目論む。<BR>
 * (旧RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorStore : public GgafDummyActor {
public:

    GgafActorStore(const char* prm_name);

    /**
     * 貸出メンバー(GgafActor)を追加登録します.
     * ストックの追加的なイメージです。<BR>
     * GgafNode<T>::addSubLast() を実行する前に、アクター種別のを引き継ぎを行います。
     * 最初に登録したアクターの種別が、本ストアーの種別となります。
     * それ以降は同じ種別のアクターを登録する制限があります。<BR>
     * また、引数のアクターには inactivateImmediately() が実行され、メンバーは非活動状態に強制されます。<BR>
     * @param prm_pSub 貸出メンバーアクター
     */
    virtual void addSubLast(GgafActor* prm_pSub) override;


    /**
     * activate系は子アクターへは影響させないようにする .
     * 子アクター（貸し出しメンバー）は、dispatch() でのみ活動状態にさせるため。
     */
    virtual void activateTree() override {
        activate();
    }

//    virtual void inactivateTree() override {
//        inactivate();
//    }
    /**
     * activate系は子アクターへは影響させないする .
     * 子アクター（貸し出しメンバー）は、dispatch() でのみ活動状態にさせるため。
     */
    virtual void activateTreeDelay(frame prm_offset_frames) override {
        activateDelay(prm_offset_frames);
    }

//    virtual void inactivateTreeDelay(frame prm_offset_frames) override {
//        inactivateDelay(prm_offset_frames);
//    }

    /**
     * メンバー借り入れ .
     * 暇そうなメンバー（active中、またはactive予約されていない）が存在すれば、取得し活動状態にする。<BR>
     * 暇なメンバーが居ない場合 NULL が返ります。<BR>
     * 取得できる場合、アクターに activate()が実行され、ポインタを返すと共に、そのアクターはアクター発送者のサブの一番後ろに移動されます。<BR>
     * 一時的にキャラを派遣するようなイメージ<BR>
     * ＜使用例＞
     * <pre><code>
     * GgafMainActor* pActor = pStore->dispatch();
     * if (pActor) {
     *     //アクターの初期処理
     *     //・・・
     *
     * }
     *
     * </code></pre>
     * @return アクター発送者の暇そうなメンバーアクター
     */
    virtual GgafCore::GgafMainActor* dispatch() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorStore::dispatch() "<<getName()<<" の子がありません");
        }
#endif
        GgafMainActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_is_active_flg == false && pActor->_will_activate_after_flg == false) {
                pActor->moveLast(); //次フレームお尻に回す
                pActor->activate(); //activate自動実行。
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
        }
        return pActor;
    }

    /**
     * 強制的にアクター取り出し .
     * アクター発送者の暇そうなサブメンバー（active中、またはactive予約されていない）が
     * 居ない場合は、活動中のメンバーを無理やり取得する。<BR>
     * dispatch() を試みて取り出せない場合、強制的にメンバー達の先頭メンバーを返します。<BR>
     * <b>＜注意＞</b><BR>
     * 取り出し後、アクターに active() を実行しても、そのアクターが既に
     * isActiveActor() == true の状態もありうるため、onActive() コールバックは
     * 呼ばれない可能性がある。<BR>
     * 強制的にonActive() コールバックを呼び出したい場合に次のようなコードに
     * しなければいけないかも知れない。
     * <pre><code>
     * GgafMainActor* pActor = pStore->dispatchForce();
     * if (pActor->isActiveActor()) {
     *     pActor->inactivateImmediately();
     *     pActor->onInactive();
     * }
     * pActor->active();
     * </code></pre>
     *
     * @return
     */
    virtual GgafCore::GgafMainActor* dispatchForce() {
        GgafMainActor* pActor = dispatch();
        if (pActor == NULL) {
            getSubFirst()->moveLastImmediately(); //お尻に回す
            pActor = getSubFirst();
        }
        return pActor;
    }

    /**
     * リセット時の処理 .
     * メンバーを全てinactivateImmediately()します。
     */
    virtual void onReset() override;

    virtual ~GgafActorStore() {
    }
};

}
#endif /*GGAFACTORSTORE_H_*/
