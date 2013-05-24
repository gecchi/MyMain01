#ifndef GGAFDXCOLLISIONAREA_H_
#define GGAFDXCOLLISIONAREA_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * 当たり判定領域クラス .
 * 当たり判定要素、当たり判定領域、という２つの言葉を次のように定義します。<BR>
 * a)当たり判定要素 ・・・ １つの 球 or AAB or プリズム の当たり判定の立体図形。<BR>
 * b)当たり判定領域 ・・・ 上記の複数の当たり判定要素が集まって、グループ化した物。<BR>
 * 本クラスは b) 当たり判定「領域」を実装したクラスです。<BR>
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDxCollisionArea : public GgafCore::GgafObject {

public:
    /** 8分木登録のための全当たり判定要素含む全体の外側の軸平行境界直方体 */
    coord _AABB_X1, _AABB_Y1, _AABB_Z1, _AABB_X2, _AABB_Y2, _AABB_Z2;
    //AABB(軸平行境界直方体:Axis-Aligned Bounding Box)

    /** 当たり判定領域要素の配列 */
    GgafDxCollisionPart** _papColliPart;
    /** 当たり判定領域要素数 */
    int _colli_part_num;

    int _hit_colli_part_index;

public:
    /**
     * コンストラクタ .
     * @param prm_colli_part_num 当たり判定領域要素数
     * @return
     */
    GgafDxCollisionArea(int prm_colli_part_num);

    /**
     * 全当たり判定要素含む最外域の軸平行境界直方体を再計算 .
     */
    virtual void updateAABB();

    virtual ~GgafDxCollisionArea();
};

}
#endif /*GGAFDXHITAREA_H_*/
