#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

Universe::Universe(const char* prm_name, Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
}

void Universe::initialize() {
    //���E�V�[���������A���V�[���̔z���ɏ���������
    addSubLast(new World("SIMPLE_WORLD"));
}

Universe::~Universe() {
}
