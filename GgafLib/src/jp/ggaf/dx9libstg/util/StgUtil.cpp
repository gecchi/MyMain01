#include "stdafx.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;




void StgUtil::shotWay001(GgafDx9GeometricActor* prm_pFrom,
                       GgafActorDepository* prm_pDepo_Shot,
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
        pActor_Shot = (GgafDx9DrawableActor*)prm_pDepo_Shot->dispatch();
        if (pActor_Shot) {
            pActor_Shot->locateAs(prm_pFrom);
            pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAngWay[i], ry);
            pActor_Shot->_pKurokoA->setMvVelo(prm_velo);
            pActor_Shot->_pKurokoA->setMvAcce(prm_acce);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}

void StgUtil::shotWay001v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDepository*     prm_pDepo_Shot,
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
            pActor_Shot = (GgafDx9DrawableActor*)prm_pDepo_Shot->dispatch();
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

void StgUtil::shotWay002(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                        GgafCore::GgafActorDepository*     prm_pDepo_Shot,
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
        pActor_Shot = (GgafDx9DrawableActor*)prm_pDepo_Shot->dispatch();
        if (pActor_Shot) {
            pActor_Shot->locateAs(prm_pFrom);
            pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAngWay[i], ry+ANGLE90);
            pActor_Shot->_pKurokoA->setMvVelo(prm_velo);
            pActor_Shot->_pKurokoA->setMvAcce(prm_acce);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}
void StgUtil::shotWay002v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDepository*     prm_pDepo_Shot,
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
            pActor_Shot = (GgafDx9DrawableActor*)prm_pDepo_Shot->dispatch();
            if (pActor_Shot) {
                pActor_Shot->locateAs(prm_pFrom);
                pActor_Shot->_pKurokoA->setRzRyMvAng(rz+paAngWay[i], ry+ANGLE90);
                pActor_Shot->_pKurokoA->setMvVelo(now_velo);
                pActor_Shot->_pKurokoA->setMvAcce(now_acce);
            }
        }
        now_velo *= prm_attenuated;
        now_acce *= prm_attenuated;
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);
}
