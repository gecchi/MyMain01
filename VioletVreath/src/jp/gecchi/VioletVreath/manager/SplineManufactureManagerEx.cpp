#include "SplineManufactureManagerEx.h"

#include "jp/ggaf/dx/util/spline/FixedFrameSplineManufacture.h"
#include "jp/ggaf/dx/util/spline/FixedVelocitySplineManufacture.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

SplineManufactureManagerEx::SplineManufactureManagerEx(const char* prm_manager_name) :
        SplineManufactureManager(prm_manager_name) {
}

SplineManufacture* SplineManufactureManagerEx::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    SplineManufacture* pSplManuf = nullptr;

    if (strcmp("EnemyEres_spline", prm_idstr) == 0) {
        pSplManuf = NEW FixedFrameSplineManufacture("Spl_HAN", 60*30);
    } else if (strcmp("Shot001_spline", prm_idstr) == 0) {
        pSplManuf = NEW FixedVelocitySplineManufacture("Spl_HAN", 10000);
    }

    if (pSplManuf == nullptr) {
        pSplManuf = SplineManufactureManager::processCreateResource(prm_idstr, prm_pConnector);
    }
    return pSplManuf;
}

