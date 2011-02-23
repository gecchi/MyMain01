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
    _num_animation_set = _pAc->GetMaxNumAnimationSets();
    _num_tracks = _pAc->GetMaxNumTracks();
    _TRACE_("_pAc->GetMaxNumTracks()="<<_pAc->GetMaxNumTracks());
    _TRACE_("_pAc->GetMaxNumAnimationSets()="<<_pAc->GetMaxNumAnimationSets());

//    _advance_time_per_frame = 1.0 / 60.0; //60����1�b
    _advance_time_per_draw = 0.0;


    _papAnimationSet = NEW LPD3DXANIMATIONSET[_num_animation_set];
    _pa_as_anime_time = NEW double[_num_animation_set];
    _pa_as_anime_speed = NEW float[_num_animation_set];
    _pa_as_weight = NEW float[_num_animation_set];
    for (UINT i = 0; i < _num_animation_set; i++) {
        hr = _pAc->GetAnimationSet(i, &(_papAnimationSet[i])); //�A�j���[�V�����Z�b�g�ێ�
        checkDxException(hr, D3D_OK, "���s���܂����B");
        _pa_as_anime_time[i] = 0.0;
        _pa_as_anime_speed[i] = 1.0;
        _pa_as_weight[i] = 1.0;
    }

    hr = _pAc->ResetTime();//�O���[�o�����Ԃ�0�ɂ���
    checkDxException(hr, D3D_OK, "���s���܂����B");
    //�����͐Î~
    for (UINT i = 0; i < _num_tracks; i++) {
        hr = _pAc->SetTrackEnable(i, TRUE);
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

    for (DWORD i = 0; i < (DWORD)_pAc->GetMaxNumTracks(); i++) {
        hr = _pAc->SetTrackEnable(i, FALSE);
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }

    _hand = 0;

}
void GgafDx9Puppeteer::play(UINT anim_set_id) {
    HRESULT hr = _pAc->SetTrackAnimationSet(_hand, _papAnimationSet[anim_set_id]);//anim_set_id�Ԃ̃A�j���[�V�����Z�b�g���g���b�N0�ԂɃZ�b�g
    checkDxException(hr, D3D_OK, "���s���܂����B");
    hr = _pAc->SetTrackEnable(_hand, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}
void GgafDx9Puppeteer::play() {
    HRESULT hr = _pAc->SetTrackEnable(_hand, TRUE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}
void GgafDx9Puppeteer::stop() {
    HRESULT hr = _pAc->SetTrackEnable(_hand, FALSE);
    checkDxException(hr, D3D_OK, "���s���܂����B");
}

void GgafDx9Puppeteer::behave() {
    _advance_time_per_draw += (1.0/60.0);
}
void GgafDx9Puppeteer::work() {
    //�A�j���[�V������i�߂�B
    HRESULT hr = _pAc->AdvanceTime(_advance_time_per_draw, NULL );
    checkDxException(hr, D3D_OK, "���s���܂����B");
    _advance_time_per_draw = 0; //���Z�b�g
    //���f���̃��[���h�ϊ��s��X�V
    _pModel->_stackWorldMat.SetWorldMatrix(&(_pPuppet->_matWorld));
    _pModel->_stackWorldMat.UpdateFrame(_pModel->_pFR);
}

GgafDx9Puppeteer::~GgafDx9Puppeteer() {
}





