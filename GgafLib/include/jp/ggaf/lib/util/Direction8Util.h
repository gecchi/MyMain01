#ifndef GGAF_LIB_DIRECTION8UTIL_H_
#define GGAF_LIB_DIRECTION8UTIL_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

//-1,0,1 の3数の3進法 を 配列要素のため正の10進数に変換するマクロ(-4～+4)
#define DIR8(X,Y) ((3*(X)) + (Y))
#define DIR8_NULL (999)

namespace GgafLib {

/**
 * 八方向ユーティリティ .
 * @version 1.00
 * @since 2015/09/16
 * @author Masatoshi Tsuge
 */
class Direction8Util {
private:
    struct FaceVec {
        float vx;
        float vy;
    };

    struct FaceSgn {
        int sgn_x;
        int sgn_y;
    };

    /** 面番号(方向番号)とベクトルのテーブル */
    static const FaceVec _vec[3*3];
    /** 面番号(方向番号)と各軸の正負のテーブル */
    static const FaceSgn _sgn[3*3];
    static const angle _angle[3*3];
public:
    static const FaceVec* _dir2vec;

    static const FaceSgn* _dir2sgn;

    static const angle* _dir2angle;

    /** 初期化用 */
    static bool is_init;

    static void init();

    /**
     * 中心からの方向ベクトルを、直近の八方向番号( DIR8(X,Y) )に変換 .
     * @param prm_vx 方向ベクトルX要素
     * @param prm_vy 方向ベクトルY要素
     * @return 直近の八方向番号( DIR8(X,Y) )、or DIR8_NULL
     */
    static dir8 cnvVec2DirNo(float prm_vx, float prm_vy);

    /**
     * 方向ベクトルを、直近の８方向に変換した場合の、XYZ軸各要素の正負の符号を取得 .
     * @param prm_vx 方向ベクトルX要素
     * @param prm_vy 方向ベクトルY要素
     * @param out_sgn_x X軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_y Y軸要素の正負 (-1 or 0 or 1)
     */
    static void cnvVec2Sgn(float prm_vx, float prm_vy,
                           int& out_sgn_x, int& out_sgn_y);

    static void cnvVec2Sgn(coord prm_vx, coord prm_vy,
                           int& out_sgn_x, int& out_sgn_y) {
        Direction8Util::cnvVec2Sgn(C_DX(prm_vx), C_DX(prm_vy),
                                         out_sgn_x, out_sgn_y);
    }

    /**
     * 八方向番号( DIR8(X,Y) )から、方向ベクトル（正規化済み）を取得 .
     * @param prm_dir_no 八方向番号( DIR8(X,Y) )
     * @param out_vx 方向ベクトルX要素
     * @param out_vy 方向ベクトルY要素
     */
    static void cnvDirNo2Vec(dir8 prm_dir_no, float& out_vx, float& out_vy);

    /**
     * 八方向番号( DIR8(X,Y) )から、XYZ軸各要素の正負の符号を取得 .
     * @param prm_dir_no 八方向番号( DIR8(X,Y) )、DIR_NNN ～ DIR_PPP
     * @param out_sgn_x X軸要素の正負 (-1 or 0 or 1)
     * @param out_sgn_y Y軸要素の正負 (-1 or 0 or 1)
     */
    static void cnvDirNo2Sgn(dir8 prm_dir_no, int& out_sgn_x, int& out_sgn_y);

    /**
     * 八方向番号( DIR8(X,Y) )から、RzRyの２軸アングル値を取得 .
     * @param prm_dir_no 八方向番号( DIR8(X,Y) )
     * @param out_rz
     * @param out_ry
     */
    static angle cnvDirNo2RzRy(dir8 prm_dir_no);

    static dir8 cnvAng2DirNo(angle prm_angle);

    static void cnvAng2Sgn(angle prm_angle, int& out_sgn_x, int& out_sgn_y);
};

}
#endif /*GGAF_LIB_DIRECTION26UTIL_H_*/
