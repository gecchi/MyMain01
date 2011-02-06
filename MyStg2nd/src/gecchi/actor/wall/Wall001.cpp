#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Wall001::Wall001(const char* prm_name) :
        WallAABActor(prm_name, "g_box001") {
    _class_name = "Wall001";
    MyStgUtil::resetWall001Status(_pStatus);//Ží•ÊFKIND_CHIKEI
}

void Wall001::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.2, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.5;
}


bool Wall001::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft/2 < _X) {
        return false;
    }
    return true;
}

