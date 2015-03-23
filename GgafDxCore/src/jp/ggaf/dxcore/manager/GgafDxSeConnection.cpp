#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeConnection::GgafDxSeConnection(const char* prm_idstr, GgafDxSe* prm_pGgafDxSe) :
    GgafResourceConnection<GgafDxSe> (prm_idstr, prm_pGgafDxSe) {
}

void GgafDxSeConnection::processReleaseResource(GgafDxSe* prm_pResource) {
    _TRACE_("GgafDxSe="<<prm_pResource->_wave_file_name<<" ‚ðŠJ•ú‚µ‚Ü‚·B");
    GGAF_DELETE(prm_pResource);
}

