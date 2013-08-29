#include "stdafx.h"
#include "actor/TestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace Mogera;

TestActor::TestActor(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Ichimatsu") {
}

void TestActor::initialize() {
    //���W�ݒ�
    position(0, 0, 0); //(0,0,0) �͉�ʂ̒��S
}

void TestActor::processBehavior() {
    _pKurokoA->behave(); //����A������������iZ����]����j
}

TestActor::~TestActor() {
}
