#include "jp/ggaf/lib/util/ColliAAPyramid.h"

#include "jp/ggaf/lib/util/StgUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAAPyramid::ColliAAPyramid() : ColliAABox() {
    _pos_pyramid = -1;
    _shape_kind = COLLI_AAPYRAMID;
}

void ColliAAPyramid::set(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, int prm_pos_pyramid, bool prm_rot_x, bool prm_rot_y, bool prm_rot_z) {
#ifdef MY_DEBUG
    if (prm_rot_x || prm_rot_y || prm_rot_z) {
        //TODO:ひまなら実装
        throwGgafCriticalException("当たり判定の直角三角錐要素は回転平行移動は未対応です。");
    }
#endif
    ColliAABox::set(prm_x1, prm_y1, prm_z1, prm_x2, prm_y2, prm_z2, prm_rot_x, prm_rot_y, prm_rot_z);

    _pos_pyramid = prm_pos_pyramid;

//    (x1,y1) (x2,y2) を 通る直線
//    y = ax + b
//    a = (y2-y1) / (x2-x1)
//    b = (x2*y1 - x1*y2) / (x2-x1)


    // (a,b) (c,d) を通る直線
    //傾き = (d-b) / (c-a);
    //切片 = (c*b - a*d) / (c-a);

    //y = ax + b より
    //b = y - ax

    //法線ベクトルを予め求めて保持
    float x1 = PX_DX(_x1);
    float y1 = PX_DX(_y1);
    float z1 = PX_DX(_z1);
    float x2 = PX_DX(_x2);
    float y2 = PX_DX(_y2);
    float z2 = PX_DX(_z2);
    float hdx = PX_DX(_hdx);
    float hdy = PX_DX(_hdy);
    float hdz = PX_DX(_hdz);

    switch (_pos_pyramid) {
        case POS_PYRAMID_nnn: {
            UTIL::getPlaneNomalVec(x2, y1, z1,
                                   x1, y2, z1,
                                   x1, y1, z2,
                                   _s_nvx, _s_nvy, _s_nvz, _s_d);
            // (x1,y2), (x2,y1) を通る直線の傾きと切片
            _a_xy = (y1-y2) / (x2-x1);
            _b_xy_z1 = (x2*y2 - x1*y1) / (x2-x1);
            //↑は、Z軸 = z1 XY平面 の値になる。
            //Z軸 = z2 XY平面 (x1,y1) を通り、傾きはそのままの場合の切片を求める
            //y = ax + b より
            //b = y - ax
            _b_xy_z2 = y1 - _a_xy*x1;

//             //XY平面 : (x1,y2), (x1+hdx, y1) を通る直線
//             _a_xy[0] = (y1-y2) / ((x1+hdx)-x1);
//             _b_xy[0] = ((x1+hdx)*y2 - x1*y1) / ((x1+hdx)-x1);
//             //XY平面 : (x2,y1), (x1, y1+hdy) を通る直線
//             _a_xy[1] = ((y1+hdy)-y1) / (x1-x2);
//             _b_xy[1] = (x1*y1 - x2*(y1+hdy)) / (x1-x2);
//
//             //YZ平面 : (y1,z2), (y1+hdy,z1) を通る直線
//             _a_yz[0] = (z1-z2) / ((y1+hdy)-y1);
//             _b_yz[0] = ((y1+hdy)*z2 - y1*z1) / ((y1+hdy)-y1);
//             //YZ平面 : (y2,z1), (y1,z1+hdz) を通る直線
//             _a_yz[1] = ((z1+hdz)-z1) / (y1-y2);
//             _b_yz[1] = (y1*z1 - y2*(z1+hdz)) / (y1-y2);
//
//             //ZX平面 : (z1,x2), (z1+hdz,x1) を通る直線
//             _a_zx[0] = (x1-x2) / ((z1+hdz)-z1);
//             _b_zx[0] = ((z1+hdz)*x2 - z1*x1) / ((z1+hdz)-z1);
//             //ZX平面 : (z2,x1), (z1,x1+hdx) を通る直線
//             _a_zx[1] = ((x1+hdx)-x1) / (z1-z2);
//             _b_zx[1] = (z1*x1 - z2*(x1+hdx)) / (z1-z2);

             break;
         }
         case POS_PYRAMID_nnp: {
             UTIL::getPlaneNomalVec(x1, y1, z1,
                                    x1, y2, z2,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_npn: {
             UTIL::getPlaneNomalVec(x2, y2, z1,
                                    x1, y2, z2,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_npp: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y1, z2,
                                    x1, y2, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_pnn: {
             UTIL::getPlaneNomalVec(x2, y1, z2,
                                    x2, y2, z1,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_pnp: {
             UTIL::getPlaneNomalVec(x1, y1, z2,
                                    x2, y2, z2,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_ppn: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y2, z1,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_ppp: {
             UTIL::getPlaneNomalVec(x1, y2, z2,
                                    x2, y2, z1,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         default: {
             break;
         }
     }
    _d_nv = sqrt((_s_nvz*_s_nvz) + (_s_nvy*_s_nvy) + (_s_nvx*_s_nvx));
    _d_c2vtx = UTIL::getDistance(_cx, _cy, _cz, _x1, _y1, _z1);
}


ColliAAPyramid::~ColliAAPyramid() {
}
