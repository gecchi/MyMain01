#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

bool StgUtil::_was_StgUtil_inited_flg = false;
float StgUtil::ROOT_1_MINUS_XX[1000];
uint32_t StgUtil::BITNUM[33];

void StgUtil::init() {
    GgafDxUtil::init();
    if (StgUtil::_was_StgUtil_inited_flg) {
        return;
    }

    //ROOT_1_MINUS_XXの設定
    for (int i = 0; i < 1000; i++) {
        StgUtil::ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }


    StgUtil::BITNUM[ 0] = 0;
    StgUtil::BITNUM[ 1] = (0x1);            //0b 00000000 00000000 00000000 00000001
    StgUtil::BITNUM[ 2] = (0x2);            //0b 00000000 00000000 00000000 00000010
    StgUtil::BITNUM[ 3] = (0x4);            //0b 00000000 00000000 00000000 00000100
    StgUtil::BITNUM[ 4] = (0x8);            //0b 00000000 00000000 00000000 00001000
    StgUtil::BITNUM[ 5] = (0x10);           //0b 00000000 00000000 00000000 00010000
    StgUtil::BITNUM[ 6] = (0x20);           //0b 00000000 00000000 00000000 00100000
    StgUtil::BITNUM[ 7] = (0x40);           //0b 00000000 00000000 00000000 01000000
    StgUtil::BITNUM[ 8] = (0x80);           //0b 00000000 00000000 00000000 10000000
    StgUtil::BITNUM[ 9] = (0x100);          //0b 00000000 00000000 00000001 00000000
    StgUtil::BITNUM[10] = (0x200);          //0b 00000000 00000000 00000010 00000000
    StgUtil::BITNUM[11] = (0x400);          //0b 00000000 00000000 00000100 00000000
    StgUtil::BITNUM[12] = (0x800);          //0b 00000000 00000000 00001000 00000000
    StgUtil::BITNUM[13] = (0x1000);         //0b 00000000 00000000 00010000 00000000
    StgUtil::BITNUM[14] = (0x2000);         //0b 00000000 00000000 00100000 00000000
    StgUtil::BITNUM[15] = (0x4000);         //0b 00000000 00000000 01000000 00000000
    StgUtil::BITNUM[16] = (0x8000);         //0b 00000000 00000000 10000000 00000000
    StgUtil::BITNUM[17] = (0x10000);        //0b 00000000 00000001 00000000 00000000
    StgUtil::BITNUM[18] = (0x20000);        //0b 00000000 00000010 00000000 00000000
    StgUtil::BITNUM[19] = (0x40000);        //0b 00000000 00000100 00000000 00000000
    StgUtil::BITNUM[20] = (0x80000);        //0b 00000000 00001000 00000000 00000000
    StgUtil::BITNUM[21] = (0x100000);       //0b 00000000 00010000 00000000 00000000
    StgUtil::BITNUM[22] = (0x200000);       //0b 00000000 00100000 00000000 00000000
    StgUtil::BITNUM[23] = (0x400000);       //0b 00000000 01000000 00000000 00000000
    StgUtil::BITNUM[24] = (0x800000);       //0b 00000000 10000000 00000000 00000000
    StgUtil::BITNUM[25] = (0x1000000);      //0b 00000001 00000000 00000000 00000000
    StgUtil::BITNUM[26] = (0x2000000);      //0b 00000010 00000000 00000000 00000000
    StgUtil::BITNUM[27] = (0x4000000);      //0b 00000100 00000000 00000000 00000000
    StgUtil::BITNUM[28] = (0x8000000);      //0b 00001000 00000000 00000000 00000000
    StgUtil::BITNUM[29] = (0x10000000);     //0b 00010000 00000000 00000000 00000000
    StgUtil::BITNUM[30] = (0x20000000);     //0b 00100000 00000000 00000000 00000000
    StgUtil::BITNUM[31] = (0x40000000);     //0b 01000000 00000000 00000000 00000000
    StgUtil::BITNUM[32] = (0x80000000);     //0b 10000000 00000000 00000000 00000000

    StgUtil::_was_StgUtil_inited_flg = true;
}

GgafDxDrawableActor* StgUtil::shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_shot,
                                         coord prm_r,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int)) {
    if (prm_set_num <= 0) {  return nullptr;  }
    float vx, vy, vz;
    GgafDxUtil::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    coord x = vx * prm_r;
    coord y = vy * prm_r;
    coord z = vz * prm_r;
    GgafDxDrawableActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        pActor_shot = (GgafDxDrawableActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
        if (pActor_shot) {
            dispatch_num++;
            pActor_shot->position(prm_x + x,
                                  prm_y + y,
                                  prm_z + z);
            pActor_shot->getKuroko()->setRzRyMvAng(prm_rz, prm_ry);
            pActor_shot->getKuroko()->setMvVelo(now_velo);
            pActor_shot->getKuroko()->setMvAcce(now_acce);
            if (pFunc_call_back_dispatched) {
                pFunc_call_back_dispatched(pActor_shot, dispatch_num, n);
            }
        }
        now_velo *= prm_attenuated;
    }
    return pActor_shot;
}

GgafDxDrawableActor* StgUtil::shotWay001(GgafDxGeometricActor* prm_pFrom,
                                         GgafActorDepository* prm_pDepo_shot,
                                         coord prm_r,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int)) {
    return shotWay001(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDxDrawableActor* StgUtil::shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                         coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                         GgafActorDepository* prm_pDepo_shot,
                                         coord prm_r,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int)) {
    angle rz,ry;
    GgafDxUtil::convVectorToRzRy(prm_to_x - prm_from_x,
                                 prm_to_y - prm_from_y,
                                 prm_to_z - prm_from_z,
                                 rz, ry);
    return shotWay001(prm_from_x, prm_from_y, prm_from_z,
                      rz, ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDxDrawableActor* StgUtil::shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rx, angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_shot,
                                         coord prm_r,
                                         int prm_way_N,
                                         angle prm_ang_clearance_N,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int, int)) {
    if (prm_way_N <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way_N];
    float vx, vy, vz;
    float tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    for (int i = 0; i < prm_way_N; i++) {
        rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        ry = D0ANG;
        GgafDxUtil::convRzRyToVector(rz, ry, vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxDrawableActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            pActor_shot = (GgafDxDrawableActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->position(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_shot->getKuroko()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getKuroko()->setMvVelo(now_velo);
                pActor_shot->getKuroko()->setMvAcce(now_acce);
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way_N);
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDxCore::GgafDxDrawableActor* StgUtil::shotWay002(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                     GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     int prm_way_N,
                                                     angle prm_ang_clearance_N,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int)) {
    return shotWay002(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_way_N,
                      prm_ang_clearance_N,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDxDrawableActor* StgUtil::shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rx, angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                         GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                         GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                         coord prm_r,
                                         int prm_way_N, int prm_way_M,
                                         angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int, int, int, int)) {
    if (prm_way_N <= 0 || prm_way_M <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    angle* paAng_way_M = NEW angle[prm_way_M];
    uint32_t* paUint32_dotmat = NEW uint32_t[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDxUtil::getWayAngle2D(0, prm_way_M, prm_ang_clearance_M, paAng_way_M);
    GgafDxGeoElem** papaGeo = NEW GgafDxGeoElem*[prm_way_N];
    float vx, vy, vz;
    float tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    uint32_t dot1,dot2,dot3;
    for (int i = 0; i < prm_way_N; i++) {
        dot1 = prm_paUint32_dotmat1 ? prm_paUint32_dotmat1[i] : 0;
        dot2 = prm_paUint32_dotmat2 ? prm_paUint32_dotmat2[i] : 0;
        dot3 = prm_paUint32_dotmat3 ? prm_paUint32_dotmat3[i] : 0;
        paUint32_dotmat[i] = dot1 | dot2 | dot3;
        if (paUint32_dotmat[i] == 0) {
            papaGeo[i] = nullptr;
            continue;
        }
        rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        papaGeo[i] = NEW GgafDxGeoElem[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                ry = GgafDxUtil::simplifyAng(paAng_way_M[j]);
                GgafDxUtil::convRzRyToVector(rz, ry, vx, vy, vz);
                tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
                ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
                tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
                papaGeo[i][j].x = (coord)(tx * prm_r);
                papaGeo[i][j].y = (coord)(ty * prm_r);
                papaGeo[i][j].z = (coord)(tz * prm_r);
                GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                             papaGeo[i][j].rz, papaGeo[i][j].ry);
            }
        }
    }
    GgafDxDrawableActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    int depo_no = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            if (paUint32_dotmat[i] == 0) {
                continue;
            }
            for (int j = 0; j < prm_way_M; j++) {
                if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                    if (prm_paUint32_dotmat1 && (prm_paUint32_dotmat1[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxDrawableActor*)prm_pDepo_shot1->dispatch(n*prm_interval_frames+1);
                        depo_no = 1;
                    } else if (prm_paUint32_dotmat2 && (prm_paUint32_dotmat2[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxDrawableActor*)prm_pDepo_shot2->dispatch(n*prm_interval_frames+1);
                        depo_no = 2;
                    } else if (prm_paUint32_dotmat3 && (prm_paUint32_dotmat3[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxDrawableActor*)prm_pDepo_shot3->dispatch(n*prm_interval_frames+1);
                        depo_no = 3;
                    } else {
                        pActor_shot = nullptr;
                        depo_no = 0;
                    }
                } else {
                    pActor_shot = nullptr;
                    depo_no = 0;
                }
                if (pActor_shot) {
                    dispatch_num++;
                    pActor_shot->position(prm_x + papaGeo[i][j].x,
                                          prm_y + papaGeo[i][j].y,
                                          prm_z + papaGeo[i][j].z);
                    pActor_shot->getKuroko()->setRzRyMvAng(papaGeo[i][j].rz, papaGeo[i][j].ry);
                    pActor_shot->getKuroko()->setMvVelo(now_velo);
                    pActor_shot->getKuroko()->setMvAcce(now_acce);
                    if (pFunc_call_back_dispatched) {
                        pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, depo_no, i, j);
                    }
                }
            }
        }
        now_velo *= prm_attenuated;
    }

    GGAF_DELETEARR(paAng_way_N);
    GGAF_DELETEARR(paAng_way_M);
    GGAF_DELETEARR(paUint32_dotmat);
    for (int i = 0; i < prm_way_N; i++) {
        if (papaGeo[i]) {
            GGAF_DELETEARR(papaGeo[i]);
        }
    }
    GGAF_DELETEARR(papaGeo);

    return pActor_shot;
}


GgafDxDrawableActor* StgUtil::shotWay003(GgafDxGeometricActor* prm_pFrom,
                                         GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                         GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                         GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                         coord prm_r,
                                         int prm_way_N, int prm_way_M,
                                         angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int, int, int, int)) {
    return shotWay003(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot1, prm_paUint32_dotmat1,
                      prm_pDepo_shot2, prm_paUint32_dotmat2,
                      prm_pDepo_shot3, prm_paUint32_dotmat3,
                      prm_r,
                      prm_way_N, prm_way_M,
                      prm_ang_clearance_N, prm_ang_clearance_M,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}


GgafDxDrawableActor* StgUtil::shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_shot,
                                         coord prm_r,
                                         int prm_radial_way_num, angle prm_expanse_angle,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int, int)) {
    if (prm_radial_way_num <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way = NEW angle[prm_radial_way_num];
    GgafDxUtil::getRadialAngle2D(0, prm_radial_way_num, paAng_way);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_radial_way_num];
    angle expanse_rz = (D180ANG - prm_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RzRy(GgafDxUtil::simplifyAng(prm_rz-D90ANG),prm_ry, matWorldRot);

    float vx, vy, vz;
    float tx, ty, tz; //最終方向の絶対座標の単位ベクトル
    for (int i = 0; i < prm_radial_way_num; i++) {
        GgafDxUtil::convRzRyToVector(expanse_rz, paAng_way[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxDrawableActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_radial_way_num; i++) {
            pActor_shot = (GgafDxDrawableActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->position(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_shot->getKuroko()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getKuroko()->setMvVelo(now_velo);
                pActor_shot->getKuroko()->setMvAcce(now_acce);
//                pActor_shot->_rz = Rz;
//                pActor_shot->_ry = Ry;
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way);
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDxDrawableActor* StgUtil::shotWay004(GgafDxGeometricActor* prm_pFrom,
                                         GgafActorDepository* prm_pDepo_shot,
                                         coord prm_r,
                                         int prm_way, angle prm_expanse_angle,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_call_back_dispatched)(GgafDxDrawableActor*, int, int, int)) {
    return shotWay004(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_way, prm_expanse_angle,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

