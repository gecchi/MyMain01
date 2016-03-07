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

void GgafDxBgmPerformer::ready(int prm_channel, const char* prm_bgm_name) {
    if (prm_channel >= _bgm_num) {
        if (_bgm_num == 0) {
            //初回
            _bgm_num = prm_channel + 1;
            _papBgmConnection = NEW GgafDxBgmConnection*[_bgm_num];
            _pa_volume = NEW double[_bgm_num];
            for (int i = 0; i < _bgm_num; i++) {
                _papBgmConnection[i] = nullptr;
                _pa_volume[i] = GGAF_MAX_VOLUME;
            }
        } else {
            //拡張する。
            int old_bgm_num = _bgm_num;
            _bgm_num = prm_channel + 1;
            GgafDxBgmConnection** new_papBgmConnection = NEW GgafDxBgmConnection*[_bgm_num];
            double*               new_pa_volume  = NEW double[_bgm_num];
            for (int i = 0; i < old_bgm_num; i++) { //旧をコピー
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

    if (_papBgmConnection[prm_channel]) {
        _TRACE_("【警告】GgafDxBgmPerformer::set() IDが使用済みです、上書きしますが意図してますか？？。prm_channel="<<prm_channel<<" prm_bgm_name="<<prm_bgm_name);
        _papBgmConnection[prm_channel]->close();
    }
    _papBgmConnection[prm_channel] = connectToBgmManager(prm_bgm_name);
    _papBgmConnection[prm_channel]->peek()->stop(); //どこかのシーンで演奏中だったかももしれないので頭出しする・・・
}

void GgafDxBgmPerformer::play(int prm_channel, int prm_volume, bool prm_is_loop) {
#ifdef MY_DEBUG
    if (prm_channel < 0 || prm_channel >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_channel="<<prm_channel<<"");
    }
    if (_papBgmConnection[prm_channel] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_channel="<<prm_channel<<"");
    }
#endif
    _pa_volume[prm_channel] = (double)prm_volume;
    _papBgmConnection[prm_channel]->peek()->play(prm_volume, 0.0f, prm_is_loop);
//    GgafDxBgmPerformer::_active_bgm_bpm = _papBgmConnection[prm_channel]->peek()->_bpm; //最新のBGMのBPMリズム
}

void GgafDxBgmPerformer::stop(int prm_channel) {
#ifdef MY_DEBUG
    if (prm_channel < 0 || prm_channel >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_channel="<<prm_channel);
    }
    if (_papBgmConnection[prm_channel] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_channel="<<prm_channel<<"");
    }
#endif
    _papBgmConnection[prm_channel]->peek()->stop();
}

void GgafDxBgmPerformer::pause(int prm_channel) {
#ifdef MY_DEBUG
    if (prm_channel < 0 || prm_channel >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_channel="<<prm_channel);
    }
    if (_papBgmConnection[prm_channel] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_channel="<<prm_channel<<"");
    }
#endif
    _papBgmConnection[prm_channel]->peek()->pause();
}

void GgafDxBgmPerformer::pause() {
    for (int channel = 0; channel < _bgm_num; channel++) {
        pause(channel);
    }
}

void GgafDxBgmPerformer::unpause(int prm_channel) {
#ifdef MY_DEBUG
    if (prm_channel < 0 || prm_channel >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_channel="<<prm_channel);
    }
    if (_papBgmConnection[prm_channel] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_channel="<<prm_channel<<"");
    }
#endif
    _papBgmConnection[prm_channel]->peek()->unpause();
}

void GgafDxBgmPerformer::unpause() {
    for (int channel = 0; channel < _bgm_num; channel++) {
        unpause(channel);
    }
}

void GgafDxBgmPerformer::stop() {
    for (int channel = 0; channel < _bgm_num; channel++) {
        stop(channel);
    }
}

void GgafDxBgmPerformer::setVolume(int prm_channel, int prm_volume) {
    _pa_volume[prm_channel] = (double)prm_volume;
    _papBgmConnection[prm_channel]->peek()->setVolume(prm_volume);
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
