#include "jp/ggaf/dxcore/sound/GgafDxSeTransmitter.h"

#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include <stdio.h>

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSeTransmitter::GgafDxSeTransmitter() : GgafObject() {
    _se_num = 0;
}

void GgafDxSeTransmitter::set(int prm_se_no, const char* prm_se_key, int prm_cannel) {
    int se_num = _vecSeConnection.size();
    if (prm_se_no >= se_num) {
        for (int i = se_num; i <= prm_se_no; i++) {
            _vecSeConnection.push_back(nullptr);
            _vec_volume.push_back(GGAF_MAX_VOLUME);
            _vec_pan.push_back(0);
        }
        _se_num = _vecSeConnection.size();
    }

    if (strlen(prm_se_key) > 128) {
        throwGgafCriticalException("SE����ID�����߂��܂��B128�����ɗ}���ĉ������Bprm_se_key="<<prm_se_key);
    }
    std::string idstr =  XTOS(prm_cannel) + "/" + prm_se_key; //�����R�l�N�V�����̎���ID���� �u�`�����l���ԍ� + "/" + wave���ʖ��v
                                                              //�Ƃ��邱�Ƃɂ��A�`�����l���ԍ��������Ȃ�� new ����Ȃ��B
    if (_vecSeConnection[prm_se_no]) {
        _TRACE_("���x���� ����ID="<<prm_se_no<<" �ɂ�SE("<<(_vecSeConnection[prm_se_no]->getIdStr())<<")���ݒ�ς݂ł����B�����ڑ��� close ��A�V����SE("<<idstr<<")���㏑�����܂��B�Ӑ}���Ă܂����H");
        _vecSeConnection[prm_se_no]->close();
    }
    _vecSeConnection[prm_se_no] = connectToSeManager(idstr.c_str());
    stop(prm_se_no);
    setVolume(prm_se_no, _vec_volume[prm_se_no]);
    setPan(prm_se_no, _vec_pan[prm_se_no]);
}

void GgafDxSeTransmitter::setVolume(int prm_se_no, double prm_volume) {
    _vec_volume[prm_se_no] = prm_volume;
    getSe(prm_se_no)->setVolume((int)(_vec_volume[prm_se_no]));
}

void GgafDxSeTransmitter::setPan(int prm_se_no, float prm_pan) {
    _vec_pan[prm_se_no] = prm_pan;
    getSe(prm_se_no)->setPan(_vec_pan[prm_se_no]);
}

void GgafDxSeTransmitter::play(int prm_se_no, bool prm_can_looping) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_se_no="<<prm_se_no);
    }
#endif
    GgafDxSe* pSe = getSe(prm_se_no);
    pSe->setVolume(_vec_volume[prm_se_no]);
    pSe->setPan(_vec_pan[prm_se_no]);
    pSe->play(prm_can_looping);
}

void GgafDxSeTransmitter::stop(int prm_se_no) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_se_no="<<prm_se_no);
    }
#endif
    getSe(prm_se_no)->stop();
}

GgafDxSe* GgafDxSeTransmitter::getSe(int prm_se_no) const {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_se_no="<<prm_se_no);
    }
#endif
    return _vecSeConnection[prm_se_no]->peek();
}


GgafDxSeTransmitter::~GgafDxSeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_vecSeConnection[i]) {
            _vecSeConnection[i]->close();
        }
    }
}

