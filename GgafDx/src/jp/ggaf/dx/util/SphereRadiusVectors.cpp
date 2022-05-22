#include "jp/ggaf/dx/util/SphereRadiusVectors.h"

#include "jp/ggaf/dx/util/Util.h"

#include <math.h>

using namespace GgafDx;

SphereRadiusVectors::SphereRadiusVectors() : GgafCore::Object() {
    uint32_t n_y, n_x, n_z;
    double xXY, yXY, x, y, z;
    double radRotAxisZ, radRotAxisY;

    for (s_ang faceAxisZ = 0; faceAxisZ <= D90SANG; faceAxisZ++) {
        //XYïΩñ è„ÇÃãÖï\ñ ÇÃì_ÇãÅÇﬂÇÈÅB
        radRotAxisZ = (((PI * 2.0) * faceAxisZ) / D360SANG) ;
        xXY = cos(radRotAxisZ);
        yXY = sin(radRotAxisZ);
        n_y = yXY * 10000000.0;
        for (s_ang faceAxisY_rev = 0; faceAxisY_rev <= D90SANG; faceAxisY_rev++) {
            //XYïΩñ è„ÇÃãÖï\ñ ÇÃì_ÇÅAYé≤âÒì]Ç∑ÇÈÅB
            //íçà”ÅFÇ±ÇÃYé≤âÒì]ÇÕÅAåvéZÇÃìsçáè„ÅAç∂éËånYé≤âÒì]ÇÃãtâÒì]Ç…Ç»ÇËÇ‹Ç∑ÅB
            radRotAxisY = (((PI * 2.0) * faceAxisY_rev) / D360SANG);
            x = xXY * cos(radRotAxisY);
            z = xXY * sin(radRotAxisY);
            n_x = x * 10000000.0;
            n_z = z * 10000000.0;
            //_sr_vec
            SrVec* pVec = &(_sr_vec[faceAxisZ][faceAxisY_rev]);
            pVec->x = n_x;
            pVec->y = n_y;
            pVec->z = n_z;

            //ãtéQè∆Çê›íË
            _vy_vz_2_rz_ry_rev[n_y][n_z].rz = faceAxisZ;
            _vy_vz_2_rz_ry_rev[n_y][n_z].ry = faceAxisY_rev;
        }
    }
}

void SphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
                                            uint32_t prm_y,
                                            uint32_t prm_z,
                                            s_ang& out_faceZ,
                                            s_ang& out_faceY_rev) {
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
    out_faceZ = pRzRy->rz;
    out_faceY_rev = pRzRy->ry;

}

SphereRadiusVectors::~SphereRadiusVectors() {
}
