#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TextureBlinker::GgafDx9TextureBlinker(GgafDx9Model* prm_pModel) :
    GgafObject() {
    _pModel = prm_pModel;
    _power_blink = 1.0f;
    _velo_power_blink = 0.0f;
    _acce_power_blink = 0.0f;
    _target_power_blink = 1.0f;
    _top_power_blink = 1000.0f;
    _bottom_power_blink = 0.0f;
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
    } if (_method == TARGET_BLINK_ACCELERATION) {
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
            _velo_power_blink = -2.0f * (_top_power_blink - _bottom_power_blink) / (int)_beat_spend_frame;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        } else if (_bottom_power_blink >= _power_blink) {
            _power_blink = _bottom_power_blink;
            _velo_power_blink = 2.0f * (_top_power_blink - _bottom_power_blink) / (int)_beat_spend_frame;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        }

    } else if (_method == BEAT_BLINK_TRIANGLEWAVE) {
        _power_blink += _velo_power_blink;
        //_TRACE_("_beat_begin_frame="<<_beat_begin_frame<<" _beat_attack_frame="<<_beat_attack_frame<<" _pModel->_blinker_frame="<<_pModel->_blinker_frame<<" | _power_blink="<<_power_blink<<" _velo_power_blink="<<_velo_power_blink<<"");
        if (_beat_begin_frame + _beat_attack_frame == _pModel->_blinker_frame) { //アタック頂点時
            _power_blink = _top_power_blink;
            _velo_power_blink = (_bottom_power_blink - _top_power_blink) / ((int)_beat_spend_frame - (int)_beat_attack_frame - (int)_beat_rest_frame);
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        } else if (_bottom_power_blink > _power_blink) {  //if (_bottom_power_blink >= _power_blink) では次に行かないので駄目ですよ！
            _power_blink = _bottom_power_blink;
            _velo_power_blink = 0;
        } else if (_beat_begin_frame + _beat_spend_frame == _pModel->_blinker_frame) { //ループ終了時
            _beat_begin_frame = _pModel->_blinker_frame;
            _velo_power_blink = (_top_power_blink - _bottom_power_blink) / (int)_beat_attack_frame;
            _one_way_cnt++;
            if (_one_way_cnt == _stop_one_way_num) {
                _method = NOBLINK;
            }
        }
    }
    //Modelに反映
    _pModel->_power_blink = _power_blink;
    _pModel->_blinker_frame++;
}

//いつかまた使うでしょう
//            _TRACE_("---実行前");
//            _TRACE_("_pModel->_blinker_frame="<<_pModel->_blinker_frame);
//            _TRACE_("_bottom_power_blink["<<<<"]="<<_bottom_power_blink);
//            _TRACE_("_top_power_blink["<<<<"]="<<_top_power_blink);
//            _TRACE_("_beat_spend_frame["<<<<"]="<<_beat_spend_frame);
//            _TRACE_("_beat_attack_frame["<<<<"]="<<_beat_attack_frame);
//            _TRACE_("_beat_rest_frame["<<<<"]="<<_beat_rest_frame);
//            _TRACE_("_beat_spend_frame["<<<<"] - _beat_attack_frame["<<<<"] - _beat_rest_frame["<<<<"]) = " << (_beat_spend_frame - _beat_attack_frame - _beat_rest_frame));
//            _TRACE_("(_bottom_power_blink["<<<<"] - _top_power_blink["<<<<"]) / (_beat_spend_frame["<<<<"] - _beat_attack_frame["<<<<"] - _beat_rest_frame["<<<<"])="<<((int)(_bottom_power_blink - _top_power_blink) / (int)(_beat_spend_frame - _beat_attack_frame - _beat_rest_frame)));
//            _TRACE_("_bottom_power_blink["<<<<"] - _top_power_blink["<<<<"]" << (_bottom_power_blink - _top_power_blink));
//            _TRACE_("_power_blink["<<<<"] _velo_power_blink["<<<<"]="<<_power_blink<<" "<<_velo_power_blink);

void GgafDx9TextureBlinker::intoTargetBlinkLinerUntil(float prm_target_power_blink, frame prm_spend_frame) {
    //_TRACE_("intoTargetBlinkLinerUntil prm_="<<prm_<<"/prm_target_power_blink="<<prm_target_power_blink<<"/prm_spend_frame="<<prm_spend_frame);
    _method = TARGET_BLINK_LINER;
    _target_power_blink = prm_target_power_blink;
    _velo_power_blink = (prm_target_power_blink - _power_blink) / (int)prm_spend_frame;
    //_TRACE_("intoTargetBlinkLinerUntil prm_target_power_blink="<<prm_target_power_blink<<"/ _power_blink["<<prm_<<"]="<<_power_blink);
    //_TRACE_("intoTargetBlinkLinerUntil _velo_power_blink["<<prm_<<"]="<<_velo_power_blink);
    if (_velo_power_blink == 0.0f) {
        _method = NOBLINK;
    }
}

void GgafDx9TextureBlinker::intoTargetBlinkAcceStep(float prm_target_power_blink, float prm_velo_power_blink, float prm_acce_power_blink) {
    _method = TARGET_BLINK_ACCELERATION;
    _target_power_blink = prm_target_power_blink;
    _velo_power_blink = prm_velo_power_blink;
    _acce_power_blink = prm_acce_power_blink;
}

void GgafDx9TextureBlinker::intoTargetBlinkLinerStep(float prm_target_power_blink, float prm_velo_power_blink) {
    _method = TARGET_BLINK_LINER;
    _target_power_blink = prm_target_power_blink;
    _velo_power_blink = sgn(prm_target_power_blink - _power_blink)*prm_velo_power_blink;
}

void GgafDx9TextureBlinker::loopLiner(frame prm_beat_spend_frame, float prm_beat_num) {
    _method = BEAT_BLINK_LINER;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);
    _beat_spend_frame = prm_beat_spend_frame;
    _velo_power_blink = (_top_power_blink - _power_blink) / ((int)prm_beat_spend_frame / 2);
    if (_velo_power_blink == 0.0f) {
        _velo_power_blink = 0.1f; //0は困る
    }
}


void GgafDx9TextureBlinker::beat(frame prm_beat_spend_frame, frame prm_attack_frame, frame prm_rest_frame, float prm_beat_num) {
    _method = BEAT_BLINK_TRIANGLEWAVE;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);

    _beat_attack_frame = prm_attack_frame;
    _beat_rest_frame = prm_rest_frame;
    _beat_begin_frame = _pModel->_blinker_frame;
    _beat_spend_frame = prm_beat_spend_frame;

    _velo_power_blink = (_top_power_blink - _power_blink) / (int)prm_attack_frame;
//    if (_velo_power_blink == 0.0f) {
//        _velo_power_blink = 0.0f;
//    }
}

void GgafDx9TextureBlinker::stopImmediately() {
    _method = NOBLINK;
}

GgafDx9TextureBlinker::~GgafDx9TextureBlinker() {
}
