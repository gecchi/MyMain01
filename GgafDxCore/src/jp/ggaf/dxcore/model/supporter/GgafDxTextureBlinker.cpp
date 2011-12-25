#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxTextureBlinker::GgafDxTextureBlinker(GgafDxModel* prm_pModel) :
    GgafObject() {
    _pModel = prm_pModel;
    _power_blink = 1.0f;
    _velo_power_blink = 0.0f;
    _acce_power_blink = 0.0f;
    _target_power_blink = 1.0f;
    _top_power_blink = 1000.0f;
    _bottom_power_blink = 0.0f;
    _one_way_cnt = 0;
    _beat_attack_frames = 0;
    _beat_rest_frames = 0;
    _frame_of_beat_begin = 0;
    _beat_down_frames = 0;
    _beat_frame_count = 0;
    _beat_progres = 0;
    _beat_target_frames = 0;
    _stop_one_way_num = -1;
    _method = NOBLINK;
}

void GgafDxTextureBlinker::behave() {

    if (_method == NOBLINK) {
        return;
    } else if (_method == TARGET_BLINK_LINER) {

        _power_blink += _velo_power_blink;

        //_TRACE_("_velo_power_blink["<<<<"]="<<_velo_power_blink<<"/_target_power_blink["<<<<"]="<<_target_power_blink<<"/_power_blink["<<<<"]="<<_power_blink);
        if (_velo_power_blink > 0.0f && _target_power_blink <= _power_blink) {
            //_TRACE_("END1");
            _power_blink = _target_power_blink;
            _method = NOBLINK;
        } else if (_velo_power_blink < 0.0f && _target_power_blink >= _power_blink) {
            //_TRACE_("END2");
            _power_blink = _target_power_blink;
            _method = NOBLINK;
        }
    } else if (_method == TARGET_BLINK_ACCELERATION) {
        _power_blink += _velo_power_blink;
        if (_velo_power_blink > 0.0f && _target_power_blink <= _power_blink) {
            _power_blink = _target_power_blink;
            _method = NOBLINK;
        } else if (_velo_power_blink < 0.0f && _target_power_blink >= _power_blink) {
            _power_blink = _target_power_blink;
            _method = NOBLINK;
        }
        _velo_power_blink += _acce_power_blink;
    } else if (_method == BEAT_BLINK_LINER) {
        _power_blink += _velo_power_blink;
        if (_top_power_blink <= _power_blink) {
            _power_blink = _top_power_blink;
            _velo_power_blink = -2.0f * (_top_power_blink - _bottom_power_blink) / (int)_beat_target_frames;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        } else if (_bottom_power_blink >= _power_blink) {
            _power_blink = _bottom_power_blink;
            _velo_power_blink = 2.0f * (_top_power_blink - _bottom_power_blink) / (int)_beat_target_frames;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        }

    } else if (_method == BEAT_BLINK_TRIANGLEWAVE) {
        _beat_frame_count++;
        if (_beat_progres == 0) { //開始～アタックまで
            _power_blink += _velo_power_blink;
            if (_beat_frame_count >= _beat_attack_frames) { //アタック時
                _power_blink = _top_power_blink;
                _velo_power_blink = (_bottom_power_blink - _top_power_blink) / float(_beat_down_frames);
                _one_way_cnt++; //半ループカウント＋１
                if (_one_way_cnt == _stop_one_way_num) {
                    _method = NOBLINK;
                }
                _beat_progres = 1; //次へ
            }
        } else if (_beat_progres == 1) { //アタック～下限まで
            _power_blink += _velo_power_blink;
            if (_beat_frame_count >= _beat_attack_frames+_beat_down_frames) { //下限時
                _power_blink = _bottom_power_blink;
                _velo_power_blink = 0;
                _beat_progres = 2;//次へ
            }
        } else if (_beat_progres == 2) { //下限～終了まで
            if (_beat_frame_count >= _beat_target_frames) { //終了時
                _one_way_cnt++; //半ループカウント＋１
                if (_one_way_cnt == _stop_one_way_num) {
                    _method = NOBLINK;
                }
                _velo_power_blink = (_top_power_blink - _power_blink) / float(_beat_attack_frames);
                _beat_frame_count = 0; //カウンタリセット
                _beat_progres = 0;//次へ(元に戻る)
            }
        }
    }
    //Modelに反映
    _pModel->_power_blink = _power_blink;
    _pModel->_blinker_frames++;
}

//いつかまた使うでしょう
//            _TRACE_("---実行前");
//            _TRACE_("_pModel->_blinker_frames="<<_pModel->_blinker_frames);
//            _TRACE_("_bottom_power_blink["<<<<"]="<<_bottom_power_blink);
//            _TRACE_("_top_power_blink["<<<<"]="<<_top_power_blink);
//            _TRACE_("_beat_target_frames["<<<<"]="<<_beat_target_frames);
//            _TRACE_("_beat_attack_frames["<<<<"]="<<_beat_attack_frames);
//            _TRACE_("_beat_rest_frames["<<<<"]="<<_beat_rest_frames);
//            _TRACE_("_beat_target_frames["<<<<"] - _beat_attack_frames["<<<<"] - _beat_rest_frames["<<<<"]) = " << (_beat_target_frames - _beat_attack_frames - _beat_rest_frames));
//            _TRACE_("(_bottom_power_blink["<<<<"] - _top_power_blink["<<<<"]) / (_beat_target_frames["<<<<"] - _beat_attack_frames["<<<<"] - _beat_rest_frames["<<<<"])="<<((int)(_bottom_power_blink - _top_power_blink) / (int)(_beat_target_frames - _beat_attack_frames - _beat_rest_frames)));
//            _TRACE_("_bottom_power_blink["<<<<"] - _top_power_blink["<<<<"]" << (_bottom_power_blink - _top_power_blink));
//            _TRACE_("_power_blink["<<<<"] _velo_power_blink["<<<<"]="<<_power_blink<<" "<<_velo_power_blink);

void GgafDxTextureBlinker::intoTargetBlinkLinerUntil(float prm_target_power_blink, frame prm_spend_frame) {
    //_TRACE_("intoTargetBlinkLinerUntil prm_="<<prm_<<"/prm_target_power_blink="<<prm_target_power_blink<<"/prm_spend_frame="<<prm_spend_frame);
    _method = TARGET_BLINK_LINER;
    _target_power_blink = prm_target_power_blink;
    _velo_power_blink = (prm_target_power_blink - _power_blink) / (int)prm_spend_frame;
    if (_velo_power_blink == 0.0f) {
        _method = NOBLINK;
    }
}

void GgafDxTextureBlinker::intoTargetBlinkAcceStep(float prm_target_power_blink, float prm_velo_power_blink, float prm_acce_power_blink) {
    _method = TARGET_BLINK_ACCELERATION;
    _target_power_blink = prm_target_power_blink;
    _velo_power_blink = prm_velo_power_blink;
    _acce_power_blink = prm_acce_power_blink;
}

void GgafDxTextureBlinker::intoTargetBlinkLinerStep(float prm_target_power_blink, float prm_velo_power_blink) {
    _method = TARGET_BLINK_LINER;
    _target_power_blink = prm_target_power_blink;
    _velo_power_blink = sgn(prm_target_power_blink - _power_blink)*prm_velo_power_blink;
}

void GgafDxTextureBlinker::loopLiner(frame prm_beat_target_frames, float prm_beat_num) {
    _method = BEAT_BLINK_LINER;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);
    _beat_target_frames = prm_beat_target_frames;
    _velo_power_blink = (_top_power_blink - _power_blink) / ((int)prm_beat_target_frames / 2);
    if (_velo_power_blink == 0.0f) {
        _velo_power_blink = 0.1f; //0は困る
    }
}


void GgafDxTextureBlinker::beat(frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    _method = BEAT_BLINK_TRIANGLEWAVE;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);

    _beat_attack_frames = prm_attack_frames;
    _beat_rest_frames = prm_rest_frames;
    _beat_target_frames = prm_beat_target_frames;
    _beat_down_frames = _beat_target_frames - _beat_attack_frames - _beat_rest_frames;
    _beat_frame_count = 0;

    //最初のアタックまでのvelo
    if (_beat_attack_frames > 0) {
        _velo_power_blink = (_top_power_blink - _power_blink) / float(_beat_attack_frames);
        _beat_progres = 0;
    } else { //アタックまでが無いの場合
        _power_blink = _top_power_blink;
        _velo_power_blink = (_bottom_power_blink - _top_power_blink) / float(_beat_down_frames);
        _one_way_cnt++; //半ループカウント＋１
        _beat_progres = 1;
    }
}

void GgafDxTextureBlinker::stopImmed() {
    _method = NOBLINK;
}

GgafDxTextureBlinker::~GgafDxTextureBlinker() {
}
