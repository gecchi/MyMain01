#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAngAssistant.h"

#include "jp/ggaf/core/util/TrapezoidalVeloValue.hpp"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

LocusVehicleMvAngAssistant::LocusVehicleMvAngAssistant(LocusVehicle* prm_pMaster) : GgafCore::Object(),
        _pMaster(prm_pMaster) {
    _smthMvRzAng._t_velo = _pMaster->_angvelo_rz_mv;
    _smthMvRzAng._t_acce = _pMaster->_angacce_rz_mv;
    _smthMvRyAng._t_velo = _pMaster->_angvelo_ry_mv;
    _smthMvRyAng._t_acce = _pMaster->_angacce_ry_mv;

    _pnd_rz.count = 0;
    _pnd_rz.target_num = 0;
    for (int t = 0; t < 10; t++) {
        _pnd_rz.target[t] = 0;
    }
    _pnd_rz.loop_num = 0;
    _pnd_rz.way = 0;
    _pnd_rz.target_frames = 0;
    _pnd_rz.p1 = 0;
    _pnd_rz.p2 = 0;
    _pnd_rz.end_angvelo = 0;
    _pnd_rz.zero_acc_end_flg = 0;

    _pnd_ry.count = 0;
    _pnd_ry.target_num = 0;
    for (int t = 0; t < 10; t++) {
        _pnd_ry.target[t] = 0;
    }
    _pnd_ry.loop_num = 0;
    _pnd_ry.way = 0;
    _pnd_ry.target_frames = 0;
    _pnd_ry.p1 = 0;
    _pnd_ry.p2 = 0;
    _pnd_ry.end_angvelo = 0;
    _pnd_ry.zero_acc_end_flg = 0;
}

void LocusVehicleMvAngAssistant::behave() {
    if (_smthMvRzAng.isTransitioning()) {
        _smthMvRzAng.behave();
        _pMaster->setRzMvAngVelo(_smthMvRzAng._t_velo - _smthMvRzAng._t_acce); //こうしないと移動車両のbehaveで２回_acce足し込まれるし
        _pMaster->setRzMvAngAcce(_smthMvRzAng._t_acce);
    } else {
        if (_pnd_rz.target_num > 0) {
            //ターゲットのアングルがある。ツイスト中
            _pnd_rz.count++;
            if (_pnd_rz.count == _pnd_rz.loop_num) {
                _pnd_rz.target_num = 0;
            } else {
                if (_pnd_rz.way == TURN_CLOCKWISE) {
                    _pnd_rz.way = TURN_COUNTERCLOCKWISE;
                } else if (_pnd_rz.way == TURN_COUNTERCLOCKWISE) {
                    _pnd_rz.way = TURN_CLOCKWISE;
                }
                int t = _pnd_rz.count % _pnd_rz.target_num;
                turnRzByDtTo(_pnd_rz.target[t],
                             _pnd_rz.way, _pnd_rz.target_frames,
                             _pnd_rz.p1, _pnd_rz.p2,
                             _pnd_rz.end_angvelo,
                             _pnd_rz.zero_acc_end_flg);
            }
        }
    }
    if (_smthMvRyAng.isTransitioning()) {
        _smthMvRyAng.behave();
        _pMaster->setRyMvAngVelo(_smthMvRyAng._t_velo - _smthMvRyAng._t_acce); //こうしないと移動車両のbehaveで２回_acce足し込まれるし
        _pMaster->setRyMvAngAcce(_smthMvRyAng._t_acce);
    } else {
        if (_pnd_ry.target_num > 0) {
            //ターゲットのアングルがある。ツイスト中
            _pnd_ry.count++;
            if (_pnd_ry.count == _pnd_ry.loop_num) {
                _pnd_ry.target_num = 0;
            } else {
                if (_pnd_ry.way == TURN_CLOCKWISE) {
                    _pnd_ry.way = TURN_COUNTERCLOCKWISE;
                } else if (_pnd_ry.way == TURN_COUNTERCLOCKWISE) {
                    _pnd_ry.way = TURN_CLOCKWISE;
                }
                int t = _pnd_ry.count % _pnd_ry.target_num;
                turnRyByDtTo(_pnd_ry.target[t],
                             _pnd_ry.way, _pnd_ry.target_frames,
                             _pnd_ry.p1, _pnd_ry.p2,
                             _pnd_ry.end_angvelo,
                             _pnd_ry.zero_acc_end_flg);
            }
        }
    }
}

void LocusVehicleMvAngAssistant::turnRzByDt(
                        angle prm_distance, int prm_target_frames,
                        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
                        bool prm_zero_acc_end_flg ) {

    _smthMvRzAng._t_value = 0;
    _smthMvRzAng._t_velo = _pMaster->_angvelo_rz_mv;
    _smthMvRzAng._t_acce = _pMaster->_angacce_rz_mv;
    _smthMvRzAng.moveByDt(prm_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_angvelo,
                           prm_zero_acc_end_flg);
}
void LocusVehicleMvAngAssistant::turnRyByDt(
                        angle prm_distance, int prm_target_frames,
                        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
                        bool prm_zero_acc_end_flg ) {

    _smthMvRyAng._t_value = 0;
    _smthMvRyAng._t_velo = _pMaster->_angvelo_ry_mv;
    _smthMvRyAng._t_acce = _pMaster->_angacce_ry_mv;
    _smthMvRyAng.moveByDt(prm_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_angvelo,
                           prm_zero_acc_end_flg);
}

void LocusVehicleMvAngAssistant::turnRzByVd(
        angvelo prm_top_angvelo, angle prm_distance,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
    _smthMvRzAng._t_value = 0;
    _smthMvRzAng._t_velo = _pMaster->_angvelo_rz_mv;
    _smthMvRzAng._t_acce = _pMaster->_angacce_rz_mv;
    _smthMvRzAng.moveByVd(prm_top_angvelo, prm_distance,
                                prm_p1,prm_p2, prm_end_angvelo,
                                prm_zero_acc_end_flg);
}
void LocusVehicleMvAngAssistant::turnRyByVd(
        angvelo prm_top_angvelo, angle prm_distance,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    _smthMvRyAng._t_value = 0;
    _smthMvRyAng._t_velo = _pMaster->_angvelo_ry_mv;
    _smthMvRyAng._t_acce = _pMaster->_angacce_ry_mv;
    _smthMvRyAng.moveByVd(prm_top_angvelo, prm_distance,
                                prm_p1,prm_p2, prm_end_angvelo,
                                prm_zero_acc_end_flg);
}


void LocusVehicleMvAngAssistant::turnRzByDtTo(
        angle prm_rz_target, int prm_way, int prm_target_frames,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    angle distance = _pMaster->getRzMvAngDistance(prm_rz_target, prm_way);
    turnRzByDt(distance, prm_target_frames,
               prm_p1, prm_p2, prm_end_angvelo,
               prm_zero_acc_end_flg);
}

void LocusVehicleMvAngAssistant::turnRyByDtTo(
        angle prm_ry_target, int prm_way, int prm_target_frames,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    angle distance = _pMaster->getRyMvAngDistance(prm_ry_target, prm_way);
    turnRyByDt(distance, prm_target_frames,
               prm_p1, prm_p2, prm_end_angvelo,
               prm_zero_acc_end_flg);
}

void LocusVehicleMvAngAssistant::turnRzRyByDtTo(
        angle prm_rz_target, angle prm_ry_target, int prm_way, bool prm_optimize_ang,
        int prm_target_frames,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    angle out_rz_distance;
    angle out_ry_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyMvAngDistanceTwd(prm_rz_target, prm_ry_target, prm_way,
                                          out_rz_distance, out_ry_distance);
    } else {
        out_rz_distance = _pMaster->getRzMvAngDistance(prm_rz_target, prm_way);
        out_ry_distance = _pMaster->getRyMvAngDistance(prm_ry_target, prm_way);
    }
    turnRzByDt(out_rz_distance, prm_target_frames,
               prm_p1, prm_p2, prm_end_angvelo,
               prm_zero_acc_end_flg);
    turnRyByDt(out_ry_distance, prm_target_frames,
               prm_p1, prm_p2, prm_end_angvelo,
               prm_zero_acc_end_flg);
}

void LocusVehicleMvAngAssistant::turnByDtTwd(
        coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
        int prm_target_frames,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
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
        turnRzRyByDtTo(
                out_rz_Target, out_ry_Target, prm_way, prm_optimize_ang,
                prm_target_frames,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_zero_acc_end_flg);
    }
}

void LocusVehicleMvAngAssistant::turnByDtTwd(
                    GeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
                    int prm_target_frames,
                    double prm_p1, double prm_p2, angvelo prm_end_angvelo,
                    bool prm_zero_acc_end_flg)
{
    turnByDtTwd(
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_target_frames,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_zero_acc_end_flg);
}


void LocusVehicleMvAngAssistant::turnRzByVdTo(
        angvelo prm_top_angvelo, angle prm_rz_target, int prm_way,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    angle distance = _pMaster->getRzMvAngDistance(prm_rz_target, prm_way);
    turnRzByVd(prm_top_angvelo, distance,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void LocusVehicleMvAngAssistant::turnRyByVdTo(
        angvelo prm_top_angvelo, angle prm_ry_target, int prm_way,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    angle distance = _pMaster->getRyMvAngDistance(prm_ry_target, prm_way);
    turnRyByVd(prm_top_angvelo, distance,
                    prm_p1, prm_p2, prm_end_angvelo,
                    prm_zero_acc_end_flg);
}

void LocusVehicleMvAngAssistant::turnRzRyByVdTo(
        angvelo prm_top_angvelo,
        angle prm_rz_target, angle prm_ry_target, int prm_way, bool prm_optimize_ang,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    angle out_rz_distance;
    angle out_ry_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyMvAngDistanceTwd(prm_rz_target, prm_ry_target, prm_way,
                                          out_rz_distance, out_ry_distance);
    } else {
        out_rz_distance = _pMaster->getRzMvAngDistance(prm_rz_target, prm_way);
        out_ry_distance = _pMaster->getRyMvAngDistance(prm_ry_target, prm_way);
    }
    double drz = ABS(out_rz_distance);
    double dry = ABS(out_ry_distance);
    if (drz > dry) {
        double drr = dry / drz;
        turnRzByVd(prm_top_angvelo, out_rz_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnRyByVd(prm_top_angvelo*drr, out_ry_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    } else if (drz < dry) {
        double drr = drz / dry;
        turnRzByVd(prm_top_angvelo*drr, out_rz_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnRyByVd(prm_top_angvelo, out_ry_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    } else {
        turnRzByVd(prm_top_angvelo, out_rz_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
        turnRyByVd(prm_top_angvelo, out_ry_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_zero_acc_end_flg);
    }
}

void LocusVehicleMvAngAssistant::turnByVdTwd(
        angvelo prm_top_angvelo,
        coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
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

void LocusVehicleMvAngAssistant::turnByVdTwd(
        angvelo prm_top_angvelo,
        GeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
        double prm_p1, double prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg)
{
    turnByVdTwd(
            prm_top_angvelo,
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_zero_acc_end_flg);
}

void LocusVehicleMvAngAssistant::turnRzPendulum(coord prm_target1, coord prm_target2,
                                               int prm_twist_num,
                                               int prm_first_way, int prm_target_frames,
                                               double prm_p1, double prm_p2, angvelo prm_end_angvelo,
                                               bool prm_zero_acc_end_flg) {
    _pnd_rz.count = 0;
    _pnd_rz.target_num = 2;
    _pnd_rz.target[0] = prm_target1;
    _pnd_rz.target[1] = prm_target2;
    _pnd_rz.loop_num = prm_twist_num;
    _pnd_rz.way = prm_first_way;
    _pnd_rz.target_frames = prm_target_frames;
    _pnd_rz.p1 = prm_p1;
    _pnd_rz.p2 = prm_p2;
    _pnd_rz.end_angvelo = prm_end_angvelo;
    _pnd_rz.zero_acc_end_flg = prm_zero_acc_end_flg;
    turnRzByDtTo(_pnd_rz.target[0],
                 _pnd_rz.way, _pnd_rz.target_frames,
                 _pnd_rz.p1, _pnd_rz.p2,
                 _pnd_rz.end_angvelo,
                 _pnd_rz.zero_acc_end_flg);
}
void LocusVehicleMvAngAssistant::turnRyPendulum(coord prm_target1, coord prm_target2,
                                               int prm_twist_num,
                                               int prm_first_way, int prm_target_frames,
                                               double prm_p1, double prm_p2, angvelo prm_end_angvelo,
                                               bool prm_zero_acc_end_flg) {
    _pnd_ry.count = 0;
    _pnd_ry.target_num = 2;
    _pnd_ry.target[0] = prm_target1;
    _pnd_ry.target[1] = prm_target2;
    _pnd_ry.loop_num = prm_twist_num;
    _pnd_ry.way = prm_first_way;
    _pnd_ry.target_frames = prm_target_frames;
    _pnd_ry.p1 = prm_p1;
    _pnd_ry.p2 = prm_p2;
    _pnd_ry.end_angvelo = prm_end_angvelo;
    _pnd_ry.zero_acc_end_flg = prm_zero_acc_end_flg;
    turnRyByDtTo(_pnd_ry.target[0],
                 _pnd_ry.way, _pnd_ry.target_frames,
                 _pnd_ry.p1, _pnd_ry.p2,
                 _pnd_ry.end_angvelo,
                 _pnd_ry.zero_acc_end_flg);
}

LocusVehicleMvAngAssistant::~LocusVehicleMvAngAssistant() {
}


