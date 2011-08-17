#ifndef GGAFDX9COLLISIONAREA_H_
#define GGAFDX9COLLISIONAREA_H_
namespace GgafDx9Core {

/**
 * 当たり判定領域クラス .
 * 当たり判定要素、当たり判定領域、という２つの言葉を次のように定義します。<BR>
 * 当たり判定要素 ・・・ １つの 球 or AAB or プリズム の当たり判定。<BR>
 * 当たり判定領域 ・・・ 複数の当たり判定要素が集まって、グループ化した物<BR>
 * 本クラスは当たり判定「領域」を実装したクラスです。<BR>
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CollisionArea : public GgafCore::GgafObject {

public:
    /** 8分木登録のための全当たり判定要素含む全体の外側の軸並行境界直方体 */
    coord _AABB_X1, _AABB_Y1, _AABB_Z1, _AABB_X2, _AABB_Y2, _AABB_Z2;
    //AABB(軸並行境界直方体:Axis-Aligned Bounding Box)

    /** 当たり判定領域要素の配列 */
    GgafDx9CollisionPart** _papColliPart;
    /** 当たり判定領域要素数 */
    int _nColliPart;

    /**
     * コンストラクタ .
     * @param prm_nColliPart 当たり判定領域要素数
     * @return
     */
    GgafDx9CollisionArea(int prm_nColliPart);

    /**
     * 全当たり判定要素含む最外域の軸並行境界直方体を再計算 .
     */
    virtual void updateAABB();

    virtual ~GgafDx9CollisionArea();
};

}
#endif /*GGAFDX9HITAREA_H_*/
