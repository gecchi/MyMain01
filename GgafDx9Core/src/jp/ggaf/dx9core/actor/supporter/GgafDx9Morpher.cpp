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
        _target_weight[i] = 0.0f;
        _top_weight[i] = 1.0f;
        _bottom_weight[i] = 0.0f;
        _halfloop_cnt[i] = 0;
        _loop_attack_frames[i] = 0;
        _loop_rest_framess[i] = 0;
        _frame_of_loop_begin[i] = 0;
        _loop_spend_frames[i] = 0;
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
        } if (_method[i] == TARGET_MORPH_ACCELERATION) {
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
            _weight[i] += _velo_weight[i];
            if (_frame_of_loop_begin[i] + _loop_spend_frames[i] == _pActor->_frame_of_behaving) { //ループ終了時
                _frame_of_loop_begin[i] = _pActor->_frame_of_behaving;
                _velo_weight[i] = (_top_weight[i] - _bottom_weight[i]) / (int)(_loop_attack_frames[i]);
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
                }
            } else if (_bottom_weight[i] > _weight[i]) {
                _weight[i] = _bottom_weight[i];
                _velo_weight[i] = 0.0f;

            } else if (_frame_of_loop_begin[i] + _loop_attack_frames[i] == _pActor->_frame_of_behaving) { //アタック頂点時
                _weight[i] = _top_weight[i];
                _velo_weight[i] = (_bottom_weight[i] - _top_weight[i]) / (int)(_loop_spend_frames[i] - _loop_attack_frames[i] - _loop_rest_framess[i]);
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
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

void GgafDx9Morpher::loopLiner(int prm_target_mesh, frame prm_loop_spend_frames, float prm_loop_num) {
    _method[prm_target_mesh] = LOOP_MORPH_LINER;
    _halfloop_cnt[prm_target_mesh] = 0;
    _stop_halfloop_num[prm_target_mesh] = (int)(prm_loop_num*2.0f);
    _velo_weight[prm_target_mesh] = 1.0f / ((int)prm_loop_spend_frames / 2);
}

void GgafDx9Morpher::loopTriangleWave(int prm_target_mesh, frame prm_loop_spend_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_loop_num) {
    _method[prm_target_mesh] = LOOP_MORPH_TRIANGLEWAVE;
    _halfloop_cnt[prm_target_mesh] = 0;
    _stop_halfloop_num[prm_target_mesh] = (int)(prm_loop_num*2.0f);

    _loop_attack_frames[prm_target_mesh] = prm_attack_frames;
    _loop_rest_framess[prm_target_mesh] = prm_rest_frames;
    _frame_of_loop_begin[prm_target_mesh] = _pActor->_frame_of_behaving;
    _loop_spend_frames[prm_target_mesh] = prm_loop_spend_frames;

    _velo_weight[prm_target_mesh] = (_top_weight[prm_target_mesh] - _weight[prm_target_mesh]) / (int)prm_attack_frames;
}
void GgafDx9Morpher::stopImmediately(int prm_target_mesh) {
    _method[prm_target_mesh] = NOMORPH;
}

GgafDx9Morpher::~GgafDx9Morpher() {
}
