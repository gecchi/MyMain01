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
    appcoord _x;
    /** y座標 */
    appcoord _y;
    /** z座標 */
    appcoord _z;
    /** 半径 */
    appcoord _r;
    /** 半径の２乗 */
    double _rr;

    ColliSphere();

    void set(appcoord x, appcoord y, appcoord z, appcoord r, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(appangle rX, appangle rY, appangle rZ) override;

    virtual ~ColliSphere();
};

}
#endif /*COLLISPHERE_H_*/
