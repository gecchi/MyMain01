#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "AnimatedSkelton") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    setScale(100);
    HRESULT hr;
    _TRACE_("_pAc->GetMaxNumTracks()="<<_pAc->GetMaxNumTracks());

    LPD3DXANIMATIONSET pAnimationSet0;
    hr = _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0�Ԃ̃A�j���[�V�����Z�b�g�擾
    checkDxException(hr, D3D_OK, "���s���܂����B");
//    LPD3DXANIMATIONSET pAnimationSet1;
//    hr = _pAc->GetAnimationSet(1, &pAnimationSet1); //ID1�Ԃ̃A�j���[�V�����Z�b�g�擾
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    LPD3DXANIMATIONSET pAnimationSet2;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet2); //ID2�Ԃ̃A�j���[�V�����Z�b�g�擾
//    checkDxException(hr, D3D_OK, "���s���܂����B");

    hr = _pAc->SetTrackAnimationSet(0, pAnimationSet0);//ID0�Ԃ̃A�j���[�V�����Z�b�g���g���b�N0�ԂɃZ�b�g�i�f�t�H���g�ł����Ȃ�͂��j
    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackAnimationSet(1, pAnimationSet1);//ID1�Ԃ̃A�j���[�V�����Z�b�g���g���b�N1�ԂɃZ�b�g�i�f�t�H���g�ł����Ȃ�͂��j
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackAnimationSet(2, pAnimationSet2);//ID2�Ԃ̃A�j���[�V�����Z�b�g���g���b�N2�ԂɃZ�b�g�i�f�t�H���g�ł����Ȃ�͂��j
//    checkDxException(hr, D3D_OK, "���s���܂����B");

    hr = _pAc->ResetTime();//�O���[�o�����Ԃ�0�ɂ���
    checkDxException(hr, D3D_OK, "���s���܂����B");

//    hr = _pAc->SetTrackPosition(0,0);//�g���b�N0(=ID0��)�̃��[�J�����Ԃ�0�ɂ���
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackPosition(1,0);//�g���b�N1(=ID1��)�̃��[�J�����Ԃ�0�ɂ���
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackPosition(2,0);//�g���b�N2(=ID2��)�̃��[�J�����Ԃ�0�ɂ���
//    checkDxException(hr, D3D_OK, "���s���܂����B");

//    hr = _pAc->SetTrackEnable(0,TRUE );//�g���b�N0(=ID0��)��L��
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackEnable(1,TRUE );//�g���b�N1(=ID1��)��L��
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackEnable(2,TRUE );//�g���b�N2(=ID2��)��L��
//    checkDxException(hr, D3D_OK, "���s���܂����B");

//    hr = _pAc->SetTrackWeight(0, 1.00);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackWeight(1, 1.00);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackWeight(2, 1.00);
//    checkDxException(hr, D3D_OK, "���s���܂����B");

//    hr = _pAc->AdvanceTime(0,NULL);//0�b�i�߂�i����𔽉f������j�B
//    checkDxException(hr, D3D_OK, "���s���܂����B");

    //ID0��(=�g���b�N0)�̃A�j���[�V�����Z�b�g�̊J�n�`�I���܂ł̎���(�b)
//    _advanceTimePerFrame =  pAnimationSet0->GetPeriod()/60.0;
//    double time_period0 = pAnimationSet0->GetPeriod();  //�EpD3DXAniMeshModel->_anim_ticks_per_second = 4800fps �̏ꍇ
                                                        //    1 ���[�v 4800 �t���[���A�j���[�V�����Ȃ�� 1.0 (�b)�𓾂�    (60/4800)
                                                        //    1 ���[�v 4800*2 �t���[���A�j���[�V�����Ȃ�� 2.0 (�b)�𓾂�
                                                        //�EpD3DXAniMeshModel->_anim_ticks_per_second = 60fps �̏ꍇ
                                                        //    1 ���[�v 60 �t���[���A�j���[�V�����Ȃ�� 1.0 (�b)�𓾂�
                                                        //    1 ���[�v 120 �t���[���A�j���[�V�����Ȃ�� 2.0 (�b)�𓾂�
//    _TRACE_("time_period0="<<time_period0);
//    double time_set0 = time_period0 / (60.0 / _pD3DXAniMeshModel->_anim_ticks_per_second); //���̃A�j���[�V�����ɂ�����b��
    //ID0��(=�g���b�N0)�� SetTrackSpeed �� 1.0 �Œ�Ȃ�� advanceTimePerFrame �� time_period0 / (time_set0 * 60.0)
//    _advanceTimePerFrame0 = time_set0 / time_set0*60.0 ; //�g���b�N0�Ԃ̃A�j���[�V������60�������Ԃ����߂�A�܂�P���[�v1�b�ɂ��邽�߂̎���
//    hr = _pAc->SetTrackSpeed(0, 1.0f);  //�g���b�N0(=ID0��)�̃X�s�[�h��ݒ�B
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackSpeed(1, 1.0f);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackSpeed(2, 1.0f);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
    _track0time = 0;
}

void TamagoActor::processBehavior() {
//    setCoordinateBy(P_MYSHIP);
    //�������Ȃ�Ƃ�����I
    _track0time += _advanceTimePerFrame;
    HRESULT hr = _pAc->SetTrackPosition(0,_track0time);//�g���b�N0(=ID0��)�̃��[�J�����Ԃ�0�ɂ���
    checkDxException(hr, D3D_OK, "���s���܂����B");

    hr = _pAc->AdvanceTime(_advanceTimePerFrame, NULL );
    checkDxException(hr, D3D_OK, "���s���܂����B");
}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("TamagoActor�q�b�g���܂����B("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
