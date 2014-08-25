#ifndef GGAFLIB_COLLISPHERE_H_
#define GGAFLIB_COLLISPHERE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

namespace GgafLib {

/**
 * 球当たり判定要素クラス
 * @version 1.00
 * @since 2010/01/17
 * @author Masatoshi Tsuge
 */
class ColliSphere : public GgafDxCore::GgafDxCollisionPart {

public:
    /** x座標 */
    coord _x;
    /** y座標 */
    coord _y;
    /** z座標 */
    coord _z;
    /** 半径 */
    coord _r;
    /** 半径の２乗 */
    double _rr;

public:
    ColliSphere();

    void set(coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z);

    void rotateRxRzRy(angle rx, angle ry, angle rz) override;

    virtual ~ColliSphere();
};

}
#endif /*GGAFLIB_COLLISPHERE_H_*/
