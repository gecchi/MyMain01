#ifndef GGAFDXCORE_GGAFDX26DIRECTIONUTIL_H_
#define GGAFDXCORE_GGAFDX26DIRECTIONUTIL_H_
#include "GgafDxCommonHeader.h"

//Ternary numeral -1,0,1 の3数の3進法 を 配列要素のため正の10進数に変換するマクロ(-13〜+13)
#define DIR26(X,Y,Z) (((3*3)*(X)) + (3*(Y)) + (Z))
#define DIR26_NULL (999)

namespace GgafDxCore {

/**
 * 斜方立方八面体２６方向ユーティリティ .
 * @version 1.00
 * @since 2014/12/11
 * @author Masatoshi Tsuge
 */
class GgafDx26DirectionUtil {
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

    struct RzRy {
        angle rz;
        angle ry;
    };

    /** 面番号(方向番号)とベクトルのテーブル */
    static const FaceVec _vec[3*3*3];
    /** 面番号(方向番号)と各軸の正負のテーブル */
    static const FaceSgn _sgn[3*3*3];
    /** 面番号(方向番号)とRzRy */
    static const RzRy _rzry[3*3*3];
public:
    static const FaceVec* _dir2vec;

    static const FaceSgn* _dir2sgn;

    static const RzRy* _face2rzry;

    /** 初期化用 */
    static bool is_init;

    static void init();

    /**
     * 中心からの方向ベクトルを、直近の斜方立方八面体の面番号(２６方向番号)に変換 .
     * @param prm_vx 方向ベクトルX要素
     * @param prm_vy 方向ベクトルY要素
     * @param prm_vz 方向ベクトルZ要素
     * @return 直近の斜方立方八面体の面番号(２６方向番号)、DIR_NNN 〜 DIR_PPP or FACE_XXX
     */
    static dir26 cnvVec2DirNo(float prm_vx, float prm_vy, float prm_vz);

    /**
     * 方向ベクトルを、直近の２６方向に変換した場合の、XYZ軸各要素の正負の符号を取得 .
     * @param prm_vx 方向ベクトルX要素
     * @param prm_vy 方向ベクトルY要素
     * @param prm_vz 方向ベクトルZ要素
     * @param out_sgn_x X軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_y Y軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_z Z軸要素の正負 (-1 or 0 or 1)
     */
    static void cnvVec2Sgn(float prm_vx, float prm_vy, float prm_vz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    /**
     * 斜方立方八面体の面番号(２６方向番号)から、方向ベクトル（正規化済み）を取得 .
     * @param prm_dir_no 斜方立方八面体の面番号(２６方向番号)、DIR_NNN 〜 DIR_PPP
     * @param out_vx 方向ベクトルX要素
     * @param out_vy 方向ベクトルY要素
     * @param out_vz 方向ベクトルZ要素
     */
    static void cnvDirNo2Vec(dir26 prm_dir_no, float& out_vx, float& out_vy, float& out_vz);

    /**
     * 斜方立方八面体の面番号(２６方向番号)から、XYZ軸各要素の正負の符号を取得 .
     * @param prm_dir_no 斜方立方八面体の面番号(２６方向番号)、DIR_NNN 〜 DIR_PPP
     * @param out_sgn_x X軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_y Y軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_z Z軸要素の正負 (-1 or 0 or 1)
     */
    static void cnvDirNo2Sgn(dir26 prm_dir_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    /**
     * 斜方立方八面体の面番号(２６方向番号)から、RzRyの２軸アングル値を取得 .
     * @param prm_dir_no 斜方立方八面体の面番号(２６方向番号)、DIR_NNN 〜 DIR_PPP
     * @param out_rz
     * @param out_ry
     */
    static void cnvDirNo2RzRy(dir26 prm_dir_no, angle& out_rz, angle& out_ry);


};

}
#endif /*GGAFDXCORE_GGAFDX26DIRECTIONUTIL_H_*/
