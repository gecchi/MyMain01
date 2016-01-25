#ifndef GGAFLIB_COLIAABOX_H_
#define GGAFLIB_COLIAABOX_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

namespace GgafLib {

/**
 * 軸平行直方体 (Axis-Aligned Box) 当たり判定要素クラス
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliAABox : public GgafDxCore::GgafDxCollisionPart {

public:
    ColliAABox();

    /**
     *
     * @param x1
     * @param y1
     * @param z1
     * @param x2
     * @param y2
     * @param z2
     * @param rot_x
     * @param rot_y
     * @param rot_z
     */
    void set(coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, bool rot_x, bool rot_y, bool rot_z);

    void rotateRxRzRy(angle rx, angle ry, angle rz) override;

    virtual ~ColliAABox();
};

}
#endif /*GGAFLIB_COLIAABOX_H_*/
