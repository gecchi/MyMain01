#ifndef GGAF_CORE_ACTORDEPOSITORY_H_
#define GGAF_CORE_ACTORDEPOSITORY_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include <typeinfo>
#include "jp/ggaf/core/actor/ex/DestructActor.h"

namespace GgafCore {

/**
 * アクター保管所（人材バンク）クラス .
 * 自アクターの子に予め幾つかアクターを登録(appendChild)してストックする。<BR>
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
class ActorDepository : public DestructActor {
private:
    //使用不可
    void appendChild(Actor* prm_pChild) override {
    }

public:
    /**
     * コンストラクタ .
     * @param prm_name
     */
    ActorDepository(const char* prm_name);

    /**
     * 貸出メンバー(Actor)を追加登録します .
     * ストックの追加的なイメージです。<BR>
     * Node<T>::appendChild() を実行する前に、アクター種別のを引き継ぎを行います。
     * 最初に登録したアクターの種別が、本デポジトリの種別となります。
     * それ以降は同じ種別のアクターを登録する制限があります。<BR>
     * また、引数のアクターには inactivateImmed() が実行され、メンバーは非活動状態に強制されます。<BR>
     * @param prm_pChild 貸出メンバーアクター
     */
    virtual void put(Actor* prm_pChild);

    /**
     * 貸出メンバー(同じ型)を一気に追加登録します.
     * @param prm_num メンバー数
     */
    template <typename T>
    void putn(const int prm_num) {
        const char* type = typeid(T).name();
        for (int i = 0; i < prm_num; i++) {
            std::string name = std::string(type) + "("+XTOS(i)+")";
            put(NEW T(name.c_str()));
        }
    }

    /**
     * activate系は子アクターへは影響させないようにする .
     * 子アクター（貸し出しメンバー）は、dispatch() でのみ活動状態にさせるため。
     */
    virtual void activateTree() override {
        activate();
    }

    /**
     * activate系は子アクターへは影響させないする .
     * 子アクター（貸し出しメンバー）は、dispatch() でのみ活動状態にさせるため。
     */
    virtual void activateTreeDelay(frame prm_offset_frames) override {
        activateDelay(prm_offset_frames);
    }

    /**
     * メンバー借り入れを試み、借り入れできれば取得し活動状態にする。 .
     * 暇そうなメンバー（非active中、またはactive予約されていない）が存在すれば、
     * 取得し、活動状態にする（遅延設定可）。<BR>
     * 暇なメンバーが居ない場合 nullptr が返ります。<BR>
     * 取得できる場合、アクターに activate()が実行され、ポインタを返すと共に、
     * そのアクターはアクター発送者の子の一番後ろに移動されます。<BR>
     * 一時的にキャラを派遣するようなイメージ<BR>
     * ＜使用例＞
     * <pre><code>
     * MainActor* pActor = pDepository->dispatch();
     * if (pActor) {
     *     //アクターの初期処理
     *     //・・・
     *
     * }
     * </code></pre>
     *
     * @param prm_offset_frames 活動状態にする遅延フレーム
     * @return アクター発送者の暇そうなメンバーアクターのポインタ
     */
    virtual MainActor* dispatch(int prm_offset_frames = 1) {
#ifdef MY_DEBUG
        if (_pChildFirst == nullptr) {
            throwCriticalException("this="<<NODE_INFO<<" の子がありません");
        }
        if (_is_active_flg || _frame_of_life+1 == _frame_of_life_when_activation) {
            //活動フラグが立っている→問題無し
            //あるいは、次フレームで活動フラグが立つ予定→デポジトリを作った直後の同一フレーム内処理のため許可
        } else {
            //＜ココに来る場合で、想定内パターンは次のような場合＞
            //① レーザーチップのセット借り入れで、ActorDepositoryStore::dispatch() を行い、チップのセットのデポジトリを得たが、直ぐに使用せず１フレーム以上ほっといた後、
            //   得たデポジトリから、チップdispatch()しようとした場合。
            //     → この場合、以下の警告メッセージが連続で表示されることになるので修正しなければならない。
            throwCriticalException("this="<<NODE_INFO<<" が非活動なデポジトリにdispatch()した雰囲気です。");
        }
#endif
        frame offset_frames = (prm_offset_frames < 1 ? 1 : prm_offset_frames);
        MainActor* pActor = (MainActor*)_pChildFirst;
        while (true) {
            if (pActor->_is_active_flg == false && pActor->isActivateScheduled() == false) {
                //取得！
                pActor->moveLast(); //お尻に回す
                pActor->activateDelay(offset_frames); //activate自動実行。
                break;
            } else {   //今活動中、或いは、次フレーム活動予定の場合は見送る
                if (pActor->_is_last_flg) {
                    pActor = nullptr;
                    break;
                } else {
                    pActor = (MainActor*)(pActor->_pNext);
                    continue;
                }
            }
        }
        //TODO:ここでonDispatch() コールバック？
        return pActor;
    }

    /**
     * 強制的にアクター取り出し .
     * アクター発送者の暇そうな子メンバー（active中、またはactive予約されていない）が
     * 居ない場合は、活動中のメンバーを無理やり横取りして取得する。<BR>
     * dispatch() を試みて取り出せない場合、強制的にメンバー達の先頭メンバーを返します。<BR>
     * <b>＜注意＞</b><BR>
     * 取り出し後、アクターに active() を実行しても、そのアクターが既に活動状態の可能性があり、つまり
     * isActiveInTheTree() → true の状態もありうるため、onActive() コールバックは呼ばれない可能性がある。<BR>
     * そこで、即座に inactivateImmed() を実行し、無理やりに onInctive() コールバックを呼び出している。<BR>
     *
     * @param prm_offset_frames 活動状態にする遅延フレーム
     * @return アクター発送者の暇そうなメンバーアクターのポインタ、或いは、先頭のアクター
     */
    virtual MainActor* dispatchForce(int prm_offset_frames = 1) {
        MainActor* pActor = dispatch(prm_offset_frames);
        if (pActor == nullptr) {
            pActor = (MainActor*)getChildFirst(); //強制敵に先頭取得
            pActor->moveLast(); //お尻に回す
            frame offset_frames = (prm_offset_frames < 1 ? 1 : prm_offset_frames);
            pActor->inactivateImmed(); //即時非活性
            pActor->onInactive();      //nextFrame() で呼び出されるべき onInactive() が呼び出されないので、ここで呼ぶ
            pActor->activateDelay(offset_frames); //activate自動実行。
        }
        //TODO:ここでonDispatch() コールバック？
        return pActor;
    }

    /**
     * リセット時の処理 .
     * メンバーを全てinactivateImmed()します。
     */
    virtual void onReset() override;

    virtual void end(frame prm_offset_frames = 1) override;

    virtual ~ActorDepository() {
    }
};

}
#endif /*GGAF_CORE_ACTORDEPOSITORY_H_*/
