#include "Wall001Prism.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Wall001Prism::Wall001Prism(const char* prm_name) :
        WallAAPrismActor(prm_name, "g_box001Prism", STATUS(Wall001Prism)) {
    _class_name = "Wall001Prism";
    //drawAnyFar(true);//遠くても表示
}

void Wall001Prism::onCreateModel() {
}

void Wall001Prism::processBehavior() {
    WallAAPrismActor::processBehavior();
//    if (P_MYSHIP->isOutOfView()) {
//        setHitAble(true, true); //自機が視野外の場合、視野外壁も当たり判定有り
//    } else {
//        setHitAble(true, false);//自機が視野内の場合、視野外壁は当たり判定無し
//    }
//    _TRACE_(getName()<<":"<<_x<<","<<_y<<","<<_z);
}
//bool Wall001Prism::isOutOfSpacetime() const {
//    if (GgafDxSpacetime::_x_bound_left <= _x) {
//        return false;
//    }
//    return true;
//}

