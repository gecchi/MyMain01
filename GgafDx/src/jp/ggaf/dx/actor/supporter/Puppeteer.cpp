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

    _ani_time_delta =  prm_ani_time_delta; //�f�t�H���g�͂Ƃ肠�����}���y�P�Q�l�l
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
//    _pStickMain->_pPerformance = &(_paPerformances[0]);
    _pStickMain->_pPerformance = nullptr;
    _pStickMain->_weight.setRange(0.0, 1.0);
    _pStickMain->_weight._t_value = 1.0;

    _pStickSub->_tno = 1;
    _pStickSub->_pPerformance = nullptr;
    _pStickSub->_weight.setRange(0.0, 1.0);
    _pStickSub->_weight._t_value = 0.0;

    //���f
    ID3DXAnimationController* pAc = _pAc;
    for (UINT hand = 0; hand < 2; hand++) {
        UINT tno = _apStick[hand]->_tno;
        Performance* p = _apStick[hand]->_pPerformance;
        if (p) {
            hr = pAc->SetTrackEnable(tno, TRUE);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            hr = pAc->SetTrackAnimationSet(tno, p->_pAnimationSet);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            _paAs[tno] = p->_pAnimationSet;
        } else {
            hr = pAc->SetTrackEnable(tno, FALSE);
            checkDxException(hr, D3D_OK, "���s���܂����B");
            _paAs[tno] = nullptr;
        }
    }

}

void Puppeteer::exchangPerformance() {
    Performance* p2 = _pStickSub->_pPerformance;
    _pStickSub->_pPerformance = _pStickMain->_pPerformance;
    _pStickMain->_pPerformance = p2;

    HRESULT hr;
    if (_pStickSub->_pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_pStickSub->_tno, _pStickSub->_pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackEnable(_pStickSub->_tno, TRUE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    } else {
        hr = _pAc->SetTrackEnable(_pStickSub->_tno, FALSE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }

    if (_pStickMain->_pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_pStickMain->_tno, _pStickMain->_pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackEnable(_pStickMain->_tno, TRUE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    } else {
        hr = _pAc->SetTrackEnable(_pStickMain->_tno, FALSE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
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

    HRESULT hr;
    hr = _pAc->SetTrackEnable(main_tno, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackAnimationSet(main_tno, _pStickMain->_pPerformance->_pAnimationSet); _paAs[main_tno] = _pStickMain->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackSpeed(main_tno, 1.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackPosition(main_tno, 0.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(main_tno, _pStickMain->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");

    UINT sub_tno = _pStickSub->_tno;
    _pStickSub->_weight._t_value = 0.0;
    hr = _pAc->SetTrackEnable(sub_tno, FALSE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}
void Puppeteer::switchTo(UINT prm_performance_no, frame prm_switch_frames) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() �A�j��ID���͈͊O�ł��Bprm_performance_no="<<prm_performance_no);
    }

    //Main��Sub������
    Stick* pWk = _pStickMain;
    _pStickMain = _pStickSub;
    _pStickSub = pWk;


    Performance* p = &(_paPerformances[prm_performance_no]);
    _pStickMain->_pPerformance = p;
    _pStickMain->_weight.transitionLinearToTop(prm_switch_frames);
    _pStickSub->_weight.transitionLinearToBottom(prm_switch_frames);


    UINT main_tno = _pStickMain->_tno;
    HRESULT hr;
    hr = _pAc->SetTrackEnable(main_tno, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackAnimationSet(main_tno, _pStickMain->_pPerformance->_pAnimationSet); _paAs[main_tno] = _pStickMain->_pPerformance->_pAnimationSet;
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackSpeed(main_tno, 1.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackPosition(main_tno, 0.0);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(main_tno, _pStickMain->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");

    UINT sub_tno = _pStickSub->_tno;
    hr = _pAc->SetTrackEnable(sub_tno, TRUE);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackAnimationSet(sub_tno, _pStickSub->_pPerformance->_pAnimationSet); _paAs[sub_tno] = _pStickSub->_pPerformance->_pAnimationSet;
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackSpeed(sub_tno, 1.0);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackPosition(sub_tno, 0.0);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackWeight(sub_tno, 1.0 - _pStickSub->_weight._t_value);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}

//// �w��̃A�j���[�V����ID�̑��݂��`�F�b�N
//  if( m_Anim.size() <= animID )
//     return false;
//
//  // �قȂ�A�j���[�V�����ł��邩���`�F�b�N
//  if( m_CurAnimID == animID )
//     return false;
//
//  // ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
//  D3DXTRACK_DESC TD;   // �g���b�N�̔\��
//  m_AnimCont->GetTrackDesc( 0, &TD );
//
//  // ���̃A�j���[�V�������g���b�N1�Ɉڍs��
//  // �g���b�N�̐ݒ�l���ڍs
//  m_AnimCont->SetAnimationSet( 1, m_Anim[m_CurAnimID].pAnimSet );
//  m_AnimCont->SetTrackDesc( 1, &TD );
//
//  // �V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
//  m_AnimCont->SetAnimationSet( 0, m_Anim[animID].pAnimSet );
//
//  // �g���b�N0�̃X�s�[�h�̐ݒ�
//  m_AnimCont->SetTrackSpeed( 0, m_Anim[animID].fTrackSpeed );
//
//  // �g���b�N�̍���������
//  m_AnimCont->SetTrackenable( 0, true );
//  m_AnimCont->SetTrackenable( 1, true );
//
//  // �E�F�C�g���Ԃ�������
//  m_Anim[animID].fCurWeightTime = 0.0f;
//
//  // ���݂̃A�j���[�V�����ԍ���؂�ւ�
//  m_PreAnimID = m_CurAnimID;
//  m_CurAnimID = animID;
//
//  return true;

//    HRESULT hr;
//    UINT tno = _pStickMain->_tno; //�g���b�N�ԍ�
//    hr = pAc->SetTrackEnable(tno, _pStickMain->_enable_motion_blend);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = pAc->SetTrackAnimationSet(tno, p->_pAnimationSet);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = pAc->SetTrackPosition(tno, p->_local_time._t_value);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = pAc->SetTrackSpeed(tno, p->_period);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = pAc->SetTrackWeight(tno, p->_weight._t_value);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
void Puppeteer::behave() {

    HRESULT hr;
    UINT main_tno = _pStickMain->_tno;
    if (_pStickMain->_weight.isTransitioning()) {
        _pStickMain->_weight.behave();
        hr = _pAc->SetTrackWeight(main_tno, _pStickMain->_weight._t_value);
        checkDxException(hr, D3D_OK, "���s���܂����B");

        _TRACE_("_pStickMain tno="<<main_tno<<" _weight="<<_pStickMain->_weight._t_value);
    }
    UINT sub_tno = _pStickSub->_tno;
    if (_pStickSub->_weight.isTransitioning()) {
        _pStickSub->_weight.behave();
        hr = _pAc->SetTrackWeight(sub_tno, _pStickSub->_weight._t_value);
        checkDxException(hr, D3D_OK, "���s���܂����B");

        _TRACE_("_pStickSub  tno="<<sub_tno<<" _weight="<<_pStickSub->_weight._t_value);
    } else {
        hr = _pAc->SetTrackEnable(sub_tno, FALSE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }
    _advance_time += _ani_time_delta;
}

void Puppeteer::stop() {
//    for (UINT hand = 0; hand < 2; hand++) {
//        Performance* p = _apStick[hand]->_pPerformance;
//        if (p) {
//            p->_method = NO_CHENGE;
//        }
//    }
}

void Puppeteer::updateAnimationTrack() {
    HRESULT hr;
    hr = _pAc->AdvanceTime(_advance_time, nullptr);
    checkDxException(hr, D3D_OK, "���s���܂����B");
    _advance_time = 0;

//    _TRACE_("updateAnimationTrack");
//    double g_time = _pAc->GetTime();
//    _TRACE_("g_time="<<g_time<< "  _ani_time_delta="<<_ani_time_delta);

}


Puppeteer::~Puppeteer() {
    GGAF_DELETE(_pStickMain);
    GGAF_DELETE(_pStickSub);
    GGAF_DELETEARR(_paPerformances);
}
