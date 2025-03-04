#include "jp/ggaf/dx/util/SphereRadiusVectors.h"

#include "jp/ggaf/dx/util/Util.h"

#include <math.h>

using namespace GgafDx;

SphereRadiusVectors::SphereRadiusVectors() : GgafCore::Object() {
    uint32_t n_y, n_x, n_z;
    double xXY, yXY, x, y, z;
    double radRotAxisZ, radRotAxisY;

    for (s_ang s_ang_Rz = 0; s_ang_Rz <= D90SANG*SR_AC; s_ang_Rz++) {
        //XY平面上の球表面の点を求める。
        radRotAxisZ = (((PI * 2.0) * s_ang_Rz) / (1.0*D360SANG*SR_AC) ) ;
        xXY = cos(radRotAxisZ);
        yXY = sin(radRotAxisZ);
        n_y = yXY * 10000000.0;
        for (s_ang s_ang_Ry_rev = 0; s_ang_Ry_rev <= D90SANG*SR_AC; s_ang_Ry_rev++) {
            //XY平面上の球表面の点を、Y軸回転する。
            //注意：このY軸回転は、計算の都合上、左手系Y軸回転の逆回転になります。
            radRotAxisY = (((PI * 2.0) * s_ang_Ry_rev) / (1.0*D360SANG*SR_AC) );
            x = xXY * cos(radRotAxisY);
            z = xXY * sin(radRotAxisY);
            n_x = x * 10000000.0;
            n_z = z * 10000000.0;
            //_sr_vec
            SrVec* pVec = &(_sr_vec[s_ang_Rz][s_ang_Ry_rev]);
            pVec->x = n_x;
            pVec->y = n_y;
            pVec->z = n_z;

            //逆参照を設定
            _vy_vz_2_rz_ry_rev[n_y][n_z].s_rz = s_ang_Rz;
            _vy_vz_2_rz_ry_rev[n_y][n_z].s_ry = s_ang_Ry_rev;
        }
    }
}

void SphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
                                            uint32_t prm_y,
                                            uint32_t prm_z,
                                            angle& out_faceZ,
                                            angle& out_faceY_rev) {
    std::map<uint32_t, std::map<uint32_t, RzRy> >::iterator ite_begin_vy = _vy_vz_2_rz_ry_rev.lower_bound(prm_y);
    if (ite_begin_vy == _vy_vz_2_rz_ry_rev.end()) {
        ite_begin_vy--;
    }
    std::map<uint32_t, RzRy>* pVz_RzRy = &(ite_begin_vy->second);
    std::map<uint32_t, RzRy>::iterator ite_begin_vz = pVz_RzRy->upper_bound(prm_z);
    if (ite_begin_vz != pVz_RzRy->begin()) {
        ite_begin_vz--;
    }
    RzRy* pRzRy = &(ite_begin_vz->second);
    out_faceZ = pRzRy->s_rz*((1.0*SANG_RATE)/SR_AC);
    out_faceY_rev = pRzRy->s_ry*((1.0*SANG_RATE)/SR_AC);

}

SphereRadiusVectors::~SphereRadiusVectors() {
}
