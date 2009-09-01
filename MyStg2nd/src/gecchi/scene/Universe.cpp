#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
    _TRACE_("Universe::Universe()");
    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void Universe::initialize() {
    _pWorld = NEW World("WORLD");
    addSubLast(_pWorld);
    _TRACE_("Universe::initialize()");
}

void Universe::processJudgement() {
}


void Universe::processBehavior() {
}

Universe::~Universe() {
}
