#include "SmpSpacetime.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "SmpSpacetime/SmpWorld.h"
#include "actor/SmpCamera.h"

using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void SmpSpacetime::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    SmpWorld* pWorld = createInFactory(SimpleSample::SmpWorld, "SIMPLE_WORLD");
    addSubLast(pWorld);
}

SmpSpacetime::~SmpSpacetime() {
}

