#include "stdafx.h"
#include "WallAABTestActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


WallAABTestActor::WallAABTestActor(const char* prm_name) :
        WallAABActor(prm_name, "_chk_WallAABTestModel", nullptr) {
    _class_name = "WallAABTestActor";
}

void WallAABTestActor::onCreateModel() {
    _pModel->setBlinkPower(0.5, 0.5);
    _pModel->_pTexBlinker->forceRange(0.2, 3.0);
    _pModel->_pTexBlinker->beat(10*20, 10*9, 0, 10*9, -1);
}

bool WallAABTestActor::isOutOfUniverse() {
    if (GgafDxUniverse::_x_gone_left < _x) {
        return false;
    }
    return true;
}

