#include "jp/ggaf/dx/manager/SplineManufactureConnection.h"

using namespace GgafDx;

SplineManufactureConnection::SplineManufactureConnection(const char* prm_idstr, SplineManufacture* prm_pResource) :
    GgafCore::ResourceConnection<SplineManufacture> (prm_idstr, prm_pResource) {
}

void SplineManufactureConnection::processReleaseResource(SplineManufacture* prm_pResource) {
    _TRACE_("SplineManufactureConnection::processReleaseResource‚Å"<<prm_pResource->_spl_file<<"‚ÌŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    GGAF_DELETE(prm_pResource);
}

