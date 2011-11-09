#ifndef COLLISPHERE_H_
#define COLLISPHERE_H_
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

    ColliSphere();

    void set(coord x, coord y, coord z, coord r, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliSphere();
};

}
#endif /*COLLISPHERE_H_*/