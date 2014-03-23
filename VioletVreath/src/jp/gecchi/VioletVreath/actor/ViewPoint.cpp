#include "stdafx.h"
#include "ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverHelperA.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerGizmo.h"
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
    getKuroko()->behave();
}

void ViewPoint::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    //_TRACE_(" ViewPoint::slideMvTo("<<tx<<","<<ty<<","<<tz<<",t="<<t<<")  now("<<_x<<","<<_y<<","<<_z<<")");
    //ƒJƒƒ‰‚Ê‚é‚Á‚ÆˆÚ“®
    pAxsMver_->hlprA()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void ViewPoint::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

ViewPoint::~ViewPoint() {
    GGAF_DELETE(pAxsMver_);
}
