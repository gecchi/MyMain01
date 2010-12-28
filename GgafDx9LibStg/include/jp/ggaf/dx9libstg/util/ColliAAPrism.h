#ifndef COLLIAAPRISM_H_
#define COLLIAAPRISM_H_
namespace GgafDx9LibStg {


#define XY_XpYn   1
#define XY_XnYp   2
#define XY_XpYp   3
#define XY_XnYn   4

#define YZ_YpZn   5
#define YZ_YnZp   6
#define YZ_YpZp   7
#define YZ_YnZn   8

#define ZX_ZpXn   9
#define ZX_ZnXp   10
#define ZX_ZpXp   11
#define ZX_ZnXn   12

/**
 * AAPrism(軸並行プリズム：Axis-Aligned Prism)当たり判定要素クラス
 * 軸並行プリズムとは、AABのある面の対角線でスライスを１回行った立体の事。
 * @version 1.00
 * @since 2010/12/28
 * @author Masatoshi Tsuge
 */
class ColliAAPrism : public GgafDx9Core::GgafDx9CollisionPart {
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

    int _pos_prism;
    int _slant_x1;
    int _slant_y1;
    int _slant_x2;
    int _slant_y2;
    int _slant_cal;

    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ);

    bool rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliAAPrism();
};

}
#endif /*COLIAAB_H_*/
