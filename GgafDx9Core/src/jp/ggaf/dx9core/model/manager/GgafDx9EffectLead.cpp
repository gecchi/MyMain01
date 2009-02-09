#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9EffectLead::GgafDx9EffectLead(char* prm_idstr, ID3DXEffect* prm_pID3DXEffect)
	:GgafResourceLead<ID3DXEffect>(prm_idstr, prm_pID3DXEffect) {
}

void GgafDx9EffectLead::processReleaseResource(ID3DXEffect* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}

