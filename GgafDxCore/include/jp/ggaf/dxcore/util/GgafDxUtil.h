#ifndef GGAFDXCORE_GGAFDXUTIL_H_
#define GGAFDXCORE_GGAFDXUTIL_H_
#include "jp/ggaf/core/util/GgafUtil.h"

#include <math.h>
#include "jp/ggaf/dxcore/util/GgafDxSphereRadiusVectors.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxCamera.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafDxCore::GgafDxUtil

////イベント用 uint32_t 数値宣言
HASHVAL(GGAF_EVENT_ON_DEVICE_LOST);

namespace GgafDxCore {

/**
 * ユーティリティクラス .
 * 静的な座標計算関連関数はココに集約していこう。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxUtil : public GgafCore::GgafUtil {

    struct AngleSet {
        angle rz[D360SANG+1];
        angle ry[D360SANG+1];
    };

public:

    //static float PARABORA[];
    /**
     * cosテーブル .
     * 要素番号範囲：0 ~ D360SANG
     * angle値 r の cosは、COS[r/SANG_RATE]
     */
    static float COS[];
    /**
     * sinテーブル .
     * 要素番号範囲：0 ~ D360SANG
     * angle値 r の sin は、SIN[r/SANG_RATE]
     */
    static float SIN[];

    /**
     * 弧度法変換テーブル .
     * 要素番号範囲：0 ~ D360SANG
     * angle値 r のラディアンは、RAD[r/SANG_RATE]
     */
    static float RAD[];
    /**
     * [傾き] → angle値変換テーブル
     * 要素番号範囲：直線 y = ax 傾き a の 10000 倍の整数精度が要素番号となる。
     * 直線 y = ax の成す角のアングル値は SLANT2ANG[(int)a*10000] となる。
     */
    static angle SLANT2ANG[];
    /**
     * 平面射影時にできるなす角 → 2軸の回転角  の変換テーブル(その1-1) .
     * 方向ベクトルを、[XY平面へ射影した時のなす角][XZ平面へ射影した時のなす角] → 元の方向ベクトルのZ軸回転角 の変換テーブル
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_z[D90SANG+1][D90SANG+1];
    /**
     * 平面射影時にできるなす角 → 2軸の回転角  の変換テーブル(その1-2) .
     * 方向ベクトルを、[XY平面へ射影した時のなす角][XZ平面へ射影した時のなす角] → 元の方向ベクトルのY軸(逆)回転角 の変換テーブル
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_y_REV[D90SANG+1][D90SANG+1];
    /**
     * 平面射影時にできるなす角 → 2軸の回転角  の変換テーブル(その2-1) .
     * 方向ベクトルを、[ZY平面へ射影した時のなす角][ZX平面へ射影した時のなす角] → 元の方向ベクトルのX軸(逆)回転角 の変換テーブル
     */
    static angle PROJANG_ZY_ZX_TO_ROTANG_x_REV[D90SANG+1][D90SANG+1];
    /**
     * 平面射影時にできるなす角 → 2軸の回転角  の変換テーブル(その2-2) .
     * 方向ベクトルを、[ZY平面へ射影した時のなす角][ZX平面へ射影した時のなす角] → 元の方向ベクトルのY軸回転角 の変換テーブル
     */
    static angle PROJANG_ZY_ZX_TO_ROTANG_y[D90SANG+1][D90SANG+1];

    /**
     * v = 1 - cos(2πt)
     * の解テーブル
     * 【説明】
     * t:時間(フレーム)
     * v:速度
     * 面積＝移動距離
     * t = 0.0→0.5→1.0 対してなめらかに v = 0.0〜2.0〜0.0 と変化し、距離1.0を移動
     */
    static double SMOOTH_DV[3600+1];

    /**
     * 半径 1000 の 1/4 円の解テーブル .
     * <pre><code>
     *      ______________
     * y = √(1000^2-x^2)
     * </code></pre>
     * の 要素[x] に対する y
     */
    static float ROOT_1_MINUS_XX[1000];

    /**
     * 黄金角 .
     * 要素[x](0〜999) は x 番目の黄金角。
     */
    static angle GOLDEN_ANG[1000];

    static uint32_t BITNUM[];

    static GgafDxSphereRadiusVectors _srv;

    static bool _was_inited_flg;

    static GgafDxCamera* _pCam;
public:
    static void init();

    /**
     * 平面上のベクトル(vx, vy) が作る原点のなす角を返す .
     * @param prm_vx ベクトル x 要素
     * @param prm_vy ベクトル y 要素
     * @return なす角のアングル値 (0 〜 360000)
     */
    static angle getAngle2D(int prm_vx, int prm_vy) {
        if (prm_vx == 0) {
            if (prm_vy > 0) {
                return D90ANG;
            } else if (prm_vy < 0) {
                return D270ANG;
            } else {
                //原点である、不定。
                return 0;
            }
        }
        if (prm_vy == 0) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return D180ANG;
            } else {
                //原点である、不定。
                return 0;
            }
        }

        if (prm_vx >= 0 && prm_vy >= 0) { //第1象限
            if (prm_vx >= prm_vy) {
                return D0ANG  + SLANT2ANG[(int)(((double)prm_vy)/prm_vx*100000.0)];
            } else {
                return D90ANG - SLANT2ANG[(int)(((double)prm_vx)/prm_vy*100000.0)];
            }
        } else if (prm_vx <= 0 && prm_vy >= 0) { //第2象限
            if (-prm_vx <= prm_vy) {
                return D90ANG + SLANT2ANG[(int)(((double)-prm_vx)/prm_vy*100000.0)];
            } else {
                return D180ANG - SLANT2ANG[(int)(((double)prm_vy)/-prm_vx*100000.0)];
            }
        } else if (prm_vx <= 0 && prm_vy <= 0) { //第3象限
            if (-prm_vx >= -prm_vy) {
                return D180ANG + SLANT2ANG[(int)(((double)-prm_vy)/-prm_vx*100000.0)];
            } else {
                return D270ANG - SLANT2ANG[(int)(((double)-prm_vx)/-prm_vy*100000.0)];
            }
        } else if (prm_vx >= 0 && prm_vy <= 0) { //第4象限
            if (prm_vx <= -prm_vy) {
                return D270ANG + SLANT2ANG[(int)(((double)prm_vx)/-prm_vy*100000.0)];
            } else {
                return D360ANG - SLANT2ANG[(int)(((double)-prm_vy)/prm_vx*100000.0)];
            }
        }
        return 0;
    }

    static angle getAngle2D(double prm_vx, double prm_vy) {
        if (ZEROd_EQ(prm_vx)) {
            if (prm_vy > 0.0) {
                return D90ANG;
            } else if (prm_vy < 0.0) {
                return D270ANG;
            } else {
                //原点である、不定。
                return 0;
            }
        }
        if (ZEROd_EQ(prm_vy)) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return D180ANG;
            } else {
                //原点である、不定。
                return 0;
            }
        }

        if (prm_vx >= 0.0 && prm_vy >= 0.0) { //第1象限
            if (prm_vx >= prm_vy) {
                return D0ANG  + SLANT2ANG[(int)(prm_vy/prm_vx*100000.0)];
            } else {
                return D90ANG - SLANT2ANG[(int)(prm_vx/prm_vy*100000.0)];
            }
        } else if (prm_vx <= 0.0 && prm_vy >= 0.0) { //第2象限
            if (-prm_vx <= prm_vy) {
                return D90ANG  + SLANT2ANG[(int)(-prm_vx/prm_vy*100000.0)];
            } else {
                return D180ANG - SLANT2ANG[(int)(prm_vy/-prm_vx*100000.0)];
            }
        } else if (prm_vx <= 0.0 && prm_vy <= 0.0) { //第3象限
            if (-prm_vx >= -prm_vy) {
                return D180ANG + SLANT2ANG[(int)(-prm_vy/-prm_vx*100000.0)];
            } else {
                return D270ANG - SLANT2ANG[(int)(-prm_vx/-prm_vy*100000.0)];
            }
        } else if (prm_vx >= 0.0 && prm_vy <= 0.0) { //第4象限
            if (prm_vx <= -prm_vy) {
                return D270ANG + SLANT2ANG[(int)(prm_vx/-prm_vy*100000.0)];
            } else {
                return D360ANG - SLANT2ANG[(int)(-prm_vy/prm_vx*100000.0)];
            }
        }
        return 0;
    }

    /**
     * アングル値の差を取る .
     * TURN_COUNTERCLOCKWISE ・・・ 回転方向が左回りで差異角取得、正の値で返る。<BR>
     * TURN_CLOCKWISE        ・・・ 回転方向が右回りで差異角取得、負の値で返る。<BR>
     * TURN_CLOSE_TO         ・・・ ターゲットの回転角と距離が近い方の回転方向で取得、左回りで正、又は、右回りの負の値になる。<BR>
     * @param angFrom
     * @param angTo
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO
     * @return アングル値の差（結果が 反時計周りは正、時計回りは負)
     */
    static angle getAngDiff(angle angFrom, angle angTo, int prm_way=TURN_CLOSE_TO);

    /**
     * 平面上において、'N'way弾(N=整数)の射出アングル値をセット(配列)で取得 .
     * @param prm_vx_Center     [in] 'N'way弾の全体として向いている方向の、方向ベクトルX要素
     * @param prm_vy_Center     [in] 'N'way弾の全体として向いている方向の、方向ベクトルY要素
     * @param prm_nWay          [in] 'N'way弾の N
     * @param prm_angClearance  [in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle       [out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_nWay,
                              angle prm_angClearance,
                              int* out_paAngle);

    /**
     * 平面上において、'N'way弾(N=整数)の射出アングル値をセット(配列)で取得 .
     * @param prm_angCenter     [in] 'N'way弾の全体として向いている方向のアングル値
     * @param prm_nWay          [in] 'N'way弾の N
     * @param prm_angClearance  [in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle       [out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle);

    /**
     * 平面上において、放射状全方向の'N'way弾(N=整数)のアングル値を配列で取得 .
     * 弾と弾との成す角は 均等になることとする。
     * 例えば全方向4way弾の場合、弾と弾との成す角は直角(90000)になる。
     * @param prm_angStart  放射状の全方向'N'way弾の１つ目の弾のアングル値
     * @param prm_nWay  [in] 'N'way弾の N。
     * @param out_paAngle   [out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle);

    static void convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz);

//    static void getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
//                                           int prm_nWay, angle prm_angClearance,
//                                           angle* out_paAngleRz, angle* out_paAngleRy);

//    static void getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, coord prm_tx, coord prm_ty, coord prm_tz,
//                                        angle& out_angFaceZ, angle* out_paAngRotY);


    /**
     * アングル値の加算 .
     * D360ANG を超えた場合、或いは 0 を下回った場合でも、
     * 0〜D360ANG に標準化される。
     * @param prm_angNow アングル値１
     * @param prm_angOffset アングル値２
     * @return 標準化された アングル値１ + アングル値２ のアングル値
     */
    static angle addAng(angle prm_angNow, angle prm_angOffset);

    /**
     *
     * @param prm_x
     * @param prm_y
     * @param prm_ang
     * @param out_x
     * @param out_y
     */
    static void rotxy(coord prm_x, coord prm_y, angle prm_ang, coord& out_x, coord& out_y);

    /**
     * 距離計算(2D) .
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return
     */
    static int getDistance(coord x1, coord y1, coord x2, coord y2);

    /**
     * 距離計算(3D) .
     * @param x1
     * @param y1
     * @param z1
     * @param x2
     * @param y2
     * @param z2
     * @return
     */
    template<typename T>
    static T getDistance(T x1, T y1, T z1, T x2, T y2, T z2) {
        return (T)( sqrt(
                      (
                        ((double)(x2 - x1)) * ((double)(x2 - x1))
                      ) + (
                        ((double)(y2 - y1)) * ((double)(y2 - y1))
                      ) + (
                        ((double)(z2 - z1)) * ((double)(z2 - z1))
                      )
                    )
                 );
    }

    static double getDistance(GgafDxCore::GgafDxGeometricActor* pA1, GgafDxCore::GgafDxGeometricActor* pA2) {
        return sqrt(
                      (
                        ((double)(pA2->_x - pA1->_x)) * ((double)(pA2->_x - pA1->_x))
                      ) + (
                        ((double)(pA2->_y - pA1->_y)) * ((double)(pA2->_y - pA1->_y))
                      ) + (
                        ((double)(pA2->_z - pA1->_z)) * ((double)(pA2->_z - pA1->_z))
                      )
                    );
    }

    static double getDistance(GgafDxCore::GgafDxGeometricActor* pA1, GgafDxCore::GgafDxGeoElem* pA2) {
        return sqrt(
                      (
                        ((double)(pA2->x - pA1->_x)) * ((double)(pA2->x - pA1->_x))
                      ) + (
                        ((double)(pA2->y - pA1->_y)) * ((double)(pA2->y - pA1->_y))
                      ) + (
                        ((double)(pA2->z - pA1->_z)) * ((double)(pA2->z - pA1->_z))
                      )
                    );
    }

    static double getDistance(GgafDxCore::GgafDxGeoElem* pA1, GgafDxCore::GgafDxGeometricActor* pA2) {
        return sqrt(
                      (
                        ((double)(pA2->_x - pA1->x)) * ((double)(pA2->_x - pA1->x))
                      ) + (
                        ((double)(pA2->_y - pA1->y)) * ((double)(pA2->_y - pA1->y))
                      ) + (
                        ((double)(pA2->_z - pA1->z)) * ((double)(pA2->_z - pA1->z))
                      )
                    );
    }

    static double getDistance(GgafDxCore::GgafDxGeoElem* pA1 ,GgafDxCore::GgafDxGeoElem* pA2) {
        return sqrt(
                      (
                        ((double)(pA2->x - pA1->x)) * ((double)(pA2->x - pA1->x))
                      ) + (
                        ((double)(pA2->y - pA1->y)) * ((double)(pA2->y - pA1->y))
                      ) + (
                        ((double)(pA2->z - pA1->z)) * ((double)(pA2->z - pA1->z))
                      )
                    );
    }

    /**
     * 原点からパラメータ座標を向く方向ベクトルの、Z軸回転アングル値とY軸回転アングル値を取得 .
     * おまけで単位方向ベクトルもゲットできる。<BR>
     * Z軸回転アングル値とY軸回転アングル値を取得する過程で、<BR>
     * 方向ベクトルの正規化を行なわなければならないため、もったいないので戻り値に。<BR>
     * @param x [in]X座標
     * @param y [in]Y座標
     * @param z [in]Z座標
     * @param out_nvx [out]単位ベクトルX要素
     * @param out_nvy [out]単位ベクトルY要素
     * @param out_nvz [out]単位ベクトルZ要素
     * @param out_angRz [out]Z軸回転アングル値
     * @param out_angRy [out]Y軸回転アングル値
     */
    static void convVectorToRzRy(coord x,
                                 coord y,
                                 coord z,
                                 float& out_nvx,
                                 float& out_nvy,
                                 float& out_nvz,
                                 angle& out_angRz,
                                 angle& out_angRy);

    /**
     * 原点(0,0,0) からパラメータ座標(vx,vy,vz) を向く方向ベクトルに対応する「Z軸回転のアングル値」と「Y軸回転のアングル値」を取得 .
     * 本クラスの中核とも言うべきメソッドその１<BR>
     * 方向ベクトル -> Z軸Y軸回転方角 の変換<BR>
     * @param vx [in]X座標
     * @param vy [in]Y座標
     * @param vz [in]Z座標
     * @param out_angRz [out]Z軸回転アングル値
     * @param out_angRy [out]Y軸回転アングル値
     */
    static void convVectorToRzRy(coord vx, coord vy, coord vz, angle& out_angRz, angle& out_angRy);

    /**
     * 原点(0,0,0) からパラメータ座標を向く方向ベクトル(単位ベクトル)に対応する「Z軸回転のアングル値」と「Y軸回転のアングル値」を取得 .
     * 本クラスの中核とも言うべきメソッドその１<BR>
     * 方向ベクトル -> Z軸Y軸回転方角 の変換。<BR>
     * 計算せずにテーブル参照で高速に行う。<BR>
     * 処理中で、方向ベクトルの正規化を行わないので <BR>
     * convVectorToRzRy(int, int, int , angle&, angle&);
     * よりやや高速。単位ベクトルが求まっているときはこちらを使用しましょう。<BR>
     * @param nvx [in]単位ベクトルX要素
     * @param nvy [in]単位ベクトルY要素
     * @param nvz [in]単位ベクトルZ要素
     * @param out_angRz [out]Z軸回転アングル値
     * @param out_angRy [out]Y軸回転アングル値
     */
    static void convVectorToRzRy(double nvx, double nvy, double nvz, angle& out_angRz, angle& out_angRy) {
        convVectorToRzRy((int)(nvx*LEN_UNIT*PX_UNIT),
                         (int)(nvy*LEN_UNIT*PX_UNIT),
                         (int)(nvz*LEN_UNIT*PX_UNIT),
                         out_angRz,
                         out_angRy );
    }

    static void convVectorToRzRy(float nvx, float nvy, float nvz, angle& out_angRz, angle& out_angRy) {
        convVectorToRzRy((int)(nvx*LEN_UNIT*PX_UNIT),
                         (int)(nvy*LEN_UNIT*PX_UNIT),
                         (int)(nvz*LEN_UNIT*PX_UNIT),
                         out_angRz,
                         out_angRy );
    }


    /**
     * Z軸回転+Y軸回転値から単位方向ベクトルを取得
     * 本クラスの中核とも言うべきメソッドその2<BR>
     * Z軸Y軸回転方角 -> 方向ベクトル の変換<BR>
     * 計算せずにテーブル参照で高速に行う。<BR>
     * @param prm_angRz [in]Z軸回転アングル値
     * @param prm_angRy [in]Y軸回転アングル値
     * @param out_nvx [out]単位ベクトルX要素
     * @param out_nvy [out]単位ベクトルY要素
     * @param out_nvz [out]単位ベクトルZ要素
     */
    static void convRzRyToVector(angle prm_angRz,
                                 angle prm_angRy,
                                 float& out_nvx,
                                 float& out_nvy,
                                 float& out_nvz);
    /**
     * ベクトル正規化 .
     * @param x
     * @param y
     * @param z
     * @param out_nvx
     * @param out_nvy
     * @param out_nvz
     */
    static void getNormalizeVector(dxcoord x,
                                   dxcoord y,
                                   dxcoord z,
                                   float& out_nvx,
                                   float& out_nvy,
                                   float& out_nvz);

    /**
     * ベクトル正規化 .
     * @param x
     * @param y
     * @param z
     * @param out_nvx
     * @param out_nvy
     * @param out_nvz
     */
    static void getNormalizeVector(coord x,
                                   coord y,
                                   coord z,
                                   float& out_nvx,
                                   float& out_nvy,
                                   float& out_nvz);

    /**
     * 方向を変えず、Z軸回転+Y軸回転もう一つの組み合わせを返す。
     * @param rz1
     * @param ry1
     */
    static void anotherRzRy(angle& rz1, angle& ry1) {
        int rz2 = 0;
        int ry2 = 0;
        if (0 <= rz1 && rz1 < D90ANG) {
            rz2 = D180ANG - rz1;

            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D90ANG <= rz1 && rz1 < D180ANG) {
            rz2 = D180ANG - rz1;
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D180ANG <= rz1 && rz1 < D270ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D270ANG <= rz1 && rz1 <= D360ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        }
        rz1 = rz2;
        ry1 = ry2;
    }

    /**
     * RzRyの最適化を試みる。
     * 方向を変えず、Z軸回転+Y軸回転もう一つの組み合わせと比較し。
     * @param rz1
     * @param ry1
     */
    static void optimizeRzRy(angle& rz1, angle& ry1) {
        int rz2 = 0;
        int ry2 = 0;
        if (0 <= rz1 && rz1 < D90ANG) {
            rz2 = D180ANG - rz1;

            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D90ANG <= rz1 && rz1 < D180ANG) {
            rz2 = D180ANG - rz1;
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D180ANG <= rz1 && rz1 < D270ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D270ANG <= rz1 && rz1 <= D360ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        }
        rz1 = rz2;
        ry1 = ry2;
    }


    static inline angle simplifyAng(angle prm_ang) {
        if (0 <= prm_ang && prm_ang < D360ANG) {
            return prm_ang;
        }
        while (prm_ang >= D360ANG) {
            prm_ang -= D360ANG;
        }
        while (prm_ang < 0) {
            prm_ang += D360ANG;
        }
        return prm_ang;
    }


    /**
     * 線分の当たり判定<BR>
     * @param x11
     * @param y11
     * @param x12
     * @param y12
     * @param x21
     * @param y21
     * @param x22
     * @param y22
     * @return true:ヒット/false:ヒットしてない
     */
    static bool chk2DLineCrossing(coord x11, coord y11, coord x12, coord y12, coord x21, coord y21, coord x22, coord y22);



    /**
     * 移動加速度を、「停止時移動距離」「現時点の速度」により求める .
     * <pre><code>
     *
     *    速度(v)
     *     ^       a:減加速度    ・・・今回求める値
     *     |       D:移動距離    ・・・引数
     *     |      V0:現時点の速度・・・引数
     *   V0|      Te:停止するフレーム・・・求めません
     *     |＼
     *     |  ＼
     *     |    ＼ 斜辺の傾きa
     *     |   D  ＼
     *     |        ＼
     *   --+----------＼-----> 時間(t)
     *   0 |          Te
     * </code></pre>
     * 上図のような状態を想定し、引数の距離(D)から、加速度(a)を計算し設定している。<BR>
     * 停止までのフレーム(Te) は 距離(D) により変化するため指定不可。<BR>
     * @param D  v目標到達速度に達するまでに費やす距離(D)
     * @param V0 現時点の速度(V0)
     * @return 必要な加速度(a)
     */
    static inline double getAcceToStop(double D, double V0) {
        // D = (1/2) V0 Te  ・・・�@
        // a = -V0 / Te     ・・・�A
        // �@より
        // Te = 2D / V0
        // これを�Aへ代入
        // a = -V0 / (2D / V0)
        // ∴ a = -(V0^2) / 2D
        return -(V0*V0) / (2.0*D);
    }

    /**
     * 移動加速度を、「移動距離」「現時点の速度」「目標到達速度」により求める .
     * <pre><code>
     *    速度(v)
     *     ^        a:加速度      ・・・今回求める値
     *     |        D:移動距離    ・・・引数
     *     |       V0:現時点の速度・・・引数
     *     |       Vt:目標到達速度・・・引数
     *     |       Te:目標到達速度に達した時の時間・・・求めません
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> 時間(t)
     *   0 |        Te
     *
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、移動距離(D)から、加速度(a)を計算し設定している。<BR>
     * 目標到達まで必要なフレーム(Te) はパラメータにより変化するため指定不可。<BR>
     * @param D  v目標到達速度に達するまでに費やす距離(D)
     * @param V0 現時点の速度(V0)
     * @param Vt 目標到達速度(Vt)
     * @return 必要な加速度(a)
     */
    static inline double getAcceByD(double D, double V0, double Vt) {
        //D = (1/2) (V0 + Vt) Te   ・・・�@
        //a = (Vt - V0) / Te       ・・・�A
        //�Aより Te = (Vt - V0) / a
        //これを�@へ代入
        //D = (Vt^2 - V0^2) / 2a
        //∴ a = (Vt^2 - V0^2) / 2D
        return ((Vt*Vt) - (V0*V0)) / (2.0*D);
    }

    /**
     * 移動加速度を、「費やす時間」「現時点の速度」「目標到達速度」により求める .
     * <pre><code>
     *    速度(v)
     *     ^        a:加速度      ・・・今回求める値
     *     |        D:移動距離    ・・・求めません
     *     |       V0:現時点の速度・・・引数
     *     |       Vt:目標到達速度・・・引数
     *     |       Te:目標到達速度に達した時の時間・・・引数
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> 時間(tフレーム)
     *   0 |        Te
     *
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、その到達時間(Te) から、加速度(a)を計算し設定している。<BR>
     * 移動距離(D)は、パラメータにより変化するため指定不可。<BR>
     * @param Te 費やす時間(Te)
     * @param V0 現時点の速度(V0)
     * @param Vt 目標到達速度(Vt)
     * @return 必要な加速度(a)
     */
    static inline double getAcceByT(double Te, double V0, double Vt) {
        //a = (Vt-V0) / Te
        return (Vt - V0) / Te;
    }

    /**
     * world変換行列設定 .
     * 拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);




    static void setWorldMatrix_ScRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_RxRzRy(angle prm_rx, angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(angle prm_Rz, angle prm_Ry, D3DXMATRIX& out_matWorld);


    /**
     * world変換行列設定 .
     * X軸回転 × Z軸回転 × Y軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRyRzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Z軸回転 × X軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※Y軸回転がありません。_ryは２回目のX軸回転となる<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRzRxScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × 拡大縮小 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_ScRzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * ビルボードX軸回転 × ビルボードY軸回転 × ビルボードZ軸回転  × 拡大縮小 × 平行移動　の変換行列を作成＆デバイスに設定 <BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_BxyzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScRzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScMvRxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void mulWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld);

    static void mulWorldMatrix_RzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld);


    static void setWorldMatrix_RzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_BxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_ScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    inline static void setWorldMatrix_RxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
        //最もよく利用するWorld変換
        //X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
        //※XYZの順でないことに注意
        // | cosRz*cosRy                        , sinRz       , cosRz*-sinRy                        , 0 |
        // | (cosRx*-sinRz*cosRy + sinRx*sinRy) , cosRx*cosRz , (cosRx*-sinRz*-sinRy + sinRx*cosRy) , 0 |
        // | (-sinRx*-sinRz*cosRy + cosRx*sinRy), -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy), 0 |
        // | dx                                 , dy          , dz                                  , 1 |
        float sinRx = ANG_SIN(prm_pActor->_rx);
        float cosRx = ANG_COS(prm_pActor->_rx);
        float sinRy = ANG_SIN(prm_pActor->_ry);
        float cosRy = ANG_COS(prm_pActor->_ry);
        float sinRz = ANG_SIN(prm_pActor->_rz);
        float cosRz = ANG_COS(prm_pActor->_rz);

        out_matWorld._11 = cosRz*cosRy;
        out_matWorld._12 = sinRz;
        out_matWorld._13 = cosRz*-sinRy;
        out_matWorld._14 = 0.0f;

        out_matWorld._21 = (cosRx*-sinRz*cosRy + sinRx*sinRy);
        out_matWorld._22 = cosRx*cosRz;
        out_matWorld._23 = (cosRx*-sinRz*-sinRy + sinRx*cosRy);
        out_matWorld._24 = 0.0f;

        out_matWorld._31 = (-sinRx*-sinRz*cosRy + cosRx*sinRy);
        out_matWorld._32 = -sinRx*cosRz;
        out_matWorld._33 = (-sinRx*-sinRz*-sinRy + cosRx*cosRy);
        out_matWorld._34 = 0.0f;

        out_matWorld._41 = prm_pActor->_fX;
        out_matWorld._42 = prm_pActor->_fY;
        out_matWorld._43 = prm_pActor->_fZ;
        out_matWorld._44 = 1.0f;
    }
};

}
#endif /*GGAFDXCORE_GGAFDXUTIL_H_*/

