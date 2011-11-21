#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MagicPointItem002::MagicPointItem002(const char* prm_name)
               : MagicPointItem(prm_name, "MagicPointItem002", STATUS(MagicPointItem002)) {
    _class_name = "MagicPointItem002";
}

void MagicPointItem002::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 300000);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "decide1");
}

MagicPointItem002::~MagicPointItem002() {
}
