#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_

typedef int angle;

class GgafDx9Util : GgafUtil {

public:
	static int _aCos_UnitLen[];
	static int _aSin_UnitLen[];
	static int _aTan_UnitLen[];
	static int _aRad_UnitLen[];
	static float _aCos[];
	static float _aSin[];


	static bool _radian_init_flg;

	static void init();
	static angle getAngle(int prm_vx, int prm_vy);
	static void getWayAngle(int prm_vx_Center, int prm_vy_Center, int prm_iWay, angle prm_angClearance, int* out_paAngle);
	static void getWayAngle(angle prm_angCenter, int prm_iWay, angle prm_angClearance, angle* out_paAngle);
	static void getRadiationAngle(angle prm_angStart, int prm_iWay, angle* out_paAngle);
	static angle addAngle(angle prm_angNow, angle prm_angOffset);
	static void rotXY(int prm_pX, int prm_pY, angle prm_ang, int* out_pX, int* out_pY);

	/**
	 * 線分の当たり判定<BR>
	 * @param (x1,y1)-(x2,y2) × (x3,y3)-(x4,y4)
	 * @return true:ヒット/false:ヒットしてない
	 */
	static bool chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);
	static int sgn(int x);

};

#endif /*GGAFDX9UTIL_H_*/

