#ifndef GGAF_LIB_COLLISPHERE_H_
#define GGAF_LIB_COLLISPHERE_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

namespace GgafLib {

/**
 * 球当たり判定要素クラス
 * @version 1.00
 * @since 2010/01/17
 * @author Masatoshi Tsuge
 */
class ColliSphere : public GgafDx::CollisionPart {

public:
    /** 半径 */
    coord _r;
    /** 半径の２乗 */
    double _rr;

public:
    ColliSphere();

    /**
     * 球当たり判定要素の設定 .
     * @param x      中心のローカルX座標
     * @param y      中心のローカルY座標
     * @param z      中心のローカルZ座標
     * @param r      半径
     * @param rot_x
     * @param rot_y
     * @param rot_z
     */
    void set(coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z);

    void changeR(coord r);

    void rotateRxRzRy(angle rx, angle ry, angle rz) override;

    virtual ~ColliSphere();
};

}
#endif /*GGAF_LIB_COLLISPHERE_H_*/
