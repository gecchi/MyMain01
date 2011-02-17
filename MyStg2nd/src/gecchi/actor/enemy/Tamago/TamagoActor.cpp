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
    _SX = _SY = _SZ = 200;
    LPD3DXANIMATIONSET pAnimationSet0;
    _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0�Ԃ̃A�j���[�V�����Z�b�g
    _pAc->SetTrackAnimationSet(0, pAnimationSet0);//ID0�Ԃ̃A�j���[�V�����Z�b�g���g���b�N0�ԂɃZ�b�g�i�f�t�H���g�ł����Ȃ�͂��j
    _pAc->ResetTime();//�O���[�o�����Ԃ�0�ɂ���
    _pAc->SetTrackPosition(0,0);//�g���b�N0(=ID0��)�̃��[�J�����Ԃ�0�ɂ���
    _pAc->AdvanceTime(0,NULL);//����𔽉f������B
    double time_set0 =  pAnimationSet0->GetPeriod(); //ID0��(=�g���b�N0)�̃A�j���[�V�����Z�b�g�̊J�n�`�I���܂ł̎���
    _advanceTimePerFrame0 = time_set0 / 60.0 ; //�g���b�N0�Ԃ̃A�j���[�V������60�������Ԃ����߂�A�܂�P���[�v1�t���[���ɂ��邽�߂̎���
    _pAc->SetTrackSpeed(0, 0.5f);  //�g���b�N0(=ID0��)�̃X�s�[�h��ݒ�B
                                  //1.0��1���[�v60�t���[��
                                  //0.5��1���[�v60*2�t���[��
                                  //0.1��1���[�v60*10�t���[���ɂȂ�͂�
}

void TamagoActor::processBehavior() {

}

void TamagoActor::processJudgement() {
}

void TamagoActor::onHit(GgafActor* prm_pOtherActor) {
    _TRACE_("TamagoActor�q�b�g���܂����B("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
