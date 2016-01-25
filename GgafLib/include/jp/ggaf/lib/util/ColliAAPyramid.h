#ifndef GGAFLIB_COLLIAAPYRAMID_H_
#define GGAFLIB_COLLIAAPYRAMID_H_
#include "GgafLibCommonHeader.h"
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
    /** 三角錐位置 */
    int _pos_pyramid;
    /** 三角錐斜面法線ベクトル */
    float _s_nvx, _s_nvy, _s_nvz, _s_d;
    /** 三角錐斜面法線ベクトルの長さ */
    float _d_nv;
    /** BOX中心から対角線の距離 */
    coord _d_c2vtx;
    /** XY平面でスライスした場合の斜面の直線の傾き */
    float _a_xy;
    /** XY平面でスライスした場合の斜面の直線のローカル座標切片（Z軸=z1） */
    float _b_xy_z1;
    /** XY平面でスライスした場合の斜面の直線のローカル座標切片（Z軸=z2） */
    float _b_xy_z2;

//    /** 各面(XY面,YZ面,ZX面) 斜辺の傾き */
//    float _a_xy[2], _a_yz[2], _a_zx[2];
//    /** 各面(XY面,YZ面,ZX面) 切片 */
//    float _b_xy[2], _b_yz[2], _b_zx[2];
public:
    ColliAAPyramid();

    void set(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, int prm_pos_pyramid, bool prm_rot_x, bool prm_rot_y, bool prm_rot_z);

    virtual ~ColliAAPyramid();
};

}
#endif /*GGAFLIB_COLLIAAPYRAMID_H_*/
