#include "jp/ggaf/dx/util/curve/SteppedCoordCurveManufacture.h"

#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/SteppedCoordCurveLocusVehicleLeader.h"

using namespace GgafDx;

SteppedCoordCurveManufacture::SteppedCoordCurveManufacture(const char* prm_coord_spl_file) :
        CurveManufacture(prm_coord_spl_file) {
    _move_method = SteppedCoord;
}

SteppedCoordCurveManufacture::SteppedCoordCurveManufacture(CurveSource* prm_pCurve) :
        CurveManufacture(prm_pCurve) {
    _move_method = SteppedCoord;
}

void SteppedCoordCurveManufacture::calculate() {
    CurveManufacture::calculate();
}

VehicleLeader* SteppedCoordCurveManufacture::createLocusVehicleLeader(GgafDx::LocusVehicle* prm_pLocusVehicle) {
    return NEW SteppedCoordCurveLocusVehicleLeader(this, prm_pLocusVehicle);
}

SteppedCoordCurveManufacture::~SteppedCoordCurveManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
}
