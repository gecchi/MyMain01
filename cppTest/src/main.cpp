#include "GgafCommonHeader.h"
#define DEBUG
#define MaxSplineSize 100
//http://www5d.biglobe.ne.jp/~stssk/maze/spline.html
//gnuplotメモ
//splot "xyz.txt" using 1:2:3 with point
// splot "xyz.txt" using 1:2:3 with point ps 1 pt 4
//set size 0.73, 1  !XY座標を正方形
//set grid xtics ytics ztics
//splot "xyz.txt" using 1:2:3 with point ps 1 pt 4, "xyz.txt" using 1:2:3 with line




class Spline {
    int num;
    double a[MaxSplineSize+1], b[MaxSplineSize+1], c[MaxSplineSize+1], d[MaxSplineSize+1];
public:
    Spline() { num=0; }
    void init(double *sp, int num);
    double culc(double t);
};

// Ｂスプライン描画
// x[num], y[num], z[num] は座標の配列
void drowSpline(double *x, double *y, double *z, int num)
{
    Spline xs, ys, zs;
    double t, m;
    xs.init(x, num);
    ys.init(y, num);
    zs.init(z, num);
    m = (double)(num-1);

    //_TRACE_(x[0]<<","<<y[0]<<","<<z[0]);
    for(t=0.0; t<=m; t += 0.1) {
        printf("%10f %10f %10f\n",xs.culc(t),ys.culc(t),zs.culc(t));
        //_TRACE_(""<<xs.culc(t)<<" "<<ys.culc(t)<<" "<<zs.culc(t));
    }
}

//スプラインデータ初期化
void Spline::init(double *sp, int spnum)
{
    double tmp, w[MaxSplineSize+1];
    int i;

    num = spnum-1;

    // ３次多項式の0次係数(a)を設定
    for(i=0; i<=num; i++) {
        a[i] = sp[i];
    }

    // ３次多項式の2次係数(c)を計算
    // 連立方程式を解く。
    // 但し、一般解法でなくスプライン計算にチューニングした方法
    c[0] = c[num] = 0.0;
    for(i=1; i<num; i++) {
        c[i] = 3.0 * (a[i-1] - 2.0 * a[i] + a[i+1]);
    }
    // 左下を消す
    w[0]=0.0;
    for(i=1; i<num; i++) {
        tmp = 4.0 - w[i-1];
        c[i] = (c[i] - c[i-1])/tmp;
        w[i] = 1.0 / tmp;
    }
    // 右上を消す
    for(i=num-1; i>0; i--) {
        c[i] = c[i] - c[i+1] * w[i];
    }

    // ３次多項式の1次係数(b)と3次係数(b)を計算
    b[num] = d[num] =0.0;
    for(i=0; i<num; i++) {
        d[i] = ( c[i+1] - c[i]) / 3.0;
        b[i] = a[i+1] - a[i] - c[i] - d[i];
    }
}

//媒介変数(0～num-1の実数）に対する値を計算
double Spline::culc(double t)
{
    int j;
    double dt;
    j = (int)floor(t); // 小数点以下切捨て
    if(j < 0) j=0; else if (j >= num) j=num-1; // 丸め誤差を考慮

    dt = t - (double)j;
    return a[j] + ( b[j] + (c[j] + d[j] * dt) * dt ) * dt;
}


int main() {
    double x[5] = { 1, 0, -1 ,0  , 1};
    double y[5] = { 0, 1, 0  ,-1,  0};
    double z[5] = { 0, 1, 0  ,10,   0};
    drowSpline(x, y, z, 5);



}
