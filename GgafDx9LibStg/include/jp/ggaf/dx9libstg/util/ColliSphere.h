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
    appcoord _x;
    /** y���W */
    appcoord _y;
    /** z���W */
    appcoord _z;
    /** ���a */
    appcoord _r;
    /** ���a�̂Q�� */
    double _rr;

    ColliSphere();

    void set(appcoord x, appcoord y, appcoord z, appcoord r, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(appangle rX, appangle rY, appangle rZ) override;

    virtual ~ColliSphere();
};

}
#endif /*COLLISPHERE_H_*/
