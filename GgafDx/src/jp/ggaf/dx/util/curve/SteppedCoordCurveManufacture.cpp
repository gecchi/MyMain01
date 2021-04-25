#include "jp/ggaf/dx/util/curve/SteppedCoordCurveManufacture.h"

#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/SteppedCoordCurveVecDriverLeader.h"

using namespace GgafDx;

SteppedCoordCurveManufacture::SteppedCoordCurveManufacture(const char* prm_coord_spl_file) :
        CurveManufacture(prm_coord_spl_file) {
}

SteppedCoordCurveManufacture::SteppedCoordCurveManufacture(CurveSource* prm_pCurve) :
        CurveManufacture(prm_pCurve) {
}

void SteppedCoordCurveManufacture::calculate() {
    CurveManufacture::calculate();
}

DriverLeader* SteppedCoordCurveManufacture::createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) {
    return NEW SteppedCoordCurveVecDriverLeader(this, prm_pVecDriver);
}

SteppedCoordCurveManufacture::~SteppedCoordCurveManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
}
