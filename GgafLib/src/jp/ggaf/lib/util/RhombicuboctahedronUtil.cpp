#include "jp/ggaf/lib/util/RhombicuboctahedronUtil.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

//Ternary numeral -1,0,1 ÇÃ3êîÇÃ3êiñ@ Ç îzóÒóvëfÇÃÇΩÇﬂê≥ÇÃ10êiêîÇ…ïœä∑Ç∑ÇÈÉ}ÉNÉç
#define TN(X,Y,Z) (((3*3)*((X)+1)) + (3*((Y)+1)) + ((Z)+1))

#define V3E (0.57735026918963)    // éŒÇﬂÇÃíPà ÉxÉNÉgÉãäeóvëf(t = (1.0 / Å„(1*1+1*1+1*1)) * 1 )
#define V2E (0.70710678118655)    // t = (1.0 / Å„(1*1+1*1)) * 1
RhombicuboctahedronUtil::FaceVec RhombicuboctahedronUtil::face_vec[28] = {
        {-V3E, -V3E, -V3E},      //0   FACE_ZRIGHT_DOWN_BEHIND = 0,     TN(-1,-1,-1)
        {-V2E, -V2E,    0},      //1   FACE_DOWN_BEHIND,                TN(-1,-1, 0)
        {-V3E, -V3E, +V3E},      //2   FACE_ZLEFT_DOWN_BEHIND,          TN(-1,-1, 1)
        {-V2E,    0, -V2E},      //3   FACE_ZRIGHT_BEHIND,              TN(-1, 0,-1)
        {  -1,    0,    0},      //4   FACE_BEHIND,                     TN(-1, 0, 0)
        {-V2E,    0, +V2E},      //5   FACE_ZLEFT_BEHIND,               TN(-1, 0, 1)
        {-V3E, +V3E, -V3E},      //6   FACE_ZRIGHT_UP_BEHIND,           TN(-1, 1,-1)
        {-V2E, +V2E,    0},      //7   FACE_UP_BEHIND,                  TN(-1, 1, 0)
        {-V3E, +V3E, +V3E},      //8   FACE_ZLEFT_UP_BEHIND,            TN(-1, 1, 1)
        {   0, -V2E, -V2E},      //9   FACE_ZRIGHT_DOWN,                TN( 0,-1,-1)
        {   0,   -1,    0},      //10  FACE_DOWN,                       TN( 0,-1, 0)
        {   0, -V2E, +V2E},      //11  FACE_ZLEFT_DOWN,                 TN( 0,-1, 1)
        {   0,    0,   -1},      //12  FACE_ZRIGHT,                     TN( 0, 0,-1)
        {   0,    0,    0},      //13  FACE_NONE,                       TN( 0, 0, 0)
        {   0,    0,   +1},      //14  FACE_ZLEFT,                      TN( 0, 0, 1)
        {   0, +V2E, -V2E},      //15  FACE_ZRIGHT_UP,                  TN( 0, 1,-1)
        {   0,   +1,    0},      //16  FACE_UP,                         TN( 0, 1, 0)
        {   0, +V2E, +V2E},      //17  FACE_ZLEFT_UP,                   TN( 0, 1, 1)
        {+V3E, -V3E, -V3E},      //18  FACE_ZRIGHT_DOWN_FRONT,          TN( 1,-1,-1)
        {+V2E, -V2E,    0},      //19  FACE_DOWN_FRONT,                 TN( 1,-1, 0)
        {+V3E, -V3E, +V3E},      //20  FACE_ZLEFT_DOWN_FRONT,           TN( 1,-1, 1)
        {+V2E,    0, -V2E},      //21  FACE_ZRIGHT_FRONT,               TN( 1, 0,-1)
        {  +1,    0,    0},      //22  FACE_FRONT,                      TN( 1, 0, 0)
        {+V2E,    0, +V2E},      //23  FACE_ZLEFT_FRONT,                TN( 1, 0, 1)
        {+V3E, +V3E, -V3E},      //24  FACE_ZRIGHT_UP_FRONT,            TN( 1, 1,-1)
        {+V2E, +V2E,    0},      //25  FACE_UP_FRONT,                   TN( 1, 1, 0)
        {+V3E, +V3E, +V3E}       //26  FACE_ZLEFT_UP_FRONT              TN( 1, 1, 1)
};

RhombicuboctahedronUtil::FaceVec RhombicuboctahedronUtil::face_sgn[28] = {
         {-1,-1,-1 },      //0   FACE_ZRIGHT_DOWN_BEHIND = 0,
         {-1,-1, 0 },      //1   FACE_DOWN_BEHIND,
         {-1,-1, 1 },      //2   FACE_ZLEFT_DOWN_BEHIND,
         {-1, 0,-1 },      //3   FACE_ZRIGHT_BEHIND,
         {-1, 0, 0 },      //4   FACE_BEHIND,
         {-1, 0, 1 },      //5   FACE_ZLEFT_BEHIND,
         {-1, 1,-1 },      //6   FACE_ZRIGHT_UP_BEHIND,
         {-1, 1, 0 },      //7   FACE_UP_BEHIND,
         {-1, 1, 1 },      //8   FACE_ZLEFT_UP_BEHIND,
         { 0,-1,-1 },      //9   FACE_ZRIGHT_DOWN,
         { 0,-1, 0 },      //10  FACE_DOWN,
         { 0,-1, 1 },      //11  FACE_ZLEFT_DOWN,
         { 0, 0,-1 },      //12  FACE_ZRIGHT,
         { 0, 0, 0 },      //13  FACE_NONE,
         { 0, 0, 1 },      //14  FACE_ZLEFT,
         { 0, 1,-1 },      //15  FACE_ZRIGHT_UP,
         { 0, 1, 0 },      //16  FACE_UP,
         { 0, 1, 1 },      //17  FACE_ZLEFT_UP,
         { 1,-1,-1 },      //18  FACE_ZRIGHT_DOWN_FRONT,
         { 1,-1, 0 },      //19  FACE_DOWN_FRONT,
         { 1,-1, 1 },      //20  FACE_ZLEFT_DOWN_FRONT,
         { 1, 0,-1 },      //21  FACE_ZRIGHT_FRONT,
         { 1, 0, 0 },      //22  FACE_FRONT,
         { 1, 0, 1 },      //23  FACE_ZLEFT_FRONT,
         { 1, 1,-1 },      //24  FACE_ZRIGHT_UP_FRONT,
         { 1, 1, 0 },      //25  FACE_UP_FRONT,
         { 1, 1, 1 },      //26  FACE_ZLEFT_UP_FRONT
};

int RhombicuboctahedronUtil::cnvVec2FaceNo(float prm_vx, float prm_vy, float prm_vz) {
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
    // u = (2Å„2 - 2) / 2 = Å„2 - 1 = 0.4142135623731
    // v = sin(3/8ÉŒ)               = 0.92387953251129

    static const float u = 0.4142135623731f;
    static const float v = 0.92387953251129f;

    float nvx, nvy, nvz;
    UTIL::getNormalizeVector(prm_vx, prm_vy, prm_vz,
                             nvx, nvy, nvz);

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

    int TNX = 0;
    int TNY = 0;
    int TNZ = 0;

    if (nvx >= 0 && nvy >= 0 && nvz >= 0) { //ëÊàÍè€å¿
        TNX = nvx >  u ?  1 : 0;
        TNY = nvy >  u ?  1 : 0;
        TNZ = nvz >  u ?  1 : 0;
    } else if (nvx <= 0 && nvy >= 0 && nvz >= 0) { //ëÊìÒè€å¿
        TNX = nvx < -u ? -1 : 0;
        TNY = nvy >  u ?  1 : 0;
        TNZ = nvz >  u ?  1 : 0;
    } else if (nvx <= 0 && nvy <= 0 && nvz >= 0) { //ëÊéOè€å¿
        TNX = nvx < -u ? -1 : 0;
        TNY = nvy < -u ? -1 : 0;
        TNZ = nvz >  u ?  1 : 0;
    } else if (nvx >= 0 && nvy <= 0 && nvz >= 0) { //ëÊélè€å¿
        TNX = nvx >  u ?  1 : 0;
        TNY = nvy < -u ? -1 : 0;
        TNZ = nvz >  u ?  1 : 0;
    } else if (nvx >= 0 && nvy >= 0 && nvz <= 0) { //ëÊå‹è€å¿
        TNX = nvx >  u ?  1 : 0;
        TNY = nvy >  u ?  1 : 0;
        TNZ = nvz < -u ? -1 : 0;
    } else if (nvx <= 0 && nvy >= 0 && nvz <= 0) { //ëÊòZè€å¿
        TNX = nvx < -u ? -1 : 0;
        TNY = nvy >  u ?  1 : 0;
        TNZ = nvz < -u ? -1 : 0;
    } else if (nvx <= 0 && nvy <= 0 && nvz <= 0) { //ëÊéµè€å¿
        TNX = nvx < -u ? -1 : 0;
        TNY = nvy < -u ? -1 : 0;
        TNZ = nvz < -u ? -1 : 0;
    } else if (nvx >= 0 && nvy <= 0 && nvz <= 0) { //ëÊî™è€å¿
        TNX = nvx >  u ?  1 : 0;
        TNY = nvy < -u ? -1 : 0;
        TNZ = nvz < -u ? -1 : 0;
    } else {
        throwGgafCriticalException("VVCameraWorker::cnvVec2FaceNo() Ç†ÇËÇ¶Ç»Ç¢("<<prm_vx<<","<<prm_vy<<","<<prm_vz<<")");
    }
    return TN(TNX, TNY, TNZ);
}

void RhombicuboctahedronUtil::cnvFaceNo2Vec(int prm_face_no, float& out_vx, float& out_vy, float& out_vz) {
    out_vx = RhombicuboctahedronUtil::face_vec[prm_face_no].vx;
    out_vy = RhombicuboctahedronUtil::face_vec[prm_face_no].vy;
    out_vz = RhombicuboctahedronUtil::face_vec[prm_face_no].vz;
}

void RhombicuboctahedronUtil::cnvFaceNo2Sgn(int prm_face_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
    out_sgn_x = RhombicuboctahedronUtil::face_sgn[prm_face_no].sgn_x;
    out_sgn_y = RhombicuboctahedronUtil::face_sgn[prm_face_no].sgn_y;
    out_sgn_z = RhombicuboctahedronUtil::face_sgn[prm_face_no].sgn_z;
}
