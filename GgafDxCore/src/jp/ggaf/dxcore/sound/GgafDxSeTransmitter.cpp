#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSeTransmitter::GgafDxSeTransmitter() : GgafObject() {
    _se_num = 0;
    _papSeCon = NULL;
}

void GgafDxSeTransmitter::useSe(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeCon = NEW GgafDxSeConnection*[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeCon[i] = NULL;
    }
}

void GgafDxSeTransmitter::set(int prm_id, const char* prm_se_name, int prm_cannel) {
#ifdef MY_DEBUG
    if (_se_num <= 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() useSe�Ŏg�p����Se�������O�ɐ錾���Ă��������Bprm_id="<<prm_id);
    }
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��B prm_id="<<prm_id);
    }
#endif
    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name);
    _papSeCon[prm_id] = connectSeManager(idstr);
}

void GgafDxSeTransmitter::play(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id);
    }
#endif
    _papSeCon[prm_id]->fetch()->play(GGAF_MAX_VOLUME, 0.0);
}

GgafDxSe* GgafDxSeTransmitter::get(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id);
    }
#endif
    return _papSeCon[prm_id]->fetch();
}


GgafDxSeTransmitter::~GgafDxSeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_papSeCon[i]) {
            _papSeCon[i]->close();
        }
    }
    DELETEARR_POSSIBLE_NULL(_papSeCon);
}

