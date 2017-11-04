#include "jp/ggaf/dxcore/util/GgafDxSphereRadiusVectors.h"

#include <math.h>

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSphereRadiusVectors::GgafDxSphereRadiusVectors() : GgafObject() {
    int index;
    static double s_angRad = ((PI * 2.0) / (D90SANG * 4));
    uint32_t xXY, yXY, xXZ, zXZ;
    double radRotAxisZ, radRotAxisY;
    for (s_ang faceAxisZ = 0; faceAxisZ <= D90SANG; faceAxisZ++) {
        //XY���ʏ�̋��\�ʂ̓_�����߂�B
        radRotAxisZ = s_angRad * faceAxisZ;
        xXY = cos(radRotAxisZ) * 1000000.0;
        yXY = sin(radRotAxisZ) * 1000000.0;
        for (s_ang faceAxisY = 0; faceAxisY <= D90SANG; faceAxisY++) {
            //XY���ʏ�̋��\�ʂ̓_���AY����]����B
            //���ӁF����Y����]�Ƃ́A�v�Z�̓s����A����nY����]�̋t��]�ɂȂ�܂��B
            radRotAxisY = s_angRad * faceAxisY;
            xXZ = xXY * cos(radRotAxisY);
            zXZ = xXY * sin(radRotAxisY);
            index = faceAxisZ * (D90SANG + 1) + faceAxisY;
            _sr[index].set(xXZ, yXY, zXZ);
        }
    }
}

void GgafDxSphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
                                                  uint32_t prm_y,
                                                  uint32_t prm_z,
                                                  s_ang& out_faceZ,
                                                  s_ang& out_faceY_rev,
                                                  int s) {
    static class COMPARE_ABLE_SR_VECTOR target;
    target.set(0, prm_y, 0);

    //rz(y�v�f)�̃o�C�i���T�[�`
    int top, bottom, center, center_prev;
    top = 0;
    bottom = (D90SANG+1)*(D90SANG+1) - 1;

    center_prev = -1;
    for (int i = 0; i < s; i++) { //�ō�25��܂Ō���
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
    for (int i = 0; i < s; i++) { //�ō�25��܂Ō���
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

    out_faceZ = top / (D90SANG+1);
    out_faceY_rev = top % ((unsigned int)(D90SANG+1));

}


GgafDxSphereRadiusVectors::~GgafDxSphereRadiusVectors() {
}
