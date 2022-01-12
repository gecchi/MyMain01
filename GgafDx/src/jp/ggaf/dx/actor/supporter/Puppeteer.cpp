#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/actor/BoneAniMeshActor.h"

using namespace GgafDx;


Puppeteer::Performance::Performance() {
    _pAnimationSet = nullptr;
    _animation_set_index = 0;
//    _local_time._t_value = 0.0;
    _target_loop        = -1;
    _loop_count         = 0;
    _period             = 1.0;
//    _weight._t_value = 1.0;
    _method             = NO_CHENGE;
    _p1 = 0.0;
    _p2 = 1.0;
}
void Puppeteer::Performance::setAnimationSet(LPD3DXANIMATIONSET prm_pAnimationSet, UINT prm_animation_set_index) {
    _pAnimationSet = prm_pAnimationSet;
    _animation_set_index = prm_animation_set_index;
    _period = _pAnimationSet->GetPeriod();
}
Puppeteer::Performance::~Performance() {
}


//26693083 <DEBUG> [0] Enable=1
//26693083 <DEBUG> [0] Position=0
//26693083 <DEBUG> [0] Speed=1
//26693083 <DEBUG> [0] Weight=1
//26693083 <DEBUG> [0] Priority=0
//26693083 <DEBUG> [1] Enable=0
//26693083 <DEBUG> [1] Position=0
//26693083 <DEBUG> [1] Speed=0
//26693083 <DEBUG> [1] Weight=0
//26693083 <DEBUG> [1] Priority=0
Puppeteer::Puppeteer() {
    _pAc = nullptr;
    _advance_time = 0.0;
    _ani_time_delta =  0.0;
    _num_perform = 0;
    _paPerformances = nullptr;
    _pStickMain = NEW Stick;
    _pStickSub = NEW Stick;
    _apStick[0] = _pStickMain;
    _apStick[1] = _pStickSub;

}
Puppeteer::Puppeteer(ID3DXAnimationController* prm_pAc_cloned,
                     double prm_ani_time_delta) : GgafCore::Object() {
    _paPerformances = nullptr;
    _pAc = prm_pAc_cloned;
    _advance_time = 0.0;
//    _TRACE_("Puppeteer::Puppeteer!!!!");
//    D3DXTRACK_DESC TD;   // �g���b�N�̔\��
//    for (int tno = 0; tno < 2; tno++) {
//        prm_pAc_cloned->GetTrackDesc(tno, &TD);
//        _TRACE_("["<<tno<<"] Enable="<<TD.Enable);
//        _TRACE_("["<<tno<<"] Position="<<TD.Position);
//        _TRACE_("["<<tno<<"] Speed="<<TD.Speed);
//        _TRACE_("["<<tno<<"] Weight="<<TD.Weight);
//        _TRACE_("["<<tno<<"] Priority="<<TD.Priority);
//    }
    HRESULT hr;
    //�O���[�o�����Ԃ�0�ɂ���
    hr = _pAc->ResetTime();
    checkDxException(hr, D3D_OK, "���s���܂����B");

    _ani_time_delta =  prm_ani_time_delta; //�f�t�H���g�͂Ƃ肠�����}���y�P�Q�l�l 4800�t���[����1�b
    _pStickMain = NEW Stick;
    _pStickSub = NEW Stick;
    _apStick[0] = _pStickMain;
    _apStick[1] = _pStickSub;

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
    UINT max_num_tracks = _pAc->GetMaxNumTracks();
    for (UINT tno = 0; tno < max_num_tracks; tno++) {
        hr = _pAc->SetTrackEnable(tno, FALSE);
    }

    //���[�V������񏉊���
    _paPerformances = NEW Performance[_num_perform];
    for (UINT i = 0; i < _num_perform; i++) {
        LPD3DXANIMATIONSET pAnimationSet;
        hr = _pAc->GetAnimationSet(i, &(pAnimationSet)); //�A�j���[�V�����Z�b�g�ێ�
        checkDxException(hr, D3D_OK, "���s���܂����B");
        _paPerformances[i].setAnimationSet(pAnimationSet, i);
    }

    //Stick������(�g���b�N�����ݒ�)
    _pStickMain->_tno = 0;
    _pStickMain->_pPerformance = nullptr;
    _pStickMain->_weight.setRange(0.000001, 1.0);
    _pStickMain->_weight._t_value = 1.0;

    _pStickSub->_tno = 1;
    _pStickSub->_pPerformance = nullptr;
    _pStickSub->_weight.setRange(0.000001, 1.0);
    _pStickSub->_weight._t_value = 0.0;

    //���f
    ID3DXAnimationController* pAc = _pAc;
    for (UINT hand = 0; hand < 2; hand++) {
        UINT tno = _apStick[hand]->_tno;
        Performance* p = _apStick[hand]->_pPerformance;
        if (p) {
            hr = pAc->SetTrackEnable(tno, TRUE);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            hr = pAc->SetTrackAnimationSet(tno, p->_pAnimationSet); _apAs[tno] = p->_pAnimationSet;
            checkDxException(hr, D3D_OK, "���s���܂����B");
        } else {
            hr = pAc->SetTrackEnable(tno, FALSE);  _apAs[tno] = nullptr;
            checkDxException(hr, D3D_OK, "���s���܂����B");

        }
    }

}


void Puppeteer::play(UINT prm_performance_no) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() �A�j��ID���͈͊O�ł��Bprm_performance_no="<<prm_performance_no);
    }

    Performance* p = &(_paPerformances[prm_performance_no]);
    _pStickMain->_pPerformance = p;
    UINT main_tno = _pStickMain->_tno;
    _pStickMain->_weight._t_value = 1.0;
    _pStickMain->_weight.stop();

    HRESULT hr;
    hr = _pAc->SetTrackEnable(main_tno, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackAnimationSet(main_tno, _pStickMain->_pPerformance->_pAnimationSet); _apAs[main_tno] = _pStickMain->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackSpeed(main_tno, 1.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackPosition(main_tno, 0.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(main_tno, _pStickMain->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");

    UINT sub_tno = _pStickSub->_tno;
    _pStickSub->_weight._t_value = 0.0;
    _pStickSub->_weight.stop();
    hr = _pAc->SetTrackEnable(sub_tno, FALSE);  _apAs[sub_tno] = nullptr;
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}
void Puppeteer::shiftTo(UINT prm_performance_no, frame prm_switch_frames) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() �A�j��ID���͈͊O�ł��Bprm_performance_no="<<prm_performance_no);
    }

    Performance* p = &(_paPerformances[prm_performance_no]);
    if (_pStickMain->_pPerformance == p) {
        _TRACE_("Puppeteer::shiftTo() prm_performance_no="<<prm_performance_no<<" �͊��ɃA�j���[�V�������̈ז�������܂����B");
        return;
    }

    _pStickSub->_pPerformance = p;
    _pStickSub->_weight.setValueBottom();
    _pStickSub->_weight.transitionLinearToTop(prm_switch_frames);
    UINT sub_tno = _pStickSub->_tno;
    HRESULT hr;
    hr = _pAc->SetTrackEnable(sub_tno, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackAnimationSet(sub_tno, _pStickSub->_pPerformance->_pAnimationSet); _apAs[sub_tno] = _pStickSub->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackSpeed(sub_tno, 1.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackPosition(sub_tno, 0.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");

    if (_pStickMain->_pPerformance) {
        _pStickMain->_weight.setValueTop();
        _pStickMain->_weight.transitionLinearToBottom(prm_switch_frames);
        UINT main_tno = _pStickMain->_tno;
        hr = _pAc->SetTrackEnable(main_tno, TRUE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackWeight(main_tno,_pStickMain->_weight._t_value);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }


    //Main��Sub������
    Stick* pWk = _pStickMain;
    _pStickMain = _pStickSub;
    _pStickSub = pWk;

}

void Puppeteer::playPartly(UINT prm_performance_no, double prm_num_loop) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() �A�j��ID���͈͊O�ł��Bprm_performance_no="<<prm_performance_no);
    }
    Performance* p = &(_paPerformances[prm_performance_no]);
    if (_pStickMain->_pPerformance == p) {
        _TRACE_("Puppeteer::shiftTo() prm_performance_no="<<prm_performance_no<<" �͊��ɃA�j���[�V�������̈ז�������܂����B");
        return;
    }
    double spend_frames = p->_period*prm_num_loop / _ani_time_delta;
    _pStickSub->_pPerformance = p;
    _pStickSub->_weight.setValueBottom();
    _pStickSub->_weight.beat((frame)spend_frames,
                             (frame)(spend_frames*0.2), (frame)(spend_frames*0.6), (frame)(spend_frames*0.2),
                             prm_num_loop);
    UINT sub_tno = _pStickSub->_tno;
    HRESULT hr;
    hr = _pAc->SetTrackEnable(sub_tno, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackAnimationSet(sub_tno, _pStickSub->_pPerformance->_pAnimationSet); _apAs[sub_tno] = _pStickSub->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackSpeed(sub_tno, 1.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackPosition(sub_tno, 0.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");

    _pStickMain->_weight.setValueTop();
    _pStickMain->_weight.rbeat((frame)spend_frames,
                               (frame)(spend_frames*0.2), (frame)(spend_frames*0.6), (frame)(spend_frames*0.2),
                               prm_num_loop);
    UINT main_tno = _pStickMain->_tno;
    hr = _pAc->SetTrackEnable(main_tno, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(main_tno,_pStickMain->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}

void Puppeteer::behave() {
    HRESULT hr;
    UINT main_tno = _pStickMain->_tno;
    if (_pStickMain->_weight.isTransitioning()) {
        _pStickMain->_weight.behave();
        hr = _pAc->SetTrackWeight(main_tno, _pStickMain->_weight._t_value);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }

    UINT sub_tno = _pStickSub->_tno;
    if (_pStickSub->_weight.isTransitioning()) {
        _pStickSub->_weight.behave();
        hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    } else {
        hr = _pAc->SetTrackEnable(sub_tno, FALSE); _apAs[sub_tno] = nullptr;
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }
    _advance_time += _ani_time_delta;
}

void Puppeteer::stop() {
    HRESULT hr;
    for (UINT tno = 0; tno < 2; tno++) {
        hr = _pAc->SetTrackEnable(tno, FALSE); _apAs[tno] = nullptr;
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }
}

void Puppeteer::updateAnimationTrack() {
    HRESULT hr;
    hr = _pAc->AdvanceTime(_advance_time, nullptr);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    _advance_time = 0;
}


Puppeteer::~Puppeteer() {
    GGAF_DELETE(_pStickMain);
    GGAF_DELETE(_pStickSub);
    GGAF_DELETE_NULLABLE(_paPerformances);
}
