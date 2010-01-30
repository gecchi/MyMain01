#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

COMPARE_ABLE_SR_VECTOR GgafDx9SphereRadiusVectors::_sr[(S_ANG90 + 1) * (S_ANG90 + 1)];

GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() : GgafObject() {
    int index;
    static double s_angRad = ((PI * 2.0) / (S_ANG90 * 4));
    static unsigned __int16 xXY, yXY, xXZ, zXZ;
    static double radRotAxisZ, radRotAxisY;
    for (s_ang angFaceAxisZ = 0; angFaceAxisZ <= S_ANG90; angFaceAxisZ++) {
        //XY���ʏ�̋��\�ʂ̓_�����߂�B
        radRotAxisZ = s_angRad * angFaceAxisZ;
        xXY = cos(radRotAxisZ) * 10000.0;
        yXY = sin(radRotAxisZ) * 10000.0;
        for (s_ang angFaceAxisY = 0; angFaceAxisY <= S_ANG90; angFaceAxisY++) {
            //XY���ʏ�̋��\�ʂ̓_���AY����]����B
            //���ӁF����Y����]�Ƃ́A�v�Z�̓s����A����nY����]�̋t��]�ɂȂ�܂��B
            radRotAxisY = s_angRad * angFaceAxisY;
            xXZ = xXY * cos(radRotAxisY);
            zXZ = xXY * sin(radRotAxisY);
            index = angFaceAxisZ * (S_ANG90 + 1) + angFaceAxisY;
            _sr[index].set(xXZ, yXY, zXZ);
        }
    }
}

void GgafDx9SphereRadiusVectors::getFaceAngClosely(unsigned __int16 prm_x,
                                                    unsigned __int16 prm_y,
                                                    unsigned __int16 prm_z,
                                                    s_ang& out_angFaceZ,
                                                    s_ang& out_angFaceY_rev,
                                                    int s) {
    static class COMPARE_ABLE_SR_VECTOR target;
    target.set(0, prm_y, 0);

    //rZ(y�v�f)�̃o�C�i���T�[�`
    static int top, bottom, center, center_prev;
    top = 0;
    bottom = (S_ANG90+1)*(S_ANG90+1) - 1;

    center_prev = -1;
    for(int i = 0; i < s; i++) { //�ō�25��܂Ō���
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
    target.set(prm_x, _sr[top].vec.y, prm_z);
    top = (top / (S_ANG90+1)) * (S_ANG90+1);
    bottom = top + (S_ANG90+1)-1;
    center_prev = -1;
    for(int i = 0; i < s; i++) { //�ō�25��܂Ō���
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

    out_angFaceZ = top / (S_ANG90+1);
    out_angFaceY_rev = top % (S_ANG90+1);

}

void GgafDx9SphereRadiusVectors::getVectorClosely(s_ang prm_angFaceY_rev,
                                                  s_ang prm_angFaceZ,
                                                  unsigned __int16& out_x,
                                                  unsigned __int16& out_y,
                                                  unsigned __int16& out_z) {
    static int index;
    index = prm_angFaceZ*(S_ANG90+1)+prm_angFaceY_rev;
    out_x = _sr[index].vec.x;
    out_y = _sr[index].vec.y;
    out_z = _sr[index].vec.z;
}

GgafDx9SphereRadiusVectors::~GgafDx9SphereRadiusVectors() {
}
