#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSeTransmitter::GgafDxSeTransmitter() : GgafObject() {
    _se_num = 0;
    _papSeCon = nullptr;
}

void GgafDxSeTransmitter::declareSeNum(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeCon = NEW GgafDxSeConnection*[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeCon[i] = nullptr;
    }
}

void GgafDxSeTransmitter::set(int prm_id, const char* prm_se_key, int prm_cannel) {

//    if (_se_num <= 0) {
//        throwGgafCriticalException("GgafDxSeTransmitter::set() useSe�Ŏg�p����Se�������O�ɐ錾���Ă��������Bprm_id="<<prm_id);
//    }
    if (_papSeCon == nullptr) {
        declareSeNum(prm_id+1); //declareSeNum���Ȃ��ꍇ��prm_id+1�܂�
    }
    if (prm_id < 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() ID���͈͊O�ł��B���̐��ł��肢���܂��B prm_id="<<prm_id);
    } else if (prm_id >= _se_num) {
        //_papSeCon[] ���g������B
        GgafDxSeConnection** papSeCon = NEW GgafDxSeConnection*[_se_num];
        for (int i = 0; i < _se_num; i++) { //�ޔ�
            papSeCon[i] = _papSeCon[i];
        }
        DELETEARR_POSSIBLE_NULL(_papSeCon);
        int wk_se_num = _se_num;
        declareSeNum(prm_id+1); //prm_id+1 �֌g���B���̎��_�� _se_num �� prm_id+1 �ōX�V�����
        for (int i = 0; i < wk_se_num; i++) { //�����p���i�ޔ���߂��j
            _papSeCon[i] = papSeCon[i];
        }
        DELETEARR_POSSIBLE_NULL(papSeCon);
    }
    if (strlen(prm_se_key) > 128) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() SE����ID�����߂��܂��B128�����ɗ}���ĉ������Bprm_se_key="<<prm_se_key);
    }
    char idstr[140];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_key); //�����R�l�N�V�����̎���ID���� �u�`�����l���ԍ� + "/" + wave���ʖ��v
                                                      //�Ƃ��邱�Ƃɂ��A�`�����l���ԍ��������Ȃ�� new ����Ȃ��B
    if (_papSeCon[prm_id]) {
        _TRACE_("GgafDxSeTransmitter::set() ���x���� ����ID="<<prm_id<<" �ɂ�SE("<<(_papSeCon[prm_id]->getIdStr())<<")���ݒ�ς݂ł����B�����ڑ��� close ��A�V����SE("<<idstr<<")���㏑�����܂��B�Ӑ}���Ă܂����H");
        _papSeCon[prm_id]->close();
    }
    _papSeCon[prm_id] = connectToSeManager(idstr);
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

