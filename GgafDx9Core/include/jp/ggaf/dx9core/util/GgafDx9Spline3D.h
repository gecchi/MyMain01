#ifndef GGAFDX9SPLINE3D_H_
#define GGAFDX9SPLINE3D_H_

#define MaxSplineSize 100

namespace GgafDx9Core {


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
            // �R����������0���W��(a)��ݒ�
            for (i = 0; i <= num; i++) {
                a[i] = sp[i];
            }
            // �R����������2���W��(c)���v�Z
            // �A���������������B
            // �A���A��ʉ�@�łȂ��X�v���C���v�Z�Ƀ`���[�j���O�������@
            c[0] = c[num] = 0.0;
            for (i = 1; i < num; i++) {
                c[i] = 3.0 * (a[i - 1] - 2.0 * a[i] + a[i + 1]);
            }
            // ����������
            w[0] = 0.0;
            for (i = 1; i < num; i++) {
                tmp = 4.0 - w[i - 1];
                c[i] = (c[i] - c[i - 1]) / tmp;
                w[i] = 1.0 / tmp;
            }
            // �E�������
            for (i = num - 1; i > 0; i--) {
                c[i] = c[i] - c[i + 1] * w[i];
            }

            // �R����������1���W��(b)��3���W��(b)���v�Z
            b[num] = d[num] = 0.0;
            for (i = 0; i < num; i++) {
                d[i] = (c[i + 1] - c[i]) / 3.0;
                b[i] = a[i + 1] - a[i] - c[i] - d[i];
            }
        }

        double compute(double t) {
            int j;
            double dt;
            j = (int)floor(t); // �����_�ȉ��؎̂�
            if (j < 0) j = 0;
            else if (j >= num) j = num - 1; // �ۂߌ덷���l��

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

