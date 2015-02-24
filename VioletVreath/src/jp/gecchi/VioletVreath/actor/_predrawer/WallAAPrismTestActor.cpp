#include "WallAAPrismTestActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


WallAAPrismTestActor::WallAAPrismTestActor(const char* prm_name) :
        WallAAPrismActor(prm_name, "_chk_WallAAPrismTestModel", nullptr) {
    _class_name = "WallAAPrismTestActor";
    setHitAble(false);
}

void WallAAPrismTestActor::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.5, 0.5);
    pModel->getTexBlinker()->forceRange(0.2, 3.0);
    pModel->getTexBlinker()->beat(10*20, 10*9, 0, 10*9, -1);
}

bool WallAAPrismTestActor::isOutOfUniverse() const {
    if (GgafDxUniverse::_x_gone_left < _x) {
        return false;
    }
    return true;
}

