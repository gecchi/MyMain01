#include "WallAABTestActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


WallAABTestActor::WallAABTestActor(const char* prm_name) :
        WallAABActor(prm_name, "_chk_WallAABTestModel", nullptr) {
    _class_name = "WallAABTestActor";
    setHitAble(false);
}

void WallAABTestActor::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.5, 0.5);
    pModel->getTexBlinker()->forceRange(0.2, 3.0);
    pModel->getTexBlinker()->beat(10*20, 10*9, 0, 10*9, -1);
}

bool WallAABTestActor::isOutOfUniverse() const {
    Universe* pUniverse =  P_GOD->getUniverse();
    if (pUniverse->_x_gone_left < _x) {
        return false;
    }
    return true;
}

