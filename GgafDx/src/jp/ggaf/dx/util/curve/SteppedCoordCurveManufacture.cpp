#include "jp/ggaf/dx/util/curve/SteppedCoordCurveManufacture.h"

#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/SteppedCoordCurveLocoVehicleLeader.h"

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

VehicleLeader* SteppedCoordCurveManufacture::createLocoVehicleLeader(GgafDx::LocoVehicle* prm_pLocoVehicle) {
    return NEW SteppedCoordCurveLocoVehicleLeader(this, prm_pLocoVehicle);
}

SteppedCoordCurveManufacture::~SteppedCoordCurveManufacture() {
    GGAF_DELETEARR_NULLABLE(_paDistance_to);
}
