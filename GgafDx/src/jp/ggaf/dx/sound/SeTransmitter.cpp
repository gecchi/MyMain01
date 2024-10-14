#include "jp/ggaf/dx/sound/SeTransmitter.h"

#include "jp/ggaf/dx/manager/SeManager.h"
#include "jp/ggaf/dx/manager/SeConnection.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/Se.h"
#include <stdio.h>

using namespace GgafDx;

SeTransmitter::SeTransmitter() : GgafCore::Object() {
}

void SeTransmitter::set(t_se_id prm_se_id, const char* prm_se_key, int prm_cannel) {
    if (strlen(prm_se_key) > 128) {
        throwCriticalException("SE����ID�����߂��܂��B128�����ɗ}���ĉ������Bprm_se_key="<<prm_se_key);
    }
    std::string idstr =  XTOS(prm_cannel) + "," + prm_se_key; //�����R�l�N�V�����̎���ID���� �u�`�����l���ԍ� + "," + wave���ʖ��v
                                                              //�Ƃ��邱�Ƃɂ��A�`�����l���ԍ��������Ȃ�� new ����Ȃ��B
    if (_mapSeConnection[prm_se_id]) {
        _TRACE_("�y�x���z ����ID="<<prm_se_id<<" �ɂ�SE("<<(_mapSeConnection[prm_se_id]->getIdStr())<<")���ݒ�ς݂ł����B�����ڑ��� close ��A�V����SE("<<idstr<<")���㏑�����܂��B�Ӑ}���Ă܂����H");
        _mapSeConnection[prm_se_id]->close();
    }
    _mapSeConnection[prm_se_id] = connectToSeManager(idstr.c_str());
    _map_volume[prm_se_id] = GGAF_MAX_VOLUME;
    _map_pan[prm_se_id] = 0;
    stop(prm_se_id);
    setVolume(prm_se_id, _map_volume[prm_se_id]);
    setPan(prm_se_id, _map_pan[prm_se_id]);
}

void SeTransmitter::setVolume(t_se_id prm_se_id, double prm_volume) {
    _map_volume[prm_se_id] = prm_volume;
    getSe(prm_se_id)->setVolume((int)(_map_volume[prm_se_id]));
}

void SeTransmitter::setPan(t_se_id prm_se_id, float prm_pan) {
    _map_pan[prm_se_id] = prm_pan;
    getSe(prm_se_id)->setPan(_map_pan[prm_se_id]);
}

void SeTransmitter::play(t_se_id prm_se_id, bool prm_can_looping) {
#ifdef MY_DEBUG
    if (_mapSeConnection.find(prm_se_id) == _mapSeConnection.end()) {
        throwCriticalException("SeTransmitter::play() Se�ԍ������ݒ�ł��Bprm_se_id="<<prm_se_id);
    }
#endif
    Se* pSe = getSe(prm_se_id);
    pSe->setVolume(_map_volume[prm_se_id]);
    pSe->setPan(_map_pan[prm_se_id]);
    pSe->play(prm_can_looping);
}

void SeTransmitter::stop(t_se_id prm_se_id) {
#ifdef MY_DEBUG
    if (_mapSeConnection.find(prm_se_id) == _mapSeConnection.end()) {
        throwCriticalException("SeTransmitter::stop() Se�ԍ������ݒ�ł��Bprm_se_id="<<prm_se_id);
    }
#endif
    getSe(prm_se_id)->stop();
}

Se* SeTransmitter::getSe(t_se_id prm_se_id) {
#ifdef MY_DEBUG
    if (_mapSeConnection.find(prm_se_id) == _mapSeConnection.end()) {
        throwCriticalException("SeTransmitter::getSe() Se�ԍ������ݒ�ł��Bprm_se_id="<<prm_se_id);
    }
#endif
    SeConnection* pCon = _mapSeConnection[prm_se_id];
    if (pCon) {
        return pCon->peek();
    } else {
        throwCriticalException("_mapSeConnection������܂���Bprm_se_id="<<prm_se_id);
    }
}


SeTransmitter::~SeTransmitter() {
    for (std::map<t_se_id, SeConnection*>::iterator it = _mapSeConnection.begin(); it != _mapSeConnection.end(); ++it) {
        _mapSeConnection[it->first]->close();
    }
}

