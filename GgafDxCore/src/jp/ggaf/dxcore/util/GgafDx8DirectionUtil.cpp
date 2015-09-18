#include "jp/ggaf/dxcore/util/GgafDx8DirectionUtil.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

#define V2E (0.70710678118655)    // t = (1.0 / ��(1*1+1*1)) * 1
const GgafDx8DirectionUtil::FaceVec GgafDx8DirectionUtil::_vec[3*3] = {

        {-V2E, -V2E},      //DIR8(-1,-1)
        {  -1,    0},      //DIR8(-1, 0)
        {-V2E, +V2E},      //DIR8(-1, 1)
        {   0,   -1},      //DIR8( 0,-1)
        {   0,    0},      //DIR8( 0, 0)
        {   0,   +1},      //DIR8( 0, 1)
        {+V2E, -V2E},      //DIR8( 1,-1)
        {  +1,    0},      //DIR8( 1, 0)
        {+V2E, +V2E}       //DIR8( 1, 1)
};
const GgafDx8DirectionUtil::FaceVec* GgafDx8DirectionUtil::_dir2vec = &(GgafDx8DirectionUtil::_vec[4]);

const GgafDx8DirectionUtil::FaceSgn GgafDx8DirectionUtil::_sgn[3*3] = {
         {-1,-1 },
         {-1, 0 },
         {-1, 1 },
         { 0,-1 },
         { 0, 0 },
         { 0, 1 },
         { 1,-1 },
         { 1, 0 },
         { 1, 1 }
};
const GgafDx8DirectionUtil::FaceSgn* GgafDx8DirectionUtil::_dir2sgn = &(GgafDx8DirectionUtil::_sgn[4]);


const angle GgafDx8DirectionUtil::_angle[3*3] = {
        D255ANG ,   //DIR8(-1,-1)
        D180ANG ,   //DIR8(-1, 0)
        D135ANG ,   //DIR8(-1, 1)
        D270ANG ,   //DIR8( 0,-1)
           0    ,   //DIR8( 0, 0)
        D90ANG  ,   //DIR8( 0, 1)
        D315ANG ,   //DIR8( 1,-1)
        D0ANG   ,   //DIR8( 1, 0)
        D45ANG      //DIR8( 1, 1)

};
const angle* GgafDx8DirectionUtil::_dir2angle = &(GgafDx8DirectionUtil::_angle[4]);



bool GgafDx8DirectionUtil::is_init = false;


void GgafDx8DirectionUtil::init() {
    if (GgafDx8DirectionUtil::is_init) {
        return;
    }
    _TRACE_("GgafDx8DirectionUtil::init()");


    GgafDx8DirectionUtil::is_init = true;
}
dir8 GgafDx8DirectionUtil::cnvVec2DirNo(float prm_vx, float prm_vy) {
    int sgn_x, sgn_y, sgn_z;
    GgafDx8DirectionUtil::cnvVec2Sgn(prm_vx, prm_vy,
                              sgn_x, sgn_y);
    return DIR8(sgn_x, sgn_y);
}

void GgafDx8DirectionUtil::cnvVec2Sgn(float prm_vx, float prm_vy,
                                     int& out_sgn_x, int& out_sgn_y) {
    //���a�P�ɓ��ڂ��鐳���p�`�̂P�ӂ� 2��2 - 2
    //                  y
    //                  ^
    //                  |
    //              ____|____
    //            �^   ^|   /�_
    //          �^   v || 1/:  �_
    //        �^       || / :    �_
    //       |         v|/  :      | ��=3/8��
    //      -+----------+---+------+---------> x
    //       |         0|<->       |
    //        �_        | u      �^
    //          �_      |      �^
    //            �_�Q�Q|�Q�Q�^
    //                  |
    // u = cos(3/8��)  = 0.3888343236509
    // v = sin(3/8��)  = 0.92387953251129

    static const float u = 0.3888343236509f;
    static const float v = 0.92387953251129f;

    float nvx, nvy;
    UTIL::getNormalizeVector(prm_vx, prm_vy,
                             nvx, nvy);

    //
    //     ^
    //     | u
    //     |____
    //    ^|   :�_
    //   v||   :  �_
    //    ||...:....�_
    //    v|   :      | u
    //-----+---+------+--------->
    //     |<--------->
    //     |     v

    if (nvx < -u) {
        out_sgn_x = -1;
    } else if (u < nvx) {
        out_sgn_x = +1;
    } else {
        out_sgn_x = 0;
    }

    if (nvy < -u) {
        out_sgn_y = -1;
    } else if (u < nvy) {
        out_sgn_y = +1;
    } else {
        out_sgn_y = 0;
    }

}


void GgafDx8DirectionUtil::cnvDirNo2Vec(dir8 prm_dir_no, float& out_vx, float& out_vy) {
    out_vx = GgafDx8DirectionUtil::_dir2vec[prm_dir_no].vx;
    out_vy = GgafDx8DirectionUtil::_dir2vec[prm_dir_no].vy;
}

void GgafDx8DirectionUtil::cnvDirNo2Sgn(dir8 prm_dir_no, int& out_sgn_x, int& out_sgn_y) {
    out_sgn_x = GgafDx8DirectionUtil::_dir2sgn[prm_dir_no].sgn_x;
    out_sgn_y = GgafDx8DirectionUtil::_dir2sgn[prm_dir_no].sgn_y;
}

angle GgafDx8DirectionUtil::cnvDirNo2RzRy(dir8 prm_dir_no) {
    return GgafDx8DirectionUtil::_dir2angle[prm_dir_no];
}

dir8 GgafDx8DirectionUtil::cnvAng2DirNo(angle prm_angle) {
    angle a = UTIL::simplifyAng(prm_angle);
    dir8 r = DIR8(0,0);
    if (a >= D_ANG(202.5)) {
        if (a >= D_ANG(292.5)) {
             if (a >= D_ANG(337.5)) {
                 r = DIR8( 1, 0);
             } else {
                 r = DIR8( 1, -1);
             }
         } else {
             if (a >= D_ANG(247.5)) {
                 r = DIR8( 0,-1);
             } else {
                 r = DIR8(-1,-1);
             }
         }

    } else {
        if (a >= D_ANG(112.5)) {
            if (a >= D_ANG(157.5)) {
                r = DIR8(-1, 0);
            } else {
                r = DIR8(-1, 1);
            }
        } else {
            if (a >= D_ANG(67.5)) {
                r = DIR8( 0, 1);
            } else if (a >= D_ANG(22.5)) {
                r = DIR8( 1, 1);
            } else {
                r = DIR8( 1, 0);
            }
        }
    }
    return r;
}

void GgafDx8DirectionUtil::cnvAng2Sgn(angle prm_angle, int& out_sgn_x, int& out_sgn_y) {
    angle a = UTIL::simplifyAng(prm_angle);

    if (a >= D_ANG(202.5)) {
        if (a >= D_ANG(292.5)) {
             if (a >= D_ANG(337.5)) {
                 out_sgn_x =  1;
                 out_sgn_y =  0;
             } else {
                 out_sgn_x =  1;
                 out_sgn_y = -1;
             }
         } else {
             if (a >= D_ANG(247.5)) {
                 out_sgn_x =  0;
                 out_sgn_y = -1;
             } else {
                 out_sgn_x = -1;
                 out_sgn_y = -1;
             }
         }

    } else {
        if (a >= D_ANG(112.5)) {
            if (a >= D_ANG(157.5)) {
                out_sgn_x = -1;
                out_sgn_y =  0;
            } else {
                out_sgn_x = -1;
                out_sgn_y =  1;
            }
        } else {
            if (a >= D_ANG(67.5)) {
                out_sgn_x =  0;
                out_sgn_y =  1;
            } else if (a >= D_ANG(22.5)) {
                out_sgn_x =  1;
                out_sgn_y =  1;
            } else {
                out_sgn_x =  1;
                out_sgn_y =  0;
            }
        }
    }
}

//       x  y  z                 x  y
//DIR26(-1,-1,-1)
//DIR26(-1,-1, 0)          DIR8(-1,-1)
//DIR26(-1,-1, 1)
//DIR26(-1, 0,-1)
//DIR26(-1, 0, 0)          DIR8(-1, 0)
//DIR26(-1, 0, 1)
//DIR26(-1, 1,-1)
//DIR26(-1, 1, 0)          DIR8(-1, 1)
//DIR26(-1, 1, 1)
//DIR26( 0,-1,-1)
//DIR26( 0,-1, 0)          DIR8( 0,-1)
//DIR26( 0,-1, 1)
//DIR26( 0, 0,-1)
//DIR26( 0, 0, 0)          DIR8( 0, 0)
//DIR26( 0, 0, 1)
//DIR26( 0, 1,-1)
//DIR26( 0, 1, 0)          DIR8( 0, 1)
//DIR26( 0, 1, 1)
//DIR26( 1,-1,-1)
//DIR26( 1,-1, 0)          DIR8( 1,-1)
//DIR26( 1,-1, 1)
//DIR26( 1, 0,-1)
//DIR26( 1, 0, 0)          DIR8( 1, 0)
//DIR26( 1, 0, 1)
//DIR26( 1, 1,-1)
//DIR26( 1, 1, 0)          DIR8( 1, 1)
//DIR26( 1, 1, 1)
