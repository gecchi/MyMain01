#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(const char* prm_source_file) :
        SplineManufacture(prm_source_file) {
}

SteppedCoordSplineManufacture::SteppedCoordSplineManufacture(SplineSource* prm_pSpl) :
        SplineManufacture(prm_pSpl) {
}

void SteppedCoordSplineManufacture::calculate() {
    SplineManufacture::calculate();
}

SplineLeader* SteppedCoordSplineManufacture::createKurokoLeader(GgafDxCore::GgafDxKuroko* prm_pKuroko) {
    return NEW SteppedCoordSplineKurokoLeader(this, prm_pKuroko);
}

SteppedCoordSplineManufacture::~SteppedCoordSplineManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
}
