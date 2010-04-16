﻿#ifndef COLIAABB_H_
#define COLIAABB_H_
namespace GgafDx9LibStg {

/**
 * AABB当たり判定要素クラス
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliBox : public GgafDx9Core::GgafDx9CollisionPart {
public:
    /** AABBのx座標の小さい方 */
    int _x1;
    /** AABBのy座標の小さい方 */
    int _y1;
    /** AABBのz座標の小さい方 */
    int _z1;
    /** AABBの対角の頂点となるx座標大きい方 */
    int _x2;
    /** AABBの対角の頂点となるy座標大きい方 */
    int _y2;
    /** AABBの対角の頂点となるz座標大きい方 */
    int _z2;


    ColliBox();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);

    bool rotate(angle rX, angle rY, angle rZ) override;

    virtual ~ColliBox();
};

}
#endif /*COLIAABB_H_*/
