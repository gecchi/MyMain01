#ifndef GGAF_DX_CURVESOURCE_H_
#define GGAF_DX_CURVESOURCE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <math.h>
#include "jp/ggaf/core/exception/CriticalException.h"

#define MaxCurveSize 1001

namespace GgafDx {

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
 * http://www5d.biglobe.ne.jp/~stssk/maze/curve.html
 * </pre>
 * @version 1.00
 * @since 2009/10/16
 * @author Masatoshi Tsuge
 */
class CurveSource : public GgafCore::Object {

public:
    /**
     * �ȈՂR���X�v���C�� .
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
                throwCriticalException("CurveSource::BCurve::init() MaxCurveSize�𒴂��Ă��܂��Bspnum="<<spnum);
            }
            double tmp, w[MaxCurveSize + 1];
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

    /** ����_X���W�̔z�� */
    double* _x_basepoint;
    /** ����_Y���W�̔z�� */
    double* _y_basepoint;
    /** ����_Z���W�̔z�� */
    double* _z_basepoint;
    /** ����_���W�� */
    int _num_basepoint;
    /** �⊮�_�i����_�܂ށjX���W�̔z�� */
    double* _x_compute;
    /** �⊮�_�i����_�܂ށjY���W�̔z�� */
    double* _y_compute;
    /** �⊮�_�i����_�܂ށjZ���W�̔z�� */
    double* _z_compute;
    /** �⊮�_���W�� */
    int _rnum;
    /** �⊮���x(1.0 �Ő���_���⊮�_�A0.5 �ŁA����_�Ԃɕ⊮�_���P�}���A0.1�ŕ⊮�_�X�� */
    double _accuracy;
    /** ���W�␳�ϊ��s�� */
    RotMat _rotmat;

    char* _coord_spl_file;
public:
    /**
     * �R���X�g���N�^ .
     * ��� init() ���Ăяo���ĉ������B
     */
    CurveSource();

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
     */
    CurveSource(double prm_paaBase[][3], int num, double prm_accuracy);

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
     * @param prm_rotmat ����_�i��ԓ_�j�̍��W��␳����ϊ��s��
     */
    CurveSource(double prm_paaBase[][3], int num, double prm_accuracy, RotMat& prm_rotmat);

    /**
     * ��`�t�@�C������I�u�W�F�N�g�\�z
     * @param prm_coord_spl_file
     */
    CurveSource(const char* prm_coord_spl_file);

    /**
     * ���������⊮�_���␳�ϊ��s���K�p���āA�g�p�ł����Ԃɂ��܂� .
     * CurveSource() �̈����Ȃ��R���X�g���N�^�łŐ��������ꍇ�ɁA�{���\�b�h��ʓr�Ăяo���K�v������܂��B
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

