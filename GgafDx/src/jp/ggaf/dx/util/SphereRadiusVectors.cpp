#include "jp/ggaf/dx/util/SphereRadiusVectors.h"

#include <math.h>

using namespace GgafDx;

SphereRadiusVectors::SphereRadiusVectors() : GgafCore::Object() {
    uint32_t n_yXY, n_xXZ, n_zXZ;
    double xXY, yXY;
    double radRotAxisZ, radRotAxisY;
    for (s_ang faceAxisZ = 0; faceAxisZ <= D90SANG; faceAxisZ++) {
        //XY平面上の球表面の点を求める。
        radRotAxisZ = (((PI * 2.0) * faceAxisZ) / D360SANG) ;
        xXY = cos(radRotAxisZ);
        yXY = sin(radRotAxisZ);
        n_yXY = yXY * 10000000.0;
        for (s_ang faceAxisY_rev = 0; faceAxisY_rev <= D90SANG; faceAxisY_rev++) {
            //XY平面上の球表面の点を、Y軸回転する。
            //注意：このY軸回転とは、計算の都合上、左手系Y軸回転の逆回転になります。
            radRotAxisY = (((PI * 2.0) * faceAxisY_rev) / D360SANG);
            n_xXZ = xXY * cos(radRotAxisY) * 10000000.0;
            n_zXZ = xXY * sin(radRotAxisY) * 10000000.0;
            SrVec* pVec = &(_sr_vec[faceAxisZ][faceAxisY_rev]);
            pVec->x = n_xXZ;
            pVec->y = n_yXY;
            pVec->z = n_zXZ;
            _vy_vz_rzry[n_yXY][n_zXZ].rz = faceAxisZ;
            _vy_vz_rzry[n_yXY][n_zXZ].ry = faceAxisY_rev;

        }
    }
}

void SphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
                                            uint32_t prm_y,
                                            uint32_t prm_z,
                                            s_ang& out_faceZ,
                                            s_ang& out_faceY_rev) {
    std::map<uint32_t, std::map<uint32_t, RzRy> >::iterator ite_begin_vy = _vy_vz_rzry.upper_bound(prm_y);
    if (ite_begin_vy != _vy_vz_rzry.begin()) {
        ite_begin_vy--;
    }
    std::map<uint32_t, RzRy>* pVz_RzRy = &(ite_begin_vy->second);
    std::map<uint32_t, RzRy>::iterator ite_begin_vz = pVz_RzRy->lower_bound(prm_z);
    if (ite_begin_vz != pVz_RzRy->begin()) {
        ite_begin_vz--;
    }
    RzRy* pRzRy = &(ite_begin_vz->second);
    out_faceZ = pRzRy->rz;
    out_faceY_rev = pRzRy->ry;
}

SphereRadiusVectors::~SphereRadiusVectors() {
}
