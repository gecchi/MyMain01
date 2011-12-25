#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxColorist::GgafDxColorist(GgafDxDrawableActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

    for (int c = 0; c < 4; c++) {
        _color[c] = LEN_UNIT;
        _velo_color[c] = 0;
        _acce_color[c] = 0;
        _target_color[c] = LEN_UNIT;
        _top_color[c] = INT_MAX;
        _bottom_color[c] = 1;
        _one_way_cnt[c] = 0;
        _beat_attack_frames[c] = 0;
        _beat_rest_frames[c] = 0;
        _beat_target_frames[c] = 0;
        _beat_down_frames[c] = 0;
        _beat_frame_count[c] = 0;
        _beat_progres[c] = 0;
        _stop_one_way_num[c] = -1;
        _method[c] = NOCOLOR;
    }
}

void GgafDxColorist::behave() {
    for (int c = 0; c < 4; c++) {
        if (_method[c] == NOCOLOR) {
            continue;
        } else if (_method[c] == TARGET_COLOR_LINER) {

            _color[c] += _velo_color[c];

            //_TRACE_("_velo_color["<<c<<"]="<<_velo_color[c]<<"/_target_color["<<c<<"]="<<_target_color[c]<<"/_color["<<c<<"]="<<_color[c]);
            if (_velo_color[c] > 0 && _target_color[c] <= _color[c]) {
                //_TRACE_("END1");
                _color[c] = _target_color[c];
                _method[c] = NOCOLOR;
            } else if (_velo_color[c] < 0 && _target_color[c] >= _color[c]) {
                //_TRACE_("END2");
                _color[c] = _target_color[c];
                _method[c] = NOCOLOR;
            }
        } else if (_method[c] == TARGET_COLOR_ACCELERATION) {
            _color[c] += _velo_color[c];
            //if (_velo_color[c] > 0 && _target_color[c] <= _color[c]) {
            if (_acce_color[c] > 0 && _target_color[c] <= _color[c]) {
                _color[c] = _target_color[c];
                _method[c] = NOCOLOR;
            //} else if (_velo_color[c] < 0 && _target_color[c] >= _color[c]) {
            } else if (_acce_color[c] < 0 && _target_color[c] >= _color[c]) {
                _color[c] = _target_color[c];
                _method[c] = NOCOLOR;
            }
            _velo_color[c] += _acce_color[c];
        } else if (_method[c] == BEAT_COLOR_LINER) {
            _color[c] += _velo_color[c];
            if (_top_color[c] <= _color[c]) {
                _color[c] = _top_color[c];
                _velo_color[c] = -2 * (_top_color[c] - _bottom_color[c]) / (int)_beat_target_frames[c];
                _one_way_cnt[c]++;
                if (_one_way_cnt[c] == _stop_one_way_num[c]) {
                    _method[c] = NOCOLOR;
                }
            } else if (_bottom_color[c] >= _color[c]) {
                _color[c] = _bottom_color[c];
                _velo_color[c] = 2 * (_top_color[c] - _bottom_color[c]) / (int)_beat_target_frames[c];
                _one_way_cnt[c]++;
                if (_one_way_cnt[c] == _stop_one_way_num[c]) {
                    _method[c] = NOCOLOR;
                }
            }

        } else if (_method[c] == BEAT_COLOR_TRIANGLEWAVE) {
            _beat_frame_count[c]++;
            if (_beat_progres[c] == 0) { //開始～アタックまで
                _color[c] += _velo_color[c];
                if (_beat_frame_count[c] >= _beat_attack_frames[c]) { //アタック時
                    _color[c] = _top_color[c];
                    _velo_color[c] = (_bottom_color[c] - _top_color[c]) / int(_beat_down_frames[c]);
                    _one_way_cnt[c]++; //半ループカウント＋１
                    if (_one_way_cnt[c] == _stop_one_way_num[c]) {
                        _method[c] = NOCOLOR;
                    }
                    _beat_progres[c] = 1; //次へ
                }
            } else if (_beat_progres[c] == 1) { //アタック～下限まで
                _color[c] += _velo_color[c];
                if (_beat_frame_count[c] >= _beat_attack_frames[c]+_beat_down_frames[c]) { //下限時
                    _color[c] = _bottom_color[c];
                    _velo_color[c] = 0;
                    _beat_progres[c] = 2;//次へ
                }
            } else if (_beat_progres[c] == 2) { //下限～終了まで
                if (_beat_frame_count[c] >= _beat_target_frames[c]) { //終了時
                    _one_way_cnt[c]++; //半ループカウント＋１
                    if (_one_way_cnt[c] == _stop_one_way_num[c]) {
                        _method[c] = NOCOLOR;
                    }
                    _velo_color[c] = (_top_color[c] - _color[c]) / int(_beat_attack_frames[c]);
                    _beat_frame_count[c] = 0; //カウンタリセット
                    _beat_progres[c] = 0;//次へ(元に戻る)
                }
            }
        }
    }
    //Actorに反映
    _pActor->setMaterialColor(_color[0]/1000.0, _color[1]/1000.0, _color[2]/1000.0);
    _pActor->setAlpha(_color[3]/1000.0);
}

void GgafDxColorist::intoTargetColorLinerUntil(int prm_target_color, frame prm_spend_frame) {
    for (int c = 0; c < 4; c++) {
        intoTargetColorLinerUntil(c, prm_target_color, prm_spend_frame);
    }
}

void GgafDxColorist::intoTargetColorLinerUntil(int prm_c, int prm_target_color, frame prm_spend_frame) {
    //_TRACE_("intoTargetColorLinerUntil prm_c="<<prm_c<<"/prm_target_color="<<prm_target_color<<"/prm_spend_frame="<<prm_spend_frame);
    _method[prm_c] = TARGET_COLOR_LINER;
    _target_color[prm_c] = prm_target_color;
    _velo_color[prm_c] = (prm_target_color - _color[prm_c]) / (int)prm_spend_frame;
    //_TRACE_("intoTargetColorLinerUntil prm_target_color="<<prm_target_color<<"/ _color["<<prm_c<<"]="<<_color[prm_c]);
    //_TRACE_("intoTargetColorLinerUntil _velo_color["<<prm_c<<"]="<<_velo_color[prm_c]);
    if (_velo_color[prm_c] == 0) {
        _velo_color[prm_c] = prm_target_color - _color[prm_c];
    }
}

void GgafDxColorist::intoTargetColorAcceStep(int prm_target_color, int prm_velo_color, int prm_acce_color) {
    for (int c = 0; c < 4; c++) {
        intoTargetColorAcceStep(c, prm_target_color, prm_velo_color, prm_acce_color);
    }
}

void GgafDxColorist::intoTargetColorAcceStep(int prm_c, int prm_target_color, int prm_velo_color, int prm_acce_color) {
    _method[prm_c] = TARGET_COLOR_ACCELERATION;
    _target_color[prm_c] = prm_target_color;
    _velo_color[prm_c] = prm_velo_color;
    _acce_color[prm_c] = prm_acce_color;
}

void GgafDxColorist::intoTargetColorLinerStep(int prm_target_color, int prm_velo_color) {
    for (int c = 0; c < 3; c++) {
        intoTargetColorLinerStep(c, prm_target_color, prm_velo_color);
    }
}

void GgafDxColorist::intoTargetColorLinerStep(int prm_c, int prm_target_color, int prm_velo_color) {
    _method[prm_c] = TARGET_COLOR_LINER;
    _target_color[prm_c] = prm_target_color;
    _velo_color[prm_c] = sgn(prm_target_color - _color[prm_c])*prm_velo_color;
}


void GgafDxColorist::loopLiner(frame prm_beat_target_frames, float prm_beat_num) {
    for (int c = 0; c < 4; c++) {
        loopLiner(c, prm_beat_target_frames, prm_beat_num);
    }
}

void GgafDxColorist::loopLiner(int prm_c, frame prm_beat_target_frames, float prm_beat_num) {
    _method[prm_c] = BEAT_COLOR_LINER;
    _one_way_cnt[prm_c] = 0;
    _stop_one_way_num[prm_c] = (int)(prm_beat_num*2.0f);
    _beat_target_frames[prm_c] = prm_beat_target_frames;
    _velo_color[prm_c] = (_top_color[prm_c] - _color[prm_c]) / ((int)prm_beat_target_frames / 2);
    if (_velo_color[prm_c] == 0) {
        _velo_color[prm_c] = _top_color[prm_c] - _color[prm_c];
    }
}

void GgafDxColorist::beat(frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    for (int c = 0; c < 4; c++) {
        beat(c, prm_beat_target_frames, prm_attack_frames, prm_rest_frames, prm_beat_num);
    }
}


void GgafDxColorist::beat(int prm_c, frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    _method[prm_c] = BEAT_COLOR_TRIANGLEWAVE;
    _one_way_cnt[prm_c] = 0;
    _stop_one_way_num[prm_c] = (int)(prm_beat_num*2.0f);

    _beat_attack_frames[prm_c] = prm_attack_frames;
    _beat_rest_frames[prm_c] = prm_rest_frames;
    _beat_target_frames[prm_c] = prm_beat_target_frames;
    _beat_down_frames[prm_c] = _beat_target_frames[prm_c] - _beat_attack_frames[prm_c] - _beat_rest_frames[prm_c];
    _beat_frame_count[prm_c] = 0;

    //最初のアタックまでのvelo
    if (_beat_attack_frames[prm_c] > 0) {
        _velo_color[prm_c] = (_top_color[prm_c] - _color[prm_c]) / int(_beat_attack_frames[prm_c]);
        _beat_progres[prm_c] = 0;
    } else { //アタックまでが無いの場合
        _color[prm_c] = _top_color[prm_c];
        _velo_color[prm_c] = (_bottom_color[prm_c] - _top_color[prm_c]) / int(_beat_down_frames[prm_c]);
        _one_way_cnt[prm_c]++; //半ループカウント＋１
        _beat_progres[prm_c] = 1;
    }
}

void GgafDxColorist::stopImmed() {
    for (int c = 0; c < 4; c++) {
        stopImmed(c);
    }
}

void GgafDxColorist::stopImmed(int prm_c) {
    _method[prm_c] = NOCOLOR;
}


GgafDxColorist::~GgafDxColorist() {
}
