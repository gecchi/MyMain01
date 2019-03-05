#ifndef GGAF_LIB_COLIAABOX_H_
#define GGAF_LIB_COLIAABOX_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

namespace GgafLib {

/**
 * �����s������ (Axis-Aligned Box) �����蔻��v�f�N���X
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliAABox : public GgafDx::CollisionPart {
public:
    /** �|�W�V������� */
    pos_t _pos_info;

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

    void setWithChengePos(coord cx, coord cy, coord cz);

    void rotateRxRzRy(angle rx, angle ry, angle rz) override;

    virtual ~ColliAABox();
};

}
#endif /*GGAF_LIB_COLIAABOX_H_*/
