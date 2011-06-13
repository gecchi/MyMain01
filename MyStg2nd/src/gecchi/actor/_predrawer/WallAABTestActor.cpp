#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


WallAABTestActor::WallAABTestActor(const char* prm_name) :
        WallAABActor(prm_name, "_chk_WallAABTestActorTest") {
    _class_name = "WallAABTestActor";
}

void WallAABTestActor::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.5, 0.2, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
}


bool WallAABTestActor::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        return false;
    }
    return true;
}
