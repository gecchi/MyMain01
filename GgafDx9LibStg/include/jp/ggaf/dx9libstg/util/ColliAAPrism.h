#ifndef COLLIAAPOS_PRISM_H_
#define COLLIAAPOS_PRISM_H_
namespace GgafDx9LibStg {


/**
 * AAPrism(軸並行プリズム：Axis-Aligned Prism)当たり判定要素クラス
 * 軸並行プリズムとは、AABのある面の対角線でスライスを１回行った立体の事。
 * @version 1.00
 * @since 2010/12/28
 * @author Masatoshi Tsuge
 */
class ColliAAPrism : public ColliAAB {
public:

    int _pos_prism;
    /** プリズム斜辺の境界線傾き */
    double _a;
    /** プリズム斜辺の境界線の切片 */
    double _b;
    /** プリズム斜辺面の法線ベクトルの逆ベクトルX要素(当たり判定計算用) */
    float _vIH_x;
    /** プリズム斜辺面の法線ベクトルの逆ベクトルY要素(当たり判定計算用) */
    float _vIH_y;

    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ);


    virtual ~ColliAAPrism();
};

}
#endif /*COLIAAB_H_*/
