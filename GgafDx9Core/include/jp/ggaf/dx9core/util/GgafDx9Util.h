#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_
namespace GgafDx9Core {

#define sgn(X) (GgafDx9Util::sign(X))
#define max3(A,B,C) (GgafDx9Util::max3(A,B,C))

typedef int angle;
typedef int s_ang;

/**
 * ���[�e�B���e�B.
 * �Ɨ������ÓI�֐��̓R�R�ɏW�񂵂Ă��܂��B
 */
class GgafDx9Util: GgafCore::GgafUtil {

public:
    static int COS_UNITLEN[];
    static int SIN_UNITLEN[];
    static int TAN_UNITLEN[];
    static int RAD_UNITLEN[];
    static float COS[];
    static float SIN[];
    static float RAD[];
    static GgafDx9SphereRadiusVectors _srv;

    static bool _was_inited_flg;

    static void init();
    /**
     * XY���W�n�iZ�������j�ɂ����āA�����x�N�g���̐����p���A���O���l�Ŏ擾
     * XY���W�n�iZ�������j�ɂ����āA���_(0,0)����(prm_vx,prm_vy)�ɐ��������������A
     * X���Ƃ̊Ԃɏo����p�i�R���̕������甽���v���Ɂj���A���O���l�Ŏ擾 .
     * @param prm_vx	X���W
     * @param prm_vy	Y���W
     * @return
     */
    static angle getAngle2D(int prm_vx, int prm_vy);

    /**
     * XY���W�n�iZ�������j�ɂ����āA'N'way�e(N=����)�̃A���O���l���擾 .
     * @param prm_vx_Center [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��X�v�f
     * @param prm_vy_Center [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��Y�v�f
     * @param prm_way	[in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��Q��
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_way,
                              angle prm_angClearance,
                              int* out_paAngle);

    /**
     * XY���W�n�iZ�������j�ɂ����āA'N'way�e(N=����)�̃A���O���l�̔z����擾 .
     * @param prm_angCenter	[in]'N'way�e�̑S�̂Ƃ��Č����Ă�������̃A���O���l
     * @param prm_way	[in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��Q��
     */
    static void getWayAngle2D(angle prm_angCenter, int prm_way, angle prm_angClearance, angle* out_paAngle);

    /**
     * XY���W�n�iZ�������j�ɂ����āA�~�̕��ˏ�S������'N'way�e(N=����)�̃A���O���l��z��Ŏ擾 .
     * �e�ƒe�Ƃ̐����p�� �ϓ��ɂȂ�B�Ⴆ�ΑS����4way�e�̏ꍇ�A�e�ƒe�Ƃ̐����p�͒��p�ł���B
     * @param prm_angStart	���ˏ�̑S����'N'way�e�̂P�ڂ̒e�̃A���O���l
     * @param prm_way	[in] 'N'way�e�� N�B
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��Q��
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
     * ���_����p�����[�^���W�����������x�N�g���́AZ����]�A���O���l��Y����]�A���O���l���擾 .
     * ���łɒP�ʕ����x�N�g�����Q�b�g�ł��܂��B<BR>
     * �Ȃ��Ȃ�΁AZ����]�A���O���l��Y����]�A���O���l���擾����ߒ��ŁA<BR>
     * �����x�N�g���̐��K�����s�Ȃ�Ȃ���΂����Ȃ����߂ł��B<BR>
     * @param x [in]X���W
     * @param y [in]Y���W
     * @param z [in]Z���W
     * @param out_nvx [out]�P�ʃx�N�g��X�v�f
     * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
     * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
     * @param out_angRotZ [out]Z����]�A���O���l
     * @param out_angRotY [out]Y����]�A���O���l
     */
    static void getRotAngleZY(int x,
                              int y,
                              int z,
                              double& out_nvx,
                              double& out_nvy,
                              double& out_nvz,
                              angle& out_angRotZ,
                              angle& out_angRotY);

    /**
     * ���_����p�����[�^���W�����������x�N�g���́AZ����]�A���O���l��Y����]�A���O���l���擾 .
     * @param x [in]X���W
     * @param y [in]Y���W
     * @param z [in]Z���W
     * @param out_angRotZ [out]Z����]�A���O���l
     * @param out_angRotY [out]Y����]�A���O���l
     */
    static void getRotAngleZY(int x, int y, int z, angle& out_angRotZ, angle& out_angRotY);

    /**
     * ���_����p�����[�^�̐��K�����ꂽ�����x�N�g��(�P�ʃx�N�g��)�́AZ����]�A���O���l��Y����]�A���O���l���擾 .
     * �����x�N�g���̐��K���͍s��Ȃ��̂ō����ł��B<BR>
     * @param vx [in]�P�ʃx�N�g��X�v�f
     * @param vy [in]�P�ʃx�N�g��Y�v�f
     * @param vz [in]�P�ʃx�N�g��Z�v�f
     * @param out_angRotZ [out]Z����]�A���O���l
     * @param out_angRotY [out]Y����]�A���O���l
     */
    static void getRotAngleZY(double vx, double vy, double vz, angle& out_angRotZ, angle& out_angRotY);


    /**
     * Z����]+Y����]�l����P�ʕ����x�N�g�����擾
     * @param prm_angRotZ [in]Z����]�A���O���l
     * @param prm_angRotY [in]Y����]�A���O���l
     * @param out_nvx [out]�P�ʃx�N�g��X�v�f
     * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
     * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
     */
    static void getNormalizeVectorZY(angle prm_angRotZ,
                                     angle prm_angRotY,
                                     double& out_nvx,
                                     double& out_nvy,
                                     double& out_nvz);

    static void getNormalizeVector(int x,
                                   int y,
                                   int z,
                                   double& out_nvx,
                                   double& out_nvy,
                                   double& out_nvz);
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
    static bool chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);
    static int sign(int x);

    static double sqrt_fast(double a, int s = 10) {
        double ret = 1;
        for (int i = 1; i <= s; i++) {
            ret = 0.5 * (ret + a / ret);
        }
        return ret;
    }
    //static DWORD max3(DWORD a, DWORD b, DWORD c);
};

}
#endif /*GGAFDX9UTIL_H_*/

