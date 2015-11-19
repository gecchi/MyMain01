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
    _papSeConnection = nullptr;
}

void GgafDxSeTransmitter::declareSeNum(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeConnection = NEW GgafDxSeConnection*[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeConnection[i] = nullptr;
    }
}

void GgafDxSeTransmitter::set(int prm_se_no, const char* prm_se_key, int prm_cannel) {
    if (_papSeConnection == nullptr) {
        declareSeNum(prm_se_no+1); //declareSeNum���Ȃ��ꍇ��prm_id+1�܂�
    }
    if (prm_se_no < 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() ID���͈͊O�ł��B���̐��ł��肢���܂��B prm_se_no="<<prm_se_no);
    } else if (prm_se_no >= _se_num) {
        //_papSeConnection[] ���g������B
        int wk_se_num = _se_num;
        GgafDxSeConnection** papSeConnection = NEW GgafDxSeConnection*[_se_num];
        for (int i = 0; i < wk_se_num; i++) { //�ޔ�
            papSeConnection[i] = _papSeConnection[i];
        }
        GGAF_DELETEARR_NULLABLE(_papSeConnection);
        declareSeNum(prm_se_no+1); //prm_se_no+1 �֌g���B���̎��_�� _se_num �� prm_se_no+1 �ōX�V�����
        for (int i = 0; i < wk_se_num; i++) { //�����p���i�ޔ���߂��j
            _papSeConnection[i] = papSeConnection[i];
        }
        GGAF_DELETEARR_NULLABLE(papSeConnection);
    }
    if (strlen(prm_se_key) > 128) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() SE����ID�����߂��܂��B128�����ɗ}���ĉ������Bprm_se_key="<<prm_se_key);
    }
    std::string idstr =  XTOS(prm_cannel) + "/" + prm_se_key; //�����R�l�N�V�����̎���ID���� �u�`�����l���ԍ� + "/" + wave���ʖ��v
                                                              //�Ƃ��邱�Ƃɂ��A�`�����l���ԍ��������Ȃ�� new ����Ȃ��B
    if (_papSeConnection[prm_se_no]) {
        _TRACE_("GgafDxSeTransmitter::set() ���x���� ����ID="<<prm_se_no<<" �ɂ�SE("<<(_papSeConnection[prm_se_no]->getIdStr())<<")���ݒ�ς݂ł����B�����ڑ��� close ��A�V����SE("<<idstr<<")���㏑�����܂��B�Ӑ}���Ă܂����H");
        _papSeConnection[prm_se_no]->close();
    }
    _papSeConnection[prm_se_no] = connectToSeManager(idstr.c_str());
}


void GgafDxSeTransmitter::play(int prm_se_no) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_se_no="<<prm_se_no);
    }
#endif
    _papSeConnection[prm_se_no]->peek()->play();
}

void GgafDxSeTransmitter::stop(int prm_se_no) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::stop() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_se_no="<<prm_se_no);
    }
#endif
    _papSeConnection[prm_se_no]->peek()->stop();
}

void GgafDxSeTransmitter::setLooping(int prm_se_no, bool prm_can_looping) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::setLooping() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_se_no="<<prm_se_no);
    }
#endif
    _papSeConnection[prm_se_no]->peek()->setLooping(prm_can_looping);
}

GgafDxSe* GgafDxSeTransmitter::get(int prm_se_no) const {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() ID���͈͊O�ł��B0~"<<(_se_num-1)<<"�ł��肢���܂��Bprm_se_no="<<prm_se_no);
    }
#endif
    return _papSeConnection[prm_se_no]->peek();
}


GgafDxSeTransmitter::~GgafDxSeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_papSeConnection[i]) {
            _papSeConnection[i]->close();
        }
    }
    GGAF_DELETEARR_NULLABLE(_papSeConnection);
}

