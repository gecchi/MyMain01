#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MagicPointItem002::MagicPointItem002(const char* prm_name)
               : MagicPointItem(prm_name, "MagicPointItem002", STATUS(MagicPointItem002)) {
    _class_name = "MagicPointItem002";
}

void MagicPointItem002::initialize() {
}
void MagicPointItem002::onActive() {
    MagicPointItem::onActive();
    _SX = _SY = _SZ = 5000; //BIG!
}

MagicPointItem002::~MagicPointItem002() {
}
