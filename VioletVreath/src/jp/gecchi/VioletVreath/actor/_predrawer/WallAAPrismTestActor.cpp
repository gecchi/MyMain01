#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


WallAAPrismTestActor::WallAAPrismTestActor(const char* prm_name) :
        WallAAPrismActor(prm_name, "_chk_WallAAPrismTestModel", NULL) {
    _class_name = "WallAAPrismTestActor";
}

void WallAAPrismTestActor::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.5, 0.2, 3.0);
    _pModel->_pTextureBlinker->setBlink(0.5);
    _pModel->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
}


bool WallAAPrismTestActor::isOutOfUniverse() {
    if (GgafDxUniverse::_X_goneLeft < _X) {
        return false;
    }
    return true;
}

