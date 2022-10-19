#ifndef GGAF_LIB_COLLISIONCHECKER2D_B_H_
#define GGAF_LIB_COLLISIONCHECKER2D_B_H_
#include "GgafLibCommonHeader.h"
#include "CollisionChecker.h"

#include "jp/ggaf/core/util/TreeElem.hpp"
namespace GgafLib {

/**
 * 2D用衝突(Board用)チェッカークラス.
 * @version 1.00
 * @since 2022/09/13
 * @author Masatoshi Tsuge
 */
class CollisionChecker2D_b : public GgafDx::Checker {

    GgafCore::LinearQuadtree_b* const _pLinearQuadtree_b; //TODO:どこに持たせようか悩むがとりあえずココに

public:
    /** 線形八分木登録用要素 */
    GgafCore::TreeElem<2u>* const _pElem;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  当たり判定機能を追加するActor
     */
    explicit CollisionChecker2D_b(GgafDx::GeometricActor* prm_pActor);

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
    bool isHit(const GgafDx::Checker* const prm_pOppChecker) override;


    /**
     * 当たり判定領域要素を軸平行直方体として定義 .
     * @param prm_index 当たり判定領域の要素番号
     * @param x1 当たり判定直方体の左上X座標（Actorローカル座標）
     * @param y1 当たり判定直方体の左上Y座標（Actorローカル座標）
     * @param x2 当たり判定直方体の右下X座標（Actorローカル座標）
     * @param y2 当たり判定直方体の右下奥Y座標（Actorローカル座標）
     */
    void setColliAABox(int prm_index,
                       coord x1, coord y1,
                       coord x2, coord y2 );


    void setColliAABox(int prm_index,
                       double per_x, double pre_y);
    void setColliAABox(int prm_index,
                       double per);

    void setColliSquare(int prm_index, coord prm_edge);

    static void drawHitArea(GgafDx::Checker* prm_pChecker);
    static void releaseHitArea();

    virtual ~CollisionChecker2D_b();
};

}
#endif /*GGAF_LIB_COLLISIONCHECKER2D_B_H_*/

