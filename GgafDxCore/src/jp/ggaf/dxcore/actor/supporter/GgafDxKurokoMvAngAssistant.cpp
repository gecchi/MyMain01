#include <jp/ggaf/dxcore/util/GgafDxUtil.h>
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAngAssistant.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"


using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoMvAngAssistant::GgafDxKurokoMvAngAssistant(GgafDxKuroko* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    _smthMvRzAng._t_velo = _pMaster->_angvelo_rz_mv;
    _smthMvRzAng._t_acce = _pMaster->_angacce_rz_mv;
    _smthMvRyAng._t_velo = _pMaster->_angvelo_ry_mv;
    _smthMvRyAng._t_acce = _pMaster->_angacce_ry_mv;
}

void GgafDxKurokoMvAngAssistant::behave() {
    if (_smthMvRzAng.isAccelerating()) {
        _smthMvRzAng.behave();
        _pMaster->setRzMvAngVelo(_smthMvRzAng._t_velo - _smthMvRzAng._t_acce); //こうしないと黒衣のbehaveで２回_acce足し込まれるし
        _pMaster->setRzMvAngAcce(_smthMvRzAng._t_acce);
    }
    if (_smthMvRyAng.isAccelerating()) {
        _smthMvRyAng.behave();
        _pMaster->setRyMvAngVelo(_smthMvRyAng._t_velo - _smthMvRyAng._t_acce); //こうしないと黒衣のbehaveで２回_acce足し込まれるし
        _pMaster->setRyMvAngAcce(_smthMvRyAng._t_acce);
    }
}

void GgafDxKurokoMvAngAssistant::turnRzByDt(
                        angle prm_angular_distance, int prm_target_frames,
                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                        bool prm_zero_acc_end_flg ) {

    _smthMvRzAng._t_value = 0;
    _smthMvRzAng._t_velo = _pMaster->_angvelo_rz_mv;
    _smthMvRzAng._t_acce = _pMaster->_angacce_rz_mv;
    _smthMvRzAng.accelerateByDt(prm_angular_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_angvelo,
                           prm_zero_acc_end_flg);
}
void GgafDxKurokoMvAngAssistant::turnRyByDt(
                        angle prm_angular_distance, int prm_target_frames,
                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                        bool prm_zero_acc_end_flg ) {

    _smthMvRyAng._t_value = 0;
    _smthMvRyAng._t_velo = _pMaster->_angvelo_ry_mv;
    _smthMvRyAng._t_acce = _pMaster->_angacce_ry_mv;
    _smthMvRyAng.accelerateByDt(prm_angular_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_angvelo,
                           prm_zero_acc_end_flg);
}

void GgafDxKurokoMvAngAssistant::turnRzByVd(
        angvelo prm_top_angvelo, angle prm_angular_distance,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
    _smthMvRzAng._t_value = 0;
    _smthMvRzAng._t_velo = _pMaster->_angvelo_rz_mv;
    _smthMvRzAng._t_acce = _pMaster->_angacce_rz_mv;
    _smthMvRzAng.accelerateByVd(prm_top_angvelo, prm_angular_distance,
                                prm_p1,prm_p2, prm_end_angvelo,
                                prm_zero_acc_end_flg);
}
void GgafDxKurokoMvAngAssistant::turnRyByVd(
        angvelo prm_top_angvelo, angle prm_angular_distance,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
    _smthMvRyAng._t_value = 0;
    _smthMvRyAng._t_velo = _pMaster->_angvelo_ry_mv;
    _smthMvRyAng._t_acce = _pMaster->_angacce_ry_mv;
    _smthMvRyAng.accelerateByVd(prm_top_angvelo, prm_angular_distance,
                                prm_p1,prm_p2, prm_end_angvelo,
                                prm_zero_acc_end_flg);
}


void GgafDxKurokoMvAngAssistant::turnRzByDtTo(angle prm_ang_rz_target, int prm_way, int prm_target_frames,
                                               float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                               bool prm_zero_acc_end_flg) {
    angle angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
    turnRzByDt(angular_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}
void GgafDxKurokoMvAngAssistant::turnRyByDtTo(angle prm_ang_ry_target, int prm_way, int prm_target_frames,
                                               float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                               bool prm_zero_acc_end_flg) {
    angle angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
    turnRyByDt(angular_distance, prm_target_frames,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void GgafDxKurokoMvAngAssistant::turnRzRyByDtTo(
        angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
        int prm_target_frames,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {

    angle out_rz_angular_distance;
    angle out_ry_angular_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyMvAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target, prm_way,
                                          out_rz_angular_distance, out_ry_angular_distance);
    } else {
        out_rz_angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
        out_ry_angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
    }

    turnRzByDt(out_rz_angular_distance, prm_target_frames,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    turnRyByDt(out_ry_angular_distance, prm_target_frames,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
}

void GgafDxKurokoMvAngAssistant::turnByDtTwd(
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
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target,
                               out_angRy_Target);
        turnRzRyByDtTo(
                out_angRz_Target, out_angRy_Target, prm_way, prm_optimize_ang,
                prm_target_frames,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_zero_acc_end_flg);
    }

}

void GgafDxKurokoMvAngAssistant::turnByDtTwd(
                    GgafDxGeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
                    int prm_target_frames,
                    float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                    bool prm_zero_acc_end_flg) {
    turnByDtTwd(
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_target_frames,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_zero_acc_end_flg);
}


void GgafDxKurokoMvAngAssistant::turnRzByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_rz_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
    angle angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
    turnRzByVd(prm_top_angvelo, angular_distance,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void GgafDxKurokoMvAngAssistant::turnRyByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_ry_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
    angle angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
    turnRyByVd(prm_top_angvelo, angular_distance,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void GgafDxKurokoMvAngAssistant::turnRzRyByVdTo(
        angvelo prm_top_angvelo,
        angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
    angle out_rz_angular_distance;
    angle out_ry_angular_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyMvAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target, prm_way,
                                         out_rz_angular_distance, out_ry_angular_distance);
    } else {
        out_rz_angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
        out_ry_angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
    }
    double drz = ABS(out_rz_angular_distance);
    double dry = ABS(out_ry_angular_distance);
    if (drz > dry) {
        double drr = dry / drz;
        turnRzByVd(prm_top_angvelo, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnRyByVd(prm_top_angvelo*drr, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    } else if (drz < dry) {
        double drr = drz / dry;
        turnRzByVd(prm_top_angvelo*drr, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnRyByVd(prm_top_angvelo, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    } else {
        turnRzByVd(prm_top_angvelo, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnRyByVd(prm_top_angvelo, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    }
}

void GgafDxKurokoMvAngAssistant::turnByVdTwd(
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
        angle out_angRz_Target;
        angle out_angRy_Target;
        UTIL::convVectorToRzRy(vx, vy, vz,
                               out_angRz_Target,
                               out_angRy_Target);
        turnRzRyByVdTo(
                prm_top_angvelo,
                out_angRz_Target, out_angRy_Target, prm_way, prm_optimize_ang,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_zero_acc_end_flg);
    }
}

void GgafDxKurokoMvAngAssistant::turnByVdTwd(
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

GgafDxKurokoMvAngAssistant::~GgafDxKurokoMvAngAssistant() {
}


