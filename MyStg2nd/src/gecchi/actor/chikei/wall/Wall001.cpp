#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


Wall001::Wall001(const char* prm_name) :
        WallAABActor(prm_name, "g_box001", STATUS(Wall001)) {
    _class_name = "Wall001";
}

void Wall001::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.1, 0.8, 3.0);
    _pModel->_pTextureBlinker->setBlink(1.0);
    _pModel->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
}


bool Wall001::isOutOfUniverse() {
    if (GgafDxUniverse::_X_goneLeft/2 < _X) {
        return false;
    }
    return true;
}

