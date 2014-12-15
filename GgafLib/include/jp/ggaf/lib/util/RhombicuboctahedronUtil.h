#ifndef GGAFLIB_RHOMBICUBOCTAHEDRONUTIL_H_
#define GGAFLIB_RHOMBICUBOCTAHEDRONUTIL_H_
#include "GgafLibCommonHeader.h"

namespace GgafLib {

/**
 * 斜方立方八面体 ユーティリティ .
 * @version 1.00
 * @since 2014/12/11
 * @author Masatoshi Tsuge
 */
class RhombicuboctahedronUtil {
public:
    enum {
        FACE_ZRIGHT_DOWN_BEHIND = 0,   //0    TN(-1,-1,-1)
        FACE_DOWN_BEHIND,              //1    TN(-1,-1, 0)
        FACE_ZLEFT_DOWN_BEHIND,        //2    TN(-1,-1, 1)
        FACE_ZRIGHT_BEHIND,            //3    TN(-1, 0,-1)
        FACE_BEHIND,                   //4    TN(-1, 0, 0)
        FACE_ZLEFT_BEHIND,             //5    TN(-1, 0, 1)
        FACE_ZRIGHT_UP_BEHIND,         //6    TN(-1, 1,-1)
        FACE_UP_BEHIND,                //7    TN(-1, 1, 0)
        FACE_ZLEFT_UP_BEHIND,          //8    TN(-1, 1, 1)
        FACE_ZRIGHT_DOWN,              //9    TN( 0,-1,-1)
        FACE_DOWN,                     //10   TN( 0,-1, 0)
        FACE_ZLEFT_DOWN,               //11   TN( 0,-1, 1)
        FACE_ZRIGHT,                   //12   TN( 0, 0,-1)
        FACE_NONE,                     //13   TN( 0, 0, 0)
        FACE_ZLEFT,                    //14   TN( 0, 0, 1)
        FACE_ZRIGHT_UP,                //15   TN( 0, 1,-1)
        FACE_UP,                       //16   TN( 0, 1, 0)
        FACE_ZLEFT_UP,                 //17   TN( 0, 1, 1)
        FACE_ZRIGHT_DOWN_FRONT,        //18   TN( 1,-1,-1)
        FACE_DOWN_FRONT,               //19   TN( 1,-1, 0)
        FACE_ZLEFT_DOWN_FRONT,         //20   TN( 1,-1, 1)
        FACE_ZRIGHT_FRONT,             //21   TN( 1, 0,-1)
        FACE_FRONT,                    //22   TN( 1, 0, 0)
        FACE_ZLEFT_FRONT,              //23   TN( 1, 0, 1)
        FACE_ZRIGHT_UP_FRONT,          //24   TN( 1, 1,-1)
        FACE_UP_FRONT,                 //25   TN( 1, 1, 0)
        FACE_ZLEFT_UP_FRONT,           //26   TN( 1, 1, 1)
    };

    struct FaceVec {
        float vx;
        float vy;
        float vz;
    };

    struct FaceSgn {
        int sgn_x;
        int sgn_y;
        int sgn_z;
    };

    static FaceVec face_vec[27];
    static FaceSgn face_sgn[27];
    static int relation_up_vec[27][27];
    static bool unused;

    static void initialize();

    static int cnvVec2FaceNo(float vx, float vy, float vz);

    static void cnvFaceNo2Vec(int prm_face_no, float& out_vx, float& out_vy, float& out_vz);

    static void cnvFaceNo2Sgn(int prm_face_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

};

}
#endif /*GGAFLIB_RHOMBICUBOCTAHEDRONUTIL_H_*/
