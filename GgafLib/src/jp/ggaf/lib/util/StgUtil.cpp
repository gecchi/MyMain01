#include "stdafx.h"
#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

GgafDxDrawableActor* StgUtil::shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_Shot,
                                         coord prm_r,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int)) {
    float vx, vy, vz;
    GgafDxUtil::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    coord X = vx * prm_r;
    coord Y = vy * prm_r;
    coord Z = vz * prm_r;
    GgafDxDrawableActor* pActor_Shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch(n*prm_interval_frames+1);
        if (pActor_Shot) {
            dispatch_num++;
            pActor_Shot->position(prm_x + X,
                                  prm_y + Y,
                                  prm_z + Z);
            pActor_Shot->_pKurokoA->setRzRyMvAng(prm_rz, prm_ry);
            pActor_Shot->_pKurokoA->setMvVelo(now_velo);
            pActor_Shot->_pKurokoA->setMvAcce(now_acce);
            if (pFunc_CallBackDispatched) {
                pFunc_CallBackDispatched(pActor_Shot, dispatch_num, n);
            }
        }
        now_velo *= prm_attenuated;
    }
    return pActor_Shot;
}

GgafDxDrawableActor* StgUtil::shotWay001(GgafDxGeometricActor* prm_pFrom,
                                         GgafActorDepository* prm_pDepo_Shot,
                                         coord prm_r,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int)) {
    return shotWay001(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_Shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_CallBackDispatched);
}

GgafDxDrawableActor* StgUtil::shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                         coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                         GgafActorDepository* prm_pDepo_Shot,
                                         coord prm_r,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int)) {
    angle rz,ry;
    GgafDxUtil::convVectorToRzRy(prm_to_x - prm_from_x,
                                 prm_to_y - prm_from_y,
                                 prm_to_z - prm_from_z,
                                 rz, ry);
    return shotWay001(prm_from_x, prm_from_y, prm_from_z,
                      rz, ry,
                      prm_pDepo_Shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_CallBackDispatched);
}

GgafDxDrawableActor* StgUtil::shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rx, angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_Shot,
                                         coord prm_r,
                                         int prm_way_N,
                                         angle prm_angClearance_N,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int, int)) {
    angle* paAng_way_N = NEW angle[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_angClearance_N, paAng_way_N);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way_N];
    float vx, vy, vz;
    angle Rz,Ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    coord x,y,z;
    for (int i = 0; i < prm_way_N; i++) {
        Rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        Ry = D0ANG;
        GgafDxUtil::convRzRyToVector(Rz, Ry, vx, vy, vz);
        x = vx * prm_r;
        y = vy * prm_r;
        z = vz * prm_r;
        paGeo[i].x = x*matWorldRot._11 + y*matWorldRot._21 + z*matWorldRot._31;
        paGeo[i].y = x*matWorldRot._12 + y*matWorldRot._22 + z*matWorldRot._32;
        paGeo[i].z = x*matWorldRot._13 + y*matWorldRot._23 + z*matWorldRot._33;
        GgafDxUtil::convVectorToRzRy(paGeo[i].x , paGeo[i].y, paGeo[i].z,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxDrawableActor* pActor_Shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch(n*prm_interval_frames+1);
            if (pActor_Shot) {
                dispatch_num++;
                pActor_Shot->position(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_Shot->_pKurokoA->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
                if (pFunc_CallBackDispatched) {
                    pFunc_CallBackDispatched(pActor_Shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way_N);
    GGAF_DELETEARR(paGeo);
    return pActor_Shot;
}

GgafDxCore::GgafDxDrawableActor* StgUtil::shotWay002(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                     GgafCore::GgafActorDepository* prm_pDepo_Shot,
                                                     coord prm_r,
                                                     int prm_way_N,
                                                     angle prm_angClearance_N,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_CallBackDispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int)) {
    return shotWay002(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_Shot,
                      prm_r,
                      prm_way_N,
                      prm_angClearance_N,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_CallBackDispatched);
}

GgafDxDrawableActor* StgUtil::shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rx, angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_Shot1, uint32_t* prm_paUint32_dotmat1,
                                         GgafActorDepository* prm_pDepo_Shot2, uint32_t* prm_paUint32_dotmat2,
                                         GgafActorDepository* prm_pDepo_Shot3, uint32_t* prm_paUint32_dotmat3,
                                         coord prm_r,
                                         int prm_way_N, int prm_way_M,
                                         angle prm_angClearance_N, angle prm_angClearance_M,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int, int, int, int)) {
    angle* paAng_way_N = NEW angle[prm_way_N];
    angle* paAng_way_M = NEW angle[prm_way_M];
    uint32_t* paUint32_dotmat = NEW uint32_t[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_angClearance_N, paAng_way_N);
    GgafDxUtil::getWayAngle2D(0, prm_way_M, prm_angClearance_M, paAng_way_M);
    GgafDxGeoElem** papaGeo = NEW GgafDxGeoElem*[prm_way_N];
    float vx, vy, vz;
    angle Rz,Ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    coord x,y,z;
    uint32_t dot1,dot2,dot3;
    for (int i = 0; i < prm_way_N; i++) {
        dot1 = prm_paUint32_dotmat1 ? prm_paUint32_dotmat1[i] : 0;
        dot2 = prm_paUint32_dotmat2 ? prm_paUint32_dotmat2[i] : 0;
        dot3 = prm_paUint32_dotmat3 ? prm_paUint32_dotmat3[i] : 0;
        paUint32_dotmat[i] = dot1 | dot2 | dot3;
        if (paUint32_dotmat[i] == 0) {
            continue;
        }
        Rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        papaGeo[i] = NEW GgafDxGeoElem[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            if (paUint32_dotmat[i] & GgafDxUtil::BITNUM[prm_way_M-j]) {
                Ry = GgafDxUtil::simplifyAng(paAng_way_M[j]);
                GgafDxUtil::convRzRyToVector(Rz, Ry, vx, vy, vz);
                x = vx * prm_r;
                y = vy * prm_r;
                z = vz * prm_r;
                papaGeo[i][j].x = x*matWorldRot._11 + y*matWorldRot._21 + z*matWorldRot._31;
                papaGeo[i][j].y = x*matWorldRot._12 + y*matWorldRot._22 + z*matWorldRot._32;
                papaGeo[i][j].z = x*matWorldRot._13 + y*matWorldRot._23 + z*matWorldRot._33;
                GgafDxUtil::convVectorToRzRy(papaGeo[i][j].x , papaGeo[i][j].y, papaGeo[i][j].z,
                                             papaGeo[i][j].rz, papaGeo[i][j].ry);
            }
        }
    }
    GgafDxDrawableActor* pActor_Shot = nullptr;
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
                if (paUint32_dotmat[i] & GgafDxUtil::BITNUM[prm_way_M-j]) {
                    if (prm_paUint32_dotmat1 && (prm_paUint32_dotmat1[i] & GgafDxUtil::BITNUM[prm_way_M-j])) {
                        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot1->dispatch(n*prm_interval_frames+1);
                        depo_no = 1;
                    } else if (prm_paUint32_dotmat2 && (prm_paUint32_dotmat2[i] & GgafDxUtil::BITNUM[prm_way_M-j])) {
                        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot2->dispatch(n*prm_interval_frames+1);
                        depo_no = 2;
                    } else if (prm_paUint32_dotmat3 && (prm_paUint32_dotmat3[i] & GgafDxUtil::BITNUM[prm_way_M-j])) {
                        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot3->dispatch(n*prm_interval_frames+1);
                        depo_no = 3;
                    } else {
                        pActor_Shot = nullptr;
                        depo_no = 0;
                    }
                } else {
                    pActor_Shot = nullptr;
                    depo_no = 0;
                }
                if (pActor_Shot) {
                    dispatch_num++;
                    pActor_Shot->position(prm_x + papaGeo[i][j].x,
                                          prm_y + papaGeo[i][j].y,
                                          prm_z + papaGeo[i][j].z);
                    pActor_Shot->_pKurokoA->setRzRyMvAng(papaGeo[i][j].rz, papaGeo[i][j].ry);
                    pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                    pActor_Shot->_pKurokoA->setMvAcce(now_acce);
                    if (pFunc_CallBackDispatched) {
                        pFunc_CallBackDispatched(pActor_Shot, dispatch_num, n, depo_no, i, j);
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
        GGAF_DELETEARR(papaGeo[i]);
    }
    GGAF_DELETEARR(papaGeo);

    return pActor_Shot;
}


GgafDxDrawableActor* StgUtil::shotWay003(GgafDxGeometricActor* prm_pFrom,
                                         GgafActorDepository* prm_pDepo_Shot1, uint32_t* prm_paUint32_dotmat1,
                                         GgafActorDepository* prm_pDepo_Shot2, uint32_t* prm_paUint32_dotmat2,
                                         GgafActorDepository* prm_pDepo_Shot3, uint32_t* prm_paUint32_dotmat3,
                                         coord prm_r,
                                         int prm_way_N, int prm_way_M,
                                         angle prm_angClearance_N, angle prm_angClearance_M,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int, int, int, int)) {
    return shotWay003(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_Shot1, prm_paUint32_dotmat1,
                      prm_pDepo_Shot2, prm_paUint32_dotmat2,
                      prm_pDepo_Shot3, prm_paUint32_dotmat3,
                      prm_r,
                      prm_way_N, prm_way_M,
                      prm_angClearance_N, prm_angClearance_M,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_CallBackDispatched);
}


GgafDxDrawableActor* StgUtil::shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                         angle prm_rz, angle prm_ry,
                                         GgafActorDepository* prm_pDepo_Shot,
                                         coord prm_r,
                                         int prm_way, angle prm_expanse_angle,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int, int)) {
    angle* paAng_way = NEW angle[prm_way];
    GgafDxUtil::getRadialAngle2D(0, prm_way, paAng_way);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way];
    angle expanse_rz = (D180ANG - prm_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RzRy(GgafDxUtil::simplifyAng(prm_rz-D90ANG),prm_ry, matWorldRot);

    float vx, vy, vz;
    coord x,y,z;
    for (int i = 0; i < prm_way; i++) {
        GgafDxUtil::convRzRyToVector(expanse_rz, paAng_way[i], vx, vy, vz);
        x = vx * prm_r;
        y = vy * prm_r;
        z = vz * prm_r;
        paGeo[i].x = x*matWorldRot._11 + y*matWorldRot._21 + z*matWorldRot._31;
        paGeo[i].y = x*matWorldRot._12 + y*matWorldRot._22 + z*matWorldRot._32;
        paGeo[i].z = x*matWorldRot._13 + y*matWorldRot._23 + z*matWorldRot._33;
        GgafDxUtil::convVectorToRzRy(paGeo[i].x , paGeo[i].y, paGeo[i].z,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxDrawableActor* pActor_Shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch(n*prm_interval_frames+1);
            if (pActor_Shot) {
                dispatch_num++;
                pActor_Shot->position(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_Shot->_pKurokoA->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Z] = Rz;
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Y] = Ry;
                if (pFunc_CallBackDispatched) {
                    pFunc_CallBackDispatched(pActor_Shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way);
    GGAF_DELETEARR(paGeo);
    return pActor_Shot;
}

GgafDxDrawableActor* StgUtil::shotWay004(GgafDxGeometricActor* prm_pFrom,
                                         GgafActorDepository* prm_pDepo_Shot,
                                         coord prm_r,
                                         int prm_way, angle prm_expanse_angle,
                                         velo prm_velo_first, acce prm_acce,
                                         int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                         void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int, int)) {
    return shotWay004(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_Shot,
                      prm_r,
                      prm_way, prm_expanse_angle,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_CallBackDispatched);
}

GgafDxDrawableActor* StgUtil::shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                               angle prm_rz, angle prm_ry,
                                               GgafActorDepository* prm_pDepo_Shot,
                                               coord prm_r,
                                               int prm_way_num,
                                               angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                               velo prm_velo_first, acce prm_acce,
                                               int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                               void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int, int)) {
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way_num];
    angle expanse_rz = (D180ANG - prm_first_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RzRy(GgafDxUtil::simplifyAng(prm_rz-D90ANG),prm_ry, matWorldRot);

    float vx, vy, vz;
    coord x,y,z;
    for (int i = 0; i < prm_way_num; i++) {
        GgafDxUtil::convRzRyToVector(expanse_rz, GOLDEN_ANG[i], vx, vy, vz);
        x = vx * prm_r;
        y = vy * prm_r;
        z = vz * prm_r;
        paGeo[i].x = x*matWorldRot._11 + y*matWorldRot._21 + z*matWorldRot._31;
        paGeo[i].y = x*matWorldRot._12 + y*matWorldRot._22 + z*matWorldRot._32;
        paGeo[i].z = x*matWorldRot._13 + y*matWorldRot._23 + z*matWorldRot._33;
        GgafDxUtil::convVectorToRzRy(paGeo[i].x , paGeo[i].y, paGeo[i].z,
                                     paGeo[i].rz, paGeo[i].ry);
        expanse_rz -= (prm_inc_expanse_angle/2);
    }
    GgafDxDrawableActor* pActor_Shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_num; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch(n*prm_interval_frames+1);
            if (pActor_Shot) {
                dispatch_num++;
                pActor_Shot->position(prm_x + paGeo[i].x,
                                      prm_y + paGeo[i].y,
                                      prm_z + paGeo[i].z);
                pActor_Shot->_pKurokoA->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Z] = Rz;
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Y] = Ry;
                if (pFunc_CallBackDispatched) {
                    pFunc_CallBackDispatched(pActor_Shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paGeo);
    return pActor_Shot;
}

GgafDxDrawableActor* StgUtil::shotWayGoldenAng(GgafDxGeometricActor* prm_pFrom,
                                               GgafActorDepository* prm_pDepo_Shot,
                                               coord prm_r,
                                               int prm_way_num,
                                               angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                               velo prm_velo_first, acce prm_acce,
                                               int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                               void (*pFunc_CallBackDispatched)(GgafDxDrawableActor*, int, int, int)) {
    return shotWayGoldenAng(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                            prm_pFrom->_rz, prm_pFrom->_ry,
                            prm_pDepo_Shot,
                            prm_r,
                            prm_way_num,
                            prm_first_expanse_angle, prm_inc_expanse_angle,
                            prm_velo_first, prm_acce,
                            prm_set_num, prm_interval_frames, prm_attenuated,
                            pFunc_CallBackDispatched);
}
