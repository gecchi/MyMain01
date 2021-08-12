#include "jp/ggaf/dx/util/SphereRadiusVectors.h"

#include <math.h>


using namespace GgafDx;

SphereRadiusVectors::SphereRadiusVectors() : GgafCore::Object() {
    int index_rz_ry;
    uint32_t n_xXY, n_yXY, n_xXZ, n_zXZ;
    double xXY, yXY, xXZ, zXZ;
    double radRotAxisZ, radRotAxisY;
    for (s_ang faceAxisZ = 0; faceAxisZ <= D90SANG; faceAxisZ++) {
        //XY平面上の球表面の点を求める。
        radRotAxisZ = (((PI * 2.0) * faceAxisZ) / D360SANG) ;
        xXY = cos(radRotAxisZ);
        yXY = sin(radRotAxisZ);
        n_xXY = xXY * 1000000.0;
        n_yXY = yXY * 1000000.0;
        for (s_ang faceAxisY = 0; faceAxisY <= D90SANG; faceAxisY++) {
            //XY平面上の球表面の点を、Y軸回転する。
            //注意：このY軸回転とは、計算の都合上、左手系Y軸回転の逆回転になります。
            radRotAxisY = (((PI * 2.0) * faceAxisY) / D360SANG);
            n_xXZ = xXY * cos(radRotAxisY) * 1000000.0;
            n_zXZ = xXY * sin(radRotAxisY) * 1000000.0;
            index_rz_ry = faceAxisZ * (D90SANG + 1) + faceAxisY;
            _sr[index_rz_ry].set(n_xXZ, n_yXY, n_zXZ);

            _vy_vz_rzry[n_yXY][n_zXZ].rz = faceAxisZ;
            _vy_vz_rzry[n_yXY][n_zXZ].ry = faceAxisY;

            //_sortmap[_sr[index_rz_ry].num_yzx] = index_rz_ry;

            //_TRACE_("("<<faceAxisZ<<","<<faceAxisY<<")\t_sr["<<index_rz_ry<<"].set("<<n_xXZ<<","<<n_yXY<<","<<n_zXZ<<")\tnum_yzx="<<_sr[index_rz_ry].num_yzx<<"\t_sortmap["<<_sr[index_rz_ry].num_yzx<<"]="<<index_rz_ry);

        }
    }
    _TRACE_("done");
}

void SphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
                                            uint32_t prm_y,
                                            uint32_t prm_z,
                                            s_ang& out_faceZ,
                                            s_ang& out_faceY_rev) {

    std::map<uint32_t, std::map<uint32_t, RzRy> >::iterator begin_vy = _vy_vz_rzry.upper_bound(prm_y);
    if (begin_vy != _vy_vz_rzry.begin()) {
        begin_vy--;
    }
    std::map<uint32_t, RzRy>& vz_rzry = begin_vy->second;
    std::map<uint32_t, RzRy>::iterator begin_vz = vz_rzry.lower_bound(prm_z);
    if (begin_vz != vz_rzry.begin()) {
        begin_vz--;
    }
    RzRy& rzry = begin_vz->second;
    out_faceZ = rzry.rz;
    out_faceY_rev = rzry.ry;
}
void SphereRadiusVectors::getFaceAngClosely_debug(uint32_t prm_x,
                                            uint32_t prm_y,
                                            uint32_t prm_z,
                                            s_ang& out_faceZ,
                                            s_ang& out_faceY_rev) {

    ///////////////////////////////////



    int s = 99;
    static class COMPARE_ABLE_SR_VECTOR target;
    target.set(0, prm_y, 0);

    //rz(y要素)のバイナリサーチ
    int top, bottom, center, center_prev;
    top = 0;
    bottom = (D90SANG+1)*(D90SANG+1) - 1;

    center_prev = -1;
    for (int i = 0; i < s; i++) { //最高25回まで検索
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
    for (int i = 0; i < s; i++) { //最高25回まで検索
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



//////////////////////////////////////////////////

//    if (prm_x==339049 && prm_y==88315 && prm_z == 936613) {
//        _TRACE_("BREAK");
//    }
//    uint64_t num_yzx = 0;
//    num_yzx = ((uint64_t)prm_y<<42) | ((uint64_t)prm_z<<21) | ((uint64_t)prm_x);
//    std::map<uint64_t, uint32_t>::iterator begin = _sortmap.lower_bound(num_yzx);
//    int index = begin->second;
//    s_ang out_faceZ2 = index / (D90SANG+1);
//    s_ang out_faceY_rev2 = index % ((unsigned int)(D90SANG+1));

    std::map<uint32_t, std::map<uint32_t, RzRy> >::iterator begin_vy = _vy_vz_rzry.upper_bound(prm_y);
    if (begin_vy != _vy_vz_rzry.begin()) {
        begin_vy--;
    } else {
        _TRACE_("きわきわ1");
    }


//    std::map<uint32_t, RzRy>& vz_rzry = _vy_vz_rzry[begin_vy->first];

    std::map<uint32_t, RzRy>& vz_rzry = begin_vy->second;

    std::map<uint32_t, RzRy>::iterator begin_vz = vz_rzry.lower_bound(prm_z);
    if (begin_vz != vz_rzry.begin()) {
        begin_vz--;
    } else {
        _TRACE_("きわきわ2");

    }

    RzRy& rzry = begin_vz->second;
    s_ang out_faceZ2 = rzry.rz;
    s_ang out_faceY_rev2 = rzry.ry;
    if ((out_faceZ2 != out_faceZ) || (out_faceY_rev != out_faceY_rev2)) {
         _TRACE_("違います。\t("<<prm_x<<","<<prm_y<<","<<prm_z<<")\ttop="<<top<<"\ttarget.num_yzx="<<target.num_yzx<<
                    "\t_sr["<<top<<"].num_yzx="<<_sr[top].num_yzx <<
                    "\tbegin_vy->first="<<begin_vy->first<<"\tbegin_vz->first="<<begin_vz->first<<
                    "\t("<<out_faceZ<<","<<out_faceY_rev<<")!=("<<out_faceZ2<<","<<out_faceY_rev2<<")  ");
    } else {
        _TRACE_("同じです。\t("<<prm_x<<","<<prm_y<<","<<prm_z<<")\ttop="<<top<<"\ttarget.num_yzx="<<target.num_yzx<<
                "\t_sr["<<top<<"].num_yzx="<<_sr[top].num_yzx <<
                "\tbegin_vy->first="<<begin_vy->first<<"\tbegin_vz->first="<<begin_vz->first<<
                "\t("<<out_faceZ<<","<<out_faceY_rev<<")!=("<<out_faceZ2<<","<<out_faceY_rev2<<")  ");


    }







}

//void SphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
//                                            uint32_t prm_y,
//                                            uint32_t prm_z,
//                                            s_ang& out_faceZ,
//                                            s_ang& out_faceY_rev,
//                                            int s) {
//    static class COMPARE_ABLE_SR_VECTOR target;
//    target.set(0, prm_y, 0);
//
//    //rz(y要素)のバイナリサーチ
//    int top, bottom, center, center_prev;
//    top = 0;
//    bottom = (D90SANG+1)*(D90SANG+1) - 1;
//
//    center_prev = -1;
//    for (int i = 0; i < s; i++) { //最高25回まで検索
//        center = (top + bottom) / 2;
//        if (_sr[center].num_yzx < target.num_yzx) {
//            top = center;
//        } else {
//            bottom = center;
//        }
//
//        if (center_prev == center) {
//            break;
//        } else {
//            center_prev = center;
//        }
//    }
//
//    //xzのサーチ
//    target.set(prm_x, _sr[top].vec.y, prm_z);
//    top = (top / (D90SANG+1)) * (D90SANG+1);
//    bottom = top + (D90SANG+1)-1;
//    center_prev = -1;
//    for (int i = 0; i < s; i++) { //最高25回まで検索
//        center = (top + bottom) / 2;
//        if (_sr[center].num_yzx < target.num_yzx) {
//            top = center;
//        } else {
//            bottom = center;
//        }
//
//        if (center_prev == center) {
//            break;
//        } else {
//            center_prev = center;
//        }
//    }
//
//    out_faceZ = top / (D90SANG+1);
//    out_faceY_rev = top % ((unsigned int)(D90SANG+1));
//
//}

//void SphereRadiusVectors::getFaceAngClosely(uint32_t prm_x,
//                                            uint32_t prm_y,
//                                            uint32_t prm_z,
//                                            s_ang& out_faceZ,
//                                            s_ang& out_faceY_rev,
//                                            int s) {
//    static class COMPARE_ABLE_SR_VECTOR target;
//
//    target.set(prm_x, prm_y, prm_z);
//    int top = 0;
//    int bottom = (D90SANG+1)*(D90SANG+1) - 1;
//    int center;
//    int center_prev = -1;
//    for (int i = 0; i < s; i++) {
//        center = (top + bottom) / 2;
//        if (_sr[center].num_yzx < target.num_yzx) {
//            top = center;
//        } else {
//            bottom = center;
//        }
//
//        if (center_prev == center) {
//            break;
//        } else {
//            center_prev = center;
//        }
//    }
//    out_faceZ = top / (D90SANG+1);
//    out_faceY_rev = top % ((unsigned int)(D90SANG+1));
//
//}


SphereRadiusVectors::~SphereRadiusVectors() {
}
