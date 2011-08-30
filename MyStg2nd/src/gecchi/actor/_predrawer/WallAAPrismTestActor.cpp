#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


WallAAPrismTestActor::WallAAPrismTestActor(const char* prm_name) :
        WallAAPrismActor(prm_name, "_chk_WallAAPrismEffectTest") {
    _class_name = "WallAAPrismTestActor";
    MyStgUtil::resetWall001Status(_pStatus);//Ží•ÊFKIND_CHIKEI
}

void WallAAPrismTestActor::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.5, 0.2, 3.0);
    _pModel->_pTextureBlinker->setBlink(0.5);
    _pModel->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
}


bool WallAAPrismTestActor::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        return false;
    }
    return true;
}

