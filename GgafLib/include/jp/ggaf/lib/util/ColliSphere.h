#ifndef GGAF_LIB_COLLISPHERE_H_
#define GGAF_LIB_COLLISPHERE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

namespace GgafLib {

/**
 * �������蔻��v�f�N���X
 * @version 1.00
 * @since 2010/01/17
 * @author Masatoshi Tsuge
 */
class ColliSphere : public GgafDx::CollisionPart {

public:
    /** ���a */
    coord _r;
    /** ���a�̂Q�� */
    double _rr;

public:
    ColliSphere();

    /**
     * �������蔻��v�f�̐ݒ� .
     * @param x      ���S�̃��[�J��X���W
     * @param y      ���S�̃��[�J��Y���W
     * @param z      ���S�̃��[�J��Z���W
     * @param r      ���a
     * @param rot_x
     * @param rot_y
     * @param rot_z
     */
    void set(coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z);

    void rotateRxRzRy(angle rx, angle ry, angle rz) override;

    virtual ~ColliSphere();
};

}
#endif /*GGAF_LIB_COLLISPHERE_H_*/
