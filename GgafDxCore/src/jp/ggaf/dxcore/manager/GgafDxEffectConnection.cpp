#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxEffectConnection::GgafDxEffectConnection(char* prm_idstr, GgafDxEffect* prm_pEffect)
	:GgafResourceConnection<GgafDxEffect>(prm_idstr, prm_pEffect) {
}

void GgafDxEffectConnection::processReleaseResource(GgafDxEffect* prm_pResource) {
	DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

