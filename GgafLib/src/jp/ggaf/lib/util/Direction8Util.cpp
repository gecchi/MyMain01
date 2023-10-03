#include "jp/ggaf/lib/util/Direction8Util.h"

#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

#define V2E (0.70710678118655)    // t = (1.0 / Å„(1*1+1*1)) * 1
const Direction8Util::FaceVec Direction8Util::_vec[3*3] = {

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
const Direction8Util::FaceVec* Direction8Util::_dir2vec = &(Direction8Util::_vec[4]);

const Direction8Util::FaceSgn Direction8Util::_sgn[3*3] = {
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
const Direction8Util::FaceSgn* Direction8Util::_dir2sgn = &(Direction8Util::_sgn[4]);


const angle Direction8Util::_angle[3*3] = {
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
const angle* Direction8Util::_dir2angle = &(Direction8Util::_angle[4]);



bool Direction8Util::is_init = false;


void Direction8Util::init() {
    if (Direction8Util::is_init) {
        return;
    }
    _TRACE_(FUNC_NAME<<"");


    Direction8Util::is_init = true;
}
dir8 Direction8Util::cnvVec2DirNo(float prm_vx, float prm_vy) {
    int sgn_x, sgn_y;
    Direction8Util::cnvVec2Sgn(prm_vx, prm_vy,
                                     sgn_x, sgn_y);
    return DIR8(sgn_x, sgn_y);
}

void Direction8Util::cnvVec2Sgn(float prm_vx, float prm_vy,
                                      int& out_sgn_x, int& out_sgn_y) {
    //îºåaÇPÇ…ì‡ê⁄Ç∑ÇÈê≥î™äpå`ÇÃÇPï”ÇÕ 2Å„2 - 2
    //                  y
    //                  ^
    //                  |
    //              ____|____
    //            Å^   ^|   /Å_
    //          Å^   v || 1/:  Å_
    //        Å^       || / :    Å_
    //       |         v|/  :      | É∆=3/8ÉŒ
    //      -+----------+---+------+---------> x
    //       |         0|<->       |
    //        Å_        | u      Å^
    //          Å_      |      Å^
    //            Å_ÅQÅQ|ÅQÅQÅ^
    //                  |
    // u = cos(3/8ÉŒ)  = 0.3888343236509
    // v = sin(3/8ÉŒ)  = 0.92387953251129

    static const double u = 0.3888343236509;
    static const double v = 0.9238795325112;

    double nvx, nvy;
    UTIL::getNormalized2DVector(prm_vx, prm_vy,
                              nvx, nvy);

    //
    //     ^
    //     | u
    //     |____
    //    ^|   :Å_
    //   v||   :  Å_
    //    ||...:....Å_
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

void Direction8Util::cnvDirNo2Vec(dir8 prm_dir_no, float& out_vx, float& out_vy) {
    out_vx = Direction8Util::_dir2vec[prm_dir_no].vx;
    out_vy = Direction8Util::_dir2vec[prm_dir_no].vy;
}

void Direction8Util::cnvDirNo2Sgn(dir8 prm_dir_no, int& out_sgn_x, int& out_sgn_y) {
    out_sgn_x = Direction8Util::_dir2sgn[prm_dir_no].sgn_x;
    out_sgn_y = Direction8Util::_dir2sgn[prm_dir_no].sgn_y;
}

angle Direction8Util::cnvDirNo2RzRy(dir8 prm_dir_no) {
    return Direction8Util::_dir2angle[prm_dir_no];
}

dir8 Direction8Util::cnvAng2DirNo(angle prm_angle) {
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

void Direction8Util::cnvAng2Sgn(angle prm_angle, int& out_sgn_x, int& out_sgn_y) {
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
