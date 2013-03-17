#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBgmConnection::GgafDxBgmConnection(char* prm_idstr, GgafDxBgm* prm_pGgafDxBgm) :
    GgafResourceConnection<GgafDxBgm> (prm_idstr, prm_pGgafDxBgm) {
}

void GgafDxBgmConnection::processReleaseResource(GgafDxBgm* prm_pResource) {
    GGAF_DELETE(prm_pResource);
}

