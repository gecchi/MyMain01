#ifndef COLLISPHERE_H_
#define COLLISPHERE_H_
namespace GgafDx9LibStg {

/**
 * 球当たり判定要素クラス
 * @version 1.00
 * @since 2010/01/17
 * @author Masatoshi Tsuge
 */
class ColliSphere : public GgafDx9Core::GgafDx9CollisionPart {
public:
    /** x座標 */
    int _x;
    /** y座標 */
    int _y;
    /** z座標 */
    int _z;
    /** 半径 */
    int _r;
    /** 半径の２乗 */
    double _rr;

    ColliSphere();

    void set(int x, int y, int z, int r, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliSphere();
};

}
#endif /*COLLISPHERE_H_*/
