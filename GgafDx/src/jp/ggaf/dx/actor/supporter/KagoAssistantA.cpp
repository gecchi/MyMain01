#include "jp/ggaf/dx/actor/supporter/KagoAssistantA.h"

#include "jp/ggaf/core/util/AccelerationValue.hpp"
#include "jp/ggaf/dx/actor/supporter/Kago.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

KagoAssistantA::KagoAssistantA(Kago* prm_pMaster) : GgafCore::Object(),
        _pMaster(prm_pMaster) {
    _smthVxMv._t_velo = _pMaster->_velo_vx_mv;
    _smthVxMv._t_acce = _pMaster->_acce_vx_mv;
    _smthVyMv._t_velo = _pMaster->_velo_vy_mv;
    _smthVyMv._t_acce = _pMaster->_acce_vy_mv;
    _smthVzMv._t_velo = _pMaster->_velo_vz_mv;
    _smthVzMv._t_acce = _pMaster->_acce_vz_mv;
}
void KagoAssistantA::behave() {
    if (_smthVxMv.isAccelerating()) {
        _smthVxMv.behave();
        _pMaster->setVxMvVelo(_smthVxMv._t_velo - _smthVxMv._t_acce);
        _pMaster->setVxMvAcce(_smthVxMv._t_acce);
    }
    if (_smthVyMv.isAccelerating()) {
        _smthVyMv.behave();
        _pMaster->setVyMvVelo(_smthVyMv._t_velo - _smthVyMv._t_acce);
        _pMaster->setVyMvAcce(_smthVyMv._t_acce);
    }
    if (_smthVzMv.isAccelerating()) {
        _smthVzMv.behave();
        _pMaster->setVzMvVelo(_smthVzMv._t_velo - _smthVzMv._t_acce );
        _pMaster->setVzMvAcce(_smthVzMv._t_acce);
    }

}

void KagoAssistantA::slideVxMvByDt(coord prm_target_distance, int prm_target_frames,
                                   float prm_p1, float prm_p2, velo prm_end_velo,
                                   bool prm_zero_acc_end_flg) {
    _smthVxMv._t_value = 0;
    _smthVxMv._t_velo = _pMaster->_velo_vx_mv;
    _smthVxMv._t_acce = _pMaster->_acce_vx_mv;
    _smthVxMv.accelerateByDt(prm_target_distance, prm_target_frames,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVyMvByDt(coord prm_target_distance, int prm_target_frames,
                                              float prm_p1, float prm_p2, velo prm_end_velo,
                                              bool prm_zero_acc_end_flg) {
    _smthVyMv._t_value = 0;
    _smthVyMv._t_velo = _pMaster->_velo_vy_mv;
    _smthVyMv._t_acce = _pMaster->_acce_vy_mv;
    _smthVyMv.accelerateByDt(prm_target_distance, prm_target_frames,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVzMvByDt(coord prm_target_distance, int prm_target_frames,
                                   float prm_p1, float prm_p2, velo prm_end_velo,
                                   bool prm_zero_acc_end_flg) {
    _smthVzMv._t_value = 0;
    _smthVzMv._t_velo = _pMaster->_velo_vz_mv;
    _smthVzMv._t_acce = _pMaster->_acce_vz_mv;
    _smthVzMv.accelerateByDt(prm_target_distance, prm_target_frames,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                       int prm_target_frames,
                                       float prm_p1, float prm_p2, velo prm_end_velo,
                                       bool prm_zero_acc_end_flg) {
    slideVxyzMvByDt( prm_x_target - _pMaster->_pActor->_x,
                     prm_y_target - _pMaster->_pActor->_y,
                     prm_z_target - _pMaster->_pActor->_z,
                     prm_target_frames,
                     prm_p1, prm_p2, prm_end_velo,
                     prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                       int prm_target_frames,
                                       float prm_x_p1, float prm_x_p2, velo prm_x_end_velo,
                                       float prm_y_p1, float prm_y_p2, velo prm_y_end_velo,
                                       float prm_z_p1, float prm_z_p2, velo prm_z_end_velo,
                                       bool prm_zero_acc_end_flg) {
    slideVxyzMvByDt( prm_x_target - _pMaster->_pActor->_x,
                     prm_y_target - _pMaster->_pActor->_y,
                     prm_z_target - _pMaster->_pActor->_z,
                     prm_target_frames,
                     prm_x_p1, prm_x_p2, prm_x_end_velo,
                     prm_y_p1, prm_y_p2, prm_y_end_velo,
                     prm_z_p1, prm_z_p2, prm_z_end_velo,
                     prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVxMvByVd(velo prm_top_velo, coord prm_target_distance,
                                   float prm_p1, float prm_p2, velo prm_end_velo,
                                   bool prm_zero_acc_end_flg) {
    _smthVxMv._t_value = 0;
    _smthVxMv._t_velo = _pMaster->_velo_vx_mv;
    _smthVxMv._t_acce = _pMaster->_acce_vx_mv;
    _smthVxMv.accelerateByVd(prm_top_velo, prm_target_distance,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVyMvByVd(velo prm_top_velo, coord prm_target_distance,
                                   float prm_p1, float prm_p2, velo prm_end_velo,
                                   bool prm_zero_acc_end_flg) {
    _smthVyMv._t_value = 0;
    _smthVyMv._t_velo = _pMaster->_velo_vy_mv;
    _smthVyMv._t_acce = _pMaster->_acce_vy_mv;
    _smthVyMv.accelerateByVd(prm_top_velo, prm_target_distance,
                             prm_p1,prm_p2,prm_end_velo,
                             prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVzMvByVd(velo prm_top_velo, coord prm_target_distance,
                                   float prm_p1, float prm_p2, velo prm_end_velo,
                                   bool prm_zero_acc_end_flg) {
    _smthVzMv._t_value = 0;
    _smthVzMv._t_velo = _pMaster->_velo_vz_mv;
    _smthVzMv._t_acce = _pMaster->_acce_vz_mv;
    _smthVzMv.accelerateByVd(prm_top_velo, prm_target_distance,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void KagoAssistantA::slideVxyzMvByVd(velo prm_top_velo,
                                     coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                                     float prm_p1, float prm_p2, velo prm_end_velo,
                                     bool prm_zero_acc_end_flg) {
    double r = MAX3(ABS(prm_x_target_distance), ABS(prm_y_target_distance), ABS(prm_z_target_distance));
    if (!ZEROd_EQ(r)) {
        slideVxMvByVd( prm_top_velo * ABS(prm_x_target_distance/r),  prm_x_target_distance,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_zero_acc_end_flg);
        slideVyMvByVd( prm_top_velo * ABS(prm_y_target_distance/r),  prm_y_target_distance,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_zero_acc_end_flg);
        slideVzMvByVd( prm_top_velo * ABS(prm_z_target_distance/r),  prm_z_target_distance ,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_zero_acc_end_flg);
    }
}

void KagoAssistantA::slideVxyzMvByVdTo(velo prm_top_velo,
                                       coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                       float prm_p1, float prm_p2, velo prm_end_velo,
                                       bool prm_zero_acc_end_flg) {
    slideVxyzMvByVd(prm_top_velo,
                    prm_x_target - _pMaster->_pActor->_x,
                    prm_y_target - _pMaster->_pActor->_y,
                    prm_z_target - _pMaster->_pActor->_z,
                    prm_p1, prm_p2, prm_end_velo,
                    prm_zero_acc_end_flg);
}

KagoAssistantA::~KagoAssistantA() {
}


