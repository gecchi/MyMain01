#include "Wall01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Wall01::Wall01(const char* prm_name) :
        MassWallActor(prm_name, "g_box001", STATUS(Wall01)) {
    _class_name = "Wall01";
    //drawAnyFar(true);//�����Ă��\��
}

void Wall01::onCreateModel() {
}

void Wall01::processBehavior() {
    MassWallActor::processBehavior();
//    if (P_MYSHIP->isOutOfView()) {
//        setHitAble(true, true); //���@������O�̏ꍇ�A����O�ǂ������蔻��L��
//    } else {
//        setHitAble(true, false);//���@��������̏ꍇ�A����O�ǂ͓����蔻�薳��
//    }
//    _TRACE_(getName()<<":"<<_x<<","<<_y<<","<<_z);
}
//bool Wall01::isOutOfSpacetime() const {
//    if (GgafDxSpacetime::_x_bound_left/2 <= _x) {
//        return false;
//    }
//    return true;
//}

