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
        //TODO:Ç–Ç‹Ç»ÇÁé¿ëï
        throwGgafCriticalException("ìñÇΩÇËîªíËÇÃíºäpéOäpêçóvëfÇÕâÒì]ïΩçsà⁄ìÆÇÕñ¢ëŒâûÇ≈Ç∑ÅB");
    }
#endif
    ColliAABox::set(prm_x1, prm_y1, prm_z1, prm_x2, prm_y2, prm_z2, prm_rot_x, prm_rot_y, prm_rot_z);
    _pos_pyramid = prm_pos_pyramid;
    //ñ@ê¸ÉxÉNÉgÉãÇó\ÇﬂãÅÇﬂÇƒï€éù
    float x1 = C_DX(_x1);
    float y1 = C_DX(_y1);
    float z1 = C_DX(_z1);
    float x2 = C_DX(_x2);
    float y2 = C_DX(_y2);
    float z2 = C_DX(_z2);

    float dg_vx, dg_vy, dg_vz; //ëŒäpê¸ï˚å¸ÉxÉNÉgÉã
    float x0, y0, z0;          //ÇRíºäpÇÃí∏ì_ÅiëŒäpê¸Ç™í ÇÈì_Åj
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
             throwGgafCriticalException("ColliAAPyramid::set() prm_pos_pyramid Ç™ïsê≥Ç≈Ç∑ÅBprm_pos_pyramid="<<prm_pos_pyramid);
             break;
         }
     }

    //ëŒäpê¸Ç∆éŒñ ÇÃåì_ÇãÅÇﬂÇÈ
    //
    //Ç±ÇÍÇ™ÅAx0, y0, z0 Çí ÇÈÇÃÇ≈ëŒäpê¸ÇÃï˚íˆéÆÇÕ
    // (x-x0/dg_vx) = (y-y0/dg_vy) = (z-z0/dg_vz)
    // (x,y,z) = (x0,y0,z0) + t(dg_vx,dg_vy,dg_vz)     ÅEÅEÅEá@
    //éŒñ  _s_nvx*x + _s_nvy*y + _s_nvz*z + _s_d = 0   ÅEÅEÅEáA
    //á@ÇáAÇ…ë„ì¸ÇµÇƒÅAÇîÇãÅÇﬂÇÈ
    // _s_nvx*(x0+t*dg_vx) + _s_nvy*(y0+t*dg_vy) + _s_nvz*(z0+t*dg_vz) + _s_d = 0
    // t=-(_s_nvz*z0+_s_nvy*y0+_s_nvx*x0+_s_d)/(_s_nvz*dg_vz+_s_nvy*dg_vy+_s_nvx*dg_vx)
    //Ç±ÇÍÇá@Ç÷ë„ì¸
    float t=-(_s_nvz*z0+_s_nvy*y0+_s_nvx*x0+_s_d)/(_s_nvz*dg_vz+_s_nvy*dg_vy+_s_nvx*dg_vx);
    //åì_ÇÕ
    _l_px = DX_C(x0 + t*dg_vx);
    _l_py = DX_C(y0 + t*dg_vy);
    _l_pz = DX_C(z0 + t*dg_vz);


    // 2èÇÃãóó£ÇÇ¢Ç©ÇÃèÍçáÇÌÇØÇ≈ê›íË
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
    //              ,ÑüÅA
    //             Ñ†  Ñ†   ,ÑüÅA
    //              `Ñü'  _Ñ†_ Ñ†á@
    //                  |Å_ `Ñü'
    //                  |  Å_   Å_
    //                  |    Å_  rÅ_
    //                  |      Å_   Å_
    //                  |        Å_    ,ÑüÅAáA
    //                  |          Å_ Ñ†| Ñ†
    //                  |            Å_`+-'
    //                  ----------------,ÑüÅA
    //              ,ÑüÅA              Ñ†  Ñ†
    //             Ñ†  Ñ†               `Ñü'
    //              `Ñü'

    //éŒñ Ç∆ãÖÇ™ê⁄ÇµÇΩèÍçáÅAãÖÇÃíÜêS(cx,cy,cz)Ç©ÇÁêÇê¸ÇéŒñ Ç…ç~ÇÎÇµÇΩì_P(x,y,z)ÇçlÇ¶
    //ê¸(cx,cy,cz)-(x,y,z) ÇÃ XYïΩñ ÅAYZïΩñ ÅAZXïΩñ Ç©ÇÁå©ÇΩÇªÇÍÇºÇÍÇÃÅuÇ»Ç∑äpÅvÉ∆ÇãÅÇﬂÇÈ
    //á@ ÅAáAÇÃÇ∆Ç´ÇÃë´ÇµÇ±Çﬁ2èÇÃãóó£ÇãÅÇﬂÇÈÇΩÇﬂÇ…






    // XYïΩñ Ç≈çlÇ¶ÇÈ
    //
    //    (x1,y1) (x2,y2) Ç í ÇÈíºê¸
    //    y = ax + b
    //    a = (y2-y1) / (x2-x1)
    //    b = (x2*y1 - x1*y2) / (x2-x1)
    //
    // (a,b) (c,d) Çí ÇÈíºê¸
    //åXÇ´ = (d-b) / (c-a);
    //êÿï– = (c*b - a*d) / (c-a);

    //y = ax + b ÇÊÇË
    //b = y - ax

    // XYïΩñ Ç≈çlÇ¶ÇÈ
    // a = (y2-y1) / (x2-x1) ÇÊÇË
    float a_XY = (y2-y1) / (x2-x1);

//    if ((_pos_pyramid & POS_PYRAMID_ppn) ||(_pos_pyramid & POS_PYRAMID_ppp)) {
////    (x1,y2)    (x2,y2)
////        _______
////        Å_    |
////          Å_  |
////            Å_|
////              (x2, y1)ÉRÉR
//        _rad_xy =              UTIL::getRad2D(x2-x2,y2-y1 , x1-x2,y2-y1);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_npn) ||(_pos_pyramid & POS_PYRAMID_npp)) {
////    (x1,y2)    (x2,y2)ÉRÉR
////        _______
////        |    Å^
////        |  Å^
////        |Å^
////    (x1, y1)
//        _rad_xy = (PI / 2.0) + UTIL::getRad2D(x1-x2,y2-y2 , x1-x2,y1-y2);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_nnn) ||(_pos_pyramid & POS_PYRAMID_nnp)) {
////    (x1,y2)ÉRÉR
////        |Å_
////        |  Å_
////        |    Å_
////        --------
//// (x1, y1)   (x2, y1)
//        _rad_xy = PI + UTIL::getRad2D(x1-x1,y1-y2 , x2-x1,y1-y2);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_pnn) ||(_pos_pyramid & POS_PYRAMID_pnp)) {
////          (x2,y2)ÉRÉR
////        Å^|
////      Å^  |
////    Å^    |
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
