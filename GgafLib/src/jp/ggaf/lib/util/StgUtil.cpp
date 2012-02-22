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
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                           prm_pTarget->_Y - prm_pFrom->_Y,
                           prm_pTarget->_Z - prm_pFrom->_Z,
                           rz, ry);
    GgafDxUtil::getWayAngle2D(0,prm_way, prm_angClearance, paAngWay);
    GgafDxDrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
        if (pActor_Shot) {
            pActor_Shot->locateAs(prm_pFrom);
            pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAngWay[i], ry);
            pActor_Shot->_pKurokoA->setMvVelo(prm_velo);
            pActor_Shot->_pKurokoA->setMvAcce(prm_acce);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}

void StgUtil::shotWay001v2(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                           GgafCore::GgafActorDepository*     prm_pDepo_Shot,
                           GgafDxCore::GgafDxGeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo_top, acce prm_acce_top,
                           int prm_num, float prm_attenuated) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDxUtil::getWayAngle2D(0,prm_way, prm_angClearance, paAngWay);
    GgafDxDrawableActor* pActor_Shot;
    velo now_velo = prm_velo_top;
    acce now_acce = prm_acce_top;
    for (int n = 0; n < prm_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
            if (pActor_Shot) {
                pActor_Shot->locateAs(prm_pFrom);
                pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAngWay[i], ry);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}

void StgUtil::shotWay002(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                        GgafCore::GgafActorDepository*     prm_pDepo_Shot,
                        GgafDxCore::GgafDxGeometricActor* prm_pTarget,
                        int prm_way, angle prm_angBegin,
                        velo prm_velo, acce prm_acce) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDxUtil::getRadialAngle2D(prm_angBegin, prm_way, paAngWay);
    GgafDxDrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
        if (pActor_Shot) {
            pActor_Shot->locateAs(prm_pFrom);
            pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAngWay[i], ry+D90ANG);
            pActor_Shot->_pKurokoA->setMvVelo(prm_velo);
            pActor_Shot->_pKurokoA->setMvAcce(prm_acce);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}
void StgUtil::shotWay002v2(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                           GgafCore::GgafActorDepository*     prm_pDepo_Shot,
                           GgafDxCore::GgafDxGeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo_top, acce prm_acce_top,
                           int prm_num, float prm_attenuated) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDxUtil::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDxUtil::getRadialAngle2D(prm_angBegin, prm_way, paAngWay);
    GgafDxDrawableActor* pActor_Shot;
    velo now_velo = prm_velo_top;
    acce now_acce = prm_acce_top;
    for (int n = 0; n < prm_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
            if (pActor_Shot) {
                pActor_Shot->locateAs(prm_pFrom);
                pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAngWay[i], ry+D90ANG);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}


void StgUtil::shotWay003(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                         GgafCore::GgafActorDepository* prm_pDepo_Shot,
                         coord prm_r,
                         int prm_way_N, int prm_way_M,
                         angle prm_angClearance_N, angle prm_angClearance_M,
                         velo prm_velo, acce prm_acce) {
    //(Rz, Ry) = (0, 0) の方向でN*Mの初期位置、方向ベクトルを先ずは作る。
    angle* paAngWay_N = NEW angle[prm_way_N];
    angle* paAngWay_M = NEW angle[prm_way_M];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_angClearance_N, paAngWay_N);
    GgafDxUtil::getWayAngle2D(0, prm_way_M, prm_angClearance_M, paAngWay_M);
    angle Rz,Ry;
    float vx, vy, vz;
    Pos** papaPos = NEW Pos*[prm_way_N];
    for (int i = 0; i < prm_way_N; i++) {
        Rz = GgafDxUtil::simplifyAng(paAngWay_N[i]);
        papaPos[i] = NEW Pos[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            Ry = GgafDxUtil::simplifyAng(paAngWay_M[j]);
            GgafDxUtil::getNormalizeVectorZY(Rz, Ry, vx, vy, vz);
            papaPos[i][j].X = vx * prm_r;
            papaPos[i][j].Y = vy * prm_r;
            papaPos[i][j].Z = vz * prm_r;
        }
    }
    //(Rz, Ry) = (0, 0) の方向で初期位置完成、これを回転移動する
    GgafDxDrawableActor* pActor_Shot;
    Pos* p;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_pFrom, matWorldRot);
    int vX, vY, vZ;
    for (int i = 0; i < prm_way_N; i++) {
        for (int j = 0; j < prm_way_M; j++) {
            pActor_Shot = (GgafDxDrawableActor*)prm_pDepo_Shot->dispatch();
            if (pActor_Shot) {
                //向きを計算
                //ローカルでのショットの方向ベクトルを(_Xorg,_Yorg,_Zorg)、
                //ワールド変換行列の回転部分（matWorldRot)の成分を mat_xx、
                //最終的な方向ベクトルを(vX, vY, vZ) とすると
                //
                //                       | mat_11 mat_12 mat_13 |
                // | _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                //                       | mat_31 mat_32 mat_33 |
                //よって
                // vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                // vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                // vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                p = &(papaPos[i][j]);
                vX = p->X*matWorldRot._11 + p->Y*matWorldRot._21 + p->Z*matWorldRot._31;
                vY = p->X*matWorldRot._12 + p->Y*matWorldRot._22 + p->Z*matWorldRot._32;
                vZ = p->X*matWorldRot._13 + p->Y*matWorldRot._23 + p->Z*matWorldRot._33;
                GgafDxUtil::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                pActor_Shot->locate(prm_pFrom->_X+vX, prm_pFrom->_Y+vY, prm_pFrom->_Z+vZ);
                pActor_Shot->_pKurokoA->setRzRyMvAng(Rz, Ry);
                pActor_Shot->_pKurokoA->setMvVelo(prm_velo);
                pActor_Shot->_pKurokoA->setMvAcce(prm_acce);
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Z] = Rz;
//                pActor_Shot->_pKurokoA->_angFace[AXIS_Y] = Ry;
            }
        }
    }

}
