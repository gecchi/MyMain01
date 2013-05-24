#include "stdafx.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineManufactureConnection::SplineManufactureConnection(char* prm_idstr, SplineManufacture* prm_pResource) :
    GgafResourceConnection<SplineManufacture> (prm_idstr, prm_pResource) {
}

void SplineManufactureConnection::processReleaseResource(SplineManufacture* prm_pResource) {
    _TRACE_("SplineManufactureConnection::processReleaseResourceで"<<prm_pResource->_source_file<<"の開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    GGAF_DELETE(prm_pResource);
}

