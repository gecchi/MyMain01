#include "stdafx.h"


bool GgafDx9Util::_isInit = false;
int GgafDx9Util::COS_UNITLEN[S_ANG360];
int GgafDx9Util::SIN_UNITLEN[S_ANG360];
int GgafDx9Util::TAN_UNITLEN[S_ANG360];
int GgafDx9Util::RAD_UNITLEN[S_ANG360];
float GgafDx9Util::COS[S_ANG360];
float GgafDx9Util::SIN[S_ANG360];


void GgafDx9Util::init() {
	if (_isInit) {
		return;
	} else {
		for (s_ang ang = 0; ang < S_ANG360; ang++) {
			double rad = (PI*2.0*ang)/S_ANG360;
			COS_UNITLEN[ang] = (int)(cos(rad)*LEN_UNIT);
			SIN_UNITLEN[ang] = (int)(sin(rad)*LEN_UNIT);
			TAN_UNITLEN[ang] = (int)(tan(rad)*LEN_UNIT);
			RAD_UNITLEN[ang] = (int)(rad*LEN_UNIT);

			COS[ang] = (float)(cos(rad));
			SIN[ang] = (float)(sin(rad));

		}

		COS_UNITLEN[0]        =  1*LEN_UNIT;
		COS_UNITLEN[S_ANG90]  =  0;
		COS_UNITLEN[S_ANG180] = -1*LEN_UNIT;
		COS_UNITLEN[S_ANG270] =  0;

		SIN_UNITLEN[0]        =  0;
		SIN_UNITLEN[S_ANG90]  =  1*LEN_UNIT;
		SIN_UNITLEN[S_ANG180] =  0;
		SIN_UNITLEN[S_ANG270] = -1*LEN_UNIT;

		TAN_UNITLEN[0]        =  0;
		TAN_UNITLEN[S_ANG90]  =  LONG_MAX;
		TAN_UNITLEN[S_ANG180] =  0;
		TAN_UNITLEN[S_ANG270] = -1*LONG_MAX;
		//TAN_UNITLEN[ANGLE360] = 0;

		COS[0]        =  1;
		COS[S_ANG90]  =  0;
		COS[S_ANG180] = -1;
		COS[S_ANG270] =  0;

		SIN[0]        =  0;
		SIN[S_ANG90]  =  1;
		SIN[S_ANG180] =  0;
		SIN[S_ANG270] = -1;

	}
}

angle GgafDx9Util::getAngle(int prm_vx, int prm_vy) {
	if (prm_vy == 0) {
		if (prm_vx > 0) {
			return 0;
		} else if (prm_vx < 0) {
			return ANGLE180;
		} else {
			//(0,0)のベクトル方向は無い
			//しかたないので 0
			return 0;
		}
	} else if (prm_vx == 0) {
		if (prm_vy > 0) {
			return ANGLE90;
		} else if (prm_vy < 0) {
			return ANGLE270;
		} else {
			//(0,0)のベクトル方向は無い
			//しかたないので 0
			return 0;
		}
	} else {

		//バイナリーサーチで直近を探す
		static s_ang left, right, middle;
		if (prm_vx > 0 && prm_vy > 0 ) { //第1象限
			left  = 1;
			right = S_ANG90 - 1;
		} else if (prm_vx < 0 && prm_vy > 0 ) { //第2象限
			left  = S_ANG90 + 1;
			right = S_ANG180 - 1;
		} else if (prm_vx < 0 && prm_vy < 0 ) { //第3象限
			left  = S_ANG180 + 1;
			right = S_ANG270 - 1;
		} else if (prm_vx > 0 && prm_vy < 0 ) { //第4象限
			left  = S_ANG270 + 1;
			right = S_ANG360 - 1;
		} else {
			//ぴったり重なっている場合
			return 0; //仕方ないので0
		}
		s_ang middle_prev = -1;
		int lTerget = (int)(LEN_UNIT*((1.0*prm_vy) / (1.0*prm_vx)));
		while (true) {
			middle = (left + right) / 2;
			if (TAN_UNITLEN[middle] < lTerget) {

				left = middle ;
			} else {
				right = middle;
			}
			if (middle_prev == middle) {
				break;
			} else {
				middle_prev = middle;
			}
		}
		return left*ANGLE_RATE;
	}
}

void GgafDx9Util::getWayAngle(int prm_vx_Center, int prm_vy_Center, int prm_iWay, angle prm_angClearance, angle* out_paAngle) {
	return getWayAngle(getAngle(prm_vx_Center, prm_vy_Center), prm_iWay, prm_angClearance, out_paAngle);
}


void GgafDx9Util::getWayAngle(angle prm_angCenter, int prm_iWay, angle prm_angClearance, angle* out_paAngle) {
	int angstart = addAngle(prm_angCenter, ((prm_iWay-1)*prm_angClearance)/-2);

    for (int i = 0; i < prm_iWay; i++) {
		out_paAngle[i] = addAngle(angstart, prm_angClearance*i);
	}
}
void GgafDx9Util::getRadiationAngle(angle prm_angStart, int prm_iWay, angle* out_paAngle) {
    for (int i = 0; i < prm_iWay; i++) {
		out_paAngle[i] = addAngle(prm_angStart, (ANGLE360*i)/prm_iWay);
	}
}

angle GgafDx9Util::addAngle(angle prm_angNow, angle prm_angOffset) {
	angle angAdd = prm_angNow + prm_angOffset;
	while(angAdd >= ANGLE360) {
		angAdd -= ANGLE360;
	}
	while(angAdd < 0) {
		angAdd += ANGLE360;
	}
	return angAdd;
}

void GgafDx9Util::rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y) {
	out_X = (int)(floor((prm_X*GgafDx9Util::COS[prm_ang/ANGLE_RATE]) - (prm_Y*GgafDx9Util::SIN[prm_ang/ANGLE_RATE])));
	out_Y = (int)(floor((prm_X*GgafDx9Util::SIN[prm_ang/ANGLE_RATE]) + (prm_Y*GgafDx9Util::COS[prm_ang/ANGLE_RATE])));
}


// 線分の当たり判定 (x11,y11)-(x12,y12) × (x21,y21)-(x22,y22)
bool GgafDx9Util::chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {

    //x座標によるチェック
    if (x11 >= x12) {
        if ((x11 < x21 && x11 < x22) || (x12 > x21 && x12 > x22)) {
            return  false;
        }
    } else {
        if ((x12 < x21 && x12 < x22) || (x11 > x21 && x11 > x22)) {
            return  false;
        }
    }
    //y座標によるチェック
    if (y11 >= y12) {
        if ((y11 < y21 && y11 < y22) || (y12 > y21 && y12 > y22)) {
            return  false;
        }
    } else {
        if ((y12 < y21 && y12 < y22) || (y11 > y21 && y11 > y22)) {
            return  false;
        }
    }
    if (((x11 - x12) * (y21 - y11) + (y11 - y12) * (x11 - x21)) * ((x11 - x12) * (y22 - y11) + (y11 - y12) * (x11 - x22)) > 0) {
        return  false;
    }
    if (((x21 - x22) * (y11 - y21) + (y21 - y22) * (x21 - x11)) * ((x21 - x22) * (y12 - y21) + (y21 - y22) * (x21 - x12)) > 0) {
        return  false;
    }
    return  true;
}

int GgafDx9Util::getDistance(int x1, int y1, int x2, int y2) {
	return sqrt( (((double)(x2-x1))*((double)(x2-x1))) + (((double)(y2-y1))*((double)(y2-y1))) );
}



int GgafDx9Util::sign(int x) {
	if(x < 0) {
        return -1;
    } else if(x > 0) {
        return 1;
    } else {
        return 0;
    }
}

//DWORD GgafDx9Util::max3(DWORD a, DWORD b, DWORD c) {
//	if (a > b) {
//		if (a > c) {
//			return a;
//		} else {
//			return c;
//		}
//	} else {
//		if (b > c) {
//			return b;
//		} else {
//			return c;
//		}
//	}
//}

