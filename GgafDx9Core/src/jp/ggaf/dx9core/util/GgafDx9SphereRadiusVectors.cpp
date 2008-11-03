#include "stdafx.h"

//GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() {
//
//}

COMPARE_ABLE_SR_VECTOR GgafDx9SphereRadiusVectors::_sr[(S_ANG90+1)*(S_ANG90+1)];

GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() {
	int index;
	static double s_angRad = ((PI*2.0) / (S_ANG90*4));
	static unsigned __int16 xXY, yXY, xXZ, zXZ;
	static double radRotAxisZ, radRotAxisY;
	for (s_ang angRotAxisZ = 0; angRotAxisZ <= S_ANG90; angRotAxisZ ++) {
		//XY���ʏ�̋��\�ʂ̓_�����߂�B
		radRotAxisZ = s_angRad * angRotAxisZ;
		xXY = cos(radRotAxisZ)*10000.0;
		yXY = sin(radRotAxisZ)*10000.0;
		for (s_ang angRotAxisY = 0; angRotAxisY <= S_ANG90; angRotAxisY ++) {
			//XY���ʏ�̋��\�ʂ̓_���AY����]����B
			radRotAxisY = s_angRad * angRotAxisY;
			xXZ = xXY*cos(radRotAxisY);
			zXZ = xXY*sin(radRotAxisY);
			index = angRotAxisZ*(S_ANG90+1) + angRotAxisY;
			_sr[index].vec.y = yXY;
			_sr[index].vec.x = xXZ;
			_sr[index].vec.z = zXZ;
		}
	}
}

void GgafDx9SphereRadiusVectors::getRotAngleClosely(unsigned __int16 prm_x, unsigned __int16 prm_y, unsigned __int16 prm_z, int& out_angRotZ, int& out_angRotY) {
	static COMPARE_ABLE_SR_VECTOR target;
	target.vec.y = prm_y;
	target.vec.x = 0;
	target.vec.z = 0;

	//y�̃o�C�i���T�[�`
	static int top, bottom, center, center_prev;
	top = 0;
	bottom = (S_ANG90+1)*(S_ANG90+1) - 1;

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
	}

	//xz�̃T�[�`
	target.vec.y = _sr[top].vec.y;
	target.vec.x = prm_x;
	target.vec.z = prm_z;

	top = (top / (S_ANG90+1)) * (S_ANG90+1);
	bottom = top + (S_ANG90+1)-1;
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
	}

	out_angRotZ = top / (S_ANG90+1);
	out_angRotY = top % (S_ANG90+1);

}

void GgafDx9SphereRadiusVectors::getVectorClosely(s_ang prm_angRotY, s_ang prm_angRotZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z) {
	int index = prm_angRotZ*(S_ANG90+1)+prm_angRotY;
	out_x = _sr[index].vec.x;
	out_y = _sr[index].vec.y;
	out_z = _sr[index].vec.z;
}

GgafDx9SphereRadiusVectors::~GgafDx9SphereRadiusVectors() {
}
