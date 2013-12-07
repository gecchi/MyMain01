#include "stdafx.h"
#include "VvvCamera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAsstA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "actor/VvvViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCamera::VvvCamera(const char* prm_name) : GgafLib::DefaultCamera(prm_name) {
    pAxMver_ = NEW GgafDxAxesMover(this);
    pKurokoAsstA_ = NEW GgafDxKurokoAsstA(_pKuroko);
}
GgafDxCameraViewPoint* VvvCamera::createViewPoint() {
    VvvViewPoint* pVP = NEW VvvViewPoint("ViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}
void VvvCamera::processBehavior() {
    DefaultCamera::processBehavior();
    pAxMver_->behave();
    pKurokoAsstA_->behave();
    _pKuroko->behave();
}

VvvCamera::~VvvCamera() {
    GGAF_DELETE(pKurokoAsstA_);
    GGAF_DELETE(pAxMver_);
}
