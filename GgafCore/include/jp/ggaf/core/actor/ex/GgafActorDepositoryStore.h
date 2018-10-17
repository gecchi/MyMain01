#ifndef GGAFCORE_GGAFACTORDEPOSITORYSTORE_H_
#define GGAFCORE_GGAFACTORDEPOSITORYSTORE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

namespace GgafCore {

/**
 * アクターデポジトリの保管所クラス .
 * GgafActorDepository は、子の登録アクター(GgafActor)が暇そうなメンバーを dispatch() するのに対し、
 * GgafActorDepositoryStore は、子の登録デポジトリ(GgafActorDepository) の 登録アクター(GgafActor)が、
 * 全員暇にしているデポジトリを優先的に dispatch() します。
 * つまり、dispatch() で得られるオブジェクトが デポジトリ(GgafActorDepository)になります。
 * 要はデポジトリのデポジトリです。<BR>
 * 【注意】<BR>
 * processFinal() で、子デポジトリの登録メンバー全てが非活動ならば、その子デポジトリを非活動にする。<BR>
 * といういう処理がある。<BR>
 * よって本オブジェクトのdispatch() を実行し、子のデポジトリを得た瞬間は、そのデポジトリのメンバー全員非活動である。（当然といえば当然）<BR>
 * このまま何もしないと、そのフレームの processFinal() で、子デポジトリのメンバーが活動終了とみなされ、全て非活動に戻ってしまい、
 * dispatch() した意味がなくなってしまう。<BR>
 * 本オブジェクトで、dispatch() したならば、得られたデポジトリから直ぐに最低一つはactiveにする必要がある。（つまりその得たリポジトリからdispatch()する）。<BR>
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
     * GgafActorDepository::appendChild() を呼び出前にチェックを行います。
     * そのため、登録アクター済みデポジトリを登録して下さい。
     * @param prm_pChild 登録デポジトリ
     */
    virtual void put(GgafActor* prm_pChild) override;

    /**
     * 子の登録デポジトリの状態更新 .
     * 非活動にできる子デポジトリがいれば非活動にする。
     * 非活動にできる条件は、子デポジトリの登録メンバー全てが非活動であること。
     */
    virtual void processFinal() override;

    virtual ~GgafActorDepositoryStore() {
    }
};

}
#endif /*GGAFCORE_GGAFACTORDEPOSITORYSTORE_H_*/
