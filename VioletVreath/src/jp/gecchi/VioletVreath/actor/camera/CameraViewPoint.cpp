#include "CameraViewPoint.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerGizmo.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraViewPoint::CameraViewPoint(const char* prm_name) :
        DefaultCameraViewPoint(prm_name) {
    _class_name = "CameraViewPoint";
    pAxsMver_ = NEW GgafDxAxesMover(this);
}

void CameraViewPoint::initialize() {
    DefaultCameraViewPoint::initialize();
}

void CameraViewPoint::processBehavior() {
    DefaultCameraViewPoint::processBehavior();
    pAxsMver_->behave();
    getKuroko()->behave();
}

void CameraViewPoint::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    //ƒJƒƒ‰‚Ê‚é‚Á‚ÆˆÚ“®
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void CameraViewPoint::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

CameraViewPoint::~CameraViewPoint() {
    GGAF_DELETE(pAxsMver_);
}
