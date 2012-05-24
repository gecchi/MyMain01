#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Wall001Prism::Wall001Prism(const char* prm_name) :
        WallAAPrismActor(prm_name, "g_box001Prism", STATUS(Wall001Prism)) {
    _class_name = "Wall001Prism";
}

void Wall001Prism::onCreateModel() {
//    _pModel->_pTextureBlinker->forceBlinkRange(0.1, 0.8, 3.0);
//    _pModel->_pTextureBlinker->setBlink(1.0);
//    _pModel->_pTextureBlinker->beat(10*20, 10*9, 10*3, -1);
}

void Wall001Prism::processBehavior() {
    WallAAPrismActor::processBehavior();
    if (P_MYSHIP->isOutOfView()) {
        setHitAble(true, true); //自機が視野外の場合、視野外壁も当たり判定有り
    } else {
        setHitAble(true, false);//自機が視野内の場合、視野外壁は当たり判定無し
    }
//    _TRACE_(getName()<<":"<<_X<<","<<_Y<<","<<_Z);
}
//bool Wall001Prism::isOutOfUniverse() {
//    if (GgafDxUniverse::_X_goneLeft < _X) {
//        return false;
//    }
//    return true;
//}

