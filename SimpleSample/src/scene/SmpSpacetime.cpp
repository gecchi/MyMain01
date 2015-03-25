#include "SmpSpacetime.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "SmpSpacetime/SmpWorld.h"
#include "actor/SmpCamera.h"

using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //SmpWorld�V�[���̍쐬�𒍕�����
    orderSceneToFactory(0, SimpleSample::SmpWorld, "SIMPLE_WORLD");
    //���̐�(Spacetime)�R���X�g���N�^���ŁA
    //���̃V�[���̏���( addSubLast(GgafScene*) )�͎��s���Ȃ��ł��������B
}

void SmpSpacetime::initialize() {
    //���E�V�[��(SmpWorld)��z���ɏ���������
    addSubLast(obtainSceneFromFactory(0));
}

SmpSpacetime::~SmpSpacetime() {
}

