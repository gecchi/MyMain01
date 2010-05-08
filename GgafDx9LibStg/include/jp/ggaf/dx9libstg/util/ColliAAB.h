#ifndef COLIAAB_H_
#define COLIAAB_H_
namespace GgafDx9LibStg {

/**
 * AAB(軸並行直方体：Axis-Aligned Box)当たり判定要素クラス
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliAAB : public GgafDx9Core::GgafDx9CollisionPart {
public:
    /** AABのx座標の小さい方 */
    int _x1;
    /** AABのy座標の小さい方 */
    int _y1;
    /** AABのz座標の小さい方 */
    int _z1;
    /** AABの対角の頂点となるx座標大きい方 */
    int _x2;
    /** AABの対角の頂点となるy座標大きい方 */
    int _y2;
    /** AABの対角の頂点となるz座標大きい方 */
    int _z2;


    ColliAAB();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);

    bool rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliAAB();
};

}
#endif /*COLIAAB_H_*/
