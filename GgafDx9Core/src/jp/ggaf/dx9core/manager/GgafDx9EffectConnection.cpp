#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9EffectConnection::GgafDx9EffectConnection(char* prm_idstr, GgafDx9Effect* prm_pEffect)
	:GgafResourceConnection<GgafDx9Effect>(prm_idstr, prm_pEffect) {
}

void GgafDx9EffectConnection::processReleaseResource(GgafDx9Effect* prm_pResource) {
	DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

