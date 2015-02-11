#include <actor/camera/MgrCameraViewPoint.h>
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrCameraViewPoint::MgrCameraViewPoint(const char* prm_name) :
        DefaultCameraViewPoint(prm_name) {
    _class_name = "MgrCameraViewPoint";
    pAxsMver_ = NEW GgafDxAxesMover(this);
}

void MgrCameraViewPoint::initialize() {
    DefaultCameraViewPoint::initialize();
}

void MgrCameraViewPoint::processBehavior() {
    DefaultCameraViewPoint::processBehavior();
    pAxsMver_->behave();
    getKuroko()->behave();
}

void MgrCameraViewPoint::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    //ƒJƒƒ‰‚Ê‚é‚Á‚ÆˆÚ“®
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void MgrCameraViewPoint::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

MgrCameraViewPoint::~MgrCameraViewPoint() {
    GGAF_DELETE(pAxsMver_);
}
