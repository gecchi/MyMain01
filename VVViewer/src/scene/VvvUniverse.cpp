#include "stdafx.h"
#include "VvvUniverse.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "scene/VvvUniverse/VvvWorld.h"

using namespace VVViewer;

VvvUniverse::VvvUniverse(const char* prm_name, VvvCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    pWorld_ = nullptr;

    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void VvvUniverse::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    pWorld_ = createInFactory(VVViewer::VvvWorld, "SIMPLE_WORLD");
    addSubLast(pWorld_);
}

VvvUniverse::~VvvUniverse() {
}

