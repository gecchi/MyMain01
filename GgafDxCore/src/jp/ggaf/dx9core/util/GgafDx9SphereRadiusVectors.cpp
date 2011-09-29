#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9SphereRadiusVectors::GgafDx9SphereRadiusVectors() : GgafObject() {
    int index;
    static double s_angRad = ((PI * 2.0) / (S_ANG90 * 4));
    UINT32 xXY, yXY, xXZ, zXZ;
    double radRotAxisZ, radRotAxisY;
    for (s_ang angFaceAxisZ = 0; angFaceAxisZ <= S_ANG90; angFaceAxisZ++) {
        //XY平面上の球表面の点を求める。
        radRotAxisZ = s_angRad * angFaceAxisZ;
        xXY = cos(radRotAxisZ) * 1000000.0;
        yXY = sin(radRotAxisZ) * 1000000.0;
        for (s_ang angFaceAxisY = 0; angFaceAxisY <= S_ANG90; angFaceAxisY++) {
            //XY平面上の球表面の点を、Y軸回転する。
            //注意：このY軸回転とは、計算の都合上、左手系Y軸回転の逆回転になります。
            radRotAxisY = s_angRad * angFaceAxisY;
            xXZ = xXY * cos(radRotAxisY);
            zXZ = xXY * sin(radRotAxisY);
            index = angFaceAxisZ * (S_ANG90 + 1) + angFaceAxisY;
            _sr[index].set(xXZ, yXY, zXZ);
        }
    }
}

void GgafDx9SphereRadiusVectors::getFaceAngClosely(UINT32 prm_x,
                                                   UINT32 prm_y,
                                                   UINT32 prm_z,
                                                   s_ang& out_angFaceZ,
                                                   s_ang& out_angFaceY_rev,
                                                   int s) {
    static class COMPARE_ABLE_SR_VECTOR target;
    target.set(0, prm_y, 0);

    //rZ(y要素)のバイナリサーチ
    int top, bottom, center, center_prev;
    top = 0;
    bottom = (S_ANG90+1)*(S_ANG90+1) - 1;

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
    top = (top / (S_ANG90+1)) * (S_ANG90+1);
    bottom = top + (S_ANG90+1)-1;
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

    out_angFaceZ = top / (S_ANG90+1);
    out_angFaceY_rev = top % (S_ANG90+1);

}

void GgafDx9SphereRadiusVectors::getVectorClosely(s_ang prm_angFaceY_rev,
                                                  s_ang prm_angFaceZ,
                                                  UINT32& out_x,
                                                  UINT32& out_y,
                                                  UINT32& out_z) {
    int index = prm_angFaceZ*(S_ANG90+1)+prm_angFaceY_rev;
    out_x = _sr[index].vec.x;
    out_y = _sr[index].vec.y;
    out_z = _sr[index].vec.z;
}

GgafDx9SphereRadiusVectors::~GgafDx9SphereRadiusVectors() {
}
