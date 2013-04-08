#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAlphaFader::GgafDxAlphaFader(GgafDxDrawableActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

    _alpha = _pActor->getAlpha();
    _velo_alpha = 0.0f;
    _acce_alpha = 0.0f;
    _target_alpha = 1.0f;
    _top_alpha = 1.0f;
    _bottom_alpha = 0.0f;
    _one_way_cnt = 0;
    _beat_attack_frames = 0;
    _beat_duration_frames = 0;
    _beat_rest_frames = 0;
    _beat_target_frames = 0;
    _beat_down_frames = 0;
    _beat_frame_count = 0;
    _beat_progres = 0;
    _stop_one_way_num = -1;
    _method = NO_ALPHAFADE;
}

void GgafDxAlphaFader::behave() {
    if (_method == NO_ALPHAFADE) {
        _pActor->setAlpha(_alpha);
        return;
    }


    if (_method == TARGET_ALPHAFADE_LINER) {
        _alpha += _velo_alpha;
        if (_velo_alpha > 0 && _target_alpha <= _alpha) {
            _alpha = _target_alpha;
            _method = NO_ALPHAFADE;
        } else if (_velo_alpha < 0 && _target_alpha >= _alpha) {
            _alpha = _target_alpha;
            _method = NO_ALPHAFADE;
        }
    } else if (_method == TARGET_ALPHAFADE_ACCELERATION) {
        _alpha += _velo_alpha;
        if (_acce_alpha > 0 && _target_alpha <= _alpha) {
            _alpha = _target_alpha;
            _method = NO_ALPHAFADE;
        } else if (_acce_alpha < 0 && _target_alpha >= _alpha) {
            _alpha = _target_alpha;
            _method = NO_ALPHAFADE;
        }
        _velo_alpha += _acce_alpha;
    } else if (_method == BEAT_ALPHAFADE_LINER) {
        _alpha += _velo_alpha;
        if (_top_alpha <= _alpha) {
            _alpha = _top_alpha;
            _velo_alpha = -2 * (_top_alpha - _bottom_alpha) / (int)_beat_target_frames;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NO_ALPHAFADE;
            }
        } else if (_bottom_alpha >= _alpha) {
            _alpha = _bottom_alpha;
            _velo_alpha = 2 * (_top_alpha - _bottom_alpha) / (int)_beat_target_frames;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NO_ALPHAFADE;
            }
        }
    } else if (_method == BEAT_ALPHAFADE_TRIANGLEWAVE) {
        _beat_frame_count++;
        if (_beat_progres == 0) { //開始～アタックまで
            _alpha += _velo_alpha;
            if (_beat_frame_count >= _beat_attack_frames) { //アタック時
                _alpha = _top_alpha;
                _velo_alpha = (_bottom_alpha - _top_alpha) / int(_beat_down_frames);
                _one_way_cnt++; //半ループカウント＋１
                if (_one_way_cnt == _stop_one_way_num) {
                    _method = NO_ALPHAFADE;
                }
                _velo_alpha = 0;
                _beat_progres = 1; //次へ
            }
        } else if (_beat_progres == 1) { //アタック～持続完了まで
            if (_beat_frame_count >= _beat_attack_frames+_beat_duration_frames) { //持続完了時
                _velo_alpha = (_bottom_alpha - _top_alpha) / int(_beat_down_frames);
                _beat_progres = 2; //次へ
            }
        } else if (_beat_progres == 2) { //持続完了～下限まで
            _alpha += _velo_alpha;
            if (_beat_frame_count >= _beat_attack_frames+_beat_duration_frames+_beat_down_frames) { //下限時
                _alpha = _bottom_alpha;
                _velo_alpha = 0;
                _beat_progres = 3;//次へ
            }
        } else if (_beat_progres == 3) { //下限～終了まで
            if (_beat_frame_count >= _beat_target_frames) { //終了時
                _one_way_cnt++; //半ループカウント＋１
                if (_one_way_cnt == _stop_one_way_num) {
                    _method = NO_ALPHAFADE;
                }

                //最初のアタックまでのvelo
                if (_beat_attack_frames > 0) {
                    _velo_alpha = (_top_alpha - _alpha) / int(_beat_attack_frames);
                    _beat_progres = 0;
                } else { //アタックまでが無いの場合
                    _alpha = _top_alpha;
                    _velo_alpha = 0;
                    _one_way_cnt++; //半ループカウント＋１
                    _beat_progres = 1;
                }
                _beat_frame_count = 0; //カウンタリセット

            }
        }
    }
    //Actorに反映
    _pActor->setAlpha(_alpha);
}

void GgafDxAlphaFader::fadeLinerUntil(float prm_target_alpha, frame prm_spend_frame) {
    //_TRACE_("fadeLinerUntil prm_c="<<prm_c<<"/prm_target_alpha="<<prm_target_alpha<<"/prm_spend_frame="<<prm_spend_frame);
    _method = TARGET_ALPHAFADE_LINER;
    _target_alpha = prm_target_alpha;
    _velo_alpha = (prm_target_alpha - _alpha) / (int)prm_spend_frame;
    //_TRACE_("fadeLinerUntil prm_target_alpha="<<prm_target_alpha<<"/ _alpha["<<prm_c<<"]="<<_alpha);
    //_TRACE_("fadeLinerUntil _velo_alpha["<<prm_c<<"]="<<_velo_alpha);
    if (int(_velo_alpha*1000.0) == 0) {
        _velo_alpha = prm_target_alpha - _alpha;
    }
}

void GgafDxAlphaFader::fadeAcceStep(float prm_target_alpha, float prm_velo_alpha, float prm_acce_alpha) {
    _method = TARGET_ALPHAFADE_ACCELERATION;
    _target_alpha = prm_target_alpha;
    _velo_alpha = prm_velo_alpha;
    _acce_alpha = prm_acce_alpha;
}

void GgafDxAlphaFader::fadeLinerStep(float prm_target_alpha, float prm_velo_alpha) {
    _method = TARGET_ALPHAFADE_LINER;
    _target_alpha = prm_target_alpha;
    _velo_alpha = SGN(prm_target_alpha - _alpha)*prm_velo_alpha;
}


void GgafDxAlphaFader::loopLiner(frame prm_beat_target_frames, float prm_beat_num) {
    _method = BEAT_ALPHAFADE_LINER;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);
    _beat_target_frames = prm_beat_target_frames;
    _velo_alpha = (_top_alpha - _alpha) / ((int)prm_beat_target_frames / 2);
    if (int(_velo_alpha*1000.0) == 0) {
        _velo_alpha = _top_alpha - _alpha;
    }
}

void GgafDxAlphaFader::beat(frame prm_beat_target_frames,
                            frame prm_attack_frames,
                            frame prm_duration_frames,
                            frame prm_rest_frames,
                            float prm_beat_num) {
    _method = BEAT_ALPHAFADE_TRIANGLEWAVE;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);

    _beat_attack_frames = prm_attack_frames;
    _beat_rest_frames = prm_rest_frames;
    _beat_duration_frames = prm_duration_frames;
    _beat_target_frames = prm_beat_target_frames;
    if (_beat_target_frames <= _beat_attack_frames + _beat_duration_frames + _beat_rest_frames) {
        _beat_down_frames = 1.0f;
    } else {
        _beat_down_frames = _beat_target_frames - _beat_attack_frames - _beat_duration_frames - _beat_rest_frames;
    }
    _beat_frame_count = 0;

    //最初のアタックまでのvelo
    if (_beat_attack_frames > 0) {
        _velo_alpha = (_top_alpha - _alpha) / int(_beat_attack_frames);
        _beat_progres = 0;
    } else { //アタックまでが無いの場合
        _alpha = _top_alpha;
        _velo_alpha = 0;
        _one_way_cnt++; //半ループカウント＋１
        _beat_progres = 1;
    }
}


GgafDxAlphaFader::~GgafDxAlphaFader() {
}
