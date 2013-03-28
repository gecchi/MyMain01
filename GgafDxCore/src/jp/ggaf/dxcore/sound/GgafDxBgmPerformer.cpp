#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

//int GgafDxBgmPerformer::_active_bgm_bpm = 120;


GgafDxBgmPerformer::GgafDxBgmPerformer() : GgafObject() {
    _bgm_num = 0;
    _paDouble_volume = nullptr;
    _papBgmConnection = nullptr;
}

void GgafDxBgmPerformer::useBgm(int prm_bgm_num) {
    _bgm_num = prm_bgm_num;
    _papBgmConnection = NEW GgafDxBgmConnection*[_bgm_num];
    _paDouble_volume = NEW double[_bgm_num];
    for (int i = 0; i < _bgm_num; i++) {
        _papBgmConnection[i] = nullptr;
        _paDouble_volume[i] = GGAF_MAX_VOLUME;
    }
}
void GgafDxBgmPerformer::set(int prm_id, const char* prm_bgm_name) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::set() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id<<" prm_bgm_name="<<prm_bgm_name);
    }
#endif
    if (_papBgmConnection[prm_id]) {
        _TRACE_("【警告】GgafDxBgmPerformer::set() IDが使用済みです、上書きしますが意図してますか？？。prm_id="<<prm_id<<" prm_bgm_name="<<prm_bgm_name);
        _papBgmConnection[prm_id]->close();
    }
    _papBgmConnection[prm_id] = connectToBgmManager(prm_bgm_name);
    _papBgmConnection[prm_id]->peek()->stop(); //どこかのシーンで演奏中だったかももしれないので頭出しする・・・
}

void GgafDxBgmPerformer::play(int prm_id, int prm_volume, bool prm_is_loop) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::play() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id<<"");
    }
#endif
    _paDouble_volume[prm_id] = (double)prm_volume;
    _papBgmConnection[prm_id]->peek()->play(prm_volume, 0.0f, prm_is_loop);
//    GgafDxBgmPerformer::_active_bgm_bpm = _papBgmConnection[prm_id]->peek()->_bpm; //最新のBGMのBPMリズム
}

void GgafDxBgmPerformer::stop(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::stop() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
#endif
    _papBgmConnection[prm_id]->peek()->stop();
}

void GgafDxBgmPerformer::pause(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::pause() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id);
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
        throwGgafCriticalException("GgafDxBgmPerformer::pause() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id);
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
    _paDouble_volume[prm_id] = (double)prm_volume;
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
    GGAF_DELETEARR_NULLABLE(_paDouble_volume);
}
