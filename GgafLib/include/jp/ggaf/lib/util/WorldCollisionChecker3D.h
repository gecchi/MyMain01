#ifndef GGAF_LIB_WORLDCOLLISIONCHECKER3D_H_
#define GGAF_LIB_WORLDCOLLISIONCHECKER3D_H_
#include "GgafLibCommonHeader.h"
#include "WorldCollisionChecker.h"

#include "jp/ggaf/core/util/lineartree/LinearOctree.hpp"

namespace GgafLib {

/**
 * ワールド空間の3Dモード用衝突チェッカークラス.
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class WorldCollisionChecker3D : public WorldCollisionChecker {

    GgafCore::LinearOctree<GgafCore::Actor>* const _pWorldLinearOctree; //TODO:どこに持たせようか悩むがとりあえずココに

public:
    /** 線形八分木登録用要素 */
    GgafCore::LinearOctree<GgafCore::Actor>::NodeElem* const _pNodeElem;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  当たり判定機能を追加するActor
     */
    explicit WorldCollisionChecker3D(GgafDx::GeometricActor* prm_pActor);

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

    virtual ~WorldCollisionChecker3D();
};

}
#endif /*GGAF_LIB_WORLDCOLLISIONCHECKER3D_H_*/

