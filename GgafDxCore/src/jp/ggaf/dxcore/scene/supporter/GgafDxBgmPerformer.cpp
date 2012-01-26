#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

int GgafDxBgmPerformer::_active_bgm_bpm = 120;


GgafDxBgmPerformer::GgafDxBgmPerformer() : GgafObject() {

    _bgm_num = 0;
    _papBgmCon = NULL;
    _pa_is_fade = NULL;
    _pa_now_volume = NULL;
    _pa_target_volume = NULL;
    _pa_inc_volume = NULL;
    _pa_is_fadeout_stop = NULL;
}
void GgafDxBgmPerformer::useBgm(int prm_bgm_num) {
    _bgm_num = prm_bgm_num;
    _papBgmCon = NEW GgafDxBgmConnection*[_bgm_num];
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
void GgafDxBgmPerformer::fade(int prm_id, frame prm_frame, int prm_target_volume) {
    _pa_is_fade[prm_id] = true;
    _pa_target_volume[prm_id] = (double)prm_target_volume;
    _pa_inc_volume[prm_id] = (prm_target_volume - _pa_now_volume[prm_id]) / (double)prm_frame;
}

void GgafDxBgmPerformer::set(int prm_id, const char* prm_bgm_name) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::set() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id<<" prm_bgm_name="<<prm_bgm_name);
    }
    if (_papBgmCon[prm_id]) {
        _TRACE_("�y�x���zGgafDxBgmPerformer::set() ID���g�p�ς݂ł��A�㏑�����܂����Ӑ}���Ă܂����H�H�Bprm_id="<<prm_id<<" prm_bgm_name="<<prm_bgm_name);
        _papBgmCon[prm_id]->close();
    }
    _papBgmCon[prm_id] = (GgafDxBgmConnection*)GgafDxSound::_pBgmManager->connect(prm_bgm_name);
}

void GgafDxBgmPerformer::play(int prm_id, int prm_volume, bool prm_is_loop) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::play() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id<<"");
    }
    _pa_now_volume[prm_id] = (double)prm_volume;
    _pa_is_fade[prm_id] = false;
    _papBgmCon[prm_id]->use()->play(prm_volume, 0.0f, prm_is_loop);
    GgafDxBgmPerformer::_active_bgm_bpm = _papBgmCon[prm_id]->use()->_bpm; //�ŐV��BGM��BPM���Y��
}

void GgafDxBgmPerformer::stop(int prm_id) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::stop() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id);
    }
    _papBgmCon[prm_id]->use()->stop();
}

void GgafDxBgmPerformer::pause(int prm_id) {
    if (prm_id < 0 || prm_id >= _bgm_num) {
        throwGgafCriticalException("GgafDxBgmPerformer::pause() ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_id="<<prm_id);
    }
    _papBgmCon[prm_id]->use()->pause();
}

void GgafDxBgmPerformer::behave() {
    for (int id = 0; id < _bgm_num; id++) {

        if (_pa_is_fade[id]) {
            _pa_now_volume[id] += _pa_inc_volume[id];
            _papBgmCon[id]->use()->setVolume(_pa_now_volume[id]);
            if (_pa_inc_volume[id] > 0 && _pa_now_volume[id] >= _pa_target_volume[id]) {
                //�����ʎ�
                setVolume(id, (int)_pa_target_volume[id]);
                _pa_is_fade[id] = false;
            } else if (_pa_inc_volume[id] < 0 && _pa_now_volume[id] <= _pa_target_volume[id]) {
                //�����ʎ�
                setVolume(id, (int)_pa_target_volume[id]);
                _pa_is_fade[id] = false;
                if (_pa_is_fadeout_stop[id]) {
                    stop(id);
                }
            }
        }

    }

}

void GgafDxBgmPerformer::setVolume(int prm_id, int prm_volume) {
    _pa_now_volume[prm_id] = (double)prm_volume;
    _papBgmCon[prm_id]->use()->setVolume(prm_volume);
}
GgafDxBgmPerformer::~GgafDxBgmPerformer() {
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
