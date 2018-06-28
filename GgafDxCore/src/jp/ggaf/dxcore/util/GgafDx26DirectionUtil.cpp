#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

#define V3E (0.57735026918963)    // ŽÎ‚ß‚Ì’PˆÊƒxƒNƒgƒ‹Še—v‘f(t = (1.0 / ã(1*1+1*1+1*1)) * 1 )
#define V2E (0.70710678118655)    // t = (1.0 / ã(1*1+1*1)) * 1
const GgafDx26DirectionUtil::FaceVec GgafDx26DirectionUtil::_vec[3*3*3] = {
        {-V3E, -V3E, -V3E},     //DIR26(-1,-1,-1) = -13
        {-V2E, -V2E,    0},     //DIR26(-1,-1, 0) = -12
        {-V3E, -V3E, +V3E},     //DIR26(-1,-1, 1) = -11
        {-V2E,    0, -V2E},     //DIR26(-1, 0,-1) = -10
        {  -1,    0,    0},     //DIR26(-1, 0, 0) = -9
        {-V2E,    0, +V2E},     //DIR26(-1, 0, 1) = -8
        {-V3E, +V3E, -V3E},     //DIR26(-1, 1,-1) = -7
        {-V2E, +V2E,    0},     //DIR26(-1, 1, 0) = -6
        {-V3E, +V3E, +V3E},     //DIR26(-1, 1, 1) = -5
        {   0, -V2E, -V2E},     //DIR26( 0,-1,-1) = -4
        {   0,   -1,    0},     //DIR26( 0,-1, 0) = -3
        {   0, -V2E, +V2E},     //DIR26( 0,-1, 1) = -2
        {   0,    0,   -1},     //DIR26( 0, 0,-1) = -1
        {   0,    0,    0},     //DIR26( 0, 0, 0) =  0
        {   0,    0,   +1},     //DIR26( 0, 0, 1) =  1
        {   0, +V2E, -V2E},     //DIR26( 0, 1,-1) =  2
        {   0,   +1,    0},     //DIR26( 0, 1, 0) =  3
        {   0, +V2E, +V2E},     //DIR26( 0, 1, 1) =  4
        {+V3E, -V3E, -V3E},     //DIR26( 1,-1,-1) =  5
        {+V2E, -V2E,    0},     //DIR26( 1,-1, 0) =  6
        {+V3E, -V3E, +V3E},     //DIR26( 1,-1, 1) =  7
        {+V2E,    0, -V2E},     //DIR26( 1, 0,-1) =  8
        {  +1,    0,    0},     //DIR26( 1, 0, 0) =  9
        {+V2E,    0, +V2E},     //DIR26( 1, 0, 1) =  10
        {+V3E, +V3E, -V3E},     //DIR26( 1, 1,-1) =  11
        {+V2E, +V2E,    0},     //DIR26( 1, 1, 0) =  12
        {+V3E, +V3E, +V3E}      //DIR26( 1, 1, 1) =  13
};
const GgafDx26DirectionUtil::FaceVec* GgafDx26DirectionUtil::_dir2vec = &(GgafDx26DirectionUtil::_vec[13]); //13 ‚Í 3*3*3=27 ‚Ì^‚ñ’†‚Ì—v‘fB_dir2vec[-13`13]‚ÅƒAƒNƒZƒX‚·‚éˆ×

const GgafDx26DirectionUtil::FaceSgn GgafDx26DirectionUtil::_sgn[3*3*3] = {
         {-1,-1,-1 },
         {-1,-1, 0 },
         {-1,-1, 1 },
         {-1, 0,-1 },
         {-1, 0, 0 },
         {-1, 0, 1 },
         {-1, 1,-1 },
         {-1, 1, 0 },
         {-1, 1, 1 },
         { 0,-1,-1 },
         { 0,-1, 0 },
         { 0,-1, 1 },
         { 0, 0,-1 },
         { 0, 0, 0 },
         { 0, 0, 1 },
         { 0, 1,-1 },
         { 0, 1, 0 },
         { 0, 1, 1 },
         { 1,-1,-1 },
         { 1,-1, 0 },
         { 1,-1, 1 },
         { 1, 0,-1 },
         { 1, 0, 0 },
         { 1, 0, 1 },
         { 1, 1,-1 },
         { 1, 1, 0 },
         { 1, 1, 1 }
};
const GgafDx26DirectionUtil::FaceSgn* GgafDx26DirectionUtil::_dir2sgn = &(GgafDx26DirectionUtil::_sgn[13]); //13 ‚Í 3*3*3=27 ‚Ì^‚ñ’†‚Ì—v‘fB_dir2sgn[-13`13]‚ÅƒAƒNƒZƒX‚·‚éˆ×


const GgafDx26DirectionUtil::RzRy GgafDx26DirectionUtil::_rzry[3*3*3] = {
        {D315ANG  , D90ANG+D45ANG },     //DIR26(-1,-1,-1)
        {D255ANG  , D0ANG         },     //DIR26(-1,-1, 0)
        {D315ANG  , D270ANG-D45ANG},     //DIR26(-1,-1, 1)
        {D0ANG    , D135ANG       },     //DIR26(-1, 0,-1)
        {D180ANG  , D0ANG         },     //DIR26(-1, 0, 0)
        {D180ANG  , D45ANG        },     //DIR26(-1, 0, 1)
        {D45ANG   , D90ANG+D45ANG },     //DIR26(-1, 1,-1)
        {D135ANG  , D0ANG         },     //DIR26(-1, 1, 0)
        {D45ANG   , D270ANG-D45ANG},     //DIR26(-1, 1, 1)
        {D315ANG  , D90ANG        },     //DIR26( 0,-1,-1)
        {D270ANG  , D0ANG         },     //DIR26( 0,-1, 0)
        {D315ANG  , D270ANG       },     //DIR26( 0,-1, 1)
        {D0ANG    , D90ANG        },     //DIR26( 0, 0,-1)
        {   0     ,    0          },     //DIR26( 0, 0, 0)
        {D0ANG    , D270ANG       },     //DIR26( 0, 0, 1)
        {D45ANG   , D90ANG        },     //DIR26( 0, 1,-1)
        {D90ANG   , D0ANG         },     //DIR26( 0, 1, 0)
        {D45ANG   , D270ANG       },     //DIR26( 0, 1, 1)
        {D315ANG  , D90ANG-D45ANG },     //DIR26( 1,-1,-1)
        {D315ANG  , D0ANG         },     //DIR26( 1,-1, 0)
        {D315ANG  , D270ANG+D45ANG},     //DIR26( 1,-1, 1)
        {D180ANG  , D135ANG       },     //DIR26( 1, 0,-1)
        {D0ANG    , D0ANG         },     //DIR26( 1, 0, 0)
        {D0ANG    , D315ANG       },     //DIR26( 1, 0, 1)
        {D45ANG   , D90ANG-D45ANG },     //DIR26( 1, 1,-1)
        {D45ANG   , D0ANG         },     //DIR26( 1, 1, 0)
        {D45ANG   , D270ANG+D45ANG}      //DIR26( 1, 1, 1)
};
const GgafDx26DirectionUtil::RzRy* GgafDx26DirectionUtil::_face2rzry = &(GgafDx26DirectionUtil::_rzry[13]); //13 ‚Í 3*3*3=27 ‚Ì^‚ñ’†‚Ì—v‘fB_dir2sgn[-13`13]‚ÅƒAƒNƒZƒX‚·‚éˆ×


dir26 GgafDx26DirectionUtil::cnvVec2DirNo(float prm_vx, float prm_vy, float prm_vz) {
    int sgn_x, sgn_y, sgn_z;
    GgafDx26DirectionUtil::cnvVec2Sgn(prm_vx, prm_vy, prm_vz,
                              sgn_x, sgn_y, sgn_z);
    return DIR26(sgn_x, sgn_y, sgn_z);
}



void GgafDx26DirectionUtil::cnvVec2Sgn(float prm_vx, float prm_vy, float prm_vz,
                                       int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
    //”¼Œa‚P‚É“àÚ‚·‚é³”ªŠpŒ`‚Ì‚P•Ó‚Í 2ã2 - 2
    //                  y
    //                  ^
    //                  |
    //              ____|____
    //            ^   ^|   /_
    //          ^   v || 1/:  _
    //        ^       || / :    _
    //       |         v|/  :      | ƒÆ=3/8ƒÎ
    //      -+----------+---+------+---------> x
    //       |         0|<->       |
    //        _        | u      ^
    //          _      |      ^
    //            _QQ|QQ^
    //                  |
    // u = cos(3/8ƒÎ)  = 0.38268343236509
    // v = sin(3/8ƒÎ)  = 0.92387953251129

    static const float u = 0.38268343236509f;
    static const float v = 0.92387953251129f;

    float nvx, nvy, nvz;
    UTIL::getNormalizedVector(prm_vx, prm_vy, prm_vz,
                             nvx, nvy, nvz);

    //
    //     ^
    //     | u
    //     |____
    //    ^|   :_
    //   v||   :  _
    //    ||...:...._
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

    if (nvz < -u) {
        out_sgn_z = -1;
    } else if (u < nvz) {
        out_sgn_z = +1;
    } else {
        out_sgn_z = 0;
    }
}

void GgafDx26DirectionUtil::cnvVec2Sgn(float prm_vx, float prm_vy, float prm_vz,
                                       float& out_nvx, float& out_nvy, float& out_nvz,
                                       int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {

    static const float u = 0.38268343236509f;
    static const float v = 0.92387953251129f;

    UTIL::getNormalizedVector(prm_vx, prm_vy, prm_vz,
                              out_nvx, out_nvy, out_nvz);
    if (out_nvx < -u) {
        out_sgn_x = -1;
    } else if (u < out_nvx) {
        out_sgn_x = +1;
    } else {
        out_sgn_x = 0;
    }

    if (out_nvy < -u) {
        out_sgn_y = -1;
    } else if (u < out_nvy) {
        out_sgn_y = +1;
    } else {
        out_sgn_y = 0;
    }

    if (out_nvz < -u) {
        out_sgn_z = -1;
    } else if (u < out_nvz) {
        out_sgn_z = +1;
    } else {
        out_sgn_z = 0;
    }
}

void GgafDx26DirectionUtil::cnvDirNo2Vec(dir26 prm_dir_no, float& out_vx, float& out_vy, float& out_vz) {
    out_vx = GgafDx26DirectionUtil::_dir2vec[prm_dir_no].vx;
    out_vy = GgafDx26DirectionUtil::_dir2vec[prm_dir_no].vy;
    out_vz = GgafDx26DirectionUtil::_dir2vec[prm_dir_no].vz;
}

void GgafDx26DirectionUtil::cnvDirNo2Sgn(dir26 prm_dir_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
    out_sgn_x = GgafDx26DirectionUtil::_dir2sgn[prm_dir_no].sgn_x;
    out_sgn_y = GgafDx26DirectionUtil::_dir2sgn[prm_dir_no].sgn_y;
    out_sgn_z = GgafDx26DirectionUtil::_dir2sgn[prm_dir_no].sgn_z;
}

void GgafDx26DirectionUtil::cnvDirNo2RzRy(dir26 prm_dir_no, angle& out_rz, angle& out_ry) {
    out_rz = GgafDx26DirectionUtil::_face2rzry[prm_dir_no].rz;
    out_ry = GgafDx26DirectionUtil::_face2rzry[prm_dir_no].ry;
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
