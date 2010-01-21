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
    int _x1;
    /** y���W */
    int _y1;
    /** z���W */
    int _z1;
    /** ���a */
    int _r;

    ColliSphere();

    void set(int x, int y, int z, int r, bool rotX, bool rotY, bool rotZ);

    bool rotate(GgafDx9Core::angle rX, GgafDx9Core::angle rY, GgafDx9Core::angle rZ) override;

    virtual ~ColliSphere();
};

}
#endif /*COLLISPHERE_H_*/
