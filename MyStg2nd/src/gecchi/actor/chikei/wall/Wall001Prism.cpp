#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Wall001Prism::Wall001Prism(const char* prm_name) :
        WallAAPrismActor(prm_name, "g_box001Prism") {
    _class_name = "Wall001Prism";
    MyStgUtil::resetWall001Status(_pStatus);//Ží•ÊFKIND_CHIKEI
}

void Wall001Prism::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.5, 0.2, 3.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
    _pGgafDx9Model->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
}


bool Wall001Prism::isOutOfUniverse() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        return false;
    }
    return true;
}

