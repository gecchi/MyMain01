#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TextureBlinker::GgafDx9TextureBlinker(GgafDx9Model* prm_pModel) :
    GgafObject() {
    _pModel = prm_pModel;
    _fPowerBlink = 1.0f;
    _velo_fPowerBlink = 0.0f;
    _acce_fPowerBlink = 0.0f;
    _target_fPowerBlink = 1.0f;
    _top_fPowerBlink = 1000.0f;
    _bottom_fPowerBlink = 0.0f;
    _one_way_cnt = 0;
    _beat_attack_frame = 0;
    _beat_rest_frame = 0;
    _beat_begin_frame = 0;
    _beat_spend_frame = 0;
    _stop_one_way_num = -1;
    _method = NOBLINK;
}

void GgafDx9TextureBlinker::behave() {

    if (_method == NOBLINK) {
        return;
    } else if (_method == TARGET_BLINK_LINER) {

        _fPowerBlink += _velo_fPowerBlink;

        //_TRACE_("_velo_fPowerBlink["<<<<"]="<<_velo_fPowerBlink<<"/_target_fPowerBlink["<<<<"]="<<_target_fPowerBlink<<"/_fPowerBlink["<<<<"]="<<_fPowerBlink);
        if (_velo_fPowerBlink > 0.0f && _target_fPowerBlink <= _fPowerBlink) {
            //_TRACE_("END1");
            _fPowerBlink = _target_fPowerBlink;
            _method = NOBLINK;
        } else if (_velo_fPowerBlink < 0.0f && _target_fPowerBlink >= _fPowerBlink) {
            //_TRACE_("END2");
            _fPowerBlink = _target_fPowerBlink;
            _method = NOBLINK;
        }
    } if (_method == TARGET_BLINK_ACCELERATION) {
        _fPowerBlink += _velo_fPowerBlink;
        if (_velo_fPowerBlink > 0.0f && _target_fPowerBlink <= _fPowerBlink) {
            _fPowerBlink = _target_fPowerBlink;
            _method = NOBLINK;
        } else if (_velo_fPowerBlink < 0.0f && _target_fPowerBlink >= _fPowerBlink) {
            _fPowerBlink = _target_fPowerBlink;
            _method = NOBLINK;
        }
        _velo_fPowerBlink += _acce_fPowerBlink;
    } else if (_method == BEAT_BLINK_LINER) {
        _fPowerBlink += _velo_fPowerBlink;
        if (_top_fPowerBlink <= _fPowerBlink) {
            _fPowerBlink = _top_fPowerBlink;
            _velo_fPowerBlink = -2.0f * (_top_fPowerBlink - _bottom_fPowerBlink) / (int)_beat_spend_frame;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        } else if (_bottom_fPowerBlink >= _fPowerBlink) {
            _fPowerBlink = _bottom_fPowerBlink;
            _velo_fPowerBlink = 2.0f * (_top_fPowerBlink - _bottom_fPowerBlink) / (int)_beat_spend_frame;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        }

    } else if (_method == BEAT_BLINK_TRIANGLEWAVE) {
        _fPowerBlink += _velo_fPowerBlink;
        //_TRACE_("_beat_begin_frame="<<_beat_begin_frame<<" _beat_attack_frame="<<_beat_attack_frame<<" _pModel->_frame_blinker="<<_pModel->_frame_blinker<<" | _fPowerBlink="<<_fPowerBlink<<" _velo_fPowerBlink="<<_velo_fPowerBlink<<"");
        if (_beat_begin_frame + _beat_attack_frame == _pModel->_frame_blinker) { //アタック頂点時
            _fPowerBlink = _top_fPowerBlink;
            _velo_fPowerBlink = (_bottom_fPowerBlink - _top_fPowerBlink) / ((int)_beat_spend_frame - (int)_beat_attack_frame - (int)_beat_rest_frame);
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        } else if (_bottom_fPowerBlink > _fPowerBlink) {  //if (_bottom_fPowerBlink >= _fPowerBlink) では次に行かないので駄目ですよ！
            _fPowerBlink = _bottom_fPowerBlink;
            _velo_fPowerBlink = 0;
        } else if (_beat_begin_frame + _beat_spend_frame == _pModel->_frame_blinker) { //ループ終了時
            _beat_begin_frame = _pModel->_frame_blinker;
            _velo_fPowerBlink = (_top_fPowerBlink - _bottom_fPowerBlink) / (int)_beat_attack_frame;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        }
    }
    //Modelに反映
    _pModel->_fPowerBlink = _fPowerBlink;
    _pModel->_frame_blinker++;
}

//いつかまた使うでしょう
//            _TRACE_("---実行前");
//            _TRACE_("_pModel->_frame_blinker="<<_pModel->_frame_blinker);
//            _TRACE_("_bottom_fPowerBlink["<<<<"]="<<_bottom_fPowerBlink);
//            _TRACE_("_top_fPowerBlink["<<<<"]="<<_top_fPowerBlink);
//            _TRACE_("_beat_spend_frame["<<<<"]="<<_beat_spend_frame);
//            _TRACE_("_beat_attack_frame["<<<<"]="<<_beat_attack_frame);
//            _TRACE_("_beat_rest_frame["<<<<"]="<<_beat_rest_frame);
//            _TRACE_("_beat_spend_frame["<<<<"] - _beat_attack_frame["<<<<"] - _beat_rest_frame["<<<<"]) = " << (_beat_spend_frame - _beat_attack_frame - _beat_rest_frame));
//            _TRACE_("(_bottom_fPowerBlink["<<<<"] - _top_fPowerBlink["<<<<"]) / (_beat_spend_frame["<<<<"] - _beat_attack_frame["<<<<"] - _beat_rest_frame["<<<<"])="<<((int)(_bottom_fPowerBlink - _top_fPowerBlink) / (int)(_beat_spend_frame - _beat_attack_frame - _beat_rest_frame)));
//            _TRACE_("_bottom_fPowerBlink["<<<<"] - _top_fPowerBlink["<<<<"]" << (_bottom_fPowerBlink - _top_fPowerBlink));
//            _TRACE_("_fPowerBlink["<<<<"] _velo_fPowerBlink["<<<<"]="<<_fPowerBlink<<" "<<_velo_fPowerBlink);

void GgafDx9TextureBlinker::intoTargetBlinkLinerUntil(float prm_target_fPowerBlink, DWORD prm_spend_frame) {
    //_TRACE_("intoTargetBlinkLinerUntil prm_="<<prm_<<"/prm_target_fPowerBlink="<<prm_target_fPowerBlink<<"/prm_spend_frame="<<prm_spend_frame);
    _method = TARGET_BLINK_LINER;
    _target_fPowerBlink = prm_target_fPowerBlink;
    _velo_fPowerBlink = (prm_target_fPowerBlink - _fPowerBlink) / (int)prm_spend_frame;
    //_TRACE_("intoTargetBlinkLinerUntil prm_target_fPowerBlink="<<prm_target_fPowerBlink<<"/ _fPowerBlink["<<prm_<<"]="<<_fPowerBlink);
    //_TRACE_("intoTargetBlinkLinerUntil _velo_fPowerBlink["<<prm_<<"]="<<_velo_fPowerBlink);
    if (_velo_fPowerBlink == 0.0f) {
        _method = NOBLINK;
    }
}

void GgafDx9TextureBlinker::intoTargetBlinkAcceStep(float prm_target_fPowerBlink, float prm_velo_fPowerBlink, float prm_acce_fPowerBlink) {
    _method = TARGET_BLINK_ACCELERATION;
    _target_fPowerBlink = prm_target_fPowerBlink;
    _velo_fPowerBlink = prm_velo_fPowerBlink;
    _acce_fPowerBlink = prm_acce_fPowerBlink;
}

void GgafDx9TextureBlinker::intoTargetBlinkLinerStep(float prm_target_fPowerBlink, float prm_velo_fPowerBlink) {
    _method = TARGET_BLINK_LINER;
    _target_fPowerBlink = prm_target_fPowerBlink;
    _velo_fPowerBlink = sgn(prm_target_fPowerBlink - _fPowerBlink)*prm_velo_fPowerBlink;
}

void GgafDx9TextureBlinker::loopLiner(DWORD prm_beat_spend_frame, float prm_beat_num) {
    _method = BEAT_BLINK_LINER;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);
    _beat_spend_frame = prm_beat_spend_frame;
    _velo_fPowerBlink = (_top_fPowerBlink - _fPowerBlink) / ((int)prm_beat_spend_frame / 2);
    if (_velo_fPowerBlink == 0.0f) {
        _velo_fPowerBlink = 0.1f; //0は困る
    }
}


void GgafDx9TextureBlinker::beat(DWORD prm_beat_spend_frame, DWORD prm_attack_frame, DWORD prm_rest_frame, float prm_beat_num) {
    _method = BEAT_BLINK_TRIANGLEWAVE;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);

    _beat_attack_frame = prm_attack_frame;
    _beat_rest_frame = prm_rest_frame;
    _beat_begin_frame = _pModel->_frame_blinker;
    _beat_spend_frame = prm_beat_spend_frame;

    _velo_fPowerBlink = (_top_fPowerBlink - _fPowerBlink) / (int)prm_attack_frame;
//    if (_velo_fPowerBlink == 0.0f) {
//        _velo_fPowerBlink = 0.0f;
//    }
}

void GgafDx9TextureBlinker::stopImmediately() {
    _method = NOBLINK;
}

GgafDx9TextureBlinker::~GgafDx9TextureBlinker() {
}
