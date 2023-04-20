#include "jp/ggaf/dx/actor/supporter/CoordVehicleAssistantA.h"

#include "jp/ggaf/core/util/TrapezoidalVeloValue.hpp"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

CoordVehicleAssistantA::CoordVehicleAssistantA(CoordVehicle* prm_pMaster) : GgafCore::Object(),
        _pMaster(prm_pMaster) {
    _smthVxMv._t_velo = _pMaster->_velo_x;
    _smthVxMv._t_acce = _pMaster->_acce_x;
    _smthVyMv._t_velo = _pMaster->_velo_y;
    _smthVyMv._t_acce = _pMaster->_acce_y;
    _smthVzMv._t_velo = _pMaster->_velo_z;
    _smthVzMv._t_acce = _pMaster->_acce_z;
}
void CoordVehicleAssistantA::behave() {
    if (_smthVxMv.isTransitioning()) {
        _smthVxMv.behave();
        _pMaster->setVeloX(_smthVxMv._t_velo - _smthVxMv._t_acce);
        _pMaster->setAcceX(_smthVxMv._t_acce);
    }
    if (_smthVyMv.isTransitioning()) {
        _smthVyMv.behave();
        _pMaster->setVeloY(_smthVyMv._t_velo - _smthVyMv._t_acce);
        _pMaster->setAcceY(_smthVyMv._t_acce);
    }
    if (_smthVzMv.isTransitioning()) {
        _smthVzMv.behave();
        _pMaster->setVeloZ(_smthVzMv._t_velo - _smthVzMv._t_acce );
        _pMaster->setAcceZ(_smthVzMv._t_acce);
    }

}

void CoordVehicleAssistantA::slideVxMvByDt(coord prm_target_distance, int prm_target_frames,
                                          double prm_p1, double prm_p2, velo prm_end_velo,
                                          bool prm_zero_acc_end_flg) {
    _smthVxMv._t_value = 0;
    _smthVxMv._t_velo = _pMaster->_velo_x;
    _smthVxMv._t_acce = _pMaster->_acce_x;
    _smthVxMv.moveByDt(prm_target_distance, prm_target_frames,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_zero_acc_end_flg);
}

void CoordVehicleAssistantA::slideVyMvByDt(coord prm_target_distance, int prm_target_frames,
                                          double prm_p1, double prm_p2, velo prm_end_velo,
                                          bool prm_zero_acc_end_flg) {
    _smthVyMv._t_value = 0;
    _smthVyMv._t_velo = _pMaster->_velo_y;
    _smthVyMv._t_acce = _pMaster->_acce_y;
    _smthVyMv.moveByDt(prm_target_distance, prm_target_frames,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void CoordVehicleAssistantA::slideVzMvByDt(coord prm_target_distance, int prm_target_frames,
                                          double prm_p1, double prm_p2, velo prm_end_velo,
                                          bool prm_zero_acc_end_flg) {
    _smthVzMv._t_value = 0;
    _smthVzMv._t_velo = _pMaster->_velo_z;
    _smthVzMv._t_acce = _pMaster->_acce_z;
    _smthVzMv.moveByDt(prm_target_distance, prm_target_frames,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void CoordVehicleAssistantA::slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                              int prm_target_frames,
                                              double prm_p1, double prm_p2, velo prm_end_velo,
                                              bool prm_zero_acc_end_flg) {
    slideVxyzMvByDt( prm_x_target - _pMaster->_pActor->_x,
                     prm_y_target - _pMaster->_pActor->_y,
                     prm_z_target - _pMaster->_pActor->_z,
                     prm_target_frames,
                     prm_p1, prm_p2, prm_end_velo,
                     prm_zero_acc_end_flg);
}

void CoordVehicleAssistantA::slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                              int prm_target_frames,
                                              double prm_x_p1, double prm_x_p2, velo prm_x_end_velo,
                                              double prm_y_p1, double prm_y_p2, velo prm_y_end_velo,
                                              double prm_z_p1, double prm_z_p2, velo prm_z_end_velo,
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

void CoordVehicleAssistantA::slideVxMvByVd(velo prm_top_velo, coord prm_target_distance,
                                          double prm_p1, double prm_p2, velo prm_end_velo,
                                          bool prm_zero_acc_end_flg) {
    _smthVxMv._t_value = 0;
    _smthVxMv._t_velo = _pMaster->_velo_x;
    _smthVxMv._t_acce = _pMaster->_acce_x;
    _smthVxMv.moveByVd(prm_top_velo, prm_target_distance,
                             prm_p1, prm_p2, prm_end_velo,
                             prm_zero_acc_end_flg);
}

void CoordVehicleAssistantA::slideVyMvByVd(velo prm_top_velo, coord prm_target_distance,
                                          double prm_p1, double prm_p2, velo prm_end_velo,
                                          bool prm_zero_acc_end_flg) {
    _smthVyMv._t_value = 0;
    _smthVyMv._t_velo = _pMaster->_velo_y;
    _smthVyMv._t_acce = _pMaster->_acce_y;
    _smthVyMv.moveByVd(prm_top_velo, prm_target_distance,
                       prm_p1,prm_p2,prm_end_velo,
                       prm_zero_acc_end_flg);
}

void CoordVehicleAssistantA::slideVzMvByVd(velo prm_top_velo, coord prm_target_distance,
                                          double prm_p1, double prm_p2, velo prm_end_velo,
                                          bool prm_zero_acc_end_flg) {
    _smthVzMv._t_value = 0;
    _smthVzMv._t_velo = _pMaster->_velo_z;
    _smthVzMv._t_acce = _pMaster->_acce_z;
    _smthVzMv.moveByVd(prm_top_velo, prm_target_distance,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_zero_acc_end_flg);
}

void CoordVehicleAssistantA::slideVxyzMvByVd(velo prm_top_velo,
                                            coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                                            double prm_p1, double prm_p2, velo prm_end_velo,
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

void CoordVehicleAssistantA::slideVxyzMvByVdTo(velo prm_top_velo,
                                              coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                              double prm_p1, double prm_p2, velo prm_end_velo,
                                              bool prm_zero_acc_end_flg) {
    slideVxyzMvByVd(prm_top_velo,
                    prm_x_target - _pMaster->_pActor->_x,
                    prm_y_target - _pMaster->_pActor->_y,
                    prm_z_target - _pMaster->_pActor->_z,
                    prm_p1, prm_p2, prm_end_velo,
                    prm_zero_acc_end_flg);
}

CoordVehicleAssistantA::~CoordVehicleAssistantA() {
}


