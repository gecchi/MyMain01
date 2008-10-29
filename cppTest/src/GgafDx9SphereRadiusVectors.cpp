#include "stdafx.h"

//GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() {
//
//}

COMPARE_ABLE_SR_VECTOR GgafDx9SphereRadiusVectors::_sr[(SCALE_ANG90+1)*(SCALE_ANG90+1)];

GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() {
	int index;
	static unsigned short xXY, yXY, xXZ, zXZ;
	static double radRotAxisZ, radRotAxisY;
	for (angle angRotAxisZ = 0; angRotAxisZ <= SCALE_ANG90; angRotAxisZ ++) {
		//XY平面状の球表面の点を求める。
		radRotAxisZ = ((PI*2.0) / (SCALE_ANG90*4)) * angRotAxisZ;
		xXY = cos(radRotAxisZ)*10000.0;
		yXY = sin(radRotAxisZ)*10000.0;
		for (angle angRotAxisY = 0; angRotAxisY <= SCALE_ANG90; angRotAxisY ++) {
			//XY平面状の球表面の点を、Y軸回転する。
			radRotAxisY = ((PI*2.0) / (SCALE_ANG90*4))* angRotAxisY;
			xXZ = xXY*cos(radRotAxisY);
			zXZ = xXY*sin(radRotAxisY);
			index = angRotAxisZ*(SCALE_ANG90+1) + angRotAxisY;
			_sr[index].vec.y = yXY;
			_sr[index].vec.x = xXZ;
			_sr[index].vec.z = zXZ;
		}
	}
}

void GgafDx9SphereRadiusVectors::getRotAngleClosely(unsigned short prm_x, unsigned short prm_y, unsigned short prm_z, int& out_angRotZ, int& out_angRotY) {
	static COMPARE_ABLE_SR_VECTOR target;
	target.vec.y = prm_y;
	target.vec.x = 0;
	target.vec.z = 0;
	//cout << "y="<<y<<" x="<<x<<" z="<<z<<" target.num_yzx="<< (target.num_yzx) << endl;
	//yのバイナリサーチ
	static int top, bottom, center, center_prev;
	//int cnt = 0;

	top = 0;
	bottom = (SCALE_ANG90+1)*(SCALE_ANG90+1) - 1;

	center_prev = -1;
	while (true) {
		center = (top + bottom) / 2;
		if (_sr[center].num_yzx < target.num_yzx) {
			top = center;
		} else {
			bottom = center;
		}

		if (center_prev == center) {
			break;
		} else {
			center_prev = center;
		}
		//cnt++;
	}
	//cout << "cnt1=" << cnt << endl;

	//xzのサーチ
	target.vec.y = _sr[top].vec.y;
	target.vec.x = prm_x;
	target.vec.z = prm_z;

	top = (top / (SCALE_ANG90+1)) * (SCALE_ANG90+1);
	bottom = top + (SCALE_ANG90+1)-1;
	center_prev = -1;
	while (true) {
		center = (top + bottom) / 2;
		if (_sr[center].num_yzx < target.num_yzx) {
			top = center;
		} else {
			bottom = center;
		}

		if (center_prev == center) {
			break;
		} else {
			center_prev = center;
		}
		//cnt++;
	}

	out_angRotZ = top / (SCALE_ANG90+1);
	out_angRotY = top % (SCALE_ANG90+1);


	//cout << "cnt2=" << cnt << endl;
	//cout << "target.num_yzx="<< target.num_yzx << " top="<< top << " out_angRotZ=" << out_angRotZ << " out_angRotY=" << out_angRotY << endl;

}

void GgafDx9SphereRadiusVectors::getVectorClosely(int out_angRotY, int prm_angRotZ, unsigned short& out_x, unsigned short& out_y, unsigned short& out_z) {
	int index = out_angRotY*(SCALE_ANG90+1)+prm_angRotZ;
	out_x = _sr[index].vec.x;
	out_y = _sr[index].vec.y;
	out_z = _sr[index].vec.z;
}

GgafDx9SphereRadiusVectors::~GgafDx9SphereRadiusVectors() {
}
