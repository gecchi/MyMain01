#ifndef GGAF_LIB_DIRECTION26UTIL_H_
#define GGAF_LIB_DIRECTION26UTIL_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

//-1,0,1 の3数の3進法 を 配列要素のため正の10進数に変換するマクロ(-13～+13)
#define DIR26(X,Y,Z) (((3*3)*(X)) + (3*(Y)) + (Z))
#define DIR26_NULL (999)

namespace GgafLib {

/**
 * 斜方立方八面体の面（２６方向）ユーティリティ .
 * @version 1.00
 * @since 2014/12/11
 * @author Masatoshi Tsuge
 */
class Direction26Util {
private:
    struct FaceVec {
        double vx;
        double vy;
        double vz;
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

    /**
     * 中心からの方向ベクトルを、直近の斜方立方八面体の面番号(２６方向番号)に変換 .
     * @param prm_vx 方向ベクトルX要素
     * @param prm_vy 方向ベクトルY要素
     * @param prm_vz 方向ベクトルZ要素
     * @return 直近の斜方立方八面体の面番号(２６方向番号)、DIR_NNN ～ DIR_PPP or FACE_XXX
     */
    static dir26 cnvVec2DirNo(double prm_vx, double prm_vy, double prm_vz);

    /**
     * 方向ベクトルを、直近の２６方向に変換した場合の、XYZ軸各要素の正負の符号を取得 .
     * @param prm_vx 方向ベクトルX要素
     * @param prm_vy 方向ベクトルY要素
     * @param prm_vz 方向ベクトルZ要素
     * @param out_sgn_x X軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_y Y軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_z Z軸要素の正負 (-1 or 0 or 1)
     */
    static void cnvVec2Sgn(double prm_vx, double prm_vy, double prm_vz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    static void cnvVec2Sgn(coord prm_vx, coord prm_vy, coord prm_vz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
        Direction26Util::cnvVec2Sgn(C_DX(prm_vx), C_DX(prm_vy), C_DX(prm_vz),
                                    out_sgn_x, out_sgn_y, out_sgn_z);
    }

    static void cnvVec2Sgn(double prm_vx, double prm_vy, double prm_vz,
                           double& out_nvx, double& out_nvy, double& out_nvz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    static void cnvVec2Sgn(coord prm_vx, coord prm_vy, coord prm_vz,
                           double& out_nvx, double& out_nvy, double& out_nvz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
        Direction26Util::cnvVec2Sgn(C_DX(prm_vx), C_DX(prm_vy), C_DX(prm_vz),
                                          out_nvx, out_nvy, out_nvz,
                                          out_sgn_x, out_sgn_y, out_sgn_z);
    }
    /**
     * 斜方立方八面体の面番号(２６方向番号)から、方向ベクトル（正規化済み）を取得 .
     * @param prm_dir_no 斜方立方八面体の面番号(２６方向番号)、DIR_NNN ～ DIR_PPP
     * @param out_vx 方向ベクトルX要素
     * @param out_vy 方向ベクトルY要素
     * @param out_vz 方向ベクトルZ要素
     */
    static void cnvDirNo2Vec(dir26 prm_dir_no, double& out_vx, double& out_vy, double& out_vz);

    /**
     * 斜方立方八面体の面番号(２６方向番号)から、XYZ軸各要素の正負の符号を取得 .
     * @param prm_dir_no 斜方立方八面体の面番号(２６方向番号)、DIR_NNN ～ DIR_PPP
     * @param out_sgn_x X軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_y Y軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_z Z軸要素の正負 (-1 or 0 or 1)
     */
    static void cnvDirNo2Sgn(dir26 prm_dir_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    /**
     * 斜方立方八面体の面番号(２６方向番号)から、RzRyの２軸アングル値を取得 .
     * @param prm_dir_no 斜方立方八面体の面番号(２６方向番号)、DIR_NNN ～ DIR_PPP
     * @param out_rz
     * @param out_ry
     */
    static void cnvDirNo2RzRy(dir26 prm_dir_no, angle& out_rz, angle& out_ry);


};

}
#endif /*GGAF_LIB_DIRECTION26UTIL_H_*/
