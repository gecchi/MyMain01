#include "stdafx.h"
#include "ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

ViewPoint::ViewPoint(const char* prm_name) :
        GgafDxCameraViewPoint(prm_name) {
    _class_name = "ViewPoint";
    pAxsMver_ = NEW GgafDxAxesMover(this);
}

void ViewPoint::initialize() {
    GgafDxCameraViewPoint::initialize();
}

void ViewPoint::processBehavior() {
    GgafDxCameraViewPoint::processBehavior();
    pAxsMver_->behave();
    _pKuroko->behave();
}

ViewPoint::~ViewPoint() {
    GGAF_DELETE(pAxsMver_);
}
