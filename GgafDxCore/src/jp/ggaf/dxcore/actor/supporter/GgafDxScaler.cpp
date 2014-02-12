#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxScaler::GgafDxScaler(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {

    _apActorScale[0] = &(prm_pActor->_sx);
    _apActorScale[1] = &(prm_pActor->_sy);
    _apActorScale[2] = &(prm_pActor->_sz);

    for (int ax = 0; ax < 3; ax++) {
//        _scale[ax] = R_SC(1.0);
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
//        _scale[ax] = R_SC(1.0);;
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
        int s = (*(_apActorScale[ax])); //現在のアクターのスケール
        _velo_scale[ax] += _acce_scale[ax];
        if (_top_scale[ax] < s + _velo_scale[ax]) {
            _velo_scale[ax] = _top_scale[ax] - s;
        } else if (_bottom_scale[ax] >  s + _velo_scale[ax]) {
            _velo_scale[ax] =  _bottom_scale[ax] - s;
        }


        method = _method[ax];
        if (method == NOSCALE) {
            (*(_apActorScale[ax])) = (*(_apActorScale[ax])) + _velo_scale[ax];

        } else {


            if (method == TARGET_SCALE_LINER || method == TARGET_SCALE_ACCELERATION) {
                if (_velo_scale[ax] > 0 && _target_scale[ax] <= s + _velo_scale[ax] ) {
                    _velo_scale[ax] = _target_scale[ax] - s;
                } else if (_velo_scale[ax] < 0 && _target_scale[ax] >= s + _velo_scale[ax] ) {
                    _velo_scale[ax] = _target_scale[ax] - s;
                }
            } else if (method == BEAT_SCALE_LINER) {
                _beat_frame_count[ax]++;
            } else if (method == BEAT_SCALE_TRIANGLEWAVE) {
                _beat_frame_count[ax]++;
                if (_beat_progres[ax] == 0) { //開始～アタックまで
                    if (_beat_frame_count[ax] >= _beat_attack_frames[ax]) { //アタック時
                        _velo_scale[ax] = _top_scale[ax] - s;
                    }

                } else if (_beat_progres[ax] == 1) { //アタック～下限まで
                    if (_beat_frame_count[ax] >= _beat_attack_frames[ax]+_beat_down_frames[ax]) { //下限時
                        _velo_scale[ax] = _bottom_scale[ax] - s;
                    }
                } else if (_beat_progres[ax] == 2) { //下限～終了まで
                    if (_beat_frame_count[ax] >= _beat_target_frames[ax]) { //終了時
                    }
                }
            }

            (*(_apActorScale[ax])) = (*(_apActorScale[ax])) + _velo_scale[ax];
            scale new_s = (*(_apActorScale[ax]));

            if (method == NOSCALE) {
                _velo_scale[ax] = 0;
                _acce_scale[ax] = 0;
            } else if (method == TARGET_SCALE_LINER || method == TARGET_SCALE_ACCELERATION)  {
                if (_target_scale[ax] == new_s) {
                    _velo_scale[ax] = 0;
                    _acce_scale[ax] = 0;
                    _method[ax] = NOSCALE;
                }
            } else if (method == BEAT_SCALE_LINER) {
                if (_beat_frame_count[ax] >= _beat_target_frames[ax]/2) {
                    if (new_s == _top_scale[ax]) {
                        _velo_scale[ax] = -2.0 * (_top_scale[ax] - _bottom_scale[ax]) / (int)_beat_target_frames[ax];
                        _one_way_cnt[ax]++;
                        _beat_frame_count[ax] = 0;
                        if (_one_way_cnt[ax] == _stop_one_way_num[ax]) { //_stop_one_way_numは負の数で無限ループなので == で判定するべし
                            _velo_scale[ax] = 0;
                            _acce_scale[ax] = 0;
                            _method[ax] = NOSCALE;
                        }
                    } else if (new_s == _bottom_scale[ax]) {
                        _velo_scale[ax] = 2.0 * (_top_scale[ax] - _bottom_scale[ax]) / (int)_beat_target_frames[ax];
                        _one_way_cnt[ax]++;
                        _beat_frame_count[ax] = 0;
                        if (_one_way_cnt[ax] == _stop_one_way_num[ax]) {
                            _velo_scale[ax] = 0;
                            _acce_scale[ax] = 0;
                            _method[ax] = NOSCALE;
                        }
                    }
                }

            } else if (method == BEAT_SCALE_TRIANGLEWAVE) {
                if (_beat_progres[ax] == 0) { //開始～アタックまで
                    if (_beat_frame_count[ax] >= _beat_attack_frames[ax]) { //アタック頂点時
                        _velo_scale[ax] = (_bottom_scale[ax] - _top_scale[ax]) / int(_beat_down_frames[ax]); //下限までの速度設定
                        _one_way_cnt[ax]++; //半ループカウント＋１
                        if (_one_way_cnt[ax] == _stop_one_way_num[ax]) {
                            _velo_scale[ax] = 0;
                            _acce_scale[ax] = 0;
                            _method[ax] = NOSCALE;
                        } else {
                            _beat_progres[ax] = 1; //次へ
                        }
                    }

                } else if (_beat_progres[ax] == 1) { //アタック～下限まで
                    if (_beat_frame_count[ax] >= _beat_attack_frames[ax]+_beat_down_frames[ax]) { //下限時
                        _velo_scale[ax] = 0;
                        _beat_progres[ax] = 2;//次へ
                    }
                } else if (_beat_progres[ax] == 2) { //下限～終了まで
                    if (_beat_frame_count[ax] >= _beat_target_frames[ax]) { //終了時
                        _one_way_cnt[ax]++; //半ループカウント＋１
                        if (_one_way_cnt[ax] == _stop_one_way_num[ax]) {
                            _velo_scale[ax] = 0;
                            _acce_scale[ax] = 0;
                            _method[ax] = NOSCALE;
                        } else {
                            if (_beat_attack_frames[ax] == 0) {
                                _velo_scale[ax] = 1073741824; //MAXLONGの半分にした（適当）
                            } else {
                                _velo_scale[ax] = (_top_scale[ax] - _bottom_scale[ax]) / int(_beat_attack_frames[ax]); //次のアタック
                            }
                            _beat_frame_count[ax] = 0; //カウンタリセット
                            _beat_progres[ax] = 0;//次へ(元に戻る)
                        }
                    }
                }
            }
        }
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
    scaleLinerUntil(MIN3(_top_scale[0],_top_scale[1],_top_scale[2]), prm_spend_frame);
}

void GgafDxScaler::scaleLinerBottom(frame prm_spend_frame) {
    scaleLinerUntil(MAX3(_bottom_scale[0],_bottom_scale[1],_bottom_scale[2]), prm_spend_frame);
}

void GgafDxScaler::scaleLinerUntil(axis prm_axis, int prm_target_scale, frame prm_spend_frame) {
    int s = (*(_apActorScale[prm_axis]));
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = (prm_target_scale - s) / (int)prm_spend_frame;
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = prm_target_scale - s;
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
    int s = (*(_apActorScale[prm_axis]));
    _method[prm_axis] = TARGET_SCALE_LINER;
    _target_scale[prm_axis] = prm_target_scale;
    _velo_scale[prm_axis] = SGN(prm_target_scale - s)*prm_velo_scale;
}

void GgafDxScaler::loopLiner(frame prm_beat_target_frames, float prm_beat_num) {
    for (int a = 0; a < 3; a++) {
        loopLiner((axis)a, prm_beat_target_frames, prm_beat_num);
    }
}

void GgafDxScaler::loopLiner(axis prm_axis, frame prm_beat_target_frames, float prm_beat_num) {
    int s = (*(_apActorScale[prm_axis]));
    _method[prm_axis] = BEAT_SCALE_LINER;
    _one_way_cnt[prm_axis] = 0;
    _stop_one_way_num[prm_axis] = (int)(prm_beat_num*2.0f);
    _beat_frame_count[prm_axis] = 0;
    _beat_target_frames[prm_axis] = prm_beat_target_frames;
    _velo_scale[prm_axis] = 1.0*(_top_scale[prm_axis] - s) / ((int)prm_beat_target_frames / 2.0);
    if (_velo_scale[prm_axis] == 0) {
        _velo_scale[prm_axis] = _top_scale[prm_axis] - s;
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

    if (prm_attack_frames <= 0 ) {
        _beat_attack_frames[prm_axis] = 1;
    } else {
        _beat_attack_frames[prm_axis] = prm_attack_frames;
    }
    _beat_rest_frames[prm_axis] = prm_rest_frames;
    _beat_target_frames[prm_axis] = prm_beat_target_frames;
    int down_frames = (int)(_beat_target_frames[prm_axis]) - (int)(_beat_attack_frames[prm_axis]) - (int)(_beat_rest_frames[prm_axis]);
    if (down_frames <= 0) {
        _beat_down_frames[prm_axis] = 1;
    } else {
        _beat_down_frames[prm_axis] = (frame)down_frames;
    }
    _beat_frame_count[prm_axis] = 0;

//    //最初のアタックまでのvelo
    int s = (*(_apActorScale[prm_axis]));
//    if (_beat_attack_frames[prm_axis] > 0) {
        _velo_scale[prm_axis] = (_top_scale[prm_axis] - s) / int(_beat_attack_frames[prm_axis]);
        _beat_progres[prm_axis] = 0;
//    } else { //アタックまでが無いの場合アタックフレーム1へ
//        (*(_apActorScale[prm_axis])) = _top_scale[prm_axis];
//        _velo_scale[prm_axis] = (_bottom_scale[prm_axis] - _top_scale[prm_axis]) / int(_beat_down_frames[prm_axis]);
//        _one_way_cnt[prm_axis]++; //半ループカウント＋１
//        _beat_progres[prm_axis] = 1;
//    }
}
scale GgafDxScaler::getTop() {
    return MIN3(_top_scale[0], _top_scale[1], _top_scale[2]);
}
scale GgafDxScaler::getBottom() {
    return MAX3(_bottom_scale[0],_bottom_scale[1],_bottom_scale[2]);
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
