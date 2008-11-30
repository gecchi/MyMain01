#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_
#define sgn(X) (GgafDx9Util::sign(X))
#define max3(A,B,C) (GgafDx9Util::max3(A,B,C))

typedef int angle;
typedef int s_ang;

class GgafDx9Util : GgafUtil {

public:
	static int COS_UNITLEN[];
	static int SIN_UNITLEN[];
	static int TAN_UNITLEN[];
	static int RAD_UNITLEN[];
	static float COS[];
	static float SIN[];
	static GgafDx9SphereRadiusVectors _srv;

	static bool _isInit;

	static void init();
	static angle getAngle(int prm_vx, int prm_vy);
	static void getWayAngle(int prm_vx_Center, int prm_vy_Center, int prm_iWay, angle prm_angClearance, int* out_paAngle);
	static void getWayAngle(angle prm_angCenter, int prm_iWay, angle prm_angClearance, angle* out_paAngle);
	static void getRadiationAngle(angle prm_angStart, int prm_iWay, angle* out_paAngle);
	static angle addAngle(angle prm_angNow, angle prm_angOffset);
	static void rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y);


	static int getDistance(int x1, int y1, int x2, int y2);

	/**
	 * ���_����p�����[�^���W�����������x�N�g���́AZ����]�A���O���l��Y����]�A���O���l���擾 .
	 * ���łɒP�ʕ����x�N�g�����Ⴆ���Ⴄ�B
	 * @param x [in]X���W
	 * @param y [in]Y���W
	 * @param z [in]Z���W
	 * @param out_nvx [out]�P�ʃx�N�g��X�v�f
	 * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
	 * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
	 * @param out_angRotZ [out]Z����]�A���O���l
	 * @param out_angRotY [out]Y����]�A���O���l
	 */
	static void getRotAngleZY(int x, int y, int z, double& out_nvx, double& out_nvy, double& out_nvz, angle& out_angRotZ, angle& out_angRotY);

	/**
	 * Z����]+Y����]����P�ʕ����x�N�g�����擾
	 * @param prm_angRotZ [in]Z����]�A���O���l
	 * @param prm_angRotY [in]Y����]�A���O���l
	 * @param out_nvx [out]�P�ʃx�N�g��X�v�f
	 * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
	 * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
	 */
	static void getNormalizeVectorZY(angle prm_angRotZ, angle prm_angRotY, double& out_nvx, double& out_nvy, double& out_nvz);

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
	//static DWORD max3(DWORD a, DWORD b, DWORD c);


};

#endif /*GGAFDX9UTIL_H_*/

