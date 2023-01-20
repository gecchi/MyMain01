#ifndef GGAF_DX_COLLISIONCHECKER_H_
#define GGAF_DX_COLLISIONCHECKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafDx {

/**
 * 衝突（当たり判定）チェッカークラス .
 * （旧GeometryCollisionChecker）
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class CollisionChecker : public GgafCore::Object {
public:
    /** 対象アクター */
    GeometricActor* const _pActor;
    /** 当たり判定領域 */
    CollisionArea* _pCollisionArea;
public:
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    explicit CollisionChecker(GeometricActor* prm_pActor);

    /**
     * 当たり判定領域を更新し、その領域をツリーに登録 .
     */
    virtual void updateHitArea() = 0;

    /**
     * 当たり判定領域を作成する（＝当たり判定領域要素の配列を作成する） .
     * 内部で領域の配列を生成します。
     * 最初に必ず実行してください。
     * @param prm_colli_part_num 当たり判定領域の当たり判定領域要素数(1～n)
     */
    virtual void createCollisionArea(int prm_colli_part_num);

    /**
     * ヒットしているかどうか
     * @param prm_pOtherCollisionChecker 相手のチェッカー
     * @return
     */
    virtual bool isHit(const CollisionChecker* const prm_pOtherCollisionChecker) = 0;

    virtual GeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_(FUNC_NAME<<" nullptrであるがよいのか！");
        }
        return _pActor;
    }

    inline CollisionArea* getArea() {
        return _pCollisionArea;
    }

    /**
     * 当たり判定領域の要素を有効にする。
     * デフォルトは有効状態になっています。
     * @param prm_index 有効にする当たり判定領域の要素番号
     */
    virtual void enable(int prm_index);

    /**
     * 当たり判定領域の要素を無効にする。
     * @param prm_index 無効にする当たり判定領域の要素番号
     */
    virtual void disable(int prm_index);

    /**
     * 当たり判定領域の要素が有効か調べる。
     * @param prm_index 調べたい当たり判定領域の要素番号
     * @return true:有効 / false:無効
     */
    virtual bool isEnable(int prm_index);

    virtual ~CollisionChecker();
};

}
#endif /*GGAF_DX_COLLISIONCHECKER_H_*/

