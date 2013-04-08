#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorpher::GgafDxMorpher(GgafDxMorphMeshActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;
    reset();
}

void GgafDxMorpher::reset() {
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
        _pActor->_weight[i] = this->_weight[i];
    }
}

void GgafDxMorpher::behave() {
    int morph_target_num = _pActor->_pMorphMeshModel->_morph_target_num;
    GgafDxMorphingMethod method;
    for (int i = 1; i <= morph_target_num; i++) {
        method = _method[i];
        if (method ==TARGET_MORPH_LINER) {
            _weight[i] += _velo_weight[i];
            if (_velo_weight[i] > 0 && _target_weight[i] < _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            } else if (_velo_weight[i] < 0 && _target_weight[i] > _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            } else if (ZEROf_EQ(_velo_weight[i])) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            }
        } else if (method ==TARGET_MORPH_ACCELERATION) {
            _weight[i] += _velo_weight[i];
            if (_velo_weight[i] > 0 && _target_weight[i] < _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            } else if (_velo_weight[i] < 0 && _target_weight[i] > _weight[i]) {
                _weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            }
            _velo_weight[i] += _acce_weight[i];
        } else if (method ==LOOP_MORPH_LINER) {
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
        } else if (method ==LOOP_MORPH_TRIANGLEWAVE) {
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

void GgafDxMorpher::morphLinerUntil(int prm_target_mesh_no, float prm_target_weight, frame prm_spend_frame) {
    if (ZEROf_EQ(prm_target_weight - _weight[prm_target_mesh_no])) {
        //既にターゲットと同じ重み
        return;
    } else {
        _method[prm_target_mesh_no] = TARGET_MORPH_LINER;
        _target_weight[prm_target_mesh_no] = prm_target_weight;
        _velo_weight[prm_target_mesh_no] = (prm_target_weight - _weight[prm_target_mesh_no]) / (int)(prm_spend_frame);
    }
}

void GgafDxMorpher::morphAcceStep(int prm_target_mesh_no, float prm_target_weight, float prm_velo_weight, float prm_acce_weight) {
    _method[prm_target_mesh_no] = TARGET_MORPH_ACCELERATION;
    _target_weight[prm_target_mesh_no] = prm_target_weight;
    _velo_weight[prm_target_mesh_no] = prm_velo_weight;
    _acce_weight[prm_target_mesh_no] = prm_acce_weight;
}


void GgafDxMorpher::morphLinerStep(int prm_target_mesh_no, float prm_target_weight, float prm_velo_weight) {
#ifdef MY_DEBUG
    if (prm_velo_weight < 0) {
        throwGgafCriticalException("GgafDxMorpher::morphLinerStep() prm_velo_weightは正の値を設定して下さい。説明読んで。");
    }
#endif
    if (ZEROf_EQ(prm_target_weight - _weight[prm_target_mesh_no])) {
        //既にターゲットと同じ重み
        return;
    } else {
        _method[prm_target_mesh_no] = TARGET_MORPH_LINER;
        _target_weight[prm_target_mesh_no] = prm_target_weight;
        _velo_weight[prm_target_mesh_no] = SGN(prm_target_weight - _weight[prm_target_mesh_no])*prm_velo_weight;
    }
}

void GgafDxMorpher::loopLiner(int prm_target_mesh_no, frame prm_beat_target_frames, float prm_beat_num) {
    _method[prm_target_mesh_no] = LOOP_MORPH_LINER;
    _halfloop_cnt[prm_target_mesh_no] = 0;
    _stop_halfloop_num[prm_target_mesh_no] = (int)(prm_beat_num*2.0f);
    _velo_weight[prm_target_mesh_no] = 1.0f / ((float)prm_beat_target_frames / 2.0f);
}

void GgafDxMorpher::beat(int prm_target_mesh_no, frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    _method[prm_target_mesh_no] = LOOP_MORPH_TRIANGLEWAVE;

    _halfloop_cnt[prm_target_mesh_no] = 0;
    _stop_halfloop_num[prm_target_mesh_no] = (int)(prm_beat_num*2.0f);

    _beat_attack_frames[prm_target_mesh_no] = prm_attack_frames;
    _beat_rest_frames[prm_target_mesh_no] = prm_rest_frames;
    _beat_target_frames[prm_target_mesh_no] = prm_beat_target_frames;
    _beat_down_frames[prm_target_mesh_no] = _beat_target_frames[prm_target_mesh_no] - _beat_attack_frames[prm_target_mesh_no] - _beat_rest_frames[prm_target_mesh_no];
    _beat_frame_count[prm_target_mesh_no] = 0;

    //最初のアタックまでのvelo
    if (_beat_attack_frames[prm_target_mesh_no] > 0) {
        _velo_weight[prm_target_mesh_no] = (_top_weight[prm_target_mesh_no] - _weight[prm_target_mesh_no]) / float(_beat_attack_frames[prm_target_mesh_no]);
        _beat_progres[prm_target_mesh_no] = 0;
    } else { //アタックまでが無いの場合
        _weight[prm_target_mesh_no] = _top_weight[prm_target_mesh_no];
        _velo_weight[prm_target_mesh_no] = (_bottom_weight[prm_target_mesh_no] - _top_weight[prm_target_mesh_no]) / float(_beat_down_frames[prm_target_mesh_no]);
        _halfloop_cnt[prm_target_mesh_no]++; //半ループカウント＋１
        _beat_progres[prm_target_mesh_no] = 1;
    }
}

void GgafDxMorpher::stopImmed(int prm_target_mesh_no) {
    _method[prm_target_mesh_no] = NOMORPH;
}

bool GgafDxMorpher::isMorphing() {
    for (int i = 1; i <= _pActor->_pMorphMeshModel->_morph_target_num; i++) {
        if (_method[i] != NOMORPH) {
            return true;
        }
    }
    return false;
}

GgafDxMorpher::~GgafDxMorpher() {
}
