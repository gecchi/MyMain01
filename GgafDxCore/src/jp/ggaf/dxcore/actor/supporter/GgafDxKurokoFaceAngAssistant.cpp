#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"

#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoFaceAngAssistant::GgafDxKurokoFaceAngAssistant(GgafDxKuroko* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    for (int ax = 0; ax < 3; ax++) {
        _smthFaceAng[ax]._t_velo = _pMaster->_angvelo_face[ax];
        _smthFaceAng[ax]._t_acce = _pMaster->_angacce_face[ax];
    }
}

void GgafDxKurokoFaceAngAssistant::behave() {
    for (int ax = 0; ax < 3; ax++) {
        if (_smthFaceAng[ax].isAccelerating()) {
            _smthFaceAng[ax].behave();
            _pMaster->setFaceAngVelo(ax, _smthFaceAng[ax]._t_velo - _smthFaceAng[ax]._t_acce); //こうしないと黒衣のbehaveで２回_acce足し込まれるし
            _pMaster->setFaceAngAcce(ax, _smthFaceAng[ax]._t_acce);
        }
    }
}

void GgafDxKurokoFaceAngAssistant::turnFaceAngByDt(axis prm_axis,
                                             angle prm_distance, int prm_target_frames,
                                             float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                             bool prm_zero_acc_end_flg ) {
    _smthFaceAng[prm_axis]._t_value = 0;
    _smthFaceAng[prm_axis]._t_velo = _pMaster->_angvelo_face[prm_axis];
    _smthFaceAng[prm_axis]._t_acce = _pMaster->_angacce_face[prm_axis];
    _smthFaceAng[prm_axis].accelerateByDt(prm_distance, prm_target_frames,
                                          prm_p1,prm_p2,prm_end_angvelo,
                                          prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::turnByVd(axis prm_axis,
                                             angvelo prm_top_angvelo, angle prm_distance,
                                             float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                             bool prm_zero_acc_end_flg) {
    _smthFaceAng[prm_axis]._t_value = 0;
    _smthFaceAng[prm_axis]._t_velo = _pMaster->_angvelo_face[prm_axis];
    _smthFaceAng[prm_axis]._t_acce = _pMaster->_angacce_face[prm_axis];
    _smthFaceAng[prm_axis].accelerateByVd(prm_top_angvelo, prm_distance,
                                          prm_p1,prm_p2, prm_end_angvelo,
                                          prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::turnRzFaceAngByDtTo(angle prm_rz_target, int prm_way, int prm_target_frames,
                                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                                 bool prm_zero_acc_end_flg) {
    angle distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way);
    turnFaceAngByDt(AXIS_Z,
                    distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::turnRyFaceAngByDtTo(angle prm_ry_target, int prm_way, int prm_target_frames,
                                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                                 bool prm_zero_acc_end_flg) {
    angle distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way);
    turnFaceAngByDt(AXIS_Y,
                    distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::rollFaceAngByDtTo(angle prm_ang_rx_target, int prm_way, int prm_target_frames,
                                               float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                               bool prm_zero_acc_end_flg) {
    angle distance = _pMaster->getFaceAngDistance(AXIS_X, prm_ang_rx_target, prm_way);
    turnFaceAngByDt(AXIS_X,
                    distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::turnRzRyFaceAngByDtTo(
                                 angle prm_rz_target, angle prm_ry_target, int prm_way, bool prm_optimize_ang,
                                 int prm_target_frames,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    angle out_rz_distance;
    angle out_ry_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyFaceAngDistanceTwd(prm_rz_target, prm_ry_target, prm_way,
                                            out_rz_distance, out_ry_distance);
    } else {
        out_rz_distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way);
        out_ry_distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way);
    }

    turnFaceAngByDt(AXIS_Z,
                    out_rz_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
    turnFaceAngByDt(AXIS_Y,
                    out_ry_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::turnFaceAngByDtTwd(
                                 coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
                                 int prm_target_frames,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    coord vx = prm_tx - _pMaster->_pActor->_x;
    coord vy = prm_ty - _pMaster->_pActor->_y;
    coord vz = prm_tz - _pMaster->_pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない
    } else {
        angle out_rz_Target;
        angle out_ry_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_rz_Target,
                               out_ry_Target);
        turnRzRyFaceAngByDtTo(
                out_rz_Target, out_ry_Target, prm_way, prm_optimize_ang,
                prm_target_frames,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_zero_acc_end_flg);
    }
}

void GgafDxKurokoFaceAngAssistant::turnFaceAngByDtTwd(
                                 GgafDxGeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
                                 int prm_target_frames,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    turnFaceAngByDtTwd(
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_target_frames,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_zero_acc_end_flg);
}


void GgafDxKurokoFaceAngAssistant::turnRzByVdTo(
        angvelo prm_top_angvelo, angle prm_rz_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
        angle distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way);
        turnByVd(AXIS_Z,
                        prm_top_angvelo, distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::turnRyByVdTo(
        angvelo prm_top_angvelo, angle prm_ry_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
        angle distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way);
        turnByVd(AXIS_Y,
                        prm_top_angvelo, distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::rollByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_rx_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
        angle distance = _pMaster->getFaceAngDistance(AXIS_X, prm_ang_rx_target, prm_way);
        turnByVd(AXIS_X,
                        prm_top_angvelo, distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
}

void GgafDxKurokoFaceAngAssistant::turnRzRyByVdTo(
                                 angvelo prm_top_angvelo,
                                 angle prm_rz_target, angle prm_ry_target, int prm_way, bool prm_optimize_ang,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    angle out_rz_distance;
    angle out_ry_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyFaceAngDistanceTwd(prm_rz_target, prm_ry_target, prm_way,
                                  out_rz_distance, out_ry_distance);
    } else {
        out_rz_distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way);
        out_ry_distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way);
    }
    double drz = ABS(out_rz_distance);
    double dry = ABS(out_ry_distance);
    if (drz > dry) {
        double drr = dry / drz;
        turnByVd(AXIS_Z,
                        prm_top_angvelo, out_rz_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnByVd(AXIS_Y,
                        prm_top_angvelo*drr, out_ry_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    } else if (drz < dry) {
        double drr = drz / dry;
        turnByVd(AXIS_Z,
                        prm_top_angvelo*drr, out_rz_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnByVd(AXIS_Y,
                        prm_top_angvelo, out_ry_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    } else {
        turnByVd(AXIS_Z,
                        prm_top_angvelo, out_rz_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnByVd(AXIS_Y,
                        prm_top_angvelo, out_ry_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    }
}

void GgafDxKurokoFaceAngAssistant::turnByVdTwd(
                                 angvelo prm_top_angvelo,
                                 coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    coord vx = prm_tx - _pMaster->_pActor->_x;
    coord vy = prm_ty - _pMaster->_pActor->_y;
    coord vz = prm_tz - _pMaster->_pActor->_z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //アクターの座標に等しいので、何もしない
    } else {
        angle out_rz_Target;
        angle out_ry_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_rz_Target,
                               out_ry_Target);
        turnRzRyByVdTo(
                prm_top_angvelo,
                out_rz_Target, out_ry_Target, prm_way, prm_optimize_ang,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_zero_acc_end_flg);
    }
}

void GgafDxKurokoFaceAngAssistant::turnByVdTwd(
                                 angvelo prm_top_angvelo,
                                 GgafDxGeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    turnByVdTwd(
            prm_top_angvelo,
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_zero_acc_end_flg);
}

GgafDxKurokoFaceAngAssistant::~GgafDxKurokoFaceAngAssistant() {
}


