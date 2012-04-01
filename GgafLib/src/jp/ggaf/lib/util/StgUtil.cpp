#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


void StgUtil::shotWay001(GgafDxGeometricActor* prm_pFrom,
                         GgafActorDepository* prm_pDepo_Shot,
                         GgafDxGeometricActor* prm_pTarget,
                         int prm_way, angle prm_angClearance,
                         velo prm_velo, acce prm_acce) {
    angle* paAng_way = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                           prm_pTarget->_Y - prm_pFrom->_Y,
                           prm_pTarget->_Z - prm_pFrom->_Z,
                           rz, ry);
    GgafDxUtil::getWayAngle2D(0,prm_way, prm_angClearance, paAng_way);
    GgafDxDrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
        if (pActor_Shot) {
            pActor_Shot->locatedBy(prm_pFrom);
            pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAng_way[i], ry);
            pActor_Shot->_pKurokoA->setMvVelo(prm_velo);
            pActor_Shot->_pKurokoA->setMvAcce(prm_acce);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAng_way);
}

void StgUtil::shotWay001v2(GgafDxGeometricActor* prm_pFrom,
                           GgafActorDepository*    prm_pDepo_Shot,
                           GgafDxGeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo_first, acce prm_acce_first,
                           int prm_set_num, float prm_attenuated) {
    angle* paAng_way = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDxUtil::getWayAngle2D(0,prm_way, prm_angClearance, paAng_way);
    GgafDxDrawableActor* pActor_Shot;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce_first;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
            if (pActor_Shot) {
                pActor_Shot->locatedBy(prm_pFrom);
                pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAng_way[i], ry);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAng_way);
}

void StgUtil::shotWay002(GgafDxGeometricActor* prm_pFrom,
                         GgafActorDepository*     prm_pDepo_Shot,
                         GgafDxGeometricActor* prm_pTarget,
                         int prm_way, angle prm_angBegin,
                         velo prm_velo, acce prm_acce) {
    angle* paAng_way = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDxUtil::getRadialAngle2D(prm_angBegin, prm_way, paAng_way);
    GgafDxDrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
        if (pActor_Shot) {
            pActor_Shot->locatedBy(prm_pFrom);
            pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAng_way[i], ry+D90ANG);
            pActor_Shot->_pKurokoA->setMvVelo(prm_velo);
            pActor_Shot->_pKurokoA->setMvAcce(prm_acce);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAng_way);
}
void StgUtil::shotWay002v2(GgafDxGeometricActor* prm_pFrom,
                           GgafActorDepository*     prm_pDepo_Shot,
                           GgafDxGeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo_first, acce prm_acce_first,
                           int prm_set_num, float prm_attenuated) {
    angle* paAng_way = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                           prm_pTarget->_Y - prm_pFrom->_Y,
                           prm_pTarget->_Z - prm_pFrom->_Z,
                           rz, ry);
    GgafDxUtil::getRadialAngle2D(prm_angBegin, prm_way, paAng_way);
    GgafDxDrawableActor* pActor_Shot;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce_first;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
            if (pActor_Shot) {
                pActor_Shot->locatedBy(prm_pFrom);
                pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAng_way[i], ry+D90ANG);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAng_way);
}



void StgUtil::shotWay003(GgafDxGeometricActor* prm_pFrom,
                         GgafActorDepository* prm_pDepo_Shot,
                         coord prm_r,
                         int prm_way_N, int prm_way_M,
                         angle prm_angClearance_N, angle prm_angClearance_M,
                         velo prm_velo_first, acce prm_acce_first,
                         int prm_set_num, frame prm_interval_frames, float prm_attenuated) {
    angle* paAng_way_N = NEW angle[prm_way_N];
    angle* paAng_way_M = NEW angle[prm_way_M];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_angClearance_N, paAng_way_N);
    GgafDxUtil::getWayAngle2D(0, prm_way_M, prm_angClearance_M, paAng_way_M);
    GgafDxGeoElem** papaGeo = NEW GgafDxGeoElem*[prm_way_N];
    float vx, vy, vz;
    angle Rz,Ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_pFrom, matWorldRot);
    coord X,Y,Z;
    for (int i = 0; i < prm_way_N; i++) {
        Rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        papaGeo[i] = NEW GgafDxGeoElem[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            Ry = GgafDxUtil::simplifyAng(paAng_way_M[j]);
            GgafDxUtil::getNormalizeVectorZY(Rz, Ry, vx, vy, vz);
            X = vx * prm_r;
            Y = vy * prm_r;
            Z = vz * prm_r;
            papaGeo[i][j]._X = X*matWorldRot._11 + Y*matWorldRot._21 + Z*matWorldRot._31;
            papaGeo[i][j]._Y = X*matWorldRot._12 + Y*matWorldRot._22 + Z*matWorldRot._32;
            papaGeo[i][j]._Z = X*matWorldRot._13 + Y*matWorldRot._23 + Z*matWorldRot._33;
            GgafDxUtil::getRzRyAng(papaGeo[i][j]._X , papaGeo[i][j]._Y, papaGeo[i][j]._Z,
                                   papaGeo[i][j]._RZ, papaGeo[i][j]._RY);
        }
    }
    GgafDxDrawableActor* pActor_Shot;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce_first;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            for (int j = 0; j < prm_way_M; j++) {
                pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch(n*prm_interval_frames+1);
                if (pActor_Shot) {
                    pActor_Shot->locate(prm_pFrom->_X + papaGeo[i][j]._X,
                                        prm_pFrom->_Y + papaGeo[i][j]._Y,
                                        prm_pFrom->_Z + papaGeo[i][j]._Z);
                    pActor_Shot->_pKurokoA->setRzRyMvAng(papaGeo[i][j]._RZ, papaGeo[i][j]._RY);
                    pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                    pActor_Shot->_pKurokoA->setMvAcce(now_acce);
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Z] = Rz;
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Y] = Ry;
                }
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }

    DELETEARR_IMPOSSIBLE_NULL(paAng_way_N);
    DELETEARR_IMPOSSIBLE_NULL(paAng_way_M);
    for (int i = 0; i < prm_way_N; i++) {
        DELETEARR_IMPOSSIBLE_NULL(papaGeo[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(papaGeo);
}

void StgUtil::shotWay004(GgafDxGeometricActor* prm_pFrom,
                         GgafActorDepository* prm_pDepo_Shot,
                         coord prm_r,
                         int prm_way, angle prm_expanse_angle,
                         velo prm_velo_first, acce prm_acce_first,
                         int prm_set_num, frame prm_interval_frames, float prm_attenuated) {
    angle* paAng_way = NEW angle[prm_way];
    GgafDxUtil::getRadialAngle2D(0, prm_way, paAng_way);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way];
    angle expanse_rz = (D180ANG - prm_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    angle org_RZ = prm_pFrom->_RZ;
    prm_pFrom->_RZ = GgafDxUtil::simplifyAng(org_RZ-D90ANG);
    GgafDxUtil::setWorldMatrix_RzRy(prm_pFrom, matWorldRot);
    prm_pFrom->_RZ = org_RZ;

    float vx, vy, vz;
    coord X,Y,Z;
    for (int i = 0; i < prm_way; i++) {
        GgafDxUtil::getNormalizeVectorZY(expanse_rz, paAng_way[i], vx, vy, vz);
        X = vx * prm_r;
        Y = vy * prm_r;
        Z = vz * prm_r;
        paGeo[i]._X = X*matWorldRot._11 + Y*matWorldRot._21 + Z*matWorldRot._31;
        paGeo[i]._Y = X*matWorldRot._12 + Y*matWorldRot._22 + Z*matWorldRot._32;
        paGeo[i]._Z = X*matWorldRot._13 + Y*matWorldRot._23 + Z*matWorldRot._33;
        GgafDxUtil::getRzRyAng(paGeo[i]._X , paGeo[i]._Y, paGeo[i]._Z,
                               paGeo[i]._RZ, paGeo[i]._RY);
    }
    GgafDxDrawableActor* pActor_Shot;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce_first;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch(n*prm_interval_frames+1);
            if (pActor_Shot) {
                pActor_Shot->locate(prm_pFrom->_X + paGeo[i]._X,
                                    prm_pFrom->_Y + paGeo[i]._Y,
                                    prm_pFrom->_Z + paGeo[i]._Z);
                pActor_Shot->_pKurokoA->setRzRyMvAng(paGeo[i]._RZ, paGeo[i]._RY);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Z] = Rz;
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Y] = Ry;
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAng_way);
    DELETEARR_IMPOSSIBLE_NULL(paGeo);
}
