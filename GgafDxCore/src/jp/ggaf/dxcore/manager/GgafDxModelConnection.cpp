#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxModelConnection::GgafDxModelConnection(char* prm_idstr, GgafDxModel* prm_pModel) :
    GgafResourceConnection<GgafDxModel> (prm_idstr, prm_pModel) {
}

void GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) {
    prm_pResource->release(); //èdóv
    GGAF_DELETE(prm_pResource);
}

