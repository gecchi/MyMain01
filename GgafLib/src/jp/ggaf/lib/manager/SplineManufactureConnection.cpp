#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"



using namespace GgafLib;

SplineManufactureConnection::SplineManufactureConnection(const char* prm_idstr, SplineManufacture* prm_pResource) :
    GgafCore::ResourceConnection<SplineManufacture> (prm_idstr, prm_pResource) {
}

void SplineManufactureConnection::processReleaseResource(SplineManufacture* prm_pResource) {
    _TRACE_("SplineManufactureConnection::processReleaseResourceで"<<prm_pResource->_spl_file<<"の開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    GGAF_DELETE(prm_pResource);
}

