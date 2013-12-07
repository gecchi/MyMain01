#include "stdafx.h"
#include "ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAsstA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

ViewPoint::ViewPoint(const char* prm_name) :
        GgafDxCameraViewPoint(prm_name) {
    _class_name = "ViewPoint";
    pAxMver_ = NEW GgafDxAxesMover(this);
    pKurokoAsstA_ = NEW GgafDxKurokoAsstA(_pKuroko);
}

void ViewPoint::initialize() {
    GgafDxCameraViewPoint::initialize();
}

void ViewPoint::processBehavior() {
    GgafDxCameraViewPoint::processBehavior();
    pAxMver_->behave();
    pKurokoAsstA_->behave();
    _pKuroko->behave();
}

ViewPoint::~ViewPoint() {
    GGAF_DELETE(pKurokoAsstA_);
    GGAF_DELETE(pAxMver_);
}
