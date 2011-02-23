#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9D3DXAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDx9D3DXAniMeshActor::GgafDx9D3DXAniMeshActor(const char* prm_name,
                                                 const char* prm_model_id,
                                                 const char* prm_effect_id,
                                                 const char* prm_technique,
                                                 GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                prm_model_id,
                                                                "A",
                                                                prm_effect_id,
                                                                "A",
                                                                prm_technique,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDx9D3DXAniMeshActor;
    _class_name = "GgafDx9D3DXAniMeshActor";
    _pD3DXAniMeshModel = (GgafDx9D3DXAniMeshModel*)_pGgafDx9Model;
    _pD3DXAniMeshEffect = (GgafDx9D3DXAniMeshEffect*)_pGgafDx9Effect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
    _pPuppeteer = NEW GgafDx9Puppeteer(this);
//
//    LPD3DXANIMATIONSET pAnimationSet0;
//    hr = _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0�Ԃ̃A�j���[�V�����Z�b�g�擾
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    LPD3DXANIMATIONSET pAnimationSet1;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet1); //ID1�Ԃ̃A�j���[�V�����Z�b�g�擾
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    LPD3DXANIMATIONSET pAnimationSet2;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet2); //ID2�Ԃ̃A�j���[�V�����Z�b�g�擾
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    LPD3DXANIMATIONSET pAnimationSet4;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet4); //ID2�Ԃ̃A�j���[�V�����Z�b�g�擾
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//
//    hr = _pAc->SetTrackAnimationSet(0, pAnimationSet0);//ID0�Ԃ̃A�j���[�V�����Z�b�g���g���b�N0�ԂɃZ�b�g�i�f�t�H���g�ł����Ȃ�͂��j
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackAnimationSet(1, pAnimationSet0);//ID1�Ԃ̃A�j���[�V�����Z�b�g���g���b�N1�ԂɃZ�b�g�i�f�t�H���g�ł����Ȃ�͂��j
//    checkDxException(hr, D3D_OK, "���s���܂����B");
////    hr = _pAc->SetTrackAnimationSet(2, pAnimationSet2);//ID2�Ԃ̃A�j���[�V�����Z�b�g���g���b�N2�ԂɃZ�b�g�i�f�t�H���g�ł����Ȃ�͂��j
////    checkDxException(hr, D3D_OK, "���s���܂����B");
//
//    hr = _pAc->ResetTime();//�O���[�o�����Ԃ�0�ɂ���
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//
//    hr = _pAc->SetTrackPosition(0,0);//�g���b�N0(=ID0��)�̃��[�J�����Ԃ�0�ɂ���
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackPosition(1,0);//�g���b�N1(=ID1��)�̃��[�J�����Ԃ�0�ɂ���
//    checkDxException(hr, D3D_OK, "���s���܂����B");
////    hr = _pAc->SetTrackPosition(2,0);//�g���b�N2(=ID2��)�̃��[�J�����Ԃ�0�ɂ���
////    checkDxException(hr, D3D_OK, "���s���܂����B");
//
//    hr = _pAc->SetTrackEnable(0,TRUE );//�g���b�N0(=ID0��)��L��
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackEnable(1,TRUE );//�g���b�N1(=ID1��)��L��
//    checkDxException(hr, D3D_OK, "���s���܂����B");
////    hr = _pAc->SetTrackEnable(2,TRUE );//�g���b�N2(=ID2��)��L��
////    checkDxException(hr, D3D_OK, "���s���܂����B");
//
//    hr = _pAc->SetTrackWeight(0, 1.00);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackWeight(1, 1.00);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
////    hr = _pAc->SetTrackWeight(2, 1.00);
////    checkDxException(hr, D3D_OK, "���s���܂����B");
//
//    hr = _pAc->AdvanceTime(0,NULL);//0�b�i�߂�i����𔽉f������j�B
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//
//    //ID0��(=�g���b�N0)�̃A�j���[�V�����Z�b�g�̊J�n�`�I���܂ł̎���(�b)
////    _advance_time_per_frame =  pAnimationSet0->GetPeriod()/60.0;
////    double time_period0 = pAnimationSet0->GetPeriod();
////    _TRACE_("time_period0="<<time_period0);
////    double time_set0 = time_period0 / (60.0 / _pD3DXAniMeshModel->_anim_ticks_per_second); //���̃A�j���[�V�����ɂ�����b��
//    //ID0��(=�g���b�N0)�� SetTrackSpeed �� 1.0 �Œ�Ȃ�� advanceTimePerFrame �� time_period0 / (time_set0 * 60.0)
////    _advance_time_per_frame0 = time_set0 / time_set0*60.0 ; //�g���b�N0�Ԃ̃A�j���[�V������60�������Ԃ����߂�A�܂�P���[�v1�b�ɂ��邽�߂̎���
//    hr = _pAc->SetTrackSpeed(0, 1.0f);  //�g���b�N0(=ID0��)�̃X�s�[�h��ݒ�B
//    checkDxException(hr, D3D_OK, "���s���܂����B");
//    hr = _pAc->SetTrackSpeed(1, 1.0f);
//    checkDxException(hr, D3D_OK, "���s���܂����B");
////    hr = _pAc->SetTrackSpeed(2, 1.0f);
////    checkDxException(hr, D3D_OK, "���s���܂����B");










    // _pAc->GetMaxNumAnimationSets()

//    if (SUCCEEDED(pAnimController->GetAnimationSetByName(szAnimSetName, &pAnimSet))) {
//        if (SUCCEEDED(pAnimSet->QueryInterface(IID_ID3DXKeyframedAnimationSet, (LPVOID*)&pKeyFramedAnimSet))) {
//            UINT dwNumAnimations = pKeyFramedAnimSet->GetNumAnimations();
//            for (UINT i = 0; i < dwNumAnimations; i++)
//                HRESULT hr = pKeyFramedAnimSet->UnregisterAnimation(i);
//        }
//        pAnimSet->Release();
//    }



}

void GgafDx9D3DXAniMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDx9D3DXAniMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_dwNumMaterials; i++) {
//        _paD3DMaterial9[i].Ambient.a = _fAlpha;
//        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
//    }
}

void GgafDx9D3DXAniMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDx9D3DXAniMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_dwNumMaterials; i++) {
//        _paD3DMaterial9[i].Ambient.a = _fAlpha;
//        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
//    }
}

void GgafDx9D3DXAniMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pD3DXAniMeshEffect->_pID3DXEffect;
    HRESULT hr;
    //�r���[�ϊ��s��
//    hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matView, &P_CAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);

    //hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matWorld, &_matWorld );
    //checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
    //SetMatrix�̓��f���ł���������Ȃ�

    // Z�o�b�t�@��L����
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

//    HRESULT hr = _pAc->SetTrackPosition(0,_track0time);//�g���b�N0(=ID0��)�̃��[�J�����Ԃ�0�ɂ���
//    checkDxException(hr, D3D_OK, "���s���܂����B");

    _pD3DXAniMeshModel->draw(this);

    // Z�o�b�t�@�𖳌���
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

}

GgafDx9D3DXAniMeshActor::~GgafDx9D3DXAniMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pPuppeteer);
}
