#ifndef GGAFLIB_COLIAAB_H_
#define GGAFLIB_COLIAAB_H_
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

namespace GgafLib {

/**
 * AAB(�����s�����́FAxis-Aligned Box)�����蔻��v�f�N���X
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliAAB : public GgafDxCore::GgafDxCollisionPart {
public:
    /** AAB��x���W�̏������� */
    coord _x1;
    /** AAB��y���W�̏������� */
    coord _y1;
    /** AAB��z���W�̏������� */
    coord _z1;
    /** AAB�̑Ίp�̒��_�ƂȂ�x���W�傫���� */
    coord _x2;
    /** AAB�̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    coord _y2;
    /** AAB�̑Ίp�̒��_�ƂȂ�z���W�傫���� */
    coord _z2;

public:
    ColliAAB();

    void set(coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, bool rot_x, bool rot_y, bool rot_z);

    void rotateRxRzRy(angle rx, angle ry, angle rz) override;

    virtual ~ColliAAB();
};

}
#endif /*GGAFLIB_COLIAAB_H_*/
