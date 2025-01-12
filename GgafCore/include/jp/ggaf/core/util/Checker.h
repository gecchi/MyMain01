#ifndef GGAF_CORE_CHECKER_H_
#define GGAF_CORE_CHECKER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/actor/Actor.h"
#include "jp/ggaf/core/util/lineartree/ITreeNodeElem.hpp"

#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * チェッククラス.
 * 八分木要素になります。
 * @version 1.00
 * @since 2024/09/26
 * @author Masatoshi Tsuge
 */
class Checker : public Object, public ITreeNodeElem {

public:
    /** チェック対象 */
    Actor* const _pActor;
    /** 拡張チェック、nullptr でなければチェックされる */
    Checker* _pNextExChecker;
public:
    /**
     * チェッカー生成 .
     * @param prm_pActor チェック対象
     */
    Checker(Actor* prm_pActor, kind_t prm_kind = 0);

    /**
     * 自チェッカーと他チェッカーの１対１の当たり判定処理を行う。
     * @param prm_pOppHitChecker 他チェッカー
     */
    virtual void executeHitChk_MeAnd(Checker* prm_pOppHitChecker) {
        if (prm_pOppHitChecker == this) {
            return;
        } else {
            //ヒットできる物どうかの判定は事前にすんでいるようにする事。
            if (processHitChkLogic(prm_pOppHitChecker)) { //自身のヒットチェック
                _pActor->onHit(this, prm_pOppHitChecker); //自分のヒット時の振る舞い
                prm_pOppHitChecker->_pActor->onHit(prm_pOppHitChecker, this); //相手のヒット時の振る舞い
            }
        }
    }

    /**
     * 自アクターと何かのアクターと衝突したかどうか判定するロジック。 .
     * executeHitChk_MeAnd(Actor*) が実行された場合に呼び出されることになる。<BR>
     * 下位クラスで独自に衝突判定ロジックを実装する。<BR>
     * このメソッドは何時呼び出されるかは決まっていない。呼び出しタイミングも下位クラス依存。<BR>
     * 想定としては、processJudgement() メソッドを実装したクラスが、その中で本メソッドを呼び出すものとしている。<BR>
     * もしそのように実装した場合、相手アクターも processJudgement() でこちらのアクターとの衝突判定を行うことになれば、<BR>
     * 衝突判定処理重複することになる。どーしたらよいか考えること。<BR>
     * @param	prm_pOppHitChecker　相手チェッカー
     * @retval	true	衝突しているを返す事
     * @retval	false	衝突していないを返す事
     */
    virtual bool processHitChkLogic(Checker* prm_pOppHitChecker) {
        return false;
    }


    /**
     * デフォルトチェッカーの _pNextExChecker に拡張チェッカーを追加
     * @return 拡張チェッカー
     */
    virtual Checker* addExChecker(kind_t prm_kind = 0);

    ~Checker();

};

}
#endif /*GGAF_CORE_CHECKER_H_*/

