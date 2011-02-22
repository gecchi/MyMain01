#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "anibox") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    setScale(4000);

}

void TamagoActor::processBehavior() {
//    _TRACE_("GgafDx9Input::isBeingPressedKey(DIK_E)="<<(GgafDx9Input::isBeingPressedKey(DIK_E)));
    if (GgafDx9Input::isPushedDownKey(DIK_E)) {
        _TRACE_("GgafDx9Input::isPushedDownKey(DIK_E)!!!!!!");
        HRESULT hr;
//        LPD3DXANIMATIONSET pAnimationSet;
//        HRESULT hr = _pAc->GetAnimationSet(1, &pAnimationSet); //ID1�Ԃ̃A�j���[�V�����Z�b�g�擾
//        checkDxException(hr, D3D_OK, "���s���܂����B");
//        hr = _pAc->SetTrackAnimationSet(0, pAnimationSet);//ID1�Ԃ̃A�j���[�V�����Z�b�g���g���b�N0�ԂɃZ�b�g
//        checkDxException(hr, D3D_OK, "���s���܂����B");
        hr = _pAc->SetTrackEnable(0, TRUE);//�g���b�N�L��
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }

    if (GgafDx9Input::isPushedDownKey(DIK_R)) {
        _TRACE_("GgafDx9Input::isPushedDownKey(DIK_R)!!!!!!");
        HRESULT hr = _pAc->SetTrackEnable(0, FALSE);//�g���b�N����
        checkDxException(hr, D3D_OK, "���s���܂����B");
    }





    _advance_time_per_draw += _advance_time_per_frame;
}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("TamagoActor�q�b�g���܂����B("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
