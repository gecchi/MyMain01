#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Scaler::GgafDx9Scaler(GgafDx9GeometricActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

    for (int axis = 0; axis < 3; axis++) {
        _scale[axis] = LEN_UNIT;
        _velo_scale[axis] = 0;
        _target_scale[axis] = LEN_UNIT;
        _top_scale[axis] = INT_MAX;
        _bottom_scale[axis] = 1;
        _one_way_cnt[axis] = 0;
        _beat_attack_frames[axis] = 0;
        _beat_rest_frames[axis] = 0;
        _beat_spend_frames[axis] = 0;
        _beat_down_frames[axis] = 0;
        _beat_frame_count[axis] = 0;
        _beat_progres[axis] = 0;
        _stop_one_way_num[axis] = -1;
        _method[axis] = NOSCALE;
    }
}

void GgafDx9Scaler::behave() {
    for (int axis = 0; axis < 3; axis++) {
        if (_method[axis] == NOSCALE) {
            continue;
        } else if (_method[axis] == TARGET_SCALE_LINER) {

            _scale[axis] += _velo_scale[axis];

            //_TRACE_("_velo_scale["<<axis<<"]="<<_velo_scale[axis]<<"/_target_scale["<<axis<<"]="<<_target_scale[axis]<<"/_scale["<<axis<<"]="<<_scale[axis]);
            if (_velo_scale[axis] > 0 && _target_scale[axis] <= _scale[axis]) {
                //_TRACE_("END1");
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            } else if (_velo_scale[axis] < 0 && _target_scale[axis] >= _scale[axis]) {
                //_TRACE_("END2");
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            }
        } if (_method[axis] == TARGET_SCALE_ACCELERATION) {
            _scale[axis] += _velo_scale[axis];
            //if (_velo_scale[axis] > 0 && _target_scale[axis] <= _scale[axis]) {
            if (_acce_scale[axis] > 0 && _target_scale[axis] <= _scale[axis]) {
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            //} else if (_velo_scale[axis] < 0 && _target_scale[axis] >= _scale[axis]) {
            } else if (_acce_scale[axis] < 0 && _target_scale[axis] >= _scale[axis]) {
                _scale[axis] = _target_scale[axis];
                _method[axis] = NOSCALE;
            }
            _velo_scale[axis] += _acce_scale[axis];
        } else if (_method[axis] == BEAT_SCALE_LINER) {
            _scale[axis] += _velo_scale[axis];
            if (_top_scale[axis] <= _scale[axis]) {
                _scale[axis] = _top_scale[axis];
                _velo_scale[axis] = -2 * (_top_scale[axis] - _bottom_scale[axis]) / (int)_beat_spend_frames[axis];
                _one_way_cnt[axis]++;
                if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                    _method[axis] = NOSCALE;
                }
            } else if (_bottom_scale[axis] >= _scale[axis]) {
                _scale[axis] = _bottom_scale[axis];
                _velo_scale[axis] = 2 * (_top_scale[axis] - _bottom_scale[axis]) / (int)_beat_spend_frames[axis];
                _one_way_cnt[axis]++;
                if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                    _method[axis] = NOSCALE;
                }
            }

        } else if (_method[axis] == BEAT_SCALE_TRIANGLEWAVE) {
            _beat_frame_count[axis]++;
            if (_beat_progres[axis] == 0) { //開始～アタックまで
                _scale[axis] += _velo_scale[axis];
                if (_beat_frame_count[axis] >= _beat_attack_frames[axis]) { //アタック時
                    _scale[axis] = _top_scale[axis];
                    _velo_scale[axis] = (_bottom_scale[axis] - _top_scale[axis]) / int(_beat_down_frames[axis]);
                    _one_way_cnt[axis]++; //半ループカウント＋１
                    if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                        _method[axis] = NOSCALE;
                    }
                    _beat_progres[axis] = 1; //次へ
                }
            } else if (_beat_progres[axis] == 1) { //アタック～下限まで
                _scale[axis] += _velo_scale[axis];
                if (_beat_frame_count[axis] >= _beat_attack_frames[axis]+_beat_down_frames[axis]) { //下限時
                    _scale[axis] = _bottom_scale[axis];
                    _velo_scale[axis] = 0;
                    _beat_progres[axis] = 2;//次へ
                }
            } else if (_beat_progres[axis] == 2) { //下限～終了まで
                if (_beat_frame_count[axis] >= _beat_spend_frames[axis]) { //終了時
                    _one_way_cnt[axis]++; //半ループカウント＋１
                    if (_one_way_cnt[axis] == _stop_one_way_num[axis]) {
                        _method[axis] = NOSCALE;
                    }
                    _velo_scale[axis] = (_top_scale[axis] - _scale[axis]) / int(_beat_attack_frames[axis]);
                    _beat_frame_count[axis] = 0; //カウンタリセット
                    _beat_progres[axis] = 0;//次へ(元に戻る)
                }
            }
        }
    }
    //Actorに反映
    _pActor->_SX = _scale[AXIS_X];
    _pActor->_SY = _scale[AXIS_Y];
    _pActor->_SZ = _scale[AXIS_Z];
}

//いつかまた使うでしょう
//            _TRACE_("---実行前");
//            _TRACE_("_pActor->_frame_of_behaving="<<_pActor->_frame_of_behaving);
//            _TRACE_("_bottom_scale["<<axis<<"]="<<_bottom_scale[axis]);
//            _TRACE_("_top_scale["<<axis<<"]="<<_top_scale[axis]);
//            _TRACE_("_beat_spend_frames["<<axis<<"]="<<_beat_spend_frames[axis]);
//            _TRACE_("_beat_attack_frames["<<axis<<"]="<<_beat_attack_frames[axis]);
//            _TRACE_("_beat_rest_frames["<<axis<<"]="<<_beat_rest_frames[axis]);
//            _TRACE_("_beat_spend_frames["<<axis<<"] - _beat_attack_frames["<<axis<<"] - _beat_rest_frames["<<axis<<"]) = " << (_beat_spend_frames[axis] - _beat_attack_frames[axis] - _beat_rest_frames[axis]));
//            _TRACE_("(_bottom_scale["<<axis<<"] - _top_scale["<<axis<<"]) / (_beat_spend_frames["<<axis<<"] - _beat_attack_frames["<<axis<<"] - _beat_rest_frames["<<axis<<"])="<<((int)(_bottom_scale[axis] - _top_scale[axis]) / (int)(_beat_spend_frames[axis] - _beat_attack_frames[axis] - _beat_rest_frames[axis])));
//            _TRACE_("_bottom_scale["<<axis<<"] - _top_scale["<<axis<<"]" << (_bottom_scale[axis] - _top_scale[axis]));
//            _TRACE_("_scale["<<axis<<"] _velo_scale["<<axis<<"]="<<_scale[axis]<<" "<<_velo_scale[axis]);

void GgafDx9Scaler::intoTargetScaleLinerUntil(int prm_target_scale, frame prm_spend_frame) {
    for (int axis = 0; axis < 3; axis++) {
        intoTargetScaleLinerUntil(axis, prm_target_scale, prm_spend_frame);
    }
}

void GgafDx9Scaler::intoTargetScaleLinerUntil(int prm_axis, int prm_target_scale, frame prm_spend_frame) {
    //_TRACE_("intoTargetScaleLinerUntil prm_axis="<<prm_axis<<"/prm_target_scale="<<prm_target_scale<<"/prm_spend_frame="<<prm_spend_frame);
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = (prm_target_scale - _scale[prm_axis]) / (int)prm_spend_frame;
    //_TRACE_("intoTargetScaleLinerUntil prm_target_scale="<<prm_target_scale<<"/ _scale["<<prm_axis<<"]="<<_scale[prm_axis]);
    //_TRACE_("intoTargetScaleLinerUntil _velo_scale["<<prm_axis<<"]="<<_velo_scale[prm_axis]);
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = prm_target_scale - _scale[prm_axis];
    }
}

void GgafDx9Scaler::intoTargetScaleAcceStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale) {
    for (int axis = 0; axis < 3; axis++) {
        intoTargetScaleAcceStep(axis, prm_target_scale, prm_velo_scale, prm_acce_scale);
    }
}

void GgafDx9Scaler::intoTargetScaleAcceStep(int prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale) {
    _method[prm_axis] = TARGET_SCALE_ACCELERATION;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = prm_velo_scale;
    _acce_scale[prm_axis] = prm_acce_scale;
}

void GgafDx9Scaler::intoTargetScaleLinerStep(int prm_target_scale, int prm_velo_scale) {
    for (int axis = 0; axis < 3; axis++) {
        intoTargetScaleLinerStep(axis, prm_target_scale, prm_velo_scale);
    }
}

void GgafDx9Scaler::intoTargetScaleLinerStep(int prm_axis, int prm_target_scale, int prm_velo_scale) {
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = sgn(prm_target_scale - _scale[prm_axis])*prm_velo_scale;
}


void GgafDx9Scaler::loopLiner(frame prm_beat_spend_frames, float prm_beat_num) {
    for (int axis = 0; axis < 3; axis++) {
        loopLiner(axis, prm_beat_spend_frames, prm_beat_num);
    }
}

void GgafDx9Scaler::loopLiner(int prm_axis, frame prm_beat_spend_frames, float prm_beat_num) {
    _method[prm_axis] = BEAT_SCALE_LINER;
    _one_way_cnt[prm_axis] = 0;
    _stop_one_way_num[prm_axis] = (int)(prm_beat_num*2.0f);
    _beat_spend_frames[prm_axis] = prm_beat_spend_frames;
    _velo_scale[prm_axis] = (_top_scale[prm_axis] - _scale[prm_axis]) / ((int)prm_beat_spend_frames / 2);
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = _top_scale[prm_axis] - _scale[prm_axis];
    }
}

void GgafDx9Scaler::beat(frame prm_beat_spend_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    for (int axis = 0; axis < 3; axis++) {
        beat(axis, prm_beat_spend_frames, prm_attack_frames, prm_rest_frames, prm_beat_num);
    }
}


void GgafDx9Scaler::beat(int prm_axis, frame prm_beat_spend_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    _method[prm_axis] = BEAT_SCALE_TRIANGLEWAVE;
    _one_way_cnt[prm_axis] = 0;
    _stop_one_way_num[prm_axis] = (int)(prm_beat_num*2.0f);

    _beat_attack_frames[prm_axis] = prm_attack_frames;
    _beat_rest_frames[prm_axis] = prm_rest_frames;
    _beat_spend_frames[prm_axis] = prm_beat_spend_frames;
    _beat_down_frames[prm_axis] = _beat_spend_frames[prm_axis] - _beat_attack_frames[prm_axis] - _beat_rest_frames[prm_axis];
    _beat_frame_count[prm_axis] = 0;

    //最初のアタックまでのvelo
    if (_beat_attack_frames[prm_axis] > 0) {
        _velo_scale[prm_axis] = (_top_scale[prm_axis] - _scale[prm_axis]) / int(_beat_attack_frames[prm_axis]);
        _beat_progres[prm_axis] = 0;
    } else { //アタックまでが無いの場合
        _scale[prm_axis] = _top_scale[prm_axis];
        _velo_scale[prm_axis] = (_bottom_scale[prm_axis] - _top_scale[prm_axis]) / int(_beat_down_frames[prm_axis]);
        _one_way_cnt[prm_axis]++; //半ループカウント＋１
        _beat_progres[prm_axis] = 1;
    }
}

void GgafDx9Scaler::stopImmediately() {
    for (int axis = 0; axis < 3; axis++) {
        stopImmediately(axis);
    }
}

void GgafDx9Scaler::stopImmediately(int prm_axis) {
    _method[prm_axis] = NOSCALE;
}


GgafDx9Scaler::~GgafDx9Scaler() {
}
