#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeConnection::GgafDxSeConnection(char* prm_idstr, GgafDxSe* prm_pGgafDxSe) :
    GgafResourceConnection<GgafDxSe> (prm_idstr, prm_pGgafDxSe) {
}

void GgafDxSeConnection::processReleaseResource(GgafDxSe* prm_pResource) {
    GGAF_DELETE(prm_pResource);
}

