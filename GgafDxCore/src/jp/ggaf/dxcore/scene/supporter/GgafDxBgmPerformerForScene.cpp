#include "stdafx.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"

#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmPerformerForScene::GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene) : GgafDxBgmPerformer() {
    _pDxScene = prm_pDxScene;
    _paBool_is_fade = nullptr;
    _paDouble_target_volume = nullptr;
    _paDouble_inc_volume = nullptr;
    _paBool_is_fadeout_stop = nullptr;
    _default_fade = 360;
}
void GgafDxBgmPerformerForScene::useBgm(int prm_bgm_num, frame prm_default_fade) {
    GgafDxBgmPerformer::useBgm(prm_bgm_num); //上位呼び出し
    _default_fade = prm_default_fade;
    _paBool_is_fade = NEW bool[_bgm_num];
    _paBool_is_fadeout_stop = NEW bool[_bgm_num];
    _paDouble_target_volume = NEW double[_bgm_num];
    _paDouble_inc_volume = NEW double[_bgm_num];
    for (int i = 0; i < _bgm_num; i++) {
        _paBool_is_fade[i] = false;
        _paBool_is_fadeout_stop[i] = true;
        _paDouble_target_volume[i] = GGAF_MAX_VOLUME;
        _paDouble_inc_volume[i] = 0;
    }
}
void GgafDxBgmPerformerForScene::fade(int prm_id, frame prm_frame, int prm_target_volume) {
    _paBool_is_fade[prm_id] = true;
    _paDouble_target_volume[prm_id] = (double)prm_target_volume;
    _paDouble_inc_volume[prm_id] = (prm_target_volume - _paDouble_volume[prm_id]) / (double)prm_frame;
}
void GgafDxBgmPerformerForScene::fadein_f(int prm_id, frame prm_frame) {
    fade(prm_id, prm_frame, GGAF_MAX_VOLUME);
}
void GgafDxBgmPerformerForScene::play_fadein_f(int prm_id, frame prm_frame) {
    play(prm_id, GGAF_MIN_VOLUME, true);
    fadein_f(prm_id, prm_frame);
}
void GgafDxBgmPerformerForScene::fadeout_f(int prm_id, frame prm_frame) {
    if (_papBgmConnection[prm_id]->peek()->isPlaying()) {
        fade(prm_id, prm_frame, GGAF_MIN_VOLUME);
        _paBool_is_fadeout_stop[prm_id] = false;
    } else {
        _TRACE_("＜警告＞GgafDxBgmPerformerForScene::fadeout_f("<<prm_id<<", "<<prm_frame<<") は、"<<
                "再生されていないので、フェードアウトを無視しました。file_name="<<_papBgmConnection[prm_id]->peek()->_ogg_file_name);
    }
}
void GgafDxBgmPerformerForScene::fadeout_stop_f(int prm_id, frame prm_frame) {
    if (_papBgmConnection[prm_id]->peek()->isPlaying()) {
        fade(prm_id, prm_frame, GGAF_MIN_VOLUME);
        _paBool_is_fadeout_stop[prm_id] = true;
    } else {
        _TRACE_("＜警告＞GgafDxBgmPerformerForScene::fadeout_stop_f("<<prm_id<<", "<<prm_frame<<") は、"<<
                "再生されていないので、フェードアウトを無視しました。file_name="<<_papBgmConnection[prm_id]->peek()->_ogg_file_name);
    }
}

void GgafDxBgmPerformerForScene::play(int prm_id, int prm_volume, bool prm_is_loop) {
    GgafDxBgmPerformer::play(prm_id, prm_volume, prm_is_loop); //上位呼び出し
    _paBool_is_fade[prm_id] = false;
}

void GgafDxBgmPerformerForScene::fadein(int prm_id) {
    fadein_f(prm_id, _default_fade);
}
void GgafDxBgmPerformerForScene::play_fadein(int prm_id) {
    play_fadein_f(prm_id, _default_fade);
}
void GgafDxBgmPerformerForScene::fadeout(int prm_id) {
    fadeout_f(prm_id, _default_fade);
}
void GgafDxBgmPerformerForScene::fadeout_stop(int prm_id) {
    fadeout_stop_f(prm_id, _default_fade);
}

void GgafDxBgmPerformerForScene::behave() {
    for (int id = 0; id < _bgm_num; id++) {
        if (_paBool_is_fade[id]) {
            //音量フェード
            _paDouble_volume[id] += _paDouble_inc_volume[id];
            if (_paDouble_inc_volume[id] > 0 && _paDouble_volume[id] >= _paDouble_target_volume[id]) {
                //増音フェード完了時
                _papBgmConnection[id]->peek()->setVolume(_paDouble_volume[id]);
                _paBool_is_fade[id] = false;
            } else if (_paDouble_inc_volume[id] < 0 && _paDouble_volume[id] <= _paDouble_target_volume[id]) {
                //減音フェード完了時
                _papBgmConnection[id]->peek()->setVolume(_paDouble_volume[id]);
                _paBool_is_fade[id] = false;
                if (_paBool_is_fadeout_stop[id]) {
                    stop(id);
                }
            } else {
                _papBgmConnection[id]->peek()->setVolume(_paDouble_volume[id]);
            }
        }
    }
}

void GgafDxBgmPerformerForScene::fadeout_stop() {
    for (int id = 0; id < _bgm_num; id++) {
        fadeout_stop(id);
    }
}

GgafDxBgmPerformerForScene::~GgafDxBgmPerformerForScene() {
    GGAF_DELETEARR_NULLABLE(_paBool_is_fade);
    GGAF_DELETEARR_NULLABLE(_paBool_is_fadeout_stop);
    GGAF_DELETEARR_NULLABLE(_paDouble_target_volume);
    GGAF_DELETEARR_NULLABLE(_paDouble_inc_volume);
}
