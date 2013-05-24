#include "stdafx.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxEffectConnection::GgafDxEffectConnection(char* prm_idstr, GgafDxEffect* prm_pEffect)
    :GgafResourceConnection<GgafDxEffect>(prm_idstr, prm_pEffect) {
}

void GgafDxEffectConnection::processReleaseResource(GgafDxEffect* prm_pResource) {
    _TRACE_("GgafDxEffect="<<prm_pResource->getName()<<" を開放します。");
    GGAF_DELETE(prm_pResource);
}

