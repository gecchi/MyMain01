#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/actor/BoneAniMeshActor.h"

using namespace GgafDx;


Puppeteer::Performance::Performance() {
    _pAnimationSet = nullptr;
    _animation_set_index = 0;
    _local_time._t_value = 0.0;
    _target_loop        = -1;
    _loop_count         = 0;
    _period             = 1.0;
    _weight._t_value = 1.0;
    _method             = NO_CHENGE;

}
void Puppeteer::Performance::setAnimationSet(LPD3DXANIMATIONSET prm_pAnimationSet, UINT prm_animation_set_index) {
    _pAnimationSet = prm_pAnimationSet;
    _animation_set_index = prm_animation_set_index;
    _period = _pAnimationSet->GetPeriod();
}
Puppeteer::Performance::~Performance() {
}



Puppeteer::Puppeteer(ID3DXAnimationController* prm_pAc_cloned) : GgafCore::Object() {
    _paPerformances = nullptr;
    _pAc = prm_pAc_cloned;
    _ani_time_delta =  60.0 / 4800; //�f�t�H���g�͂Ƃ肠�����}���y�P�Q�l�l
    _speed_rate = 1.0;
    HRESULT hr;
    _num_perform = _pAc->GetMaxNumAnimationSets();
#ifdef MY_DEBUG
    if (_num_perform == 0) {
        throwCriticalException("Puppeteer �A�j���[�V�����Z�b�g���������܂���B");
    }
    if (_pAc->GetMaxNumTracks() < 2) {
        throwCriticalException("Puppeteer �A�j���[�V�����g���b�N�����Ȃ��Ƃ�2�K�v�ł��B���g�p�̃r�f�I�J�[�h�ł̓g���b�N�@�\������܂���B");
    }
#endif
    //int x = 'o'  ^0^  -~-  -0-  ~-~  +0+  0-0  *0*  0*0;


    //���[�V������񏉊���
    double min_period = DBL_MAX;
    _paPerformances = NEW Performance[_num_perform];
    for (UINT i = 0; i < _num_perform; i++) {
        LPD3DXANIMATIONSET pAnimationSet;
        hr = _pAc->GetAnimationSet(i, &(pAnimationSet)); //�A�j���[�V�����Z�b�g�ێ�
        checkDxException(hr, D3D_OK, "���s���܂����B");
        _paPerformances[i].setAnimationSet(pAnimationSet, i);
        _paPerformances[i]._period = _paPerformances[i]._pAnimationSet->GetPeriod();
        if (min_period > _paPerformances[i]._period) {
            min_period = _paPerformances[i]._period;
        }
    }
    _ani_time_period = min_period;
    //�ŏ��� min_period �� 60�t���[��1�b�ŃA�j���[�V��������悤��
    //�f�t�H���g�� _ani_time_delta ��ݒ�B
    //�O���[�o�����Ԃ�0�ɂ���
    hr = _pAc->ResetTime();
    checkDxException(hr, D3D_OK, "���s���܂����B");
    //�A�j���[�V�����R���g���[���̃f�t�H���g�̂P�t���[��������̃A�j���[�V�����t���[��
    _ani_time_delta = _ani_time_period / 60.0; //60�t���[���łP���[�v����O���[�o���A�j�����Ԃ��f�t�H���g�ɂ��Ă���

    //Stick������(�g���b�N�����ݒ�)
    _aStick[LEFT_HAND]._tno = 0;
    _aStick[LEFT_HAND]._enable_motion_blend = TRUE;
    _aStick[LEFT_HAND]._pPerformance = &(_paPerformances[0]);

    _aStick[RIGHT_HAND]._tno = 1;
    _aStick[RIGHT_HAND]._enable_motion_blend = FALSE;
    _aStick[RIGHT_HAND]._pPerformance = nullptr;
}

void Puppeteer::exchangPerformance() {
    Performance* p2 = _aStick[RIGHT_HAND]._pPerformance;
    _aStick[RIGHT_HAND]._pPerformance = _aStick[LEFT_HAND]._pPerformance;
    _aStick[LEFT_HAND]._pPerformance = p2;

    HRESULT hr;
    if (_aStick[RIGHT_HAND]._pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_aStick[RIGHT_HAND]._tno, _aStick[RIGHT_HAND]._pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackEnable(_aStick[RIGHT_HAND]._tno, TRUE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    } else {
        hr = _pAc->SetTrackEnable(_aStick[RIGHT_HAND]._tno, FALSE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }

    if (_aStick[LEFT_HAND]._pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_aStick[LEFT_HAND]._tno, _aStick[LEFT_HAND]._pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackEnable(_aStick[LEFT_HAND]._tno, TRUE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    } else {
        hr = _pAc->SetTrackEnable(_aStick[LEFT_HAND]._tno, FALSE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }

}

void Puppeteer::play(PuppeteerStick prm_handed,
          UINT prm_performance_no,
          double prm_loopnum,
          PuppeteerMethod prm_method) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() �A�j��ID���͈͊O�ł��Bprm_performance_no="<<prm_performance_no);
    }
    Performance* p = &(_paPerformances[prm_performance_no]);
    p->_local_time.accelerateByDt(
            p->_period * prm_loopnum,           //VAL_TYPE prm_target_value_distance,
            (p->_period / _ani_time_delta) * prm_loopnum, //frame prm_frame_of_target,
            0.0, 1.0,            //double prm_p1, double prm_p2,
            0.0,                  //VAL_TYPE prm_end_velo,
            true                  //bool prm_zero_acc_end_flg
    );

    p->_target_loop = prm_loopnum;
    p->_loop_count = 0;
    p->_method     = prm_method;
    _aStick[prm_handed]._enable_motion_blend = TRUE;
    _aStick[prm_handed]._pPerformance = p;

    ID3DXAnimationController* pAc = _pAc;
    HRESULT hr;
    UINT tno = _aStick[prm_handed]._tno; //�g���b�N�ԍ�
    hr = pAc->SetTrackEnable(tno, _aStick[prm_handed]._enable_motion_blend);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = pAc->SetTrackAnimationSet(tno, p->_pAnimationSet);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = pAc->SetTrackPosition(tno, p->_local_time._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = pAc->SetTrackSpeed(tno, p->_period);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = pAc->SetTrackWeight(tno, p->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}

void Puppeteer::behave() {
    for (UINT i = 0; i < 2; i++) {
        Performance* p = _aStick[i]._pPerformance;
        if (p) {
            if (p->_method == NO_CHENGE) {
                break;
            } else if (p->_method == PLAY_LOOPING) {
                if (p->_local_time.isAccelerating()) {
                    p->_local_time.behave();
                } else {
                     p->_method = NO_CHENGE;
                }
            } else {
                throwCriticalException("����ȃ��\�b�h�͖͂��T�|�[�g�ł��B p->_method="<<p->_method);
            }
        }
    }

//    //�V�t�g����
//    if (_is_shifting_performance) {
//        _shifted++;
//        if (_shifted < _shift_duaration) {
//            //�V�t�g��
//            double weight = 1.0 * _shifted / _shift_duaration;
//            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_tno, weight);
//            checkDxException(hr, D3D_OK, "���s���܂����B");
//            hr = _pAc->SetTrackWeight(!(_pStickActive->_tno), 1.00-weight);
//            checkDxException(hr, D3D_OK, "���s���܂����B");
//        } else if (_shifted == _shift_duaration) {
//            //�V�t�g������
//            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_tno, 1.0);
//            checkDxException(hr, D3D_OK, "���s���܂����B");
//            hr = _pAc->SetTrackEnable(!(_pStickActive->_tno), FALSE);
//            checkDxException(hr, D3D_OK, "���s���܂����B");
//            hr = _pAc->SetTrackWeight(!(_pStickActive->_tno), 1.00);
//            checkDxException(hr, D3D_OK, "���s���܂����B");
//            _is_shifting_performance = false;
//        }
//    }

}

void Puppeteer::stop() {
    for (UINT hand = 0; hand < 2; hand++) {
        Performance* p = _aStick[hand]._pPerformance;
        if (p) {
            p->_method = NO_CHENGE;
        }
    }
}

void Puppeteer::updateAnimationTrack() {
    HRESULT hr;

    ID3DXAnimationController* pAc = _pAc;
    for (UINT hand = 0; hand < 2; hand++) {
        Stick* s = &(_aStick[hand]);
        UINT tno = s->_tno; //�g���b�N�ԍ�
        Performance* pPerformance = s->_pPerformance;
        if (pPerformance) {
            hr = pAc->SetTrackPosition(tno, pPerformance->_local_time._t_value);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            _paAs[tno] = pPerformance->_pAnimationSet;
        } else {
            _paAs[tno] = nullptr;
        }
    }
    //0�b�i�߂�i���Ƃɂ���Ĕ��f������j�B
    hr = pAc->AdvanceTime(0, nullptr);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}


Puppeteer::~Puppeteer() {
    GGAF_DELETEARR(_paPerformances);
}

