#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultCameraViewPoint::DefaultCameraViewPoint(const char* prm_name) : GgafDxCameraViewPoint(prm_name) {
    _class_name = "DefaultCameraViewPoint";
}

void DefaultCameraViewPoint::initialize() {
}

void DefaultCameraViewPoint::processBehavior() {
    getAxesMover()->behave();
    getKuroko()->behave();
}

void DefaultCameraViewPoint::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    //ƒJƒƒ‰‚Ê‚é‚Á‚ÆˆÚ“®
    getAxesMover()->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}

void DefaultCameraViewPoint::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

DefaultCameraViewPoint::~DefaultCameraViewPoint() {
}
