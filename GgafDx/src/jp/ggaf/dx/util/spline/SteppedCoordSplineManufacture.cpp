#include "jp/ggaf/dx/util/spline/SteppedCoordSplineManufacture.h"

#include "jp/ggaf/dx/util/spline/SplineSource.h"
#include "jp/ggaf/dx/util/spline/SteppedCoordSplineVecDriverLeader.h"

using namespace GgafDx;

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(const char* prm_coord_data_file) :
        SplineManufacture(prm_coord_data_file) {
}

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(SplineSource* prm_pSpl) :
        SplineManufacture(prm_pSpl) {
}

void SteppedCoordSplineManufacture::calculate() {
    SplineManufacture::calculate();
}

SplineLeader* SteppedCoordSplineManufacture::createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) {
    return NEW SteppedCoordSplineVecDriverLeader(this, prm_pVecDriver);
}

SteppedCoordSplineManufacture::~SteppedCoordSplineManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
}
