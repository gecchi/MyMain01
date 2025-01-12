#ifndef GGAF_VIEWCOLLISIONCHECKER_H_
#define GGAF_VIEWCOLLISIONCHECKER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "WorldCollisionChecker.h"

#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"

namespace GgafLib {

/**
 * 画面2D用衝突チェッカークラス.
 * @version 1.00
 * @since 2022/09/13
 * @author Masatoshi Tsuge
 */
class ViewCollisionChecker : public GgafDx::CollisionChecker {

public:
#ifdef MY_DEBUG
    /** １フレームの当たり判定要素同士の判定回数 */
    static unsigned int _num_check;

    static unsigned int _num_check_actors;
#endif

    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  当たり判定機能を追加するActor
     */
    explicit ViewCollisionChecker(GgafDx::GeometricActor* prm_pActor, kind_t prm_kind = 0);

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
    bool isHit_old(const GgafDx::CollisionChecker* const prm_pOppChecker) ;

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

    static void drawHitArea(GgafDx::CollisionChecker* prm_pColliChecker);
    static void releaseHitArea();

    virtual ~ViewCollisionChecker();
};

}
#endif /*GGAF_VIEWCOLLISIONCHECKER_H_*/

