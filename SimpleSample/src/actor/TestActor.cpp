#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

TestActor::TestActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x ���Q�Ƃ����B
}

void TestActor::initialize() {
    //���W�ݒ�
    _X = _Y = _Z = 0; //(0,0,0) �͉�ʂ̒��S
    //���qA�ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
    _pKurokoA->setFaceAngVelo(AXIS_Z, DEG2ANG(2));
}

void TestActor::processBehavior() {
    _pKurokoA->behave(); //���qA������������iZ����]����j
}

TestActor::~TestActor() {
}
