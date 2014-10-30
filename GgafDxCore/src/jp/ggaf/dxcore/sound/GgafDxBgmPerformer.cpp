#include "jp/ggaf/dxcore/sound/GgafDxBgmPerformer.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

//int GgafDxBgmPerformer::_active_bgm_bpm = 120;

GgafDxBgmPerformer::GgafDxBgmPerformer() : GgafObject() {
    _bgm_num = 0;
    _pa_volume = nullptr;
    _papBgmConnection = nullptr;
}

void GgafDxBgmPerformer::ready(int prm_id, const char* prm_bgm_name) {
    if (prm_id >= _bgm_num) {
        if (_bgm_num == 0) {
            //����
            _bgm_num = prm_id + 1;
            _papBgmConnection = NEW GgafDxBgmConnection*[_bgm_num];
            _pa_volume = NEW double[_bgm_num];
            for (int i = 0; i < _bgm_num; i++) {
                _papBgmConnection[i] = nullptr;
                _pa_volume[i] = GGAF_MAX_VOLUME;
            }
        } else {
            //�g������B
            int old_bgm_num = _bgm_num;
            _bgm_num = prm_id + 1;
            GgafDxBgmConnection** new_papBgmConnection = NEW GgafDxBgmConnection*[_bgm_num];
            double*               new_pa_volume  = NEW double[_bgm_num];
            for (int i = 0; i < old_bgm_num; i++) { //�����R�s�[
                new_papBgmConnection[i] = _papBgmConnection[i];
                new_pa_volume[i]  = _pa_volume[i];
            }
            for (int i = old_bgm_num; i < _bgm_num; i++) {
                new_papBgmConnection[i] = nullptr;
                new_pa_volume[i]  = GGAF_MAX_VOLUME;
            }
            GGAF_DELETEARR_NULLABLE(_papBgmConnection);
            GGAF_DELETEARR_NULLABLE(_pa_volume);
            _papBgmConnection = new_papBgmConnection;
            _pa_volume  = new_pa_volume;
        }
    }

    if (_papBgmConnection[prm_id]) {
        _DTRACE_("�y�x���zGgafDxBgmPerformer::set() ID���g�p�ς݂ł��A�㏑�����܂����Ӑ}���Ă܂����H�H�Bprm_id="<<prm_id<<" prm_bgm_name="<<prm_bgm_name);
        _papBgmConnection[prm_id]->close();
    }
    _papBgmConnection[prm_id] = getConnection_BgmManager(prm_bgm_name);
    _papBgmConnection[prm_id]->peek()->stop(); //�ǂ����̃V�[���ŉ��t������������������Ȃ��̂œ��o������E�E�E
}

void GgafDxBgmPerformer::play(int prm_id, int prm_volume, bool prm_is_loop) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::play() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id<<"");
    }
    if (_papBgmConnection[prm_id] == nullptr) {
        throwGgafCriticalException("GgafDxBgmPerformer::play() �Ȃ��Z�b�g����Ă܂���Bprm_id="<<prm_id<<"");
    }
#endif
    _pa_volume[prm_id] = (double)prm_volume;
    _papBgmConnection[prm_id]->peek()->play(prm_volume, 0.0f, prm_is_loop);
//    GgafDxBgmPerformer::_active_bgm_bpm = _papBgmConnection[prm_id]->peek()->_bpm; //�ŐV��BGM��BPM���Y��
}

void GgafDxBgmPerformer::stop(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::stop() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id);
    }
    if (_papBgmConnection[prm_id] == nullptr) {
        throwGgafCriticalException("GgafDxBgmPerformer::stop() �Ȃ��Z�b�g����Ă܂���Bprm_id="<<prm_id<<"");
    }
#endif
    _papBgmConnection[prm_id]->peek()->stop();
}

void GgafDxBgmPerformer::pause(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::pause() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id);
    }
    if (_papBgmConnection[prm_id] == nullptr) {
        throwGgafCriticalException("GgafDxBgmPerformer::pause() �Ȃ��Z�b�g����Ă܂���Bprm_id="<<prm_id<<"");
    }
#endif
    _papBgmConnection[prm_id]->peek()->pause();
}

void GgafDxBgmPerformer::pause() {
    for (int id = 0; id < _bgm_num; id++) {
        pause(id);
    }
}

void GgafDxBgmPerformer::unpause(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::unpause() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id);
    }
    if (_papBgmConnection[prm_id] == nullptr) {
        throwGgafCriticalException("GgafDxBgmPerformer::unpause() �Ȃ��Z�b�g����Ă܂���Bprm_id="<<prm_id<<"");
    }
#endif
    _papBgmConnection[prm_id]->peek()->unpause();
}

void GgafDxBgmPerformer::unpause() {
    for (int id = 0; id < _bgm_num; id++) {
        unpause(id);
    }
}

void GgafDxBgmPerformer::stop() {
    for (int id = 0; id < _bgm_num; id++) {
        stop(id);
    }
}

void GgafDxBgmPerformer::setVolume(int prm_id, int prm_volume) {
    _pa_volume[prm_id] = (double)prm_volume;
    _papBgmConnection[prm_id]->peek()->setVolume(prm_volume);
}
GgafDxBgmPerformer::~GgafDxBgmPerformer() {
    if (_papBgmConnection) {
        for (int i = 0; i < _bgm_num; i++) {
            if (_papBgmConnection[i]) {
                _papBgmConnection[i]->close();
            }

        }
    }
    GGAF_DELETEARR_NULLABLE(_papBgmConnection);
    GGAF_DELETEARR_NULLABLE(_pa_volume);
}
