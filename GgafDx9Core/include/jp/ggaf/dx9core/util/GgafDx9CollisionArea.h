#ifndef GGAFDX9COLLISIONAREA_H_
#define GGAFDX9COLLISIONAREA_H_
namespace GgafDx9Core {

/**
 * 当たり判定領域インターフェイスクラス(新)
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CollisionArea : public GgafCore::GgafObject {

public:
    /** 各当たり判定要素含む全体の外側の境界BOX(8分木登録のため) */
    int _AABB_X1, _AABB_Y1, _AABB_Z1, _AABB_X2, _AABB_Y2, _AABB_Z2;

    /** 各当たり判定要素の配列 */
    GgafDx9CollisionPart** _papColliPart;
    /** 全たり判定要素数 */
    int _nColliPart;


    GgafDx9CollisionArea(int prm_nColliPart);

    void updateAABB();


    virtual ~GgafDx9CollisionArea();
};

}
#endif /*GGAFDX9HITAREA_H_*/
