#include "jp/ggaf/dx/actor/supporter/RikishaMvAssistant.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/core/util/ValueAccelerator.hpp"


using namespace GgafDx;

RikishaMvAssistant::RikishaMvAssistant(Rikisha* prm_pMaster) : GgafCore::Object(),
        _pMaster(prm_pMaster) {
    _smthMv._t_velo = _pMaster->_velo_mv;
    _smthMv._t_acce = _pMaster->_acc_mv;
}

void RikishaMvAssistant::behave() {
    if (_smthMv.isAccelerating()) {
        _smthMv.behave();
        _pMaster->setMvVelo(_smthMv._t_velo - _smthMv._t_acce);
        _pMaster->setMvAcce(_smthMv._t_acce);
    }
}

void RikishaMvAssistant::slideByDt(coord prm_target_distance, int prm_target_frames,
                                        float prm_p1, float prm_p2, velo prm_end_velo,
                                        bool prm_zero_acc_end_flg) {
    _smthMv._t_value = 0;
    _smthMv._t_velo = _pMaster->_velo_mv;
    _smthMv._t_acce = _pMaster->_acc_mv;
    _smthMv.accelerateByDt(prm_target_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_velo,
                           prm_zero_acc_end_flg);
}

void RikishaMvAssistant::slideByVd(velo prm_top_velo, coord prm_target_distance,
                                        float prm_p1, float prm_p2, velo prm_end_velo,
                                        bool prm_zero_acc_end_flg) {
    _smthMv._t_value = 0;
    _smthMv._t_velo = _pMaster->_velo_mv;
    _smthMv._t_acce = _pMaster->_acc_mv;
    _smthMv.accelerateByVd(prm_top_velo, prm_target_distance,
                           prm_p1,prm_p2,prm_end_velo,
                           prm_zero_acc_end_flg);
}

RikishaMvAssistant::~RikishaMvAssistant() {
}


