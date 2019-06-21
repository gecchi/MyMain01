#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineRikishaLeader.h"



using namespace GgafLib;

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(const char* prm_coord_data_file) :
        SplineManufacture(prm_coord_data_file) {
}

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(SplineSource* prm_pSpl) :
        SplineManufacture(prm_pSpl) {
}

void SteppedCoordSplineManufacture::calculate() {
    SplineManufacture::calculate();
}

SplineLeader* SteppedCoordSplineManufacture::createRikishaLeader(GgafDx::Rikisha* prm_pRikisha) {
    return NEW SteppedCoordSplineRikishaLeader(this, prm_pRikisha);
}

SteppedCoordSplineManufacture::~SteppedCoordSplineManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
}
