#ifndef GGAFLIB_DirectionUtil_H_
#define GGAFLIB_DirectionUtil_H_
#include "GgafLibCommonHeader.h"

//Ternary numeral -1,0,1 の3数の3進法 を 配列要素のため正の10進数に変換するマクロ(-13～+13)
#define TN(X,Y,Z) (((3*3)*(X)) + (3*(Y)) + (Z))
typedef int face26;

namespace GgafLib {

/**
 * 斜方立方八面体２６方向ユーティリティ .
 * @version 1.00
 * @since 2014/12/11
 * @author Masatoshi Tsuge
 */
class DirectionUtil {
private:
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

    /** 面番号とベクトルのテーブル */
    static FaceVec _vec[3*3*3];
    /** 面番号と各軸の正負のテーブル */
    static FaceSgn _sgn[3*3*3];
    /** カメラのUP要素ベクトルの面番号と、視線の反対ベクトルの面番号との関連テーブル */
    static face26 _relation_up_vec[3*3*3][3*3*3];
public:
    /**
     * 斜方立方八面体の面番号定数 .
     */
    enum {
        FACE_NNN = TN(-1,-1,-1),     //-13
        FACE_NNZ = TN(-1,-1, 0),     //-12
        FACE_NNP = TN(-1,-1, 1),     //-11
        FACE_NZN = TN(-1, 0,-1),     //-10
        FACE_NZZ = TN(-1, 0, 0),     //-9
        FACE_NZP = TN(-1, 0, 1),     //-8
        FACE_NPN = TN(-1, 1,-1),     //-7
        FACE_NPZ = TN(-1, 1, 0),     //-6
        FACE_NPP = TN(-1, 1, 1),     //-5
        FACE_ZNN = TN( 0,-1,-1),     //-4
        FACE_ZNZ = TN( 0,-1, 0),     //-3
        FACE_ZNP = TN( 0,-1, 1),     //-2
        FACE_ZZN = TN( 0, 0,-1),     //-1
        FACE_ZZZ = TN( 0, 0, 0),     // 0   // 特別な方向が無いという方向。
        FACE_ZZP = TN( 0, 0, 1),     // 1
        FACE_ZPN = TN( 0, 1,-1),     // 2
        FACE_ZPZ = TN( 0, 1, 0),     // 3
        FACE_ZPP = TN( 0, 1, 1),     // 4
        FACE_PNN = TN( 1,-1,-1),     // 5
        FACE_PNZ = TN( 1,-1, 0),     // 6
        FACE_PNP = TN( 1,-1, 1),     // 7
        FACE_PZN = TN( 1, 0,-1),     // 8
        FACE_PZZ = TN( 1, 0, 0),     // 9
        FACE_PZP = TN( 1, 0, 1),     // 10
        FACE_PPN = TN( 1, 1,-1),     // 11
        FACE_PPZ = TN( 1, 1, 0),     // 12
        FACE_PPP = TN( 1, 1, 1),     // 13
        FACE_XXX = 666,
    };

    static FaceVec* _face2vec;

    static FaceSgn* _face2sgn;

    static int (*_relation_up_by_vec)[3*3*3];
    /** 初期化用 */
    static bool is_init;

    static void init();

    static face26 cnvVec2FaceNo(float prm_vx, float prm_vy, float prm_vz);

    static void cnvVec2Sgn(float prm_vx, float prm_vy, float prm_vz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    static void cnvFaceNo2Vec(face26 prm_face_no, float& out_vx, float& out_vy, float& out_vz);

    static void cnvFaceNo2Sgn(face26 prm_face_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

};

}
#endif /*GGAFLIB_DirectionUtil_H_*/
