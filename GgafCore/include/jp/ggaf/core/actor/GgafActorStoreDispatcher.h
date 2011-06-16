#ifndef GGAFACTORSTOREDISPATCHER_H_
#define GGAFACTORSTOREDISPATCHER_H_
namespace GgafCore {

/**
 * アクターストアーのストアークラス .
 * GgafActorStore は、サブの登録アクター(GgafActor)が暇そうなメンバーを dispatch() するのに対し、
 * GgafActorStoreDispatcher は、サブの登録ストアー(GgafActorStore) の 登録アクター(GgafActor)が、
 * 全員暇しているストアーを優先的にdispatch() する。
 * @version 1.00
 * @since 2011/06/15
 * @author Masatoshi Tsuge
 */
class GgafActorStoreDispatcher : public GgafActorStore {

private :


public:
    GgafActorStoreDispatcher(const char* prm_name);

    /**
     * ストアーを登録します.
     * GgafActorStore::addSubLast() を呼び出前にチェックを行います。
     * そのため、登録アクター済みストアーを登録して下さい。
     * @param prm_pSub 登録ストアー
     */
    virtual void addSubLast(GgafActor* prm_pSub) override;

    /**
     * サブの登録ストアーの状態更新 .
     * 非活動にできるサブストアーがいれば非活動にする。
     * 非活動にできる条件は、サブストアーの登録メンバー全てが非活動であること。
     */
    virtual void processFinal() override;

    virtual ~GgafActorStoreDispatcher() {
    }
};

}
#endif /*GGAFACTORSTOREDISPATCHER_H_*/
