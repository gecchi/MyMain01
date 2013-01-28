#ifndef GGAFACTORDEPOSITORYSTORE_H_
#define GGAFACTORDEPOSITORYSTORE_H_
namespace GgafCore {

/**
 * アクターデポジトリの保管所クラス .
 * GgafActorDepository は、サブの登録アクター(GgafActor)が暇そうなメンバーを dispatch() するのに対し、
 * GgafActorDepositoryStore は、サブの登録デポジトリ(GgafActorDepository) の 登録アクター(GgafActor)が、
 * 全員暇にしているデポジトリを優先的に dispatch() します。
 * つまり、dispatch() で得られるオブジェクトが デポジトリ(GgafActorDepository)になります。
 * 簡単に言うとデポジトリのデポジトリです。<BR>
 * 【注意】<BR>
 * processFinal() で、サブデポジトリの登録メンバー全てが非活動ならば、そのサブデポジトリを非活動にする。<BR>
 * といういう処理がある。<BR>
 * 本オブジェクトで、dispatch() し、サブデポジトリを得た瞬間は、サブデポジトリのメンバー全員非活動である。<BR>
 * このまま何もしないと、そのフレームの processFinal() で、サブデポジトリのメンバーが全て非活動に戻ってしまい、
 * dispatch() した意味がなくなってしまう。<BR>
 * 本オブジェクトで、dispatch() したならば、得られたデポジトリから直ぐに最低一つはdispatch() し無ければいけない。<BR>
 * @version 1.00
 * @since 2011/06/15
 * @author Masatoshi Tsuge
 */
class GgafActorDepositoryStore : public GgafActorDepository {

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pStat
     */
    GgafActorDepositoryStore(const char* prm_name, GgafStatus* prm_pStat = nullptr);

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
