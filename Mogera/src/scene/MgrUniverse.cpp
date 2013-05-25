#include "stdafx.h"
#include "MgrUniverse.h"

#include "scene/MgrUniverse/MgrWorld.h"

using namespace Mogera;

MgrUniverse::MgrUniverse(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void MgrUniverse::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    MgrWorld* pWorld = createInFactory(Mogera::MgrWorld, "MOGERA_WORLD");
    addSubLast(pWorld);
}

MgrUniverse::~MgrUniverse() {
}

