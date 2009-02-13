#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9EffectConnection::GgafDx9EffectConnection(char* prm_idstr, ID3DXEffect* prm_pID3DXEffect)
	:GgafResourceConnection<ID3DXEffect>(prm_idstr, prm_pID3DXEffect) {
}

void GgafDx9EffectConnection::processReleaseResource(ID3DXEffect* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}

