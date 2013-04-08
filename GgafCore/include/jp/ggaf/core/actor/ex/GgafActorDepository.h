#ifndef GGAFACTORDEPOSITORY_H_
#define GGAFACTORDEPOSITORY_H_
namespace GgafCore {

/**
 * アクター保管所（人材バンク）クラス .
 * 自アクターのサブに予め幾つかアクターを登録(addSubLast)してストックする。<BR>
 * dispatch() メソッドが呼び出されると、デポジトリ内の活動していないアクター探して提供する。<BR>
 * アクターは使い終わったらinactivate()すると、ストックに戻ったことになる。<BR>
 * 弾など何度も使いまわしたいアクターや、出現数制限したい場合等に有効となるハズである。<BR>
 * 連続 dispatch() の場合、次のdispatch()のアクター必ずツリーの隣同士となっているという法則がある。<BR>
 * これは、dispatch() したアクターは、ストック並びの一番最後に回されるため。<BR>
 * ポリライン（レーザー）のひと纏まりの単位として使用できるかもしれない、と目論む。<BR>
 * (旧RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorDepository : public GgafDummyActor {
public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pStat
     */
    GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat = nullptr);

    /**
     * 貸出メンバー(GgafActor)を追加登録します.
     * ストックの追加的なイメージです。<BR>
     * GgafNode<T>::addSubLast() を実行する前に、アクター種別のを引き継ぎを行います。
     * 最初に登録したアクターの種別が、本デポジトリの種別となります。
     * それ以降は同じ種別のアクターを登録する制限があります。<BR>
     * また、引数のアクターには inactivateImmed() が実行され、メンバーは非活動状態に強制されます。<BR>
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
     * メンバー借り入れを試み、借り入れできれば取得し活動状態にする。 .
     * 暇そうなメンバー（active中、またはactive予約されていない）が存在すれば、
     * 取得し、活動状態にする（遅延設定可）。<BR>
     * 暇なメンバーが居ない場合 nullptr が返ります。<BR>
     * 取得できる場合、アクターに activate()が実行され、ポインタを返すと共に、
     * そのアクターはアクター発送者のサブの一番後ろに移動されます。<BR>
     * 一時的にキャラを派遣するようなイメージ<BR>
     * ＜使用例＞
     * <pre><code>
     * GgafMainActor* pActor = pDepository->dispatch();
     * if (pActor) {
     *     //アクターの初期処理
     *     //・・・
     *
     * }
     *
     * </code></pre>
     *
     * @param prm_offset_frames 活動状態にする遅延フレーム
     * @return アクター発送者の暇そうなメンバーアクターのポインタ
     */
    virtual GgafCore::GgafMainActor* dispatch(int prm_offset_frames = 1) {
#ifdef MY_DEBUG
        if (_pSubFirst == nullptr) {
            throwGgafCriticalException("GgafActorDepository::dispatch() this="<<getName()<<"("<<this<<") の子がありません");
        }
        if (_is_active_flg == true || (_will_activate_after_flg == true && _frame_of_life+1 == _frame_of_life_when_activation)) {
            //活動フラグが立っている→問題無し
            //あるいは、次フレームで活動フラグが立つ予定→デポジトリを作った直後の同一フレーム内処理のため許可
        } else {
            //＜ココに来る場合で、想定内パターンは次のような場合＞
            //① レーザーチップのセット借り入れで、GgafActorDepositoryStore::dispatch() を行い、チップのセットのデポジトリを得たが、直ぐに使用せず１フレーム以上ほっといた後、
            //   得たデポジトリから、チップdispatch()しようとした場合。
            //     → この場合、以下の警告メッセージが連続で表示されることになるので修正しなければならない。
            throwGgafCriticalException("GgafActorDepository::dispatch() this="<<getName()<<"("<<this<<") が非活動な雰囲気です。");
        }
#endif
        frame offset_frames = (prm_offset_frames < 1 ? 1 : prm_offset_frames);
        GgafMainActor* pActor = (GgafMainActor*)_pSubFirst;
        while (true) {
            if (pActor->_is_active_flg == false && pActor->_will_activate_after_flg == false) {
                pActor->moveLast(); //次フレームお尻に回す
                pActor->activateDelay(offset_frames); //activate自動実行。

                break;//取得！
            } else {   //今活動中、或いは、次フレーム活動予定の場合は見送る
                if (pActor->_is_last_flg) {
                    pActor = nullptr;
                    break;
                } else {
                    pActor = (GgafMainActor*)(pActor->_pNext);
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
     * isActiveInTheTree() == true の状態もありうるため、onActive() コールバックは
     * 呼ばれない可能性がある。<BR>
     * 強制的にonActive() コールバックを呼び出したい場合に次のようなコードに
     * しなければいけないかも知れない。
     * <pre><code>
     * GgafMainActor* pActor = pDepository->dispatchForce();
     * if (pActor->isActiveInTheTree()) {
     *     pActor->inactivateImmed();
     *     pActor->onActive();
     * }
     * pActor->active();
     * </code></pre>
     *
     * @param prm_offset_frames 活動状態にする遅延フレーム
     * @return
     */
    virtual GgafMainActor* dispatchForce(frame prm_offset_frames = 1) {
        GgafMainActor* pActor = dispatch(prm_offset_frames);
        if (pActor == nullptr) {
            getSubFirst()->moveLastImmed(); //お尻に回す
            pActor = (GgafMainActor*)getSubFirst();
        }
        return pActor;
    }

    /**
     * リセット時の処理 .
     * メンバーを全てinactivateImmed()します。
     */
    virtual void onReset() override;

    virtual void end(frame prm_offset_frames = 1) override;

    virtual ~GgafActorDepository() {
    }
};

}
#endif /*GGAFACTORDEPOSITORY_H_*/
