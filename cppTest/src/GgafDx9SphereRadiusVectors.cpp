#include "stdafx.h"

//GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() {
//
//}

COMPARE_ABLE_SR_VECTOR GgafDx9SphereRadiusVectors::_sr[(ANGLE90+1)*(ANGLE90+1)];
GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() {
	int index;
	static unsigned short xXY, yXY, xXZ, zXZ;
	static double radRotAxisZ, radRotAxisY;
	for (angle angRotAxisZ = 0; angRotAxisZ <= ANGLE90; angRotAxisZ ++) {
		//XY平面状の球表面の点を求める。
		radRotAxisZ = ((PI*2.0) / (ANGLE90*4)) * angRotAxisZ;
		xXY = cos(radRotAxisZ)*10000.0;
		yXY = sin(radRotAxisZ)*10000.0;
		for (angle angRotAxisY = 0; angRotAxisY <= ANGLE90; angRotAxisY ++) {
			//XY平面状の球表面の点を、Y軸回転する。
			radRotAxisY = ((PI*2.0) / (ANGLE90*4))* angRotAxisY;
			xXZ = xXY*cos(radRotAxisY);
			zXZ = xXY*sin(radRotAxisY);
			index = angRotAxisZ*(ANGLE90+1) + angRotAxisY;
			_sr[index].vec.y = yXY;
			_sr[index].vec.x = xXZ;
			_sr[index].vec.z = zXZ;
		}
	}
}

void GgafDx9SphereRadiusVectors::getRotAngleClosely(unsigned short x, unsigned short y, unsigned short z, angle& out_angRotZ, angle& out_angRotY) {
	static COMPARE_ABLE_SR_VECTOR target;
	target.vec.y = y;
	target.vec.x = 0;
	target.vec.z = 0;
	//cout << "y="<<y<<" x="<<x<<" z="<<z<<" target.num_yzx="<< (target.num_yzx) << endl;
	//yのバイナリサーチ
	static int left, right, middle;
	int middle_prev;

	left = 0;
	right = (ANGLE90+1)*(ANGLE90+1) - 1;

	middle_prev = -1;
	while (true) {
		middle = (left + right) / 2;
		if (_sr[middle].num_yzx < target.num_yzx) {
			left = middle;
		} else {
			right = middle;
		}

		if (middle_prev == middle) {
			break;
		} else {
			middle_prev = middle;
		}
	}

	//xのサーチ
	target.vec.y = _sr[left].vec.y;
	target.vec.x = x;

	left = 0;
	right = (ANGLE90+1)*(ANGLE90+1) - 1;

	middle_prev = -1;
	while (true) {
		middle = (left + right) / 2;
		if (_sr[middle].num_yzx < target.num_yzx) {
			left = middle;
		} else {
			right = middle;
		}

		if (middle_prev == middle) {
			break;
		} else {
			middle_prev = middle;
		}
	}

	//zのサーチ
	target.vec.x = _sr[left].vec.x;
	target.vec.z = z;

	left = 0;
	right = (ANGLE90+1)*(ANGLE90+1) - 1;

	middle_prev = -1;
	while (true) {
		middle = (left + right) / 2;
		if (_sr[middle].num_yzx < target.num_yzx) {
			left = middle;
		} else {
			right = middle;
		}

		if (middle_prev == middle) {
			break;
		} else {
			middle_prev = middle;
		}
	}

	div_t ires = div(left, ANGLE90+1);
	out_angRotZ = ires.quot;
	out_angRotY = ires.rem;

	//cout << "target.num_yzx="<< target.num_yzx << " left="<< left << " out_angRotZ=" << out_angRotZ << " out_angRotY=" << out_angRotY << endl;

}

GgafDx9SphereRadiusVectors::~GgafDx9SphereRadiusVectors() {
}
