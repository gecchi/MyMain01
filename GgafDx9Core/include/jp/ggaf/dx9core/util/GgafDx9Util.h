#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_
namespace GgafDx9Core {

#define sgn(X) (GgafDx9Util::sign(X))
#define max3(A,B,C) (GgafDx9Util::max3(A,B,C))

/**
 * ユーティリティ.
 * 独立した静的な座標関連関数はココに集約。
 */
class GgafDx9Util: GgafCore::GgafUtil {

public:
    static int COS_UNITLEN[];
    static int SIN_UNITLEN[];
    static int TAN_UNITLEN[];
    static int RAD_UNITLEN[];
    static float PARABORA[];
    static float COS[];
    static float SIN[];
    static float RAD[];

    static int SLANT_ANG_0[];


    static GgafDx9SphereRadiusVectors _srv;

    static bool _was_inited_flg;

    static void init();

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
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE0+SLANT_ANG_0["<<(int)(1.0*prm_vy/prm_vx*10000)<<"]="<<(ANGLE0+SLANT_ANG_0[(int)(1.0*prm_vy/prm_vx*10000)]));
                return ANGLE0  + SLANT_ANG_0[(int)(1.0*prm_vy/prm_vx*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE90-SLANT_ANG_0["<<(int)(1.0*prm_vy/prm_vx*10000)<<"]="<<(ANGLE90-SLANT_ANG_0[(int)(1.0*prm_vy/prm_vx*10000)]));
                return ANGLE90 - SLANT_ANG_0[(int)(1.0*prm_vx/prm_vy*10000)];
            }
        } else if (prm_vx <= 0 && prm_vy >= 0) { //第2象限
            if (-prm_vx <= prm_vy) {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE90+SLANT_ANG_0["<<(int)(1.0*-prm_vx/prm_vy*10000)<<"]="<<(ANGLE90+SLANT_ANG_0[(int)(1.0*-prm_vx/prm_vy*10000)]));
                return ANGLE90 + SLANT_ANG_0[(int)(1.0*-prm_vx/prm_vy*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE180-SLANT_ANG_0["<<(int)(1.0*prm_vy/-prm_vx*10000)<<"]="<<(ANGLE180-SLANT_ANG_0[(int)(1.0*prm_vy/-prm_vx*10000)]));
                return ANGLE180 - SLANT_ANG_0[(int)(1.0*prm_vy/-prm_vx*10000)];
            }
        } else if (prm_vx <= 0 && prm_vy <= 0) { //第3象限
            if (-prm_vx >= -prm_vy) {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE180+SLANT_ANG_0["<<(int)(1.0*-prm_vy/-prm_vx*10000)<<"]="<<(ANGLE180+SLANT_ANG_0[(int)(1.0*-prm_vy/-prm_vx*10000)]));
                return ANGLE180 + SLANT_ANG_0[(int)(1.0*-prm_vy/-prm_vx*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE270-SLANT_ANG_0["<<(int)(1.0*-prm_vx/-prm_vy*10000)<<"]="<<(ANGLE270-SLANT_ANG_0[(int)(1.0*-prm_vx/-prm_vy*10000)]));
                return ANGLE270 - SLANT_ANG_0[(int)(1.0*-prm_vx/-prm_vy*10000)];
            }
        } else if (prm_vx >= 0 && prm_vy <= 0) { //第4象限
            if (prm_vx <= -prm_vy) {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE270+SLANT_ANG_0["<<(int)(1.0*prm_vx/-prm_vy*10000)<<"]="<<(ANGLE270+SLANT_ANG_0[(int)(1.0*prm_vx/-prm_vy*10000)]));
                return ANGLE270 + SLANT_ANG_0[(int)(1.0*prm_vx/-prm_vy*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE360-SLANT_ANG_0["<<(int)(1.0*-prm_vy/prm_vx*10000)<<"]="<<(ANGLE360-SLANT_ANG_0[(int)(1.0*-prm_vy/prm_vx*10000)]));
                return ANGLE360 - SLANT_ANG_0[(int)(1.0*-prm_vy/prm_vx*10000)];
            }
        }
        return 0;
    }

    /**
     * 近いほうのアングル値の差を取る
     * @param angFrom
     * @param angTo
     * @return アングル値の差（正負あり)
     */
    static angle getDifferenceAngle(angle angFrom, angle angTo) {
            if (0 <= angFrom && angFrom < ANGLE180) {
                if (0 <= angTo && angTo < angFrom) {
                    return -1 * (angFrom - angTo);
                } else if (angTo == angFrom) {
                    //重なってる場合
                    return 0;
                } else if (angFrom < angTo && angTo < angFrom + ANGLE180) {
                    return angTo - angFrom;
                } else if (angTo == angFrom + ANGLE180) {
                    //正反対を向いている（＝距離は等しい）
                    //仕方ないので正の値とする。(正確には -ANGLE180 or ANGLE180)
                    return ANGLE180;
                } else if (angFrom + ANGLE180 < angTo && angTo <= ANGLE360) {
                    return -1 * (angFrom + (ANGLE360 - angTo));
                } else {
                    //おかしい
                    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo);
                    throwGgafCriticalException("GgafDx9Util::getDifferenceAngle アングル値が範囲外です(1)。");
                }
            } else if (ANGLE180 <= angFrom && angFrom <= ANGLE360) {
                if (0 <= angTo && angTo < angFrom - ANGLE180) {
                    return ANGLE360 - angFrom + angTo;
                } else if (angTo == angFrom - ANGLE180) {
                    //正反対を向いている（＝距離は等しい）
                    //仕方ないので正の値とする。(正確には -ANGLE180 or ANGLE180)
                    return ANGLE180;
                } else if (angFrom - ANGLE180 < angTo && angTo < angFrom) {
                    return -1 * (angFrom - angTo);
                } else if (angFrom == angTo) {
                    //重なってる場合
                    return 0;
                } else if (angFrom < angTo && angTo <= ANGLE360) {
                    return angTo - angFrom;
                } else {
                    //おかしい
                    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo);
                    throwGgafCriticalException("GgafDx9Util::getDifferenceAngle アングル値が範囲外です(2)。");
                }
            }

        _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo);
        throwGgafCriticalException("GgafDx9Util::getDifferenceAngle  何故かしら角の距離が求めれません。(1)");
    }


    /**
     * XY座標系（Z軸無視）において、方向ベクトルの成す角をアングル値で取得 .
     * XY座標系（Z軸無視）において、原点(0,0)から(prm_vx,prm_vy)に線分を引いた時、
     * X軸との間に出来る角（３時の方向から反時計回りに）をアングル値で取得 .
     * @param prm_vx	X座標
     * @param prm_vy	Y座標
     * @return 成す角
     */
    //static angle getAngle2D(int prm_vx, int prm_vy);

    /**
     * XY座標系（Z軸無視）において、'N'way弾(N=整数)のアングル値を取得 .
     * @param prm_vx_Center [in] 'N'way弾の全体として向いている方向の、方向ベクトルX要素
     * @param prm_vy_Center [in] 'N'way弾の全体として向いている方向の、方向ベクトルY要素
     * @param prm_way	[in] 'N'way弾の N
     * @param prm_angClearance	[in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle	[out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_way,
                              angle prm_angClearance,
                              int* out_paAngle);

    /**
     * XY座標系（Z軸無視）において、'N'way弾(N=整数)のアングル値の配列を取得 .
     * @param prm_angCenter	[in]'N'way弾の全体として向いている方向のアングル値
     * @param prm_way	[in] 'N'way弾の N
     * @param prm_angClearance	[in] 'N'way弾の弾と弾との成す角をアングル値で指定
     * @param out_paAngle	[out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getWayAngle2D(angle prm_angCenter, int prm_way, angle prm_angClearance, angle* out_paAngle);


//    static void getMoveRzRyWayShot3D_XZ(int prm_way, angle prm_angClearance, int prm_tX, int prm_tY, int prm_tZ,
//                                        angle& out_angRotZ, angle* out_paAngRotY);


    /**
     * XY座標系（Z軸無視）において、円の放射状全方向の'N'way弾(N=整数)のアングル値を配列で取得 .
     * 弾と弾との成す角は 均等になる。例えば全方向4way弾の場合、弾と弾との成す角は直角である。
     * @param prm_angStart	放射状の全方向'N'way弾の１つ目の弾のアングル値
     * @param prm_way	[in] 'N'way弾の N。
     * @param out_paAngle	[out] 得られる'N'way弾 のアングル値配列のポインタ
     */
    static void getRadiationAngle2D(angle prm_angStart, int prm_way, angle* out_paAngle);

    /**
     *
     * @param prm_angNow
     * @param prm_angOffset
     * @return
     */
    static angle addAngle(angle prm_angNow, angle prm_angOffset);

    /**
     *
     * @param prm_X
     * @param prm_Y
     * @param prm_ang
     * @param out_X
     * @param out_Y
     */
    static void rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y);

    /**
     *
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return
     */
    static int getDistance(int x1, int y1, int x2, int y2);

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
     * @param out_angRotZ [out]Z軸回転アングル値
     * @param out_angRotY [out]Y軸回転アングル値
     */
    static void getRotAngleZY(int x,
                              int y,
                              int z,
                              float& out_nvx,
                              float& out_nvy,
                              float& out_nvz,
                              angle& out_angRotZ,
                              angle& out_angRotY);

    /**
     * 原点からパラメータ座標を向く方向ベクトルの、Z軸回転アングル値とY軸回転アングル値を取得 .
     * @param x [in]X座標
     * @param y [in]Y座標
     * @param z [in]Z座標
     * @param out_angRotZ [out]Z軸回転アングル値
     * @param out_angRotY [out]Y軸回転アングル値
     */
    static void getRotAngleZY(int x, int y, int z, angle& out_angRotZ, angle& out_angRotY);

    /**
     * 原点からパラメータの正規化された方向ベクトル(単位ベクトル)の、Z軸回転アングル値とY軸回転アングル値を取得 .
     * 方向ベクトルの正規化は行わないので高速です。<BR>
     * @param vx [in]単位ベクトルX要素
     * @param vy [in]単位ベクトルY要素
     * @param vz [in]単位ベクトルZ要素
     * @param out_angRotZ [out]Z軸回転アングル値
     * @param out_angRotY [out]Y軸回転アングル値
     */
    static void getRotAngleZY(float vx, float vy, float vz, angle& out_angRotZ, angle& out_angRotY);


    /**
     * Z軸回転+Y軸回転値から単位方向ベクトルを取得
     * @param prm_angRotZ [in]Z軸回転アングル値
     * @param prm_angRotY [in]Y軸回転アングル値
     * @param out_nvx [out]単位ベクトルX要素
     * @param out_nvy [out]単位ベクトルY要素
     * @param out_nvz [out]単位ベクトルZ要素
     */
    static void getNormalizeVectorZY(angle prm_angRotZ,
                                     angle prm_angRotY,
                                     float& out_nvx,
                                     float& out_nvy,
                                     float& out_nvz);

    static void getNormalizeVector(int x,
                                   int y,
                                   int z,
                                   float& out_nvx,
                                   float& out_nvy,
                                   float& out_nvz);
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
    static bool chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);

    /**
     * 符号判定.
     * @param x
     * @return
     */
    template<typename T>
    static T sign(T x) {
        if (x < 0) {
            return -1;
        } else if (x > 0) {
            return 1;
        } else {
            return 0;
        }
    }

    /**
     * @param x
     * @return
     */
    template<typename T>
    static T abs(T x) {
        if (x < 0) {
            return -1.0* x;
        } else if (x > 0) {
            return x;
        } else {
            return 0.0;
        }
    }

    /**
     * 平方根の近似を求める .
     * 標準sqrtよりも計算がはやいでしょう。
     * @param a 平方根を求めたい値
     * @param s 精度（計算ループ回数）
     * @return 引数aの平方根
     */
    static float sqrt_fast(float a, int s = 11) {
        float ret = 1;
        for (int i = 1; i <= s; i++) {
            ret = 0.5 * (ret + a / ret);
        }
        return ret;
    }
    //static DWORD max3(DWORD a, DWORD b, DWORD c);
};

}
#endif /*GGAFDX9UTIL_H_*/

