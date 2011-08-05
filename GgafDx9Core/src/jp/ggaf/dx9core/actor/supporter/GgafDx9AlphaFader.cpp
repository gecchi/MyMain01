#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9AlphaFader::GgafDx9AlphaFader(GgafDx9DrawableActor* prm_pActor) :
    GgafObject() {
    _pActor = prm_pActor;

    _alpha = _pActor->getAlpha();
    _velo_alpha = 0.0f;
    _target_alpha = 1.0f;
    _top_alpha = 1.0f;
    _bottom_alpha = 0.0f;
    _one_way_cnt = 0;
    _beat_attack_frames = 0;
    _beat_rest_frames = 0;
    _beat_target_frames = 0;
    _beat_down_frames = 0;
    _beat_frame_count = 0;
    _beat_progres = 0;
    _stop_one_way_num = -1;
    _method = NO_ALPHAFADE;
}

void GgafDx9AlphaFader::behave() {
    if (_method == NO_ALPHAFADE) {
        return;
    } else if (_method == TARGET_ALPHAFADE_LINER) {

        _alpha += _velo_alpha;

        //_TRACE_("_velo_alpha["<<c<<"]="<<_velo_alpha<<"/_target_alpha["<<c<<"]="<<_target_alpha<<"/_alpha["<<c<<"]="<<_alpha);
        if (_velo_alpha > 0 && _target_alpha <= _alpha) {
            //_TRACE_("END1");
            _alpha = _target_alpha;
            _method = NO_ALPHAFADE;
        } else if (_velo_alpha < 0 && _target_alpha >= _alpha) {
            //_TRACE_("END2");
            _alpha = _target_alpha;
            _method = NO_ALPHAFADE;
        }
    } else if (_method == TARGET_ALPHAFADE_ACCELERATION) {
        _alpha += _velo_alpha;
        //if (_velo_alpha > 0 && _target_alpha <= _alpha) {
        if (_acce_alpha > 0 && _target_alpha <= _alpha) {
            _alpha = _target_alpha;
            _method = NO_ALPHAFADE;
        //} else if (_velo_alpha < 0 && _target_alpha >= _alpha) {
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
        if (_beat_progres == 0) { //�J�n�`�A�^�b�N�܂�
            _alpha += _velo_alpha;
            if (_beat_frame_count >= _beat_attack_frames) { //�A�^�b�N��
                _alpha = _top_alpha;
                _velo_alpha = (_bottom_alpha - _top_alpha) / int(_beat_down_frames);
                _one_way_cnt++; //�����[�v�J�E���g�{�P
                if (_one_way_cnt == _stop_one_way_num) {
                    _method = NO_ALPHAFADE;
                }
                _beat_progres = 1; //����
            }
        } else if (_beat_progres == 1) { //�A�^�b�N�`�����܂�
            _alpha += _velo_alpha;
            if (_beat_frame_count >= _beat_attack_frames+_beat_down_frames) { //������
                _alpha = _bottom_alpha;
                _velo_alpha = 0;
                _beat_progres = 2;//����
            }
        } else if (_beat_progres == 2) { //�����`�I���܂�
            if (_beat_frame_count >= _beat_target_frames) { //�I����
                _one_way_cnt++; //�����[�v�J�E���g�{�P
                if (_one_way_cnt == _stop_one_way_num) {
                    _method = NO_ALPHAFADE;
                }
                _velo_alpha = (_top_alpha - _alpha) / int(_beat_attack_frames);
                _beat_frame_count = 0; //�J�E���^���Z�b�g
                _beat_progres = 0;//����(���ɖ߂�)
            }
        }
    }
    //Actor�ɔ��f
    _pActor->setAlpha(_alpha);
}

void GgafDx9AlphaFader::intoTargetAlphaLinerUntil(float prm_target_alpha, frame prm_spend_frame) {
    //_TRACE_("intoTargetAlphaLinerUntil prm_c="<<prm_c<<"/prm_target_alpha="<<prm_target_alpha<<"/prm_spend_frame="<<prm_spend_frame);
    _method = TARGET_ALPHAFADE_LINER;
    _target_alpha = prm_target_alpha;
    _velo_alpha = (prm_target_alpha - _alpha) / (int)prm_spend_frame;
    //_TRACE_("intoTargetAlphaLinerUntil prm_target_alpha="<<prm_target_alpha<<"/ _alpha["<<prm_c<<"]="<<_alpha);
    //_TRACE_("intoTargetAlphaLinerUntil _velo_alpha["<<prm_c<<"]="<<_velo_alpha);
    if (int(_velo_alpha*1000.0) == 0) {
        _velo_alpha = prm_target_alpha - _alpha;
    }
}

void GgafDx9AlphaFader::intoTargetAlphaAcceStep(float prm_target_alpha, float prm_velo_alpha, float prm_acce_alpha) {
    _method = TARGET_ALPHAFADE_ACCELERATION;
    _target_alpha = prm_target_alpha;
    _velo_alpha = prm_velo_alpha;
    _acce_alpha = prm_acce_alpha;
}

void GgafDx9AlphaFader::intoTargetAlphaLinerStep(float prm_target_alpha, float prm_velo_alpha) {
    _method = TARGET_ALPHAFADE_LINER;
    _target_alpha = prm_target_alpha;
    _velo_alpha = sgn(prm_target_alpha - _alpha)*prm_velo_alpha;
}


void GgafDx9AlphaFader::loopLiner(frame prm_beat_target_frames, float prm_beat_num) {
    _method = BEAT_ALPHAFADE_LINER;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);
    _beat_target_frames = prm_beat_target_frames;
    _velo_alpha = (_top_alpha - _alpha) / ((int)prm_beat_target_frames / 2);
    if (int(_velo_alpha*1000.0) == 0) {
        _velo_alpha = _top_alpha - _alpha;
    }
}

void GgafDx9AlphaFader::beat(frame prm_beat_target_frames, frame prm_attack_frames, frame prm_rest_frames, float prm_beat_num) {
    _method = BEAT_ALPHAFADE_TRIANGLEWAVE;
    _one_way_cnt = 0;
    _stop_one_way_num = (int)(prm_beat_num*2.0f);

    _beat_attack_frames = prm_attack_frames;
    _beat_rest_frames = prm_rest_frames;
    _beat_target_frames = prm_beat_target_frames;
    _beat_down_frames = _beat_target_frames - _beat_attack_frames - _beat_rest_frames;
    _beat_frame_count = 0;

    //�ŏ��̃A�^�b�N�܂ł�velo
    if (_beat_attack_frames > 0) {
        _velo_alpha = (_top_alpha - _alpha) / int(_beat_attack_frames);
        _beat_progres = 0;
    } else { //�A�^�b�N�܂ł������̏ꍇ
        _alpha = _top_alpha;
        _velo_alpha = (_bottom_alpha - _top_alpha) / int(_beat_down_frames);
        _one_way_cnt++; //�����[�v�J�E���g�{�P
        _beat_progres = 1;
    }
}


GgafDx9AlphaFader::~GgafDx9AlphaFader() {
}