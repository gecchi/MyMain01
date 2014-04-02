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

void GgafDxBgmPerformerForScene::ready(int prm_id, const char* prm_bgm_name) {
    if (prm_id >= _bgm_num) {
        if (_bgm_num == 0) {
            //����
            int new_bgm_num = prm_id + 1;
            _paBool_is_fade = NEW bool[new_bgm_num];
            _paBool_is_fadeout_stop = NEW bool[new_bgm_num];
            _paDouble_target_volume = NEW double[new_bgm_num];
            _paDouble_inc_volume = NEW double[new_bgm_num];
            for (int i = 0; i < new_bgm_num; i++) {
                _paBool_is_fade[i] = false;
                _paBool_is_fadeout_stop[i] = true;
                _paDouble_target_volume[i] = GGAF_MAX_VOLUME;
                _paDouble_inc_volume[i] = 0;
            }
        } else {
            //�g������B
            int old_bgm_num = _bgm_num;
            int new_bgm_num = prm_id + 1;
            bool* new_paBool_is_fade = NEW bool[new_bgm_num];
            bool* new_paBool_is_fadeout_stop = NEW bool[new_bgm_num];
            double* new_paDouble_target_volume = NEW double[new_bgm_num];
            double* new_paDouble_inc_volume = NEW double[new_bgm_num];
            for (int i = 0; i < old_bgm_num; i++) { //�����R�s�[
                new_paBool_is_fade[i] = _paBool_is_fade[i];
                new_paBool_is_fadeout_stop[i] = _paBool_is_fadeout_stop[i];
                new_paDouble_target_volume[i] = _paDouble_target_volume[i];
                new_paDouble_inc_volume[i]    = _paDouble_inc_volume[i];
            }
            for (int i = old_bgm_num; i < new_bgm_num; i++) {
                new_paBool_is_fade[i] = false;
                new_paBool_is_fadeout_stop[i] = true;
                new_paDouble_target_volume[i] = GGAF_MAX_VOLUME;
                new_paDouble_inc_volume[i] = 0;
            }
            GGAF_DELETEARR_NULLABLE(_paBool_is_fade);
            GGAF_DELETEARR_NULLABLE(_paBool_is_fadeout_stop);
            GGAF_DELETEARR_NULLABLE(_paDouble_target_volume);
            GGAF_DELETEARR_NULLABLE(_paDouble_inc_volume);
            _paBool_is_fade = new_paBool_is_fade;
            _paBool_is_fadeout_stop = new_paBool_is_fadeout_stop;
            _paDouble_target_volume = new_paDouble_target_volume;
            _paDouble_inc_volume = new_paDouble_inc_volume;
        }
    }
    GgafDxBgmPerformer::ready(prm_id, prm_bgm_name); //��ʌĂяo��
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
        _TRACE_("���x����GgafDxBgmPerformerForScene::fadeout_f("<<prm_id<<", "<<prm_frame<<") �́A"<<
                "�Đ�����Ă��Ȃ��̂ŁA�t�F�[�h�A�E�g�𖳎����܂����Bfile_name="<<_papBgmConnection[prm_id]->peek()->_ogg_file_name);
    }
}
void GgafDxBgmPerformerForScene::fadeout_stop_f(int prm_id, frame prm_frame) {
    if (_papBgmConnection[prm_id]->peek()->isPlaying()) {
        fade(prm_id, prm_frame, GGAF_MIN_VOLUME);
        _paBool_is_fadeout_stop[prm_id] = true;
    } else {
        _TRACE_("���x����GgafDxBgmPerformerForScene::fadeout_stop_f("<<prm_id<<", "<<prm_frame<<") �́A"<<
                "�Đ�����Ă��Ȃ��̂ŁA�t�F�[�h�A�E�g�𖳎����܂����Bfile_name="<<_papBgmConnection[prm_id]->peek()->_ogg_file_name);
    }
}

void GgafDxBgmPerformerForScene::play(int prm_id, int prm_volume, bool prm_is_loop) {
    GgafDxBgmPerformer::play(prm_id, prm_volume, prm_is_loop); //��ʌĂяo��
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
            //���ʃt�F�[�h
            _paDouble_volume[id] += _paDouble_inc_volume[id];
            if (_paDouble_inc_volume[id] > 0 && _paDouble_volume[id] >= _paDouble_target_volume[id]) {
                //�����t�F�[�h������
                _papBgmConnection[id]->peek()->setVolume(_paDouble_volume[id]);
                _paBool_is_fade[id] = false;
            } else if (_paDouble_inc_volume[id] < 0 && _paDouble_volume[id] <= _paDouble_target_volume[id]) {
                //�����t�F�[�h������
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
