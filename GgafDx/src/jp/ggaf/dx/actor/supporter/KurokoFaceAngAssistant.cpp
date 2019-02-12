#include "jp/ggaf/dx/actor/supporter/KurokoFaceAngAssistant.h"

#include "jp/ggaf/core/util/ValueAccelerator.hpp"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

KurokoFaceAngAssistant::KurokoFaceAngAssistant(Kuroko* prm_pMaster) : GgafCore::Object(),
        _pMaster(prm_pMaster) {
    for (int ax = 0; ax < 3; ax++) {
        _smthFaceAng[ax]._t_velo = _pMaster->_angvelo_face[ax];
        _smthFaceAng[ax]._t_acce = _pMaster->_angacce_face[ax];

        _tw[ax].count = 0;
        _tw[ax].target_num = 0;
        for (int t = 0; t < 10; t++) {
            _tw[ax].target[t] = 0;
        }
        _tw[ax].loop_num = 0;
        _tw[ax].way = 0;
        _tw[ax].target_frames = 0;
        _tw[ax].p1 = 0;
        _tw[ax].p2 = 0;
        _tw[ax].end_angvelo = 0;
        _tw[ax].zero_acc_end_flg = 0;
    }
}

void KurokoFaceAngAssistant::behave() {
    for (int ax = 0; ax < 3; ax++) {
        if (_smthFaceAng[ax].isAccelerating()) {
            _smthFaceAng[ax].behave();
            _pMaster->setFaceAngVelo(ax, _smthFaceAng[ax]._t_velo - _smthFaceAng[ax]._t_acce); //こうしないと黒衣のbehaveで２回_acce足し込まれるし
            _pMaster->setFaceAngAcce(ax, _smthFaceAng[ax]._t_acce);
        } else {
            if (_tw[ax].target_num > 0) {
                //ターゲットのアングルがある。ツイスト中
                _tw[ax].count++;
                if (_tw[ax].count == _tw[ax].loop_num) {
                    _tw[ax].target_num = 0;
                    continue;
                } else {
                    if (_tw[ax].way == TURN_CLOCKWISE) {
                        _tw[ax].way = TURN_COUNTERCLOCKWISE;
                    } else if (_tw[ax].way == TURN_COUNTERCLOCKWISE) {
                        _tw[ax].way = TURN_CLOCKWISE;
                    }
                    int t = _tw[ax].count % _tw[ax].target_num;
                    angle distance = _pMaster->getFaceAngDistance(ax, _tw[ax].target[t], _tw[ax].way);
                    turnByDt(ax, distance, _tw[ax].target_frames,
                             _tw[ax].p1, _tw[ax].p2, _tw[ax].end_angvelo,
                             _tw[ax].zero_acc_end_flg);
                }
            }
        }
    }
}

void KurokoFaceAngAssistant::turnByDt(axis prm_axis,
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

void KurokoFaceAngAssistant::turnByVd(axis prm_axis,
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

void KurokoFaceAngAssistant::turnRzByDtTo(angle prm_rz_target, int prm_way, int prm_target_frames,
                                                float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                                bool prm_zero_acc_end_flg) {
    angle distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way);
    turnByDt(AXIS_Z,
             distance, prm_target_frames,
             prm_p1, prm_p2, prm_end_angvelo,
             prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::turnRyByDtTo(angle prm_ry_target, int prm_way, int prm_target_frames,
                                                float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                                bool prm_zero_acc_end_flg) {
    angle distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way);
    turnByDt(AXIS_Y,
             distance, prm_target_frames,
             prm_p1, prm_p2, prm_end_angvelo,
             prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::rollFaceAngByDtTo(angle prm_ang_rx_target, int prm_way, int prm_target_frames,
                                                     float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                                     bool prm_zero_acc_end_flg) {
    angle distance = _pMaster->getFaceAngDistance(AXIS_X, prm_ang_rx_target, prm_way);
    turnByDt(AXIS_X,
             distance, prm_target_frames,
             prm_p1, prm_p2, prm_end_angvelo,
             prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::turnRzRyByDtTo(
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

    turnByDt(AXIS_Z,
             out_rz_distance, prm_target_frames,
             prm_p1, prm_p2, prm_end_angvelo,
             prm_zero_acc_end_flg);
    turnByDt(AXIS_Y,
             out_ry_distance, prm_target_frames,
             prm_p1, prm_p2, prm_end_angvelo,
             prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::turnByDtTwd(
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
        turnRzRyByDtTo(
                out_rz_Target, out_ry_Target, prm_way, prm_optimize_ang,
                prm_target_frames,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_zero_acc_end_flg);
    }
}

void KurokoFaceAngAssistant::turnByDtTwd(
                                 GeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
                                 int prm_target_frames,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    turnByDtTwd(
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_target_frames,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_zero_acc_end_flg);
}


void KurokoFaceAngAssistant::turnRzByVdTo(
        angvelo prm_top_angvelo, angle prm_rz_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
        angle distance = _pMaster->getFaceAngDistance(AXIS_Z, prm_rz_target, prm_way);
        turnByVd(AXIS_Z,
                 prm_top_angvelo, distance,
                 prm_p1, prm_p2, prm_end_angvelo,
                 prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::turnRyByVdTo(
        angvelo prm_top_angvelo, angle prm_ry_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
        angle distance = _pMaster->getFaceAngDistance(AXIS_Y, prm_ry_target, prm_way);
        turnByVd(AXIS_Y,
                 prm_top_angvelo, distance,
                 prm_p1, prm_p2, prm_end_angvelo,
                 prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::rollByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_rx_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_zero_acc_end_flg) {
        angle distance = _pMaster->getFaceAngDistance(AXIS_X, prm_ang_rx_target, prm_way);
        turnByVd(AXIS_X,
                 prm_top_angvelo, distance,
                 prm_p1, prm_p2, prm_end_angvelo,
                 prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::turnRzRyByVdTo(
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

void KurokoFaceAngAssistant::turnByVdTwd(
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

void KurokoFaceAngAssistant::turnByVdTwd(
                                 angvelo prm_top_angvelo,
                                 GeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_zero_acc_end_flg) {
    turnByVdTwd(
            prm_top_angvelo,
            prm_pActor_target->_x, prm_pActor_target->_y, prm_pActor_target->_z, prm_way, prm_optimize_ang,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_zero_acc_end_flg);
}

void KurokoFaceAngAssistant::twist(axis prm_axis, angle prm_ang_target1, angle prm_ang_target2, int prm_twist_num,
                                         int prm_first_way, int prm_target_frames,
                                         float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                         bool prm_zero_acc_end_flg) {

    _tw[prm_axis].count = 0;
    _tw[prm_axis].target_num = 2;
    _tw[prm_axis].target[0] = prm_ang_target1;
    _tw[prm_axis].target[1] = prm_ang_target2;
    _tw[prm_axis].loop_num = prm_twist_num;
    _tw[prm_axis].way = prm_first_way;
    _tw[prm_axis].target_frames = prm_target_frames;
    _tw[prm_axis].p1 = prm_p1;
    _tw[prm_axis].p2 = prm_p2;
    _tw[prm_axis].end_angvelo = prm_end_angvelo;
    _tw[prm_axis].zero_acc_end_flg = prm_zero_acc_end_flg;
    angle distance = _pMaster->getFaceAngDistance(prm_axis, _tw[prm_axis].target[0], _tw[prm_axis].way);
    turnByDt(prm_axis,
             distance, _tw[prm_axis].target_frames,
             _tw[prm_axis].p1, _tw[prm_axis].p2, _tw[prm_axis].end_angvelo,
             _tw[prm_axis].zero_acc_end_flg);
}


KurokoFaceAngAssistant::~KurokoFaceAngAssistant() {
}


