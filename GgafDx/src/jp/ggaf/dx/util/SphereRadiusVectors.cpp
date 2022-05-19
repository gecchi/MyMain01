#include "jp/ggaf/dx/util/SphereRadiusVectors.h"

#include <math.h>

using namespace GgafDx;

SphereRadiusVectors::SphereRadiusVectors() : GgafCore::Object() {
    uint32_t n_yXY, n_xXZ, n_zXZ;
    double xXY, yXY;
    double radRotAxisZ, radRotAxisY;
    for (s_ang faceAxisZ = 0; faceAxisZ <= D90SANG; faceAxisZ++) {
        //XYïΩñ è„ÇÃãÖï\ñ ÇÃì_ÇãÅÇﬂÇÈÅB
        radRotAxisZ = (((PI * 2.0) * faceAxisZ) / D360SANG) ;
        xXY = cos(radRotAxisZ);
        yXY = sin(radRotAxisZ);
        n_yXY = yXY * 10000000.0;
        for (s_ang faceAxisY_rev = 0; faceAxisY_rev <= D90SANG; faceAxisY_rev++) {
            //XYïΩñ è„ÇÃãÖï\ñ ÇÃì_ÇÅAYé≤âÒì]Ç∑ÇÈÅB
            //íçà”ÅFÇ±ÇÃYé≤âÒì]Ç∆ÇÕÅAåvéZÇÃìsçáè„ÅAç∂éËånYé≤âÒì]ÇÃãtâÒì]Ç…Ç»ÇËÇ‹Ç∑ÅB
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
    std::map<uint32_t, std::map<uint32_t, RzRy> >::iterator ite_begin_vy = _vy_vz_rzry.lower_bound(prm_y);
//    if (ite_begin_vy != _vy_vz_rzry.begin()) {
//        ite_begin_vy--;
//    }
    std::map<uint32_t, RzRy>* pVz_RzRy = &(ite_begin_vy->second);
    std::map<uint32_t, RzRy>::iterator ite_begin_vz = pVz_RzRy->upper_bound(prm_z);
    if (ite_begin_vz != pVz_RzRy->begin()) {
        ite_begin_vz--;
    }
    RzRy* pRzRy = &(ite_begin_vz->second);
    out_faceZ = pRzRy->rz;
    out_faceY_rev = pRzRy->ry;
}


//618175922 <DEBUG> [886][898]=(852,9997014,244320)
//618175922 <DEBUG> [886][899]=(426,9997014,244321)
//618175922 <DEBUG> [886][900]=(0,9997014,244321)
//
//
//618175921 <DEBUG> [886][809]=(38641,9997014,241246)
//618175921 <DEBUG> [886][810]=(38220,9997014,241313)
//618175921 <DEBUG> [886][811]=(37799,9997014,241380)
//
//618201586 <DEBUG> x (88600,81000) -> (88600,89700) Å¶(0.003822,0.999701,-0.0241313)


SphereRadiusVectors::~SphereRadiusVectors() {
}
