#include "stdafx.h"
#include "VvvViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAsstA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvViewPoint::VvvViewPoint(const char* prm_name) :
        GgafDxCameraViewPoint(prm_name) {
    _class_name = "VvvViewPoint";
    pAxMver_ = NEW GgafDxAxesMover(this);
    pKurokoAsstA_ = NEW GgafDxKurokoAsstA(_pKuroko);
}

void VvvViewPoint::processBehavior() {
    GgafDxCameraViewPoint::processBehavior();
    pAxMver_->behave();
    pKurokoAsstA_->behave();
    _pKuroko->behave();
}

VvvViewPoint::~VvvViewPoint() {
    GGAF_DELETE(pKurokoAsstA_);
    GGAF_DELETE(pAxMver_);
}
