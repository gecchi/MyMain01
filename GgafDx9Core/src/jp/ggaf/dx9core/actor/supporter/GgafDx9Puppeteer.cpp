#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Puppeteer::GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet) : GgafObject() {
    _pPuppet = prm_pPuppet;
    _pModel = (GgafDx9D3DXAniMeshModel*)_pPuppet->_pGgafDx9Model;
    HRESULT hr = _pModel->_pAcBase->CloneAnimationController(
                                        _pModel->_pAcBase->GetMaxNumAnimationOutputs(),
                                        _pModel->_pAcBase->GetMaxNumAnimationSets(),
                                        _pModel->_pAcBase->GetMaxNumTracks(),
                                        _pModel->_pAcBase->GetMaxNumEvents(),
                                        &_pAc);
    checkDxException(hr, D3D_OK, "GgafDx9Puppeteer::GgafDx9Puppeteer() �A�j���[�V�����R���g���[���[�̃N���[���Ɏ��s���܂����Bname="<<_pPuppet->getName());
    _num_tricks = _pAc->GetMaxNumAnimationSets();
    if (_pAc->GetMaxNumTracks() < 2) {
    throwGgafCriticalException("GgafDx9Puppeteer �A�j���[�V�����g���b�N�͏��Ȃ��Ƃ�2�K�v�ł��B");
    }
    _TRACE_("_pAc->GetMaxNumTracks()="<<_pAc->GetMaxNumTracks());
    _TRACE_("_pAc->GetMaxNumAnimationSets()="<<_pAc->GetMaxNumAnimationSets());

//    _advance_time_per_frame = 1.0 / 60.0; //60����1�b
    _advance_time_per_draw = 0.0;

    //���[�V����������
    _paPerformances = NEW Performance[_num_tricks];
    for (UINT i = 0; i < _num_tricks; i++) {
        hr = _pAc->GetAnimationSet(i, &(_paPerformances[i]._pAnimationSet)); //�A�j���[�V�����Z�b�g�ێ�
        checkDxException(hr, D3D_OK, "���s���܂����B");
        _paPerformances[i]._is_playing = false;
        _paPerformances[i]._method = NO_MOTION;
        _paPerformances[i]._speed = 1.0;
//        _paPerformances[i]._weight = 1.0;
        _paPerformances[i]._target_time = 0.0;
        _paPerformances[i]._total_time = _paPerformances[i]._pAnimationSet->GetPeriod();
//        _paPerformances[i]._one_loop_time = _paPerformances[i]._total_time * _paPerformances[i]._speed ;
//        _paPerformances[i]._velo_time = (1.0 / 60.0) * _paPerformances[i]._speed;
        _paPerformances[i]._local_time = 0.0;

    }

    hr = _pAc->ResetTime();//�O���[�o�����Ԃ�0�ɂ���
    checkDxException(hr, D3D_OK, "���s���܂����B");

    //�g���b�N������
    for (UINT i = 0; i < 2; i++) {
        hr = _pAc->SetTrackEnable(i, FALSE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackPosition(i, 0); //�g���b�N���[�J�����Ԃ�0�ɂ���
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackSpeed(i, 1.0f);  //�g���b�N�X�s�[�h��ݒ�B
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackWeight(i, 1.00);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }

    hr = _pAc->AdvanceTime(0,NULL);//0�b�i�߂�i����𔽉f������j�B
    checkDxException(hr, D3D_OK, "���s���܂����B");

//    for (DWORD i = 0; i < (DWORD)_pAc->GetMaxNumTracks(); i++) {
//        hr = _pAc->SetTrackEnable(i, FALSE);
//        checkDxException(hr, D3D_OK, "���s���܂����B");
//    }
    _aStick[LEFT_HANDED]._no = 0;
    _aStick[LEFT_HANDED]._pPerformance = NULL;
    _aStick[RIGHT_HANDED]._no = 0;
    _aStick[RIGHT_HANDED]._pPerformance = NULL;
    _active_hand = LEFT_HANDED;
    _pStickActive = &_aStick[_active_hand];

    _is_shifting_performance = false;
    _weight_per_frame_for_shift = 0;
    _shift_duaration = 0;
    _shifted = 0;
}

void GgafDx9Puppeteer::exchangStick() {
    _active_hand = !_active_hand;
    _pStickActive = &_aStick[_active_hand];
}
void GgafDx9Puppeteer::shift(UINT performance_no, frame shift_duaration, GgafDx9MotionMethod method) {
    _is_shifting_performance = true;
    _shift_duaration = shift_duaration;
    _shifted = 0;
    _weight_per_frame_for_shift = 1.0 / shift_duaration;
    exchangStick();
    play(performance_no, method);
}
void GgafDx9Puppeteer::play(UINT performance_no, double speed, GgafDx9MotionMethod method) {
    _paPerformances[performance_no]._speed = speed;
    HRESULT hr = _pAc->SetTrackSpeed(_pStickActive->_no, _pStickActive->_pPerformance->_speed);  //�g���b�N�X�s�[�h��ݒ�B
    checkDxException(hr, D3D_OK, "���s���܂����B");
    play(performance_no, method);
}


void GgafDx9Puppeteer::play(UINT performance_no, GgafDx9MotionMethod method) {
    _paPerformances[performance_no]._method = method;
    _pStickActive->_pPerformance = &(_paPerformances[performance_no]);
    HRESULT hr = _pAc->SetTrackAnimationSet(_pStickActive->_no, _pStickActive->_pPerformance->_pAnimationSet);//motion_id�Ԃ̃A�j���[�V�����Z�b�g���g���b�N0�ԂɃZ�b�g
    checkDxException(hr, D3D_OK, "���s���܂����B");

    play();
}
void GgafDx9Puppeteer::play() {
    _pStickActive->_pPerformance->_is_playing = true;
    HRESULT hr = _pAc->SetTrackEnable(_pStickActive->_no, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}
void GgafDx9Puppeteer::stop() {
    _pStickActive->_pPerformance->_is_playing = false;
    HRESULT hr = _pAc->SetTrackEnable(_pStickActive->_no, FALSE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}

void GgafDx9Puppeteer::behave() {
    _advance_time_per_draw += (1.0/60.0);
    for (UINT i = 0; i < 2; i++) {
        if (_aStick[i]._pPerformance) {
            Performance* p = _aStick[i]._pPerformance;
            if (p->_is_playing) {
                if (p->_method == LOOP_MOTION_LINER) {
                    p->_local_time += ((1.0 / 60.0) * _paPerformances[i]._speed);
                }
            }
        }
    }

    if (_is_shifting_performance) {
        _shifted++;
        if (_shifted < _shift_duaration) {
            //�V�t�g��
            double weight = 1.0 * _shifted / _shift_duaration;
            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_no, weight);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            hr = _pAc->SetTrackWeight(!(_pStickActive->_no), 1.00-weight);
            checkDxException(hr, D3D_OK, "���s���܂����B");
        } else if (_shifted == _shift_duaration) {
            //�V�t�g������
            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_no, 1.0);
            checkDxException(hr, D3D_OK, "���s���܂����B");

            _pStickActive->_pPerformance->_is_playing = false;
            hr = _pAc->SetTrackEnable(!(_pStickActive->_no), FALSE);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            hr = _pAc->SetTrackWeight(!(_pStickActive->_no), 1.00);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            _is_shifting_performance = false;
        }
    }
}
void GgafDx9Puppeteer::work() {
    //�A�j���[�V������i�߂�B
    for (UINT i = 0; i < 2; i++) {
        if (_aStick[i]._pPerformance) {
            HRESULT hr = _pAc->SetTrackPosition(i, _aStick[i]._pPerformance->_local_time); //�g���b�N���[�J������
            checkDxException(hr, D3D_OK, "���s���܂����B");
        }
    }

    HRESULT hr = _pAc->AdvanceTime(_advance_time_per_draw, NULL );
    checkDxException(hr, D3D_OK, "���s���܂����B");
    _advance_time_per_draw = 0; //���Z�b�g
    //���f���̃��[���h�ϊ��s��X�V
    _pModel->_stackWorldMat.SetWorldMatrix(&(_pPuppet->_matWorld));
    _pModel->_stackWorldMat.UpdateFrame(_pModel->_pFR);
}

GgafDx9Puppeteer::~GgafDx9Puppeteer() {
    DELETEARR_IMPOSSIBLE_NULL(_paPerformances);
}





