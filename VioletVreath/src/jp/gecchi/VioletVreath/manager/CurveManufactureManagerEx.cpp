#include "CurveManufactureManagerEx.h"

#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

CurveManufactureManagerEx::CurveManufactureManagerEx(const char* prm_manager_name) :
        CurveManufactureManager(prm_manager_name) {
}

CurveManufacture* CurveManufactureManagerEx::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    CurveManufacture* pCurveManuf = nullptr;

    if (strcmp("EnemyEres_curve", prm_idstr) == 0) {
        pCurveManuf = NEW FixedFrameCurveManufacture("Spl_HAN", 60*30);
        pCurveManuf->setMoveDriver(CurveManufacture::MoveDriver::CoordVehicle);
    } else if (strcmp("Shot001_curve", prm_idstr) == 0) {
        pCurveManuf = NEW FixedVelocityCurveManufacture("Spl_HAN", 10000);
    }

    if (pCurveManuf == nullptr) {
        pCurveManuf = CurveManufactureManager::processCreateResource(prm_idstr, prm_pConnector);
    }
    return pCurveManuf;
}

