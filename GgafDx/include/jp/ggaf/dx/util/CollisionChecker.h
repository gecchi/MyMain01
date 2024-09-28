#ifndef GGAF_DX_COLLISIONCHECKER_H_
#define GGAF_DX_COLLISIONCHECKER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/Checker.h"
#include <vector>

namespace GgafDx {

/**
 * 衝突（当たり判定）チェッカークラス .
 * （旧GeometryCollisionChecker）
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class CollisionChecker : public GgafCore::Checker {
public:
    /** 対象アクター */
    GeometricActor* const _pColliActor;
    /** 当たり判定領域 */
    CollisionArea* _pCollisionArea;

    std::vector<CollisionArea*> _vecCollisionArea;

public:
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    explicit CollisionChecker(GeometricActor* prm_pActor);

    /**
     * 当たり判定ロジック .
     * 当たり判定ロジックを実装している。<BR>
     * チェッカーオブジェクトがある場合、<BR>
     * CollisionChecker::isHit() で判定する。<BR>
     * チェッカーオブジェクトが無い場合、<BR>
     * ヒットしていないこととする。<BR>
     * @param prm_pOtherChecker 相手のチェッカー
     * @return true：ヒットしている／false：ヒットしていない
     */
    virtual bool processHitChkLogic(GgafCore::Checker* prm_pOtherChecker) override;

    /**
     * 当たり判定領域を更新し、その領域をツリーに登録 .
     */
    virtual void updateHitArea() {};

    /**
     * 当たり判定領域（現在有効となっているもの）を取得 .
     * @return 有効な当たり判定領域
     */
    inline CollisionArea* getCollisionArea() {
        return _pCollisionArea;
    }

    /**
     * 当たり判定領域を１つ生成して追加する。 .
     * 初めて本メソッドを実行すると、内部リストに保持され、その当たり判定領域が有効になります。
     * ２回目以降の実行は、生成した当たり判定領域を内部リストの末尾に追加します。（有効になりません）
     * @param prm_colli_part_num 当たり判定領域内の、当たり判定要素数(1～n)
     */
    virtual void addCollisionArea(int prm_colli_part_num);

    /**
     * 当たり判定領域を切り替える .
     * @param prm_index 当たり判定領域リストのインデックス。
     *                  最初の   addCollisionArea() に切り替え => 0 を設定
     *                  ２回目の addCollisionArea() に切り替え => 1 を設定
     *                  ３回目の addCollisionArea() に切り替え => 2 を設定
     *                  …
     */
    virtual void changeCollisionArea(int prm_index);

    /**
     * ヒットしているかどうか
     * @param prm_pOtherCollisionChecker 相手のチェッカー
     * @return
     */
    virtual bool isHit(const CollisionChecker* const prm_pOtherCollisionChecker) {
        return false;
    }

    /**
     * 当たり判定領域が適用されているアクターを取得 .
     * @return 当たり判定領域が適用されているアクター
     */
    virtual GeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_(FUNC_NAME<<" nullptrであるがよいのか！");
        }
        return _pColliActor;
    }

    virtual ~CollisionChecker();
};

}
#endif /*GGAF_DX_COLLISIONCHECKER_H_*/

