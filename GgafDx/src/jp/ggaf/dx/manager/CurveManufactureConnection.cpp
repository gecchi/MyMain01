#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"

using namespace GgafDx;

CurveManufactureConnection::CurveManufactureConnection(const char* prm_idstr, CurveManufacture* prm_pResource) :
    GgafCore::ResourceConnection<CurveManufacture> (prm_idstr, prm_pResource) {
}

void CurveManufactureConnection::processReleaseResource(CurveManufacture* prm_pResource) {
    _TRACE_("CurveManufactureConnection::processReleaseResource‚Å"<<prm_pResource->_ldr_file<<"‚ÌŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    GGAF_DELETE(prm_pResource);
}

