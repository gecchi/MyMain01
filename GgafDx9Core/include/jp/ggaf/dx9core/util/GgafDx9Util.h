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
	 * 原点からパラメータ座標を向く方向ベクトルの、Z軸回転アングル値とY軸回転アングル値を取得 .
	 * ついでに単位方向ベクトルも貰えちゃう。
	 * @param x [in]X座標
	 * @param y [in]Y座標
	 * @param z [in]Z座標
	 * @param out_nvx [out]単位ベクトルX要素
	 * @param out_nvy [out]単位ベクトルY要素
	 * @param out_nvz [out]単位ベクトルZ要素
	 * @param out_angRotZ [out]Z軸回転アングル値
	 * @param out_angRotY [out]Y軸回転アングル値
	 */
	static void getRotAngleZY(int x, int y, int z, double& out_nvx, double& out_nvy, double& out_nvz, angle& out_angRotZ, angle& out_angRotY);

	/**
	 * Z軸回転+Y軸回転から単位方向ベクトルを取得
	 * @param prm_angRotZ [in]Z軸回転アングル値
	 * @param prm_angRotY [in]Y軸回転アングル値
	 * @param out_nvx [out]単位ベクトルX要素
	 * @param out_nvy [out]単位ベクトルY要素
	 * @param out_nvz [out]単位ベクトルZ要素
	 */
	static void getNormalizeVectorZY(angle prm_angRotZ, angle prm_angRotY, double& out_nvx, double& out_nvy, double& out_nvz);

	/**
	 * 線分の当たり判定<BR>
	 * @param x11
	 * @param y11
	 * @param x12
	 * @param y12
	 * @param x21
	 * @param y21
	 * @param x22
	 * @param y22
	 * @return true:ヒット/false:ヒットしてない
	 */
	static bool chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);
	static int sign(int x);
	//static DWORD max3(DWORD a, DWORD b, DWORD c);


};

#endif /*GGAFDX9UTIL_H_*/

