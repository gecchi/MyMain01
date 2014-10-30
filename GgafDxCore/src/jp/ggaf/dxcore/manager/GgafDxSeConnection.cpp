#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeConnection::GgafDxSeConnection(char* prm_idstr, GgafDxSe* prm_pGgafDxSe) :
    GgafResourceConnection<GgafDxSe> (prm_idstr, prm_pGgafDxSe) {
}

void GgafDxSeConnection::processReleaseResource(GgafDxSe* prm_pResource) {
    _DTRACE_("GgafDxSe="<<prm_pResource->_wave_file_name<<" を開放します。");
    GGAF_DELETE(prm_pResource);
}

