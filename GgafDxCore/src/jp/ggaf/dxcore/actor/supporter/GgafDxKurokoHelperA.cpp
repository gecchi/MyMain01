#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxAccelerator.hpp"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoHelperA::GgafDxKurokoHelperA(GgafDxKuroko* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    _smthMv._velo = _pMaster->_veloMv;
    _smthMv._acce = _pMaster->_accMv;
}

void GgafDxKurokoHelperA::behave() {
    bool flg = _smthMv._prm._flg;
    _smthMv.behave();
    if (flg) {
        _pMaster->setMvVelo(_smthMv._velo - _smthMv._acce);
        _pMaster->setMvAcce(_smthMv._acce);
    }
}

void GgafDxKurokoHelperA::slideMvByDt(coord prm_target_distance, int prm_target_frames,
                                     float prm_p1, float prm_p2, velo prm_end_velo,
                                     bool prm_endacc_flg) {
    _smthMv._value = 0;
    _smthMv._velo = _pMaster->_veloMv;
    _smthMv._acce = _pMaster->_accMv;
    _smthMv.accelerateByDt(prm_target_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_velo,
                           prm_endacc_flg);
}

void GgafDxKurokoHelperA::slideMvByVd(velo prm_top_velo, coord prm_target_distance,
                                    float prm_p1, float prm_p2, velo prm_end_velo,
                                    bool prm_endacc_flg) {
    _smthMv._value = 0;
    _smthMv._velo = _pMaster->_veloMv;
    _smthMv._acce = _pMaster->_accMv;
    _smthMv.accelerateByVd(prm_top_velo, prm_target_distance,
                           prm_p1,prm_p2,prm_end_velo,
                           prm_endacc_flg);
}

GgafDxKurokoHelperA::~GgafDxKurokoHelperA() {
}


