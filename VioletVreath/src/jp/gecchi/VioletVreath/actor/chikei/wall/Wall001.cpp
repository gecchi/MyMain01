#include "Wall001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Wall001::Wall001(const char* prm_name) :
        WallAABActor(prm_name, "g_box001", STATUS(Wall001)) {
    _class_name = "Wall001";
    //drawAnyFar(true);//�����Ă��\��
}

void Wall001::onCreateModel() {
}

void Wall001::processBehavior() {
    WallAABActor::processBehavior();
//    if (P_MYSHIP->isOutOfView()) {
//        setHitAble(true, true); //���@������O�̏ꍇ�A����O�ǂ������蔻��L��
//    } else {
//        setHitAble(true, false);//���@��������̏ꍇ�A����O�ǂ͓����蔻�薳��
//    }
//    _TRACE_(getName()<<":"<<_x<<","<<_y<<","<<_z);
}
//bool Wall001::isOutOfSpacetime() const {
//    if (GgafDxSpacetime::_x_gone_left/2 < _x) {
//        return false;
//    }
//    return true;
//}

