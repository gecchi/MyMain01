#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"

#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmPerformerForScene::GgafDxBgmPerformerForScene(GgafDxScene* prm_pDxScene) : GgafDxBgmPerformer() {
    _pDxScene = prm_pDxScene;
    _default_fade = 600;
}

void GgafDxBgmPerformerForScene::ready(int prm_bgm_no, const char* prm_bgm_name) {
    int bgm_num = _vec_is_fade.size();
    if (prm_bgm_no >= bgm_num) {
        for (int i = bgm_num; i <= prm_bgm_no; i++) {
            _vec_is_fade.push_back(false);
            _vec_is_fadeout_stop.push_back(true);
            _vec_target_volume.push_back(GGAF_MAX_VOLUME);
            _vec_inc_volume.push_back(0);
        }
    }
    GgafDxBgmPerformer::ready(prm_bgm_no, prm_bgm_name); //上位呼び出し
}

void GgafDxBgmPerformerForScene::fade(int prm_bgm_no, frame prm_frame, int prm_target_volume) {
    _vec_is_fade[prm_bgm_no] = true;
    _vec_target_volume[prm_bgm_no] = (double)prm_target_volume;
    _vec_inc_volume[prm_bgm_no] = (prm_target_volume - getVolume(prm_bgm_no)) / (double)prm_frame;
}

void GgafDxBgmPerformerForScene::fadein_f(int prm_bgm_no, frame prm_frame) {
    fade(prm_bgm_no, prm_frame, GGAF_MAX_VOLUME);
}

void GgafDxBgmPerformerForScene::play_fadein_f(int prm_bgm_no, frame prm_frame) {
    setVolume(prm_bgm_no, GGAF_MIN_VOLUME);
    play(prm_bgm_no, true);
    fadein_f(prm_bgm_no, prm_frame);
}

void GgafDxBgmPerformerForScene::fadeout_f(int prm_bgm_no, frame prm_frame) {
    fade(prm_bgm_no, prm_frame, GGAF_MIN_VOLUME);
    _vec_is_fadeout_stop[prm_bgm_no] = false;

//    if (_vecBgmConnection[prm_bgm_no]->peek()->isPlaying()) {
//
//    } else {
//        _TRACE_("＜警告＞GgafDxBgmPerformerForScene::fadeout_f("<<prm_bgm_no<<", "<<prm_frame<<") は、"
//                "再生されていないので、フェードアウトを無視しました。file_name="<<_vecBgmConnection[prm_bgm_no]->peek()->_ogg_file_name);
//    }
}

void GgafDxBgmPerformerForScene::fadeout_stop_f(int prm_bgm_no, frame prm_frame) {
    fade(prm_bgm_no, prm_frame, GGAF_MIN_VOLUME);
    _vec_is_fadeout_stop[prm_bgm_no] = true;

//    if (_vecBgmConnection[prm_bgm_no]->peek()->isPlaying()) {
//
//    } else {
//        _TRACE_("＜警告＞GgafDxBgmPerformerForScene::fadeout_stop_f("<<prm_bgm_no<<", "<<prm_frame<<") は、"
//                "再生されていないので、フェードアウトを無視しました。file_name="<<_vecBgmConnection[prm_bgm_no]->peek()->_ogg_file_name);
//    }
}

void GgafDxBgmPerformerForScene::fadein(int prm_bgm_no) {
    fadein_f(prm_bgm_no, _default_fade);
}
void GgafDxBgmPerformerForScene::play_fadein(int prm_bgm_no) {
    play_fadein_f(prm_bgm_no, _default_fade);
}
void GgafDxBgmPerformerForScene::fadeout(int prm_bgm_no) {
    fadeout_f(prm_bgm_no, _default_fade);
}
void GgafDxBgmPerformerForScene::fadeout_stop(int prm_bgm_no) {
    fadeout_stop_f(prm_bgm_no, _default_fade);
}

void GgafDxBgmPerformerForScene::play(int prm_bgm_no, bool prm_is_loop) {
    GgafDxBgmPerformer::play(prm_bgm_no, prm_is_loop); //上位呼び出し
    _vec_is_fade[prm_bgm_no] = false;
}
void GgafDxBgmPerformerForScene::behave() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        if (_vec_is_fade[bgm_no]) {
            //音量フェード
            addVolume(bgm_no, _vec_inc_volume[bgm_no]);
            if (_vec_inc_volume[bgm_no] > 0 && getVolume(bgm_no) >= _vec_target_volume[bgm_no]) {
                //増音フェード完了時
                setVolume(bgm_no, _vec_target_volume[bgm_no]);
                _vec_is_fade[bgm_no] = false;
            } else if (_vec_inc_volume[bgm_no] < 0 && getVolume(bgm_no) <= _vec_target_volume[bgm_no]) {
                //減音フェード完了時
                setVolume(bgm_no, _vec_target_volume[bgm_no]);
                _vec_is_fade[bgm_no] = false;
                if (_vec_is_fadeout_stop[bgm_no]) {
                    //減音フェード完了時に演奏停止
                    stop(bgm_no);
                }
            }
        }
    }
}

void GgafDxBgmPerformerForScene::fadeout_stop() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        fadeout_stop(bgm_no);
    }
}

GgafDxBgmPerformerForScene::~GgafDxBgmPerformerForScene() {

}
