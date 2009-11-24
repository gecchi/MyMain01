#ifndef GGAFDX9SPLINE3D_H_
#define GGAFDX9SPLINE3D_H_

#define MaxSplineSize 100

namespace GgafDx9Core {

//本クラスはIshida So 氏作成のサンプルを参考に作成しました。
//素晴らしいサンプルを作成されたIshida So氏に感謝いたします。
//参考サイト
//「Samayou Oharikui」
//http://www5d.biglobe.ne.jp/~stssk/
//内のコンテンツ
//「簡略化した３次スプライン曲線の生成方法」
//http://www5d.biglobe.ne.jp/~stssk/maze/spline.html
//
//                                2009/10/16 Masatoshi Tsuge

/**
 * スプライン曲線生成クラス .
 * @version 1.00
 * @since 2009/10/16
 * @author Masatoshi Tsuge
 */
class GgafDx9Spline3D {

public:

    class GgafDx9Spline {

    public:
        int num;
        double a[MaxSplineSize + 1], b[MaxSplineSize + 1], c[MaxSplineSize + 1], d[MaxSplineSize + 1];

        GgafDx9Spline() {
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

    GgafDx9Spline3D(double prm_paaBase[][3], int num, double prm_accuracy);

    void compute(double prm_accuracy);

    double* _X_establish;
    double* _Y_establish;
    double* _Z_establish;
    int _num_establish;

    GgafDx9Spline _xs;
    GgafDx9Spline _ys;
    GgafDx9Spline _zs;

    double* _X_compute;
    double* _Y_compute;
    double* _Z_compute;
    int _rnum;



    virtual ~GgafDx9Spline3D();

};

}
#endif /*GGAFDX9SPLINE3D_H_*/

