#include "stdafx.h"
#include "VvvViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvViewPoint::VvvViewPoint(const char* prm_name) :
        GgafDxCameraViewPoint(prm_name) {
    _class_name = "VvvViewPoint";
    pAxsMver_ = NEW GgafDxAxesMover(this);
}

void VvvViewPoint::processBehavior() {
    GgafDxCameraViewPoint::processBehavior();
    pAxsMver_->behave();
    _pKuroko->behave();
}

VvvViewPoint::~VvvViewPoint() {
    GGAF_DELETE(pAxsMver_);
}
