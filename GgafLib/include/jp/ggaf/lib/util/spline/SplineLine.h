#ifndef GGAFLIB_SPLINELINE_H_
#define GGAFLIB_SPLINELINE_H_
#include "jp/ggaf/core/GgafObject.h"

#include <math.h>
#define MaxSplineSize 1001

namespace GgafLib {

/**
 * ���B-�X�v���C���Ȑ��N���X .
 * <pre>
 * �{�N���X��Ishida So ���쐬�̃T���v�����Q�l�ɍ쐬���܂����B
 * �@�\�I�ȃT���v�����쐬���ꂽIshida So���Ɋ��ӂ������܂��B
 * �Q�l�T�C�g
 * �uSamayou Oharikui�v
 * http://www5d.biglobe.ne.jp/~stssk/
 * ���̃R���e���c
 * �u�ȗ��������R���X�v���C���Ȑ��̐������@�v
 * http://www5d.biglobe.ne.jp/~stssk/maze/spline.html
 * </pre>
 * @version 1.00
 * @since 2009/10/16
 * @author Masatoshi Tsuge
 */
class SplineLine : public GgafCore::GgafObject {

public:
    /**
     * �ȈՂR���X�v���C�� .
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


public:
    /**
     * �R���X�g���N�^ .
     * ��� init() ���Ăяo���ĉ������B
     */
    SplineLine();

    /**
     * �R���X�g���N�^ .
     * ��� init() ���Ăяo���Ȃ��ėǂ��B
     * @param prm_paaBase ����_���W�̔z��
     *                    [][0] X���W
     *                    [][1] Y���W
     *                    [][2] Z���W
     * @param num         ����_���W�̔z��
     * @param prm_accuracy �⊮�_�}�����x�B
     *                     1.0�ŕ⊮�_�Ȃ��B
     *                     0.5�Ő���_�Ԓ��_����ǉ��B
     *                     0.1����1����_�Ԃ�10�_�⊮�A�Ƃ������
     * @return
     */
    SplineLine(double prm_paaBase[][3], int num, double prm_accuracy);

    /**
     * ���������⊮�_���A�g�p�ł����Ԃɂ��܂� .
     * @param prm_paaBase ����_���W�̔z��
     *                    [][0] X���W
     *                    [][1] Y���W
     *                    [][2] Z���W
     * @param num         ����_���W�̔z��
     * @param prm_accuracy �⊮�_�}�����x�B
     *                     1.0�ŕ⊮�_�Ȃ��B
     *                     0.5�Ő���_�Ԓ��_��1�ǉ��B
     *                     0.1����1����_�Ԃ�9�̕⊮�_�A�Ƃ������
     */
    void init(double prm_paaBase[][3], int num, double prm_accuracy);

    /**
     * �⊮�_�v�Z
     * @param prm_accuracy �⊮�_�}�����x�B
     *                     1.0�ŕ⊮�_�Ȃ��B
     *                     0.5�Ő���_�Ԃɒ��_��1�ǉ��B
     *                     0.1���Ɛ���_�Ԃ�9�̕⊮�_�A�Ƃ������
     */
    void compute(double prm_accuracy);

    /** ����_X���W�̔z�� */
    double* _X_basepoint;
    /** ����_Y���W�̔z�� */
    double* _Y_basepoint;
    /** ����_Z���W�̔z�� */
    double* _Z_basepoint;
    /** ����_���W�� */
    int _num_basepoint;

    BSpline _xs;
    BSpline _ys;
    BSpline _zs;

    /** �⊮�_�i����_�܂ށjX���W�̔z�� */
    double* _X_compute;
    /** �⊮�_�i����_�܂ށjY���W�̔z�� */
    double* _Y_compute;
    /** �⊮�_�i����_�܂ށjZ���W�̔z�� */
    double* _Z_compute;
    /** �⊮�_���W�� */
    int _rnum;
    /** �⊮���x(1.0 �Ő���_���⊮�_�A0.5 �ŁA����_�Ԃɕ⊮�_���P�}���A0.1�ŕ⊮�_�X�� */
    double _accuracy;

    virtual ~SplineLine();

};

}
#endif /*GGAFLIB_SPLINELINE_H_*/

