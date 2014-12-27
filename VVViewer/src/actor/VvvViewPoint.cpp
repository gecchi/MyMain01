#include "VvvViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvViewPoint::VvvViewPoint(const char* prm_name) :
        DefaultCameraViewPoint(prm_name) {
    _class_name = "VvvViewPoint";
    pAxsMver_ = NEW GgafDxAxesMover(this);
}

void VvvViewPoint::processBehavior() {
    DefaultCameraViewPoint::processBehavior();
    pAxsMver_->behave();
    getKuroko()->behave();
}

void VvvViewPoint::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    //ƒJƒƒ‰‚Ê‚é‚Á‚ÆˆÚ“®
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void VvvViewPoint::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
VvvViewPoint::~VvvViewPoint() {
    GGAF_DELETE(pAxsMver_);
}
