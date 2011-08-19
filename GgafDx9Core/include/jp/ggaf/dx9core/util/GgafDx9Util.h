#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_
namespace GgafDx9Core {

#define sgn(X) (GgafDx9Core::GgafDx9Util::sign(X))
#define max3(A,B,C) (GgafDx9Core::GgafDx9Util::max3(A,B,C))




/**
 * ユーティリティクラス .
 * 静的な座標計算関連関数はココに集約していこう。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDx9Util: public GgafCore::GgafUtil {

    struct AngleSet {
        angle RZ[S_ANG360+1];
        angle RY[S_ANG360+1];
    };

public:

    static float PARABORA[];
    /**
     * cosテーブル .
     * 要素番号範囲：0 ~ S_ANG360
     * angle値 r の cosは、COS[r/ANGLE_RATE]
     */
    static float COS[];
    /**
     * sinテーブル .
     * 要素番号範囲：0 ~ S_ANG360
     * angle値 r の sin は、SIN[r/ANGLE_RATE]
     */
    static float SIN[];
    /**
     * 弧度法変換テーブル .
     * 要素番号範囲：0 ~ S_ANG360
     * angle値 r のラディアンは、RAD[r/ANGLE_RATE]
     */
    static float RAD[];
    /**
     * [傾き] → angle値変換テーブル
     * 要素番号範囲：直線 y = ax 傾き a の 10000 倍の整数精度が要素番号となる。
     * 直線 y = ax の成す角のアングル値は SLANT2ANG[(int)a*10000] となる。
     */
    static angle SLANT2ANG[];
    /**
     * 平面射影時にできるなす角 → 2軸回角  の変換テーブル(その1-1) .
     * 方向ベクトルを、[XY平面へ射影した時のなす角][XZ平面へ射影した時のなす角] → 元の方向ベクトルのZ軸回転角 の変換テーブル
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_Z[S_ANG90+1][S_ANG90+1];
    /**
     * 平面射影時にできるなす角 → 2軸回角  の変換テーブル(その1-2) .
     * 方向ベクトルを、[XY平面へ射影した時のなす角][XZ平面へ射影した時のなす角] → 元の方向ベクトルのY軸(逆)回転角 の変換テーブル
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_Y_REV[S_ANG90+1][S_ANG90+1];
    /**
     * 平面射影時にできるなす角 → 2軸回角  の変換テーブル(その2-1) .
     * 方向ベクトルを、[ZY平面へ射影した時のなす角][ZX平面へ射影した時のなす角] → 元の方向ベクトルのX軸(逆)回転角 の変換テーブル
     */
    static angle PROJANG_ZY_ZX_TO_ROTANG_X_REV[S_ANG90+1][S_ANG90+1];
    /**
     * 平面射影時にできるなす角 → 2軸回角  の変換テーブル(その2-2) .
     * 方向ベクトルを、[ZY平面へ射影した時のなす角][ZX平面へ射影した時のなす角] → 元の方向ベクトルのY軸回転角 の変換テーブル
     */
    static angle PROJANG_ZY_ZX_TO_ROTANG_Y[S_ANG90+1][S_ANG90+1];

    //static AngleSet ROTY_ANGLE[S_ANG360+1];


    /**
     * 半径 1000 の 1/4 円の解テーブル .
     *      ______________
     * y = √(1000^2-x^2)
     * の 要素[x] に対する y
     */
    static float ROOT_1_MINUS_XX[1000];


    static GgafDx9SphereRadiusVectors _srv;

    static bool _was_inited_flg;

    static void init();

    /**
     * 平面上のベクトル(vx, vy) が作る原点のなす角を返す .
     * @param prm_vx ベクトル x 要素
     * @param prm_vy ベクトル y 要素
     * @return なす角のアングル値 (0 〜 360000)
     */
    template<typename T>
    static angle getAngle2D(T prm_vx, T prm_vy) {
        if (prm_vx == 0) {
            if (prm_vy > 0) {
                return ANGLE90;
            } else if (prm_vy < 0) {
                return ANGLE270;
            } else {
                //原点である、不定。
                return 0;
            }
        }
        if (prm_vy == 0) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return ANGLE180;
            } else {
                //原点である、不定。
                return 0;
            }
        }
        if (prm_vx >= 0 && prm_vy >= 0) { //第1象限
            if (prm_vx >= prm_vy) {
                return ANGLE0  + SLANT2ANG[(int)(1.0*prm_vy/prm_vx*100000)];
            } else {
                return ANGLE90 - SLANT2ANG[(int)(1.0*prm_vx/prm_vy*100000)];
            }
        } else if (prm_vx <= 0 && prm_vy >= 0) { //第2象限
            if (-prm_vx <= prm_vy) {
                return ANGLE90 + SLANT2ANG[(int)(1.0*-prm_vx/prm_vy*100000)];
            } else {
                return ANGLE180 - SLANT2ANG[(int)(1.0*prm_vy/-prm_vx*100000)];
            }
        } else if (prm_vx <= 0 && prm_vy <= 0) { //第3象限
            if (-prm_vx >= -prm_vy) {
                return ANGLE180 + SLANT2ANG[(int)(1.0*-prm_vy/-prm_vx*100000)];
            } else {
                return ANGLE270 - SLANT2ANG[(int)(1.0*-prm_vx/-prm_vy*100000)];
            }
        } else if (prm_vx >= 0 && prm_vy <= 0) { //第4象限
            if (prm_vx <= -prm_vy) {
                return ANGLE270 + SLANT2ANG[(int)(1.0*prm_vx/-prm_vy*100000)];
            } else {
                return ANGLE360 - SLANT2ANG[(int)(1.0*-prm_vy/prm_vx*100000)];
            }
        }
        return 0;
    }

    /**
     * アングル値の差を取る .
     * TURN_COUNTERCLOCKWISE ・・・ 回転方向が左回りで差異角取得、正の値で返る。<BR>
     * TURN_CLOCKWISE        ・・・ 回転方向が右回りで差異角取得、負の値で返る。<BR>
     * TURN_CLOSE_TO         ・・・ ターゲットの回転角と距離が近い方の回転方向で取得、正又は負の値になる。<BR>
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
     * @param prm_nWay	        [in] 'N'way弾の N
     * @param prm_angClearance	[in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle	    [out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_nWay,
                              angle prm_angClearance,
                              int* out_paAngle);

    /**
     * 平面上において、'N'way弾(N=整数)の射出アングル値をセット(配列)で取得 .
     * @param prm_angCenter	    [in]'N'way弾の全体として向いている方向のアングル値
     * @param prm_nWay	        [in] 'N'way弾の N
     * @param prm_angClearance	[in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle	    [out] 得られる'N'way弾 のアングル値配列のポインタ
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

//    static void getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, coord prm_tX, coord prm_tY, coord prm_tZ,
//                                        angle& out_angFaceZ, angle* out_paAngRotY);


    /**
     *
     * @param prm_angNow
     * @param prm_angOffset
     * @return
     */
    static angle addAng(angle prm_angNow, angle prm_angOffset);

    /**
     *
     * @param prm_X
     * @param prm_Y
     * @param prm_ang
     * @param out_X
     * @param out_Y
     */
    static void rotXY(coord prm_X, coord prm_Y, angle prm_ang, coord& out_X, coord& out_Y);

    /**
     *
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return
     */
    static int getDistance(coord x1, coord y1, coord x2, coord y2);

    /**
     * 距離計算 .
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


    static double getDistance(GgafDx9Core::GgafDx9GeometricActor* pA1, GgafDx9Core::GgafDx9GeometricActor* pA2) {
        return sqrt(
                      (
                        ((double)(pA2->_X - pA1->_X)) * ((double)(pA2->_X - pA1->_X))
                      ) + (
                        ((double)(pA2->_Y - pA1->_Y)) * ((double)(pA2->_Y - pA1->_Y))
                      ) + (
                        ((double)(pA2->_Z - pA1->_Z)) * ((double)(pA2->_Z - pA1->_Z))
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
     * @param out_angFaceZ [out]Z軸回転アングル値
     * @param out_angFaceY [out]Y軸回転アングル値
     */
    static void getRzRyAng(coord x,
                           coord y,
                           coord z,
                           float& out_nvx,
                           float& out_nvy,
                           float& out_nvz,
                           angle& out_angFaceZ,
                           angle& out_angFaceY);

    /**
     * 原点からパラメータ座標を向く方向ベクトルに対応する「Z軸回転のアングル値」と「Y軸回転のアングル値」を取得 .
     * 本クラスの中核とも言うべきメソッドその１<BR>
     * 方向ベクトル -> Z軸Y軸回転方角 の変換<BR>
     * @param x [in]X座標
     * @param y [in]Y座標
     * @param z [in]Z座標
     * @param out_angFaceZ [out]Z軸回転アングル値
     * @param out_angFaceY [out]Y軸回転アングル値
     */
    static void getRzRyAng(coord x, coord y, coord z, angle& out_angFaceZ, angle& out_angFaceY);

    /**
     * 原点からパラメータ座標を向く方向ベクトル(単位ベクトル)に対応する「Z軸回転のアングル値」と「Y軸回転のアングル値」を取得 .
     * 本クラスの中核とも言うべきメソッドその１<BR>
     * 方向ベクトル -> Z軸Y軸回転方角 の変換。<BR>
     * 計算せずにテーブル参照で高速に行う。<BR>
     * 処理中で、方向ベクトルの正規化を行わないので <BR>
     * getRzRyAng(int, int, int , angle&, angle&);
     * よりやや高速。単位ベクトルが求まっているときはこちらを使用しましょう。<BR>
     * @param nvx [in]単位ベクトルX要素
     * @param nvy [in]単位ベクトルY要素
     * @param nvz [in]単位ベクトルZ要素
     * @param out_angFaceZ [out]Z軸回転アングル値
     * @param out_angFaceY [out]Y軸回転アングル値
     */
    static void getRzRyAng(double nvx, double nvy, double nvz, angle& out_angFaceZ, angle& out_angFaceY) {
        getRzRyAng((int)(nvx*LEN_UNIT*PX_UNIT),
                   (int)(nvy*LEN_UNIT*PX_UNIT),
                   (int)(nvz*LEN_UNIT*PX_UNIT),
                   out_angFaceZ,
                   out_angFaceY );
    }

    static void getRzRyAng(float nvx, float nvy, float nvz, angle& out_angFaceZ, angle& out_angFaceY) {
        getRzRyAng((int)(nvx*LEN_UNIT*PX_UNIT),
                   (int)(nvy*LEN_UNIT*PX_UNIT),
                   (int)(nvz*LEN_UNIT*PX_UNIT),
                   out_angFaceZ,
                   out_angFaceY );


    }


    /**
     * Z軸回転+Y軸回転値から単位方向ベクトルを取得
     * 本クラスの中核とも言うべきメソッドその2<BR>
     * Z軸Y軸回転方角 -> 方向ベクトル の変換<BR>
     * 計算せずにテーブル参照で高速に行う。<BR>
     * @param prm_angFaceZ [in]Z軸回転アングル値
     * @param prm_angFaceY [in]Y軸回転アングル値
     * @param out_nvx [out]単位ベクトルX要素
     * @param out_nvy [out]単位ベクトルY要素
     * @param out_nvz [out]単位ベクトルZ要素
     */
    static void getNormalizeVectorZY(angle prm_angFaceZ,
                                     angle prm_angFaceY,
                                     float& out_nvx,
                                     float& out_nvy,
                                     float& out_nvz);

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
        if (0 <= rz1 && rz1 < ANGLE90) {
            rz2 = ANGLE180 - rz1;

            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE90 <= rz1 && rz1 < ANGLE180) {
            rz2 = ANGLE180 - rz1;
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE180 <= rz1 && rz1 < ANGLE270) {
            rz2 = ANGLE180 + (ANGLE360 - rz1);
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE270 <= rz1 && rz1 <= ANGLE360) {
            rz2 = ANGLE180 + (ANGLE360 - rz1);
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
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
        if (0 <= rz1 && rz1 < ANGLE90) {
            rz2 = ANGLE180 - rz1;

            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE90 <= rz1 && rz1 < ANGLE180) {
            rz2 = ANGLE180 - rz1;
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE180 <= rz1 && rz1 < ANGLE270) {
            rz2 = ANGLE180 + (ANGLE360 - rz1);
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE270 <= rz1 && rz1 <= ANGLE360) {
            rz2 = ANGLE180 + (ANGLE360 - rz1);
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        }
        rz1 = rz2;
        ry1 = ry2;
    }


    static angle simplifyAng(angle prm_ang) {
        angle angSimple = prm_ang;
        while (angSimple >= ANGLE360) {
            angSimple -= ANGLE360;
        }
        while (angSimple < 0) {
            angSimple += ANGLE360;
        }
        return angSimple;
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
     * world変換行列設定 .
     * 拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);




    static void setWorldMatrix_ScRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_RxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Z軸回転 × Y軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※XYZの順でないことに注意<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Y軸回転 × Z軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * X軸回転 × Z軸回転 × X軸回転 × 拡大縮小 × 平行移動 の変換行列を設定<BR>
     * ※Y軸回転がありません。_RYは２回目のX軸回転となる<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RxRzRxScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_RzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * 単位行列 × 拡大縮小 × Z軸回転 × 平行移動 の変換行列を設定<BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_ScRzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world変換行列設定 .
     * ビルボードX軸回転 × ビルボードY軸回転 × ビルボードZ軸回転  × 拡大縮小 × 平行移動　の変換行列を作成＆デバイスに設定 <BR>
     * @param prm_pActor [in]対象アクター
     * @param out_matWorld [out]world変換行列
     */
    static void setWorldMatrix_BxyzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScRzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScMvRxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void mulWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld);

    static void mulWorldMatrix_RzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld);

    static void setWorldMatrix_RxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_ScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

};

}
#endif /*GGAFDX9UTIL_H_*/

