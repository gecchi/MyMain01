#ifndef GGAF_LIB_WORLDCOLLISIONCHECKER2D_H_
#define GGAF_LIB_WORLDCOLLISIONCHECKER2D_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "WorldCollisionChecker.h"

#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"

namespace GgafLib {

/**
 * ワールド空間の2Dモード用衝突チェッカークラス.
 * @version 1.00
 * @since 2017/08/04
 * @author Masatoshi Tsuge
 */
class WorldCollisionChecker2D : public WorldCollisionChecker {

public:

    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  当たり判定機能を追加するActor
     */
    explicit WorldCollisionChecker2D(GgafDx::GeometricActor* prm_pActor, kind_t prm_kind = 0);

    /**
     * 当たり判定領域BOXの回転平行移動と、八分木登録を行います .
     * 当たり判定機能を使用するには、このメソッドを毎フレーム実行する必要があります。<br>
     * しかし、フレームワークに組み込まれているため、実装者は特に気にする必要がない。<br>
     * 現在は GgafDx::GeometricActor::processSettlementBehavior から毎フレームコールされている。<br>
     * もし processSettlementBehavior() を下位でオーバーライドする場合は気を付けるべし！<br>
     */
    virtual void updateHitArea() override;

    /**
     * 自身の判定領域と他の当たり判定領域と接触しているか調べる
     * @param prm_pOppChecker 他の当たり判定領域
     * @return true:当たっている / false:当たっていない
     */
    bool isHit(const GgafDx::CollisionChecker* const prm_pOppChecker) override;

    virtual ~WorldCollisionChecker2D();
};

}
#endif /*GGAF_LIB_WORLDCOLLISIONCHECKER2D_H_*/

