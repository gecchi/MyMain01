#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


WallAABTestActor::WallAABTestActor(const char* prm_name) :
        WallAABActor(prm_name, "_chk_WallAABTestModel", nullptr) {
    _class_name = "WallAABTestActor";
}

void WallAABTestActor::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.5, 0.2, 3.0);
    _pModel->_pTextureBlinker->setBlink(0.5);
    _pModel->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
}


bool WallAABTestActor::isOutOfUniverse() {
    if (GgafDxUniverse::_X_goneLeft < _X) {
        return false;
    }
    return true;
}

