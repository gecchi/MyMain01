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
    //drawAnyFar(true);//�����Ă��\��
}

void Wall001Prism::onCreateModel() {
}

void Wall001Prism::processBehavior() {
    WallAAPrismActor::processBehavior();
//    if (P_MYSHIP->isOutOfView()) {
//        setHitAble(true, true); //���@������O�̏ꍇ�A����O�ǂ������蔻��L��
//    } else {
//        setHitAble(true, false);//���@��������̏ꍇ�A����O�ǂ͓����蔻�薳��
//    }
//    _TRACE_(getName()<<":"<<_x<<","<<_y<<","<<_z);
}
//bool Wall001Prism::isOutOfSpacetime() const {
//    if (GgafDxSpacetime::_x_bound_left <= _x) {
//        return false;
//    }
//    return true;
//}

