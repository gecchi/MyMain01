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
    appcoord _x1;
    /** AABのy座標の小さい方 */
    appcoord _y1;
    /** AABのz座標の小さい方 */
    appcoord _z1;
    /** AABの対角の頂点となるx座標大きい方 */
    appcoord _x2;
    /** AABの対角の頂点となるy座標大きい方 */
    appcoord _y2;
    /** AABの対角の頂点となるz座標大きい方 */
    appcoord _z2;


    ColliAAB();

    void set(appcoord x1, appcoord y1, appcoord z1, appcoord x2, appcoord y2, appcoord z2, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(appangle rX, appangle rY, appangle rZ) override;

    virtual ~ColliAAB();
};

}
#endif /*COLIAAB_H_*/
