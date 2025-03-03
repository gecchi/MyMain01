#ifndef GGAF_DX_UTIL_H_
#define GGAF_DX_UTIL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/Util.h"

#include <math.h>
#include "jp/ggaf/dx/util/SphereRadiusVectors.h"
#include "jp/ggaf/dx/util/GeoElem.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/camera/Camera.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafDx::Util

////�C�x���g�p
DECLARE_EVENT_VAL(GGAF_EVENT_ON_DEVICE_LOST);
DECLARE_EVENT_VAL(GGAF_EVENT_ON_DEVICE_LOST_RESTORE);


#define PROJANG_ZY_ZX_TO_ROTANG_x_REV PROJANG_XY_XZ_TO_ROTANG_z
namespace GgafDx {

/**
 * ���[�e�B���e�B�N���X .
 * �ÓI�ȍ��W�v�Z�֘A�֐��̓R�R�ɏW�񂵂Ă������B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Util : public GgafCore::Util {

//    struct AngleSet {
//        angle rz[D360SANG+1];
//        angle ry[D360SANG+1];
//    };

public:

    //static float PARABORA[];
    /**
     * cos�e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ 36000
     * angle�l r �� cos�́ACOS[r/10]
     */
    static double COS[];
    /**
     * sin�e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ 36000
     * angle�l r �� sin �́ASIN[r/10]
     */
    static double SIN[];

    /**
     * �ʓx�@�ϊ��e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ 36000
     * angle�l r �̃��f�B�A���́ARAD[r/10]
     */
    static double RAD[];
    /**
     * [�X��] �� angle�l�ϊ��e�[�u��
     * �v�f�ԍ��͈́F���� y = ax �X�� a �� 100000 �{�̐������x���v�f�ԍ��ƂȂ�B
     * ���� y = ax �̐����p�̃A���O���l�� SLANT2ANG[(int)a*100000] �ƂȂ�B
     */
    static angle SLANT2ANG[];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����1-1) .
     * �����x�N�g�����A[XY���ʂ֎ˉe�������̂Ȃ��p][XZ���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����Z����]�p �̕ϊ��e�[�u��
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_z[D90SANG*SR_AC+1][D90SANG*SR_AC+1];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����1-2) .
     * �����x�N�g�����A[XY���ʂ֎ˉe�������̂Ȃ��p][XZ���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����Y��(�t)��]�p �̕ϊ��e�[�u��
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_y_REV[D90SANG*SR_AC+1][D90SANG*SR_AC+1];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����2-1) .
     * �����x�N�g�����A[ZY���ʂ֎ˉe�������̂Ȃ��p][ZX���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����X��(�t)��]�p �̕ϊ��e�[�u��
     */
//    static angle PROJANG_ZY_ZX_TO_ROTANG_x_REV[D90SANG*SR_AC+1][D90SANG*SR_AC+1];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����2-2) .
     * �����x�N�g�����A[ZY���ʂ֎ˉe�������̂Ȃ��p][ZX���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����Y����]�p �̕ϊ��e�[�u��
     */
    static angle PROJANG_ZY_ZX_TO_ROTANG_y[D90SANG*SR_AC+1][D90SANG*SR_AC+1];

    static double RND_CIRCLE_X[];
    static double RND_CIRCLE_Y[];
    static double RND_SPHERE_X[];
    static double RND_SPHERE_Y[];
    static double RND_SPHERE_Z[];

    static SphereRadiusVectors _srv;

    static bool _was_GgafDx_Util_inited_flg;



    static Camera* _pCam;
public:
    static void init();


    static double getRad2D(double vx1, double vy1, double vx2, double vy2) {

        // a�Eb = |a||b|cos�� ���
        //cos�� = ���� / �����̐�
        double cos_t = ((vx1*vx2)+(vy1*vy2)) / (sqrt((vx1*vx1)+(vy1*vy1)) *  sqrt((vx2*vx2)+(vy2*vy2)) );
        return acos(cos_t);
    }

    /**
     * ���ی��̕��ʏ�̃x�N�g��(vx, vy) ����錴�_�̂Ȃ��p��Ԃ� .
     * ���̊֐����g�p����O��́A vx > 0, vy > 0 ���\�ߖ��炩�ł��邱�ƁB
     * @param prm_vx �x�N�g�� x �v�f (> 0)
     * @param prm_vy �x�N�g�� y �v�f (> 0)
     * @return �Ȃ��p�̃A���O���l (0 �` D90ANG)
     */
    static angle getAngle2D_first_quadrant(int prm_vx, int prm_vy) {
        if (prm_vx >= prm_vy) {
            return D0ANG  + SLANT2ANG[(int)(((double)prm_vy)/prm_vx*100000.0)];
        } else {
            return D90ANG - SLANT2ANG[(int)(((double)prm_vx)/prm_vy*100000.0)];
        }
    }
    /**
     * ���ʏ�̃x�N�g��(vx, vy) ����錴�_�̂Ȃ��p��Ԃ� .
     * @param prm_vx �x�N�g�� x �v�f
     * @param prm_vy �x�N�g�� y �v�f
     * @return �Ȃ��p�̃A���O���l (0 �` 360000)
     */
    static angle getAngle2D(int prm_vx, int prm_vy) {

        if (prm_vx == 0) {
            if (prm_vy > 0) {
                return D90ANG;
            } else if (prm_vy < 0) {
                return D270ANG;
            } else {
                //���_�ł���A�s��B
                _TRACE_("�y�x���z Util::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") �͌��_�ł���A�Ȃ��p�͕s��A0��Ԃ��܂��B(1)");
                return 0;
            }
        } else if (prm_vy == 0) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return D180ANG;
            } else {
                _TRACE_("�y�x���z Util::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") �͌��_�ł���A�Ȃ��p�͕s��A0��Ԃ��܂��B(2)");
                return 0;
            }
        }

        if (prm_vx >= 0 && prm_vy >= 0) { //��1�ی�
            if (prm_vx >= prm_vy) {
                return D0ANG  + SLANT2ANG[(int)(((double)prm_vy)/prm_vx*100000.0)];
            } else {
                return D90ANG - SLANT2ANG[(int)(((double)prm_vx)/prm_vy*100000.0)];
            }
        } else if (prm_vx <= 0 && prm_vy >= 0) { //��2�ی�
            if (-prm_vx <= prm_vy) {
                return D90ANG + SLANT2ANG[(int)(((double)-prm_vx)/prm_vy*100000.0)];
            } else {
                return D180ANG - SLANT2ANG[(int)(((double)prm_vy)/-prm_vx*100000.0)];
            }
        } else if (prm_vx <= 0 && prm_vy <= 0) { //��3�ی�
            if (-prm_vx >= -prm_vy) {
                return D180ANG + SLANT2ANG[(int)(((double)-prm_vy)/-prm_vx*100000.0)];
            } else {
                return D270ANG - SLANT2ANG[(int)(((double)-prm_vx)/-prm_vy*100000.0)];
            }
        } else if (prm_vx >= 0 && prm_vy <= 0) { //��4�ی�
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
                //���_�ł���A�s��B
                _TRACE_("�y�x���z Util::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") �͌��_�ł���A�Ȃ��p�͕s��A0��Ԃ��܂��B(3)");
                return 0;
            }
        }
        if (ZEROd_EQ(prm_vy)) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return D180ANG;
            } else {
                _TRACE_("�y�x���z Util::getAngle2D() ("<<prm_vx<<","<<prm_vy<<") �͌��_�ł���A�Ȃ��p�͕s��A0��Ԃ��܂��B(4)");
                //���_�ł���A�s��B
                return 0;
            }
        }

        if (prm_vx >= 0.0 && prm_vy >= 0.0) { //��1�ی�
            if (prm_vx >= prm_vy) {
                return D0ANG  + SLANT2ANG[(int)(prm_vy/prm_vx*100000.0)];
            } else {
                return D90ANG - SLANT2ANG[(int)(prm_vx/prm_vy*100000.0)];
            }
        } else if (prm_vx <= 0.0 && prm_vy >= 0.0) { //��2�ی�
            if (-prm_vx <= prm_vy) {
                return D90ANG  + SLANT2ANG[(int)(-prm_vx/prm_vy*100000.0)];
            } else {
                return D180ANG - SLANT2ANG[(int)(prm_vy/-prm_vx*100000.0)];
            }
        } else if (prm_vx <= 0.0 && prm_vy <= 0.0) { //��3�ی�
            if (-prm_vx >= -prm_vy) {
                return D180ANG + SLANT2ANG[(int)(-prm_vy/-prm_vx*100000.0)];
            } else {
                return D270ANG - SLANT2ANG[(int)(-prm_vx/-prm_vy*100000.0)];
            }
        } else if (prm_vx >= 0.0 && prm_vy <= 0.0) { //��4�ی�
            if (prm_vx <= -prm_vy) {
                return D270ANG + SLANT2ANG[(int)(prm_vx/-prm_vy*100000.0)];
            } else {
                return D360ANG - SLANT2ANG[(int)(-prm_vy/prm_vx*100000.0)];
            }
        }
        return 0;
    }

    /**
     * �A���O���l�̍������ .
     * TURN_CLOSE_TO         �E�E�E �^�[�Q�b�g�̉�]�p�Ƌ������߂����̉�]�����Ŏ擾�A�����Ő��A���́A�E���̕��̒l�ɂȂ�B<BR>
     * TURN_ANTICLOSE_TO     �E�E�E �^�[�Q�b�g�̉�]�p�Ƌ����������̕��̉�]�����Ŏ擾�A�����Ő��A���́A�E���̕��̒l�ɂȂ�B<BR>
     * TURN_COUNTERCLOCKWISE �E�E�E ��]�����������ō��يp�擾�A���̒l�ŕԂ�B<BR>
     * TURN_CLOCKWISE        �E�E�E ��]�������E���ō��يp�擾�A���̒l�ŕԂ�B<BR>
     * @param prm_from ��̃A���O���l
     * @param prm_to �������Ώۂ̃A���O���l
     * @param prm_way TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE
     * @return prm_from �` prm_to �̃A���O���l�̍��i���ʂ� �����v����͐��A���v���͕����Ӗ�����)
     */
    static angle getAngDiff(angle prm_from, angle prm_to, int prm_way=TURN_CLOSE_TO);

    /**
     * ���ʏ�ɂ����āA'N'way�e(N=����)�̎ˏo�A���O���l���Z�b�g(�z��)�Ŏ擾 .
     * @param prm_vx_Center     [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��X�v�f
     * @param prm_vy_Center     [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��Y�v�f
     * @param prm_ways          [in] 'N'way�e�� N
     * @param prm_clearance  [in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle       [out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngleArr(int prm_vx_Center, int prm_vy_Center, int prm_ways,  angle prm_clearance,  angle* out_paAngle);

    /**
     * ���ʏ�ɂ����āA'N'way�e(N=����)�̎ˏo�A���O���l���Z�b�g(�z��)�Ŏ擾 .
     * @param prm_center     [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������̃A���O���l
     * @param prm_ways       [in] 'N'way�e�� N
     * @param prm_clearance  [in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle    [out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngleArr(angle prm_center, int prm_ways, angle prm_clearance, angle* out_paAngle);

    /**
     * ���ʏ�ɂ����āA'N'way�e(N=����)�̎ˏo�A���O���l���Z�b�g(�z��)�Ŏ擾 .
     * @param prm_start [in] 'N'way�e�̈�Ԓ[�i�J�n�j�̕����̃A���O���l
     * @param prm_end   [in] 'N'way�e�̂�������̈�Ԓ[�i�I���j�̕����̃A���O���l
     * @param prm_ways [in] 'N'way�e�� N
     * @param prm_way TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE
     * @param out_paAngle [out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngleArr(angle prm_start, angle prm_end, int prm_ways, angle* out_paAngle, int prm_way);

    /**
     * ���ʏ�ɂ����āA���ˏ�S������'N'way�e(N=����)�̃A���O���l��z��Ŏ擾 .
     * �e�ƒe�Ƃ̐����p�� �ϓ��ɂȂ邱�ƂƂ���B
     * �Ⴆ�ΑS����4way�e�̏ꍇ�A�e�ƒe�Ƃ̐����p�͒��p(90000)�ɂȂ�B
     * @param prm_start  ���ˏ�̑S����'N'way�e�̂P�ڂ̒e�̃A���O���l
     * @param prm_ways  [in] 'N'way�e�� N�B
     * @param out_paAngle   [out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getRadialAngleArr(angle prm_start, int prm_ways, angle* out_paAngle);

    static void convRzRyToRyRz(angle prm_rz, angle prm_ry, angle& out_ry, angle& out_rz);

//    static void getWayAngle_LinedRzLongitude(angle prm_ang_center_rz, angle prm_ang_center_ry,
//                                           int prm_ways, angle prm_clearance,
//                                           angle* out_paAngleRz, angle* out_paAngleRy);

//    static void getMoveRzRyWayShot3D_XZ(int prm_ways, angle prm_clearance, coord prm_tx, coord prm_ty, coord prm_tz,
//                                        angle& out_faceZ, angle* out_paAngRotY);


    /**
     * �A���O���l�̉��Z .
     * D360ANG �𒴂����ꍇ�A������ 0 ����������ꍇ�ł��A
     * 0�`D360ANG �ɕW���������B
     * @param prm_angNow �A���O���l
     * @param prm_ang_offset ������A���O���l�i�����Ő��A�E���̕��̒l�j
     * @return �W�������ꂽ �A���O���l + ������A���O���l �̃A���O���l
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
     * �����v�Z(2D) .
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return
     */
    static int getDistance(coord x1, coord y1, coord x2, coord y2);

    /**
     * �����v�Z(3D) .
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

    template<typename T>
    static T getDistanceFromOrigin(T x, T y, T z) {
        return (T)( sqrt(
                      (
                        ((double)(x)) * ((double)(x))
                      ) + (
                        ((double)(y)) * ((double)(y))
                      ) + (
                        ((double)(z)) * ((double)(z))
                      )
                    )
                 );
    }

    static double getDistance(const GeometricActor* pA1, const GeometricActor* pA2) {
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

    static double getDistance(const GeometricActor* pA1, const GeoElem* pA2) {
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

    static double getDistance(const GeoElem* pA1, const GeometricActor* pA2) {
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

    static double getDistance(const GeoElem* pA1 , const GeoElem* pA2) {
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
     * ���_����̋���(2D)�̋ߎ����v�Z .
     * sqrt() ���g�p������������B
     * @param x X���W
     * @param y Y���W
     * @return
     */
    static int getApproxDistanceFromOrigin(int x, int y) {
        x = abs(x);
        y = abs(y);
        int64_t max = x > y ? x : y;
        int64_t min = x > y ? y : x;
        int64_t d = 2*max < 5*min  ?  864 *max + 569*min :
                                      1016*max + 190*min;
        return (int)((d + 512) >> 10);
    }

    /**
     * ���_����̋���(2D)�̋ߎ����v�Z .
     * sqrt() ���g�p������������B
     * ���������ׂĐ��Ɨ\�߂킩���Ă���ꍇ�̂��傢�����o�[�W����
     * @param abs_x ����X���W
     * @param abs_y ����Y���W
     * @return ���_����̋����̋ߎ�
     */
    static int getApproxDistanceFromOrigin2(int abs_x, int abs_y) {
        int64_t max = abs_x > abs_y ? abs_x : abs_y;
        int64_t min = abs_x > abs_y ? abs_y : abs_x;
        int64_t d = 2*max < 5*min  ?  864 *max + 569*min :
                                      1016*max + 190*min;
        return (int)((d + 512) >> 10);
    }

    /**
     * �����ߎ��l�v�Z(2D) .
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return �����̋ߎ�
     */
    static coord getApproxDistance(coord x1, coord y1, coord x2, coord y2) {
        return Util::getApproxDistanceFromOrigin(x2-x1, y2-y1);
    }

// �����R�o�[�W�����͑��x�I��sqrt() �Ɠ����B
// ���������Đ��x���ǂ� sqrt() ���g���ׂ��l���āA�ȈՔł���������폜

//    /**
//     * �����̋ߎ����v�Z(3D) .
//     * @param x
//     * @param y
//     * @param z
//     * @return ���_����̋����̋ߎ�
//     */
//    static int getApproxDistanceFromOrigin(int x, int y, int z) {
//        return Util::getApproxDistanceFromOrigin(getApproxDistanceFromOrigin(x, y), z);
//    }
//
//    /**
//     * �����̋ߎ����v�Z(3D) �i�� ���������ׂĐ��Ɨ\�߂킩���Ă���ꍇ�̂��傢�����o�[�W�����j .
//     * @param abs_x
//     * @param abs_y
//     * @param abs_z
//     * @return ���_����̋����̋ߎ�
//     */
//    static int getApproxDistanceFromOrigin2(int abs_x, int abs_y, int abs_z) {
//        return Util::getApproxDistanceFromOrigin2(getApproxDistanceFromOrigin2(abs_x, abs_y), abs_z);
//    }

//
//    /**
//     * �����̋ߎ����v�Z(3D) .
//     * @param x1
//     * @param y1
//     * @param z1
//     * @param x2
//     * @param y2
//     * @param z2
//     * @return �����̋ߎ�
//     */
//    static coord getApproxDistance(coord x1, coord y1, coord z1, coord x2, coord y2, coord z2) {
//        return Util::getApproxDistanceFromOrigin(x2-x1, y2-y1, z2-z1);
//    }
//
//    static double getApproxDistance(GeometricActor* pA1, GeometricActor* pA2) {
//        return Util::getApproxDistanceFromOrigin(pA2->_x - pA1->_x, pA2->_y - pA1->_y, pA2->_z - pA1->_z);
//    }
//
//    static double getApproxDistance(GeometricActor* pA1, GeoElem* pA2) {
//        return Util::getApproxDistanceFromOrigin(pA2->x - pA1->_x, pA2->y - pA1->_y, pA2->z - pA1->_z);
//    }
//
//    static double getApproxDistance(GeoElem* pA1, GeometricActor* pA2) {
//        return Util::getApproxDistanceFromOrigin(pA2->_x - pA1->x, pA2->_y - pA1->y, pA2->_z - pA1->z);
//    }
//
//    static double getApproxDistance(GeoElem* pA1 ,GeoElem* pA2) {
//        return Util::getApproxDistanceFromOrigin(pA2->x - pA1->x, pA2->y - pA1->y, pA2->z - pA1->z);
//    }

    static void calcVecToAng(double prm_x,
                             double prm_y,
                             double prm_z,
                             s_ang& out_faceZ,
                             s_ang& out_faceY_rev);
    /**
     * ���_(0,0,0) ����p�����[�^���W(vx,vy,vz) �����������x�N�g���ɑΉ�����uZ����]�̃A���O���l�v�ƁuY����]�̃A���O���l�v���擾 .
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h���̂P<BR>
     * �����x�N�g�� -> Z��Y����]���p �̕ϊ�<BR>
     * @param vx [in]X���W
     * @param vy [in]Y���W
     * @param vz [in]Z���W
     * @param out_rz [out]Z����]�A���O���l
     * @param out_ry [out]Y����]�A���O���l
     */
    static void convVectorToRzRy(coord vx, coord vy, coord vz, angle& out_rz, angle& out_ry);
//    static void convVectorToRzRy2(coord vx, coord vy, coord vz, angle& out_rz, angle& out_ry);
    /**
     * ���_(0,0,0) ����p�����[�^���W�����������x�N�g��(�P�ʃx�N�g��)�ɑΉ�����uZ����]�̃A���O���l�v�ƁuY����]�̃A���O���l�v���擾 .
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h���̂P<BR>
     * �����x�N�g�� -> Z��Y����]���p �̕ϊ��B<BR>
     * �v�Z�����Ƀe�[�u���Q�Ƃō����ɍs���B<BR>
     * �������ŁA�����x�N�g���̐��K�����s��Ȃ��̂� <BR>
     * convVectorToRzRy(int, int, int , angle&, angle&);
     * ����⍂���B�P�ʃx�N�g�������܂��Ă���Ƃ��͂�������g�p���܂��傤�B<BR>
     * @param nvx [in]�P�ʃx�N�g��X�v�f
     * @param nvy [in]�P�ʃx�N�g��Y�v�f
     * @param nvz [in]�P�ʃx�N�g��Z�v�f
     * @param out_rz [out]Z����]�A���O���l
     * @param out_ry [out]Y����]�A���O���l
     */
    static void convVectorToRzRy(double nvx, double nvy, double nvz, angle& out_rz, angle& out_ry) {
        convVectorToRzRy((int)(nvx*100000),
                         (int)(nvy*100000),
                         (int)(nvz*100000),
                         out_rz,
                         out_ry );
    }

//    static void convVectorToRzRy(float nvx, float nvy, float nvz, angle& out_rz, angle& out_ry) {
//        convVectorToRzRy((int)(nvx*100000),
//                         (int)(nvy*100000),
//                         (int)(nvz*100000),
//                         out_rz,
//                         out_ry );
//    }

    /**
     * Z����]+Y����]�l����P�ʕ����x�N�g�����擾
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h����2<BR>
     * Z��Y����]���p -> �����x�N�g�� �̕ϊ�<BR>
     * �v�Z�����Ƀe�[�u���Q�Ƃō����ɍs���B<BR>
     * @param prm_rz [in]Z����]�A���O���l
     * @param prm_ry [in]Y����]�A���O���l
     * @param out_nvx [out]�P�ʃx�N�g��X�v�f
     * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
     * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
     */
    static void convRzRyToVector(angle prm_rz,
                                 angle prm_ry,
                                 double& out_nvx,
                                 double& out_nvy,
                                 double& out_nvz);

    /**
     * �x�N�g�����K�� .
     * @param x
     * @param y
     * @param out_nvx
     * @param out_nvy
     */
    static void getNormalized2DVector(double x,
                                      double y,
                                      double& out_nvx,
                                      double& out_nvy) {
        const double t = 1.0 / sqrt(x * x + y * y);
        out_nvx = t * x;
        out_nvy = t * y;
    }

    /**
     * �x�N�g�����K�� .
     * @param x
     * @param y
     * @param out_nvx
     * @param out_nvy
     */
    static void getNormalized2DVector(coord x,
                                      coord y,
                                      double& out_nvx,
                                      double& out_nvy ) {
        const double vx = (double)(x * (1.0 / (LEN_UNIT * PX_UNIT)));
        const double vy = (double)(y * (1.0 / (LEN_UNIT * PX_UNIT)));
        const double t = 1.0 / sqrt(vx * vx + vy * vy);
        out_nvx = t * vx;
        out_nvy = t * vy;
    }


    /**
     * �x�N�g�����K�� .
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
                                    double& out_nvx,
                                    double& out_nvy,
                                    double& out_nvz ) {
        const double t = 1.0 / sqrt(x * x + y * y + z * z);
        out_nvx = t * x;
        out_nvy = t * y;
        out_nvz = t * z;
    }

    /**
     * �x�N�g�����K�� .
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
                                    double& out_nvx,
                                    double& out_nvy,
                                    double& out_nvz ) {
        const double vx = x * (1.0 / (LEN_UNIT * PX_UNIT));
        const double vy = y * (1.0 / (LEN_UNIT * PX_UNIT));
        const double vz = z * (1.0 / (LEN_UNIT * PX_UNIT));
        const double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
        out_nvx = t * vx;
        out_nvy = t * vy;
        out_nvz = t * vz;
    }

    /**
     * ������ς����AZ����]+Y����]������̑g�ݍ��킹��Ԃ��B
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
     * �A���O���l�̐��K�� .
     * @param prm_ang �A���O���l
     * @return 0 �` D360ANG �͈̔͂Ɏ��߂�ꂽ�A���O���l
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
     * �����̓����蔻��<BR>
     * @param x11
     * @param y11
     * @param x12
     * @param y12
     * @param x21
     * @param y21
     * @param x22
     * @param y22
     * @return true:�q�b�g/false:�q�b�g���ĂȂ�
     */
    static bool chk2DLineCrossing(coord x11, coord y11, coord x12, coord y12, coord x21, coord y21, coord x22, coord y22);


    /**
     * ���_���S�̋��ʂƃx�N�g���̌�_�����߂�
     * @param in_r  ���_���S�̋��ʂ̔��a
     * @param in_x1   �x�N�g��From X�v�f
     * @param in_y1   �x�N�g��From Y�v�f
     * @param in_z1   �x�N�g��From Z�v�f
     * @param in_x2   �x�N�g��To X�v�f
     * @param in_y2   �x�N�g��To Y�v�f
     * @param in_z2   �x�N�g��To Z�v�f
     * @param out_x   ���ʂ̌�_X�v�f
     * @param out_y   ���ʂ̌�_Y�v�f
     * @param out_z   ���ʂ̌�_Z�v�f
     */
    template<typename T>
    static void getIntersectionSphereAndVec(double in_r,
                                            double in_x1, double in_y1, double in_z1,
                                            double in_x2, double in_y2, double in_z2,
                                            T& out_x, T& out_y, T& out_z) {
        double vx = in_x2 - in_x1;
        double vy = in_y2 - in_y1;
        double vz = in_z2 - in_z1;
        // �����̍��W(X,Y,Z)��
        //   X = x2 + t*vx;
        //   Y = y2 + t*vy;
        //   Z = z2 + t*vz;
        //�ł���
        //��������ʂ̎�
        //x^2 + y^2 + z^2 = r^2
        //�ɑ������
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
        if (ZEROd_EQ(vzvz+vyvy+vxvx)) {
            //0���Z���߂�Ȃ�
            _TRACE_("�y�x���zgetIntersectionSphereAndVec() 0���Z�̂��߁A���ʂ͐���������܂���");
            out_x = (T)in_r;
            out_y = (T)0;
            out_z = (T)0;
        } else {
            double t = (sqrt((-vyvy-vxvx)*z2z2+(2*vy*vz*in_y2+2*vx*vz*in_x2)*in_z2+(-vzvz-vxvx)*y2y2+2*vx*vy*in_x2*in_y2+(-vzvz-vyvy)*
                        x2x2+rr*vzvz+rr*vyvy+rr*vxvx)-vz*in_z2-vy*in_y2-vx*in_x2)/(vzvz+vyvy+vxvx);

            out_x = (T)(in_x2 + t*vx);
            out_y = (T)(in_y2 + t*vy);
            out_z = (T)(in_z2 + t*vz);
        }
    }

    /**
     * ���_���S�̋��ʂƃx�N�g���̌�_�����߂�
     * @tparam T
     * @param in_r
     * @param in_x
     * @param in_y
     * @param in_z
     * @param out_x
     * @param out_y
     * @param out_z
     */
    template<typename T>
    static void getIntersectionSphereAndVec(double in_r,
                                            double in_x, double in_y, double in_z,
                                            T& out_x, T& out_y, T& out_z) {
//    	t=sqrt(r^2*vz^2+r^2*vy^2+r^2*vx^2)/(vz^2+vy^2+vx^2)
        double vxvx = in_x * in_x;
        double vyvy = in_y * in_y;
        double vzvz = in_z * in_z;
        double rr = in_r * in_r;
        double t=sqrt(rr*vzvz+rr*vyvy+rr*vxvx)/(vzvz+vyvy+vxvx);
        out_x = (T)(t*in_x);
        out_y = (T)(t*in_y);
        out_z = (T)(t*in_z);
    }

    template<typename T>
    static void getIntersectionSphereAndVec(double in_x, double in_y, double in_z,
                                            T& out_x, T& out_y, T& out_z) {
//    		t=1/sqrt(vz^2+vy^2+vx^2)
        double vxvx = in_x * in_x;
        double vyvy = in_y * in_y;
        double vzvz = in_z * in_z;
        double t = 1.0/sqrt(vzvz+vyvy+vxvx);
        out_x = (T)(t*in_x);
        out_y = (T)(t*in_y);
        out_z = (T)(t*in_z);
    }


    /**
     * ���_���S�̋����̈�l�ȃ����_�����W��Ԃ� .
     * @param r ���̔��a
     * @param out_x
     * @param out_y
     * @param out_z
     */
    static void getRndSpherCoord(double r,
                                 double& out_x,
                                 double& out_y,
                                 double& out_z) {
        int rnd = RND(0,10000-1);
        out_x = RND_SPHERE_X[rnd] * r;
        out_y = RND_SPHERE_Y[rnd] * r;
        out_z = RND_SPHERE_Z[rnd] * r;
    }

    /**
     * ���_���S�̉~���̈�l�ȃ����_�����W��Ԃ� .
     * @param r �~�̔��a
     * @param out_x
     * @param out_y
     */
    static void getRndCircleCoord(double r,
                                  double& out_x,
                                  double& out_y) {
        int rnd = RND(0,10000-1);
        out_x = RND_CIRCLE_X[rnd] * r;
        out_y = RND_CIRCLE_Y[rnd] * r;
    }

    /**
     * �R���_�ɐڂ���ʂ̖@���x�N�g�������߂� .
     * �����̒��_�͎��v���Ɏw�肷��ƁA���̖ʂ̏オ�@���ƂȂ�B
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
     * 3������ԃx�N�g�� V,W �̐����p�����߂�B
     * @param V
     * @param W
     * @return �x�N�g�� V,W �̐����p(���W�A�� 0 �` PI)
     */
    static float get3DRadAngle(D3DXVECTOR3& V, D3DXVECTOR3& W) {
        //�x�N�g�� V W �̐����p�����߂�
        //    V=(vx,vy,vz)=(bx-ax,by-ay,bz-az)
        //    W=(wx,wy,wz)=(cx-ax,cy-ay,cz-az)
        //    �Ƃ����V�AW�x�N�g�����Ȃ��p��
        //    cos��=(V�AW�x�N�g���̓��ρj���iV�̑傫���j���iW�̑傫���j
        //        =(vx*wx+vy*wy+vz*wz)   �� ��(vx^2+vy^2+vz^2) �� ��(wx^2+wy^2+wz^2)
        FLOAT dot = D3DXVec3Dot(&V, &W);
        FLOAT lV = D3DXVec3Length(&V);
        FLOAT lW = D3DXVec3Length(&W);
        FLOAT cosTh = dot / lV / lW;
        float rad = acos(cosTh);
        if (rad < 0) {
            rad = -rad;
        }
        if (rad > PI) {
            return 2.0*PI - rad;
        } else {
            return rad;
        }
    }

    static void putMat(D3DXMATRIX* pMat) {
        _TRACE_( pMat->_11<<", "<< pMat->_12<<", "<< pMat->_13<<", "<< pMat->_14);
        _TRACE_( pMat->_21<<", "<< pMat->_22<<", "<< pMat->_23<<", "<< pMat->_24);
        _TRACE_( pMat->_31<<", "<< pMat->_32<<", "<< pMat->_33<<", "<< pMat->_34);
        _TRACE_( pMat->_41<<", "<< pMat->_42<<", "<< pMat->_43<<", "<< pMat->_44);
    };


    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

    /**
     * world�ϊ��s��ݒ� .
     * �g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_ScRxRzRyMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);




    static void setWorldMatrix_ScRzRyMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RxRzRy(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_RxRzRy(angle prm_rx, angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld);


    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRzRyScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRyRzScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Z����] �~ X����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��Y����]������܂���B_ry�͂Q��ڂ�X����]�ƂȂ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRzRxScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_ScRzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �r���{�[�hX����] �~ �r���{�[�hY����] �~ �r���{�[�hZ����]  �~ �g��k�� �~ ���s�ړ� �̕ϊ��s����쐬���f�o�C�X�ɐݒ� <BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_BxyzScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScRzBxyzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScMvRxRzRy(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);


    static void mulWorldMatrix_ScRxRzRyMv(const GeometricActor* const prm_pActor, D3DXMATRIX& inout_matWorld);

    static void mulWorldMatrix_RzRyScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& inout_matWorld);


    static void setWorldMatrix_RzBxyzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_BxyzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_AlignAppScBxyzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_ScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld);

    inline static void setWorldMatrix_RxRzRyMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
        //�ł��悭���p����World�ϊ�
        //X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
        //��XYZ�̏��łȂ����Ƃɒ���
        // | cosRz*cosRy                        , sinRz       , cosRz*-sinRy                        , 0 |
        // | (cosRx*-sinRz*cosRy + sinRx*sinRy) , cosRx*cosRz , (cosRx*-sinRz*-sinRy + sinRx*cosRy) , 0 |
        // | (-sinRx*-sinRz*cosRy + cosRx*sinRy), -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy), 0 |
        // | dx                                 , dy          , dz                                  , 1 |
        const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
        const float cosRx = (float)ANG_COS(prm_pActor->_rx);
        const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
        const float cosRy = (float)ANG_COS(prm_pActor->_ry);
        const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
        const float cosRz = (float)ANG_COS(prm_pActor->_rz);

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
#endif /*GGAF_DX_UTIL_H_*/

