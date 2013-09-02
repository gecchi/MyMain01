#ifndef GGAFLIB_SPLINELINE_H_
#define GGAFLIB_SPLINELINE_H_
#include "jp/ggaf/core/GgafObject.h"

#include <math.h>
#define MaxSplineSize 1001

namespace GgafLib {

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
 * http://www5d.biglobe.ne.jp/~stssk/maze/spline.html
 * </pre>
 * @version 1.00
 * @since 2009/10/16
 * @author Masatoshi Tsuge
 */
class SplineLine : public GgafCore::GgafObject {

public:
    /**
     * 簡易３次スプライン .
     */
    class BSpline {
    public:
        int num;
        double a[MaxSplineSize + 1], b[MaxSplineSize + 1], c[MaxSplineSize + 1], d[MaxSplineSize + 1];
    public:
        BSpline() {
            num = 0;
        }
        void init(double *sp, int spnum) {
            double tmp, w[MaxSplineSize + 1];
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


public:
    /**
     * コンストラクタ .
     * 後で init() を呼び出して下さい。
     */
    SplineLine();

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
     * @return
     */
    SplineLine(double prm_paaBase[][3], int num, double prm_accuracy);

    /**
     * 初期化し補完点し、使用できる状態にします .
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
     * @param prm_accuracy 補完点挿入粒度。
     *                     1.0で補完点なし。
     *                     0.5で制御点間に中点を1つ追加。
     *                     0.1だと制御点間に9個の補完点、といった具合
     */
    void compute(double prm_accuracy);

    /** 制御点X座標の配列 */
    double* _X_basepoint;
    /** 制御点Y座標の配列 */
    double* _Y_basepoint;
    /** 制御点Z座標の配列 */
    double* _Z_basepoint;
    /** 制御点座標数 */
    int _num_basepoint;

    BSpline _xs;
    BSpline _ys;
    BSpline _zs;

    /** 補完点（制御点含む）X座標の配列 */
    double* _X_compute;
    /** 補完点（制御点含む）Y座標の配列 */
    double* _Y_compute;
    /** 補完点（制御点含む）Z座標の配列 */
    double* _Z_compute;
    /** 補完点座標数 */
    int _rnum;
    /** 補完粒度(1.0 で制御点＝補完点、0.5 で、制御点間に補完点を１つ挿入、0.1で補完点９個 */
    double _accuracy;

    virtual ~SplineLine();

};

}
#endif /*GGAFLIB_SPLINELINE_H_*/

