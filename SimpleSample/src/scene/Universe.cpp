#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

Universe::Universe(const char* prm_name, Camera* prm_pCam) :
        DefaultUniverse(prm_name, prm_pCam) {
    //�u���̐��v�R���X�g���N�^���ŁA�V�[���� new �͍s��Ȃ��ŉ������B
}

void Universe::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    addSubLast(new World("SIMPLE_WORLD"));
}

Universe::~Universe() {
}
