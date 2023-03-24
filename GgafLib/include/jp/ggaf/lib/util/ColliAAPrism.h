#ifndef GGAF_LIB_COLLIAAPRISM_H_
#define GGAF_LIB_COLLIAAPRISM_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/ColliAABox.h"

namespace GgafLib {

/**
 * 軸平行の直方三角柱 (Axis-Aligned Prism)当たり判定要素クラス
 * 軸平行の直方三角柱とは、AAB(軸平行直方体)のある面を、対角線でスライスを１回行った立体の事。
 * @version 1.00
 * @since 2010/12/28
 * @author Masatoshi Tsuge
 */
class ColliAAPrism : public ColliAABox {

public:
    /** プリズム斜辺の境界線傾き */
    double _a;
    /** プリズム斜辺の境界線の切片(ローカル座標) */
    double _b;
    /** プリズム斜辺面の法線ベクトルの逆ベクトルX要素(当たり判定計算用) */
    float _vIH_x;
    /** プリズム斜辺面の法線ベクトルの逆ベクトルY要素(当たり判定計算用) */
    float _vIH_y;

public:
    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z);

    virtual ~ColliAAPrism();
};

}
#endif /*GGAF_LIB_COLLIAAPRISM_H_*/
