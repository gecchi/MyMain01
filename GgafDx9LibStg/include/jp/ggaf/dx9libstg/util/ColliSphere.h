#ifndef COLLISPHERE_H_
#define COLLISPHERE_H_
namespace GgafDx9LibStg {

/**
 * �������蔻��v�f�N���X
 * @version 1.00
 * @since 2010/01/17
 * @author Masatoshi Tsuge
 */
class ColliSphere : public GgafDx9Core::GgafDx9CollisionPart {
public:
    /** x���W */
    int _x;
    /** y���W */
    int _y;
    /** z���W */
    int _z;
    /** ���a */
    int _r;
    /** ���a�̂Q�� */
    double _rr;

    ColliSphere();

    void set(int x, int y, int z, int r, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliSphere();
};

}
#endif /*COLLISPHERE_H_*/
