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
    Actor* const _pActor;
    /** 拡張 */
    Checker* _pNextChecker;
    /**
     * ステータスセットを作成 .
     * リセットメソッドを実行しステータス初期化を行います。
     * @param prm_pFunc_reset ステータスリセットメソッド
     */
    Checker(Actor* prm_pActor);

    /**
     * 自チェッカーと他チェッカーの１対１の当たり判定処理を行う。
     * @param prm_pOtherActor 他アクター
     */
    virtual void executeHitChk_MeAnd(Checker* prm_pOtherChecker) {
        if (prm_pOtherChecker == this) {
            return;
        } else {
            //ヒットできる物どうかの判定は事前にすんでいるようにする事。
            if (processHitChkLogic(prm_pOtherChecker)) { //自身のヒットチェック
                _pActor->onHit(prm_pOtherChecker, prm_pOtherChecker->_pActor); //自分のヒット時の振る舞い
                prm_pOtherChecker->_pActor->onHit(this, _pActor); //相手のヒット時の振る舞い
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
     * @param	prm_pOtherChecker　相手チェッカー
     * @retval	true	衝突しているを返す事
     * @retval	false	衝突していないを返す事
     */
    virtual bool processHitChkLogic(Checker* prm_pOtherChecker) {
        return false;
    }

    ~Checker();

};

}
#endif /*GGAF_CORE_CHECKER_H_*/

