#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

int GgafDx9BgmPerformer::_active_bgm_bpm = 120;


GgafDx9BgmPerformer::GgafDx9BgmPerformer() : GgafObject() {

    _bgm_num = 0;
    _papBgmCon = NULL;
    _pa_is_fade = NULL;
    _pa_now_volume = NULL;
    _pa_target_volume = NULL;
    _pa_inc_volume = NULL;
    _pa_is_fadeout_stop = NULL;
}
void GgafDx9BgmPerformer::useBgm(int prm_bgm_num) {
    _bgm_num = prm_bgm_num;
    _papBgmCon = NEW GgafDx9BgmConnection*[_bgm_num];
    _pa_is_fade = NEW bool[_bgm_num];
    _pa_is_fadeout_stop = NEW bool[_bgm_num];
    _pa_now_volume = NEW double[_bgm_num];
    _pa_target_volume = NEW double[_bgm_num];
    _pa_inc_volume = NEW double[_bgm_num];
    for (int i = 0; i < _bgm_num; i++) {
        _papBgmCon[i] = NULL;
        _pa_is_fade[i] = false;
        _pa_is_fadeout_stop[i] = true;
        _pa_now_volume[i] = GGAF_MAX_VOLUME;
        _pa_target_volume[i] = GGAF_MAX_VOLUME;
        _pa_inc_volume[i] = 0;
    }
}
void GgafDx9BgmPerformer::fade(int prm_id, frame prm_frame, int prm_target_volume) {
    _pa_is_fade[prm_id] = true;
    _pa_target_volume[prm_id] = (double)prm_target_volume;
    _pa_inc_volume[prm_id] = (prm_target_volume - _pa_now_volume[prm_id]) / (double)prm_frame;
}

void GgafDx9BgmPerformer::set(int prm_id, const char* prm_bgm_name) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDx9BgmPerformer::seteBGM() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
    _papBgmCon[prm_id] = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->connect(prm_bgm_name);
}

void GgafDx9BgmPerformer::play(int prm_id, int prm_volume, bool prm_is_loop) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDx9BgmPerformer::play() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
    _pa_now_volume[prm_id] = (double)prm_volume;
    _pa_is_fade[prm_id] = false;
    _papBgmCon[prm_id]->use()->play(prm_volume, 0.0f, prm_is_loop);
    GgafDx9BgmPerformer::_active_bgm_bpm = _papBgmCon[prm_id]->use()->_bpm; //最新のBGMのBPMリズム
}

void GgafDx9BgmPerformer::stop(int prm_id) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDx9BgmPerformer::stop() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
    _papBgmCon[prm_id]->use()->stop();
}

void GgafDx9BgmPerformer::pause(int prm_id) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDx9BgmPerformer::pause() IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
    _papBgmCon[prm_id]->use()->pause();
}

void GgafDx9BgmPerformer::behave() {
    for (int id = 0; id < _bgm_num; id++) {

        if (_pa_is_fade[id]) {
            _pa_now_volume[id] += _pa_inc_volume[id];
            _papBgmCon[id]->use()->setVolume(_pa_now_volume[id]);
            if (_pa_inc_volume[id] > 0 && _pa_now_volume[id] >= _pa_target_volume[id]) {
                //増音量時
                setVolume(id, (int)_pa_target_volume[id]);
                _pa_is_fade[id] = false;
            } else if (_pa_inc_volume[id] < 0 && _pa_now_volume[id] <= _pa_target_volume[id]) {
                //減音量時
                setVolume(id, (int)_pa_target_volume[id]);
                _pa_is_fade[id] = false;
                if (_pa_is_fadeout_stop[id]) {
                    stop(id);
                }
            }
        }

    }

}

void GgafDx9BgmPerformer::setVolume(int prm_id, int prm_volume) {
    _pa_now_volume[prm_id] = (double)prm_volume;
    _papBgmCon[prm_id]->use()->setVolume(prm_volume);
}
GgafDx9BgmPerformer::~GgafDx9BgmPerformer() {
    if (_papBgmCon) {
        for (int i = 0; i < _bgm_num; i++) {
            if (_papBgmCon[i]) {
                _papBgmCon[i]->close();
            }

        }
    }
    DELETEARR_POSSIBLE_NULL(_papBgmCon);
    DELETEARR_POSSIBLE_NULL(_pa_is_fade);
    DELETEARR_POSSIBLE_NULL(_pa_is_fadeout_stop);
    DELETEARR_POSSIBLE_NULL(_pa_now_volume);
    DELETEARR_POSSIBLE_NULL(_pa_target_volume);
    DELETEARR_POSSIBLE_NULL(_pa_inc_volume);
}
