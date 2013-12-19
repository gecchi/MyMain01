#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverHelperA.h"

#include "jp/ggaf/dxcore/util/GgafDxAccelerator.hpp"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"


using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAxesMoverHelperA::GgafDxAxesMoverHelperA(GgafDxAxesMover* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    _smthVxMv._velo = _pMaster->_veloVxMv;
    _smthVxMv._acce = _pMaster->_acceVxMv;
    _smthVyMv._velo = _pMaster->_veloVyMv;
    _smthVyMv._acce = _pMaster->_acceVyMv;
    _smthVzMv._velo = _pMaster->_veloVzMv;
    _smthVzMv._acce = _pMaster->_acceVzMv;
}
void GgafDxAxesMoverHelperA::behave() {
    bool flgx = _smthVxMv._prm._flg;
    _smthVxMv.behave();
    bool flgy = _smthVyMv._prm._flg;
    _smthVyMv.behave();
    bool flgz = _smthVzMv._prm._flg;
    _smthVzMv.behave();


    if (flgx) {
        _pMaster->setVxMvVelo(_smthVxMv._velo - _smthVxMv._acce);
        _pMaster->setVxMvAcce(_smthVxMv._acce);
    }
    if (flgy) {
        _pMaster->setVyMvVelo(_smthVyMv._velo - _smthVyMv._acce);
        _pMaster->setVyMvAcce(_smthVyMv._acce);
    }
    if (flgz) {
        _pMaster->setVzMvVelo(_smthVzMv._velo - _smthVzMv._acce );
        _pMaster->setVzMvAcce(_smthVzMv._acce);
    }

}

void GgafDxAxesMoverHelperA::slideVxMvByDt(coord prm_target_distance, int prm_target_frames,
                                           float prm_p1, float prm_p2, velo prm_end_velo,
                                           bool prm_endacc_flg) {
    _smthVxMv._value = 0;
    _smthVxMv._velo = _pMaster->_veloVxMv;
    _smthVxMv._acce = _pMaster->_acceVxMv;
    _smthVxMv.accelerateByDt(prm_target_distance, prm_target_frames,
                             prm_p1,prm_p2,prm_end_velo,
                             prm_endacc_flg);
}

void GgafDxAxesMoverHelperA::slideVyMvByDt(coord prm_target_distance, int prm_target_frames,
                                           float prm_p1, float prm_p2, velo prm_end_velo,
                                           bool prm_endacc_flg) {
    _smthVyMv._value = 0;
    _smthVyMv._velo = _pMaster->_veloVyMv;
    _smthVyMv._acce = _pMaster->_acceVyMv;
    _smthVyMv.accelerateByDt(prm_target_distance, prm_target_frames,
                             prm_p1,prm_p2,prm_end_velo,
                             prm_endacc_flg);
}

void GgafDxAxesMoverHelperA::slideVzMvByDt(coord prm_target_distance, int prm_target_frames,
                                           float prm_p1, float prm_p2, velo prm_end_velo,
                                           bool prm_endacc_flg) {
    _smthVzMv._value = 0;
    _smthVzMv._velo = _pMaster->_veloVzMv;
    _smthVzMv._acce = _pMaster->_acceVzMv;
    _smthVzMv.accelerateByDt(prm_target_distance, prm_target_frames,
                             prm_p1,prm_p2,prm_end_velo,
                             prm_endacc_flg);
}

void GgafDxAxesMoverHelperA::slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                               int prm_target_frames,
                                               float prm_p1, float prm_p2, velo prm_end_velo,
                                               bool prm_endacc_flg) {
    slideVxyzMvByDt( prm_x_target - _pMaster->_pActor->_x,
                     prm_y_target - _pMaster->_pActor->_y,
                     prm_z_target - _pMaster->_pActor->_z,
                     prm_target_frames,
                     prm_p1,  prm_p2,  prm_end_velo,
                     prm_endacc_flg);
}


void GgafDxAxesMoverHelperA::slideVxMvByVd(velo prm_top_velo, coord prm_target_distance,
                                           float prm_p1, float prm_p2, velo prm_end_velo,
                                           bool prm_endacc_flg) {
    _smthVxMv._value = 0;
    _smthVxMv._velo = _pMaster->_veloVxMv;
    _smthVxMv._acce = _pMaster->_acceVxMv;
    _smthVxMv.accelerateByVd(prm_top_velo, prm_target_distance,
                             prm_p1,prm_p2,prm_end_velo,
                             prm_endacc_flg);
}

void GgafDxAxesMoverHelperA::slideVyMvByVd(velo prm_top_velo, coord prm_target_distance,
                                           float prm_p1, float prm_p2, velo prm_end_velo,
                                           bool prm_endacc_flg) {
    _smthVyMv._value = 0;
    _smthVyMv._velo = _pMaster->_veloVyMv;
    _smthVyMv._acce = _pMaster->_acceVyMv;
    _smthVyMv.accelerateByVd(prm_top_velo, prm_target_distance,
                             prm_p1,prm_p2,prm_end_velo,
                             prm_endacc_flg);
}

void GgafDxAxesMoverHelperA::slideVzMvByVd(velo prm_top_velo, coord prm_target_distance,
                                           float prm_p1, float prm_p2, velo prm_end_velo,
                                           bool prm_endacc_flg) {
    _smthVzMv._value = 0;
    _smthVzMv._velo = _pMaster->_veloVzMv;
    _smthVzMv._acce = _pMaster->_acceVzMv;
    _smthVzMv.accelerateByVd(prm_top_velo, prm_target_distance,
                             prm_p1,prm_p2,prm_end_velo,
                             prm_endacc_flg);
}
void GgafDxAxesMoverHelperA::slideVxyzMvByVd(velo prm_top_velo,
                                             coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                                             float prm_p1, float prm_p2, velo prm_end_velo,
                                             bool prm_endacc_flg) {
    double r = MAX3(ABS(prm_x_target_distance), ABS(prm_y_target_distance), ABS(prm_z_target_distance));
    if (!ZEROd_EQ(r)) {
        slideVxMvByVd( prm_top_velo * ABS(prm_x_target_distance/r),  prm_x_target_distance,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_endacc_flg);
        slideVyMvByVd( prm_top_velo * ABS(prm_y_target_distance/r),  prm_y_target_distance,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_endacc_flg);
        slideVzMvByVd( prm_top_velo * ABS(prm_z_target_distance/r),  prm_z_target_distance ,
                       prm_p1, prm_p2, prm_end_velo,
                       prm_endacc_flg);
    }
}
void GgafDxAxesMoverHelperA::slideVxyzMvByVdTo(velo prm_top_velo,
                                               coord prm_x_target, coord prm_y_target, coord prm_z_target,
                                               float prm_p1, float prm_p2, velo prm_end_velo,
                                               bool prm_endacc_flg) {
    slideVxyzMvByVd(prm_top_velo,
                    prm_x_target - _pMaster->_pActor->_x,
                    prm_y_target - _pMaster->_pActor->_y,
                    prm_z_target - _pMaster->_pActor->_z,
                    prm_p1, prm_p2, prm_end_velo,
                    prm_endacc_flg);
}

GgafDxAxesMoverHelperA::~GgafDxAxesMoverHelperA() {
}


