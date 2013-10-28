#include "stdafx.h"
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
}

void WallAAPrismTestActor::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.5, 0.2, 3.0);
    _pModel->_pTexBlinker->setPower(0.5);
    _pModel->_pTexBlinker->beat(10*20, 10*9, 10*3, -1);
}


bool WallAAPrismTestActor::isOutOfUniverse() {
    if (GgafDxUniverse::_x_gone_left < _x) {
        return false;
    }
    return true;
}

