#include "stdafx.h"
#include "Wall001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Wall001::Wall001(const char* prm_name) :
        WallAABActor(prm_name, "g_box001", STATUS(Wall001)) {
    _class_name = "Wall001";
    //drawAnyFar(true);//遠くても表示
}

void Wall001::onCreateModel() {
//    _pModel->_pTexBlinker->setBlinkableRange(0.1, 0.8, 3.0);
//    _pModel->_pTexBlinker->setPower(1.0);
//    _pModel->_pTexBlinker->beat(10*20, 10*9, 10*3, -1);
}

void Wall001::processBehavior() {
    WallAABActor::processBehavior();
//    if (P_MYSHIP->isOutOfView()) {
//        setHitAble(true, true); //自機が視野外の場合、視野外壁も当たり判定有り
//    } else {
//        setHitAble(true, false);//自機が視野内の場合、視野外壁は当たり判定無し
//    }
//    _TRACE_(getName()<<":"<<_x<<","<<_y<<","<<_z);
}
//bool Wall001::isOutOfUniverse() {
//    if (GgafDxUniverse::_x_gone_left/2 < _x) {
//        return false;
//    }
//    return true;
//}

