#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSphereRadiusVectors::GgafDxSphereRadiusVectors() : GgafObject() {
    int index;
    static double s_angRad = ((PI * 2.0) / (D90SANG * 4));
    UINT32 xXY, yXY, xXZ, zXZ;
    double radRotAxisZ, radRotAxisY;
    for (s_ang angFaceAxisZ = 0; angFaceAxisZ <= D90SANG; angFaceAxisZ++) {
        //XY���ʏ�̋��\�ʂ̓_�����߂�B
        radRotAxisZ = s_angRad * angFaceAxisZ;
        xXY = cos(radRotAxisZ) * 1000000.0;
        yXY = sin(radRotAxisZ) * 1000000.0;
        for (s_ang angFaceAxisY = 0; angFaceAxisY <= D90SANG; angFaceAxisY++) {
            //XY���ʏ�̋��\�ʂ̓_���AY����]����B
            //���ӁF����Y����]�Ƃ́A�v�Z�̓s����A����nY����]�̋t��]�ɂȂ�܂��B
            radRotAxisY = s_angRad * angFaceAxisY;
            xXZ = xXY * cos(radRotAxisY);
            zXZ = xXY * sin(radRotAxisY);
            index = angFaceAxisZ * (D90SANG + 1) + angFaceAxisY;
            _sr[index].set(xXZ, yXY, zXZ);
        }
    }
}

void GgafDxSphereRadiusVectors::getFaceAngClosely(UINT32 prm_x,
                                                  UINT32 prm_y,
                                                  UINT32 prm_z,
                                                  s_ang& out_angFaceZ,
                                                  s_ang& out_angFaceY_rev,
                                                  int s) {
    static class COMPARE_ABLE_SR_VECTOR target;
    target.set(0, prm_y, 0);

    //rZ(y�v�f)�̃o�C�i���T�[�`
    int top, bottom, center, center_prev;
    top = 0;
    bottom = (D90SANG+1)*(D90SANG+1) - 1;

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
    top = (top / (D90SANG+1)) * (D90SANG+1);
    bottom = top + (D90SANG+1)-1;
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

    out_angFaceZ = top / (D90SANG+1);
    out_angFaceY_rev = top % (D90SANG+1);

}


GgafDxSphereRadiusVectors::~GgafDxSphereRadiusVectors() {
}
