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
    //法線ベクトルを予め求めて保持
    float x1 = C_DX(_x1);
    float y1 = C_DX(_y1);
    float z1 = C_DX(_z1);
    float x2 = C_DX(_x2);
    float y2 = C_DX(_y2);
    float z2 = C_DX(_z2);

    float dg_vx, dg_vy, dg_vz; //対角線方向ベクトル
    float x0, y0, z0;          //３直角の頂点（対角線が通る点）
    switch (_pos_pyramid) {
        case POS_PYRAMID_nnn: {
            UTIL::getPlaneNomalVec(x2, y1, z1,
                                   x1, y2, z1,
                                   x1, y1, z2,
                                   _s_nvx, _s_nvy, _s_nvz, _s_d);
            x0 = x1;
            y0 = y1;
            z0 = z1;
            dg_vx = x2-x1;
            dg_vy = y2-y1;
            dg_vz = z2-z1;
            break;
         }
         case POS_PYRAMID_nnp: {
             UTIL::getPlaneNomalVec(x1, y1, z1,
                                    x1, y2, z2,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x1;
             y0 = y1;
             z0 = z2;
             dg_vx = x2-x1;
             dg_vy = y2-y1;
             dg_vz = z1-z2;
             break;
         }
         case POS_PYRAMID_npn: {
             UTIL::getPlaneNomalVec(x2, y2, z1,
                                    x1, y2, z2,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x1;
             y0 = y2;
             z0 = z1;
             dg_vx = x2-x1;
             dg_vy = y1-y2;
             dg_vz = z2-z1;
             break;
         }
         case POS_PYRAMID_npp: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y1, z2,
                                    x1, y2, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x1;
             y0 = y2;
             z0 = z2;
             dg_vx = x2-x1;
             dg_vy = y1-y2;
             dg_vz = z1-z2;
             break;
         }
         case POS_PYRAMID_pnn: {
             UTIL::getPlaneNomalVec(x2, y1, z2,
                                    x2, y2, z1,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y1;
             z0 = z1;
             dg_vx = x1-x2;
             dg_vy = y2-y1;
             dg_vz = z2-z1;
             break;
         }
         case POS_PYRAMID_pnp: {
             UTIL::getPlaneNomalVec(x1, y1, z2,
                                    x2, y2, z2,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y1;
             z0 = z2;
             dg_vx = x1-x2;
             dg_vy = y2-y1;
             dg_vz = z1-z2;
             break;
         }
         case POS_PYRAMID_ppn: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y2, z1,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y2;
             z0 = z1;
             dg_vx = x1-x2;
             dg_vy = y1-y2;
             dg_vz = z2-z1;
             break;
         }
         case POS_PYRAMID_ppp: {
             UTIL::getPlaneNomalVec(x1, y2, z2,
                                    x2, y2, z1,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y2;
             z0 = z2;
             dg_vx = x1-x2;
             dg_vy = y1-y2;
             dg_vz = z1-z2;
             break;
         }
         default: {
             throwGgafCriticalException("ColliAAPyramid::set() prm_pos_pyramid が不正です。prm_pos_pyramid="<<prm_pos_pyramid);
             break;
         }
     }

    //対角線と斜面の交点を求める
    //
    //これが、x0, y0, z0 を通るので対角線の方程式は
    // (x-x0/dg_vx) = (y-y0/dg_vy) = (z-z0/dg_vz)
    // (x,y,z) = (x0,y0,z0) + t(dg_vx,dg_vy,dg_vz)     ・・・�@
    //斜面 _s_nvx*x + _s_nvy*y + _s_nvz*z + _s_d = 0   ・・・�A
    //�@を�Aに代入して、ｔを求める
    // _s_nvx*(x0+t*dg_vx) + _s_nvy*(y0+t*dg_vy) + _s_nvz*(z0+t*dg_vz) + _s_d = 0
    // t=-(_s_nvz*z0+_s_nvy*y0+_s_nvx*x0+_s_d)/(_s_nvz*dg_vz+_s_nvy*dg_vy+_s_nvx*dg_vx)
    //これを�@へ代入
    float t=-(_s_nvz*z0+_s_nvy*y0+_s_nvx*x0+_s_d)/(_s_nvz*dg_vz+_s_nvy*dg_vy+_s_nvx*dg_vx);
    //交点は
    _l_px = DX_C(x0 + t*dg_vx);
    _l_py = DX_C(y0 + t*dg_vy);
    _l_pz = DX_C(z0 + t*dg_vz);


    // 2条の距離をいかの場合わけで設定
    //
    //  a
    //	if(o_scx < b_x1) {
    //		square_length += (double)(o_scx - b_x1) * (o_scx - b_x1);
    //	}

    //	b
    //	if(o_scx > b_x2) {
    //		square_length += (double)(o_scx - b_x2) * (o_scx - b_x2);
    //	}

    //          a         b      c        d      e
    //    -------------><---><---------><---><-----------------
    //              ,─、
    //             │  │   ,─、
    //              `─'  _│_ │�@
    //                  |＼ `─'
    //                  |  ＼   ＼
    //                  |    ＼  r＼
    //                  |      ＼   ＼
    //                  |        ＼    ,─、�A
    //                  |          ＼ │| │
    //                  |            ＼`+-'
    //                  ----------------,─、
    //              ,─、              │  │
    //             │  │               `─'
    //              `─'

    //斜面と球が接した場合、球の中心(cx,cy,cz)から垂線を斜面に降ろした点P(x,y,z)を考え
    //線(cx,cy,cz)-(x,y,z) の XY平面、YZ平面、ZX平面から見たそれぞれの「なす角」θを求める
    //�@ 、�Aのときの足しこむ2条の距離を求めるために






    // XY平面で考える
    //
    //    (x1,y1) (x2,y2) を 通る直線
    //    y = ax + b
    //    a = (y2-y1) / (x2-x1)
    //    b = (x2*y1 - x1*y2) / (x2-x1)
    //
    // (a,b) (c,d) を通る直線
    //傾き = (d-b) / (c-a);
    //切片 = (c*b - a*d) / (c-a);

    //y = ax + b より
    //b = y - ax

    // XY平面で考える
    // a = (y2-y1) / (x2-x1) より
    float a_XY = (y2-y1) / (x2-x1);

//    if ((_pos_pyramid & POS_PYRAMID_ppn) ||(_pos_pyramid & POS_PYRAMID_ppp)) {
////    (x1,y2)    (x2,y2)
////        _______
////        ＼    |
////          ＼  |
////            ＼|
////              (x2, y1)ココ
//        _rad_xy =              UTIL::getRad2D(x2-x2,y2-y1 , x1-x2,y2-y1);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_npn) ||(_pos_pyramid & POS_PYRAMID_npp)) {
////    (x1,y2)    (x2,y2)ココ
////        _______
////        |    ／
////        |  ／
////        |／
////    (x1, y1)
//        _rad_xy = (PI / 2.0) + UTIL::getRad2D(x1-x2,y2-y2 , x1-x2,y1-y2);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_nnn) ||(_pos_pyramid & POS_PYRAMID_nnp)) {
////    (x1,y2)ココ
////        |＼
////        |  ＼
////        |    ＼
////        --------
//// (x1, y1)   (x2, y1)
//        _rad_xy = PI + UTIL::getRad2D(x1-x1,y1-y2 , x2-x1,y1-y2);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_pnn) ||(_pos_pyramid & POS_PYRAMID_pnp)) {
////          (x2,y2)ココ
////        ／|
////      ／  |
////    ／    |
////   --------
//// (x1, y1)   (x2, y1)
//        _rad_xy = ((3.0 * PI) / 2.0) + UTIL::getRad2D(x2-x2,y1-y2 , x1-x2,y1-y2);
//    }
//
////    _rad_xy =              UTIL::getRad2D(x2-x2,y2-y1 , x1-x2,y2-y1);

    _rad_xy = UTIL::getRad2D(x2-x2,y2-y1 , x1-x2,y2-y1);
    _rad_yz = UTIL::getRad2D(y2-y2,z2-z1 , y1-y2,z2-z1);
    _rad_zx = UTIL::getRad2D(z2-z2,x2-x1 , z1-z2,x2-x1);
}


ColliAAPyramid::~ColliAAPyramid() {
}
