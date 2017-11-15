#ifndef GGAFDXCORE_GGAFDXUTIL_H_
#define GGAFDXCORE_GGAFDXUTIL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafUtil.h"

#include <math.h>
#include "jp/ggaf/dxcore/util/GgafDxSphereRadiusVectors.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafDxCore::GgafDxUtil

////イベント用
HASHVAL(GGAF_EVENT_ON_DEVICE_LOST);
HASHVAL(GGAF_EVENT_ON_DEVICE_LOST_RESTORE);

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

    static GgafDxSphereRadiusVectors _srv;

    static bool _was_GgafDxUtil_inited_flg;



    static GgafDxCamera* _pCam;
public:
    static void init();

    /**
     * 平面上のベクトル(vx, vy) が作る原点のなす角を返す .
     * @param prm_vx ベクトル x 要素
     * @param prm_vy ベクトル y 要素
     * @return なす角のアングル値 (0 ～ 360000)
     */
    static angle getAngle2D(int prm_vx, int prm_vy) {
        if (prm_vx == 0) {
            if (prm_vy > 0) {
                return D90ANG;
            } else if (prm_vy < 0) {
                return D270ANG;
            } else {
                //原点である、不定。
                _TRACE_("＜警告＞ GgafDxUtil::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") は原点である、なす角は不定、0を返します。(1)");
                return 0;
            }
        } else if (prm_vy == 0) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return D180ANG;
            } else {
                _TRACE_("＜警告＞ GgafDxUtil::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") は原点である、なす角は不定、0を返します。(2)");
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
                _TRACE_("＜警告＞ GgafDxUtil::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") は原点である、なす角は不定、0を返します。(3)");
                return 0;
            }
        }
        if (ZEROd_EQ(prm_vy)) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return D180ANG;
            } else {
                _TRACE_("＜警告＞ GgafDxUtil::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") は原点である、なす角は不定、0を返します。(4)");
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
     * TURN_CLOSE_TO         ・・・ ターゲットの回転角と距離が近い方の回転方向で取得、左回りで正、又は、右回りの負の値になる。<BR>
     * TURN_ANTICLOSE_TO     ・・・ ターゲットの回転角と距離が遠回りの方の回転方向で取得、左回りで正、又は、右回りの負の値になる。<BR>
     * TURN_COUNTERCLOCKWISE ・・・ 回転方向が左回りで差異角取得、正の値で返る。<BR>
     * TURN_CLOCKWISE        ・・・ 回転方向が右回りで差異角取得、負の値で返る。<BR>
     * @param prm_from
     * @param prm_to
     * @param prm_way TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE
     * @return アングル値の差（結果が 反時計周りは正、時計回りは負)
     */
    static angle getAngDiff(angle prm_from, angle prm_to, int prm_way=TURN_CLOSE_TO);

    /**
     * 平面上において、'N'way弾(N=整数)の射出アングル値をセット(配列)で取得 .
     * @param prm_vx_Center     [in] 'N'way弾の全体として向いている方向の、方向ベクトルX要素
     * @param prm_vy_Center     [in] 'N'way弾の全体として向いている方向の、方向ベクトルY要素
     * @param prm_ways          [in] 'N'way弾の N
     * @param prm_clearance  [in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle       [out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_ways,
                              angle prm_clearance,
                              angle* out_paAngle);

    /**
     * 平面上において、'N'way弾(N=整数)の射出アングル値をセット(配列)で取得 .
     * @param prm_center     [in] 'N'way弾の全体として向いている方向のアングル値
     * @param prm_ways          [in] 'N'way弾の N
     * @param prm_clearance  [in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle       [out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getWayAngle2D(angle prm_center, int prm_ways, angle prm_clearance, angle* out_paAngle);

    /**
     * 平面上において、放射状全方向の'N'way弾(N=整数)のアングル値を配列で取得 .
     * 弾と弾との成す角は 均等になることとする。
     * 例えば全方向4way弾の場合、弾と弾との成す角は直角(90000)になる。
     * @param prm_start  放射状の全方向'N'way弾の１つ目の弾のアングル値
     * @param prm_ways  [in] 'N'way弾の N。
     * @param out_paAngle   [out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getRadialAngle2D(angle prm_start, int prm_ways, angle* out_paAngle);

    static void convRzRyToRyRz(angle prm_rz, angle prm_ry, angle& out_ry, angle& out_rz);

//    static void getWayAngle_LinedRzLongitude(angle prm_ang_center_rz, angle prm_ang_center_ry,
//                                           int prm_ways, angle prm_clearance,
//                                           angle* out_paAngleRz, angle* out_paAngleRy);

//    static void getMoveRzRyWayShot3D_XZ(int prm_ways, angle prm_clearance, coord prm_tx, coord prm_ty, coord prm_tz,
//                                        angle& out_faceZ, angle* out_paAngRotY);


    /**
     * アングル値の加算 .
     * D360ANG を超えた場合、或いは 0 を下回った場合でも、
     * 0～D360ANG に標準化される。
     * @param prm_angNow アングル値１
     * @param prm_ang_offset アングル値２
     * @return 標準化された アングル値１ + アングル値２ のアングル値
     */
    static angle addAng(angle prm_ang, angle prm_offset);

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
     * @param out_rz [out]Z軸回転アングル値
     * @param out_ry [out]Y軸回転アングル値
     */
    static void convVectorToRzRy(coord x,
                                 coord y,
                                 coord z,
                                 float& out_nvx,
                                 float& out_nvy,
                                 float& out_nvz,
                                 angle& out_rz,
                                 angle& out_ry);

    /**
     * 原点(0,0,0) からパラメータ座標(vx,vy,vz) を向く方向ベクトルに対応する「Z軸回転のアングル値」と「Y軸回転のアングル値」を取得 .
     * 本クラスの中核とも言うべきメソッドその１<BR>
     * 方向ベクトル -> Z軸Y軸回転方角 の変換<BR>
     * @param vx [in]X座標
     * @param vy [in]Y座標
     * @param vz [in]Z座標
     * @param out_rz [out]Z軸回転アングル値
     * @param out_ry [out]Y軸回転アングル値
     */
    static void convVectorToRzRy(coord vx, coord vy, coord vz, angle& out_rz, angle& out_ry);

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
     * @param out_rz [out]Z軸回転アングル値
     * @param out_ry [out]Y軸回転アングル値
     */
    static void convVectorToRzRy(double nvx, double nvy, double nvz, angle& out_rz, angle& out_ry) {
        convVectorToRzRy((int)(nvx*100000),
                         (int)(nvy*100000),
                         (int)(nvz*100000),
                         out_rz,
                         out_ry );
    }

    static void convVectorToRzRy(float nvx, float nvy, float nvz, angle& out_rz, angle& out_ry) {
        convVectorToRzRy((int)(nvx*100000),
                         (int)(nvy*100000),
                         (int)(nvz*100000),
                         out_rz,
                         out_ry );
    }

    /**
     * Z軸回転+Y軸回転値から単位方向ベクトルを取得
     * 本クラスの中核とも言うべきメソッドその2<BR>
     * Z軸Y軸回転方角 -> 方向ベクトル の変換<BR>
     * 計算せずにテーブル参照で高速に行う。<BR>
     * @param prm_rz [in]Z軸回転アングル値
     * @param prm_ry [in]Y軸回転アングル値
     * @param out_nvx [out]単位ベクトルX要素
     * @param out_nvy [out]単位ベクトルY要素
     * @param out_nvz [out]単位ベクトルZ要素
     */
    static void convRzRyToVector(angle prm_rz,
                                 angle prm_ry,
                                 float& out_nvx,
                                 float& out_nvy,
                                 float& out_nvz);

    /**
     * ベクトル正規化 .
     * @param x
     * @param y
     * @param out_nvx
     * @param out_nvy
     */
    static void getNormalizedVector(double x,
                                    double y,
                                    float& out_nvx,
                                    float& out_nvy) {
        const double t = 1.0 / sqrt(x * x + y * y);
        out_nvx = (float)(t * x);
        out_nvy = (float)(t * y);
    }

    /**
     * ベクトル正規化 .
     * @param x
     * @param y
     * @param out_nvx
     * @param out_nvy
     */
    static void getNormalizedVector(coord x,
                                    coord y,
                                    float& out_nvx,
                                    float& out_nvy ) {
        const double vx = (double)(x * (1.0 / (LEN_UNIT * PX_UNIT)));
        const double vy = (double)(y * (1.0 / (LEN_UNIT * PX_UNIT)));
        const double t = 1.0 / sqrt(vx * vx + vy * vy);
        out_nvx = (float)(t * vx);
        out_nvy = (float)(t * vy);
    }


    /**
     * ベクトル正規化 .
     * @param x
     * @param y
     * @param z
     * @param out_nvx
     * @param out_nvy
     * @param out_nvz
     */
    static void getNormalizedVector(double x,
                                    double y,
                                    double z,
                                    float& out_nvx,
                                    float& out_nvy,
                                    float& out_nvz ) {
        const double t = 1.0 / sqrt(x * x + y * y + z * z);
        out_nvx = (float)(t * x);
        out_nvy = (float)(t * y);
        out_nvz = (float)(t * z);
    }

    /**
     * ベクトル正規化 .
     * @param x
     * @param y
     * @param z
     * @param out_nvx
     * @param out_nvy
     * @param out_nvz
     */
    static void getNormalizedVector(coord x,
                                    coord y,
                                    coord z,
                                    float& out_nvx,
                                    float& out_nvy,
                                    float& out_nvz ) {
        const double vx = (double)(x * (1.0 / (LEN_UNIT * PX_UNIT)));
        const double vy = (double)(y * (1.0 / (LEN_UNIT * PX_UNIT)));
        const double vz = (double)(z * (1.0 / (LEN_UNIT * PX_UNIT)));
        const double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
        out_nvx = (float)(t * vx);
        out_nvy = (float)(t * vy);
        out_nvz = (float)(t * vz);
    }

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
     * アングル値の正規化 .
     * @param prm_ang アングル値
     * @return 0 ～ D360ANG の範囲に収められたアングル値
     */
    static inline angle simplifyAng(angle prm_ang) {
        if (0 <= prm_ang && prm_ang < D360ANG) {
            return prm_ang;
        } else if (prm_ang >= D360ANG) {
            return prm_ang % D360ANG;
        } else { // prm_ang < 0
            return D360ANG - ((-1 * prm_ang) % D360ANG);
        }
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
     * 原点中心の球面とベクトルの交点を求める
     * @param in_r  原点中心の球面の半径
     * @param in_x1   ベクトルFrom X要素
     * @param in_y1   ベクトルFrom Y要素
     * @param in_z1   ベクトルFrom Z要素
     * @param in_x2   ベクトルTo X要素
     * @param in_y2   ベクトルTo Y要素
     * @param in_z2   ベクトルTo Z要素
     * @param out_x   結果の交点X要素
     * @param out_y   結果の交点Y要素
     * @param out_z   結果の交点Z要素
     */
    template<typename T>
    static void getIntersectionSphereAndVec(double in_r,
                                            double in_x1, double in_y1, double in_z1,
                                            double in_x2, double in_y2, double in_z2,
                                            T& out_x, T& out_y, T& out_z) {
        double vx = in_x2 - in_x1;
        double vy = in_y2 - in_y1;
        double vz = in_z2 - in_z1;
        // 直線の座標(X,Y,Z)は
        //   X = x2 + t*vx;
        //   Y = y2 + t*vy;
        //   Z = z2 + t*vz;
        //である
        //これを球面の式
        //x^2 + y^2 + z^2 = r^2
        //に代入する
        //(x2 + t*vx)^2 + (y2 + t*vy)^2 + (z2 + t*vz)^2 = r^2
        //    t=-(sqrt((-vy^2-vx^2)*z2^2+(2*vy*vz*y2+2*vx*vz*x2)*z2+(-vz^2-vx^2)*y2^2+2*vx*vy*x2*y2+(-vz^2-vy^2)*
        //    x2^2+r^2*vz^2+r^2*vy^2+r^2*vx^2)+vz*z2+vy*y2+vx*x2)/(vz^2+vy^2+vx^2),
        //    t= (sqrt((-vy^2-vx^2)*z2^2+(2*vy*vz*y2+2*vx*vz*x2)*z2+(-vz^2-vx^2)*y2^2+2*vx*vy*x2*y2+(-vz^2-vy^2)*
        //    x2^2+r^2*vz^2+r^2*vy^2+r^2*vx^2)-vz*z2-vy*y2-vx*x2)/(vz^2+vy^2+vx^2)
        double vxvx = vx * vx;
        double vyvy = vy * vy;
        double vzvz = vz * vz;
        double x2x2 = in_x2 * in_x2;
        double y2y2 = in_y2 * in_y2;
        double z2z2 = in_z2 * in_z2;
        double rr = in_r * in_r;
        double t = (sqrt((-vyvy-vxvx)*z2z2+(2*vy*vz*in_y2+2*vx*vz*in_x2)*in_z2+(-vzvz-vxvx)*y2y2+2*vx*vy*in_x2*in_y2+(-vzvz-vyvy)*
                    x2x2+rr*vzvz+rr*vyvy+rr*vxvx)-vz*in_z2-vy*in_y2-vx*in_x2)/(vzvz+vyvy+vxvx);

        out_x = in_x2 + t*vx;
        out_y = in_y2 + t*vy;
        out_z = in_z2 + t*vz;
    }

    /**
     * ３頂点に接する面の法線ベクトルを求める .
     * 引数の頂点は時計回りに指定すると、その面の上が法線となる。
     * @param p1x
     * @param p1y
     * @param p1z
     * @param p2x
     * @param p2y
     * @param p2z
     * @param p3x
     * @param p3y
     * @param p3z
     * @param out_nvx
     * @param out_nvy
     * @param out_nvz
     */
    static void getPlaneNomalVec(float p1x, float p1y, float p1z,
                                 float p2x, float p2y, float p2z,
                                 float p3x, float p3y, float p3z,
                                 float& out_nvx, float& out_nvy, float& out_nvz, float& out_d);
    /**
     * world変換行列設定 .
     * 拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_ScRxRzRyMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);




    static void setWorldMatrix_ScRzRyMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RxRzRy(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_RxRzRy(angle prm_rx, angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld);


    /**
     * world変換行列設定 .
     * X軸回転 × Z軸回転 × Y軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRzRyScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRyRzScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Z軸回転 × X軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※Y軸回転がありません。_ryは２回目のX軸回転となる<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRzRxScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × 拡大縮小 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_ScRzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * ビルボードX軸回転 × ビルボードY軸回転 × ビルボードZ軸回転  × 拡大縮小 × 平行移動　の変換行列を作成＆デバイスに設定 <BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_BxyzScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScRzBxyzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScMvRxRzRy(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);


    static void mulWorldMatrix_ScRxRzRyMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& inout_matWorld);

    static void mulWorldMatrix_RzRyScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& inout_matWorld);


    static void setWorldMatrix_RzBxyzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_BxyzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_ScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    inline static void setWorldMatrix_RxRzRyMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
        //最もよく利用するWorld変換
        //X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
        //※XYZの順でないことに注意
        // | cosRz*cosRy                        , sinRz       , cosRz*-sinRy                        , 0 |
        // | (cosRx*-sinRz*cosRy + sinRx*sinRy) , cosRx*cosRz , (cosRx*-sinRz*-sinRy + sinRx*cosRy) , 0 |
        // | (-sinRx*-sinRz*cosRy + cosRx*sinRy), -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy), 0 |
        // | dx                                 , dy          , dz                                  , 1 |
        const float sinRx = ANG_SIN(prm_pActor->_rx);
        const float cosRx = ANG_COS(prm_pActor->_rx);
        const float sinRy = ANG_SIN(prm_pActor->_ry);
        const float cosRy = ANG_COS(prm_pActor->_ry);
        const float sinRz = ANG_SIN(prm_pActor->_rz);
        const float cosRz = ANG_COS(prm_pActor->_rz);

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

