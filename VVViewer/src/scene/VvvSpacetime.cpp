#include "VvvSpacetime.h"

#include "scene/VvvSpacetime/VvvWorld.h"

using namespace VVViewer;

VvvSpacetime::VvvSpacetime(const char* prm_name, VvvCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    pWorld_ = nullptr;

    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void VvvSpacetime::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    pWorld_ = desireScene(VVViewer::VvvWorld, "SIMPLE_WORLD");
    addSubLast(pWorld_);
}

VvvSpacetime::~VvvSpacetime() {
}

