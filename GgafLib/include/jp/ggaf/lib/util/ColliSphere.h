#ifndef GGAFLIB_COLLISPHERE_H_
#define GGAFLIB_COLLISPHERE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

namespace GgafLib {

/**
 * �������蔻��v�f�N���X
 * @version 1.00
 * @since 2010/01/17
 * @author Masatoshi Tsuge
 */
class ColliSphere : public GgafDxCore::GgafDxCollisionPart {

public:
    /** x���W */
    coord _x;
    /** y���W */
    coord _y;
    /** z���W */
    coord _z;
    /** ���a */
    coord _r;
    /** ���a�̂Q�� */
    double _rr;

public:
    ColliSphere();

    void set(coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z);

    void rotateRxRzRy(angle rx, angle ry, angle rz) override;

    virtual ~ColliSphere();
};

}
#endif /*GGAFLIB_COLLISPHERE_H_*/
