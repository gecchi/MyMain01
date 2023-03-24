#ifndef GGAF_DX_CURVESOURCE_H_
#define GGAF_DX_CURVESOURCE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <math.h>
#include "jp/ggaf/core/exception/CriticalException.h"

#define MaxCurveSize 1001

namespace GgafDx {

/**
 * 空間B-スプライン曲線クラス .
 * <pre>
 * 本クラスはIshida So 氏作成のサンプルを参考に作成しました。
 * 機能的なサンプルを作成されたIshida So氏に感謝いたします。
 * 参考サイト
 * 「Samayou Oharikui」
 * http://www5d.biglobe.ne.jp/~stssk/
 * 内のコンテンツ
 * 「簡略化した３次スプライン曲線の生成方法」
 * http://www5d.biglobe.ne.jp/~stssk/maze/curve.html
 * </pre>
 * @version 1.00
 * @since 2009/10/16
 * @author Masatoshi Tsuge
 */
class CurveSource : public GgafCore::Object {

public:
    /**
     * 簡易３次スプライン .
     */
    class BCurve {
    public:
        int num;
        double a[MaxCurveSize + 1], b[MaxCurveSize + 1], c[MaxCurveSize + 1], d[MaxCurveSize + 1];
    public:
        BCurve() {
            num = 0;
        }
        void init(double *sp, int spnum) {
            if (spnum >= MaxCurveSize) {
                throwCriticalException("CurveSource::BCurve::init() MaxCurveSizeを超えています。spnum="<<spnum);
            }
            double tmp, w[MaxCurveSize + 1];
            int i;
            num = spnum - 1;
            // ３次多項式の0次係数(a)を設定
            for (i = 0; i <= num; i++) {
                a[i] = sp[i];
            }
            // ３次多項式の2次係数(c)を計算
            // 連立方程式を解く。
            // 但し、一般解法でなくスプライン計算にチューニングした方法
            c[0] = c[num] = 0.0;
            for (i = 1; i < num; i++) {
                c[i] = 3.0 * (a[i - 1] - 2.0 * a[i] + a[i + 1]);
            }
            // 左下を消す
            w[0] = 0.0;
            for (i = 1; i < num; i++) {
                tmp = 4.0 - w[i - 1];
                c[i] = (c[i] - c[i - 1]) / tmp;
                w[i] = 1.0 / tmp;
            }
            // 右上を消す
            for (i = num - 1; i > 0; i--) {
                c[i] = c[i] - c[i + 1] * w[i];
            }
            // ３次多項式の1次係数(b)と3次係数(b)を計算
            b[num] = d[num] = 0.0;
            for (i = 0; i < num; i++) {
                d[i] = (c[i + 1] - c[i]) / 3.0;
                b[i] = a[i + 1] - a[i] - c[i] - d[i];
            }
        }
        double compute(double t) {
            int j;
            double dt;
            j = (int)floor(t); // 小数点以下切捨て
            if (j < 0) j = 0;
            else if (j >= num) j = num - 1; // 丸め誤差を考慮

            dt = t - (double)j;
            return a[j] + (b[j] + (c[j] + d[j] * dt) * dt) * dt;
        }
    };

    struct RotMat {
        double _11, _12, _13, _14;
        double _21, _22, _23, _24;
        double _31, _32, _33, _34;
        double _41, _42, _43, _44;
        RotMat() {
            _11 = 1.0; _12 = 0.0; _13 = 0.0; _14 = 0.0;
            _21 = 0.0; _22 = 1.0; _23 = 0.0; _24 = 0.0;
            _31 = 0.0; _32 = 0.0; _33 = 1.0; _34 = 0.0;
            _41 = 0.0; _42 = 0.0; _43 = 0.0; _44 = 1.0;
        }
        void set(double d11, double d12, double d13, double d14,
                 double d21, double d22, double d23, double d24,
                 double d31, double d32, double d33, double d34,
                 double d41, double d42, double d43, double d44 ) {
            _11 = d11; _12 = d12; _13 = d13; _14 = d14;
            _21 = d21; _22 = d22; _23 = d23; _24 = d24;
            _31 = d31; _32 = d32; _33 = d33; _34 = d34;
            _41 = d41; _42 = d42; _43 = d43; _44 = d44;
        }
    };

public:

    BCurve _xs;
    BCurve _ys;
    BCurve _zs;

    /** 制御点X座標の配列 */
    double* _x_basepoint;
    /** 制御点Y座標の配列 */
    double* _y_basepoint;
    /** 制御点Z座標の配列 */
    double* _z_basepoint;
    /** 制御点座標数 */
    int _num_basepoint;
    /** 補完点（制御点含む）X座標の配列 */
    double* _x_compute;
    /** 補完点（制御点含む）Y座標の配列 */
    double* _y_compute;
    /** 補完点（制御点含む）Z座標の配列 */
    double* _z_compute;
    /** 補完点座標数 */
    int _rnum;
    /** 補完粒度(1.0 で制御点＝補完点、0.5 で、制御点間に補完点を１つ挿入、0.1で補完点９個 */
    double _accuracy;
    /** 座標補正変換行列 */
    RotMat _rotmat;

    char* _coord_spl_file;
public:
    /**
     * コンストラクタ .
     * 後で init() を呼び出して下さい。
     */
    CurveSource();

    /**
     * コンストラクタ .
     * 後で init() を呼び出さなくて良い。
     * @param prm_paaBase 制御点座標の配列
     *                    [][0] X座標
     *                    [][1] Y座標
     *                    [][2] Z座標
     * @param num         制御点座標の配列数
     * @param prm_accuracy 補完点挿入粒度。
     *                     1.0で補完点なし。
     *                     0.5で制御点間中点を一つ追加。
     *                     0.1だと1制御点間に10点補完、といった具合
     */
    CurveSource(double prm_paaBase[][3], int num, double prm_accuracy);

    /**
     * コンストラクタ .
     * 後で init() を呼び出さなくて良い。
     * @param prm_paaBase 制御点座標の配列
     *                    [][0] X座標
     *                    [][1] Y座標
     *                    [][2] Z座標
     * @param num         制御点座標の配列数
     * @param prm_accuracy 補完点挿入粒度。
     *                     1.0で補完点なし。
     *                     0.5で制御点間中点を一つ追加。
     *                     0.1だと1制御点間に10点補完、といった具合
     * @param prm_rotmat 制御点（補間点）の座標を補正する変換行列
     */
    CurveSource(double prm_paaBase[][3], int num, double prm_accuracy, RotMat& prm_rotmat);

    /**
     * 定義ファイルからオブジェクト構築
     * @param prm_coord_spl_file
     */
    CurveSource(const char* prm_coord_spl_file);

    /**
     * 初期化し補完点し補正変換行列を適用して、使用できる状態にします .
     * CurveSource() の引数なしコンストラクタでで生成した場合に、本メソッドを別途呼び出す必要があります。
     * @param prm_paaBase 制御点座標の配列
     *                    [][0] X座標
     *                    [][1] Y座標
     *                    [][2] Z座標
     * @param num         制御点座標の配列数
     * @param prm_accuracy 補完点挿入粒度。
     *                     1.0で補完点なし。
     *                     0.5で制御点間中点を1つ追加。
     *                     0.1だと1制御点間に9個の補完点、といった具合
     */
    void init(double prm_paaBase[][3], int num, double prm_accuracy);

    /**
     * 補完点計算
     */
    void compute();

    /**
     *
     */
    void rotation(angle prm_rx, angle prm_ry, angle prm_rz);

    virtual ~CurveSource();

};

}
#endif /*GGAF_DX_CURVESOURCE_H_*/

