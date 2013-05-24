#include "stdafx.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmConnection::GgafDxBgmConnection(char* prm_idstr, GgafDxBgm* prm_pGgafDxBgm) :
    GgafResourceConnection<GgafDxBgm> (prm_idstr, prm_pGgafDxBgm) {
}

void GgafDxBgmConnection::processReleaseResource(GgafDxBgm* prm_pResource) {
    _TRACE_("GgafDxBgm="<<prm_pResource->_ogg_file_name<<" ‚ðŠJ•ú‚µ‚Ü‚·B");
    GGAF_DELETE(prm_pResource);
}

