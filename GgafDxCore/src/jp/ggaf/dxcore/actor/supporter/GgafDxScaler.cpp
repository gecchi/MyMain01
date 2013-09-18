#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxScaler::GgafDxScaler(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {

    for (int ax = 0; ax < 3; ax++) {
        _scale[ax] = R_SC(1.0);
        _velo_scale[ax] = 0;
        _acce_scale[ax] = 0;
        _target_scale[ax] = R_SC(1.0);
        _top_scale[ax] = INT_MAX;
        _bottom_scale[ax] = 1;
        _one_way_cnt[ax] = 0;
        _beat_attack_frames[ax] = 0;
        _beat_rest_frames[ax] = 0;
        _beat_target_frames[ax] = 0;
        _beat_down_frames[ax] = 0;
        _beat_frame_count[ax] = 0;
        _beat_progres[ax] = 0;
        _stop_one_way_num[ax] = -1;
        _method[ax] = NOSCALE;
    }
}

void GgafDxScaler::reset() {
    for (int ax = 0; ax < 3; ax++) {
        _scale[ax] = R_SC(1.0);;
        _velo_scale[ax] = 0;
        _acce_scale[ax] = 0;
        _target_scale[ax] = R_SC(1.0);;
        _top_scale[ax] = INT_MAX;
        _bottom_scale[ax] = 1;
        _one_way_cnt[ax] = 0;
        _beat_attack_frames[ax] = 0;
        _beat_rest_frames[ax] = 0;
        _beat_target_frames[ax] = 0;
        _beat_down_frames[ax] = 0;
        _beat_frame_count[ax] = 0;
        _beat_progres[ax] = 0;
        _stop_one_way_num[ax] = -1;
        _method[ax] = NOSCALE;
    }
}
void GgafDxScaler::behave() {
    GgafDxScalingMethod method;
    for (int ax = 0; ax < 3; ax++) {
        method = _method[ax];
        if (method == NOSCALE) {
            continue;
        } else if (method == TARGET_SCALE_LINER) {
            _scale[ax] += _velo_scale[ax];
            if (_velo_scale[ax] > 0 && _target_scale[ax] <= _scale[ax]) {
                _scale[ax] = _target_scale[ax];
                _method[ax] = NOSCALE;
            } else if (_velo_scale[ax] < 0 && _target_scale[ax] >= _scale[ax]) {
                _scale[ax] = _target_scale[ax];
                _method[ax] = NOSCALE;
            }
        } else if (method == TARGET_SCALE_ACCELERATION) {
            _scale[ax] += _velo_scale[ax];
            if (_acce_scale[ax] > 0 && _target_scale[ax] <= _scale[ax]) {
                _scale[ax] = _target_scale[ax];
                _method[ax] = NOSCALE;
            } else if (_acce_scale[ax] < 0 && _target_scale[ax] >= _scale[ax]) {
                _scale[ax] = _target_scale[ax];
                _method[ax] = NOSCALE;
            }
            _velo_scale[ax] += _acce_scale[ax];
        } else if (method == BEAT_SCALE_LINER) {
            _scale[ax] += _velo_scale[ax];
            if (_top_scale[ax] <= _scale[ax]) {
                _scale[ax] = _top_scale[ax];
                _velo_scale[ax] = -2 * (_top_scale[ax] - _bottom_scale[ax]) / (int)_beat_target_frames[ax];
                _one_way_cnt[ax]++;
                if (_one_way_cnt[ax] == _stop_one_way_num[ax]) {
                    _method[ax] = NOSCALE;
                }
            } else if (_bottom_scale[ax] >= _scale[ax]) {
                _scale[ax] = _bottom_scale[ax];
                _velo_scale[ax] = 2 * (_top_scale[ax] - _bottom_scale[ax]) / (int)_beat_target_frames[ax];
                _one_way_cnt[ax]++;
                if (_one_way_cnt[ax] == _stop_one_way_num[ax]) {
                    _method[ax] = NOSCALE;
                }
            }

        } else if (method == BEAT_SCALE_TRIANGLEWAVE) {
            _beat_frame_count[ax]++;
            if (_beat_progres[ax] == 0) { //開始〜アタックまで
                _scale[ax] += _velo_scale[ax];
                if (_beat_frame_count[ax] >= _beat_attack_frames[ax]) { //アタック時
                    _scale[ax] = _top_scale[ax];
                    _velo_scale[ax] = (_bottom_scale[ax] - _top_scale[ax]) / int(_beat_down_frames[ax]);
                    _one_way_cnt[ax]++; //半ループカウント＋１
                    if (_one_way_cnt[ax] == _stop_one_way_num[ax]) {
                        _method[ax] = NOSCALE;
                    }
                    _beat_progres[ax] = 1; //次へ
                }
            } else if (_beat_progres[ax] == 1) { //アタック〜下限まで
                _scale[ax] += _velo_scale[ax];
                if (_beat_frame_count[ax] >= _beat_attack_frames[ax]+_beat_down_frames[ax]) { //下限時
                    _scale[ax] = _bottom_scale[ax];
                    _velo_scale[ax] = 0;
                    _beat_progres[ax] = 2;//次へ
                }
            } else if (_beat_progres[ax] == 2) { //下限〜終了まで
                if (_beat_frame_count[ax] >= _beat_target_frames[ax]) { //終了時
                    _one_way_cnt[ax]++; //半ループカウント＋１
                    if (_one_way_cnt[ax] == _stop_one_way_num[ax]) {
                        _method[ax] = NOSCALE;
                    }
                    if (_beat_attack_frames[ax] == 0) {
                        _velo_scale[ax] = 1073741824; //MAXLONGの半分にした（適当）
                    } else {
                        _velo_scale[ax] = (_top_scale[ax] - _scale[ax]) / int(_beat_attack_frames[ax]);
                    }
                    _beat_frame_count[ax] = 0; //カウンタリセット
                    _beat_progres[ax] = 0;//次へ(元に戻る)
                }
            }
        }
    }
    //Actorに反映
    if (_pActor->_SX != _scale[AXIS_X] || _pActor->_SY != _scale[AXIS_Y] || _pActor->_SZ != _scale[AXIS_Z]) {
        _pActor->setScale(_scale[AXIS_X], _scale[AXIS_Y], _scale[AXIS_Z]);
    }
}

//いつかまた使うでしょう
//            _TRACE_("---実行前");
//            _TRACE_("_pActor->_frame_of_behaving="<<_pActor->_frame_of_behaving);
//            _TRACE_("_bottom_scale["<<ax<<"]="<<_bottom_scale[ax]);
//            _TRACE_("_top_scale["<<ax<<"]="<<_top_scale[ax]);
//            _TRACE_("_beat_target_frames["<<ax<<"]="<<_beat_target_frames[ax]);
//            _TRACE_("_beat_attack_frames["<<ax<<"]="<<_beat_attack_frames[ax]);
//            _TRACE_("_beat_rest_frames["<<ax<<"]="<<_beat_rest_frames[ax]);
//            _TRACE_("_beat_target_frames["<<ax<<"] - _beat_attack_frames["<<ax<<"] - _beat_rest_frames["<<ax<<"]) = " << (_beat_target_frames[ax] - _beat_attack_frames[ax] - _beat_rest_frames[ax]));
//            _TRACE_("(_bottom_scale["<<ax<<"] - _top_scale["<<ax<<"]) / (_beat_target_frames["<<ax<<"] - _beat_attack_frames["<<ax<<"] - _beat_rest_frames["<<ax<<"])="<<((int)(_bottom_scale[ax] - _top_scale[ax]) / (int)(_beat_target_frames[ax] - _beat_attack_frames[ax] - _beat_rest_frames[ax])));
//            _TRACE_("_bottom_scale["<<ax<<"] - _top_scale["<<ax<<"]" << (_bottom_scale[ax] - _top_scale[ax]));
//            _TRACE_("_scale["<<ax<<"] _velo_scale["<<ax<<"]="<<_scale[ax]<<" "<<_velo_scale[ax]);

void GgafDxScaler::scaleLinerUntil(int prm_target_scale, frame prm_spend_frame) {
    for (int a = 0; a < 3; a++) {
        scaleLinerUntil((axis)a, prm_target_scale, prm_spend_frame);
    }
}

void GgafDxScaler::scaleLinerTop(frame prm_spend_frame) {
    scaleLinerUntil(MAX3(_top_scale[0],_top_scale[1],_top_scale[2]), prm_spend_frame);
}

void GgafDxScaler::scaleLinerBottom(frame prm_spend_frame) {
    scaleLinerUntil(MIN3(_bottom_scale[0],_bottom_scale[1],_bottom_scale[2]), prm_spend_frame);
}

void GgafDxScaler::scaleLinerUntil(axis prm_axis, int prm_target_scale, frame prm_spend_frame) {
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = (prm_target_scale - _scale[prm_axis]) / (int)prm_spend_frame;
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = prm_target_scale - _scale[prm_axis];
    }
}

void GgafDxScaler::scaleAcceStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale) {
    for (int a = 0; a < 3; a++) {
        scaleAcceStep((axis)a, prm_target_scale, prm_velo_scale, prm_acce_scale);
    }
}

void GgafDxScaler::scaleAcceStep(axis prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale) {
    _method[prm_axis] = TARGET_SCALE_ACCELERATION;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = prm_velo_scale;
    _acce_scale[prm_axis] = prm_acce_scale;
}

void GgafDxScaler::scaleLinerStep(int prm_target_scale, int prm_velo_scale) {
    for (int a = 0; a < 3; a++) {
        scaleLinerStep((axis)a, prm_target_scale, prm_velo_scale);
    }
}

void GgafDxScaler::scaleLinerStep(axis prm_axis, int prm_target_scale, int prm_velo_scale) {
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = SGN(prm_target_scale - _scale[prm_axis])*prm_velo_scale;
}

void GgafDxScaler::loopLiner(frame prm_beat_target_frames, float prm_beat_num) {
    for (int a = 0; a < 3; a++) {
        loopLiner((axis)a, prm_beat_target_frames, prm_beat_num);
    }
}

void GgafDxScaler::loopLiner(axis prm_axis, frame prm_beat_target_frames, float prm_beat_num) {
    _method[prm_axis] = BEAT_SCALE_LINER;
    _one_way_cnt[prm_axis] = 0;
    _stop_one_way_num[prm_axis] = (int)(prm_beat_num*2.0f);
    _beat_target_frames[prm_axis] = prm_beat_target_frames;
    _velo_scale[prm_axis] = (_top_scale[prm_axis] - _scale[prm_axis]) / ((int)prm_beat_target_frames / 2);
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = _top_scale[prm_axis] - _scale[prm_axis];
    }
}

void GgafDxScaler::beat(frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    for (int a = 0; a < 3; a++) {
        beat((axis)a, prm_beat_target_frames, prm_attack_frames, prm_rest_frames, prm_beat_num);
    }
}

void GgafDxScaler::beat(axis prm_axis, frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    _method[prm_axis] = BEAT_SCALE_TRIANGLEWAVE;
    _one_way_cnt[prm_axis] = 0;
    _stop_one_way_num[prm_axis] = (int)(prm_beat_num*2.0f);

    _beat_attack_frames[prm_axis] = prm_attack_frames;
    _beat_rest_frames[prm_axis] = prm_rest_frames;
    _beat_target_frames[prm_axis] = prm_beat_target_frames;
    int down_frames = (int)(_beat_target_frames[prm_axis]) - (int)(_beat_attack_frames[prm_axis]) - (int)(_beat_rest_frames[prm_axis]);
    if (down_frames <= 0) {
        _beat_down_frames[prm_axis] = 1;
    } else {
        _beat_down_frames[prm_axis] = (frame)down_frames;
    }
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

void GgafDxScaler::stopImmed() {
    for (int a = 0; a < 3; a++) {
        stopImmed((axis)a);
    }
}

void GgafDxScaler::stopImmed(axis prm_axis) {
    _method[prm_axis] = NOSCALE;
}
bool GgafDxScaler::isScaling(axis prm_axis) {
    if (_method[prm_axis] == NOSCALE) {
        return false;
    } else {
        return true;
    }
}

bool GgafDxScaler::isScaling() {
    for (int a = 0; a < 3; a++) {
        if (_method[(axis)a] != NOSCALE) {
            return true;
        }
    }
    return false;
}

GgafDxScaler::~GgafDxScaler() {
}
