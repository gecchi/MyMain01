#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


boolean StgUtil::isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
                       GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppABB) {

    //������v���Ȃ��m�����������ȏ���(Z>Y>X)�ɔ���
    if (pActor->_Z + pAAB->_z2 >= pOppActor->_Z + pOppABB->_z1) {
        if (pActor->_Z + pAAB->_z1 <= pOppActor->_Z + pOppABB->_z2) {
            if (pActor->_Y + pAAB->_y2 >= pOppActor->_Y + pOppABB->_y1) {
                if (pActor->_Y + pAAB->_y1 <= pOppActor->_Y + pOppABB->_y2) {
                    if (pActor->_X + pAAB->_x2 >= pOppActor->_X + pOppABB->_x1) {
                        if (pActor->_X + pAAB->_x1 <= pOppActor->_X + pOppABB->_x2) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

boolean StgUtil::isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
                     GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere) {
    //���� �� ����
    //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
    //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
    if (
        (double)((pOppActor->_X+pOppSphere->_x) - (pActor->_X+pSphere->_x)) * ((pOppActor->_X+pOppSphere->_x) - (pActor->_X+pSphere->_x)) +
        (double)((pOppActor->_Y+pOppSphere->_y) - (pActor->_Y+pSphere->_y)) * ((pOppActor->_Y+pOppSphere->_y) - (pActor->_Y+pSphere->_y)) +
        (double)((pOppActor->_Z+pOppSphere->_z) - (pActor->_Z+pSphere->_z)) * ((pOppActor->_Z+pOppSphere->_z) - (pActor->_Z+pSphere->_z))
          <=
        (double)(pOppSphere->_r + pSphere->_r) * (pOppSphere->_r + pSphere->_r)
    ) {
        return true;
    } else {
        return false;
    }
}

boolean StgUtil::isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
                       GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere) {
    //��AAB �� ����
    int o_scx =  pOppActor->_X+pOppSphere->_cx;
    int o_scy =  pOppActor->_Y+pOppSphere->_cy;
    int o_scz =  pOppActor->_Z+pOppSphere->_cz;
    int bx1 = pActor->_X+pAAB->_x1;
    int bx2 = pActor->_X+pAAB->_x2;
    int by1 = pActor->_Y+pAAB->_y1;
    int by2 = pActor->_Y+pAAB->_y2;
    int bz1 = pActor->_Z+pAAB->_z1;
    int bz2 = pActor->_Z+pAAB->_z2;
    double square_length = 0; //���̒��S��AAB�̍ŒZ�������悵���l
    if(o_scx < bx1) {
        square_length += (double)(o_scx - bx1) * (o_scx - bx1);
    }
    if(o_scx > bx2) {
        square_length += (double)(o_scx - bx2) * (o_scx - bx2);
    }
    if(o_scy < by1) {
        square_length += (double)(o_scy - by1) * (o_scy - by1);
    }
    if(o_scy > by2) {
        square_length += (double)(o_scy - by2) * (o_scy - by2);
    }
    if(o_scz < bz1) {
        square_length += (double)(o_scz - bz1) * (o_scz - bz1);
    }
    if(o_scz > bz2) {
        square_length += (double)(o_scz - bz2) * (o_scz - bz2);
    }
    //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
    if (square_length <= (double)pOppSphere->_r * pOppSphere->_r) {
        return true;
    } else {
        return false;
    }


}
void StgUtil::shotWay001(GgafDx9GeometricActor* prm_pFrom,
                       GgafActorDispatcher* prm_pDispatcher_Shot,
                       GgafDx9GeometricActor* prm_pTarget,
                       int prm_way, angle prm_angClearance,
                       velo prm_velo, acce prm_acce) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getWayAngle2D(0,prm_way, prm_angClearance, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
        if (pActor_Shot) {
            pActor_Shot->setCoordinateBy(prm_pFrom);
            pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry);
            pActor_Shot->_pMover->setMvVelo(prm_velo);
            pActor_Shot->_pMover->setMvAcce(prm_acce);
            pActor_Shot->activate();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}

void StgUtil::shotWay001v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*     prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo_top, acce prm_acce_top,
                           int prm_num, float prm_attenuated) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getWayAngle2D(0,prm_way, prm_angClearance, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    velo now_velo = prm_velo_top;
    acce now_acce = prm_acce_top;
    for (int n = 0; n < prm_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
            if (pActor_Shot) {
                pActor_Shot->setCoordinateBy(prm_pFrom);
                pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry);
                pActor_Shot->_pMover->setMvVelo(now_velo);
                pActor_Shot->_pMover->setMvAcce(now_acce);
                pActor_Shot->activate();
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}

void StgUtil::shotWay002(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                        GgafCore::GgafActorDispatcher*     prm_pDispatcher_Shot,
                        GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                        int prm_way, angle prm_angBegin,
                        velo prm_velo, acce prm_acce) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getRadialAngle2D(prm_angBegin, prm_way, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    for (int i = 0; i < prm_way; i++) {
        pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
        if (pActor_Shot) {
            pActor_Shot->setCoordinateBy(prm_pFrom);
            pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry+ANGLE90);
            pActor_Shot->_pMover->setMvVelo(prm_velo);
            pActor_Shot->_pMover->setMvAcce(prm_acce);
            pActor_Shot->activate();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}
void StgUtil::shotWay002v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*     prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo_top, acce prm_acce_top,
                           int prm_num, float prm_attenuated) {
    angle* paAngWay = NEW angle[prm_way];
    angle rz,ry;
    GgafDx9Util::getRzRyAng(prm_pTarget->_X - prm_pFrom->_X,
                            prm_pTarget->_Y - prm_pFrom->_Y,
                            prm_pTarget->_Z - prm_pFrom->_Z,
                            rz, ry);
    GgafDx9Util::getRadialAngle2D(prm_angBegin, prm_way, paAngWay);
    GgafDx9DrawableActor* pActor_Shot;
    velo now_velo = prm_velo_top;
    acce now_acce = prm_acce_top;
    for (int n = 0; n < prm_num; n++) {
        for (int i = 0; i < prm_way; i++) {
            pActor_Shot = (GgafDx9DrawableActor*)prm_pDispatcher_Shot->employ();
            if (pActor_Shot) {
                pActor_Shot->setCoordinateBy(prm_pFrom);
                pActor_Shot->_pMover->setRzRyMvAng(rz+paAngWay[i], ry+ANGLE90);
                pActor_Shot->_pMover->setMvVelo(now_velo);
                pActor_Shot->_pMover->setMvAcce(now_acce);
                pActor_Shot->activate();
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}
