#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9GeometryScaler::GgafDx9GeometryScaler(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

    for (int axis = 0; axis < 3; axis++) {
        _scale[axis] = LEN_UNIT;
        _velo_scale[axis] = 0;
        _target_scale[axis] = LEN_UNIT;
        _top_scale[axis] = LEN_UNIT*1000;
        _bottom_scale[axis] = LEN_UNIT;
        _one_way_cnt[axis] = 0;
        _beat_attack_frame[axis] = 0;
        _beat_rest_frame[axis] = 0;
        _beat_begin_frame[axis] = 0;
        _beat_spend_frame[axis] = 0;
        _stop_one_way_num[axis] = -1;
        _method[axis] = NOSCALE;
    }


}

void GgafDx9GeometryScaler::behave() {
    for (int axis = 0; axis < 3; axis++) {
        if (_method[axis] == NOSCALE) {
            continue;
        } else if (_method[axis] == TARGET_SCALE_LINER) {
            _scale[axis] += _velo_scale[axis];
            if (_velo_scale[axis] > 0 && _target_scale[axis] <= _scale[axis]) {
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            } else if (_velo_scale[axis] < 0 && _target_scale[axis] >= _scale[axis]) {
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            }
        } if (_method[axis] == TARGET_SCALE_ACCELERATION) {
            _scale[axis] += _velo_scale[axis];
            if (_velo_scale[axis] > 0 && _target_scale[axis] <= _scale[axis]) {
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            } else if (_velo_scale[axis] < 0 && _target_scale[axis] >= _scale[axis]) {
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            }
            _velo_scale[axis] += _acce_scale[axis];
        } else if (_method[axis] == BEAT_SCALE_LINER) {
            _scale[axis] += _velo_scale[axis];
            if (_top_scale[axis] <= _scale[axis]) {
                _scale[axis] = _top_scale[axis];
                _velo_scale[axis] = -2 * (int)(_top_scale[axis] - _bottom_scale[axis]) / (int)(_beat_spend_frame[axis]);
                _one_way_cnt[axis]++;
                if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                    _method[axis] = NOSCALE;
                }
            } else if (_bottom_scale[axis] >= _scale[axis]) {
                _scale[axis] = _bottom_scale[axis];
                _velo_scale[axis] = 2 * (int)(_top_scale[axis] - _bottom_scale[axis]) / (int)(_beat_spend_frame[axis]);
                _one_way_cnt[axis]++;
                if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                    _method[axis] = NOSCALE;
                }
            }
//_TRACE_("_bottom_scale["<<axis<<"]="<<_bottom_scale[axis]);
//_TRACE_("_top_scale["<<axis<<"]="<<_top_scale[axis]);
//_TRACE_("_beat_spend_frame["<<axis<<"]="<<_beat_spend_frame[axis]);
//_TRACE_("_beat_attack_frame["<<axis<<"]="<<_beat_attack_frame[axis]);
//_TRACE_("_beat_rest_frame["<<axis<<"]="<<_beat_rest_frame[axis]);
//_TRACE_("_beat_spend_frame["<<axis<<"] - _beat_attack_frame["<<axis<<"] - _beat_rest_frame["<<axis<<"]) = " << (_beat_spend_frame[axis] - _beat_attack_frame[axis] - _beat_rest_frame[axis]));
//_TRACE_("(_bottom_scale["<<axis<<"] - _top_scale["<<axis<<"]) / (_beat_spend_frame["<<axis<<"] - _beat_attack_frame["<<axis<<"] - _beat_rest_frame["<<axis<<"])="<<((int)(_bottom_scale[axis] - _top_scale[axis]) / (int)(_beat_spend_frame[axis] - _beat_attack_frame[axis] - _beat_rest_frame[axis])));
//_TRACE_("_bottom_scale["<<axis<<"] - _top_scale["<<axis<<"]" << (_bottom_scale[axis] - _top_scale[axis]));
//_TRACE_("11_scale["<<axis<<"] _velo_scale["<<axis<<"]="<<_scale[axis]<<" "<<_velo_scale[axis]);

        } else if (_method[axis] == BEAT_SCALE_TRIANGLEWAVE) {
            _scale[axis] += _velo_scale[axis];
            if (_beat_begin_frame[axis] + _beat_attack_frame[axis] <= _pActor->_lifeframe) { //アタック頂点時
                _scale[axis] = _top_scale[axis];
                _velo_scale[axis] = ((int)(_bottom_scale[axis] - _top_scale[axis])) / ((int)(_beat_spend_frame[axis] - _beat_attack_frame[axis] - _beat_rest_frame[axis]));
                _one_way_cnt[axis]++;
                if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                    _method[axis] = NOSCALE;
                }

            } else if (_bottom_scale[axis] >= _scale[axis]) {
                _scale[axis] = _bottom_scale[axis];
                _velo_scale[axis] = 0;

            } else if (_beat_begin_frame[axis] + _beat_spend_frame[axis] <= _pActor->_lifeframe) { //ループ終了時
                _beat_begin_frame[axis] = _pActor->_lifeframe;
                _velo_scale[axis] = ((int)(_top_scale[axis] - _bottom_scale[axis])) / _beat_attack_frame[axis];
                _one_way_cnt[axis]++;
                if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                    _method[axis] = NOSCALE;
                }
            }
        }
    }
    //Actorに反映
    _pActor->_SX = _scale[AXIS_X];
    _pActor->_SY = _scale[AXIS_Y];
    _pActor->_SZ = _scale[AXIS_Z];
}

void GgafDx9GeometryScaler::intoTargetScaleLinerUntil(int prm_target_scale, DWORD prm_spend_frame) {
    for (int axis = 0; axis < 3; axis++) {
        intoTargetScaleLinerUntil(axis, prm_target_scale, prm_spend_frame);
    }
}

void GgafDx9GeometryScaler::intoTargetScaleLinerUntil(int prm_axis, int prm_target_scale, DWORD prm_spend_frame) {
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = (prm_target_scale - _scale[prm_axis])/prm_spend_frame;
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = prm_target_scale - _scale[prm_axis];
    }
}

void GgafDx9GeometryScaler::intoTargetScaleAccelerationStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale) {
    for (int axis = 0; axis < 3; axis++) {
        intoTargetScaleAccelerationStep(axis, prm_target_scale, prm_velo_scale, prm_acce_scale);
    }
}

void GgafDx9GeometryScaler::intoTargetScaleAccelerationStep(int prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale) {
    _method[prm_axis] = TARGET_SCALE_ACCELERATION;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = prm_velo_scale;
    _acce_scale[prm_axis] = prm_acce_scale;
}

void GgafDx9GeometryScaler::intoTargetScaleLinerStep(int prm_target_scale, int prm_velo_scale) {
    for (int axis = 0; axis < 3; axis++) {
        intoTargetScaleLinerStep(axis, prm_target_scale, prm_velo_scale);
    }
}

void GgafDx9GeometryScaler::intoTargetScaleLinerStep(int prm_axis, int prm_target_scale, int prm_velo_scale) {
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = sgn(prm_target_scale - _scale[prm_axis])*prm_velo_scale;
}


void GgafDx9GeometryScaler::beatLiner(DWORD prm_beat_spend_frame, float prm_beat_num) {
    for (int axis = 0; axis < 3; axis++) {
        beatLiner(axis, prm_beat_spend_frame, prm_beat_num);
    }
}

void GgafDx9GeometryScaler::beatLiner(int prm_axis, DWORD prm_beat_spend_frame, float prm_beat_num) {
    _method[prm_axis] = BEAT_SCALE_LINER;
    _one_way_cnt[prm_axis] = 0;
    _stop_one_way_num[prm_axis] = (int)(prm_beat_num*2.0f);
    _beat_spend_frame[prm_axis] = prm_beat_spend_frame;
    _velo_scale[prm_axis] = (int)(_top_scale[prm_axis] - _scale[prm_axis]) / (prm_beat_spend_frame / 2);
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = _top_scale[prm_axis] - _scale[prm_axis];
    }
}

void GgafDx9GeometryScaler::beat(DWORD prm_beat_spend_frame, DWORD prm_attack_frame, DWORD prm_rest_frame, float prm_beat_num) {
    for (int axis = 0; axis < 3; axis++) {
        beat(axis, prm_beat_spend_frame, prm_attack_frame, prm_rest_frame, prm_beat_num);
    }
}


void GgafDx9GeometryScaler::beat(int prm_axis, DWORD prm_beat_spend_frame, DWORD prm_attack_frame, DWORD prm_rest_frame, float prm_beat_num) {
    _method[prm_axis] = BEAT_SCALE_TRIANGLEWAVE;
    _one_way_cnt[prm_axis] = 0;
    _stop_one_way_num[prm_axis] = (int)(prm_beat_num*2.0f);

    _beat_attack_frame[prm_axis] = prm_attack_frame;
    _beat_rest_frame[prm_axis] = prm_rest_frame;
    _beat_begin_frame[prm_axis] = _pActor->_lifeframe;
    _beat_spend_frame[prm_axis] = prm_beat_spend_frame;

    _velo_scale[prm_axis] = (int)(_top_scale[prm_axis] - _scale[prm_axis]) / prm_attack_frame;
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = _top_scale[prm_axis] - _scale[prm_axis];
    }

}

void GgafDx9GeometryScaler::stopImmediately() {
    for (int axis = 0; axis < 3; axis++) {
        stopImmediately(axis);
    }
}

void GgafDx9GeometryScaler::stopImmediately(int prm_axis) {
    _method[prm_axis] = NOSCALE;
}


GgafDx9GeometryScaler::~GgafDx9GeometryScaler() {
}
