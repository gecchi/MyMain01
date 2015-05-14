#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoAssistantA::GgafDxKurokoAssistantA(GgafDxKuroko* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    _smthMv._org_velo = _pMaster->_velo_mv;
    _smthMv._org_acce = _pMaster->_acc_mv;
}

void GgafDxKurokoAssistantA::behave() {
    if (_smthMv.isAccelerating()) {
        _smthMv.behave();
        _pMaster->setMvVelo(_smthMv._org_velo - _smthMv._org_acce);
        _pMaster->setMvAcce(_smthMv._org_acce);
    }
}

void GgafDxKurokoAssistantA::slideMvByDt(coord prm_target_distance, int prm_target_frames,
                                         float prm_p1, float prm_p2, velo prm_end_velo,
                                         bool prm_zero_acc_end_flg) {
    _smthMv._org_value = 0;
    _smthMv._org_velo = _pMaster->_velo_mv;
    _smthMv._org_acce = _pMaster->_acc_mv;
    _smthMv.accelerateByDt(prm_target_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_velo,
                           prm_zero_acc_end_flg);
}

void GgafDxKurokoAssistantA::slideMvByVd(velo prm_top_velo, coord prm_target_distance,
                                      float prm_p1, float prm_p2, velo prm_end_velo,
                                      bool prm_zero_acc_end_flg) {
    _smthMv._org_value = 0;
    _smthMv._org_velo = _pMaster->_velo_mv;
    _smthMv._org_acce = _pMaster->_acc_mv;
    _smthMv.accelerateByVd(prm_top_velo, prm_target_distance,
                           prm_p1,prm_p2,prm_end_velo,
                           prm_zero_acc_end_flg);
}

GgafDxKurokoAssistantA::~GgafDxKurokoAssistantA() {
}


