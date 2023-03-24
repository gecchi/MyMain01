#ifndef GGAF_LIB_COLLIAAPYRAMID_H_
#define GGAF_LIB_COLLIAAPYRAMID_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/ColliAABox.h"

namespace GgafLib {

/**
 * 軸平行の直角三角錐(Axis-Aligned Pyramid) 当たり判定要素クラス
 * 軸平行の直角三角錐とは、AABox のある頂点の近隣３頂点を通る面で
 * スライスして出来上がった三角錐の事です。
 * @version 1.00
 * @since 2016/01/15
 * @author Masatoshi Tsuge
 */
class ColliAAPyramid : public ColliAABox {

public:
    /** 三角錐斜面法線ベクトル */
    float _s_nvx, _s_nvy, _s_nvz, _s_d;
    /** 対角線と斜面の交点 */
    coord _l_px, _l_py, _l_pz;
public:
    ColliAAPyramid();

    void set(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, pos_t prm_pos_info, bool prm_rot_x, bool prm_rot_y, bool prm_rot_z);

    virtual ~ColliAAPyramid();
};

}
#endif /*GGAF_LIB_COLLIAAPYRAMID_H_*/
