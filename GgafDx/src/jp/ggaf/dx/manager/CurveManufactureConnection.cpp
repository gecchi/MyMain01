#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"

using namespace GgafDx;

CurveManufactureConnection::CurveManufactureConnection(const char* prm_idstr, CurveManufacture* prm_pResource) :
    GgafCore::ResourceConnection<CurveManufacture> (prm_idstr, prm_pResource) {
}

void CurveManufactureConnection::processReleaseResource(CurveManufacture* prm_pResource) {
    _TRACE_("CurveManufactureConnection::processReleaseResourceで"<<prm_pResource->_ldr_file<<"の開放(ここでぶっ壊れたらclose()漏れの可能性あり)");
    GGAF_DELETE(prm_pResource);
}

