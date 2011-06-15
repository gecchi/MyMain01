#ifndef GGAFACTORDISPATCHERDISPATCHER_H_
#define GGAFACTORDISPATCHERDISPATCHER_H_
namespace GgafCore {

/**
 * アクターディスパッチャーのパッチャークラス .
 * GgafActorDispatcher は、サブの登録アクター(GgafActor)が暇そうなメンバーを employ() するのに対し、
 * GgafActorDispatcherDispatcher は、サブの登録ディスパッチャー(GgafActorDispatcher) の 登録アクター(GgafActor)が、
 * 全員暇しているディスパッチャーを優先的にemploy() する。
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorDispatcherDispatcher : public GgafActorDispatcher {

private :

    virtual void addSubLast(GgafActor* prm_pSub) override;

public:
    GgafActorDispatcherDispatcher(const char* prm_name);

    /**
     * ディスパッチャーを登録します.
     * 具体的には、addSubLast() を呼び出し、種別を引き継ぎます。
     * そのため、登録アクター済みディスパッチャーを登録して下さい。
     * @param prm_pSub 登録ディスパッチャー
     */
    virtual void addSubLast(GgafActorDispatcher* prm_pSub) {
        addSubLast((GgafActor*)prm_pSub);
    }


    /**
     * activate系は子アクターへは影響させない事をやめる。
     */
    virtual void activateTree() override {
        //２つ上の継承元の本来のactivateTree()を実行
        GgafDummyActor::activateTree();
    }

//    virtual void inactivateTree() override {
//        inactivate();
//    }
    /**
     * activate系は子アクターへは影響させない事をやめる。
     */
    virtual void activateTreeDelay(frame prm_offset_frames) override {
        //２つ上の継承元の本来のactivateTree()を実行
        GgafDummyActor::activateTreeDelay();
    }

//    virtual void inactivateTreeDelay(frame prm_offset_frames) override {
//        inactivateDelay(prm_offset_frames);
//    }

    /**
     * ディスパッチャー取り出し .
     * 暇そうなディスパッチャー（登録メンバーが全て暇なディスパッチャー）がいれば取得する。<BR>
     * 暇そうなディスパッチャー居ない場合 NULL が返ります。<BR>
     * 取得できる場合、ポインタを返すと共に、そのディスパッチャーはサブの一番後ろに移動されます。<BR>
     * ＜使用例＞
     * <pre><code>
     * GgafActorDispatcher* pDispatcher = pDispatcherDispatcher->employ();
     * if (pDispatcher) {
     *     GgafMainActor* pActor = pDispatcher->employ();
     *     if (pActor) {
     *         //アクターの初期処理
     *         //・・・
     *
     *         pActor->active();
     *     }
     * }
     *
     * </code></pre>
     * @return 暇そうなディスパッチャー or NULL
     */
    virtual GgafActorDispatcher* employ() override {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDispatcherDispatcher::employ() "<<getName()<<" の子がありません");
        }
#endif
        GgafActorDispatcher* pDispatcher = (GgafActorDispatcher*)getSubFirst();
        for (int i = 0; i <= 100000; i++) {
            if (pDispatcher->_active_member == 0) {
                pDispatcher->moveLast(); //お尻に回す
                _active_member++;
                break;//取得！
            } else {
                if (pDispatcher->isLast()) {
                    pDispatcher = NULL;
                    break;
                } else {
                    pDispatcher = (GgafActorDispatcher*)(pDispatcher->getNext());
                    continue;
                }
            }
#ifdef MY_DEBUG
            if (i == 100000) {
                throwGgafCriticalException("GgafActorDispatcherDispatcher::employ() "<<getName()<<" のメンバの末尾フラグが見つかりません。循環ループしている可能性があります。");
            }
#endif
        }
        return pDispatcher;
    }

    /**
     * 強制的にアクター取り出し .
     * アクター発送者の暇そうなサブメンバー（active中、またはactive予約されていない）が
     * 居なくても強制的に取得する。<BR>
     * employ() を試みて取り出せない場合、強制的に先頭のアクターを返します。<BR>
     * <b>＜注意＞</b><BR>
     * 取り出し後、アクターに active() を実行しても、そのアクターが既に
     * isActiveActor() == true の状態もありうるため、onActive() コールバックは
     * 呼ばれない可能性がある。<BR>
     * 強制的にonActive() コールバックを呼び出したい場合に次のようなコードに
     * しなければいけないかも知れない。
     * <pre><code>
     * GgafMainActor* pActor = pDispatcherDispatcher->employForce();
     * if (pActor->isActiveActor()) {
     *     pActor->inactivateImmediately();
     *     pActor->onInactive();
     * }
     * pActor->active();
     * </code></pre>
     *
     * @return
     */
    virtual GgafActorDispatcher* employForce() {
        GgafActorDispatcher* pDispatcher = employ();
        if (pDispatcher == NULL) {
            getSubFirst()->moveLastImmediately(); //お尻に回す
            pDispatcher = (GgafActorDispatcher*)getSubFirst();
        }
        return pDispatcher;
    }

    /**
     * リセット時の処理 .
     */
    virtual void onReset() override {

    }

    virtual ~GgafActorDispatcherDispatcher() {
    }
};

}
#endif /*GGAFACTORDISPATCHERDISPATCHER_H_*/
