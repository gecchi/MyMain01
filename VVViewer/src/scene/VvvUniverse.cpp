#include "stdafx.h"
using namespace VVViewer;

VvvUniverse::VvvUniverse(const char* prm_name, VvvCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void VvvUniverse::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    pWorld_ = createInFactory(VvvWorld, "SIMPLE_WORLD");
    addSubLast(pWorld_);
}

VvvUniverse::~VvvUniverse() {
}

