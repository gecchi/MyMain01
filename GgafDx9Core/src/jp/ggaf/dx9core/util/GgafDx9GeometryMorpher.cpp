#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9GeometryMorpher::GgafDx9GeometryMorpher(GgafDx9MorphMeshActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;
    for (int i = 0; i < 10; i++) {
        _velo_weight[i] = 0.0;
        _target_weight[i] = 0.0;
        _top_weight[i] = 1.0;
        _bottom_weight[i] = 0.0;
        _halfloop_cnt[i] = 0;
        _loop_attack_frame[i] = 0;
        _loop_rest_frame[i] = 0;
        _loop_begin_frame[i] = 0;
        _loop_spend_frame[i] = 0;
        _stop_halfloop_num[i] = -1;
        _method[i] = NOMORPH;
    }
}

void GgafDx9GeometryMorpher::behave() {
    for (int i = 1; i <= _pActor->_pMorphMeshModel->_morph_target_num; i++) {
        if (_method[i] == TARGET_LINER) {
            _pActor->_weight[i] += _velo_weight[i];
            if (_velo_weight[i] > 0 && _target_weight[i] < _pActor->_weight[i]) {
                _pActor->_weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            } else if (_velo_weight[i] < 0 && _target_weight[i] > _pActor->_weight[i]) {
                _pActor->_weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            }
        } if (_method[i] == TARGET_ACCELERATION) {
            _pActor->_weight[i] += _velo_weight[i];
            if (_velo_weight[i] > 0 && _target_weight[i] < _pActor->_weight[i]) {
                _pActor->_weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            } else if (_velo_weight[i] < 0 && _target_weight[i] > _pActor->_weight[i]) {
                _pActor->_weight[i] = _target_weight[i];
                _method[i] = NOMORPH;
            }
            _velo_weight[i] += _acce_weight[i];
        } else if (_method[i] == LOOP_LINER) {
            _pActor->_weight[i] += _velo_weight[i];
            if (_top_weight[i] < _pActor->_weight[i]) {
                _pActor->_weight[i] = _top_weight[i];
                _velo_weight[i] = -1*_velo_weight[i];
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
                }
            } else if (_bottom_weight[i] > _pActor->_weight[i]) {
                _pActor->_weight[i] = _bottom_weight[i];
                _velo_weight[i] = -1*_velo_weight[i];
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
                }
            }
        } else if (_method[i] == LOOP_TRIANGLEWAVE) {
            _pActor->_weight[i] += _velo_weight[i];
            if (_loop_begin_frame[i] + _loop_attack_frame[i] == _pActor->_lifeframe) { //アタック頂点時
                _pActor->_weight[i] = _top_weight[i];
                _velo_weight[i] = (_bottom_weight[i] - _top_weight[i]) / (_loop_spend_frame[i] - _loop_attack_frame[i] - _loop_rest_frame[i]);
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
                }

            } else if (_bottom_weight[i] > _pActor->_weight[i]) {
                _pActor->_weight[i] = _bottom_weight[i];
                _velo_weight[i] = 0.0;

            } else if (_loop_begin_frame[i] + _loop_spend_frame[i] == _pActor->_lifeframe) { //ループ終了時
                _loop_begin_frame[i] = _pActor->_lifeframe;
                _velo_weight[i] = (_top_weight[i] - _bottom_weight[i]) / _loop_attack_frame[i];
                _halfloop_cnt[i]++;
                if (_halfloop_cnt[i] == _stop_halfloop_num[i]) {
                    _method[i] = NOMORPH;
                }
            }
        }
    }
}

void GgafDx9GeometryMorpher::intoTargetLinerUntil(int prm_target_mesh, float prm_target_weight, DWORD prm_spend_frame) {
    _method[prm_target_mesh] = TARGET_LINER;
    _target_weight[prm_target_mesh] = prm_target_weight;
    _velo_weight[prm_target_mesh] = (prm_target_weight - _pActor->_weight[prm_target_mesh])/prm_spend_frame;
}

void GgafDx9GeometryMorpher::intoTargetAccelerationStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight, float prm_acce_weight) {
    _method[prm_target_mesh] = TARGET_ACCELERATION;
    _target_weight[prm_target_mesh] = prm_target_weight;
    _velo_weight[prm_target_mesh] = prm_velo_weight;
    _acce_weight[prm_target_mesh] = prm_acce_weight;
}


void GgafDx9GeometryMorpher::intoTargetLinerStep(int prm_target_mesh, float prm_target_weight, float prm_velo_weight) {
    _method[prm_target_mesh] = TARGET_LINER;
    _target_weight[prm_target_mesh] = prm_target_weight;
    _velo_weight[prm_target_mesh] = sgn(prm_target_weight - _pActor->_weight[prm_target_mesh])*prm_velo_weight;
}

void GgafDx9GeometryMorpher::loopLiner(int prm_target_mesh, DWORD prm_loop_spend_frame, float prm_loop_num) {
    _method[prm_target_mesh] = LOOP_LINER;
    _halfloop_cnt[prm_target_mesh] = 0;
    _stop_halfloop_num[prm_target_mesh] = (int)(prm_loop_num*2.0);
    _velo_weight[prm_target_mesh] = 1.0 / (prm_loop_spend_frame / 2);
}

void GgafDx9GeometryMorpher::loopTriangleWave(int prm_target_mesh, DWORD prm_loop_spend_frame, DWORD prm_attack_frame, DWORD prm_rest_frame, float prm_loop_num) {
    _method[prm_target_mesh] = LOOP_TRIANGLEWAVE;
    _halfloop_cnt[prm_target_mesh] = 0;
    _stop_halfloop_num[prm_target_mesh] = (int)(prm_loop_num*2.0);

    _loop_attack_frame[prm_target_mesh] = prm_attack_frame;
    _loop_rest_frame[prm_target_mesh] = prm_rest_frame;
    _loop_begin_frame[prm_target_mesh] = _pActor->_lifeframe;
    _loop_spend_frame[prm_target_mesh] = prm_loop_spend_frame;

    _velo_weight[prm_target_mesh] = (_top_weight[prm_target_mesh] - _pActor->_weight[prm_target_mesh]) / prm_attack_frame;
}
void GgafDx9GeometryMorpher::stopImmediately(int prm_target_mesh) {
    _method[prm_target_mesh] = NOMORPH;
}

GgafDx9GeometryMorpher::~GgafDx9GeometryMorpher() {
}
