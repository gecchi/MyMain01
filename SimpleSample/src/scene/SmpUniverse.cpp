#include "stdafx.h"
using namespace SimpleSample;

SmpUniverse::SmpUniverse(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void SmpUniverse::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    addSubLast(new SmpWorld("SIMPLE_WORLD"));
}

SmpUniverse::~SmpUniverse() {
}
