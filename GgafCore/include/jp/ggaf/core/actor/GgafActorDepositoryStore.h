#ifndef GGAFACTORDEPOSITORYSTORE_H_
#define GGAFACTORDEPOSITORYSTORE_H_
namespace GgafCore {

/**
 * アクターデポジトリのデポジトリクラス .
 * GgafActorDepository は、サブの登録アクター(GgafActor)が暇そうなメンバーを dispatch() するのに対し、
 * GgafActorDepositoryStore は、サブの登録デポジトリ(GgafActorDepository) の 登録アクター(GgafActor)が、
 * 全員暇しているデポジトリを優先的にdispatch() する。
 * @version 1.00
 * @since 2011/06/15
 * @author Masatoshi Tsuge
 */
class GgafActorDepositoryStore : public GgafActorDepository {

private :


public:
    GgafActorDepositoryStore(const char* prm_name);

    /**
     * デポジトリを登録します.
     * GgafActorDepository::addSubLast() を呼び出前にチェックを行います。
     * そのため、登録アクター済みデポジトリを登録して下さい。
     * @param prm_pSub 登録デポジトリ
     */
    virtual void addSubLast(GgafActor* prm_pSub) override;

    /**
     * サブの登録デポジトリの状態更新 .
     * 非活動にできるサブデポジトリがいれば非活動にする。
     * 非活動にできる条件は、サブデポジトリの登録メンバー全てが非活動であること。
     */
    virtual void processFinal() override;

    virtual ~GgafActorDepositoryStore() {
    }
};

}
#endif /*GGAFACTORDEPOSITORYSTORE_H_*/
