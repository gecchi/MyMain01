#include "stdafx.h"
using namespace SimpleSample;

SmpUniverse::SmpUniverse(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void SmpUniverse::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    SmpWorld* pWorld = createInFactory(SmpWorld, "SIMPLE_WORLD");
    addSubLast(pWorld);
}

SmpUniverse::~SmpUniverse() {
}

