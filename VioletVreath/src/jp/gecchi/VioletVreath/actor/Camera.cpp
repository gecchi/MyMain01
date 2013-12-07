#include "stdafx.h"
#include "Camera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAsstA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "Camera";
    pAxMver_ = NEW GgafDxAxesMover(this);
    pKurokoAsstA_ = NEW GgafDxKurokoAsstA(_pKuroko);
}

GgafDxCameraViewPoint* Camera::createViewPoint() {
    ViewPoint* pVP = NEW ViewPoint("ViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

void Camera::initialize() {
    DefaultCamera::initialize();
}

void Camera::processBehavior() {
    DefaultCamera::processBehavior();
    pAxMver_->behave();
    pKurokoAsstA_->behave();
    _pKuroko->behave();
}

Camera::~Camera() {
    GGAF_DELETE(pAxMver_);
    GGAF_DELETE(pKurokoAsstA_);
}
