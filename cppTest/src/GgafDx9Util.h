#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_
#define sgn(X) (GgafDx9Util::sign(X))
#define max3(A,B,C) (GgafDx9Util::max3(A,B,C))

//typedef int angle;

class GgafDx9Util /*: GgafUtil*/ {

public:
	static int COS_UNITLEN[];
	static int SIN_UNITLEN[];
	static int TAN_UNITLEN[];
	static int RAD_UNITLEN[];
	static float COS[];
	static float SIN[];


	static bool _isInit;

	static void init();
	static angle getAngle(int prm_vx, int prm_vy);
	static void getWayAngle(int prm_vx_Center, int prm_vy_Center, int prm_iWay, angle prm_angClearance, int* out_paAngle);
	static void getWayAngle(angle prm_angCenter, int prm_iWay, angle prm_angClearance, angle* out_paAngle);
	static void getRadiationAngle(angle prm_angStart, int prm_iWay, angle* out_paAngle);
	static angle addAngle(angle prm_angNow, angle prm_angOffset);
	static void rotXY(int prm_pX, int prm_pY, angle prm_ang, int* out_pX, int* out_pY);

	static int getDistance(int x1, int y1, int x2, int y2);

	/**
	 * ê¸ï™ÇÃìñÇΩÇËîªíË<BR>
	 * @param (x1,y1)-(x2,y2) Å~ (x3,y3)-(x4,y4)
	 * @return true:ÉqÉbÉg/false:ÉqÉbÉgÇµÇƒÇ»Ç¢
	 */
	static bool chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);
	static int sign(int x);
	//static DWORD max3(DWORD a, DWORD b, DWORD c);
};

#endif /*GGAFDX9UTIL_H_*/

