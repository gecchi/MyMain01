#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"


using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoAssistantB::GgafDxKurokoAssistantB(GgafDxKuroko* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    for (int ax = 0; ax < 3; ax++) {
        _smthFaceAng[ax]._velo = _pMaster->_angvelo_face[ax];
        _smthFaceAng[ax]._acce = _pMaster->_angacce_face[ax];
    }
}

void GgafDxKurokoAssistantB::behave() {
    for (int ax = 0; ax < 3; ax++) {
        bool flg = _smthFaceAng[ax]._prm._flg;
        _smthFaceAng[ax].behave();
        if (flg) {
            _pMaster->setFaceAngVelo(ax, _smthFaceAng[ax]._velo - _smthFaceAng[ax]._acce); //こうしないと黒衣のbehaveで２回_acce足し込まれるし
            _pMaster->setFaceAngAcce(ax, _smthFaceAng[ax]._acce);
        }
    }
}

void GgafDxKurokoAssistantB::turnFaceAngByDt(
                        axis prm_axis,
                        angle prm_angular_distance, int prm_target_frames,
                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                        bool prm_endacc_flg ) {

    _smthFaceAng[prm_axis]._value = 0;
    _smthFaceAng[prm_axis]._velo = _pMaster->_angvelo_face[prm_axis];
    _smthFaceAng[prm_axis]._acce = _pMaster->_angacce_face[prm_axis];
    _smthFaceAng[prm_axis].accelerateByDt(prm_angular_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_angvelo,
                           prm_endacc_flg);
}

void GgafDxKurokoAssistantB::turnFaceAngByVd(
        axis prm_axis,
        angvelo prm_top_angvelo, angle prm_angular_distance,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    _smthFaceAng[prm_axis]._value = 0;
    _smthFaceAng[prm_axis]._velo = _pMaster->_angvelo_face[prm_axis];
    _smthFaceAng[prm_axis]._acce = _pMaster->_angacce_face[prm_axis];
    _smthFaceAng[prm_axis].accelerateByVd(prm_top_angvelo, prm_angular_distance,
                           prm_p1,prm_p2, prm_end_angvelo,
                           prm_endacc_flg);
}




void GgafDxKurokoAssistantB::turnRzFaceAngByDtTo(angle prm_ang_rz_target, int prm_way, int prm_target_frames,
                                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                        bool prm_endacc_flg) {
    angle angular_distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way);
    turnFaceAngByDt(AXIS_Z,
                    angular_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_endacc_flg);
}
void GgafDxKurokoAssistantB::turnRyFaceAngByDtTo(angle prm_ang_ry_target, int prm_way, int prm_target_frames,
                                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                        bool prm_endacc_flg) {
    angle angular_distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way);
    turnFaceAngByDt(AXIS_Y,
                    angular_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_endacc_flg);
}

void GgafDxKurokoAssistantB::rollFaceAngByDtTo(angle prm_ang_rx_target, int prm_way, int prm_target_frames,
                                                float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                                bool prm_endacc_flg) {
    angle angular_distance = _pMaster->getFaceAngDistance(AXIS_X, prm_ang_rx_target, prm_way);
    turnFaceAngByDt(AXIS_X,
                    angular_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_endacc_flg);
}

void GgafDxKurokoAssistantB::turnRzRyFaceAngByDtTo(
        angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
        int prm_target_frames,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {

    angle out_rz_angular_distance;
    angle out_ry_angular_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyFaceAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target, prm_way,
                                  out_rz_angular_distance, out_ry_angular_distance);
    } else {
        out_rz_angular_distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way);
        out_ry_angular_distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way);
    }

    turnFaceAngByDt(AXIS_Z,
                    out_rz_angular_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_endacc_flg);
    turnFaceAngByDt(AXIS_Y,
                    out_ry_angular_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_endacc_flg);
}

void GgafDxKurokoAssistantB::turnFaceAngByDtTwd(
        coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
        int prm_target_frames,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {

    coord vx = prm_tx - _pMaster->_pActor->_x;
    coord vy = prm_ty - _pMaster->_pActor->_y;
    coord vz = prm_tz - _pMaster->_pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない
    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target,
                               out_angRy_Target);
        turnRzRyFaceAngByDtTo(
                out_angRz_Target, out_angRy_Target, prm_way, prm_optimize_ang,
                prm_target_frames,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_endacc_flg);
    }
}

void GgafDxKurokoAssistantB::turnFaceAngByDtTwd(
                    GgafDxGeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
                    int prm_target_frames,
                    float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                    bool prm_endacc_flg) {
    turnFaceAngByDtTwd(
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_target_frames,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_endacc_flg);
}


void GgafDxKurokoAssistantB::turnRzFaceAngByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_rz_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
        angle angular_distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way);
        turnFaceAngByVd(
                AXIS_Z,
                prm_top_angvelo, angular_distance,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_endacc_flg);
}

void GgafDxKurokoAssistantB::turnRyFaceAngByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_ry_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
        angle angular_distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way);
        turnFaceAngByVd(
                AXIS_Y,
                prm_top_angvelo, angular_distance,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_endacc_flg);
}

void GgafDxKurokoAssistantB::rollFaceAngByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_rx_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
        angle angular_distance = _pMaster->getFaceAngDistance(AXIS_X, prm_ang_rx_target, prm_way);
        turnFaceAngByVd(
                AXIS_X,
                prm_top_angvelo, angular_distance,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_endacc_flg);
}

void GgafDxKurokoAssistantB::turnRzRyFaceAngByVdTo(
        angvelo prm_top_angvelo,
        angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    angle out_rz_angular_distance;
    angle out_ry_angular_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyFaceAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target, prm_way,
                                  out_rz_angular_distance, out_ry_angular_distance);
    } else {
        out_rz_angular_distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_ang_rz_target, prm_way);
        out_ry_angular_distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ang_ry_target, prm_way);
    }
    double drz = ABS(out_rz_angular_distance);
    double dry = ABS(out_ry_angular_distance);
    if (drz > dry) {
        double drr = dry / drz;
        turnFaceAngByVd(AXIS_Z,
                        prm_top_angvelo, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
        turnFaceAngByVd(AXIS_Y,
                        prm_top_angvelo*drr, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
    } else if (drz < dry) {
        double drr = drz / dry;
        turnFaceAngByVd(AXIS_Z,
                        prm_top_angvelo*drr, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
        turnFaceAngByVd(AXIS_Y,
                        prm_top_angvelo, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
    } else {
        turnFaceAngByVd(AXIS_Z,
                        prm_top_angvelo, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
        turnFaceAngByVd(AXIS_Y,
                        prm_top_angvelo, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
    }
}

void GgafDxKurokoAssistantB::turnFaceAngByVdTwd(
        angvelo prm_top_angvelo,
        coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    coord vx = prm_tx - _pMaster->_pActor->_x;
    coord vy = prm_ty - _pMaster->_pActor->_y;
    coord vz = prm_tz - _pMaster->_pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない
    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target,
                               out_angRy_Target);
        turnRzRyFaceAngByVdTo(
                prm_top_angvelo,
                out_angRz_Target, out_angRy_Target, prm_way, prm_optimize_ang,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_endacc_flg);
    }
}

void GgafDxKurokoAssistantB::turnFaceAngByVdTwd(
        angvelo prm_top_angvelo,
        GgafDxGeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {

    turnFaceAngByVdTwd(
            prm_top_angvelo,
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_endacc_flg);
}

GgafDxKurokoAssistantB::~GgafDxKurokoAssistantB() {
}


