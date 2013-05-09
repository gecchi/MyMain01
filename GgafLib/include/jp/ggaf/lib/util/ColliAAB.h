#ifndef COLIAAB_H_
#define COLIAAB_H_
namespace GgafLib {

/**
 * AAB(軸平行直方体：Axis-Aligned Box)当たり判定要素クラス
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliAAB : public GgafDxCore::GgafDxCollisionPart {
public:
    /** AABのx座標の小さい方 */
    coord _x1;
    /** AABのy座標の小さい方 */
    coord _y1;
    /** AABのz座標の小さい方 */
    coord _z1;
    /** AABの対角の頂点となるx座標大きい方 */
    coord _x2;
    /** AABの対角の頂点となるy座標大きい方 */
    coord _y2;
    /** AABの対角の頂点となるz座標大きい方 */
    coord _z2;

public:
    ColliAAB();

    void set(coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliAAB();
};

}
#endif /*COLIAAB_H_*/
