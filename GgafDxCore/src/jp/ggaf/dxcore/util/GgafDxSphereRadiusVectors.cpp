#include "jp/ggaf/dxcore/util/GgafDxSphereRadiusVectors.h"

#include <math.h>

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSphereRadiusVectors::GgafDxSphereRadiusVectors() : GgafObject() {
    int index;
    static double s_angRad = ((PI * 2.0) / (D90SANG * 4));
    uint32_t xXY, yXY, xXZ, zXZ;
    double radRotAxisZ, radRotAxisY;
    for (s_ang ang_faceAxisZ = 0; ang_faceAxisZ <= D90SANG; ang_faceAxisZ++) {
        //XY平面上の球表面の点を求める。
        radRotAxisZ = s_angRad * ang_faceAxisZ;
        xXY = cos(radRotAxisZ) * 1000000.0;
        yXY = sin(radRotAxisZ) * 1000000.0;
        for (s_ang ang_faceAxisY = 0; ang_faceAxisY <= D90SANG; ang_faceAxisY++) {
            //XY平面上の球表面の点を、Y軸回転する。
            //注意：このY軸回転とは、計算の都合上、左手系Y軸回転の逆回転になります。
            radRotAxisY = s_angRad * ang_faceAxisY;
            xXZ = xXY * cos(radRotAxisY);
            zXZ = xXY * sin(radRotAxisY);
            index = ang_faceAxisZ * (D90SANG + 1) + ang_faceAxisY;
            _sr[index].set(xXZ, yXY, zXZ);
        }
    }
}

void GgafDxSphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
                                                  uint32_t prm_y,
                                                  uint32_t prm_z,
                                                  s_ang& out_ang_faceZ,
                                                  s_ang& out_ang_faceY_rev,
                                                  int s) {
    static class COMPARE_ABLE_SR_VECTOR target;
    target.set(0, prm_y, 0);

    //rz(y要素)のバイナリサーチ
    int top, bottom, center, center_prev;
    top = 0;
    bottom = (D90SANG+1)*(D90SANG+1) - 1;

    center_prev = -1;
    for(int i = 0; i < s; i++) { //最高25回まで検索
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

    //xzのサーチ
    target.set(prm_x, _sr[top].vec.y, prm_z);
    top = (top / (D90SANG+1)) * (D90SANG+1);
    bottom = top + (D90SANG+1)-1;
    center_prev = -1;
    for(int i = 0; i < s; i++) { //最高25回まで検索
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

    out_ang_faceZ = top / (D90SANG+1);
    out_ang_faceY_rev = top % ((unsigned int)(D90SANG+1));

}


GgafDxSphereRadiusVectors::~GgafDxSphereRadiusVectors() {
}
