#include "Wall01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Wall01::Wall01(const char* prm_name) :
        CubeMapMassWallActor(prm_name, "g_box001", STATUS(Wall01)) {
//Wall01::Wall01(const char* prm_name) :
//        MassWallActor(prm_name, "g_box001", STATUS(Wall01)) {
    _class_name = "Wall01";
    setCubeMap("uffizi_cross_cubemap.dds", 0.4);
    getModel()->setSpecular(5.0, 1.0);
}

void Wall01::onCreateModel() {
}
void Wall01::onActive() {
    MassWallActor::onActive();
    setAlpha(0);
    getAlphaFader()->transitionLinearToTop(60);
}
void Wall01::processBehavior() {
    MassWallActor::processBehavior();
    getAlphaFader()->behave();
//    if (pMYSHIP->isOutOfView()) {
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

