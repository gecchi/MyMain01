#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Morpher::GgafDx9Morpher(GgafDx9MorphMeshActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;
    for (int i = 0; i <= MAX_MORPH_TARGET; i++) {
        //i=0は実質未使用。
        _weight[i] = 0.0f;
        _velo_weight[i] = 0.0f;
        _acce_weight[i] = 0.0f;
        _target_weight[i] = 0.0f;
        _top_weight[i] = 1.0f;
        _bottom_weight[i] = 0.0f;
        _halfloop_cnt[i] = 0;
        _beat_attack_frames[i] = 0;
        _beat_rest_frames[i] = 0;
        _frame_of_beat_begin[i] = 0;
        _beat_target_frames[i] = 0;
        _stop_halfloop_num[i] = -1;
        _method[i] = NOMORPH;
    }
}

void GgafDx9Morpher::behave() {
    for (int i = 1; i <= _pActor->_pMorphMeshModel->_morph_target_num; i++) {
        if (_method[i] == TARGET_MORPH_LINER) {
            _weight[i] += _velo_weight[i];
            if (_velo_weight[i] > 0 && _target_weight[i] < _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            } else if (_velo_weight[i] < 0 && _target_weight[i] > _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            }
        } else if (_method[i] == TARGET_MORPH_ACCELERATION) {
            _weight[i] += _velo_weight[i];
            if (_velo_weight[i] > 0 && _target_weight[i] < _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            } else if (_velo_weight[i] < 0 && _target_weight[i] > _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            }
            _velo_weight[i] += _acce_weight[i];
        } else if (_method[i] == LOOP_MORPH_LINER) {
            _weight[i] += _velo_weight[i];
            if (_top_weight[i] < _weight[i]) {
                _weight[i] = _top_weight[i];
                _velo_weight[i] = -1*_velo_weight[i];
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
                }
            } else if (_bottom_weight[i] > _weight[i]) {
                _weight[i] = _bottom_weight[i];
                _velo_weight[i] = -1*_velo_weight[i];
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
                }
            }
        } else if (_method[i] == LOOP_MORPH_TRIANGLEWAVE) {
            _beat_frame_count[i]++;
            if (_beat_progres[i] == 0) { //開始～アタックまで
                _weight[i] += _velo_weight[i];
                if (_beat_frame_count[i] >= _beat_attack_frames[i]) { //アタック時
                    _weight[i] = _top_weight[i];
                    _velo_weight[i] = (_bottom_weight[i] - _top_weight[i]) / float(_beat_down_frames[i]);
                    _halfloop_cnt[i]++; //半ループカウント＋１
                    if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                        _method[i] = NOMORPH;
                    }
                    _beat_progres[i] = 1; //次へ
                }
            } else if (_beat_progres[i] == 1) { //アタック～下限まで
                _weight[i] += _velo_weight[i];
                if (_beat_frame_count[i] >= _beat_attack_frames[i]+_beat_down_frames[i]) { //下限時
                    _weight[i] = _bottom_weight[i];
                    _velo_weight[i] = 0;
                    _beat_progres[i] = 2;//次へ
                }
            } else if (_beat_progres[i] == 2) { //下限～終了まで
                if (_beat_frame_count[i] >= _beat_target_frames[i]) { //終了時
                    _halfloop_cnt[i]++; //半ループカウント＋１
                    if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                        _method[i] = NOMORPH;
                    }
                    _velo_weight[i] = (_top_weight[i] - _weight[i]) / float(_beat_attack_frames[i]);
                    _beat_frame_count[i] = 0; //カウンタリセット
                    _beat_progres[i] = 0;//次へ(元に戻る)
                }
            }
        }
        _pActor->_weight[i] = this->_weight[i];
    }
}

void GgafDx9Morpher::intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, frame prm_spend_frame) {
    _method[prm_target_mesh] = TARGET_MORPH_LINER;
    _target_weight[prm_target_mesh] = prm_target_weight;
    _velo_weight[prm_target_mesh] = (prm_target_weight - _weight[prm_target_mesh]) / (int)(prm_spend_frame);
}

void GgafDx9Morpher::intoTargetAcceStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight, float prm_acce_weight) {
    _method[prm_target_mesh] = TARGET_MORPH_ACCELERATION;
    _target_weight[prm_target_mesh] = prm_target_weight;
    _velo_weight[prm_target_mesh] = prm_velo_weight;
    _acce_weight[prm_target_mesh] = prm_acce_weight;
}


void GgafDx9Morpher::intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight) {
    _method[prm_target_mesh] = TARGET_MORPH_LINER;
    _target_weight[prm_target_mesh] = prm_target_weight;
    _velo_weight[prm_target_mesh] = sgn(prm_target_weight - _weight[prm_target_mesh])*prm_velo_weight;
}

void GgafDx9Morpher::loopLiner(int prm_target_mesh, frame prm_beat_target_frames, float prm_beat_num) {
    _method[prm_target_mesh] = LOOP_MORPH_LINER;
    _halfloop_cnt[prm_target_mesh] = 0;
    _stop_halfloop_num[prm_target_mesh] = (int)(prm_beat_num*2.0f);
    _velo_weight[prm_target_mesh] = 1.0f / ((float)prm_beat_target_frames / 2.0f);
}

void GgafDx9Morpher::beat(int prm_target_mesh, frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    _method[prm_target_mesh] = LOOP_MORPH_TRIANGLEWAVE;

    _halfloop_cnt[prm_target_mesh] = 0;
    _stop_halfloop_num[prm_target_mesh] = (int)(prm_beat_num*2.0f);

    _beat_attack_frames[prm_target_mesh] = prm_attack_frames;
    _beat_rest_frames[prm_target_mesh] = prm_rest_frames;
    _beat_target_frames[prm_target_mesh] = prm_beat_target_frames;
    _beat_down_frames[prm_target_mesh] = _beat_target_frames[prm_target_mesh] - _beat_attack_frames[prm_target_mesh] - _beat_rest_frames[prm_target_mesh];
    _beat_frame_count[prm_target_mesh] = 0;

    //最初のアタックまでのvelo
    if (_beat_attack_frames[prm_target_mesh] > 0) {
        _velo_weight[prm_target_mesh] = (_top_weight[prm_target_mesh] - _weight[prm_target_mesh]) / float(_beat_attack_frames[prm_target_mesh]);
        _beat_progres[prm_target_mesh] = 0;
    } else { //アタックまでが無いの場合
        _weight[prm_target_mesh] = _top_weight[prm_target_mesh];
        _velo_weight[prm_target_mesh] = (_bottom_weight[prm_target_mesh] - _top_weight[prm_target_mesh]) / float(_beat_down_frames[prm_target_mesh]);
        _halfloop_cnt[prm_target_mesh]++; //半ループカウント＋１
        _beat_progres[prm_target_mesh] = 1;
    }
}
void GgafDx9Morpher::stopImmediately(int prm_target_mesh) {
    _method[prm_target_mesh] = NOMORPH;
}

GgafDx9Morpher::~GgafDx9Morpher() {
}
